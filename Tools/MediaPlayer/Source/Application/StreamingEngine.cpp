///
/// @brief      Simple Streaming Engine class
///

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "StreamingEngine.h"

#include "VDR/Interface/Unit/Audio/IVDRAudioUnits.h"
#include "VDR/Interface/Unit/Video/IVDRVideoUnits.h"
#include "VDR/Interface/Unit/Audio/IVDRAudioTypes.h"
#include "VDR/Interface/Unit/Memory/IVDRMemoryUnits.h"
#include "VDR/Interface/Unit/Datapath/IVDRDatapathUnits.h"
#include "STF/Interface/STFDebug.h"
#include "STF/Interface/STFTimer.h"

#define DBG_VDR_CMD_STRING(c)	((c==VDR_STRMCMD_NONE)?"NONE": \
	(c==VDR_STRMCMD_BEGIN)?"BEGIN": \
	(c==VDR_STRMCMD_DO)?"DO": \
	(c==VDR_STRMCMD_STEP)?"STEP": \
	(c==VDR_STRMCMD_FLUSH)?"FLUSH": \
	"???")
	
#define DP_SSD DP
#define DP_RM DP

///////////////////////////////////////////////////////////////////////////////
// Player Streaming Parser
///////////////////////////////////////////////////////////////////////////////

void PlayerStreamingParser::ThreadEntry(void)
	{

	while (!terminate)
		{
		WaitThreadSignal();

		if (segmentCompleted)
			{
				completionEvent.SetSignal();
			}
		}
	}


STFResult PlayerStreamingParser::NotifyThreadTermination(void)
	{
	SetThreadSignal();

	STFRES_RAISE_OK;
	}



STFResult PlayerStreamingParser::ParseRange(const VDRDataRange & range, uint32 & offset)
	{
	if (offset == range.size)
		STFRES_RAISE_OK;
	else
		{
		STFRES_RAISE(STFRES_OBJECT_FULL);
		}
	}


STFResult PlayerStreamingParser::ParseCommit(void)
	{
	STFRES_RAISE_OK;
	}


STFResult PlayerStreamingParser::ParseEndSegment(void)
	{
	segmentCompleted = true;

	STFRES_RAISE_OK;
	}


PlayerStreamingParser::PlayerStreamingParser()
	: STFThread("PlayerStreamingParser", 100000, STFTP_ABOVE_NORMAL)
	{
	segmentCompleted = false;
	}


PlayerStreamingParser::~PlayerStreamingParser(void)
	{
	}


STFResult PlayerStreamingParser::Initialize(void)
	{
	segmentCompleted = false;

	STFRES_RAISE_OK;
	}


STFResult PlayerStreamingParser::WaitForCompletion(void)
	{
	while (!segmentCompleted)
		completionEvent.Wait();

	STFRES_RAISE_OK;
	}
				 


///////////////////////////////////////////////////////////////////////////////
// Streaming Engine
///////////////////////////////////////////////////////////////////////////////

STFResult StreamingEngine::SendStreamData(bool preparing)
	{
	VDRDataRange	range;
	STFAutoMutex	lock(&streamLock);
	STFResult		res;
	uint32			done;
	//uint32			i, count;
	//uint32			*target;

	for(;;)
		{
		switch (stsState)
			{
			case STSS_INIT:
				DP_SSD("State = STSS_INIT\n");
				STFRES_RAISE_OK;
				break;

			case STSS_BEGIN_SEGMENT:
				DP_SSD("State = STSS_BEGIN_SEGMENT\n");
				lastRange = false;
				STFRES_REASSERT(outputFormatter.BeginSegment(0, false));

				stsState = STSS_DATA_DISCONTINUITY;
				// intentional drop-through

			case STSS_DATA_DISCONTINUITY:
				DP_SSD("State = STSS_DATA_DISCONTINUITY\n");
				STFRES_REASSERT(outputFormatter.PutDataDiscontinuity());

				stsState = STSS_BEGIN_GROUP;
				// intentional drop-through

			case STSS_BEGIN_GROUP:
				DP_SSD("State = STSS_BEGIN_GROUP\n");
				STFRES_REASSERT(outputFormatter.BeginGroup(0, false, false));

				stsState = STSS_GET_RANGE; // NHV: Guess this was the intended state change
				// intentional drop-through

			case STSS_GET_RANGE:
				//DP_SSD("State = STSS_GET_RANGE\n");
				STFRES_REASSERT(allocator->GetMemoryBlocks(&streamBlock, 0, 1, done));
				if (done != 1)
					{
					DP_SSD("SendStreamData: No empty MemoryBlocks\n");
					STFRES_RAISE(STFRES_NOT_ENOUGH_MEMORY);   // can not happen while preparing, as GetMemoryBlocks() will wait
					}
				stsState = STSS_READ_RANGE;
				// intentional drop-through

			case STSS_READ_RANGE:
				//DP_SSD("State = STSS_READ_RANGE - block: %x size: %d\n", streamBlock->GetStart(), streamBlock->GetSize());
				streamBlockSize = fread(streamBlock->GetStart(), 1, streamBlock->GetSize(), streamFile);
				if (streamBlockSize == 0)
					{
					stsState = STSS_END_GROUP;
					break;
					}

				stsState = STSS_SEND_RANGE;
				// intentional drop-through

			case STSS_SEND_RANGE:
				//DP_SSD("State = STSS_SEND_RANGE\n");
				range.block = streamBlock;
				range.offset = 0;
				range.size = streamBlockSize;
				//res = (outputFormatter.PutRange(range));
				//if (STFRES_FAILED(res))
				//	{
				//	DP_SSD("Data delivery bounced\n");
				//	STFRES_RAISE(res);
				//	}
				res = (outputFormatter.PutRange(range));
				while (res == STFRES_OBJECT_FULL)
				{
					STFRES_REASSERT(SystemTimer->WaitDuration(10));
					res = (outputFormatter.PutRange(range));
				}
				res = (outputFormatter.Commit());
				res = (outputFormatter.Commit());
			
				streamBlock->Release();
				streamBlock = NULL;

				stsState = STSS_GET_RANGE;
				break;

			case STSS_END_GROUP:
				DP_SSD("State = STSS_END_GROUP\n");
				STFRES_REASSERT(outputFormatter.CompleteGroup(false));

				stsState = STSS_TIME_DISCONTINUITY;
				// intentional drop-through

			case STSS_TIME_DISCONTINUITY:
				DP_SSD("State = STSS_TIME_DISCONTINUITY\n");
				STFRES_REASSERT(outputFormatter.PutTimeDiscontinuity());

				stsState = STSS_END_SEGMENT;
				// intentional drop-through

			case STSS_END_SEGMENT:
				DP_SSD("State = STSS_END_SEGMENT\n");
				STFRES_REASSERT(outputFormatter.CompleteSegment(true));	// We want the segment end notification to know when playback has finished!

				stsState = STSS_FINAL;
				// intentional drop-through

			case STSS_FINAL:
				DP_SSD("State = STSS_FINAL\n");
 				STFRES_RAISE_OK;
				break;

			case STSS_FRAME_START:
				DP("ERROR: StreamingTest::SendStreamData(%d) called in state STSS_FRAME_START\n", (int) preparing);
 				STFRES_RAISE_OK;
				break;
			}
		}
	}


//
// This function is called in the context of another thread (the one of the dispatcher)!
//
STFResult StreamingEngine::ReceiveMessage(STFMessage & message)
	{
	STFAutoMutex	lock(&streamLock);

	switch (message.message)
		{
		case VDRMID_STRM_COMMAND_COMPLETED:
			// Was a command completed?
			DP_RM("ReceiveMessage: VDRMID_STRM_COMMAND_COMPLETED\n");
			commandCompletionSignal.Set();
			break;

		case VDRMID_STRM_PACKET_ARRIVAL:
			// Have new data packets arrived?
			DP_RM("ReceiveMessage: VDRMID_STRM_PACKET_ARRIVAL\n");
			//inputParser.ParseReceivePacket();
			break;

		case VDRMID_MEMORY_POOL_ALLOCATOR_BLOCKS_AVAILABLE:
			DP_RM("ReceiveMessage: VDRMID_MEMORY_POOL_ALLOCATOR_BLOCKS_AVAILABLE\n");
		case VDRMID_STRM_PACKET_REQUEST:
			DP_RM("ReceiveMessage: VDRMID_STRM_PACKET_REQUEST\n");
			SendStreamData(false);
			break;

		case VDRMID_STRM_START_POSSIBLE:
			// Reception of this message signals that all mixer inputs in the streaming chain
			// have enough data queued up to allow starting the streaming (= send of DO command now possible)
			DP_RM("*** Stream start possible!\n");
			streamingStartupSignal.Set();
			break;

		case VDRMID_STRM_START_REQUIRED:
			// This message signals that at least one of the mixer inputs has all its queues full
			// and must be started immediately. Sending the DO command is now required.
			DP_RM("*** Stream start required!\n");
			streamingStartupSignal.Set();
			break;

		// This message signals the end of presentation
		// Normally, we would have to check the parameter if really the right
		// segment was ended. But in this example, there is just one, so we do not really care.
		case VDRMID_STRM_SEGMENT_END:
		  //inputParser.segmentCompleted = true;
		  //inputParser.SetThreadSignal();
			break;
		default:
			DP("ReceiveMessage: unhandled message \n");
			
		}
	
	message.Complete();

	STFRES_RAISE_OK;
	}


STFResult StreamingEngine::DoCommand(VDRStreamingCommand com, uint32 param)
	{
	STFResult res;
	
	DP("%s : ENTER\n", __FUNCTION__);
	commandCompletionSignal.Reset();
	
	res = playerProxy->SendCommand(com, param);
	DP("Sending command %d (%s).\n", com, DBG_VDR_CMD_STRING(com));

	if (res == STFRES_PROCESSING_COMMAND)
		DP("Already processing command.\n");
	else if (STFRES_FAILED(res))
		DP("Command %d (%s) processing error: 0x%08x\n", com, DBG_VDR_CMD_STRING(com), res);

	// Wait for command to be completed within 3000 ms
	res = commandCompletionSignal.WaitTimeout(STFLoPrec32BitDuration(3000));

	if (res == STFRES_TIMEOUT)
		DP("Command %d (%s) timed out!\n", com, DBG_VDR_CMD_STRING(com));
	else if (res == STFRES_OK)
		DP("Command %d (%s) Completed successfully!\n", com, DBG_VDR_CMD_STRING(com));
	else
		DP("Command %d (%s) Unknown Error!\n", com, DBG_VDR_CMD_STRING(com));

	STFRES_RAISE_OK;
	}


STFResult StreamingEngine::StartStreaming(void)
	{
	STFResult res;
		
	rangeCount = 0;
	
	DP("%s: ENTER\n", __FUNCTION__);

	//inputParser.Initialize();
	//DP("inputParser Initialized\n");

	// Start the input parser's thread
	//inputParser.StartThread();
	//DP("inputParser Thread Started\n");

	//container = NULL;
	streamingStartupSignal.Reset();
	STFRES_REASSERT(DoCommand(VDR_STRMCMD_BEGIN, VDR_STRMDIR_FORWARD));
	DP("Streaming in forward direction\n");

	stsState = STSS_BEGIN_SEGMENT;
	
	DP("Opening Media file\n");
	if (streamFile == NULL)
		{
		DP("fopen(\"%s\",\"rb\")\n", fileName);
		streamFile = fopen(fileName, "rb");
		if (streamFile == NULL)
			{
			DP("File not found!\n");
			return STFRES_OBJECT_NOT_FOUND;
			}
		}

	SendStreamData(true);

	// Now wait until the streaming chain signals that streaming can or must be started

	res = streamingStartupSignal.WaitTimeout(STFLoPrec32BitDuration(3000));
	if (res == STFRES_OK)
		{	
		STFRES_REASSERT(DoCommand(VDR_STRMCMD_DO, 0x10000));
		}
	else if (res == STFRES_TIMEOUT)
		{
		DP("Timed out waiting for startup signal!\n");
		}
	else
		DP("Unknown error for startup signal! res = 0x%x\n", res);

	STFRES_RAISE_OK;
	}


STFResult StreamingEngine::WaitStreaming(void)
	{
	  //inputParser.WaitForCompletion();

	STFRES_RAISE_OK;
	}


STFResult StreamingEngine::EndStreaming(void)
	{
	// First issue a Flush command (mandatory!)
	STFRES_RAISE(DoCommand(VDR_STRMCMD_FLUSH, 0));
	}


STFResult StreamingEngine::TestStreaming(void)
	{
	STFTimer         myTimer;
	
	STFRES_REASSERT(PrepareTest());
	
	DP("StreamingEngine PrepareStreaming\n");
	STFRES_REASSERT(StartStreaming());
	
	DP("StreamingEngine Wait 10 seconds\n");
	STFRES_REASSERT(myTimer.WaitDuration(10000));
	
	DP("StreamingEngine EndStreaming\n");
	STFRES_REASSERT(EndStreaming());
	
	DP("DVDtestApp Dumping...");
	WriteDebugRecording ("trace_dump.txt");
	
	DP("StreamingEngine Wait 2 seconds\n");
	STFRES_REASSERT(myTimer.WaitDuration(2000));
	
	DP("TestStreaming Exit.\n");
	STFRES_RAISE_OK;
	}


STFResult StreamingEngine::WaitForCommandtoFinish(IVDRStreamingProxyUnit * proxy, int waitMs, VDRStreamingState targetState)
	{
	VDRStreamingState curState;
	STFResult res = STFRES_TIMEOUT;
	int count = waitMs / 100;

	while (count--)
		{
		proxy->GetState(curState);

		if (curState == targetState)
			{
			res = STFRES_OK;
			break;
			}
		SystemTimer->WaitDuration(100);
		}
	assert (curState == targetState);

	return res;
	}

// 
STFResult StreamingEngine::Initialize(int argc, char**argv)
{
	STFResult res;
	commandCompletionSignal.Reset();

	fileName = (char*) argv[1];

	for (int i = 0; i < argc; ++i) 
	{
		DP(" Received : %s \n", argv[i]);
	}
	
	DP("Creating an instance of the driver component, and getting its interface.\n");
	STFRES_REASSERT(VDRCreateDriverInstance("VDRLinux", 0, driver));

	DP("Asking the driver component for the UnitSet Factory interface.\n");
	if (STFRES_IS_ERROR(driver->QueryInterface (VDRIID_VDR_UNITSET_FACTORY, (void*&)unitSetFactory)))
	{
		STFRES_RAISE(STFRES_NOT_ENOUGH_MEMORY);
	}
		
	DP("Creating a UnitSet containing a Streaming Unit and a Playback Pool Allocator.\n");
	if (STFRES_IS_ERROR(unitSetFactory->CreateUnitSet(
				decoderUnitSet,
				VDRUID_GENERIC_PLAYBACK_POOL_ALLOCATOR,
				VDRUID_DVD_STREAM_TRANSDUCER_PROXY,
				VDR_UNITS_DONE)))
	{
		STFRES_RAISE(STFRES_NOT_ENOUGH_MEMORY);
	}


	DP("Get interface of the memory pool allocator for storing compressed data.\n");
	if (STFRES_IS_ERROR(decoderUnitSet->QueryUnitInterface(
		VDRUID_GENERIC_PLAYBACK_POOL_ALLOCATOR,
		VDRIID_VDR_MEMORYPOOL_ALLOCATOR,
		(void*&)allocator)))
	{
		STFRES_RAISE(STFRES_NOT_ENOUGH_MEMORY);
	}
	
	DP("Ask for Tag Unit interface of the memory pool allocator, and configure something just for that unit.\n");	
	if (STFRES_IS_ERROR(decoderUnitSet->QueryUnitInterface(
		VDRUID_GENERIC_PLAYBACK_POOL_ALLOCATOR,
		VDRIID_VDR_TAG_UNIT,
		(void*&)allocTags)))
	{
		STFRES_RAISE(STFRES_NOT_ENOUGH_MEMORY);
	}
	
	DP("Configure the pool allocator for the compressed data memory pool.\n");
	// 320kBytes size -> >= 20 streaming data packets
	// We want it to be divided into 64 blocks of 2048 bytes each
	// DWORD aligned
	//
	allocTags->Configure(SET_MEMPOOL_TOTALSIZE(32 * 1024 * 1024) +
		SET_MEMPOOL_BLOCKSIZE(2048) +
		SET_MEMPOOL_ALIGNMENT_FACTOR(4) +
		SET_MEMPOOL_POOLNAME("decoder memory buffer") +
		TAGDONE);
	allocTags->Release();

	if (STFRES_IS_ERROR(decoderUnitSet->QueryUnitInterface(
		VDRUID_GENERIC_PLAYBACK_POOL_ALLOCATOR,
		VDRIID_VDR_MESSAGE_SINK_REGISTRATION,
		(void*&)memorySinkRegistration)))
	{
		STFRES_RAISE(STFRES_NOT_ENOUGH_MEMORY);
	}
	
	DP("Register \"this\" as message sink at the Streaming Unit to receive Memory Pool Messages.\n");
	memorySinkRegistration->RegisterMessageSink(this);
	memorySinkRegistration->Release();

	DP("Get streaming proxy interface of the DVD Stream Transducer Streaming Chain Unit.\n");
	if (STFRES_IS_ERROR(decoderUnitSet->QueryUnitInterface(
		VDRUID_DVD_STREAM_TRANSDUCER_PROXY,
		VDRIID_VDR_STREAMING_PROXY_UNIT,
		(void*&)playerProxy)))
	{
		STFRES_RAISE(STFRES_NOT_ENOUGH_MEMORY);
	}
	
	playerProxy->GetState(curState);
	DP("Initial state of Player Streaming Chain is: %d\n", curState);
	
	DP("Get Message Sink Registration interface of the DVD Stream Transducer Streaming Chain Unit.\n");
	if (STFRES_IS_ERROR(decoderUnitSet->QueryUnitInterface(
		VDRUID_DVD_STREAM_TRANSDUCER_PROXY,
		VDRIID_VDR_MESSAGE_SINK_REGISTRATION,
		(void*&)sinkRegistration)))
	{
		STFRES_RAISE(STFRES_NOT_ENOUGH_MEMORY);
	}
	
	DP("Register \"this\" as message sink at the Streaming Unit.\n");
	sinkRegistration->RegisterMessageSink(this);
	

	//DP("Connect input & output\n");
	//if (STFRES_IS_ERROR(inputParser.Connect(playerProxy, 1)))
	//{
	//	DP("### Connecting output of playerProxy failed!\n");
	//}
	//else
	//{
	//	DP("inputParser.Connect(playerProxy, 1) succesfull.\n");
	//}

	if (STFRES_IS_ERROR(outputFormatter.Connect(playerProxy, 0)))
	{
		DP("### Connecting input of playerProxy failed!\n");
	}
	else
	{
		DP("outputFormatter.Connect(playerProxy, 0) succesfull.\n");
	}
#if 0
	if (STFRES_IS_ERROR(playerProxy->ProvideAllocator(0, allocator)))
	{
		DP("### ProvideAllocator failed!\n");
		STFRES_RAISE(STFRES_NOT_ENOUGH_MEMORY);
	}
	else
	{
		DP("ProvideAllocator succesfull.\n");
	}
#endif
	if (STFRES_IS_ERROR(decoderUnitSet->ActivateAndLock(VDRUALF_REALTIME_PRIORITY | VDRUALF_TIME_VALID, 
		STFHiPrec64BitTime(), 
		STFHiPrec32BitDuration(0))))
	{
		DP("### Activate of Unit Set failed!\n");
		STFRES_RAISE(STFRES_NOT_ENOUGH_MEMORY);
	}
	
	DP("Initialized succesfully.\n");
	STFRES_RAISE_OK;
}

STFResult StreamingEngine::Cleanup(void)
{
	DP("Disconnecting Output Formatter\n");
	outputFormatter.Disconnect();

	if (sinkRegistration)
		{
		DP("Releasing SinkRegistration\n");
		sinkRegistration->Release();
		sinkRegistration = NULL;
		}

	if (playerProxy)
		{
		DP("Releasing decoderProxy\n");
		playerProxy->Release();
		playerProxy = NULL;
		}

	if (decoderUnitSet)
		{
		DP("Unlocking and Passivating decoderUnitSet\n");
		decoderUnitSet->Unlock();
		decoderUnitSet->Passivate();
		}

	if (unitSetFactory)
		{
		DP("Releasing unitSetFactory\n");
		unitSetFactory->Release();
		unitSetFactory = NULL;
		}
		
	DP("Cleanup succesfully.\n");
	
	STFRES_RAISE_OK;
}

STFResult StreamingEngine::PrepareTest(void)
{
	STFRES_RAISE_OK;
}
// NHV

// This function decides which sort of streaming test is executed.
#if 0 // NHV: Not yet removed, example.
STFResult StreamingTestController::ExecuteTest (void)
	{
	STFResult res;

	// First set up the data source.

	// Create a harddisk file as the data source.
	DriveSectorFile *sectorFile;
	sectorFile = new DriveSectorFile (this->driver);
	if (sectorFile == NULL)
		{
		DP("File %s, line %d: Can't create data source, no memory\n", __FILE__, __LINE__);
		STFRES_RAISE(STFRES_NOT_ENOUGH_MEMORY);
		}
	res = sectorFile->Initialize ();
	if (STFRES_FAILED(res))
		{
		DP("File %s, line %d: Can't init data source, error %08x\n", __FILE__, __LINE__, res);
		STFRES_RAISE(res);
		}

	// Create a data source that works out of a memory buffer.
	BufferedExternalFileDataSource *dataSource = new BufferedExternalFileDataSource;
	if (dataSource == NULL)
		{
		DP("File %s, line %d: Can't create data source\n", __FILE__, __LINE__);
		STFRES_RAISE(STFRES_NOT_ENOUGH_MEMORY);
		}

	streamingTest = new ProgramStreamPlayback (driver, dataSource);

	// Execute the Streaming Test
	if (STFRES_FAILED(res = streamingTest->TestStreaming()))
		{
		DP("Streaming test returned with error result: %x\n", res);
		}

	STFRES_RAISE_OK;
	}
#endif

// This function is called in the context of another thread (the one of the dispatcher)!
STFResult CommandCompletionMessageSink::ReceiveMessage(STFMessage & message)
	{
	if (message.message == VDRMID_STRM_COMMAND_COMPLETED)
		{
		// Was a command completed?
		commandCompleteSignal.Set();
		}

	message.Complete();
	STFRES_RAISE_OK;
	}

STFResult CommandCompletionMessageSink::WaitForCommandCompletion(uint32 waitMs)
	{
	return(commandCompleteSignal.WaitTimeout(STFLoPrec32BitDuration(waitMs)));
	}

STFResult	CommandCompletionMessageSink::ResetSignal()
	{ 
	commandCompleteSignal.Reset(); 
	STFRES_RAISE_OK;
	}



