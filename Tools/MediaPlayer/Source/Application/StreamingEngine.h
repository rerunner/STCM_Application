//
// PURPOSE:		Streaming Test application
//

#ifndef STREAMINGENGINE_H
#define STREAMINGENGINE_H

#include "VDR/Interface/Base/IVDRLayer.h"
#include "VDR/Interface/Unit/IVDRUnitSetFactory.h"
#include "VDR/Interface/Unit/Board/IVDRBoard.h"
#include "VDR/Interface/Streaming/IVDRStreaming.h"
#include "VDR/Support/Streaming/VDRStreamingFormatter.h"
#include "STF/Interface/STFGenericDebug.h"
#include "STF/Interface/Types/STFMessage.h"


class PlayerStreamingParser : public VDRStreamingParser, public STFThread
	{
	friend class StreamingEngine;

	protected:
		bool		segmentCompleted;
		STFSignal	completionEvent;

		void 		ThreadEntry(void);
		STFResult 	NotifyThreadTermination(void);

	public:
		PlayerStreamingParser(void);
		~PlayerStreamingParser(void);

		STFResult Initialize(void);

		STFResult WaitForCompletion(void);

		virtual STFResult ParseEndSegment(void);
		virtual STFResult ParseCommit(void);
		virtual STFResult ParseRange(const VDRDataRange & range, uint32 & offset);
	};


// Streaming Test class - is a dispatched message sink for registering at streaming proxy unit
class StreamingEngine : public DispatchedSTFMessageSink
	{
	protected:
		TriggeredWaitableQueuedSTFMessageProcessingDispatcher	* dispatcher;
		ThreadedSTFMessageDispatcher * threadedDispatcher;

		STFTimeoutSignal	commandCompletionSignal;	// Signal streaming command completion from dispatcher thread
		STFTimeoutSignal	streamingStartupSignal;		// Signal streaming startup completion

		IVDRBase				*	driver;				// Driver Interface
		IVDRStreamingProxyUnit	*	playerProxy;		// Streaming Proxy Unit interface of the Player Chain Unit
 		IVDRMemoryPoolAllocator	*	allocator;			// Interface to the allocator providing us with VDRMemoryBlocks

		VDRStreamingFormatter		outputFormatter;
		//PlayerStreamingParser		inputParser;

		char						* fileName; // QnD
		FILE						* streamFile;
		VDRMemoryBlock				* streamBlock;
		int32						streamBlockSize;

		STFMutex					streamLock;

		uint8						*	pcmMem;
		uint32						curMemPtr;

		uint32						rangeCount;

		bool						fileLoaded;
		bool						lastRange;
		
		STFResult                    res;
		IVDRUnitSetFactory          *unitSetFactory;
		IVDRUnitSet                 *decoderUnitSet;
		IVDRTagUnit                 *allocTags;
		IVDRMessageSinkRegistration *sinkRegistration, *memorySinkRegistration;
		VDRStreamingState            curState;       /// Current state of Streaming Chain

		bool		segmentCompleted;

		enum StreamingTestStreamState
			{
			STSS_INIT,		  
			STSS_DATA_DISCONTINUITY,
			STSS_BEGIN_SEGMENT,
			STSS_BEGIN_GROUP,
			STSS_FRAME_START,
			STSS_GET_RANGE,
			STSS_READ_RANGE,
			STSS_SEND_RANGE,
			STSS_END_GROUP,
			STSS_END_SEGMENT,
			STSS_TIME_DISCONTINUITY,
			STSS_FINAL
			} stsState;

		STFResult SendStreamData(bool preparing);

		STFResult DoCommand(VDRStreamingCommand com, uint32 param);
		
		// Override from DispatchedSTFMessageSink - receives streaming messages
		virtual STFResult ReceiveMessage(STFMessage & message);

		STFResult StartStreaming(void);
		STFResult WaitStreaming(void);
		STFResult EndStreaming(void);

		//virtual STFResult PrepareTest(void) = 0;

		STFResult WaitForCommandtoFinish(IVDRStreamingProxyUnit * proxy, int waitMs=2000, VDRStreamingState targetState=VDR_STRMSTATE_READY);

	public:
		StreamingEngine(IVDRBase * driver) : 
			DispatchedSTFMessageSink(threadedDispatcher = new ThreadedSTFMessageDispatcher("MessageThread", 20000, STFTP_NORMAL, dispatcher = new TriggeredWaitableQueuedSTFMessageProcessingDispatcher(32)))
			{
			this->driver = driver;

			driver->AddRef();
			
			streamFile = NULL;

			stsState = STSS_INIT;

			segmentCompleted = false;
			}

		virtual ~StreamingEngine()
			{
			driver->Release();
			}

		STFResult TestStreaming(void);
		STFResult Initialize (int argc, char**argv);
		STFResult Cleanup(void);
		STFResult PrepareTest(void);
	};


class CommandCompletionMessageSink: public DispatchedSTFMessageSink
	{
	protected:
		STFTimeoutSignal	commandCompleteSignal;	// Signal streaming command completion from dispatcher thread

	public:
		CommandCompletionMessageSink(ThreadedSTFMessageDispatcher * threadedDispatcher)	: DispatchedSTFMessageSink(threadedDispatcher)	{	}
		virtual ~CommandCompletionMessageSink(void) { }
		
		// Override from DispatchedSTFMessageSink - receives streaming messages
		virtual STFResult ReceiveMessage(STFMessage & message);

		virtual STFResult	WaitForCommandCompletion(uint32 waitMs);
		virtual STFResult	ResetSignal();
	};

#endif // STREAMINGENGINE

