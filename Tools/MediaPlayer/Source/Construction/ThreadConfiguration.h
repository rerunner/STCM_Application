
#ifndef THREADCONFIGURATION_H
#define THREADCONFIGURATION_H

#include "STF/Interface/STFThread.h"

#ifndef MAX_USER_PRIORITY
#define MAX_USER_PRIORITY 255
#endif

#define HIGH_PRIORITY  MAX_USER_PRIORITY
#define LOW_PRIORITY   (MAX_USER_PRIORITY-1)

extern const uint32	TCTP_DV_AUDIO_DECODER;
extern const char		TCTN_DV_AUDIO_DECODER[];
extern const uint32	TCSS_DV_AUDIO_DECODER;

extern const uint32	TCTP_AC3_DECODER;
extern const uint32	TCSS_AC3_DECODER;
extern const char 		TCTN_AC3_DECODER[];

extern const uint32	TCTP_SDL2_VIDEO_RENDERER;
extern const uint32	TCSS_SDL2_VIDEO_RENDERER;
extern const char 		TCTN_SDL2_VIDEO_RENDERER[];

extern const uint32	TCTP_WIN32_DV_DECODER;
extern const char		TCTN_WIN32_DV_DECODER[];
extern const uint32	TCSS_WIN32_DV_DECODER;

extern const uint32	TCTP_ASV_VDR_INTERFACE;
extern const char		TCTN_ASV_VDR_INTERFACE[];
extern const uint32	TCSS_ASV_VDR_INTERFACE;

extern const uint32 TCTP_FRAME_REORDER;
extern const uint32 TCSS_FRAME_REORDER;

extern const uint32 TCTP_ENCODERWORKER_INPUTDATA;
extern const uint32 TCSS_ENCODERWORKER_INPUTDATA;

extern const uint32 TCTP_ENCODERWORKER_OUTPUTPACKET;
extern const uint32 TCSS_ENCODERWORKER_OUTPUTPACKET;

extern const uint32 TCTP_MMECLIENT;
extern const uint32 TCSS_MMECLIENT;

extern const uint32 TCTP_MMECLIENT_SENDBUFFERSQUEUE;
extern const uint32 TCSS_MMECLIENT_SENDBUFFERSQUEUE;

extern const uint32 TCTP_JPEG_FRAME_STREAM_DECODER;
extern const uint32 TCSS_JPEG_FRAME_STREAM_DECODER;
extern const char   TCTN_JPEG_FRAME_STREAM_DECODER[];

extern const uint32 TCTP_WIN32_APPLICATION_WINDOW;
extern const uint32 TCSS_WIN32_APPLICATION_WINDOW;

extern const uint32 TCTP_WIN32_GRAPHICAL_RUNTIME_CONFIGURATOR;
extern const uint32 TCSS_WIN32_GRAPHICAL_RUNTIME_CONFIGURATOR;

extern const uint32 TCTP_WIN32_COMM_PROXY;
extern const uint32 TCSS_WIN32_COMM_PROXY;
extern const char   TCTN_WIN32_COMM_PROXY[];

extern const uint32 TCTP_VIDEO_STREAMMIXER;
extern const uint32 TCSS_VIDEO_STREAMMIXER;
extern const char   TCTN_VIDEO_STREAMMIXER[];

extern const uint32 TCTP_VIDEO_STREAMMIXER_INPUT;
extern const uint32 TCSS_VIDEO_STREAMMIXER_INPUT;
extern const char   TCTN_VIDEO_STREAMMIXER_INPUT[];

extern const uint32 TCTP_AUDIO_STREAMMIXER;
extern const uint32 TCSS_AUDIO_STREAMMIXER;
extern const char   TCTN_AUDIO_STREAMMIXER[];

extern const uint32 TCTP_AUDIO_STREAMMIXER_INPUT;
extern const uint32 TCSS_AUDIO_STREAMMIXER_INPUT;																		   
extern const char   TCTN_AUDIO_STREAMMIXER_INPUT[];

extern const uint32 TCTP_SPDIF_STREAMMIXER;
extern const uint32 TCSS_SPDIF_STREAMMIXER;
extern const char   TCTN_SPDIF_STREAMMIXER[];

extern const uint32 TCTP_SPDIF_STREAMMIXER_INPUT;
extern const uint32 TCSS_SPDIF_STREAMMIXER_INPUT;
extern const char   TCTN_SPDIF_STREAMMIXER_INPUT[];

extern const uint32 TCTP_PCM_PLAYER;
extern const uint32 TCSS_PCM_PLAYER;
extern const char   TCTN_PCM_PLAYER[];

extern const uint32 TCTP_VIDEORENDERER;
extern const uint32 TCSS_VIDEORENDERER;
extern const char   TCTN_VIDEORENDERER[];

extern const uint32 TCTP_AUDIO_FRAME_STREAM_DECODER;
extern const uint32 TCSS_AUDIO_FRAME_STREAM_DECODER;
extern const char   TCTN_AUDIO_FRAME_STREAM_DECODER[];

extern const uint32 TCTP_DVP_INTERRUPT_SERVICE;
extern const uint32 TCSS_DVP_INTERRUPT_SERVICE;

extern const uint32 TCTP_WIN32_INTERRUPT_CONTROLLER;
extern const uint32 TCSS_WIN32_INTERRUPT_CONTROLLER;

extern const uint32 TCTP_IEEE_1394_BUS;
extern const uint32 TCSS_IEEE_1394_BUS;

extern const uint32 TCTP_CPU_VIDEO_FORMAT_CONVERTER;
extern const uint32 TCSS_CPU_VIDEO_FORMAT_CONVERTER;

extern const uint32 TCTP_MPEG_VIDEO_DATAHANDLER;
extern const uint32 TCSS_MPEG_VIDEO_DATAHANDLER;
extern const char   TCTN_MPEG_VIDEO_DATAHANDLER[];

extern const uint32 TCTP_MPEG_STRATEGIC_VIDEO_DECODER;
extern const uint32 TCSS_MPEG_STRATEGIC_VIDEO_DECODER;
extern const char   TCTN_MPEG_STRATEGIC_VIDEO_DECODER[];

extern const uint32 TCTP_MPEG_SUBPICTURE_DATAHANDLER;
extern const uint32 TCSS_MPEG_SUBPICTURE_DATAHANDLER;
extern const char   TCTN_MPEG_SUBPICTURE_DATAHANDLER[];

extern const uint32 TCTP_MPEG_STRATEGIC_SUBPICTURE_DECODER;
extern const uint32 TCSS_MPEG_STRATEGIC_SUBPICTURE_DECODER;
extern const char   TCTN_MPEG_STRATEGIC_SUBPICTURE_DECODER[];

extern const uint32 TCTP_DRIVE;
extern const uint32 TCSS_DRIVE;

extern const uint32 TCTP_MEMORY_MESSAGE_DISPATCHER;
extern const uint32 TCSS_MEMORY_MESSAGE_DISPATCHER;
extern const char   TCTN_MEMORY_MESSAGE_DISPATCHER[];

extern const uint32 TCTP_GENERIC_MESSAGE_DISPATCHER;
extern const uint32 TCSS_GENERIC_MESSAGE_DISPATCHER;
extern const char   TCTN_GENERIC_MESSAGE_DISPATCHER[];

extern const uint32 TCTP_VBI_LINEPARSER;
extern const uint32 TCSS_VBI_LINEPARSER;
extern const char   TCTN_VBI_LINEPARSER[];

extern const uint32 TCTP_VIDEO_BLITTER;
extern const uint32 TCSS_VIDEO_BLITTER;
extern const char   TCTN_VIDEO_BLITTER[];

// From Dvd_driver\Device\Source\Unit\Video\VBI\Application\CGMSApp.cpp:
extern const uint32 TCTP_CGMS;
extern const uint32 TCSS_CGMS;
extern const char   TCTN_CGMS[];

//From Dvd_driver\Device\Source\Unit\Video\VBI\Application\GemstarApp.cpp:
extern const uint32 TCTP_GEMSTAR;
extern const uint32 TCSS_GEMSTAR;
extern const char   TCTN_GEMSTAR[];

//From Dvd_app\Source\Recorder_App\Middleware\Source\Unit\Tuner\NICAM.cpp
extern const uint32 TCTP_NICAM;
extern const uint32 TCSS_NICAM;
extern const char	TCTN_NICAM[];

//From Dvd_app\Source\Recorder_App\Middleware\Source\Unit\Utility\HardwareDelayTaskLoop.cpp
extern const uint32 TCTP_DEFAULT_DELAY_LOOP;
extern const uint32 TCSS_DEFAULT_DELAY_LOOP;
extern const char	TCTN_DEFAULT_DELAY_LOOP[];

//From Dvd_driver\Device\Source\Unit\Video\VBI\Application\TeletextApp.cpp
extern const uint32 TCTP_TELETEXT;
extern const uint32 TCSS_TELETEXT;
extern const char   TCTN_TELETEXT[];

//From Dvd_app\Source\Recorder_App\Middleware\Source\Unit\Tuner\TChannel.cpp
extern const uint32 TCTP_CHANNEL;
extern const uint32 TCSS_CHANNEL;
extern const char	TCTN_CHANNEL[];

//From Dvd_app\Source\Recorder_App\Middleware\Source\Unit\Generic\Controller.cpp
extern const uint32	TCTP_CONTROLLER_DEFAULT;
extern const uint32	TCSS_CONTROLLER_DEFAULT;
extern const char	TCTN_CONTROLLER_DEFAULT[];

//From Dvd_driver\Device\Source\Unit\Video\VBI\Encoder\Generic\VbiGenerator.cpp
extern const uint32 TCTP_VBIGENERATOR;
extern const uint32 TCSS_VBIGENERATOR;
extern const char   TCTN_VBIGENERATOR[];

//From Dvd_driver\Device\Source\Unit\Video\VBI\Application\VPSApp.cpp
extern const uint32 TCTP_VPS; 
extern const uint32 TCSS_VPS;
extern const char   TCTN_VPS[];

//From Dvd_app\Source\Recorder_App\Middleware\Source\Unit\Tuner\AutoSearchTask.cpp
extern const uint32 TCTP_AUTOSEARCH;
extern const uint32 TCSS_AUTOSEARCH;
extern const char   TCTN_AUTOSEARCH[];

//These were originally located in Dvd_Navi/Navigation/Source/Common/NaviThreadConfig.h
extern const uint32 TCTP_AVF_PARSER;
extern const uint32 TCSS_AVF_PARSER;
extern const char   TCTN_AVF_PARSER[];

extern const uint32 TCTP_AVI_PARSER;
extern const uint32 TCSS_AVI_PARSER;
extern const char   TCTN_AVI_PARSER[];

extern const uint32 TCTP_GENERIC_VDR_INTERFACE;
extern const uint32 TCSS_GENERIC_VDR_INTERFACE;
extern const char   TCTN_GENERIC_VDR_INTERFACE[];

extern const uint32 TCTP_DDP_GLOBAL_SCHEDULER;
extern const uint32 TCSS_DDP_GLOBAL_SCHEDULER;
extern const char   TCTN_DDP_GLOBAL_SCHEDULER[];

extern const uint32 TCTP_DDP_PLAYER_SCHEDULER;
extern const uint32 TCSS_DDP_PLAYER_SCHEDULER;
extern const char   TCTN_DDP_PLAYER_SCHEDULER[];

extern const uint32 TCTP_AVF_STREAM_SERVER;
extern const uint32 TCSS_AVF_STREAM_SERVER;
extern const char   TCTN_AVF_STREAM_SERVER[];

extern const uint32 TCTP_AVF_DRIVE_BLOCK_POOL;
extern const uint32 TCSS_AVF_DRIVE_BLOCK_POOL;
extern const char   TCTN_AVF_DRIVE_BLOCK_POOL[];
//End of definitions from Dvd_Navi/Navigation/Source/Common/NaviThreadConfig.h

//These were originally located in Dvd_Navi/NavigationRecorder/Source/Common/NaviRecorder/ThreadConfig.h
extern const uint32 TCTP_BURNING_BOX;
extern const uint32 TCSS_BURNING_BOX;
extern const char   TCTN_BURNING_BOX[];

extern const uint32 TCTP_DDP_RECORDER_SCHEDULER;
extern const uint32 TCSS_DDP_RECORDER_SCHEDULER;
extern const char   TCTN_DDP_RECORDER_SCHEDULER[];
//End of definitions from Dvd_Navi/NavigationRecorder/Source/Common/NaviRecorder/ThreadConfig.h

//These were originally located in Dvd_app\Source\Common\AppThreadConfig.h
extern const uint32 TCTP_DSI_MANAGER;
extern const uint32 TCSS_DSI_MANAGER;
extern const char   TCTN_DSI_MANAGER[];

extern const uint32 TCTP_PLAYER_SYS_EVENT_HANDLER;
extern const uint32 TCSS_PLAYER_SYS_EVENT_HANDLER;
extern const char   TCTN_PLAYER_SYS_EVENT_HANDLER[];

extern const uint32 TCTP_TIMER_TICK;
extern const uint32 TCSS_TIMER_TICK;
extern const char   TCTN_TIMER_TICK[];
//End of definitions from Dvd_app\Source\Common\AppThreadConfig.h

// From Dvd_Navi\NavigationRecorder\Source\Common\DDPGlobalRecorderScheduler.h:
extern const uint32 TCTP_DDP_GLOBAL_RECORDER_SCHEDULER;
extern const uint32 TCSS_DDP_GLOBAL_RECORDER_SCHEDULER;
extern const char   TCTN_DDP_GLOBAL_RECORDER_SCHEDULER[];

// From Dvd_Navi\NavigationRecorder\Source\Common\DVDRecorder.cpp:
extern const uint32 TCTP_DVDRECORDER_THREAD;
extern const uint32 TCSS_DVDRECORDER_THREAD;
extern const char   TCTN_DVDRECORDER_THREAD[];

// From Dvd_driver\STF\Source\STFTimer.cpp:
extern const uint32	TCTP_EVENT_SCHEDULER;
extern const uint32	TCSS_EVENT_SCHEDULER;
extern const char	TCTN_EVENT_SCHEDULER[];

// From Dvd_driver\MMEplus\Source\EMBX\Host\HostTransformer.cpp:
extern const uint32	TCTP_HOST_RECEIVER;
extern const uint32	TCSS_HOST_RECEIVER;
extern const char	TCTN_HOST_RECEIVER[];

//From Dvd_Navi\NavigationRecorder\Source\Common\VDRAccess\DVDRecorderStreamingParser.cpp
extern const uint32	TCTP_PACKET_ARRIVAL;
extern const uint32	TCSS_PACKET_ARRIVAL;
extern const char	TCTN_PACKET_ARRIVAL[];

//From Dvd_Navi\Navigation\Source\Common\PlaybackStreamBuffer.cpp
extern const uint32	TCTP_PLAYBACK_STREAM_BUFFER;
extern const uint32	TCSS_PLAYBACK_STREAM_BUFFER;
extern const char	TCTN_PLAYBACK_STREAM_BUFFER[];

//From Dvd_Navi\FileSystem\Interface\RootFile.h
extern const uint32	TCTP_ROOT_FILESYSTEM;
extern const uint32	TCSS_ROOT_FILESYSTEM;
extern const char	TCTN_ROOT_FILESYSTEM[];

//From Dvd_driver\VDR\Support\InofficialCode\SerialMenu\Source\SerialMenu.cpp
extern const uint32	TCTP_SERIAL_MENU;
extern const uint32	TCSS_SERIAL_MENU;
extern const char	TCTN_SERIAL_MENU[];

//From Dvd_Navi\FileSystem\Source\VFIInterface.cpp
extern const uint32	TCTP_VFI_SCHEDULER;
extern const uint32	TCSS_VFI_SCHEDULER;
extern const char	TCTN_VFI_SCHEDULER[];

//From Dvd_Navi\FileSystem\Source\VolumeCache.h
extern const uint32	TCTP_VOLUME_CACHE;
extern const uint32	TCSS_VOLUME_CACHE;
extern const char	TCTN_VOLUME_CACHE[];

//From Dvd_app\Source\GUI\WindowMain\MW_ScreenSaver.cpp
extern const uint32	TCTP_SCREEN_SAVER;
extern const uint32	TCSS_SCREEN_SAVER;
extern const char	TCTN_SCREEN_SAVER[];

//From Dvd_app\Source\Recorder_App\Source\Library\DVExternalSource.cpp
extern const uint32	TCTP_DVMIDLAYER_DISPATCHER;
extern const uint32	TCSS_DVMIDLAYER_DISPATCHER;
extern const char	TCTN_DVMIDLAYER_DISPATCHER[];

//From Dvd_Navi\NavigationRecorder\Source\Simulation\Stubs\AVDataProvider.cpp
extern const uint32	TCTP_DDP_AV_DATA_PROVIDER;
extern const uint32	TCSS_DDP_AV_DATA_PROVIDER;
extern const char	TCTN_DDP_AV_DATA_PROVIDER[];

//From Dvd_driverExt\Gemstar\Source\Serial\SerialPortAdapter.cpp
extern const uint32	TCTP_SERIAL_PORT_ADAPTER;
extern const uint32	TCSS_SERIAL_PORT_ADAPTER;
extern const char	TCTN_SERIAL_PORT_ADAPTER[];

//From Dvd_driver\VDR\Source\Streaming\StreamingDebug.cpp
extern const uint32	TCTP_STREAM_DUMP_UNIT;
extern const uint32	TCSS_STREAM_DUMP_UNIT;
extern const char	TCTN_STREAM_DUMP_UNIT[];

//From Dvd_app\Source\Recorder_App\Middleware\Source\Unit\CopyUtil\CopyManager.cpp
extern const uint32	TCTP_COPY_MANAGER;
extern const uint32	TCSS_COPY_MANAGER;
extern const char	TCTN_COPY_MANAGER[];

//The following are used in Dvd_driver\Device\Source\Unit\ExternalDevice\Specific\IEEE1394MfrInterface.cpp
extern const uint32	TCTP_TSK_IN_TRAY;
extern const uint32	TCSS_TSK_IN_TRAY;

extern const uint32	TCTP_HAL_INT_TSK;
extern const uint32	TCSS_HAL_INT_TSK;

extern const uint32	TCTP_ENUM_NODES;
extern const uint32	TCSS_ENUM_NODES;

extern const uint32	TCTP_BM_CONTEND;
extern const uint32	TCSS_BM_CONTEND;

extern const uint32	TCTP_BUS_RESET;
extern const uint32	TCSS_BUS_RESET;

extern const uint32	TCTP_VLX_TIMER;
extern const uint32	TCSS_VLX_TIMER;

extern const uint32	TCTP_VLTST;
extern const uint32	TCSS_VLTST;

extern const uint32	TCTP_LCD_TIMER;
extern const uint32	TCSS_LCD_TIMER;

extern const uint32	TCTP_HALBRG;
extern const uint32	TCSS_HALBRG;

extern const uint32	TCTP_LOG_SVR;
extern const uint32	TCSS_LOG_SVR;

extern const uint32 TCTP_BUS_RESET_STORM;
extern const uint32	TCSS_BUS_RESET_STORM;

extern const uint32	TCTP_VLNM_EVENT_HANDLER;
extern const uint32	TCSS_VLNM_EVENT_HANDLER;

extern const uint32	TCTP_CMM_LIGHT_HANDLER;
extern const uint32	TCSS_CMM_LIGHT_HANDLER;

extern const uint32	TCTP_VL_CONN_MGR_LISTENER;
extern const uint32	TCSS_VL_CONN_MGR_LISTENER;

#endif // THREADCONFIGURATION_H



