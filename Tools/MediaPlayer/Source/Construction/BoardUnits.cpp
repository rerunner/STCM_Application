/// 
/// @brief Global Board Configuration Structure 
///
/// @par SCOPE:
/// Customer Implementation File
///

#include "MemoryMap.h"
#include "ThreadConfiguration.h"

//
// VDR includes
//

#include "VDR/Source/Construction/IUnitConstruction.h"
#include "VDR/Interface/Unit/Audio/IVDRAudioUnits.h"
#include "VDR/Interface/Unit/Video/IVDRVideoUnits.h"
#include "VDR/Interface/Unit/Datapath/VDRMixerInputTypes.h"
#include "VDR/Interface/Unit/Board/IVDRBoard.h"
#include "VDR/Interface/Unit/Memory/IVDRMemoryUnits.h"
#include "VDR/Interface/Unit/Datapath/IVDRDatapathUnits.h"

//
// application relative includes
//

// Include Custom Unit IDs (includes Common Custom Unit IDs, too)
#include "../../Interface/ICustomUnitIDs.h"

// From here we get the Unit Creation Functions declarations.
// This file will be automatically created in the future:
#include "UnitCreationFunctions.ucf"


// Define the video output format to be used
#define VIDEO_OUTPUT_FORMAT        VDR_ARGB8888

// Here we declare the "local" unit IDs. It must be made sure that
// these numbers are unique within this file! All these IDs must have bit 30 set to 1.
//
// We declare them here because  no application is supposed to access them.
// These numbers can be reassigned for each customized project.


/************ local or private IDs must not be registered *****************/

static const VDRUID VDRUID_MEMORYOVERLAPDETECTOR                         = 0x40001000;
static const VDRUID VDRUID_MEMORY_MESSAGE_DISPATCHER                     = 0x40001001;

// all playback memory partition & pools
static const VDRUID VDRUID_PLAYBACK_MEMORY_PARTITION                     = 0x40001010;
static const VDRUID VDRUID_PLAYBACK_LINEAR_MEMORY_POOL                   = 0x40001011;
static const VDRUID VDRUID_PLAYBACK_HEAP_MEMORY_POOL                     = 0x40001012;

// clut memory pool for video mixer
static const VDRUID VDRUID_MIXER_CLUT_LINEAR_MEMORY_POOL                 = 0x40001030;

// Drive stuff.
static const VDRUID VDRUID_DRIVE_1                                       = 0x40001100;
static const VDRUID VDRUID_DRIVE_2                                       = 0x40001101;

static const VDRUID VDRUID_TRACKBUFFER_DRIVE_1                           = 0x40001102;
static const VDRUID VDRUID_LINEARMEMPOOL_DRIVE_1                         = 0x40001103;
static const VDRUID VDRUID_MEMORYPARTITION_DRIVE_1                       = 0x40001104;
static const VDRUID VDRUID_ATA_HARDWARE_PROXY_DRIVE_1                    = 0x40001105;

static const VDRUID VDRUID_TRACKBUFFER_DRIVE_2                           = 0x40001106;
static const VDRUID VDRUID_LINEARMEMPOOL_DRIVE_2                         = 0x40001107;
static const VDRUID VDRUID_MEMORYPARTITION_DRIVE_2                       = 0x40001108;
static const VDRUID VDRUID_ATAPI_HARDWARE_PROXY_DRIVE_2                  = 0x40001109;


static const VDRUID VDRUID_MME_MANAGER                                   = 0x40006000;

static const VDRUID VDRUID_AUDIO_PLAYER                                  = 0x40003022;
static const VDRUID VDRUID_OCTOPUS_AUDIO_DECODER                         = 0x40003023;
static const VDRUID VDRUID_OCTOPUS_AUDIO_DECODE_RENDERER                 = 0x40003026;
static const VDRUID VDRUID_MAIN_MIXER_INPUT                              = 0x40003027;
static const VDRUID VDRUID_AUX_MIXER_INPUT                               = 0x40003028;
static const VDRUID VDRUID_WIN32_PCM_POST_PROCESSOR                      = 0x40003029;
static const VDRUID VDRUID_MAIN_PCM_RENDERER                             = 0x4000302b;
static const VDRUID VDRUID_AUX_PCM_RENDERER                              = 0x4000302c;
static const VDRUID VDRUID_MAIN_MIXER_OUTPUT                             = 0x4000302d;
static const VDRUID VDRUID_8K_MAIN_PCM_PLAYER                            = 0x4000302e;
static const VDRUID VDRUID_ALSA_MAIN_PCM_PLAYER                          = 0x4000302f;
static const VDRUID VDRUID_AUDIO_FRAME_MIXER                             = 0x40003030;
//static const VDRUID VDRUID_MME_AUDIO_FRAME_MIXER                         = 0x40003031;
static const VDRUID VDRUID_SPDIF_FRAME_MIXER                             = 0x40003032;
static const VDRUID VDRUID_MAIN_SPDIF_MIXER_INPUT                        = 0x40003033;
static const VDRUID VDRUID_AC3_FRAME_STREAM_REPLICATOR                   = 0x40003034;
static const VDRUID VDRUID_LPCM_FRAME_STREAM_REPLICATOR                  = 0x40003035;
static const VDRUID VDRUID_MPEG2AUDIO_FRAME_STREAM_REPLICATOR            = 0x40003036;
//static const VDRUID VDRUID_MME_MACRO_DECODER_PROCESSOR                   = 0x40003037;
//static const VDRUID VDRUID_MME_PCM_POST_PROCESSSOR                       = 0x40003038;
static const VDRUID VDRUID_DTS_FRAME_STREAM_REPLICATOR                   = 0x40003039;
static const VDRUID VDRUID_MLP_FRAME_STREAM_REPLICATOR                   = 0x4000303a;
static const VDRUID VDRUID_CDDA_FRAME_STREAM_REPLICATOR                  = 0x4000303b;
static const VDRUID VDRUID_WIN32_MAIN_SPDIF_PLAYER                       = 0x4000303c;
static const VDRUID VDRUID_MAIN_SPDIF_RENDERER                           = 0x40003080;
static const VDRUID VDRUID_STANDARD_SPDIF_PLAYER                         = 0x40003081;
static const VDRUID VDRUID_8K_SPDIF_DATA_FORMATTER                       = 0x40003082;
static const VDRUID VDRUID_SPDIF_MIXER_OUTPUT                            = 0x40003084;
static const VDRUID VDRUID_PCM_MIXER_SPDIF_PCM_OUTPUT                    = 0x40003085;
static const VDRUID VDRUID_STANDARD_SPDIF_PLAYBACK                       = 0x40003086;
static const VDRUID VDRUID_MESSAGE_DISPATCHER                            = 0x40002001;
static const VDRUID VDRUID_AC3_FRAME_ANALYZER                            = 0x40002002;
static const VDRUID VDRUID_AC3_FRAME_STREAM_DECODER                      = 0x40002003;
static const VDRUID VDRUID_AC3_STREAM_DECODER                            = 0x40002004;
static const VDRUID VDRUID_LPCM_FRAME_ANALYZER                           = 0x40002005;
static const VDRUID VDRUID_LPCM_STREAM_DECODER                           = 0x40002006;
static const VDRUID VDRUID_MPEG2AUDIO_FRAME_ANALYZER                     = 0x40002007;
static const VDRUID VDRUID_MPEG2AUDIO_STREAM_DECODER                     = 0x40002008;
static const VDRUID VDRUID_MPEG2AUDIO_FRAME_STREAM_DECODER               = 0x40002009;
static const VDRUID VDRUID_DTS_FRAME_ANALYZER                            = 0x40002010;
static const VDRUID VDRUID_DTS_STREAM_DECODER                            = 0x40002011;
static const VDRUID VDRUID_DTS_FRAME_STREAM_DECODER                      = 0x40002012;
static const VDRUID VDRUID_MLP_FRAME_ANALYZER                            = 0x40002013;
static const VDRUID VDRUID_MLP_STREAM_DECODER                            = 0x40002014;
static const VDRUID VDRUID_MLP_FRAME_STREAM_DECODER                      = 0x40002015;
static const VDRUID VDRUID_CDDA_FRAME_STREAM_DECODER                     = 0x40002016;
static const VDRUID VDRUID_CDDA_SUBCH_FRAME_SPLITTER                     = 0x40002017;
static const VDRUID VDRUID_CDDA_AUDIO_FRAME_SPLITTER                     = 0x40002018;
static const VDRUID VDRUID_CDDA_STREAM_DECODER                           = 0x40002019;
static const VDRUID VDRUID_AC3_FRAME_ANALYZER_PLAYER                     = 0x40002100;
static const VDRUID VDRUID_LPCM_FRAME_STREAM_DECODER                     = 0x40002103;

static const VDRUID VDRUID_AC3_DECODER						= 0x40003142;
static const VDRUID VDRUID_PULSEAUDIO_RENDERER				= 0x40003144;
static const VDRUID VDRUID_SDL2AUDIO_RENDERER				= 0x40003145;
static const VDRUID VDRUID_AC3_PLAYER						= 0x40003146;

//static const VDRUID VDRUID_MME_LPCM_FRAME_DECODER                        = 0x40002104;
//static const VDRUID VDRUID_MME_MPEG2AUDIO_FRAME_DECODER	                 = 0x40002105;
//static const VDRUID VDRUID_MME_DTS_FRAME_DECODER                         = 0x40002106;
//static const VDRUID VDRUID_MME_MLP_FRAME_DECODER                         = 0x40002107;
//static const VDRUID VDRUID_MME_CDDA_FRAME_DECODER                        = 0x40002108;
static const VDRUID VDRUID_GENERIC_AUDIO_SYNTH                           = 0x40002200;
static const VDRUID VDRUID_WAVE_GENERATOR                                = 0x40002201;
static const VDRUID VDRUID_MIXER_INPUT_CONTROL_AUX                       = 0x40002300;
static const VDRUID VDRUID_MAIN_AUDIO_RENDERER                           = 0x40003040;
static const VDRUID VDRUID_AUDIO_RENDERER_FRAME_STREAM_REPLICATOR        = 0x40003041;

//
// Primary Video Transducer
//
static const VDRUID VDRUID_PRIMARY_VIDEO_TRANSDUCER                      = 0x40003100;
static const VDRUID VDRUID_MPEG_VIDEO_STREAM_DECODER                     = 0x40003110;
static const VDRUID VDRUID_MPEG_VIDEO_PLAYER	            					= 0x40003111;
//static const VDRUID VDRUID_MPEG_VIDEO_DATA_HANDLER                      = 0x40003111;
//static const VDRUID VDRUID_STRATEGIC_MPEG_VIDEO_DECODER                 = 0x40003112;

//static const VDRUID VDRUID_DMA_AND_SCD_ENGINE                            = 0x40003120;
//static const VDRUID VDRUID_MPEG_VIDEO_HEADER_PARSER                      = 0x40003130;
//static const VDRUID VDRUID_DVD_VIDEO_FRAME_EXTRACTOR                     = 0x40003150;
//static const VDRUID VDRUID_JPEG_FRAME_EXTRACTOR                          = 0x40003151;

//
// Secondary Video Transducer
//
static const VDRUID VDRUID_SECONDARY_VIDEO_TRANSDUCER                    = 0x40007100;
static const VDRUID VDRUID_SUBPICTURE_DECODER                            = 0x40007101;
static const VDRUID VDRUID_SUBPICTURE_DATA_HANDLER                       = 0x40007102;
static const VDRUID VDRUID_STRATEGIC_SUBPICTURE_DECODER                  = 0x40007103;
static const VDRUID VDRUID_SOFTWARE_DMA_ENGINE                           = 0x40007104;

//
// Video frame mixer
//
static const VDRUID VDRUID_VIDEO_FRAME_MIXER                             = 0x40003000;
static const VDRUID VDRUID_BUTTON_HIGHLIGHT_PROCESSOR                    = 0x40003001;
//
// Video Frame Mixer input IDs
//
static const VDRUID VDRUID_VIDEO_FRAME_MIXER_INPUT                       = 0x40003140; // main video
static const VDRUID VDRUID_VIDEO_FRAME_MIXER_INPUT_1                     = 0x40003141; // subpicture
static const VDRUID VDRUID_VIDEO_FRAME_MIXER_INPUT_2                     = 0x40003142; // on screen display (OSD)
static const VDRUID VDRUID_VIDEO_FRAME_MIXER_INPUT_3                     = 0x40003143; // additional OSD for test player
static const VDRUID VDRUID_VIDEO_FRAME_MIXER_INPUT_5                     = 0x40003145; // JPEG decoder's mixer input

//
// Input controls for video mixer inputs
//
static const VDRUID VDRUID_VIDEO_MIXER_INPUT_CONTROL_MAIN_INTERNAL       = 0x40003160;
static const VDRUID VDRUID_VIDEO_MIXER_INPUT_CONTROL_SUBPICTURE_INTERNAL = 0x40003161;
static const VDRUID VDRUID_VIDEO_MIXER_INPUT_CONTROL_OSD_INTERNAL        = 0x40003162;

//
// VBI IDs
//
static const VDRUID VDRUID_VBI_DECODER                                   = 0x40003200;
static const VDRUID VDRUID_VBI_LINE_PARSER                               = 0x40003205;
static const VDRUID VDRUID_VBI_REPLICATOR                                = 0x40003210;
static const VDRUID VDRUID_GEMSTAR_DECODER                               = 0x40003220;
static const VDRUID VDRUID_CGMS_DECODER                                  = 0x40003230;
static const VDRUID VDRUID_CGMS_REPLICATOR                               = 0x40003240;
static const VDRUID VDRUID_TELETEXT_DECODER                              = 0x40003250;
static const VDRUID VDRUID_VPS_DECODER                                   = 0x40003260;



//
// Program Stream Transducer
//
static const VDRUID VDRUID_PROGRAM_STREAM_TRANSDUCER                     = 0x40004000;
static const VDRUID VDRUID_MPEG_DEMULTIPLEXER                            = 0x40004001;

//
// Alternate DVD Demux
//
static const VDRUID VDRUID_DVD_STREAM_TRANSDUCER                         = 0x40004031;
static const VDRUID VDRUID_DVD_DEMULTIPLEXER                             = 0x40004020;
static const VDRUID VDRUID_DVD_DEMUX_REPLICATOR                          = 0x40004021;
static const VDRUID VDRUID_DVD_DEMUX_VIDEO_SPLITTER                      = 0x40004022;
static const VDRUID VDRUID_DVD_DEMUX_AUDIO_SPLITTER                      = 0x40004023;
static const VDRUID VDRUID_DVD_DEMUX_SUBPICTURE_SPLITTER                 = 0x40004024;
static const VDRUID VDRUID_DVD_DEMUX_VIDEO_UNPACKER                      = 0x40004025;
static const VDRUID VDRUID_DVD_DEMUX_AUDIO_UNPACKER                      = 0x40004026;
static const VDRUID VDRUID_DVD_DEMUX_SUBPICTURE_UNPACKER                 = 0x40004027;

static const VDRUID VDRUID_MPEGPROGRAM_STREAM_TRANSDUCER                 = 0x40004231;
static const VDRUID VDRUID_MPEGPROGRAM_DEMULTIPLEXER                     = 0x40004220;
static const VDRUID VDRUID_MPEGPROGRAM_DEMUX_REPLICATOR                  = 0x40004221;
static const VDRUID VDRUID_MPEGPROGRAM_DEMUX_VIDEO_SPLITTER              = 0x40004222;
static const VDRUID VDRUID_MPEGPROGRAM_DEMUX_AUDIO_SPLITTER              = 0x40004223;
static const VDRUID VDRUID_MPEGPROGRAM_DEMUX_SUBPICTURE_SPLITTER         = 0x40004224;
static const VDRUID VDRUID_MPEGPROGRAM_DEMUX_VIDEO_UNPACKER              = 0x40004225;
static const VDRUID VDRUID_MPEGPROGRAM_DEMUX_AUDIO_UNPACKER              = 0x40004226;
static const VDRUID VDRUID_MPEGPROGRAM_DEMUX_SUBPICTURE_UNPACKER         = 0x40004227;

//
// Demultiplexed Stream Transducer
//
static const VDRUID VDRUID_DEMULTIPLEXED_STREAM_TRANSDUCER               = 0x40004040;
static const VDRUID VDRUID_DEMULTIPLEXED_STREAM_DEMULTIPLEXER            = 0x40004041;

//
//DVD Audio related units
//
//DVDAudio Transducer Proxy - Demux with Audio and RTI(in future) chain
static const VDRUID VDRUID_DVDAUDIO_DEMULTIPLEXER                        = 0x40004228;
static const VDRUID VDRUID_DVDAUDIO_STREAM_TRANSDUCER                    = 0x40004229;

//ASV Transducer Proxy - Demux with Video and SubPic chain
static const VDRUID VDRUID_ASV_DEMUX_REPLICATOR                          = 0x4000422a;
static const VDRUID VDRUID_ASV_DEMULTIPLEXER                             = 0x4000422b;
static const VDRUID VDRUID_ASV_TRANSDUCER                                = 0x4000422c;

//
// Video display stuff
//
static const VDRUID VDRUID_VIDEO_OUT                                     = 0x40000006;
static const VDRUID VDRUID_VIDEO_PLAYER                                  = 0x40000007;
static const VDRUID VDRUID_VIDEO_MIXER_OUTPUT                            = 0x4000000a;

static const VDRUID VDRUID_VIDEO_BLITTER                                 = 0x4000000f;
static const VDRUID VDRUID_VIDEO_RENDERER                                = 0x40000010;
static const VDRUID VDRUID_STM8000_VIDEO_MIXER                           = 0x40000011;
static const VDRUID VDRUID_GRAPHICS_2D                                   = 0x40000012;
static const VDRUID VDRUID_DEFERRED_VIDEO_BLITTER                        = 0x40000013;
static const VDRUID VDRUID_VIDEO_OUTPUT                                  = 0x40009020;


//
// DV Decoder 
//
static const VDRUID VDRUID_DV_FRAME_DECODER                              = 0x40007000;
static const VDRUID VDRUID_DV_DATA_HANDLER                               = 0x40007001;
static const VDRUID VDRUID_WIN32_DV_DECODER                              = 0x40007002; 
static const VDRUID VDRUID_DV_AUDIO_DECODER                              = 0x40007003; 
static const VDRUID VDRUID_WIN32_DV_AUDIO_DECODER                        = 0x40007004; 
static const VDRUID VDRUID_DV_CAPTURE_VIDEO_LINK_INPUT                   = 0x40007005; 
static const VDRUID VDRUID_STM_8000_DV_CAPTURE                           = 0x40007006;
static const VDRUID VDRUID_DV_VIDEO_PREPROCESSOR_LINK_OUTPUT             = 0x40007007; 
static const VDRUID VDRUID_FORMAT_CONVERTER                              = 0x40007008; 


// 
// IEEE 1394
//
static const VDRUID VDRUID_IEEE_1394_BUS                                 = 0x40007010; 


// interrupt levels
static const VDRUID VDRUID_INTERRUPT_LEVEL_1                             = 0x40004102;
static const VDRUID VDRUID_INTERRUPT_LEVEL_2                             = 0x40004103;
static const VDRUID VDRUID_INTERRUPT_LEVEL_3                             = 0x40004104;
static const VDRUID VDRUID_INTERRUPT_LEVEL_4                             = 0x40004105;
static const VDRUID VDRUID_INTERRUPT_LEVEL_5                             = 0x40004106;
static const VDRUID VDRUID_INTERRUPT_LEVEL_6                             = 0x40004107;
static const VDRUID VDRUID_INTERRUPT_LEVEL_7                             = 0x40004108;
static const VDRUID VDRUID_INTERRUPT_LEVEL_8                             = 0x40004109;
static const VDRUID VDRUID_INTERRUPT_LEVEL_9                             = 0x4000410a;
static const VDRUID VDRUID_INTERRUPT_LEVEL_10                            = 0x4000410b;
static const VDRUID VDRUID_INTERRUPT_LEVEL_11                            = 0x4000410c;
static const VDRUID VDRUID_INTERRUPT_LEVEL_12                            = 0x4000410d;
static const VDRUID VDRUID_INTERRUPT_LEVEL_13                            = 0x4000410e;
static const VDRUID VDRUID_INTERRUPT_LEVEL_14                            = 0x4000410f;
static const VDRUID VDRUID_INTERRUPT_LEVEL_15                            = 0x40004110;
static const VDRUID VDRUID_INTERRUPT_LEVEL_0                             = 0x40004112;


// Win32 interrupt stuff
static const VDRUID VDRUID_INTERRUPT_CONTROLLER                          = 0x40005100;
static const VDRUID VDRUID_VSYNC_INTERRUPT                               = 0x40005101;

// Win32 support stuff
static const VDRUID VDRUID_WIN32_APPLICATIONWINDOW                       = 0x40005000;
static const VDRUID VDRUID_WIN32_WINDOWCONTROL                           = 0x40005001;
static const VDRUID VDRUID_WIN32_EVENTPROVIDER                           = 0x40005003;
static const VDRUID VDRUID_WIN32_RUNTIMECONFIGURATOR                     = 0x40005004;
static const VDRUID VDRUID_WIN32_FRONTPANEL                              = 0x40005006;
static const VDRUID VDRUID_FRONT_PANEL_STRING_OPERATIONS                 = 0x40005007;
static const VDRUID VDRUID_FRONT_PANEL_PIE_OPERATIONS                    = 0x40005008;
static const VDRUID VDRUID_FRONT_PANEL_ICONCONTROL                       = 0x40005009;
static const VDRUID VDRUID_WIN32REMOTE                                   = 0x4000500a;
static const VDRUID VDRUID_DEBUG_MENU_COMM_PROXY                         = 0x4000500b;


// JPEG
static const VDRUID VDRUID_STILL_FRAME_SPECIALFX_UNIT                    = 0x40009000;
static const VDRUID VDRUID_JPEG_FRAME_STREAM_DECODER                     = 0x40009001;
//static const VDRUID VDRUID_MME_JPEG_FRAME_DECODER                        = 0x40009002;
static const VDRUID VDRUID_JPEG_TEST_CHAIN                               = 0x40009003;
static const VDRUID VDRUID_JPEG_OUTPUT_TERMINATOR                        = 0x40009004;
static const VDRUID VDRUID_JPEG_STREAMING_CHAIN                          = 0x40009005;


static const VDRUID VDRUID_STREAMING_DEBUG_1                             = 0x4000a001;
static const VDRUID VDRUID_STREAMING_DEBUG_2                             = 0x4000a002;
static const VDRUID VDRUID_STREAMING_DEBUG_3                             = 0x4000a003;
static const VDRUID VDRUID_STREAMING_DEBUG_4                             = 0x4000a004;
static const VDRUID VDRUID_STREAMING_DEBUG_5                             = 0x4000a005;
static const VDRUID VDRUID_STREAMING_DEBUG_6                             = 0x4000a006;
static const VDRUID VDRUID_STREAMING_DEBUG_7                             = 0x4000a007;
static const VDRUID VDRUID_STREAMING_DEBUG_CDDA_1                        = 0x4000a008;
static const VDRUID VDRUID_STREAMING_DEBUG_CDDA_2                        = 0x4000a009;

static const VDRUID VDRUID_STREAMING_DEBUG_AUDIO_1                       = 0x4000c010;
static const VDRUID VDRUID_STREAMING_DEBUG_AUDIO_2                       = 0x4000c011;
static const VDRUID VDRUID_STREAMING_DEBUG_AUDIO_3                       = 0x4000c012;
static const VDRUID VDRUID_STREAMING_DEBUG_AC3_1                         = 0x4000c020;
static const VDRUID VDRUID_STREAMING_DEBUG_AC3_2                         = 0x4000c021;
static const VDRUID VDRUID_STREAMING_DEBUG_AC3_3                         = 0x4000c022;
static const VDRUID VDRUID_STREAMING_DEBUG_AC3_4                         = 0x4000c023;
static const VDRUID VDRUID_STREAMING_DEBUG_AC3_5                         = 0x4000c024;
static const VDRUID VVDRUID_STREAMING_DEBUG_AUDIO_RENDERER_1             = 0x4000c025;
static const VDRUID VVDRUID_STREAMING_DEBUG_AUDIO_RENDERER_2             = 0x4000c026;
static const VDRUID VVDRUID_STREAMING_DEBUG_AUDIO_RENDERER_3             = 0x4000c027;

static const VDRUID VDRUID_STREAMING_DEBUG_MP2a_1                        = 0x4000c120;




uint64 GlobalBoardConfig[] =
   {
   CREATE_UNIT(VDRUID_VDR_BOARD, CreateStandardBoard),
               //??? The following creation parameters should be automatically retrieved from somewhere...
               DWORD_PARAM(1),       // boardVersion
               DWORD_PARAM(0),       // boardRevision
               DWORD_PARAM(0),       // driverVersion
               DWORD_PARAM(1),       // driverRevision
               DWORD_PARAM(24032009),// driverBuild 
               PARAMS_DONE,
      // The dependency list of the board determines the units an application can
      // request to be part of a Unit Set. So here we specify the units accessible
      // by applications.
		
      // The unit IDs of the following units are public, and thus defined in header files
      // located somewhere in VDR/Interface:
      VDRUID_GENERIC_PLAYBACK_POOL_ALLOCATOR,   PARAMS_DONE,		
      VDRUID_DVD_STREAM_TRANSDUCER_PROXY,       PARAMS_DONE, // DVD Program Stream Streaming Chain
   MAPPING_DONE,

   ////////////////////////////////////////////////////////////////////////////
   // MemoryPoolAllocator message dispatcher
   ////////////////////////////////////////////////////////////////////////////

   CREATE_UNIT (VDRUID_MEMORY_MESSAGE_DISPATCHER, CreateMessageDispatcher),
                DWORD_PARAM(TCTP_MEMORY_MESSAGE_DISPATCHER), // Thread priority
                DWORD_PARAM(TCSS_MEMORY_MESSAGE_DISPATCHER), // Stack size
                STRING_PARAM(TCTN_MEMORY_MESSAGE_DISPATCHER),
         PARAMS_DONE,
   MAPPING_DONE,

   ////////////////////////////////////////////////////////////////////////////
   // Memory Pool and Partition Units
   ////////////////////////////////////////////////////////////////////////////

   // The memory overlap detector detects any overlapping of memory partitions or other objects
   // at construction time.
   CREATE_UNIT (VDRUID_MEMORYOVERLAPDETECTOR, CreateMemoryOverlapDetector),
                PARAMS_DONE,
   MAPPING_DONE,

   // The memory partition for all playback devices.
   CREATE_UNIT (VDRUID_PLAYBACK_MEMORY_PARTITION, CreateMemoryPartition),
                DWORD_PARAM(PLAYBACK_MEMORY_PARTITION_BASE),
                DWORD_PARAM(PLAYBACK_MEMORY_PARTITION_SIZE), 
                PARAMS_DONE, // LMI memory!
      VDRUID_MEMORYOVERLAPDETECTOR, PARAMS_DONE,
   MAPPING_DONE,

   // The linear memory pool for the playback memory.
   CREATE_UNIT (VDRUID_PLAYBACK_LINEAR_MEMORY_POOL, CreateLinearMemoryPool),
                PARAMS_DONE,
      VDRUID_PLAYBACK_MEMORY_PARTITION, PARAMS_DONE,
      VDRUID_MEMORY_MESSAGE_DISPATCHER, PARAMS_DONE,
   MAPPING_DONE,

   // The heap memory pool for the playback memory.
   CREATE_UNIT (VDRUID_PLAYBACK_HEAP_MEMORY_POOL, CreateHeapMemoryPool),
                PARAMS_DONE,
      VDRUID_PLAYBACK_MEMORY_PARTITION, PARAMS_DONE,
      VDRUID_MEMORY_MESSAGE_DISPATCHER, PARAMS_DONE,
   MAPPING_DONE,
	
   // The linear memory pool for playback applications.
   CREATE_UNIT (VDRUID_GENERIC_PLAYBACK_POOL_ALLOCATOR, CreateLinearMemoryPool),
                PARAMS_DONE,
      VDRUID_PLAYBACK_MEMORY_PARTITION, PARAMS_DONE,
      VDRUID_MEMORY_MESSAGE_DISPATCHER, PARAMS_DONE,
   MAPPING_DONE,


   ////////////////////////////////////////////////////////////////////////////
   // Debug Termination units.
   ////////////////////////////////////////////////////////////////////////////
   // Three debug units used as terminators
   CREATE_UNIT (VDRUID_STREAMING_DEBUG_1, CreateStreamingTerminator),
                PARAMS_DONE,
   MAPPING_DONE,
   
   CREATE_UNIT (VDRUID_STREAMING_DEBUG_2, CreateStreamingTerminator),
                PARAMS_DONE,
   MAPPING_DONE,
   
   CREATE_UNIT (VDRUID_STREAMING_DEBUG_3, CreateStreamingTerminator),
                PARAMS_DONE,
   MAPPING_DONE,
   
   ////////////////////////////////////////////////////////////////////////////
   // Support Units
   ////////////////////////////////////////////////////////////////////////////

   // The generic message dispatcher unit
   CREATE_UNIT (VDRUID_MESSAGE_DISPATCHER, CreateMessageDispatcher),
                DWORD_PARAM(TCTP_GENERIC_MESSAGE_DISPATCHER),  // Thread priority
                DWORD_PARAM(TCSS_GENERIC_MESSAGE_DISPATCHER),  // Stack size
                STRING_PARAM(TCTN_GENERIC_MESSAGE_DISPATCHER), // Thread name
                PARAMS_DONE,
   MAPPING_DONE,

	
   ////////////////////////////////////////////////////////////////////////////
   // Audio Units
   ////////////////////////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////////////////////////////
   // Decoders for the various audio types
   ////////////////////////////////////////////////////////////////////////////
   //
   // AC3
   // 
   CREATE_UNIT (VDRUID_AC3_DECODER, CreatePhysicalAC3Decoder),
		DWORD_PARAM(TCTP_AC3_DECODER),	// Thread priority
		DWORD_PARAM(TCSS_AC3_DECODER),	// Thread stack size
		STRING_PARAM(TCTN_AC3_DECODER),	// Thread Name
		DWORD_PARAM(60),			// Data Buffer Count
		DWORD_PARAM(6144),	// Data Buffer Size, 6 blocks of size 6*256 equals 1 frame in floats. 1 float = 4 Bytes
		DWORD_PARAM(4),			// Memory Alignment Factor In Bytes
		DWORD_PARAM(6144),	// Data Buffer Block Size
	PARAMS_DONE,
		VDRUID_PLAYBACK_LINEAR_MEMORY_POOL, PARAMS_DONE,
		VDRUID_MESSAGE_DISPATCHER, PARAMS_DONE,
	MAPPING_DONE,

   ////////////////////////////////////////////////////////////////////////
   // Audio Renderer Units
   ////////////////////////////////////////////////////////////////////////
   
   CREATE_UNIT (VDRUID_SDL2AUDIO_RENDERER, CreateSDL2AudioRenderer),
	PARAMS_DONE,
		VDRUID_MESSAGE_DISPATCHER, PARAMS_DONE,
	MAPPING_DONE,

	CREATE_UNIT (VDRUID_AC3_PLAYER, CreateGenericStreamingChainUnit),
		DWORD_PARAM(1),	// num inputs
		DWORD_PARAM(0),	// num outputs
		DWORD_PARAM(0xff000000), // Connect Chain, Out(CID0) -> Unit0, In(CID0) ChainIn -> Decoder
		DWORD_PARAM(0x00010100), // Connect Unit0, Out(CID1) -> Unit1, In(CID0) Decoder -> Renderer
	PARAMS_DONE,
		VDRUID_AC3_DECODER, PARAMS_DONE, //Unit 0
		VDRUID_SDL2AUDIO_RENDERER, PARAMS_DONE, //Unit 1
	MAPPING_DONE,


   ////////////////////////////////////////////////////////////////////////////
   // Video Decode Units
   ////////////////////////////////////////////////////////////////////////////

   CREATE_UNIT (VDRUID_MPEG_VIDEO_STREAM_DECODER, CreateMPEGVideoDecoder),
               DWORD_PARAM(TCTP_WIN32_DV_DECODER),  // Thread priority
               DWORD_PARAM(TCSS_WIN32_DV_DECODER),  // Stack size
               STRING_PARAM(TCTN_WIN32_DV_DECODER), // Thread name
               DWORD_PARAM(4),     // Data Buffer Count
               DWORD_PARAM(2048),   // Data Buffer Size, 6 blocks of size 6*256 equals 1 frame in floats. 1 float = 4 Bytes
               DWORD_PARAM(4),      // Memory Alignment Factor In Bytes
               DWORD_PARAM(2048),   // Data Buffer Block Size
   PARAMS_DONE,
      VDRUID_PLAYBACK_LINEAR_MEMORY_POOL, PARAMS_DONE,
		VDRUID_MESSAGE_DISPATCHER, PARAMS_DONE,
   MAPPING_DONE,

   ////////////////////////////////////////////////////////////////////////
   // Video Display Units
   ////////////////////////////////////////////////////////////////////////
 
   CREATE_UNIT (VDRUID_MPEG_VIDEO_PLAYER, CreateGenericStreamingChainUnit),
		DWORD_PARAM(1),	// num inputs
		DWORD_PARAM(0),	// num outputs
		DWORD_PARAM(0xff000000), // Connect Chain, Out(CID0) -> Unit0, In(CID0) ChainIn -> Decoder
		DWORD_PARAM(0x00010100), // Connect Unit0, Out(CID1) -> Unit1, In(CID0) Decoder -> Renderer
	PARAMS_DONE,
		VDRUID_MPEG_VIDEO_STREAM_DECODER, PARAMS_DONE, //Unit 0
		//VDRUID_SDL2VIDEO_RENDERER, PARAMS_DONE, //Unit 1
      VDRUID_STREAMING_DEBUG_2,         PARAMS_DONE, // debug terminator 2
	MAPPING_DONE,

   ////////////////////////////////////////////////////////////////////////////
   // Stream Units
   ////////////////////////////////////////////////////////////////////////////

   CREATE_UNIT (VDRUID_DVD_STREAM_TRANSDUCER, CreateGenericStreamingChainUnit),
                DWORD_PARAM(1),	// num inputs
                DWORD_PARAM(0),	// num outputs
                // chain connection
                DWORD_PARAM(0xff000000),// Connect Chain, Out(CID0) -> Unit0, In(CID0) com. data -> Demultiplexer
                // Demultiplexer -> Transducers
                DWORD_PARAM(0x00010100),// Connect Unit0, Out(CID1) -> Unit1, In(CID0) Demux -> mpeg video decoder
                DWORD_PARAM(0x00020200),// Connect Unit0, Out(CID2) -> Unit2, In(CID0) Demux -> Audio Player
                DWORD_PARAM(0x00030300),// Connect Unit0, Out(CID3) -> Unit3, In(CID0) Demux -> debug terminator 3
                PARAMS_DONE,
      VDRUID_DVD_DEMULTIPLEXER, PARAMS_DONE,
      VDRUID_MPEG_VIDEO_PLAYER, PARAMS_DONE,
      //VDRUID_STREAMING_DEBUG_2,         PARAMS_DONE, // debug terminator 2
      VDRUID_AC3_PLAYER, PARAMS_DONE,
      VDRUID_STREAMING_DEBUG_3, PARAMS_DONE, // debug terminator 3
   MAPPING_DONE,

   CREATE_UNIT (VDRUID_DVD_STREAM_TRANSDUCER_PROXY, CreateSingleStreamingProxyUnit),
                PARAMS_DONE,
      VDRUID_MESSAGE_DISPATCHER,    PARAMS_DONE,
      VDRUID_DVD_STREAM_TRANSDUCER, PARAMS_DONE,
   MAPPING_DONE,

   CREATE_UNIT (VDRUID_DVD_DEMUX_REPLICATOR, CreateStreamReplicatorStreamingUnit),
                DWORD_PARAM(3),
                PARAMS_DONE,
   MAPPING_DONE,

   CREATE_UNIT (VDRUID_DVD_DEMUX_VIDEO_SPLITTER, CreateDVDPESVideoSplitterUnit),
                PARAMS_DONE,
   MAPPING_DONE,

   CREATE_UNIT (VDRUID_DVD_DEMUX_AUDIO_SPLITTER, CreateDVDPESAudioSplitterUnit),
                PARAMS_DONE,
   MAPPING_DONE,

   CREATE_UNIT (VDRUID_DVD_DEMUX_SUBPICTURE_SPLITTER, CreateDVDPESSubpictureSplitterUnit),
                PARAMS_DONE,
   MAPPING_DONE,

   CREATE_UNIT (VDRUID_STREAMING_DEBUG_6, CreateLoggingStreamingUnit),
                STRING_PARAM("STUT"),
                PARAMS_DONE,
   MAPPING_DONE,

   CREATE_UNIT (VDRUID_DVD_DEMULTIPLEXER, CreateGenericStreamingChainUnit),
                DWORD_PARAM(1), // num inputs
                DWORD_PARAM(3), // num outputs
                // REPLICATOR
                DWORD_PARAM(0xff000000), // Connect Unit7, Out1 -> Unit0, In0					
                DWORD_PARAM(0x00010100), // Connect Unit0, Out1 -> Unit1, In0
                DWORD_PARAM(0x00020200), // Connect Unit0, Out2 -> Unit2, In0
                DWORD_PARAM(0x00030300), // Connect Unit0, Out3 -> Unit3, In0
                // SPLITTER to UNPACKER		
                DWORD_PARAM(0x01010400),// Connect Unit1, Out0 -> Unit4, In0
                DWORD_PARAM(0x02010500),// Connect Unit2, Out0 -> Unit5, In0
                DWORD_PARAM(0x03010600),// Connect Unit3, Out0 -> Unit6, In0
                // UNPACKER
                DWORD_PARAM(0x0401ff01),// Connect Unit4, Out0 -> Chain, In0
                DWORD_PARAM(0x0501ff02),// Connect Unit5, Out0 -> Chain, In1
                DWORD_PARAM(0x0601ff03),// Connect Unit6, Out0 -> Chain, In2
                PARAMS_DONE,
      VDRUID_DVD_DEMUX_REPLICATOR,          PARAMS_DONE,
      VDRUID_DVD_DEMUX_VIDEO_SPLITTER,      PARAMS_DONE,
      VDRUID_DVD_DEMUX_AUDIO_SPLITTER,      PARAMS_DONE,
      VDRUID_DVD_DEMUX_SUBPICTURE_SPLITTER, PARAMS_DONE,
      VDRUID_DVD_DEMUX_VIDEO_UNPACKER,      PARAMS_DONE,
      VDRUID_DVD_DEMUX_AUDIO_UNPACKER,      PARAMS_DONE,
      VDRUID_DVD_DEMUX_SUBPICTURE_UNPACKER, PARAMS_DONE,
   MAPPING_DONE,

   CREATE_UNIT (VDRUID_DVD_DEMUX_VIDEO_UNPACKER, CreateDVDPESStreamUnpackerUnit),
                DWORD_PARAM(16),
                PARAMS_DONE,
   MAPPING_DONE,

   CREATE_UNIT (VDRUID_DVD_DEMUX_AUDIO_UNPACKER, CreateDVDPESStreamUnpackerUnit),
                DWORD_PARAM(2),
                PARAMS_DONE,
   MAPPING_DONE,

   CREATE_UNIT (VDRUID_DVD_DEMUX_SUBPICTURE_UNPACKER, CreateDVDPESStreamUnpackerUnit),
                DWORD_PARAM(1),
                PARAMS_DONE,
   MAPPING_DONE,

   UNITS_DONE
   };

