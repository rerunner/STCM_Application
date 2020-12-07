#include "ThreadConfiguration.h"

const uint32	TCTP_DV_AUDIO_DECODER						=			STFTP_NORMAL;
const char		TCTN_DV_AUDIO_DECODER[]	   				=			"DVAudDec";
const uint32	TCSS_DV_AUDIO_DECODER						=			17000;

const uint32 TCTP_AC3_DECODER  =			STFTP_ABOVE_NORMAL;
const uint32 TCSS_AC3_DECODER  =			20000;
const char TCTN_AC3_DECODER[] =			"PCMPlayer";

const uint32 TCTP_SDL2_VIDEO_RENDERER  =			STFTP_ABOVE_NORMAL;
const uint32 TCSS_SDL2_VIDEO_RENDERER  =			20000;
const char TCTN_SDL2_VIDEO_RENDERER[] =			"SDL2VRen";

const uint32	TCTP_WIN32_DV_DECODER						=			STFTP_NORMAL;
const char		TCTN_WIN32_DV_DECODER[]	   				=			"W32DVDec";
const uint32	TCSS_WIN32_DV_DECODER						=			30000;

const uint32	TCTP_ASV_VDR_INTERFACE						=			STFTP_NORMAL;
const char		TCTN_ASV_VDR_INTERFACE[]					=			"ASVVDRInt";
const uint32	TCSS_ASV_VDR_INTERFACE						=			17000;

const uint32	TCTP_FRAME_REORDER							=			STFTP_NORMAL;
const uint32	TCSS_FRAME_REORDER							=			17000;

const uint32	TCTP_ENCODERWORKER_INPUTDATA				=			STFTP_NORMAL;
const uint32	TCSS_ENCODERWORKER_INPUTDATA				=			17000;

const uint32	TCTP_ENCODERWORKER_OUTPUTPACKET				=			STFTP_NORMAL;
const uint32	TCSS_ENCODERWORKER_OUTPUTPACKET				=			17000;

const uint32	TCTP_MMECLIENT								=			STFTP_NORMAL;
const uint32	TCSS_MMECLIENT								=			0x10000;

const uint32	TCTP_MMECLIENT_SENDBUFFERSQUEUE				=			STFTP_NORMAL;
const uint32	TCSS_MMECLIENT_SENDBUFFERSQUEUE				=			0x10000;

const uint32	TCTP_JPEG_FRAME_STREAM_DECODER				=			STFTP_NORMAL;
const uint32	TCSS_JPEG_FRAME_STREAM_DECODER				=			20000;
const char		TCTN_JPEG_FRAME_STREAM_DECODER[]			=			"JFSD";

const uint32	TCTP_WIN32_APPLICATION_WINDOW				=			STFTP_NORMAL;
const uint32	TCSS_WIN32_APPLICATION_WINDOW				=			20000;

const uint32	TCTP_WIN32_GRAPHICAL_RUNTIME_CONFIGURATOR	=			STFTP_NORMAL;
const uint32	TCSS_WIN32_GRAPHICAL_RUNTIME_CONFIGURATOR	=			20000;

const uint32	TCTP_WIN32_COMM_PROXY						=			STFTP_NORMAL;
const uint32	TCSS_WIN32_COMM_PROXY						=			20000;
const char		TCTN_WIN32_COMM_PROXY[]						=			"Win32CommProxy";

const uint32	TCTP_VIDEO_STREAMMIXER						=			STFTP_13;
const uint32	TCSS_VIDEO_STREAMMIXER						=			OSAL_MIN_STACK_SIZE;
const char		TCTN_VIDEO_STREAMMIXER[]					=			"VStrMix";

const uint32	TCTP_VIDEO_STREAMMIXER_INPUT				=			STFTP_9;
const uint32	TCSS_VIDEO_STREAMMIXER_INPUT				=			OSAL_MIN_STACK_SIZE;
const char		TCTN_VIDEO_STREAMMIXER_INPUT[]				=			"VMixDsp";

const uint32	TCTP_AUDIO_STREAMMIXER						=			STFTP_9;
const uint32	TCSS_AUDIO_STREAMMIXER						=			OSAL_MIN_STACK_SIZE;
const char		TCTN_AUDIO_STREAMMIXER[]					=			"AStrMix";

const uint32	TCTP_AUDIO_STREAMMIXER_INPUT				=			STFTP_9;
const uint32	TCSS_AUDIO_STREAMMIXER_INPUT				=			OSAL_MIN_STACK_SIZE;																				   
const char		TCTN_AUDIO_STREAMMIXER_INPUT[]				=			"AMixDsp";

const uint32	TCTP_SPDIF_STREAMMIXER						=			STFTP_9;
const uint32	TCSS_SPDIF_STREAMMIXER						=			OSAL_MIN_STACK_SIZE;
const char		TCTN_SPDIF_STREAMMIXER[]					=			"SStrMix";

const uint32	TCTP_SPDIF_STREAMMIXER_INPUT				=			STFTP_9;
const uint32	TCSS_SPDIF_STREAMMIXER_INPUT				=			OSAL_MIN_STACK_SIZE;
const char		TCTN_SPDIF_STREAMMIXER_INPUT[]				=			"SMixDsp";

const uint32	TCTP_PCM_PLAYER								=			STFTP_ABOVE_NORMAL;
const uint32	TCSS_PCM_PLAYER								=			10000;
const char		TCTN_PCM_PLAYER[]							=			"PCMPlayer";

const uint32	TCTP_VIDEORENDERER							=			STFTP_ABOVE_NORMAL;
const uint32	TCSS_VIDEORENDERER							=			0x10000;
const char		TCTN_VIDEORENDERER[]						=			"Win32VideoRenderer";

const uint32	TCTP_AUDIO_FRAME_STREAM_DECODER				=			STFTP_ABOVE_NORMAL;
const uint32	TCSS_AUDIO_FRAME_STREAM_DECODER				=			20000;
const char		TCTN_AUDIO_FRAME_STREAM_DECODER[]			=			 "AFSD";

const uint32	TCTP_DVP_INTERRUPT_SERVICE					=			STFTP_ABOVE_NORMAL;
const uint32	TCSS_DVP_INTERRUPT_SERVICE					=			0x8000;

const uint32	TCTP_WIN32_INTERRUPT_CONTROLLER				=			STFTP_ABOVE_NORMAL;
const uint32	TCSS_WIN32_INTERRUPT_CONTROLLER				=			0x8000;

const uint32	TCTP_IEEE_1394_BUS                       	=			STFTP_ABOVE_NORMAL;
const uint32	TCSS_IEEE_1394_BUS                       	=			20000;

const uint32	TCTP_CPU_VIDEO_FORMAT_CONVERTER				=			STFTP_BELOW_NORMAL;
const uint32	TCSS_CPU_VIDEO_FORMAT_CONVERTER				=			20000;

const uint32	TCTP_MPEG_VIDEO_DATAHANDLER					=			STFTP_HIGHER;
const uint32	TCSS_MPEG_VIDEO_DATAHANDLER					=			20000;
const char		TCTN_MPEG_VIDEO_DATAHANDLER[]				=			"MPEGViDataHandler";

const uint32	TCTP_MPEG_STRATEGIC_VIDEO_DECODER			=			STFTP_HIGHER;
const uint32	TCSS_MPEG_STRATEGIC_VIDEO_DECODER			=			20000;
const char		TCTN_MPEG_STRATEGIC_VIDEO_DECODER[]			=			"MPEGViDecDriver";

const uint32	TCTP_MPEG_SUBPICTURE_DATAHANDLER			=			STFTP_HIGHER;
const uint32	TCSS_MPEG_SUBPICTURE_DATAHANDLER			=			20000;
const char		TCTN_MPEG_SUBPICTURE_DATAHANDLER[]			=			"SubpicDataHandler";

const uint32	TCTP_MPEG_STRATEGIC_SUBPICTURE_DECODER		=			STFTP_HIGHER;
const uint32	TCSS_MPEG_STRATEGIC_SUBPICTURE_DECODER		=			20000;
const char		TCTN_MPEG_STRATEGIC_SUBPICTURE_DECODER[]	=			"SPDecDriver";

const uint32	TCTP_DRIVE									=			STFTP_HIGHEST;
const uint32	TCSS_DRIVE									=			0x4000;

const uint32	TCTP_MEMORY_MESSAGE_DISPATCHER				=			STFTP_15;
const uint32	TCSS_MEMORY_MESSAGE_DISPATCHER				=			20000;
const char		TCTN_MEMORY_MESSAGE_DISPATCHER[]			=			"MMsgPrc";

const uint32	TCTP_GENERIC_MESSAGE_DISPATCHER				=			STFTP_15;
const uint32	TCSS_GENERIC_MESSAGE_DISPATCHER				=			20000;
const char		TCTN_GENERIC_MESSAGE_DISPATCHER[]			=			"GMsgPrc";

const uint32	TCTP_VBI_LINEPARSER							=			STFTP_ABOVE_NORMAL;
const uint32	TCSS_VBI_LINEPARSER							=			OSAL_MIN_STACK_SIZE;
const char		TCTN_VBI_LINEPARSER[]						=			"VbiLineParser";

const uint32	TCTP_VIDEO_BLITTER							=			STFTP_13;
const uint32	TCSS_VIDEO_BLITTER							=			OSAL_MIN_STACK_SIZE;
const char		TCTN_VIDEO_BLITTER[]						=			"DeferredBlitter";

const uint32	TCTP_CGMS									=			STFTP_HIGHER;
const uint32	TCSS_CGMS									=			OSAL_MIN_STACK_SIZE;
const char		TCTN_CGMS[]									=			"CGMSApp";

const uint32	TCTP_GEMSTAR								=			STFTP_HIGHER;
const uint32	TCSS_GEMSTAR								=			OSAL_MIN_STACK_SIZE;
const char		TCTN_GEMSTAR[]								=			"GemstarApp";

const uint32	TCTP_NICAM									=			LOW_PRIORITY;
const uint32	TCSS_NICAM									=			OSAL_MIN_STACK_SIZE;
const char		TCTN_NICAM[]								=			"NICAM_LOOP";

const uint32	TCTP_DEFAULT_DELAY_LOOP						=			STFTP_7;
const uint32	TCSS_DEFAULT_DELAY_LOOP						=			OSAL_MIN_STACK_SIZE;
const char		TCTN_DEFAULT_DELAY_LOOP[]					=			"PER_SECOND_TASK_LOOP";

const uint32	TCTP_TELETEXT								=			STFTP_HIGHER;
const uint32	TCSS_TELETEXT								=			OSAL_MIN_STACK_SIZE;
const char		TCTN_TELETEXT[]								=			"TeletextApp";

const uint32	TCTP_CHANNEL								=			LOW_PRIORITY;
const uint32	TCSS_CHANNEL								=			OSAL_MIN_STACK_SIZE;
const char		TCTN_CHANNEL[]								=			"TUNECH_LOOP";

const uint32	TCTP_CONTROLLER_DEFAULT						=			LOW_PRIORITY;
const uint32	TCSS_CONTROLLER_DEFAULT						=			OSAL_MIN_STACK_SIZE;
const char		TCTN_CONTROLLER_DEFAULT[]					=			"UNDEFINED_CONTROLLER";

const uint32	TCTP_VBIGENERATOR							=			STFTP_ABOVE_NORMAL;
const uint32	TCSS_VBIGENERATOR							=			OSAL_MIN_STACK_SIZE;
const char		TCTN_VBIGENERATOR[]							=			"VBIGeneratorThread";

const uint32	TCTP_VPS									=			STFTP_HIGHER; 
const uint32	TCSS_VPS									=			OSAL_MIN_STACK_SIZE;
const char		TCTN_VPS[]									=			"VPSApp";

const uint32	TCTP_AUTOSEARCH								=			LOW_PRIORITY;
const uint32	TCSS_AUTOSEARCH								=			OSAL_MIN_STACK_SIZE;
const char		TCTN_AUTOSEARCH[]							=			"SEARCH_LOOP";

const uint32	TCTP_AVF_PARSER						    	=			STFTP_HIGHER;
const uint32	TCSS_AVF_PARSER								=			OSAL_MIN_STACK_SIZE;
const char		TCTN_AVF_PARSER[]							=			"ASFParserThread";

const uint32	TCTP_AVI_PARSER                         	=			STFTP_HIGHER;
const uint32	TCSS_AVI_PARSER                         	=			OSAL_MIN_STACK_SIZE;
const char		TCTN_AVI_PARSER[]                         	=			"AVIParserThread";

const uint32	TCTP_GENERIC_VDR_INTERFACE              	=			STFTP_NORMAL;
const uint32	TCSS_GENERIC_VDR_INTERFACE              	=			OSAL_MIN_STACK_SIZE;
const char		TCTN_GENERIC_VDR_INTERFACE[]              	=			"DVDPlayerVDRInterface";

const uint32	TCTP_DDP_GLOBAL_SCHEDULER               	=			STFTP_NORMAL;
const uint32	TCSS_DDP_GLOBAL_SCHEDULER               	=			OSAL_MIN_STACK_SIZE;
const char		TCTN_DDP_GLOBAL_SCHEDULER[]              	=			"DDPGlobalScheduler";

const uint32	TCTP_DDP_PLAYER_SCHEDULER               	=			STFTP_NORMAL;
const uint32	TCSS_DDP_PLAYER_SCHEDULER				   	=			OSAL_MIN_STACK_SIZE;
const char		TCTN_DDP_PLAYER_SCHEDULER[]               	=			"DDPPlayerScheduler";

const uint32	TCTP_AVF_STREAM_SERVER			        	=			STFTP_ABOVE_NORMAL;
const uint32	TCSS_AVF_STREAM_SERVER						=			OSAL_MIN_STACK_SIZE;
const char		TCTN_AVF_STREAM_SERVER[] 					=			"AVFSSThread";

const uint32	TCTP_AVF_DRIVE_BLOCK_POOL					=			STFTP_ABOVE_NORMAL;
const uint32	TCSS_AVF_DRIVE_BLOCK_POOL					=			OSAL_MIN_STACK_SIZE;
const char		TCTN_AVF_DRIVE_BLOCK_POOL[]  				=			"AVFDBPThread";

const uint32	TCTP_BURNING_BOX							=			STFTP_BELOW_NORMAL;
const uint32	TCSS_BURNING_BOX							=			OSAL_MIN_STACK_SIZE;
const char		TCTN_BURNING_BOX[]							=			"BurningBoxThread";

const uint32	TCTP_DDP_RECORDER_SCHEDULER					=			STFTP_NORMAL;
const uint32	TCSS_DDP_RECORDER_SCHEDULER					=			OSAL_MIN_STACK_SIZE;
const char		TCTN_DDP_RECORDER_SCHEDULER[]				=			"DDPGlobalRecorderScheduler";

const uint32	TCTP_DSI_MANAGER							=			STFTP_BELOW_NORMAL;
const uint32	TCSS_DSI_MANAGER							=			OSAL_MIN_STACK_SIZE;
const char		TCTN_DSI_MANAGER[]							=			"DSIMgrThread";

const uint32	TCTP_PLAYER_SYS_EVENT_HANDLER				=			STFTP_BELOW_NORMAL;
const uint32	TCSS_PLAYER_SYS_EVENT_HANDLER				=			OSAL_MIN_STACK_SIZE;
const char		TCTN_PLAYER_SYS_EVENT_HANDLER[]				=			"PlayerMessageDispatcherThread";

const uint32	TCTP_TIMER_TICK								=			STFTP_BELOW_NORMAL;
const uint32	TCSS_TIMER_TICK								=			OSAL_MIN_STACK_SIZE;
const char		TCTN_TIMER_TICK[]							=			"TimerTickThread";

const uint32	TCTP_DDP_GLOBAL_RECORDER_SCHEDULER			=			STFTP_NORMAL;
const uint32	TCSS_DDP_GLOBAL_RECORDER_SCHEDULER			=			OSAL_MIN_STACK_SIZE;
const char		TCTN_DDP_GLOBAL_RECORDER_SCHEDULER[]		=			"DDP Recorder Scheduler";

const uint32	TCTP_DVDRECORDER_THREAD						=			STFTP_5;
const uint32	TCSS_DVDRECORDER_THREAD            			=			OSAL_MIN_STACK_SIZE;
const char		TCTN_DVDRECORDER_THREAD[]					=			"DVDRecoderMessageProcessor";

const uint32	TCTP_EVENT_SCHEDULER						=			STFTP_HIGHEST;
const uint32	TCSS_EVENT_SCHEDULER						=			OSAL_MIN_STACK_SIZE;
const char		TCTN_EVENT_SCHEDULER[]						=			"EventScheduler";

const uint32	TCTP_HOST_RECEIVER							=			STFTP_ABOVE_NORMAL;
const uint32	TCSS_HOST_RECEIVER							=			OSAL_MIN_STACK_SIZE;
const char		TCTN_HOST_RECEIVER[]						=			"HostRec";

const uint32	TCTP_PACKET_ARRIVAL							=			STFTP_HIGHER;
const uint32	TCSS_PACKET_ARRIVAL							=			OSAL_MIN_STACK_SIZE;
const char		TCTN_PACKET_ARRIVAL[]						=			"PacketArrivalThread";

const uint32	TCTP_PLAYBACK_STREAM_BUFFER					=			STFTP_ABOVE_NORMAL;
const uint32	TCSS_PLAYBACK_STREAM_BUFFER					=			OSAL_MIN_STACK_SIZE;
const char		TCTN_PLAYBACK_STREAM_BUFFER[]				=			"PlaybackStreamBufferThread";

const uint32	TCTP_ROOT_FILESYSTEM						=			STFTP_ABOVE_NORMAL;
const uint32	TCSS_ROOT_FILESYSTEM						=			OSAL_MIN_STACK_SIZE;
const char		TCTN_ROOT_FILESYSTEM[]						=			"RootFileSystemProcessor";

const uint32	TCTP_SERIAL_MENU							=			STFTP_LOWER;
const uint32	TCSS_SERIAL_MENU							=			OSAL_MIN_STACK_SIZE;
const char		TCTN_SERIAL_MENU[]							=			"SerialMenu";

const uint32	TCTP_VFI_SCHEDULER							=			STFTP_NORMAL;
const uint32	TCSS_VFI_SCHEDULER							=			OSAL_MIN_STACK_SIZE;
const char		TCTN_VFI_SCHEDULER[]						=			"VFI Scheduler";

const uint32	TCTP_VOLUME_CACHE							=			STFTP_ABOVE_NORMAL;
const uint32	TCSS_VOLUME_CACHE							=			OSAL_MIN_STACK_SIZE;
const char		TCTN_VOLUME_CACHE[]							=			"VolumeCacheAsyncCachedRequestProcessor";

const uint32	TCTP_SCREEN_SAVER							=			STFTP_BELOW_NORMAL;
const uint32	TCSS_SCREEN_SAVER							=			OSAL_MIN_STACK_SIZE;
const char		TCTN_SCREEN_SAVER[]							=			"ScreenSaverDrawThread";

const uint32	TCTP_DVMIDLAYER_DISPATCHER					=			STFTP_NORMAL;
const uint32	TCSS_DVMIDLAYER_DISPATCHER					=			OSAL_MIN_STACK_SIZE;
const char		TCTN_DVMIDLAYER_DISPATCHER[]				=			"DVMidLayerDispatcherThread";

const uint32	TCTP_DDP_AV_DATA_PROVIDER					=			STFTP_HIGHEST;
const uint32	TCSS_DDP_AV_DATA_PROVIDER					=			10000;
const char		TCTN_DDP_AV_DATA_PROVIDER[]					=			"DDPAVDataProviderRoutine";

const uint32	TCTP_SERIAL_PORT_ADAPTER					=			STFTP_NORMAL;
const uint32	TCSS_SERIAL_PORT_ADAPTER					=			20000;
const char		TCTN_SERIAL_PORT_ADAPTER[]					=			"SerialPortAdapter";

const uint32	TCTP_STREAM_DUMP_UNIT						=			STFTP_NORMAL;
const uint32	TCSS_STREAM_DUMP_UNIT						=			10000;
const char		TCTN_STREAM_DUMP_UNIT[]						=			"Stream dump unit";

const uint32	TCTP_COPY_MANAGER							=			LOW_PRIORITY;
const uint32	TCSS_COPY_MANAGER							=			OSAL_MIN_STACK_SIZE;
const char		TCTN_COPY_MANAGER[]							=			"Copy MGR Task";

const uint32	TCTP_TSK_IN_TRAY							=			STFTP_CRITICAL;
const uint32	TCSS_TSK_IN_TRAY							=			(6*1024);

const uint32	TCTP_HAL_INT_TSK							=			STFTP_HIGHEST;
const uint32	TCSS_HAL_INT_TSK							=			(8*1024);

const uint32	TCTP_ENUM_NODES								=			STFTP_ABOVE_NORMAL;
const uint32	TCSS_ENUM_NODES								=			(5*1024);

const uint32	TCTP_BM_CONTEND								=			150;
const uint32	TCSS_BM_CONTEND								=			(4*1024);

const uint32	TCTP_BUS_RESET								=			STFTP_9;
const uint32	TCSS_BUS_RESET								=			(5*1024);

const uint32	TCTP_VLX_TIMER								=			100;
const uint32	TCSS_VLX_TIMER								=			(20*1024);

const uint32	TCTP_VLTST									=			100;
const uint32	TCSS_VLTST									=			(20*1024);

const uint32	TCTP_LCD_TIMER								=			STFTP_BELOW_NORMAL;
const uint32	TCSS_LCD_TIMER								=			(6*1024);

const uint32	TCTP_HALBRG									=			40;
const uint32	TCSS_HALBRG									=			(5*1024);

const uint32	TCTP_LOG_SVR								=			35;
const uint32	TCSS_LOG_SVR								=			(7*1024);

const uint32	TCTP_BUS_RESET_STORM						=			40;
const uint32	TCSS_BUS_RESET_STORM						=			(7*1024);

const uint32	TCTP_VLNM_EVENT_HANDLER						=			11;
const uint32	TCSS_VLNM_EVENT_HANDLER						=			(11*1024);

const uint32	TCTP_CMM_LIGHT_HANDLER						=			STFTP_7;
const uint32	TCSS_CMM_LIGHT_HANDLER						=			(12*1024);

const uint32	TCTP_VL_CONN_MGR_LISTENER					=			STFTP_7;
const uint32	TCSS_VL_CONN_MGR_LISTENER					=			(4*1024);

