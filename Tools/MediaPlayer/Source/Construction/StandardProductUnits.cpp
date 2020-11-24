// This is an example for how to declare all Physical Units that
// make up the Board/System, and how they depend on each other.

#include "StandardProductMemoryMap.h"
#include "ThreadConfiguration.h"

#include "Device/Interface/Unit/Interrupt/IInterruptControl.h"

//
// VDR includes
//

#include "VDR/Source/Construction/IUnitConstruction.h"

#include "VDR/Interface/Unit/Audio/IVDRAudioUnits.h"
#include "VDR/Interface/Unit/Video/IVDRVideoUnits.h"
#include "VDR/Interface/Unit/Datapath/VDRMixerInputTypes.h"
#include "VDR/Interface/Unit/Board/IVDRBoard.h"
#include "VDR/Interface/Unit/Communication/IVDRRS232.h"
#include "VDR/Interface/Unit/Drive/IVDRDriveTable.h"
#include "VDR/Interface/Unit/EncBufferAllocator/IVDREncBufferAllocator.h"
#include "VDR/Interface/Unit/Memory/IVDRMemoryUnits.h"
#include "VDR/Interface/Unit/Region/IVDRRegion.h"
#include "VDR/Interface/Unit/Remote/IVDRRemote.h"
#include "VDR/Interface/Unit/Support/IVDRDebugMenu.h"
#include "VDR/Interface/Unit/Datapath/IVDRDatapathUnits.h"
#include "VDR/Interface/Unit/Video/Display/IVDRVideoDisplay.h"
#include "VDR/Interface/Unit/Video/DVDecoder/IVDRDVCapture.h"
#include "VDR/Interface/Unit/FrontPanel/IVDRFrontPanel.h"

#include "VDR/Interface/Unit/Video/StillFrameDecoder/IVDRStillFrameDecoderUnits.h"
#include "VDR/Interface/Unit/DRM/Adp/IVDRDrmAdpEngineUnits.h"

//
// application relative includes
//

// Include Custom Unit IDs (includes Common Custom Unit IDs, too)
#include "../../Interface/ICustomUnitIDs.h"

#include "../../Source/Unit/Remote/StandardProductKeyboardRemoteMapping.h"
#include "../../Source/Unit/Drive/DriveConfiguration.h"

// From here we get the Unit Creation Functions declarations.
// This file will be automatically created in the future:
#include "UnitCreationFunctions.ucf"




// Temporary switch for testing new video stream mixer (remove as soon as it has been deugged!)
#define USE_MME_AUDIO_MIXER				1
#define USE_FAKE_SUBPICTURE_STREAMING	0

					  
//// JPEG DEBUG defines
// set the following switch to activate debug units at the inoput and output
// of the JPEGFrameStreamDecoder streaming unit
#define _JPEG_DEBUG_UNITS (_DEBUG && 0)
// this must be set to 1, as otherwise not frame mixer input is generated for JPEG
#define JPEG_MIXER_COUNT 1


#define TERMINATE_AUDIO_STREAMING		0
#define TERMINATE_VIDEO_STREAMING		0	// pre decoder
#define TERMINATE_VIDEO_MIXER_INPUT		0
#define TERMINATE_SUBPIC_MIXER_INPUT	0
#define TERMINATE_OSD_MIXER_INPUT	   0
#define TERMINATE_SPDIF_MIXER_INPUT     1
#define TERMINATE_SPDIF_OUT				1

// Use the following switches to insert StreamingDebug units in the demux
// and/or audio decoder chains, to monitor the streaming (logs to DPR).
#define DEBUG_DEMULTIPLEXER_STREAMING		0
#define DEBUG_AUDIO_STREAMING					0
#define DEBUG_VIDEO_DECODER_STREAMING     0  // either this or demux debug !
#define DEBUG_AC3_STREAM_DECODER				0
#define DEBUG_USE_NEW_COMBINED_AUDIO_RENDERER	0
#define DEBUG_DUMP_AC3_STREAM_ANALYZER		0
#define DEBUG_DUMP_MP2A_STREAM_ANALYZER	0

#define USE_AUX_AUDIO_INPUT			1

// Define the video output format to be used
#define VIDEO_OUTPUT_FORMAT  VDR_ARGB8888 

// Here we declare the "local" unit IDs. It must be made sure that
// these numbers are unique within this file! All these IDs must have bit 30 set to 1.
//
// We declare them here because  no application is supposed to access them.
// These numbers can be reassigned for each customized project.


/************ local or private IDs must not be registered *****************/

static const VDRUID VDRUID_MEMORYOVERLAPDETECTOR			= 0x40001000;
static const VDRUID VDRUID_MEMORY_MESSAGE_DISPATCHER		= 0x40001001;

// all playback memory partition & pools
static const VDRUID VDRUID_PLAYBACK_MEMORY_PARTITION		= 0x40001010;
static const VDRUID VDRUID_PLAYBACK_LINEAR_MEMORY_POOL	= 0x40001011;	// currently defined in ICustomUnits.h - for to be seen by tests
static const VDRUID VDRUID_PLAYBACK_HEAP_MEMORY_POOL			= 0x40001012;

// all recording memory partition & pool
static const VDRUID VDRUID_RECORDING_MEMORY_PARTITION		= 0x40001020;
static const VDRUID VDRUID_RECORDING_LINEAR_MEMORY_POOL	= 0x40001021;	// currently defined in ICustomUnits.h - for to be seen by tests

// clut memory pool for video mixer
static const VDRUID VDRUID_MIXER_CLUT_LINEAR_MEMORY_POOL	= 0x40001030;

// Drive stuff.
static const VDRUID VDRUID_DRIVE_1								= 0x40001100;
static const VDRUID VDRUID_DRIVE_2								= 0x40001101;

static const VDRUID VDRUID_TRACKBUFFER_DRIVE_1				= 0x40001102;
static const VDRUID VDRUID_LINEARMEMPOOL_DRIVE_1			= 0x40001103;
static const VDRUID VDRUID_MEMORYPARTITION_DRIVE_1			= 0x40001104;
static const VDRUID VDRUID_ATA_HARDWARE_PROXY_DRIVE_1		= 0x40001105;

static const VDRUID VDRUID_TRACKBUFFER_DRIVE_2				= 0x40001106;
static const VDRUID VDRUID_LINEARMEMPOOL_DRIVE_2			= 0x40001107;
static const VDRUID VDRUID_MEMORYPARTITION_DRIVE_2			= 0x40001108;
static const VDRUID VDRUID_ATAPI_HARDWARE_PROXY_DRIVE_2	= 0x40001109;


static const VDRUID VDRUID_MME_MANAGER							= 0x40006000;

static const VDRUID VDRUID_AUDIO_PLAYER						= 0x40003022;
static const VDRUID VDRUID_OCTOPUS_AUDIO_DECODER			= 0x40003023;
static const VDRUID VDRUID_OCTOPUS_AUDIO_DECODE_RENDERER	= 0x40003026;
static const VDRUID VDRUID_MAIN_MIXER_INPUT					= 0x40003027;
static const VDRUID VDRUID_AUX_MIXER_INPUT					= 0x40003028;
static const VDRUID VDRUID_WIN32_PCM_POST_PROCESSOR		= 0x40003029;
static const VDRUID VDRUID_MAIN_PCM_RENDERER					= 0x4000302b;
static const VDRUID VDRUID_AUX_PCM_RENDERER					= 0x4000302c;
static const VDRUID VDRUID_MAIN_MIXER_OUTPUT					= 0x4000302d;
static const VDRUID VDRUID_8K_MAIN_PCM_PLAYER				= 0x4000302e;
static const VDRUID VDRUID_WIN32_MAIN_PCM_PLAYER			= 0x4000302f;
static const VDRUID VDRUID_AUDIO_FRAME_MIXER					= 0x40003030;
static const VDRUID VDRUID_MME_AUDIO_FRAME_MIXER			= 0x40003031;
static const VDRUID VDRUID_SPDIF_FRAME_MIXER					= 0x40003032;
static const VDRUID VDRUID_MAIN_SPDIF_MIXER_INPUT			= 0x40003033;
static const VDRUID VDRUID_AC3_FRAME_STREAM_REPLICATOR	= 0x40003034;
static const VDRUID VDRUID_LPCM_FRAME_STREAM_REPLICATOR	= 0x40003035;
static const VDRUID VDRUID_MPEG2AUDIO_FRAME_STREAM_REPLICATOR	= 0x40003036;
static const VDRUID VDRUID_MME_MACRO_DECODER_PROCESSOR	= 0x40003037;	
static const VDRUID VDRUID_MME_PCM_POST_PROCESSSOR			= 0x40003038;
static const VDRUID VDRUID_DTS_FRAME_STREAM_REPLICATOR	= 0x40003039;		//Previr
static const VDRUID VDRUID_MLP_FRAME_STREAM_REPLICATOR	= 0x4000303a;		//Satej
static const VDRUID VDRUID_CDDA_FRAME_STREAM_REPLICATOR	= 0x4000303b;		//Kausik
static const VDRUID VDRUID_WIN32_MAIN_SPDIF_PLAYER			= 0x4000303c;

// For testing the chain links
static const VDRUID VDRUID_MAIN_SPDIF_RENDERER					= 0x40003080;
static const VDRUID VDRUID_STANDARD_SPDIF_PLAYER				= 0x40003081;
static const VDRUID VDRUID_8K_SPDIF_DATA_FORMATTER				= 0x40003082;
static const VDRUID VDRUID_SPDIF_MIXER_OUTPUT					= 0x40003084;
static const VDRUID VDRUID_PCM_MIXER_SPDIF_PCM_OUTPUT			= 0x40003085;
static const VDRUID VDRUID_STANDARD_SPDIF_PLAYBACK				= 0x40003086;

static const VDRUID VDRUID_MESSAGE_DISPATCHER				= 0x40002001;

static const VDRUID VDRUID_AC3_FRAME_ANALYZER				= 0x40002002;
static const VDRUID VDRUID_AC3_FRAME_STREAM_DECODER		= 0x40002003;
static const VDRUID VDRUID_AC3_STREAM_DECODER				= 0x40002004;
static const VDRUID VDRUID_LPCM_FRAME_ANALYZER				= 0x40002005;
static const VDRUID VDRUID_LPCM_STREAM_DECODER				= 0x40002006;
static const VDRUID VDRUID_MPEG2AUDIO_FRAME_ANALYZER		= 0x40002007;
static const VDRUID VDRUID_MPEG2AUDIO_STREAM_DECODER		= 0x40002008;
static const VDRUID VDRUID_MPEG2AUDIO_FRAME_STREAM_DECODER	= 0x40002009;
static const VDRUID VDRUID_DTS_FRAME_ANALYZER				= 0x40002010;		//Previr
static const VDRUID VDRUID_DTS_STREAM_DECODER				= 0x40002011;		//Previr
static const VDRUID VDRUID_DTS_FRAME_STREAM_DECODER		= 0x40002012;		//Previr
static const VDRUID VDRUID_MLP_FRAME_ANALYZER				= 0x40002013;		//Satej
static const VDRUID VDRUID_MLP_STREAM_DECODER				= 0x40002014;		//Satej
static const VDRUID VDRUID_MLP_FRAME_STREAM_DECODER		= 0x40002015;		//Satej

static const VDRUID VDRUID_CDDA_FRAME_STREAM_DECODER		= 0x40002016;		//Kausik for CDDA Decoder
static const VDRUID VDRUID_CDDA_SUBCH_FRAME_SPLITTER		= 0x40002017;		//Kausik for CDDA Decoder
static const VDRUID VDRUID_CDDA_AUDIO_FRAME_SPLITTER		= 0x40002018;		//Kausik for CDDA Decoder
static const VDRUID VDRUID_CDDA_STREAM_DECODER				= 0x40002019;

static const VDRUID VDRUID_AC3_FRAME_ANALYZER_PLAYER		= 0x40002100;
static const VDRUID VDRUID_MME_AC3_FRAME_DECODER			= 0x40002102;
static const VDRUID VDRUID_LPCM_FRAME_STREAM_DECODER		= 0x40002103;
static const VDRUID VDRUID_MME_LPCM_FRAME_DECODER			= 0x40002104;
static const VDRUID VDRUID_MME_MPEG2AUDIO_FRAME_DECODER	= 0x40002105;
static const VDRUID VDRUID_MME_DTS_FRAME_DECODER			= 0x40002106;		//Previr
static const VDRUID VDRUID_MME_MLP_FRAME_DECODER			= 0x40002107;		//Satej

static const VDRUID VDRUID_MME_CDDA_FRAME_DECODER			= 0x40002108;		//Kausik for CDDA Decoder

static const VDRUID VDRUID_GENERIC_AUDIO_SYNTH				= 0x40002200;
static const VDRUID VDRUID_WAVE_GENERATOR						= 0x40002201;

static const VDRUID VDRUID_MIXER_INPUT_CONTROL_AUX			= 0x40002300;
static const VDRUID VDRUID_MAIN_AUDIO_RENDERER							= 0x40003040;
static const VDRUID VDRUID_AUDIO_RENDERER_FRAME_STREAM_REPLICATOR	= 0x40003041;

//
// Primary Video Transducer
//
static const VDRUID VDRUID_PRIMARY_VIDEO_TRANSDUCER		= 0x40003100;
static const VDRUID VDRUID_MPEG_VIDEO_DECODER				= 0x40003110;
static const VDRUID VDRUID_MPEG_VIDEO_DATA_HANDLER			= 0x40003111;
static const VDRUID VDRUID_STRATEGIC_MPEG_VIDEO_DECODER	= 0x40003112;

static const VDRUID VDRUID_DMA_AND_SCD_ENGINE				= 0x40003120;
static const VDRUID VDRUID_MPEG_VIDEO_HEADER_PARSER		= 0x40003130;
static const VDRUID VDRUID_DVD_VIDEO_FRAME_EXTRACTOR		= 0x40003150;
static const VDRUID VDRUID_JPEG_FRAME_EXTRACTOR          = 0x40003151;

//
// Secondary Video Transducer (kept private until at the moment)
//
static const VDRUID VDRUID_SECONDARY_VIDEO_TRANSDUCER		= 0x40007100;
static const VDRUID VDRUID_SUBPICTURE_DECODER				= 0x40007101;
static const VDRUID VDRUID_SUBPICTURE_DATA_HANDLER			= 0x40007102;
static const VDRUID VDRUID_STRATEGIC_SUBPICTURE_DECODER	= 0x40007103;
static const VDRUID VDRUID_SOFTWARE_DMA_ENGINE				= 0x40007104;

//
// Video frame mixer
//
static const VDRUID VDRUID_VIDEO_FRAME_MIXER					= 0x40003000;
static const VDRUID VDRUID_BUTTON_HIGHLIGHT_PROCESSOR		= 0x40003001;
//
// Video Frame Mixer input IDs
//
static const VDRUID VDRUID_VIDEO_FRAME_MIXER_INPUT			= 0x40003140;	// main video
static const VDRUID VDRUID_VIDEO_FRAME_MIXER_INPUT_1		= 0x40003141;	// subpicture
static const VDRUID VDRUID_VIDEO_FRAME_MIXER_INPUT_2		= 0x40003142;	// on screen display (OSD)
static const VDRUID VDRUID_VIDEO_FRAME_MIXER_INPUT_3		= 0x40003143;	// additional OSD for test player
static const VDRUID VDRUID_VIDEO_FRAME_MIXER_INPUT_5		= 0x40003145;	// JPEG decoder's mixer input

//
// Input controls for video mixer inputs
//
static const VDRUID VDRUID_VIDEO_MIXER_INPUT_CONTROL_MAIN_INTERNAL			= 0x40003160;
static const VDRUID VDRUID_VIDEO_MIXER_INPUT_CONTROL_SUBPICTURE_INTERNAL	= 0x40003161;
static const VDRUID VDRUID_VIDEO_MIXER_INPUT_CONTROL_OSD_INTERNAL				= 0x40003162;

//
// VBI IDs
//
static const VDRUID VDRUID_VBI_DECODER							= 0x40003200;
static const VDRUID VDRUID_VBI_LINE_PARSER					= 0x40003205;
static const VDRUID VDRUID_VBI_REPLICATOR						= 0x40003210;
static const VDRUID VDRUID_GEMSTAR_DECODER					= 0x40003220;
static const VDRUID VDRUID_CGMS_DECODER						= 0x40003230;
static const VDRUID VDRUID_CGMS_REPLICATOR					= 0x40003240;
static const VDRUID VDRUID_TELETEXT_DECODER					= 0x40003250;
static const VDRUID VDRUID_VPS_DECODER							= 0x40003260;



//
// Program Stream Transducer
//
static const VDRUID VDRUID_PROGRAM_STREAM_TRANSDUCER		= 0x40004000;
static const VDRUID VDRUID_MPEG_DEMULTIPLEXER				= 0x40004001;

//
// Alternate DVD Demux
//
static const VDRUID VDRUID_DVD_STREAM_TRANSDUCER			= 0x40004031;
static const VDRUID VDRUID_DVD_DEMULTIPLEXER					= 0x40004020;
static const VDRUID VDRUID_DVD_DEMUX_REPLICATOR				= 0x40004021;
static const VDRUID VDRUID_DVD_DEMUX_VIDEO_SPLITTER		= 0x40004022;
static const VDRUID VDRUID_DVD_DEMUX_AUDIO_SPLITTER		= 0x40004023;
static const VDRUID VDRUID_DVD_DEMUX_SUBPICTURE_SPLITTER	= 0x40004024;
static const VDRUID VDRUID_DVD_DEMUX_VIDEO_UNPACKER		= 0x40004025;
static const VDRUID VDRUID_DVD_DEMUX_AUDIO_UNPACKER		= 0x40004026;
static const VDRUID VDRUID_DVD_DEMUX_SUBPICTURE_UNPACKER	= 0x40004027;

static const VDRUID VDRUID_MPEGPROGRAM_STREAM_TRANSDUCER				= 0x40004231;
static const VDRUID VDRUID_MPEGPROGRAM_DEMULTIPLEXER					= 0x40004220;
static const VDRUID VDRUID_MPEGPROGRAM_DEMUX_REPLICATOR				= 0x40004221;
static const VDRUID VDRUID_MPEGPROGRAM_DEMUX_VIDEO_SPLITTER			= 0x40004222;
static const VDRUID VDRUID_MPEGPROGRAM_DEMUX_AUDIO_SPLITTER			= 0x40004223;
static const VDRUID VDRUID_MPEGPROGRAM_DEMUX_SUBPICTURE_SPLITTER	= 0x40004224;
static const VDRUID VDRUID_MPEGPROGRAM_DEMUX_VIDEO_UNPACKER			= 0x40004225;
static const VDRUID VDRUID_MPEGPROGRAM_DEMUX_AUDIO_UNPACKER			= 0x40004226;
static const VDRUID VDRUID_MPEGPROGRAM_DEMUX_SUBPICTURE_UNPACKER	= 0x40004227;

//
// Demultiplexed Stream Transducer
//
static const VDRUID VDRUID_DEMULTIPLEXED_STREAM_TRANSDUCER		= 0x40004040;
static const VDRUID VDRUID_DEMULTIPLEXED_STREAM_DEMULTIPLEXER	= 0x40004041;
//
//DVD Audio related units
//

//DVDAudio Transducer Proxy - Demux with Audio and RTI(in future) chain
static const VDRUID VDRUID_DVDAUDIO_DEMULTIPLEXER			= 0x40004228;//Output Audio Chain and RTI chain (in future)
static const VDRUID VDRUID_DVDAUDIO_STREAM_TRANSDUCER			= 0x40004229;

//ASV Transducer Proxy - Demux with Video and SubPic chain
static const VDRUID VDRUID_ASV_DEMUX_REPLICATOR				= 0x4000422a;
static const VDRUID VDRUID_ASV_DEMULTIPLEXER				= 0x4000422b;//Output Video and Subpic chain
static const VDRUID VDRUID_ASV_TRANSDUCER				= 0x4000422c;

//
// Video display stuff
//
static const VDRUID VDRUID_VIDEO_OUT								= 0x40000006;
static const VDRUID VDRUID_VIDEO_PLAYER							= 0x40000007;
static const VDRUID VDRUID_VIDEO_MIXER_OUTPUT					= 0x4000000a;

static const VDRUID VDRUID_VIDEO_BLITTER							= 0x4000000f;
static const VDRUID VDRUID_VIDEO_RENDERER							= 0x40000010;
static const VDRUID VDRUID_STM8000_VIDEO_MIXER					= 0x40000011;
static const VDRUID VDRUID_GRAPHICS_2D								= 0x40000012;
static const VDRUID VDRUID_DEFERRED_VIDEO_BLITTER					= 0x40000013;
static const VDRUID VDRUID_VIDEO_OUTPUT                     = 0x40009020;

//
// DV Decoder 
//
static const VDRUID VDRUID_DV_FRAME_DECODER						= 0x40007000;
static const VDRUID VDRUID_DV_DATA_HANDLER						= 0x40007001;
static const VDRUID VDRUID_WIN32_DV_DECODER						= 0x40007002; 
static const VDRUID VDRUID_DV_AUDIO_DECODER						= 0x40007003; 
static const VDRUID VDRUID_WIN32_DV_AUDIO_DECODER				= 0x40007004; 
static const VDRUID VDRUID_DV_CAPTURE_VIDEO_LINK_INPUT		= 0x40007005; 
static const VDRUID VDRUID_STM_8000_DV_CAPTURE					= 0x40007006;
static const VDRUID VDRUID_DV_VIDEO_PREPROCESSOR_LINK_OUTPUT		= 0x40007007; 
static const VDRUID VDRUID_FORMAT_CONVERTER						= 0x40007008; 


// 
// IEEE 1394
//
static const VDRUID VDRUID_IEEE_1394_BUS							= 0x40007010; 


// interrupt levels
static const VDRUID VDRUID_INTERRUPT_LEVEL_1						= 0x40004102;
static const VDRUID VDRUID_INTERRUPT_LEVEL_2						= 0x40004103;
static const VDRUID VDRUID_INTERRUPT_LEVEL_3						= 0x40004104;
static const VDRUID VDRUID_INTERRUPT_LEVEL_4						= 0x40004105;
static const VDRUID VDRUID_INTERRUPT_LEVEL_5						= 0x40004106;
static const VDRUID VDRUID_INTERRUPT_LEVEL_6						= 0x40004107;
static const VDRUID VDRUID_INTERRUPT_LEVEL_7						= 0x40004108;
static const VDRUID VDRUID_INTERRUPT_LEVEL_8						= 0x40004109;
static const VDRUID VDRUID_INTERRUPT_LEVEL_9						= 0x4000410a;
static const VDRUID VDRUID_INTERRUPT_LEVEL_10					= 0x4000410b;
static const VDRUID VDRUID_INTERRUPT_LEVEL_11					= 0x4000410c;
static const VDRUID VDRUID_INTERRUPT_LEVEL_12					= 0x4000410d;
static const VDRUID VDRUID_INTERRUPT_LEVEL_13					= 0x4000410e;
static const VDRUID VDRUID_INTERRUPT_LEVEL_14					= 0x4000410f;
static const VDRUID VDRUID_INTERRUPT_LEVEL_15					= 0x40004110;
static const VDRUID VDRUID_INTERRUPT_LEVEL_0						= 0x40004112;


// Win32 interrupt stuff
static const VDRUID VDRUID_INTERRUPT_CONTROLLER					= 0x40005100;
static const VDRUID VDRUID_VSYNC_INTERRUPT						= 0x40005101;

// Win32 support stuff
static const VDRUID VDRUID_WIN32_APPLICATIONWINDOW				= 0x40005000;
static const VDRUID VDRUID_WIN32_WINDOWCONTROL					= 0x40005001;
static const VDRUID VDRUID_WIN32_EVENTPROVIDER					= 0x40005003;
static const VDRUID VDRUID_WIN32_RUNTIMECONFIGURATOR			= 0x40005004;
static const VDRUID VDRUID_WIN32_FRONTPANEL                 = 0x40005006;
static const VDRUID VDRUID_FRONT_PANEL_STRING_OPERATIONS    = 0x40005007;
static const VDRUID VDRUID_FRONT_PANEL_PIE_OPERATIONS       = 0x40005008;
static const VDRUID VDRUID_FRONT_PANEL_ICONCONTROL          = 0x40005009;
static const VDRUID VDRUID_WIN32REMOTE                      = 0x4000500a;
static const VDRUID VDRUID_DEBUG_MENU_COMM_PROXY            = 0x4000500b;


// JPEG
static const VDRUID VDRUID_STILL_FRAME_SPECIALFX_UNIT			= 0x40009000;
static const VDRUID VDRUID_JPEG_FRAME_STREAM_DECODER			= 0x40009001;
static const VDRUID VDRUID_MME_JPEG_FRAME_DECODER				= 0x40009002;
static const VDRUID VDRUID_JPEG_TEST_CHAIN						= 0x40009003;
static const VDRUID VDRUID_JPEG_OUTPUT_TERMINATOR				= 0x40009004;
static const VDRUID VDRUID_JPEG_STREAMING_CHAIN					= 0x40009005;


static const VDRUID VDRUID_STREAMING_DEBUG_1						= 0x4000a001;
static const VDRUID VDRUID_STREAMING_DEBUG_2						= 0x4000a002;
static const VDRUID VDRUID_STREAMING_DEBUG_3						= 0x4000a003;
static const VDRUID VDRUID_STREAMING_DEBUG_4						= 0x4000a004;
static const VDRUID VDRUID_STREAMING_DEBUG_5						= 0x4000a005;
static const VDRUID VDRUID_STREAMING_DEBUG_6						= 0x4000a006;
static const VDRUID VDRUID_STREAMING_DEBUG_7						= 0x4000a007;
static const VDRUID VDRUID_STREAMING_DEBUG_CDDA_1				= 0x4000a008;
static const VDRUID VDRUID_STREAMING_DEBUG_CDDA_2				= 0x4000a009;

static const VDRUID VDRUID_STREAMING_DEBUG_AUDIO_1				= 0x4000c010;
static const VDRUID VDRUID_STREAMING_DEBUG_AUDIO_2				= 0x4000c011;
static const VDRUID VDRUID_STREAMING_DEBUG_AUDIO_3				= 0x4000c012;
static const VDRUID VDRUID_STREAMING_DEBUG_AC3_1				= 0x4000c020;
static const VDRUID VDRUID_STREAMING_DEBUG_AC3_2				= 0x4000c021;
static const VDRUID VDRUID_STREAMING_DEBUG_AC3_3				= 0x4000c022;
static const VDRUID VDRUID_STREAMING_DEBUG_AC3_4				= 0x4000c023;
static const VDRUID VDRUID_STREAMING_DEBUG_AC3_5				= 0x4000c024;
static const VDRUID_STREAMING_DEBUG_AUDIO_RENDERER_1			= 0x4000c025;
static const VDRUID_STREAMING_DEBUG_AUDIO_RENDERER_2			= 0x4000c026;
static const VDRUID_STREAMING_DEBUG_AUDIO_RENDERER_3			= 0x4000c027;

static const VDRUID VDRUID_STREAMING_DEBUG_MP2a_1				= 0x4000c120;

#if _JPEG_DEBUG_UNITS
static const VDRUID VDRUID_STREAMING_JPEG_DEBUG_1				= 0x4000c020;
static const VDRUID VDRUID_STREAMING_JPEG_DEBUG_2				= 0x4000c021;
#endif


//Default video mixer input and output video standard
static const MovingImageStandard defaultDisplayVideoStandard = MIS_576_25;


uint32 GlobalBoardConfig[] =
	{
	CREATE_UNIT(VDRUID_VDR_BOARD, CreateStandardBoard),
					//??? The following creation parameters should be automatically retrieved from somewhere...
					DWORD_PARAM(1),		// boardVersion
					DWORD_PARAM(0),		// boardRevision
					DWORD_PARAM(0),		// driverVersion
					DWORD_PARAM(1),		// driverRevision
					DWORD_PARAM(4711),	// driverBuild 
					PARAMS_DONE,
		// The dependency list of the board determines the units an application can
		// request to be part of a Unit Set. So here we specify the units accessible
		// by applications.
		
		// The unit IDs of the following units are public, and thus defined in header files
		// located somewhere in VDR/Interface:
		
		VDRUID_DVD_STREAM_TRANSDUCER_PROXY,				PARAMS_DONE,	// DVD Program Stream Streaming Chain
		VDRUID_JPEG_FRAME_EXTRACTOR_PROXY,           PARAMS_DONE,   // 
		VDRUID_DVD_VIDEO_FRAME_EXTRACTOR_PROXY,		PARAMS_DONE,	// DVD Program Stream Video Frame Extractor Chain
		VDRUID_MPEG_PROGRAM_STREAM_TRANSDUCER_PROXY,	PARAMS_DONE,	// MPEG Program Stream Streaming Chain
		VDRUID_PROGRAM_STREAM_TRANSDUCER_PROXY,		PARAMS_DONE,	// MPEG Program Stream Streaming Chain using single unit demux (outdated)
		VDRUID_ASV_TRANSDUCER_PROXY,						PARAMS_DONE,	// ASV Transducer for ASVPlayabck in DVD-Audio
		VDRUID_DVDAUDIO_STREAM_TRANSDUCER_PROXY,		PARAMS_DONE,	// DVD Audio Transducer for AOTT playback in DVD-Audio

		VDRUID_DEMULTIPLEXED_STREAM_TRANSDUCER_PROXY,	PARAMS_DONE,	// Divx Program Stream Streaming Chain
		VDRUID_AUDIO_PLAYER_PROXY,						PARAMS_DONE,	// Standard Audio Player Streaming Chain
		VDRUID_MAIN_AUDIO_RENDERER_PROXY,			PARAMS_DONE,	// same as PCM renerer proxy
		VDRUID_AUDIO_PCM_STREAM_MIXER,				PARAMS_DONE,	// PCM Audio Stream Mixer (for property control by application)
		VDRUID_SPDIF_STREAM_MIXER,						PARAMS_DONE,	// SPDIF Mixer
		VDRUID_VIDEO_MIXER,								PARAMS_DONE,	// Video Mixer (for property control by application)
#if USE_AUX_AUDIO_INPUT
		VDRUID_AUDIO_SYNTHESIZER,						PARAMS_DONE,	// Audio Synthesizer for generating test sounds
		VDRUID_AUDIO_MIXER_INPUT_CONTROL_AUX,		PARAMS_DONE,	// 
#endif
		VDRUID_AUDIO_PCM_POST_PROCESSOR_CONTROL,	PARAMS_DONE,
		VDRUID_GRAPHICS_2D_PROXY,						PARAMS_DONE,
		VDRUID_VIDEO_RENDERER_PROXY,					PARAMS_DONE,	// Video renderer Streaming Chain
		VDRUID_VIDEO_MIXER,								PARAMS_DONE,

		VDRUID_VIDEO_MIXER_INPUT_CONTROL_MAIN,			PARAMS_DONE,
		VDRUID_VIDEO_MIXER_INPUT_CONTROL_SUBPICTURE,	PARAMS_DONE,
		VDRUID_VIDEO_MIXER_INPUT_CONTROL_OSD,			PARAMS_DONE,

		VDRUID_DEFAULT_REMOTE_CONTROL,				PARAMS_DONE,	// Remote Control (enter here for messages passed to the application)
		VDRUID_ENCBUFFER_MEMORYPOOL,					PARAMS_DONE,
		VDRUID_GENERIC_PLAYBACK_POOL_ALLOCATOR,	PARAMS_DONE,
		VDRUID_DRIVETABLE,								PARAMS_DONE,
		VDRUID_REGION_UNIT,								PARAMS_DONE,
#if 0 /* Disabled by Nico 16-04-2007 */
		VDRUID_VBI_DECODER_PROXY,						PARAMS_DONE,	// Used in VideoDisplayTest
#endif
		VDRUID_DRM_ADP_ENGINE,							PARAMS_DONE,

		// The following unit IDs are not (yet) publicly defined.
		// However, we want to make them available for testing with our
		// Demo Board or Streaming Test applications. For this purpose
		// they are made "Customer defined" unit IDs, and so their
		// declaration is moved to Custom/DemoBoard/Interface/IVDRCustomUnitIDs.h.
		// That file can then be included by "customized" applications.

		VDRUID_VIDEO_PLAYER_PROXY,						PARAMS_DONE,	// Used in VideoDisplayTest
		VDRUID_VIDEO_DISPLAY,							PARAMS_DONE,	// Used in VideoDisplayTest
		VDRUID_DRIVE_2,									PARAMS_DONE,
		VDRUID_AC3_STREAM_PLAYER,						PARAMS_DONE,	
		VDRUID_TEST_LINEARMEMPOOL_DRIVE_1,			PARAMS_DONE,	// Testing purposes
		VDRUID_JPEG_DECODER_PROXY,						PARAMS_DONE,	// Testing purposes
		VDRUID_FRONT_PANEL_DISPLAY_PROXY,         PARAMS_DONE,
		MAPPING_DONE,

	////////////////////////////////////////////////////////////////////////////
	// MemoryPoolAllocator message dispatcher
	////////////////////////////////////////////////////////////////////////////

	CREATE_UNIT (VDRUID_MEMORY_MESSAGE_DISPATCHER, CreateMessageDispatcher),
					 DWORD_PARAM(TCTP_MEMORY_MESSAGE_DISPATCHER),		// Thread priority
					 DWORD_PARAM(TCSS_MEMORY_MESSAGE_DISPATCHER),		// Stack size
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
					 DWORD_PARAM(PLAYBACK_MEMORY_PARTITION_SIZE), PARAMS_DONE,	// LMI memory!
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

	// The memory partition for the track buffer memory of drive 1.
	CREATE_UNIT (VDRUID_MEMORYPARTITION_DRIVE_1, CreateMemoryPartition),
					 DWORD_PARAM(MEMORYPARTITION_DRIVE_1_BASE),
					 DWORD_PARAM(MEMORYPARTITION_DRIVE_1_SIZE),
					 PARAMS_DONE,
		VDRUID_MEMORYOVERLAPDETECTOR, PARAMS_DONE,
		MAPPING_DONE,

	// The memory pool for drive 1 uses the memory partition.
	CREATE_UNIT (VDRUID_LINEARMEMPOOL_DRIVE_1, CreateLinearMemoryPool),
					 PARAMS_DONE,
		VDRUID_MEMORYPARTITION_DRIVE_1, PARAMS_DONE,
		VDRUID_MEMORY_MESSAGE_DISPATCHER, PARAMS_DONE,
		MAPPING_DONE,

	// The memory partition for the track buffer memory of drive 2
	CREATE_UNIT (VDRUID_MEMORYPARTITION_DRIVE_2, CreateMemoryPartition),
					 DWORD_PARAM(MEMORYPARTITION_DRIVE_2_BASE),
					 DWORD_PARAM(MEMORYPARTITION_DRIVE_2_SIZE),
					 PARAMS_DONE,
		VDRUID_MEMORYOVERLAPDETECTOR, PARAMS_DONE,
		MAPPING_DONE,

	// The memory pool for drive 2 uses the memory partition.
	CREATE_UNIT (VDRUID_LINEARMEMPOOL_DRIVE_2, CreateLinearMemoryPool),
					 PARAMS_DONE,
		VDRUID_MEMORYPARTITION_DRIVE_2, PARAMS_DONE,
		VDRUID_MEMORY_MESSAGE_DISPATCHER, PARAMS_DONE,
		MAPPING_DONE,


	// The memory pool for drive 1 test applications.
	CREATE_UNIT (VDRUID_TEST_LINEARMEMPOOL_DRIVE_1, CreateLinearMemoryPool),
					 PARAMS_DONE,
		VDRUID_MEMORYPARTITION_DRIVE_1, PARAMS_DONE,
		VDRUID_MEMORY_MESSAGE_DISPATCHER, PARAMS_DONE,
		MAPPING_DONE,

	// The memory partition for all recording devices.
	CREATE_UNIT (VDRUID_RECORDING_MEMORY_PARTITION, CreateMemoryPartition),
 					 DWORD_PARAM(RECORDING_MEMORY_PARTITION_BASE),
					 DWORD_PARAM(RECORDING_MEMORY_PARTITION_SIZE), PARAMS_DONE,
		VDRUID_MEMORYOVERLAPDETECTOR, PARAMS_DONE,
		MAPPING_DONE,

	// The linear memory pool for the recording memory.
	CREATE_UNIT (VDRUID_RECORDING_LINEAR_MEMORY_POOL, CreateLinearMemoryPool),
					 PARAMS_DONE,
		VDRUID_RECORDING_MEMORY_PARTITION, PARAMS_DONE,
		VDRUID_MEMORY_MESSAGE_DISPATCHER, PARAMS_DONE,
		MAPPING_DONE,

	// The Encoding Buffer Pool Allocator is the official vast resource for encoding (sector) buffers.
	CREATE_UNIT (VDRUID_ENCBUFFER_MEMORYPOOL, CreateEncBufferAllocator),
					 DWORD_PARAM(ENCBUFFER_POOL_SIZE), PARAMS_DONE,
		VDRUID_RECORDING_MEMORY_PARTITION, PARAMS_DONE,
		VDRUID_MEMORY_MESSAGE_DISPATCHER, PARAMS_DONE,
		MAPPING_DONE,

	////////////////////////////////////////////////////////////////////////////
	// Drive and track buffer units.
	////////////////////////////////////////////////////////////////////////////


	// The track buffer for drive 1 supports 300 sector infos.
	CREATE_UNIT (VDRUID_TRACKBUFFER_DRIVE_1, CreateHash1Trackbuffer),
					 DWORD_PARAM(300), PARAMS_DONE,
		MAPPING_DONE,

	// The track buffer for drive 2 supports 300 sector infos.
	CREATE_UNIT (VDRUID_TRACKBUFFER_DRIVE_2, CreateHash1Trackbuffer),
					 DWORD_PARAM(6000), PARAMS_DONE,
		MAPPING_DONE,

	// This is drive 2. The track buffer uses all of the memory partition it resides in.
	CREATE_UNIT (VDRUID_DRIVE_2, CreateATAPISingleTrayDrive),
					 DWORD_PARAM(MEMORYPARTITION_DRIVE_2_SIZE), 
					 STRING_PARAM("DVD"),
					 DWORD_PARAM(TCTP_DRIVE),		// Thread priority
					 DWORD_PARAM(TCSS_DRIVE),		// Stack size
					 PARAMS_DONE,
		VDRUID_TRACKBUFFER_DRIVE_2, PARAMS_DONE,
		VDRUID_ATAPI_HARDWARE_PROXY_DRIVE_2, PARAMS_DONE,		// the proxy is also the data control
		VDRUID_ATAPI_HARDWARE_PROXY_DRIVE_2, PARAMS_DONE,		// the proxy is also the hardware control
		VDRUID_MESSAGE_DISPATCHER, PARAMS_DONE,
		MAPPING_DONE,

	// The ATAPI hardware proxy for drive 2. It is also the drive's Data Control.
	CREATE_UNIT (VDRUID_ATAPI_HARDWARE_PROXY_DRIVE_2, CreateWin32ATAPIHardwareProxy),
					 DWORD_PARAM(64), PARAMS_DONE,		// number of communication buffers
		VDRUID_LINEARMEMPOOL_DRIVE_2,			PARAMS_DONE, // memory pool for trackbuffer
		MAPPING_DONE,


	// This is drive 1. The track buffer uses all of the memory partition it resides in.
	/* CREATE_UNIT (VDRUID_DRIVE_1, CreateATADrive),
					 DWORD_PARAM(MEMORYPARTITION_DRIVE_1_SIZE),
					 STRING_PARAM("Harddisk"), 
					 DWORD_PARAM(TCTP_DRIVE),		// Thread priority
					 DWORD_PARAM(TCSS_DRIVE),		// Stack size					 
					 PARAMS_DONE,
		VDRUID_TRACKBUFFER_DRIVE_1, PARAMS_DONE,
		VDRUID_ATA_HARDWARE_PROXY_DRIVE_1, PARAMS_DONE,		// the proxy is also the data control
		VDRUID_ATA_HARDWARE_PROXY_DRIVE_1, PARAMS_DONE,		// the proxy is also the hardware control
		VDRUID_MESSAGE_DISPATCHER, PARAMS_DONE,
		MAPPING_DONE, */

	// The Win32 ATA hardware proxy for drive 1. It is also the drive's Data Control.
	CREATE_UNIT (VDRUID_ATA_HARDWARE_PROXY_DRIVE_1, CreateWin32ATAHardwareProxy),
					 DWORD_PARAM(64),		// 64 communication buffers
		STRING_PARAM(DRIVE_CONFIGURATION_INCLUDE_FILE), PARAMS_DONE,
		VDRUID_LINEARMEMPOOL_DRIVE_1, PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_DRIVETABLE, CreateDriveTable),		// The DriveTable maintains a list of all drives connected.
					 DWORD_PARAM(2), PARAMS_DONE,					// This parameter means the maximum number of drives that we connect
//		VDRUID_DRIVE_1, PARAMS_DONE,
		VDRUID_DRIVE_2, PARAMS_DONE,
		MAPPING_DONE,


	////////////////////////////////////////////////////////////////////////////
	// Support Units
	////////////////////////////////////////////////////////////////////////////

	// The generic message dispatcher unit
	CREATE_UNIT (VDRUID_MESSAGE_DISPATCHER, CreateMessageDispatcher),
					 DWORD_PARAM(TCTP_GENERIC_MESSAGE_DISPATCHER),		// Thread priority
					 DWORD_PARAM(TCSS_GENERIC_MESSAGE_DISPATCHER),		// Stack size
					 STRING_PARAM(TCTN_GENERIC_MESSAGE_DISPATCHER),		// Thread name
					 PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_DEBUG_MENU, CreateDebugMenuUnit),
					 PARAMS_DONE,
		VDRUID_DEBUG_MENU_COMM_PROXY,		PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_DEBUG_MENU_COMM_PROXY, CreateWin32CommProxy),
					 DWORD_PARAM(TCTP_WIN32_COMM_PROXY),		// Thread priority
					 DWORD_PARAM(TCSS_WIN32_COMM_PROXY),		// Stack size
					 STRING_PARAM(TCTN_WIN32_COMM_PROXY),		// Thread name
					 DWORD_PARAM(4431),							// Port number
					 DWORD_PARAM(0),							// accessible from outside (0=no/1=yes)
					 PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_REGION_UNIT, CreateRegionUnit),
					 PARAMS_DONE,
		MAPPING_DONE,

	////////////////////////////////////////////////////////////////////////////
	// MME Units
	////////////////////////////////////////////////////////////////////////////

	CREATE_UNIT (VDRUID_MME_MANAGER, CreateMMEManagerUnit),
					PARAMS_DONE,
		MAPPING_DONE,

	
	////////////////////////////////////////////////////////////////////////////
	// DivxN DRM ADP units
	////////////////////////////////////////////////////////////////////////////

	CREATE_UNIT (VDRUID_DRM_ADP_ENGINE, CreateDrmAdpEngine),
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

	CREATE_UNIT (VDRUID_AC3_FRAME_ANALYZER, CreateAC3FrameAnalyzer),
					 PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_MME_MACRO_DECODER_PROCESSOR, CreateMMEMacroDecoderProcessor),
					 PARAMS_DONE,
		MAPPING_DONE,


	CREATE_UNIT (VDRUID_MME_AC3_FRAME_DECODER, CreateMMEAC3FrameDecoder),
					 DWORD_PARAM(16),						// How many frames per StreamingDataPacket on the output
					 DWORD_PARAM(3840),					// Max input frame size (compressed AC3 @ 32kHz)
					 DWORD_PARAM(6 * 256 * 4 * 10),	// Max output frame size (PCM): 6 blocks of 10 channels, with 4 bytes per sample
					 DWORD_PARAM(1),						// Want to Linearize i/p data before decoding
					 PARAMS_DONE,
		VDRUID_PLAYBACK_LINEAR_MEMORY_POOL,	PARAMS_DONE,
		VDRUID_MME_MANAGER,						PARAMS_DONE,
		VDRUID_MME_MACRO_DECODER_PROCESSOR,		PARAMS_DONE,
		MAPPING_DONE,

		
	CREATE_UNIT (VDRUID_AC3_FRAME_STREAM_DECODER, CreateMMEAC3FrameStreamDecoder),
					 DWORD_PARAM(TCTP_AUDIO_FRAME_STREAM_DECODER),		// Thread priority
					 DWORD_PARAM(TCSS_AUDIO_FRAME_STREAM_DECODER),		// Stack size
					 STRING_PARAM(TCTN_AUDIO_FRAME_STREAM_DECODER),		// Thread name
					 DWORD_PARAM(1),	// Number of frames after which to generate an output data packet
					 DWORD_PARAM(8),	// allocated output frames //chz test temp
					 PARAMS_DONE,
		VDRUID_MME_AC3_FRAME_DECODER,		PARAMS_DONE,
		MAPPING_DONE,

	// AC3 Stream Decoder (wrapper for analyzer + decoder)
#if DEBUG_AC3_STREAM_DECODER

		CREATE_UNIT (VDRUID_STREAMING_DEBUG_AC3_1, CreateLoggingStreamingUnit),
					STRING_PARAM("AC3a"),
					PARAMS_DONE,
		MAPPING_DONE,
		CREATE_UNIT (VDRUID_STREAMING_DEBUG_AC3_2, CreateLoggingStreamingUnit),
					STRING_PARAM("AC3b"),
					PARAMS_DONE,
		MAPPING_DONE,
		CREATE_UNIT (VDRUID_STREAMING_DEBUG_AC3_3, CreateLoggingStreamingUnit),
					STRING_PARAM("AC3c"),
					PARAMS_DONE,
		MAPPING_DONE,
		CREATE_UNIT (VDRUID_STREAMING_DEBUG_AC3_4, CreateLoggingStreamingUnit),
					STRING_PARAM("AC3d"),
					PARAMS_DONE,
		MAPPING_DONE,
		CREATE_UNIT (VDRUID_STREAMING_DEBUG_AC3_5, CreateLoggingStreamingUnit),
					STRING_PARAM("AC3e"),
					PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_AC3_STREAM_DECODER, CreateAudioStreamDecoderUnit),
					DWORD_PARAM(1),		// num inputs
					DWORD_PARAM(2),		// num of outputs

					// Analyzer
					DWORD_PARAM(0xff000300),	// Connect Chain, Out0 -> Unit0, In0
					DWORD_PARAM(0x03010000),

					DWORD_PARAM(0x00010400),	// Connect Unit0, Out0 -> Unit2, In0
					DWORD_PARAM(0x04010200),

					// Replicator
					DWORD_PARAM(0x02010600),	// Connect Unit2, Out1 -> Unit1, In0
					DWORD_PARAM(0x06010100),

					DWORD_PARAM(0x02020500),	// Connect Unit2, Out2 -> Chain, In1
					DWORD_PARAM(0x0501ff02),

					// Decoder
					DWORD_PARAM(0x01010700),	// Connect Unit1, Out0 -> Chain, In0
					DWORD_PARAM(0x0701ff01),

					PARAMS_DONE,
		VDRUID_AC3_FRAME_ANALYZER,						PARAMS_DONE,
		VDRUID_AC3_FRAME_STREAM_DECODER,				PARAMS_DONE,
		VDRUID_AC3_FRAME_STREAM_REPLICATOR,			PARAMS_DONE,

		VDRUID_STREAMING_DEBUG_AC3_1,					PARAMS_DONE,
		VDRUID_STREAMING_DEBUG_AC3_2,					PARAMS_DONE,
		VDRUID_STREAMING_DEBUG_AC3_3,					PARAMS_DONE,
		VDRUID_STREAMING_DEBUG_AC3_4,					PARAMS_DONE,
		VDRUID_STREAMING_DEBUG_AC3_5,					PARAMS_DONE,
		MAPPING_DONE,
#elif DEBUG_DUMP_AC3_STREAM_ANALYZER
		CREATE_UNIT (VDRUID_STREAMING_DEBUG_AC3_1, CreateDumpingStreamingUnit),
					STRING_PARAM("c:\\AC3a"),
					PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_AC3_STREAM_DECODER, CreateAudioStreamDecoderUnit),
					DWORD_PARAM(1),		// num inputs
					DWORD_PARAM(2),		// num of outputs

					// Analyzer
					DWORD_PARAM(0xff000000),	// Connect Chain, Out0 -> Unit0, In0

					DWORD_PARAM(0x00010300),	// Connect Unit0, Out0 -> Unit2, In0
					DWORD_PARAM(0x03010200),

					// Replicator
					DWORD_PARAM(0x02010100),	// Connect Unit2, Out1 -> Unit1, In0

					DWORD_PARAM(0x0202ff02),	// Connect Unit2, Out2 -> Chain, In1

					// Decoder
					DWORD_PARAM(0x0101ff01),	// Connect Unit1, Out0 -> Chain, In0

					PARAMS_DONE,
		VDRUID_AC3_FRAME_ANALYZER,						PARAMS_DONE,
		VDRUID_AC3_FRAME_STREAM_DECODER,				PARAMS_DONE,
		VDRUID_AC3_FRAME_STREAM_REPLICATOR,			PARAMS_DONE,

		VDRUID_STREAMING_DEBUG_AC3_1,					PARAMS_DONE,
		MAPPING_DONE,
#else
	CREATE_UNIT (VDRUID_AC3_STREAM_DECODER, CreateAudioStreamDecoderUnit),
					DWORD_PARAM(1),		// num inputs
					DWORD_PARAM(2),		// num of outputs

					// Analyzer
					DWORD_PARAM(0xff000000),	// Connect Chain, Out0 -> Unit0, In0
					DWORD_PARAM(0x00010200),	// Connect Unit0, Out0 -> Unit2, In0

					// Replicator
					DWORD_PARAM(0x02010100),	// Connect Unit2, Out1 -> Unit1, In0
					DWORD_PARAM(0x0202ff02),	// Connect Unit2, Out2 -> Chain, In1

					// Decoder
					DWORD_PARAM(0x0101ff01),	// Connect Unit1, Out0 -> Chain, In0

					PARAMS_DONE,
		VDRUID_AC3_FRAME_ANALYZER,						PARAMS_DONE,
		VDRUID_AC3_FRAME_STREAM_DECODER,				PARAMS_DONE,
		VDRUID_AC3_FRAME_STREAM_REPLICATOR,			PARAMS_DONE,
		MAPPING_DONE,
#endif

	CREATE_UNIT (VDRUID_AC3_FRAME_STREAM_REPLICATOR, CreateStreamReplicatorStreamingUnit),
				DWORD_PARAM(2),	// 1 stream -> 2 streams
				DWORD_PARAM(3),	// SRMFM_FORWARD_MAIN
				PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_AC3_STREAM_PLAYER, CreateSingleStreamingProxyUnit),
					 PARAMS_DONE,
		VDRUID_MESSAGE_DISPATCHER, PARAMS_DONE,
		VDRUID_AC3_STREAM_DECODER, PARAMS_DONE,
		MAPPING_DONE,


	//
	// LPCM
	//

	// LPCM Audio Frame Analyzer (used to quantize source PCM data)
	CREATE_UNIT (VDRUID_LPCM_FRAME_ANALYZER, CreateLPCMFrameAnalyzer),
					 DWORD_PARAM(8 * 300),				// Number of samples per Data Range that is sent 
																// (must be multiple of 8 if GPFIFO transfer size is 8 cells)
					 PARAMS_DONE,
		MAPPING_DONE,

	// MME LPCM Frame Decoder (interface unit to MME)
	CREATE_UNIT (VDRUID_MME_LPCM_FRAME_DECODER, CreateMMELPCMFrameDecoder),
					 DWORD_PARAM(4),						// Max number of frames to queue at MME
					 DWORD_PARAM(8 * 300),				// Max input frame size (here: 1 frame = 1 DVD packet content)
					 DWORD_PARAM(6 * 256 * 4 * 10),	// Max output frame size (PCM): 1004 samples (mono) to 10 channels, with 4 bytes per sample
					 DWORD_PARAM(1),						// Want to Linearize i/p data before decoding
					 PARAMS_DONE,
		VDRUID_PLAYBACK_LINEAR_MEMORY_POOL,	PARAMS_DONE,  // this is memory source for linearisation of data
		VDRUID_MME_MANAGER,						PARAMS_DONE,
		VDRUID_MME_MACRO_DECODER_PROCESSOR,	PARAMS_DONE,
		MAPPING_DONE,


	// MME based LPCM Frame Stream Decoder
	CREATE_UNIT (VDRUID_LPCM_FRAME_STREAM_DECODER, CreateMMELPCMFrameStreamDecoder),
					 DWORD_PARAM(TCTP_AUDIO_FRAME_STREAM_DECODER),		// Thread priority
					 DWORD_PARAM(TCSS_AUDIO_FRAME_STREAM_DECODER),		// Stack size
					 STRING_PARAM(TCTN_AUDIO_FRAME_STREAM_DECODER),		// Thread name
					 DWORD_PARAM(1),	// Number of frames after which a data packet is committed
					 DWORD_PARAM(8),	// allocated output frames
					 PARAMS_DONE,
		VDRUID_MME_LPCM_FRAME_DECODER,		PARAMS_DONE,
		MAPPING_DONE,


	// LPCM Stream Decoder (wrapper for analyzer + decoder)
#if 0
	CREATE_UNIT (VDRUID_LPCM_STREAM_DECODER, CreateAudioStreamDecoderUnit),
					 PARAMS_DONE,
		VDRUID_LPCM_FRAME_ANALYZER,				PARAMS_DONE,
		VDRUID_LPCM_FRAME_STREAM_DECODER,		PARAMS_DONE,
		VDRUID_LPCM_FRAME_STREAM_REPLICATOR,	PARAMS_DONE,
		MAPPING_DONE,
#else
	CREATE_UNIT (VDRUID_LPCM_STREAM_DECODER, CreateAudioStreamDecoderUnit),
					DWORD_PARAM(1),		// num inputs
					DWORD_PARAM(2),		// num of outputs

					// Analyzer
					DWORD_PARAM(0xff000000),	// Connect Chain, Out0 -> Unit0, In0
					DWORD_PARAM(0x00010200),	// Connect Unit0, Out0 -> Unit2, In0

					// Replicator
					DWORD_PARAM(0x02010100),	// Connect Unit2, Out1 -> Unit1, In0
					DWORD_PARAM(0x0202ff02),	// Connect Unit2, Out2 -> Chain, In1

					// Decoder
					DWORD_PARAM(0x0101ff01),	// Connect Unit1, Out0 -> Chain, In0

					PARAMS_DONE,
		VDRUID_LPCM_FRAME_ANALYZER,						PARAMS_DONE,
		VDRUID_LPCM_FRAME_STREAM_DECODER,				PARAMS_DONE,
		VDRUID_LPCM_FRAME_STREAM_REPLICATOR,			PARAMS_DONE,
		MAPPING_DONE,
#endif

	CREATE_UNIT (VDRUID_LPCM_FRAME_STREAM_REPLICATOR, CreateStreamReplicatorStreamingUnit),
				DWORD_PARAM(2),	// 1 stream -> 2 streams
				DWORD_PARAM(3),	// SRMFM_FORWARD_MAIN
				PARAMS_DONE,
		MAPPING_DONE,


	//
	// MPEG-2
	//

	// MPEG2AUDIO Audio Frame Analyzer (used to quantize source PCM data)
	CREATE_UNIT (VDRUID_MPEG2AUDIO_FRAME_ANALYZER, CreateMP2aFrameAnalyzer),
//					 DWORD_PARAM(8 * 300),				// Number of samples per Data Range that is sent 
//																// (must be multiple of 8 if GPFIFO transfer size is 8 cells)
					 PARAMS_DONE,
		MAPPING_DONE,

	// MME MPEG2AUDIO Frame Decoder (interface unit to MME)
		CREATE_UNIT (VDRUID_MME_MPEG2AUDIO_FRAME_DECODER, CreateMMEMP2aFrameDecoder),
					 DWORD_PARAM(4),						// Max number of frames to queue at MME
					 DWORD_PARAM(1152 + 1584),					// Max input frame size (from DVD spec, frame + extframe)
					 DWORD_PARAM(10 * 12 * 96 * 4),	// Max output frame size (PCM): 12 blocks of 10 channels, with 4 bytes per sample, 96 samples each
					 DWORD_PARAM(1),						// Want to Linearize i/p data before decoding
					 PARAMS_DONE,
		VDRUID_PLAYBACK_LINEAR_MEMORY_POOL,	PARAMS_DONE,
		VDRUID_MME_MANAGER,						PARAMS_DONE,
		VDRUID_MME_MACRO_DECODER_PROCESSOR,		PARAMS_DONE,
		MAPPING_DONE,


	// MME based MPEG2AUDIO Frame Stream Decoder
	CREATE_UNIT (VDRUID_MPEG2AUDIO_FRAME_STREAM_DECODER, CreateMMEMP2aFrameStreamDecoder),
					 DWORD_PARAM(TCTP_AUDIO_FRAME_STREAM_DECODER),		// Thread priority
					 DWORD_PARAM(TCSS_AUDIO_FRAME_STREAM_DECODER),		// Stack size
					 STRING_PARAM(TCTN_AUDIO_FRAME_STREAM_DECODER),		// Thread name
					 DWORD_PARAM(1),	// Number of frames after which a data packet is committed
					 DWORD_PARAM(8),	// allocated output frames
					 PARAMS_DONE,
		VDRUID_MME_MPEG2AUDIO_FRAME_DECODER,		PARAMS_DONE,
		MAPPING_DONE,


	// MPEG2AUDIO Stream Decoder (wrapper for analyzer + decoder)
#if DEBUG_DUMP_MP2A_STREAM_ANALYZER
		CREATE_UNIT (VDRUID_STREAMING_DEBUG_MP2a_1, CreateDumpingStreamingUnit),
					STRING_PARAM("c:\\MP2a"),
					PARAMS_DONE,
		MAPPING_DONE,
					 
	CREATE_UNIT (VDRUID_MPEG2AUDIO_STREAM_DECODER, CreateAudioStreamDecoderUnit),
					DWORD_PARAM(1),		// num inputs
					DWORD_PARAM(2),		// num of outputs

					// Analyzer
					DWORD_PARAM(0xff000000),	// Connect Chain, Out0 -> Unit0, In0

					DWORD_PARAM(0x00010300),	// Connect Unit0, Out0 -> Unit2, In0
					DWORD_PARAM(0x03010200),

					// Replicator
					DWORD_PARAM(0x02010100),	// Connect Unit2, Out1 -> Unit1, In0

					DWORD_PARAM(0x0202ff02),	// Connect Unit2, Out2 -> Chain, In1

					// Decoder
					DWORD_PARAM(0x0101ff01),	// Connect Unit1, Out0 -> Chain, In0

					PARAMS_DONE,
		VDRUID_MPEG2AUDIO_FRAME_ANALYZER,						PARAMS_DONE,
		VDRUID_MPEG2AUDIO_FRAME_STREAM_DECODER,				PARAMS_DONE,
		VDRUID_MPEG2AUDIO_FRAME_STREAM_REPLICATOR,			PARAMS_DONE,

		VDRUID_STREAMING_DEBUG_MP2a_1,					PARAMS_DONE,
		MAPPING_DONE,
#else
	CREATE_UNIT (VDRUID_MPEG2AUDIO_STREAM_DECODER, CreateAudioStreamDecoderUnit),
					DWORD_PARAM(1),		// num inputs
					DWORD_PARAM(2),		// num of outputs

					// Analyzer
					DWORD_PARAM(0xff000000),	// Connect Chain, Out0 -> Unit0, In0
					DWORD_PARAM(0x00010200),	// Connect Unit0, Out0 -> Unit2, In0

					// Replicator
					DWORD_PARAM(0x02010100),	// Connect Unit2, Out1 -> Unit1, In0
					DWORD_PARAM(0x0202ff02),	// Connect Unit2, Out2 -> Chain, In1

					// Decoder
					DWORD_PARAM(0x0101ff01),	// Connect Unit1, Out0 -> Chain, In0

					PARAMS_DONE,
		VDRUID_MPEG2AUDIO_FRAME_ANALYZER,						PARAMS_DONE,
		VDRUID_MPEG2AUDIO_FRAME_STREAM_DECODER,				PARAMS_DONE,
		VDRUID_MPEG2AUDIO_FRAME_STREAM_REPLICATOR,			PARAMS_DONE,
		MAPPING_DONE,
#endif

	CREATE_UNIT (VDRUID_MPEG2AUDIO_FRAME_STREAM_REPLICATOR, CreateStreamReplicatorStreamingUnit),
				DWORD_PARAM(2),	// 1 stream -> 2 streams
				DWORD_PARAM(3),	// SRMFM_FORWARD_MAIN
				PARAMS_DONE,
		MAPPING_DONE,


	//
	// DTS
	//
#if 0 /* DTS Disabled by Nico 16-04-2007 */

	// DTS Audio Frame Analyzer (used to quantize source PCM data)
	CREATE_UNIT (VDRUID_DTS_FRAME_ANALYZER, CreateDTSFrameAnalyzer),
			 PARAMS_DONE,
	   		MAPPING_DONE,

	// MME DTS Frame Decoder (interface unit to MME)
		CREATE_UNIT (VDRUID_MME_DTS_FRAME_DECODER, CreateMMEDTSFrameDecoder),
					 DWORD_PARAM(1),						// Max number of frames to queue at MME
					 DWORD_PARAM(16384),					// Max input frame size (syncword to syncword distance)
					 DWORD_PARAM(4*16*256*6),				// Max output frame size (PCM): 16 blocks of 6 channels, with 4 bytes per sample, 256 samples each
					 DWORD_PARAM(1),						// Want to Linearize i/p data before decoding
					 PARAMS_DONE,
		VDRUID_PLAYBACK_LINEAR_MEMORY_POOL,	PARAMS_DONE,
		VDRUID_MME_MANAGER,						PARAMS_DONE,
		VDRUID_MME_MACRO_DECODER_PROCESSOR,		PARAMS_DONE,
		MAPPING_DONE,


	// MME based DTS Frame Stream Decoder
	CREATE_UNIT (VDRUID_DTS_FRAME_STREAM_DECODER, CreateMMEDTSFrameStreamDecoder),
					 DWORD_PARAM(TCTP_AUDIO_FRAME_STREAM_DECODER),		// Thread priority
					 DWORD_PARAM(TCSS_AUDIO_FRAME_STREAM_DECODER),		// Stack size
					 STRING_PARAM(TCTN_AUDIO_FRAME_STREAM_DECODER),		// Thread name
					 DWORD_PARAM(1),	// Number of frames after which a data packet is committed
					 DWORD_PARAM(8),	// allocated output frames
					 PARAMS_DONE,
		VDRUID_MME_DTS_FRAME_DECODER,		PARAMS_DONE,
		MAPPING_DONE,

	// DTS Stream Decoder (wrapper for analyzer + decoder)
#if 0
	CREATE_UNIT (VDRUID_DTS_STREAM_DECODER, CreateAudioStreamDecoderUnit),
					 PARAMS_DONE,
		VDRUID_DTS_FRAME_ANALYZER,				PARAMS_DONE,
		VDRUID_DTS_FRAME_STREAM_DECODER,		PARAMS_DONE,
		VDRUID_DTS_FRAME_STREAM_REPLICATOR,	PARAMS_DONE,
		MAPPING_DONE,
#else
	CREATE_UNIT (VDRUID_DTS_STREAM_DECODER, CreateAudioStreamDecoderUnit),
					DWORD_PARAM(1),		// num inputs
					DWORD_PARAM(2),		// num of outputs

					// Analyzer
					DWORD_PARAM(0xff000000),	// Connect Chain, Out0 -> Unit0, In0
					DWORD_PARAM(0x00010200),	// Connect Unit0, Out0 -> Unit2, In0

					// Replicator
					DWORD_PARAM(0x02010100),	// Connect Unit2, Out1 -> Unit1, In0
					DWORD_PARAM(0x0202ff02),	// Connect Unit2, Out2 -> Chain, In1

					// Decoder
					DWORD_PARAM(0x0101ff01),	// Connect Unit1, Out0 -> Chain, In0

					PARAMS_DONE,
		VDRUID_DTS_FRAME_ANALYZER,						PARAMS_DONE,
		VDRUID_DTS_FRAME_STREAM_DECODER,				PARAMS_DONE,
		VDRUID_DTS_FRAME_STREAM_REPLICATOR,			PARAMS_DONE,
		MAPPING_DONE,
#endif

	CREATE_UNIT (VDRUID_DTS_FRAME_STREAM_REPLICATOR, CreateStreamReplicatorStreamingUnit),
				DWORD_PARAM(2),	// 1 stream -> 2 streams
				DWORD_PARAM(3),	// SRMFM_FORWARD_MAIN
				PARAMS_DONE,
		MAPPING_DONE,

#endif /* if 0 : DTS Disabled by Nico */

	//
	//CDDA
	//
	// CDDA Frame stream replicator
	CREATE_UNIT (VDRUID_CDDA_FRAME_STREAM_REPLICATOR, CreateStreamReplicatorStreamingUnit),
				DWORD_PARAM(2),	// 1 stream -> 2 streams
				DWORD_PARAM(3),	// SRMFM_FORWARD_MAIN
				PARAMS_DONE,
	MAPPING_DONE,

#if 0
	// CDDA Frame Splitter (used to quantize source PCM data and the subchannel)
	CREATE_UNIT (VDRUID_CDDA_SUBCH_FRAME_SPLITTER, CreateCDDASubChFrameSplitter),
					DWORD_PARAM(2300),	// Audio data Size per block
					DWORD_PARAM(100),	// Subchannel data size per block
					PARAMS_DONE,
	MAPPING_DONE,

	// CDDA Frame Splitter (used to quantize source PCM data and the subchannel)
	CREATE_UNIT (VDRUID_CDDA_AUDIO_FRAME_SPLITTER, CreateCDDAAudioFrameSplitter),
					DWORD_PARAM(0),	// Subchannel data Size per block
					DWORD_PARAM(2400),	// Audio data size per block
					PARAMS_DONE,
	MAPPING_DONE,
#else
	// CDDA Frame Splitter (used to quantize source PCM data and the subchannel)
	CREATE_UNIT (VDRUID_CDDA_AUDIO_FRAME_SPLITTER, CreateCDDASplitterUnit),
					DWORD_PARAM(0),	// Subchannel data Size per block
					DWORD_PARAM(1),	// Audio data size per block
					DWORD_PARAM(2352),
					DWORD_PARAM(0),
					PARAMS_DONE,
	MAPPING_DONE,

	// CDDA Frame Splitter (used to quantize source PCM data and the subchannel)
	CREATE_UNIT (VDRUID_CDDA_SUBCH_FRAME_SPLITTER, CreateCDDASplitterUnit),
					DWORD_PARAM(0),	// Audio data Size per block
					DWORD_PARAM(0),	// Subchannel data size per block
					DWORD_PARAM(2300),
					DWORD_PARAM(52),
					PARAMS_DONE,
	MAPPING_DONE,

#endif

	// MME MLP Frame Decoder (interface unit to MME)
	CREATE_UNIT (VDRUID_MME_CDDA_FRAME_DECODER, CreateMMECDDAFrameDecoder),
	// Use the LPCM MME Frame Decoder for decoding the CDDA Stuff
	//CREATE_UNIT (VDRUID_MME_CDDA_FRAME_DECODER, CreateMMELPCMFrameDecoder),
					DWORD_PARAM(4),						// Max number of frames to queue at MME
					DWORD_PARAM(2352),					// Max input frame size per block
					DWORD_PARAM(10*2400*2),				// Max output frame size (PCM): 588 samples ,4 bytes/channel and 10 channels
					DWORD_PARAM(1),						// Want to Linearize i/p data before decoding
					PARAMS_DONE,
	VDRUID_PLAYBACK_LINEAR_MEMORY_POOL,	PARAMS_DONE,
	VDRUID_MME_MANAGER,						PARAMS_DONE,
	VDRUID_MME_MACRO_DECODER_PROCESSOR,	PARAMS_DONE,
	MAPPING_DONE,

	// MME based CDDA Frame Stream Decoder
	CREATE_UNIT (VDRUID_CDDA_FRAME_STREAM_DECODER, CreateMMECDDAFrameStreamDecoder),
					DWORD_PARAM(TCTP_AUDIO_FRAME_STREAM_DECODER),		// Thread priority
					DWORD_PARAM(TCSS_AUDIO_FRAME_STREAM_DECODER),		// Stack size
					STRING_PARAM(TCTN_AUDIO_FRAME_STREAM_DECODER),		// Thread name
					DWORD_PARAM(1),	// Number of frames after which a data packet is committed
					DWORD_PARAM(8),	// allocated output frames
					PARAMS_DONE,
	VDRUID_MME_CDDA_FRAME_DECODER,		PARAMS_DONE,
	MAPPING_DONE,

	CREATE_UNIT (VDRUID_STREAMING_DEBUG_CDDA_1, CreateLoggingStreamingUnit),
					STRING_PARAM("CDDA_DEC_OUT"),
					PARAMS_DONE,
	MAPPING_DONE,

	CREATE_UNIT (VDRUID_STREAMING_DEBUG_CDDA_2, CreateLoggingStreamingUnit),
					STRING_PARAM("CDDA_DEC_IN"),
					PARAMS_DONE,
	MAPPING_DONE,

	// CDDA Stream Decoder (wrapper for analyzer + decoder) based on  GenericStreamingChainUnit
///
///				
///					,----------------------.
///					|				           +-> c1-subchannel
/// cdda-data-c0->+ CDDA Stream Decoder  |
///					|				           +-> c2-audio
///					`----------------------'
///
/// is composed of 
///
///
///				
///					,---------------------------------------------------.
///					|						   ,------------.						 |
///					|					   ,->+ S Splitter +---------------->+-> c1-subchannel
///					|	,----------.  /	`------------'						 |
///					|	|			  +-'												 |
/// cdda-data-c0->+->+Replicator|												 |
///					|	|			  +-.												 |
///					|	'----------'  \   ,------------.  ,-----------.  |
///					|						`->+ A Splitter +->+ A Decoder +->+-> c2-audio
///					|						   `------------'	 `-----------'	 |
///					`---------------------------------------------------'	
#if 0
	CREATE_UNIT (VDRUID_CDDA_STREAM_DECODER, CreateAudioStreamDecoderUnit),
					 DWORD_PARAM(1),		// num inputs
					 DWORD_PARAM(2),		// num of outputs

					 // CDDA REPLICATOR
					 DWORD_PARAM(0xff000000),	// Connect Chain, Out0 -> Unit0, In0
					 DWORD_PARAM(0x00010100),	// Connect Unit0, Out0 -> Unit1, In0
					 DWORD_PARAM(0x00020200),	// Connect Unit0, Out1 -> Unit2, In0

					 // S SPLITTER
					 DWORD_PARAM(0x0101ff02),	// Connect Unit1, Out0 -> Chain, In2

					 // A SPLITTER
					 DWORD_PARAM(0x02010400),	// Connect Unit2, Out0 -> Unit4, In0

					 // debug 1
					 DWORD_PARAM(0x04010300),	// Connect Unit4, Out0 -> Unit3, In0

					 // A SPLITTER
					 DWORD_PARAM(0x03010500),	// Connect Unit3, Out0 -> Unit5, In0

					 // A Decoder
					 DWORD_PARAM(0x0501ff01),	// Connect Unit5, Out0 -> Chain, In1

					 PARAMS_DONE,
	VDRUID_CDDA_FRAME_STREAM_REPLICATOR,	PARAMS_DONE,
	VDRUID_CDDA_SUBCH_FRAME_SPLITTER,		PARAMS_DONE,
	VDRUID_CDDA_AUDIO_FRAME_SPLITTER,		PARAMS_DONE,
	VDRUID_CDDA_FRAME_STREAM_DECODER,		PARAMS_DONE,
	VDRUID_STREAMING_DEBUG_CDDA_1,			PARAMS_DONE,
	VDRUID_STREAMING_DEBUG_CDDA_2,			PARAMS_DONE,
	MAPPING_DONE,

#else

	// CDDA Stream Decoder (wrapper for splitters + decoder)
	CREATE_UNIT (VDRUID_CDDA_STREAM_DECODER, CreateAudioStreamDecoderUnit),
					 DWORD_PARAM(1),		// num inputs
					 DWORD_PARAM(2),		// num of outputs

					 // CDDA REPLICATOR
					 DWORD_PARAM(0xff000000),	// Connect Chain, Out0 -> Unit0, In0
					 DWORD_PARAM(0x00010100),	// Connect Unit0, Out0 -> Unit1, In0
					 DWORD_PARAM(0x00020200),	// Connect Unit0, Out1 -> Unit2, In0

					 // S SPLITTER
					 DWORD_PARAM(0x0101ff02),	// Connect Unit1, Out0 -> Chain, In2

					 // A SPLITTER
					 DWORD_PARAM(0x02010300),	// Connect Unit2, Out0 -> Unit3, In0

					 // A SPLITTER
					 DWORD_PARAM(0x0301ff01),	// Connect Unit3, Out0 -> Chain, In1

					 PARAMS_DONE,
	VDRUID_CDDA_FRAME_STREAM_REPLICATOR,	PARAMS_DONE,
	VDRUID_CDDA_SUBCH_FRAME_SPLITTER,		PARAMS_DONE,
	VDRUID_CDDA_AUDIO_FRAME_SPLITTER,		PARAMS_DONE,
	VDRUID_CDDA_FRAME_STREAM_DECODER,		PARAMS_DONE,
	MAPPING_DONE,

#endif
	//
	// End CDDA
	//

	////////////////////////////////////////////////////////////////////////////
	// Octopus Architecture Audio Decoding Streaming Chains and Proxies
	////////////////////////////////////////////////////////////////////////////

//  Satej - Start
	// MLP Audio Frame Analyzer (used to quantize source PCM data)
	CREATE_UNIT (VDRUID_MLP_FRAME_ANALYZER, CreateMLPFrameAnalyzer),
			 PARAMS_DONE,
	   		MAPPING_DONE,

	// MME MLP Frame Decoder (interface unit to MME)
		CREATE_UNIT (VDRUID_MME_MLP_FRAME_DECODER, CreateMMEMLPFrameDecoder),
					 DWORD_PARAM(1),						// Max number of frames to queue at MME
					 DWORD_PARAM(13312),					// Max input frame size (syncword to syncword distance)
					 DWORD_PARAM(10*160*8*4),				// Max output frame size (PCM): 16 blocks of 6 channels, with 4 bytes per sample, 256 samples each
					 DWORD_PARAM(1),						// Want to Linearize i/p data before decoding
					 PARAMS_DONE,
		VDRUID_PLAYBACK_LINEAR_MEMORY_POOL,	PARAMS_DONE,
		VDRUID_MME_MANAGER,						PARAMS_DONE,
		VDRUID_MME_MACRO_DECODER_PROCESSOR,		PARAMS_DONE,
		MAPPING_DONE,


	// MME based MLP Frame Stream Decoder
	CREATE_UNIT (VDRUID_MLP_FRAME_STREAM_DECODER, CreateMMEMLPFrameStreamDecoder),
					 DWORD_PARAM(TCTP_AUDIO_FRAME_STREAM_DECODER),		// Thread priority
					 DWORD_PARAM(TCSS_AUDIO_FRAME_STREAM_DECODER),		// Stack size
					 STRING_PARAM(TCTN_AUDIO_FRAME_STREAM_DECODER),		// Thread name
					 DWORD_PARAM(1),	// Number of frames after which a data packet is committed
					 DWORD_PARAM(8),	// allocated output frames
					 PARAMS_DONE,
		VDRUID_MME_MLP_FRAME_DECODER,		PARAMS_DONE,
		MAPPING_DONE,


	// MLP Stream Decoder (wrapper for analyzer + decoder)
#if 0
	CREATE_UNIT (VDRUID_MLP_STREAM_DECODER, CreateAudioStreamDecoderUnit),
					 PARAMS_DONE,
		VDRUID_MLP_FRAME_ANALYZER,				PARAMS_DONE,
		VDRUID_MLP_FRAME_STREAM_DECODER,		PARAMS_DONE,
		VDRUID_MLP_FRAME_STREAM_REPLICATOR,	PARAMS_DONE,
		MAPPING_DONE,
#else
	CREATE_UNIT (VDRUID_MLP_STREAM_DECODER, CreateAudioStreamDecoderUnit),
					DWORD_PARAM(1),		// num inputs
					DWORD_PARAM(2),		// num of outputs

					// Analyzer
					DWORD_PARAM(0xff000000),	// Connect Chain, Out0 -> Unit0, In0
					DWORD_PARAM(0x00010200),	// Connect Unit0, Out0 -> Unit2, In0

					// Replicator
					DWORD_PARAM(0x02010100),	// Connect Unit2, Out1 -> Unit1, In0
					DWORD_PARAM(0x0202ff02),	// Connect Unit2, Out2 -> Chain, In1

					// Decoder
					DWORD_PARAM(0x0101ff01),	// Connect Unit1, Out0 -> Chain, In0

					PARAMS_DONE,
		VDRUID_MLP_FRAME_ANALYZER,						PARAMS_DONE,
		VDRUID_MLP_FRAME_STREAM_DECODER,				PARAMS_DONE,
		VDRUID_MLP_FRAME_STREAM_REPLICATOR,			PARAMS_DONE,
		MAPPING_DONE,
#endif

	CREATE_UNIT (VDRUID_MLP_FRAME_STREAM_REPLICATOR, CreateStreamReplicatorStreamingUnit),
				DWORD_PARAM(2),	// 1 stream -> 2 streams
				DWORD_PARAM(3),	// SRMFM_FORWARD_MAIN
				PARAMS_DONE,
		MAPPING_DONE,

// Satej - End

	// Streaming Proxy for Audio Player
	CREATE_UNIT (VDRUID_AUDIO_PLAYER_PROXY, CreateSingleStreamingProxyUnit),
					 PARAMS_DONE,
		VDRUID_MESSAGE_DISPATCHER,				PARAMS_DONE,
		VDRUID_AUDIO_PLAYER,						PARAMS_DONE,
		MAPPING_DONE,



#if DEBUG_AUDIO_STREAMING
	CREATE_UNIT (VDRUID_STREAMING_DEBUG_AUDIO_1, CreateLoggingStreamingUnit),
					STRING_PARAM("APIN"),
					PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_STREAMING_DEBUG_AUDIO_2, CreateLoggingStreamingUnit),
					STRING_PARAM("APD1"),
					PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_STREAMING_DEBUG_AUDIO_3, CreateLoggingStreamingUnit),
					STRING_PARAM("APD2"),
					PARAMS_DONE,
		MAPPING_DONE,

	// Instrumented Audio Player for debugging
	// Based on the Generic Streaming Chain Unit
	CREATE_UNIT (VDRUID_AUDIO_PLAYER, CreateGenericStreamingChainUnit),
					DWORD_PARAM(1),	// num inputs
					DWORD_PARAM(0),	// num outputs

					// Debug unit 1 (APIN)
					DWORD_PARAM(0xff000200),	// Chain, In0 -> Unit2, In0

					// Octopus Audio Decoder (Unit 0)
					DWORD_PARAM(0x02010000),	// Connect Unit2, Out0  -> Unit0, In0

					// Debug unit 2 (APD1)
					DWORD_PARAM(0x00010300),	// Connect Unit0, Out0 -> Unit3, In0
					DWORD_PARAM(0x03010100),	// Connect Unit3, Out0 -> Unit1, In0
					
					// Debug unit 3 (APD2)
					DWORD_PARAM(0x00020400),	// Connect Unit0, Out1 -> Unit4, In0
					DWORD_PARAM(0x04010101),	// Connect Unit3, Out0 -> Unit1, In1
									
					PARAMS_DONE,
		VDRUID_OCTOPUS_AUDIO_DECODER,					PARAMS_DONE,
		VDRUID_OCTOPUS_AUDIO_DECODE_RENDERER,		PARAMS_DONE,

		VDRUID_STREAMING_DEBUG_AUDIO_1,				PARAMS_DONE,
		VDRUID_STREAMING_DEBUG_AUDIO_2,				PARAMS_DONE,
		VDRUID_STREAMING_DEBUG_AUDIO_3,				PARAMS_DONE,

		MAPPING_DONE,

#elif TERMINATE_AUDIO_STREAMING
	CREATE_UNIT (VDRUID_AUDIO_PLAYER, CreateStreamingTerminator),
					 PARAMS_DONE,
		MAPPING_DONE,

#else // #if DEBUG_AUDIO_STREAMING

	// Audio Player
	// Based on the Generic Streaming Chain Unit
	CREATE_UNIT (VDRUID_AUDIO_PLAYER, CreateGenericStreamingChainUnit),
					DWORD_PARAM(1),	// num inputs
					DWORD_PARAM(0),	// num outputs

					// Octopus Audio Decoder (Unit 0)
					DWORD_PARAM(0xff000000),	// Connect Chain, In0  -> Unit0, In0

					// Octopus Audio Decode Renderer
					DWORD_PARAM(0x00010100),	// Connect Unit0, Out0 -> Unit1, In0
					DWORD_PARAM(0x00020101),	// Connect Unit0, Out1 -> Unit1, In1
					PARAMS_DONE,
		VDRUID_OCTOPUS_AUDIO_DECODER,					PARAMS_DONE,
		VDRUID_OCTOPUS_AUDIO_DECODE_RENDERER,		PARAMS_DONE,

		MAPPING_DONE,
#endif // #if DEBUG_AUDIO_STREAMING

	// 8k specific Audio Decoder
	CREATE_UNIT (VDRUID_OCTOPUS_AUDIO_DECODER, CreateOctopusAudioDecoder),
					 // Temporarily needed switch to control the memory pool allocator by Tags
					 DWORD_PARAM(1),	
					 PARAMS_DONE,
		VDRUID_AC3_STREAM_DECODER,				PARAMS_DONE,
		VDRUID_LPCM_STREAM_DECODER,			PARAMS_DONE,
// #if MPEG2AUDIO_INTEGRATED
		VDRUID_MPEG2AUDIO_STREAM_DECODER,	PARAMS_DONE,	
#if 0 /* DTS Disabled by Nico 16-04-2007 */
		VDRUID_DTS_STREAM_DECODER,	PARAMS_DONE,
#endif
		VDRUID_MLP_STREAM_DECODER,  PARAMS_DONE,
// #endif // MPEG2AUDIO_INTEGRATED
// Add the CDDA Decoder before the next comment
		VDRUID_CDDA_STREAM_DECODER,	PARAMS_DONE,
// end of Add the CDDA Decoder
		MAPPING_DONE,

	// Octopus Audio Decode Renderer
	// Based on the Generic Streaming Chain Unit
	CREATE_UNIT (VDRUID_OCTOPUS_AUDIO_DECODE_RENDERER, CreateGenericStreamingChainUnit),
					DWORD_PARAM(2),	// num inputs
					DWORD_PARAM(0),	// num outputs

					// PCM Mixer Input (Unit0)
					DWORD_PARAM(0x01010000),	// Connect Unit1, Out0 -> Unit0, In0

					// PCM Post Processor (Unit1)
					DWORD_PARAM(0xff000100),	// Connect Chain, In1 -> Unit1, In0

					// SPDIF Mixer Input (Unit2)
					DWORD_PARAM(0xff010200),	// Connect Chain, In0 -> Unit2, In0
					PARAMS_DONE,
		VDRUID_MAIN_MIXER_INPUT,				PARAMS_DONE,
		VDRUID_WIN32_PCM_POST_PROCESSOR,		PARAMS_DONE,
		VDRUID_MAIN_SPDIF_MIXER_INPUT,		PARAMS_DONE,
		MAPPING_DONE,


	////////////////////////////////////////////////////////////////////////////
	// Audio Mixer and Audio Rendering Chain
	////////////////////////////////////////////////////////////////////////////

#if TERMINATE_SPDIF_MIXER_INPUT
	CREATE_UNIT (VDRUID_MAIN_SPDIF_MIXER_INPUT, CreateStreamingTerminator),
					 PARAMS_DONE,
		MAPPING_DONE,
#else
	// Main SPDIF Mixer Input
	CREATE_UNIT (VDRUID_MAIN_SPDIF_MIXER_INPUT, CreateStreamMixerInput),
					 DWORD_PARAM(TCTP_SPDIF_STREAMMIXER_INPUT),		// Thread priority
					 DWORD_PARAM(TCSS_SPDIF_STREAMMIXER_INPUT),		// Stack size
					 STRING_PARAM(TCTN_SPDIF_STREAMMIXER_INPUT),		// Thread name
					 DWORD_PARAM(MIT_AUDIO_SPDIF),
					 PARAMS_DONE,
		VDRUID_SPDIF_STREAM_MIXER,				PARAMS_DONE,
		MAPPING_DONE,
#endif

	CREATE_UNIT (VDRUID_SPDIF_MIXER_OUTPUT, CreateStreamMixerOutput),
					 DWORD_PARAM(16),	// Size of data packet storage 
					 PARAMS_DONE,
		VDRUID_SPDIF_STREAM_MIXER,				PARAMS_DONE,
		MAPPING_DONE,

	// Main SPDIF Renderer Streaming Chain
	// Public proxy for the Standard SPDIF Player Chain
	CREATE_UNIT (VDRUID_STANDARD_SPDIF_PLAYER_PROXY, CreateSingleStreamingProxyUnit),
					 PARAMS_DONE,
		VDRUID_MESSAGE_DISPATCHER,				PARAMS_DONE,
		VDRUID_STANDARD_SPDIF_PLAYBACK,			PARAMS_DONE,
		MAPPING_DONE,


	CREATE_UNIT (VDRUID_STANDARD_SPDIF_PLAYBACK, CreateStandardSPDIFPlaybackUnit),
					 PARAMS_DONE,
		//VDRUID_AC3_FRAME_ANALYZER,				PARAMS_DONE,
		VDRUID_LPCM_FRAME_ANALYZER,			PARAMS_DONE,
		VDRUID_STANDARD_SPDIF_PLAYER,			PARAMS_DONE,
		MAPPING_DONE,

	// Standard SPDIF Player Streaming Chain Unit comprising of a formatter and a hardware SPDIF Player
	// ??? Replaced by StreamingTerminator as it is not yet working properly
	CREATE_UNIT (VDRUID_STANDARD_SPDIF_PLAYER, CreateStandardSPDIFPlayer),	//CreateStreamingTerminator),
					 PARAMS_DONE,
		VDRUID_8K_SPDIF_DATA_FORMATTER,		PARAMS_DONE,
		VDRUID_WIN32_MAIN_SPDIF_PLAYER,					PARAMS_DONE,
		MAPPING_DONE,


		// 8k specific SPDIF data formatter unit
	CREATE_UNIT (VDRUID_8K_SPDIF_DATA_FORMATTER, CreateSPDIFFormatterUnit),
					 PARAMS_DONE,
		VDRUID_PLAYBACK_LINEAR_MEMORY_POOL,			PARAMS_DONE,	// Memory Pool Allocator
		MAPPING_DONE,


	// Public SPDIF Mixer
	CREATE_UNIT (VDRUID_SPDIF_STREAM_MIXER, CreateStreamMixer),
					 DWORD_PARAM(TCTP_SPDIF_STREAMMIXER),		// Thread priority
					 DWORD_PARAM(TCSS_SPDIF_STREAMMIXER),		// Stack size
					 STRING_PARAM(TCTN_SPDIF_STREAMMIXER),		// Thread name
					 PARAMS_DONE,
		VDRUID_SPDIF_FRAME_MIXER,				PARAMS_DONE,
		MAPPING_DONE,

	// Specific SPDIF Frame Mixer
	CREATE_UNIT (VDRUID_SPDIF_FRAME_MIXER, CreateSPDIFFrameMixer),
					 PARAMS_DONE,
		MAPPING_DONE,


	CREATE_UNIT (VDRUID_MME_PCM_POST_PROCESSSOR, CreateMMEPCMPostProcessor),
					 PARAMS_DONE,
		MAPPING_DONE,

	// PCM Post Processor Control
	CREATE_UNIT (VDRUID_AUDIO_PCM_POST_PROCESSOR_CONTROL, CreatePCMPostProcessorControl),
					 PARAMS_DONE,
		VDRUID_MME_AUDIO_FRAME_MIXER,						PARAMS_DONE,	// post proc tags MUST go thru MME mixer
		MAPPING_DONE,

#if USE_AUX_AUDIO_INPUT
	// Mixer Input Control
	CREATE_UNIT (VDRUID_MIXER_INPUT_CONTROL_AUX, CreateStreamMixerInputControl),
					 PARAMS_DONE,
		VDRUID_AUX_MIXER_INPUT,					PARAMS_DONE,
		MAPPING_DONE,

	// Mixer Input Control Proxy
	CREATE_UNIT (VDRUID_AUDIO_MIXER_INPUT_CONTROL_AUX, CreateSingleStreamingProxyUnit),
					 PARAMS_DONE,
		VDRUID_MESSAGE_DISPATCHER, PARAMS_DONE,
		VDRUID_MIXER_INPUT_CONTROL_AUX, PARAMS_DONE,
		MAPPING_DONE,

	// "Aux" PCM Mixer Input
	CREATE_UNIT (VDRUID_AUX_MIXER_INPUT, CreateStreamMixerInput),
					 DWORD_PARAM(TCTP_AUDIO_STREAMMIXER_INPUT),		// Thread priority
					 DWORD_PARAM(TCSS_AUDIO_STREAMMIXER_INPUT),		// Stack size
					 STRING_PARAM(TCTN_AUDIO_STREAMMIXER_INPUT),		// Thread name
					 DWORD_PARAM(MIT_AUDIO_PCM),
					 DWORD_PARAM(1),											// Use allocator (useAllocator = 1), for use by synthesizer
					 DWORD_PARAM(2),											// base priority (should be higher than the default of 1 used by video)
					 DWORD_PARAM(0),											// trickmode priority (should be lower than the default of 1 used by video)
					 PARAMS_DONE,
		VDRUID_AUDIO_PCM_STREAM_MIXER,		PARAMS_DONE,
		MAPPING_DONE,

#endif


#if TERMINATE_AUDIO_MIXER_INPUT

	CREATE_UNIT (VDRUID_MAIN_MIXER_INPUT, CreateStreamingTerminator),
					 PARAMS_DONE,
		MAPPING_DONE,
#else
	// "Main" Mixer Input
	CREATE_UNIT (VDRUID_MAIN_MIXER_INPUT, CreateStreamMixerInput),
					 DWORD_PARAM(TCTP_AUDIO_STREAMMIXER_INPUT),		// Thread priority
					 DWORD_PARAM(TCSS_AUDIO_STREAMMIXER_INPUT),		// Stack size
					 STRING_PARAM(TCTN_AUDIO_STREAMMIXER_INPUT),		// thread name
					 DWORD_PARAM(MIT_AUDIO_PCM),
					 DWORD_PARAM(1),											// Use allocator (useAllocator = 1)
					 DWORD_PARAM(2),											// base priority 
					 DWORD_PARAM(0),											// trickmode priority
					 PARAMS_DONE,
		VDRUID_AUDIO_PCM_STREAM_MIXER,		PARAMS_DONE,
		MAPPING_DONE,
#endif


	// "Main" PCM Mixer Output
	CREATE_UNIT (VDRUID_MAIN_MIXER_OUTPUT, CreateStreamMixerOutput),
					 DWORD_PARAM(16),	// Size of data packet storage 
					 PARAMS_DONE,
		VDRUID_AUDIO_PCM_STREAM_MIXER,		PARAMS_DONE,
		MAPPING_DONE,

	// Public PCM Mixer
	CREATE_UNIT (VDRUID_AUDIO_PCM_STREAM_MIXER, CreateStreamMixer),
					 DWORD_PARAM(TCTP_AUDIO_STREAMMIXER),		// Thread priority
					 DWORD_PARAM(TCSS_AUDIO_STREAMMIXER),		// Stack size
					 STRING_PARAM(TCTN_AUDIO_STREAMMIXER),		// Thread name
					 PARAMS_DONE,
#if USE_MME_AUDIO_MIXER
		VDRUID_MME_AUDIO_FRAME_MIXER,		PARAMS_DONE,
#else
		VDRUID_AUDIO_FRAME_MIXER,		PARAMS_DONE,
#endif
		MAPPING_DONE,

	// Specific Simple PCM Frame Mixer
	CREATE_UNIT (VDRUID_AUDIO_FRAME_MIXER, CreateAudioFrameMixer),
					 PARAMS_DONE,
		VDRUID_PLAYBACK_LINEAR_MEMORY_POOL,	PARAMS_DONE,
		MAPPING_DONE,


			// Specific MME PCM Frame Mixer
	CREATE_UNIT (VDRUID_MME_AUDIO_FRAME_MIXER, CreateMMEAudioFrameMixer),
					 PARAMS_DONE,
		VDRUID_PLAYBACK_LINEAR_MEMORY_POOL,	PARAMS_DONE,
		VDRUID_MME_PCM_POST_PROCESSSOR,	PARAMS_DONE,
		VDRUID_MME_MANAGER, PARAMS_DONE,
		MAPPING_DONE,


	// For testing purposes - a WIN32 based PCM player
	CREATE_UNIT (VDRUID_WIN32_MAIN_PCM_PLAYER, CreateWIN32PCMPlayer),
					 DWORD_PARAM(32),		// msec len of buffer
					 DWORD_PARAM(6),		
					 DWORD_PARAM(TCTP_PCM_PLAYER),		// Thread priority
					 DWORD_PARAM(TCSS_PCM_PLAYER),		// Stack size
					 STRING_PARAM(TCTN_PCM_PLAYER),		// Thread name
					 PARAMS_DONE,
		VDRUID_PLAYBACK_LINEAR_MEMORY_POOL,	PARAMS_DONE,
		MAPPING_DONE,

	// For testing purposes - a WIN32 based SPDIF player
	CREATE_UNIT (VDRUID_WIN32_MAIN_SPDIF_PLAYER, CreateWIN32SPDIFPlayer),
					 DWORD_PARAM(32),		// msec len of buffer
					 DWORD_PARAM(6),		
					 DWORD_PARAM(TCTP_PCM_PLAYER),		// Thread priority
					 DWORD_PARAM(TCSS_PCM_PLAYER),		// Stack size
					 STRING_PARAM(TCTN_PCM_PLAYER),		// Thread name
					 PARAMS_DONE,
		VDRUID_PLAYBACK_LINEAR_MEMORY_POOL,	PARAMS_DONE,
		MAPPING_DONE,


#if USE_AUX_AUDIO_INPUT
	CREATE_UNIT (VDRUID_WAVE_GENERATOR, CreateAudioWaveGenerator),
					 PARAMS_DONE,
		MAPPING_DONE,
	CREATE_UNIT (VDRUID_GENERIC_AUDIO_SYNTH, CreateGenericStreamingChainUnit),
					DWORD_PARAM(0),	// num inputs
					DWORD_PARAM(0),	// num outputs

					// Connection between Wave Generator and Mixer Input
					DWORD_PARAM(0x00000100),	// Unit0, Out0 -> Unit1, In0
					PARAMS_DONE,
		VDRUID_WAVE_GENERATOR,					PARAMS_DONE,
		VDRUID_AUX_MIXER_INPUT,					PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_AUDIO_SYNTHESIZER, CreateSingleStreamingProxyUnit),
					 PARAMS_DONE,
		VDRUID_MESSAGE_DISPATCHER, PARAMS_DONE,
		VDRUID_GENERIC_AUDIO_SYNTH, PARAMS_DONE,
		MAPPING_DONE,
#endif
	// Streaming Proxy for Main PCM Renderer
	CREATE_UNIT (VDRUID_MAIN_PCM_RENDERER_PROXY, CreateSingleStreamingProxyUnit),
					 PARAMS_DONE,
		VDRUID_MESSAGE_DISPATCHER,				PARAMS_DONE,
		VDRUID_MAIN_PCM_RENDERER,				PARAMS_DONE,
		MAPPING_DONE,

	// Streaming Proxy for Combined Audio Renderer
	CREATE_UNIT (VDRUID_MAIN_AUDIO_RENDERER_PROXY, CreateSingleStreamingProxyUnit),
					 PARAMS_DONE,
		VDRUID_MESSAGE_DISPATCHER,				PARAMS_DONE,
		VDRUID_MAIN_AUDIO_RENDERER,				PARAMS_DONE,
		MAPPING_DONE,

#if TERMINATE_SPDIF_OUT
	CREATE_UNIT (VDRUID_MAIN_AUDIO_RENDERER, CreateGenericStreamingChainUnit),
					DWORD_PARAM(0),	// num inputs
					DWORD_PARAM(0),	// num outputs

					// PCM MAIN Mixer output (Unit 0) to PCM Player
					DWORD_PARAM(0x00000100),	// Connect Unit0, Out0  -> Unit1, In0					
					PARAMS_DONE,

		VDRUID_MAIN_MIXER_OUTPUT,				PARAMS_DONE,
		VDRUID_WIN32_MAIN_PCM_PLAYER,				PARAMS_DONE,
		MAPPING_DONE,
#else		// !TERMINATE_SPDIF_OUT
#if DEBUG_USE_NEW_COMBINED_AUDIO_RENDERER

	CREATE_UNIT (VDRUID_STREAMING_DEBUG_AUDIO_RENDERER_1, CreateLoggingStreamingUnit),
					STRING_PARAM("APCMIN"),
					PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_STREAMING_DEBUG_AUDIO_RENDERER_2, CreateLoggingStreamingUnit),
					STRING_PARAM("ASPDIFIN_PCM"),
					PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_STREAMING_DEBUG_AUDIO_RENDERER_3, CreateLoggingStreamingUnit),
					STRING_PARAM("ASPDIFIN_FRAME"),
					PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_MAIN_AUDIO_RENDERER, CreateGenericStreamingChainUnit),
					DWORD_PARAM(0),	// num inputs
					DWORD_PARAM(0),	// num outputs

					// MAIN Mixer output (Unit 0) to stream replicator
					DWORD_PARAM(0x00000100),	// Connect Unit0, Out0  -> Unit1, In0

					// Stream replicator to Debug unit 1 (APCMIN) & Debug unit 2 (ASPDIFIN)
					DWORD_PARAM(0x01010400),	// Connect Unit1, Out1 -> Unit4, In0
					DWORD_PARAM(0x01020500),	// Connect Unit1, Out2 -> Unit5, In0
					
					// Debug unit 1 (APCMIN) to PCM player
					DWORD_PARAM(0x04010200),	// Connect Unit4, Out1 -> Unit2, In0

					// Debug unit 2 (ASPDIFIN) to SPDIF player
					DWORD_PARAM(0x05010300),	// Connect Unit5, Out1 -> Unit3, In0
					DWORD_PARAM(0x06000700),	// Connect Unit5, Out1 -> Unit3, In0

					DWORD_PARAM(0x07010301),	// Connect Unit5, Out1 -> Unit3, In0
					PARAMS_DONE,

		VDRUID_MAIN_MIXER_OUTPUT,				PARAMS_DONE,
		VDRUID_AUDIO_RENDERER_FRAME_STREAM_REPLICATOR, PARAMS_DONE,
		VDRUID_WIN32_MAIN_PCM_PLAYER,				PARAMS_DONE,
		VDRUID_STANDARD_SPDIF_PLAYER,			PARAMS_DONE,
		VDRUID_STREAMING_DEBUG_AUDIO_RENDERER_1,PARAMS_DONE,
		VDRUID_STREAMING_DEBUG_AUDIO_RENDERER_2,PARAMS_DONE,
		VDRUID_SPDIF_MIXER_OUTPUT,				PARAMS_DONE,
		VDRUID_STREAMING_DEBUG_AUDIO_RENDERER_3, PARAMS_DONE,

		MAPPING_DONE,
#else
	CREATE_UNIT (VDRUID_MAIN_AUDIO_RENDERER, CreateGenericStreamingChainUnit),
					DWORD_PARAM(0),	// num inputs
					DWORD_PARAM(0),	// num outputs

					// PCM MAIN Mixer output (Unit 0) to stream replicator
					DWORD_PARAM(0x00000100),	// Connect Unit0, Out0  -> Unit1, In0

					// SPDIF Mixer output (Unit 0) to Standard SPDIF player 
					DWORD_PARAM(0x04000301),	// Connect Unit4, Out0  -> Unit3, In0

					// Stream replicator to PCM player & Standard SPDIf player
					DWORD_PARAM(0x01010200),	// Connect Unit1, Out1 -> Unit2, In0
					DWORD_PARAM(0x01020300),	// Connect Unit1, Out2 -> Unit3, In0
					
					PARAMS_DONE,

		VDRUID_MAIN_MIXER_OUTPUT,				PARAMS_DONE,
		VDRUID_AUDIO_RENDERER_FRAME_STREAM_REPLICATOR, PARAMS_DONE,
		VDRUID_WIN32_MAIN_PCM_PLAYER,				PARAMS_DONE,
		VDRUID_STANDARD_SPDIF_PLAYER,			PARAMS_DONE,
		VDRUID_SPDIF_MIXER_OUTPUT,				PARAMS_DONE,

		MAPPING_DONE,
#endif
#endif

	CREATE_UNIT (VDRUID_AUDIO_RENDERER_FRAME_STREAM_REPLICATOR, CreateStreamReplicatorStreamingUnit),
				DWORD_PARAM(2),	// 1 stream -> 2 streams TBD when SPDIF chain is able to take in PCM
				DWORD_PARAM(3),
				PARAMS_DONE,
		MAPPING_DONE,

	// Main (Multi Channel) PCM Renderer
	CREATE_UNIT (VDRUID_MAIN_PCM_RENDERER, CreateSTm8000PCMRenderer),
					 PARAMS_DONE,
		VDRUID_MAIN_MIXER_OUTPUT,				PARAMS_DONE,
		VDRUID_WIN32_MAIN_PCM_PLAYER,			PARAMS_DONE,
		MAPPING_DONE,


	////////////////////////////////////////////////////////////////////////////
	// VBI Engine Units
	////////////////////////////////////////////////////////////////////////////

#if 0 /* Disabled by Nico 16-04-2007 */
	CREATE_UNIT (VDRUID_VBI_DECODER_PROXY, CreateSingleStreamingProxyUnit),
					 PARAMS_DONE,
		VDRUID_MESSAGE_DISPATCHER, PARAMS_DONE,
		VDRUID_VBI_DECODER,			PARAMS_DONE,
		MAPPING_DONE,


	CREATE_UNIT (VDRUID_VBI_DECODER, CreateGenericStreamingChainUnit),
					DWORD_PARAM(1),	// num inputs
					DWORD_PARAM(5),	// num outputs

					// Line Parser (Unit 0)
					DWORD_PARAM(0xff000000),	// Connect Chain, In0  -> Unit0, In0
					DWORD_PARAM(0x00010100),	// Connect Unit0, Out0 -> Unit1, In0

					// Replicator (Unit 1)
					DWORD_PARAM(0x01010200),	// Connect Unit0, Out0 -> Unit2, In0
					DWORD_PARAM(0x01020300),	// Connect Unit0, Out1 -> Unit3, In0
					DWORD_PARAM(0x01030400),	// Connect Unit0, Out2 -> Unit4, In0
					DWORD_PARAM(0x01040500),	// Connect Unit0, Out3 -> Unit5, In0

					// CGMS decoder to CGMS replicator
					DWORD_PARAM(0x03010600),	// Connect Unit2, Out0 -> Unit5, In0

					// sub units  to chain
					DWORD_PARAM(0x0201ff01),	// Connect Unit2, Out0 -> chain, In0
					DWORD_PARAM(0x0401ff04),	// Connect Unit4, Out0 -> chain, In3
					DWORD_PARAM(0x0501ff05),	// Connect Unit5, Out0 -> chain, In4
					DWORD_PARAM(0x0601ff02),	// Connect Unit6, Out0 -> chain, In1
					DWORD_PARAM(0x0602ff03),	// Connect Unit6, Out1 -> chain, In2

					PARAMS_DONE,

		VDRUID_VBI_LINE_PARSER,					PARAMS_DONE,
		VDRUID_VBI_REPLICATOR,					PARAMS_DONE,
		VDRUID_GEMSTAR_DECODER,					PARAMS_DONE,
		VDRUID_CGMS_DECODER,						PARAMS_DONE,
		VDRUID_TELETEXT_DECODER,				PARAMS_DONE,
		VDRUID_VPS_DECODER,						PARAMS_DONE,
		VDRUID_CGMS_REPLICATOR,					PARAMS_DONE,
		MAPPING_DONE,



	CREATE_UNIT (VDRUID_VBI_LINE_PARSER, CreatePhysicalLineParserUnit),
					 DWORD_PARAM(TCTP_VBI_LINEPARSER),		// Thread priority
					 DWORD_PARAM(TCSS_VBI_LINEPARSER),		// Stack size
					 PARAMS_DONE,
		MAPPING_DONE,


	CREATE_UNIT (VDRUID_VBI_REPLICATOR, CreateStreamReplicatorStreamingUnit),
				DWORD_PARAM(4),			// 4 output number of subunits - 2 (replicator)
				PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_GEMSTAR_DECODER, CreatePhysicalGemstarDecoderUnit),
					 PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_CGMS_DECODER, CreatePhysicalCGMSDecoderUnit),
					 PARAMS_DONE,
		MAPPING_DONE,

		CREATE_UNIT (VDRUID_CGMS_REPLICATOR, CreateStreamReplicatorStreamingUnit),
				DWORD_PARAM(2),			// 2 output  (replicator)
				PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_TELETEXT_DECODER, CreatePhysicalTeletextDecoderUnit),
					 PARAMS_DONE,
		VDRUID_RECORDING_LINEAR_MEMORY_POOL,            PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_VPS_DECODER, CreatePhysicalVPSDecoderUnit),
					 PARAMS_DONE,
		MAPPING_DONE,

#endif /* if 0 */

	////////////////////////////////////////////////////////////////////////////
	// Video Decoder Units
	////////////////////////////////////////////////////////////////////////////

	CREATE_UNIT (VDRUID_MPEG_VIDEO_DATA_HANDLER, CreateMPEGVideoDataHandler),
					 DWORD_PARAM(TCTP_MPEG_VIDEO_DATAHANDLER),		// Thread priority
					 DWORD_PARAM(TCSS_MPEG_VIDEO_DATAHANDLER),		// Stack size
					 STRING_PARAM(TCTN_MPEG_VIDEO_DATAHANDLER),		// Thread name
					 PARAMS_DONE,
		VDRUID_PLAYBACK_LINEAR_MEMORY_POOL,		PARAMS_DONE,
		VDRUID_DMA_AND_SCD_ENGINE,					PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_STRATEGIC_MPEG_VIDEO_DECODER, CreateStrategicMPEGVideoDecoder),
					 DWORD_PARAM(TCTP_MPEG_STRATEGIC_VIDEO_DECODER),		// Thread priority
					 DWORD_PARAM(TCSS_MPEG_STRATEGIC_VIDEO_DECODER),		// Stack size
					 STRING_PARAM(TCTN_MPEG_STRATEGIC_VIDEO_DECODER),		// Thread name
					 DWORD_PARAM(0x65400),			// luma framebuffer size	(standard 405kB)
					 DWORD_PARAM(0x32A00),			// chroma framebuffer size	(standard 202.5kB)
					 DWORD_PARAM(2),					// optional additional framebuffers to be locked in render queue
					 PARAMS_DONE,
		VDRUID_MPEG_VIDEO_HEADER_PARSER,			PARAMS_DONE,
		MAPPING_DONE,

#if DEBUG_VIDEO_DECODER_STREAMING

	CREATE_UNIT (VDRUID_STREAMING_DEBUG_1, CreateLoggingStreamingUnit),
					STRING_PARAM("								VDIN"),
					PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_STREAMING_DEBUG_2, CreateLoggingStreamingUnit),
					STRING_PARAM("																VDCON"),
					PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_STREAMING_DEBUG_3, CreateLoggingStreamingUnit),
					STRING_PARAM("																								VDOUT"),
					PARAMS_DONE,
		MAPPING_DONE,


	CREATE_UNIT (VDRUID_MPEG_VIDEO_DECODER, CreateGenericStreamingChainUnit),
				DWORD_PARAM(1),	// num inputs
				DWORD_PARAM(1),	// num outputs

				// chain connection
				DWORD_PARAM(0xff000200),// Connect Chain, Out(CID0) -> Unit0, In(CID0) com. video data      -> video data handler
				DWORD_PARAM(0x02010000),// Connect Chain, Out(CID0) -> Unit0, In(CID0) com. video data      -> video data handler
				DWORD_PARAM(0x01010400),// Connect Unit1, Out(CID1) -> Chain, In(CID1) strategic video dec. -> standard output to mixer input
				DWORD_PARAM(0x0401ff01),// Connect Unit1, Out(CID1) -> Chain, In(CID1) strategic video dec. -> standard output to mixer input

				// data handler -> strategic decoder
				DWORD_PARAM(0x00010300),// Connect Unit0, Out(CID1) -> Unit1, In(CID0)
				DWORD_PARAM(0x03010100),// Connect Unit0, Out(CID1) -> Unit1, In(CID0)

				PARAMS_DONE,
		VDRUID_MPEG_VIDEO_DATA_HANDLER,			PARAMS_DONE,
		VDRUID_STRATEGIC_MPEG_VIDEO_DECODER,	PARAMS_DONE,
		VDRUID_STREAMING_DEBUG_1,					PARAMS_DONE,
		VDRUID_STREAMING_DEBUG_2,					PARAMS_DONE,
		VDRUID_STREAMING_DEBUG_3,					PARAMS_DONE,
		MAPPING_DONE,

#else	// DEBUG_VIDEO_DECODER_STREAMING
	CREATE_UNIT (VDRUID_MPEG_VIDEO_DECODER, CreateGenericStreamingChainUnit),
				DWORD_PARAM(1),	// num inputs
				DWORD_PARAM(1),	// num outputs

				// chain connection
				DWORD_PARAM(0xff000000),// Connect Chain, Out(CID0) -> Unit0, In(CID0) com. video data      -> video data handler
				DWORD_PARAM(0x0101ff01),// Connect Unit1, Out(CID1) -> Chain, In(CID1) strategic video dec. -> standard output to mixer input

				// data handler -> strategic decoder
				DWORD_PARAM(0x00010100),// Connect Unit0, Out(CID1) -> Unit1, In(CID0)

				PARAMS_DONE,
		VDRUID_MPEG_VIDEO_DATA_HANDLER,			PARAMS_DONE,
		VDRUID_STRATEGIC_MPEG_VIDEO_DECODER,	PARAMS_DONE,
		MAPPING_DONE,
#endif // DEBUG_VIDEO_DECODER_STREAMING

#if TERMINATE_VIDEO_STREAMING
	CREATE_UNIT (VDRUID_PRIMARY_VIDEO_TRANSDUCER, CreateStreamingTerminator),
					 PARAMS_DONE,
		MAPPING_DONE,

#else 
	CREATE_UNIT (VDRUID_PRIMARY_VIDEO_TRANSDUCER, CreateGenericStreamingChainUnit),
				DWORD_PARAM(1),	// num inputs
				DWORD_PARAM(1),	// num outputs

				// chain connection
				DWORD_PARAM(0xff000000),// Connect Chain, Out(CID0) -> Unit0, In(CID0) com. video data -> video decoder

				// decoder -> mixer input
				DWORD_PARAM(0x00010100),// Connect Unit0, Out(CID1) -> Unit1, In(CID0) video decoder   -> mixer input

				PARAMS_DONE,
		VDRUID_MPEG_VIDEO_DECODER,					PARAMS_DONE,
		VDRUID_VIDEO_FRAME_MIXER_INPUT,			PARAMS_DONE,
		MAPPING_DONE,

#endif // #if TERMINATE_VIDEO_STREAMING

	CREATE_UNIT (VDRUID_DVD_VIDEO_FRAME_EXTRACTOR, CreateGenericStreamingChainUnit),
				DWORD_PARAM(1),	// num inputs
				DWORD_PARAM(1),	// num outputs

				// chain connection
				DWORD_PARAM(0xff000000),// Connect Chain, Out(CID0) -> Unit0, In(CID0) com. video data -> video splitter
				DWORD_PARAM(0x0201ff01),// Connect Unit2, Out(CID1) -> Chain, In(CID1) video decoder   -> video frame out

				// unit connection
				DWORD_PARAM(0x00010100),// Connect Unit0, Out(CID1) -> Unit1, In(CID0) video splitter  -> video unpacker
				DWORD_PARAM(0x01010200),// Connect Unit1, Out(CID1) -> Unit2, In(CID0) video unpacker  -> video decoder

				PARAMS_DONE,
		VDRUID_DVD_DEMUX_VIDEO_SPLITTER,			PARAMS_DONE,
		VDRUID_DVD_DEMUX_VIDEO_UNPACKER,			PARAMS_DONE,
		VDRUID_MPEG_VIDEO_DECODER,					PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_DVD_VIDEO_FRAME_EXTRACTOR_PROXY, CreateSingleStreamingProxyUnit),
					 PARAMS_DONE,
		VDRUID_MESSAGE_DISPATCHER,					PARAMS_DONE,
		VDRUID_DVD_VIDEO_FRAME_EXTRACTOR,		PARAMS_DONE,
		MAPPING_DONE,

	/*
	// PCM Mixer (Emulation for Win32)
	CREATE_UNIT (VDRUID_VIDEO_MIXER, CreateWIN32VideoFrameMixer),
					 PARAMS_DONE,
		VDRUID_MME_MANAGER,			PARAMS_DONE,
		MAPPING_DONE,
	*/

	CREATE_UNIT(VDRUID_JPEG_FRAME_EXTRACTOR, CreateGenericStreamingChainUnit),
					DWORD_PARAM(1), 
					DWORD_PARAM(1), 
					DWORD_PARAM(0xff000000), // SCUo-iJFSD
					DWORD_PARAM(0x00010100), // SCUo-iJFSDo-iSFX
					DWORD_PARAM(0x0101ff01), // SCUo-iJFSDo-iSFXo-iSCUO
					PARAMS_DONE, 
		VDRUID_JPEG_FRAME_STREAM_DECODER, PARAMS_DONE, 
		VDRUID_STILL_FRAME_SPECIALFX_UNIT, PARAMS_DONE, 
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_JPEG_FRAME_EXTRACTOR_PROXY, CreateSingleStreamingProxyUnit),
					 PARAMS_DONE,
		VDRUID_MESSAGE_DISPATCHER,					PARAMS_DONE,
		VDRUID_JPEG_FRAME_EXTRACTOR,	         PARAMS_DONE,
		MAPPING_DONE,

	////////////////////////////////////////////////////////////////////////////
	// Subpicture Units
	////////////////////////////////////////////////////////////////////////////	
	CREATE_UNIT (VDRUID_SUBPICTURE_DATA_HANDLER, CreateSubpictureDataHandler),
					 DWORD_PARAM(TCTP_MPEG_SUBPICTURE_DATAHANDLER),		// Thread priority
					 DWORD_PARAM(TCSS_MPEG_SUBPICTURE_DATAHANDLER),		// Stack size
					 STRING_PARAM(TCTN_MPEG_SUBPICTURE_DATAHANDLER),   // Thread name
					 PARAMS_DONE,
		VDRUID_SOFTWARE_DMA_ENGINE,				PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_STRATEGIC_SUBPICTURE_DECODER, CreateStrategicSubpictureDecoder),
					 DWORD_PARAM(TCTP_MPEG_STRATEGIC_SUBPICTURE_DECODER),		// Thread priority
					 DWORD_PARAM(TCSS_MPEG_STRATEGIC_SUBPICTURE_DECODER),		// Stack size
					 STRING_PARAM(TCTN_MPEG_STRATEGIC_SUBPICTURE_DECODER),	// Thread name
					 DWORD_PARAM(8),	// Alpha value in LUT from subpicture not supported.
					 PARAMS_DONE,
		VDRUID_PLAYBACK_LINEAR_MEMORY_POOL,		PARAMS_DONE,
		VDRUID_PLAYBACK_LINEAR_MEMORY_POOL,		PARAMS_DONE,
		VDRUID_PLAYBACK_LINEAR_MEMORY_POOL,		PARAMS_DONE,
		VDRUID_PLAYBACK_LINEAR_MEMORY_POOL,		PARAMS_DONE,
		VDRUID_MME_MANAGER,							PARAMS_DONE,
		MAPPING_DONE,
#if 0
	CREATE_UNIT (VDRUID_SUBPICTURE_DECODER, CreateSubpictureDecoder),
					 PARAMS_DONE,
	   VDRUID_SUBPICTURE_DATA_HANDLER,			PARAMS_DONE,
		VDRUID_STRATEGIC_SUBPICTURE_DECODER,	PARAMS_DONE,
		MAPPING_DONE,
#else
	CREATE_UNIT (VDRUID_SUBPICTURE_DECODER, CreateGenericStreamingChainUnit),
				DWORD_PARAM(1),	// num inputs
				DWORD_PARAM(1),	// num outputs

				// chain connection
				DWORD_PARAM(0xff000000),// Connect Chain, Out(CID0) -> Unit0, In(CID0) com. subp. data   -> data handler
				DWORD_PARAM(0x0101ff01),// Connect Unit1, Out(CID1) -> Chain, In(CID1) strategic decoder -> mixer input

				// data handler -> strategic decoder
				DWORD_PARAM(0x00010100),// Connect Unit0, Out(CID1) -> Unit1, In(CID0)

				PARAMS_DONE,
	   VDRUID_SUBPICTURE_DATA_HANDLER,			PARAMS_DONE,
		VDRUID_STRATEGIC_SUBPICTURE_DECODER,	PARAMS_DONE,
		MAPPING_DONE,
#endif


#if USE_FAKE_SUBPICTURE_STREAMING || TERMINATE_VIDEO_STREAMING
	// For now, we have to fake the subpicture decoder as it is not yet properly generating the group/segment messages
	// So we terminate the chain here.
	CREATE_UNIT (VDRUID_SECONDARY_VIDEO_TRANSDUCER, CreateStreamingTerminator),
					 PARAMS_DONE,
		MAPPING_DONE,
#else	//USE_FAKE_SUBPICTURE_STREAMING
	CREATE_UNIT (VDRUID_SECONDARY_VIDEO_TRANSDUCER, CreateGenericStreamingChainUnit),
				DWORD_PARAM(1),	// num inputs
				DWORD_PARAM(0),	// num outputs

				// chain connection
				DWORD_PARAM(0xff000000),// Connect Chain, Out(CID0) -> Unit0, In(CID0) com. subp. data -> subp. decoder

				// decoder -> mixer input
				DWORD_PARAM(0x00010100),// Connect Unit0, Out(CID1) -> Unit1, In(CID0) subp. decoder   -> mixer input

				PARAMS_DONE,
		VDRUID_SUBPICTURE_DECODER,					PARAMS_DONE,
	   VDRUID_VIDEO_FRAME_MIXER_INPUT_1,		PARAMS_DONE,
		MAPPING_DONE,
#endif //USE_FAKE_SUBPICTURE_STREAMING

	////////////////////////////////////////////////////////////////////////
	// Video Display Units
	////////////////////////////////////////////////////////////////////////

#if TERMINATE_VIDEO_MIXER_INPUT
	CREATE_UNIT (VDRUID_VIDEO_FRAME_MIXER_INPUT, CreateStreamingTerminator),
					 PARAMS_DONE,
		MAPPING_DONE,
#else
	// "Main" Video Mixer Input
	CREATE_UNIT (VDRUID_VIDEO_FRAME_MIXER_INPUT, CreateStreamMixerInput),
					 DWORD_PARAM(TCTP_VIDEO_STREAMMIXER_INPUT),		// Thread priority
					 DWORD_PARAM(TCSS_VIDEO_STREAMMIXER_INPUT),		// Stack size
					 STRING_PARAM(TCTN_VIDEO_STREAMMIXER_INPUT),		// Thread name
					 DWORD_PARAM(MIT_VIDEO),
					 DWORD_PARAM(1),											// Provide allocator
					 PARAMS_DONE,
		VDRUID_VIDEO_MIXER,		PARAMS_DONE,
		MAPPING_DONE,
#endif


#if TERMINATE_SUBPIC_MIXER_INPUT
		// Additional Video Mixer Input (subpicture)
	CREATE_UNIT (VDRUID_VIDEO_FRAME_MIXER_INPUT_1, CreateStreamingTerminator),
					 PARAMS_DONE,
		MAPPING_DONE,
#else
		// Additional Video Mixer Input (subpicture)
	// Mixer Input Control for main video
	CREATE_UNIT (VDRUID_VIDEO_MIXER_INPUT_CONTROL_MAIN_INTERNAL, CreateStreamMixerInputControl),
					 PARAMS_DONE,
		VDRUID_VIDEO_FRAME_MIXER_INPUT,					PARAMS_DONE,
		MAPPING_DONE,

	// Mixer Input Control Proxy for main video
	CREATE_UNIT (VDRUID_VIDEO_MIXER_INPUT_CONTROL_MAIN, CreateSingleStreamingProxyUnit),
					 PARAMS_DONE,
		VDRUID_MESSAGE_DISPATCHER, PARAMS_DONE,
		VDRUID_VIDEO_MIXER_INPUT_CONTROL_MAIN_INTERNAL, PARAMS_DONE,
		MAPPING_DONE,

#endif


#if TERMINATE_SUBPIC_MIXER_INPUT
		// Additional Video Mixer Input (subpicture)
	CREATE_UNIT (VDRUID_VIDEO_FRAME_MIXER_INPUT_1, CreateStreamingTerminator),
					 PARAMS_DONE,
		MAPPING_DONE,
#else
		// Additional Video Mixer Input (subpicture)
	CREATE_UNIT (VDRUID_VIDEO_FRAME_MIXER_INPUT_1, CreateStreamMixerInput),
					 DWORD_PARAM(TCTP_VIDEO_STREAMMIXER_INPUT),		// Thread priority
					 DWORD_PARAM(TCSS_VIDEO_STREAMMIXER_INPUT),		// Stack size
					 STRING_PARAM(TCTN_VIDEO_STREAMMIXER_INPUT),		// Thread name
					 DWORD_PARAM(MIT_SUBPICTURE),
					 DWORD_PARAM(0),		// Don't use allocator (useAllocator = 0)
					 PARAMS_DONE,
		VDRUID_VIDEO_MIXER,		PARAMS_DONE,
		MAPPING_DONE,

	// Mixer Input Control for subpicture
	CREATE_UNIT (VDRUID_VIDEO_MIXER_INPUT_CONTROL_SUBPICTURE_INTERNAL, CreateStreamMixerInputControl),
					 PARAMS_DONE,
		VDRUID_VIDEO_FRAME_MIXER_INPUT_1,					PARAMS_DONE,
		MAPPING_DONE,

	// Mixer Input Control Proxy for subpicture
	CREATE_UNIT (VDRUID_VIDEO_MIXER_INPUT_CONTROL_SUBPICTURE, CreateSingleStreamingProxyUnit),
					 PARAMS_DONE,
		VDRUID_MESSAGE_DISPATCHER, PARAMS_DONE,
		VDRUID_VIDEO_MIXER_INPUT_CONTROL_SUBPICTURE_INTERNAL, PARAMS_DONE,
		MAPPING_DONE,

#endif
		

#if TERMINATE_OSD_MIXER_INPUT
	// Additional Video Mixer Input (OSD)
	CREATE_UNIT (VDRUID_VIDEO_FRAME_MIXER_INPUT_2, CreateStreamingTerminator),
					 PARAMS_DONE,
		MAPPING_DONE,

	// Additional Video Mixer Input (OSD - to be used by VideoTestPlayer)
	CREATE_UNIT (VDRUID_VIDEO_FRAME_MIXER_INPUT_3, CreateStreamingTerminator),
					 PARAMS_DONE,
		MAPPING_DONE,
#else
#endif
		

#if TERMINATE_OSD_MIXER_INPUT
	// Additional Video Mixer Input (OSD)
	CREATE_UNIT (VDRUID_VIDEO_FRAME_MIXER_INPUT_2, CreateStreamingTerminator),
					 PARAMS_DONE,
		MAPPING_DONE,
#else
	// Additional Video Mixer Input (OSD)
	CREATE_UNIT (VDRUID_VIDEO_FRAME_MIXER_INPUT_2, CreateStreamMixerInput),
					 DWORD_PARAM(TCTP_VIDEO_STREAMMIXER_INPUT),		// Thread priority
					 DWORD_PARAM(TCSS_VIDEO_STREAMMIXER_INPUT),		// Stack size
					 STRING_PARAM(TCTN_VIDEO_STREAMMIXER_INPUT),		// Thread name
					 DWORD_PARAM(MIT_OSD),
					 DWORD_PARAM(0),		// Don't use allocator (useAllocator = 0)
					 PARAMS_DONE,
		VDRUID_VIDEO_MIXER,		PARAMS_DONE,
		MAPPING_DONE,


	// Additional Video Mixer Input (OSD - to be used by VideoTestPlayer)
	CREATE_UNIT (VDRUID_VIDEO_FRAME_MIXER_INPUT_3, CreateStreamMixerInput),
					 DWORD_PARAM(TCTP_VIDEO_STREAMMIXER_INPUT),		// Thread priority
					 DWORD_PARAM(TCSS_VIDEO_STREAMMIXER_INPUT),		// Stack size
					 STRING_PARAM(TCTN_VIDEO_STREAMMIXER_INPUT),		// Thread name
					 DWORD_PARAM(MIT_OSD),
					 DWORD_PARAM(0),		// Don't use allocator (useAllocator = 0)
					 PARAMS_DONE,
		VDRUID_VIDEO_MIXER,		PARAMS_DONE,
		MAPPING_DONE,

	// Mixer Input Control for OSD
	CREATE_UNIT (VDRUID_VIDEO_MIXER_INPUT_CONTROL_OSD_INTERNAL, CreateStreamMixerInputControl),
					 PARAMS_DONE,
		VDRUID_VIDEO_FRAME_MIXER_INPUT_2,					PARAMS_DONE,
		MAPPING_DONE,

	// Mixer Input Control Proxy for OSD
	CREATE_UNIT (VDRUID_VIDEO_MIXER_INPUT_CONTROL_OSD, CreateSingleStreamingProxyUnit),
					 PARAMS_DONE,
		VDRUID_MESSAGE_DISPATCHER, PARAMS_DONE,
		VDRUID_VIDEO_MIXER_INPUT_CONTROL_OSD_INTERNAL, PARAMS_DONE,
		MAPPING_DONE,

#endif


	// Video Mixer output
	CREATE_UNIT (VDRUID_VIDEO_MIXER_OUTPUT, CreateStreamMixerOutput),
					 DWORD_PARAM(16),	// Size of data packet storage
					 PARAMS_DONE,
		VDRUID_VIDEO_MIXER,		PARAMS_DONE,
		MAPPING_DONE,

	// The video stream mixer
	CREATE_UNIT (VDRUID_VIDEO_MIXER, CreateStreamMixer),
					 DWORD_PARAM(TCTP_VIDEO_STREAMMIXER),		// Thread priority
					 DWORD_PARAM(TCSS_VIDEO_STREAMMIXER),		// Stack size
					 STRING_PARAM(TCTN_VIDEO_STREAMMIXER),		// Thread name
					 PARAMS_DONE,
		VDRUID_VIDEO_FRAME_MIXER,					PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_VIDEO_FRAME_MIXER, CreateWin32VideoFrameMixer),
#if TERMINATE_SUBPIC_MIXER_INPUT
#if TERMINATE_VIDEO_MIXER_INPUT || TERMINATE_OSD_MIXER_INPUT
					 DWORD_PARAM(1 + JPEG_MIXER_COUNT),	// number of inputs
#else
					 DWORD_PARAM(2 + JPEG_MIXER_COUNT),	// number of inputs
#endif // term video || osd
#else	 // no terminates
					 //4th input is the used by VideoTestPlayer
					 DWORD_PARAM(4 + JPEG_MIXER_COUNT),	// number of inputs
#endif
					 DWORD_PARAM(1),	// number of outputs
					 DWORD_PARAM(16),	// input queue length (in frames per input)
					 DWORD_PARAM(defaultDisplayVideoStandard), //Default video standard used by video display
					 DWORD_PARAM(VIDEO_OUTPUT_FORMAT),	// video output format
					 PARAMS_DONE,
		VDRUID_DEFERRED_VIDEO_BLITTER,						PARAMS_DONE,
		VDRUID_MIXER_CLUT_LINEAR_MEMORY_POOL,	PARAMS_DONE,
		VDRUID_BUTTON_HIGHLIGHT_PROCESSOR, PARAMS_DONE,
		VDRUID_PLAYBACK_LINEAR_MEMORY_POOL,	PARAMS_DONE, //Memory pool for allocators to be provided to upstream units
		MAPPING_DONE,

	CREATE_UNIT(VDRUID_DEFERRED_VIDEO_BLITTER, CreateDeferredBlitterUnit),
					 DWORD_PARAM(TCTP_VIDEO_BLITTER),   // thread priority
					 DWORD_PARAM(TCSS_VIDEO_BLITTER),   // thread stack size
					 STRING_PARAM(TCTN_VIDEO_BLITTER),  // thread name
					 DWORD_PARAM(8),					// blitter queue length
					 PARAMS_DONE,
		VDRUID_VIDEO_BLITTER, PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT(VDRUID_VIDEO_BLITTER, CreateWin32BlitterUnit),
					 PARAMS_DONE,
		VDRUID_WIN32_WINDOWCONTROL,				PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_BUTTON_HIGHLIGHT_PROCESSOR, CreateButtonHighlightProcessor),
					PARAMS_DONE,
		MAPPING_DONE,

	// The linear memory pool for themixer clut memory.
	CREATE_UNIT (VDRUID_MIXER_CLUT_LINEAR_MEMORY_POOL, CreateLinearMemoryPool),
					 PARAMS_DONE,
		VDRUID_PLAYBACK_MEMORY_PARTITION, PARAMS_DONE,
		VDRUID_MEMORY_MESSAGE_DISPATCHER, PARAMS_DONE,
		MAPPING_DONE,

	// Proxy unit for video renderer chain
	CREATE_UNIT(VDRUID_VIDEO_RENDERER_PROXY, CreateSingleStreamingProxyUnit),
					PARAMS_DONE,
		VDRUID_MESSAGE_DISPATCHER, PARAMS_DONE,
		VDRUID_VIDEO_DISPLAY, PARAMS_DONE,
		MAPPING_DONE,


	// Video renderer chain

	CREATE_UNIT (VDRUID_VIDEO_DISPLAY, CreateVideoDisplay),
					 PARAMS_DONE,
		VDRUID_VIDEO_MIXER_OUTPUT, PARAMS_DONE,
		VDRUID_VIDEO_RENDERER, PARAMS_DONE,
		VDRUID_VIDEO_OUTPUT, PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_VIDEO_RENDERER, CreateWin32VideoRenderer),
					 DWORD_PARAM(3), // No. of display buffers //	DWORD_PARAM(8), // chz 09_Jan_04 changing to 8 will allow smooth start up 
					 DWORD_PARAM(IRQ_DISP_0),
					 DWORD_PARAM(TCTP_VIDEORENDERER),		// Thread priority
					 DWORD_PARAM(TCSS_VIDEORENDERER),		// Stack size
//					 STRING_PARAM(TCTN_VIDEORENDERER),		// Thread name
					 DWORD_PARAM(VIDEO_OUTPUT_FORMAT),	// video output format
		 			 PARAMS_DONE,
		VDRUID_VIDEO_BLITTER, PARAMS_DONE,
		VDRUID_VSYNC_INTERRUPT, PARAMS_DONE,
		VDRUID_INTERRUPT_CONTROLLER,	PARAMS_DONE,		// This unit needs an interrupt controller to support the VSYNC interrupt
//		VDRUID_WIN32_RUNTIMECONFIGURATOR, PARAMS_DONE,
		MAPPING_DONE,


	CREATE_UNIT (VDRUID_VIDEO_OUTPUT, CreateGenericVideoOutput),
					 PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_GRAPHICS_2D, CreateGraphics2D),
					 DWORD_PARAM(4*1024*1024 + 824*1024),	//Size of memory pool for allocating bitmaps via IVDRGraphics2D::CreateBitmap
					 PARAMS_DONE,
		VDRUID_PLAYBACK_HEAP_MEMORY_POOL,	PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_GRAPHICS_2D_STREAM, CreateGraphics2DStream),
					 PARAMS_DONE,
		VDRUID_GRAPHICS_2D,						PARAMS_DONE,
		VDRUID_VIDEO_FRAME_MIXER_INPUT_2,	PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_GRAPHICS_2D_PROXY, CreateGraphics2DProxy),
					 PARAMS_DONE,
		VDRUID_MESSAGE_DISPATCHER, PARAMS_DONE,
		VDRUID_GRAPHICS_2D_STREAM, PARAMS_DONE,
		MAPPING_DONE,

	////////////////////////////////////////////////////////////////////////////
	// Video Engines
	////////////////////////////////////////////////////////////////////////////

	CREATE_UNIT (VDRUID_DMA_AND_SCD_ENGINE, CreateSoftwareDMAAndSCDEngine),
					 DWORD_PARAM(1),	// enable single callback after list transfer
					 PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_MPEG_VIDEO_HEADER_PARSER, CreateMPEGVideoHeaderParserEngine),
					 PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_SOFTWARE_DMA_ENGINE, CreateSoftwareDMAChannelEngine),
					 PARAMS_DONE,
		MAPPING_DONE,


	//////////////////////////////////////////////////////////////////////////
	// Video Player Units (for VideoDisplayTest only)
	//////////////////////////////////////////////////////////////////////////

	CREATE_UNIT (VDRUID_VIDEO_PLAYER, CreateVideoTestPlayer),
					 PARAMS_DONE,
		VDRUID_VIDEO_FRAME_MIXER_INPUT,		PARAMS_DONE,
		VDRUID_VIDEO_FRAME_MIXER_INPUT_1,	PARAMS_DONE,
		VDRUID_VIDEO_FRAME_MIXER_INPUT_3,	PARAMS_DONE,
		VDRUID_PLAYBACK_HEAP_MEMORY_POOL,	PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_VIDEO_PLAYER_PROXY, CreateSingleStreamingProxyUnit),
					 PARAMS_DONE,
		VDRUID_MESSAGE_DISPATCHER, PARAMS_DONE,
		VDRUID_VIDEO_PLAYER, PARAMS_DONE,
		MAPPING_DONE,


	////////////////////////////////////////////////////////////////////////////
	// Stream Units
	////////////////////////////////////////////////////////////////////////////

	//
	// the first 3 units created are using the initial single unit demux (outdated)
	//
	CREATE_UNIT (VDRUID_MPEG_DEMULTIPLEXER, CreateMPEGStreamDemultiplexer),
					 PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_PROGRAM_STREAM_TRANSDUCER, CreateGenericStreamingChainUnit),
				DWORD_PARAM(1),	// num inputs
				DWORD_PARAM(1),	// num outputs

				// chain connection
				DWORD_PARAM(0xff000000),// Connect Chain, Out(CID0) -> Unit0, In(CID0) com. data -> Demultiplexer
				DWORD_PARAM(0x0101ff01),// Connect Unit1, Out(CID1) -> Chain, In(CID1) Prim.Vid. -> frame-grab output 

				// Demultiplexer -> Transducer
				DWORD_PARAM(0x00010100),// Connect Unit0, Out(CID1) -> Unit1, In(CID0) Demux -> Prim.Vid.Transducer
				DWORD_PARAM(0x00020200),// Connect Unit0, Out(CID2) -> Unit2, In(CID0) Demux -> Audio Transducer
				DWORD_PARAM(0x00030300),// Connect Unit0, Out(CID3) -> Unit2, In(CID0) Demux -> Sec.Vid.Transducer

				PARAMS_DONE,
		VDRUID_MPEG_DEMULTIPLEXER,					PARAMS_DONE,
		VDRUID_PRIMARY_VIDEO_TRANSDUCER,			PARAMS_DONE,
		VDRUID_AUDIO_PLAYER,							PARAMS_DONE,
		VDRUID_SECONDARY_VIDEO_TRANSDUCER,		PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_PROGRAM_STREAM_TRANSDUCER_PROXY, CreateSingleStreamingProxyUnit),
					 PARAMS_DONE,
		VDRUID_MESSAGE_DISPATCHER,					PARAMS_DONE,
		VDRUID_PROGRAM_STREAM_TRANSDUCER,		PARAMS_DONE,
		MAPPING_DONE,


	//
	// Demultiplexed Transducer Proxy (DivX)
	//
	CREATE_UNIT (VDRUID_DEMULTIPLEXED_STREAM_DEMULTIPLEXER, CreateDemultiplexedStreamDemultiplexer),
					 PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_DEMULTIPLEXED_STREAM_TRANSDUCER, CreateDemultiplexedStreamTransducer),
					 PARAMS_DONE,
		VDRUID_DEMULTIPLEXED_STREAM_DEMULTIPLEXER,	PARAMS_DONE,
		VDRUID_PRIMARY_VIDEO_TRANSDUCER,			PARAMS_DONE,
		VDRUID_AUDIO_PLAYER,							PARAMS_DONE,
		VDRUID_SECONDARY_VIDEO_TRANSDUCER,		PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_DEMULTIPLEXED_STREAM_TRANSDUCER_PROXY, CreateSingleStreamingProxyUnit),
					 PARAMS_DONE,
		VDRUID_MESSAGE_DISPATCHER,					PARAMS_DONE,
		VDRUID_DEMULTIPLEXED_STREAM_TRANSDUCER,		PARAMS_DONE,
		MAPPING_DONE,

#if DEBUG_DEMULTIPLEXER_STREAMING
	CREATE_UNIT (VDRUID_STREAMING_DEBUG_1, CreateLoggingStreamingUnit),
					STRING_PARAM("RPIN"),
					PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_STREAMING_DEBUG_2, CreateLoggingStreamingUnit),
					STRING_PARAM("RPVI"),
					PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_STREAMING_DEBUG_3, CreateLoggingStreamingUnit),
					STRING_PARAM("RPAU"),
					PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_STREAMING_DEBUG_4, CreateLoggingStreamingUnit),
					STRING_PARAM("RPSP"),
					PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_STREAMING_DEBUG_5, CreateLoggingStreamingUnit),
					STRING_PARAM("RAU1"),
					PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_STREAMING_DEBUG_6, CreateLoggingStreamingUnit),
					STRING_PARAM("RVI1"),
					PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_STREAMING_DEBUG_7, CreateLoggingStreamingUnit),
					STRING_PARAM("RVI2"),
					PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_DVD_DEMULTIPLEXER, CreateGenericStreamingChainUnit),
					DWORD_PARAM(1),	// num inputs
					DWORD_PARAM(3),	// num outputs

					// DEBUG
					DWORD_PARAM(0xff000700),// Connect Chain, Out0 -> Unit7, In0
					DWORD_PARAM(0x0801ff01),// Connect Unit4, Out0 -> Chain, In0
					DWORD_PARAM(0x0901ff02),// Connect Unit5, Out0 -> Chain, In1
					DWORD_PARAM(0x0a01ff03),// Connect Unit6, Out0 -> Chain, In2

					// REPLICATOR
					DWORD_PARAM(0x07010000),// Connect Unit7, Out1 -> Unit0, In0					
					DWORD_PARAM(0x00010c00),// Connect Unit0, Out1 -> Unit1, In0
					DWORD_PARAM(0x0c010100),// Connect Unit0, Out1 -> Unit1, In0
					DWORD_PARAM(0x00020200),// Connect Unit0, Out2 -> Unit2, In0
					DWORD_PARAM(0x00030300),// Connect Unit0, Out3 -> Unit3, In0

					// SPLITTER to UNPACKER		
					DWORD_PARAM(0x01010d00),// Connect Unit1, Out0 -> Unit4, In0
					DWORD_PARAM(0x0d010400),
					DWORD_PARAM(0x02010b00),// Connect Unit2, Out0 -> Unit5, In0
					DWORD_PARAM(0x0b010500),
					DWORD_PARAM(0x03010600),// Connect Unit3, Out0 -> Unit6, In0

					// UNPACKER
					DWORD_PARAM(0x04010800),// Connect Unit4, Out0 -> Chain, In0
					DWORD_PARAM(0x05010900),// Connect Unit5, Out0 -> Chain, In1
					DWORD_PARAM(0x06010a00),// Connect Unit6, Out0 -> Chain, In2
					
					PARAMS_DONE,
		VDRUID_DVD_DEMUX_REPLICATOR,				PARAMS_DONE,
		VDRUID_DVD_DEMUX_VIDEO_SPLITTER,			PARAMS_DONE,
		VDRUID_DVD_DEMUX_AUDIO_SPLITTER,			PARAMS_DONE,
		VDRUID_DVD_DEMUX_SUBPICTURE_SPLITTER,	PARAMS_DONE,
		VDRUID_DVD_DEMUX_VIDEO_UNPACKER,			PARAMS_DONE,
		VDRUID_DVD_DEMUX_AUDIO_UNPACKER,			PARAMS_DONE,
		VDRUID_DVD_DEMUX_SUBPICTURE_UNPACKER,	PARAMS_DONE,

		VDRUID_STREAMING_DEBUG_1,					PARAMS_DONE,
		VDRUID_STREAMING_DEBUG_2,					PARAMS_DONE,
		VDRUID_STREAMING_DEBUG_3,					PARAMS_DONE,
		VDRUID_STREAMING_DEBUG_4,					PARAMS_DONE,
		VDRUID_STREAMING_DEBUG_5,					PARAMS_DONE,
		VDRUID_STREAMING_DEBUG_6,					PARAMS_DONE,
		VDRUID_STREAMING_DEBUG_7,					PARAMS_DONE,

		MAPPING_DONE,

	CREATE_UNIT (VDRUID_MPEGPROGRAM_DEMULTIPLEXER, CreateGenericStreamingChainUnit),
					DWORD_PARAM(1),	// num inputs
					DWORD_PARAM(3),	// num outputs

					// DEBUG
					DWORD_PARAM(0xff000700),// Connect Chain, Out0 -> Unit7, In0
					DWORD_PARAM(0x0801ff01),// Connect Unit4, Out0 -> Chain, In0
					DWORD_PARAM(0x0901ff02),// Connect Unit5, Out0 -> Chain, In1
					DWORD_PARAM(0x0a01ff03),// Connect Unit6, Out0 -> Chain, In2

					// REPLICATOR
					DWORD_PARAM(0x07010000),// Connect Unit7, Out1 -> Unit0, In0					
					DWORD_PARAM(0x00010c00),// Connect Unit0, Out1 -> Unit1, In0
					DWORD_PARAM(0x0c010100),// Connect Unit0, Out1 -> Unit1, In0
					DWORD_PARAM(0x00020200),// Connect Unit0, Out2 -> Unit2, In0
					DWORD_PARAM(0x00030300),// Connect Unit0, Out3 -> Unit3, In0

					// SPLITTER to UNPACKER		
					DWORD_PARAM(0x01010d00),// Connect Unit1, Out0 -> Unit4, In0
					DWORD_PARAM(0x0d010400),
					DWORD_PARAM(0x02010b00),// Connect Unit2, Out0 -> Unit5, In0
					DWORD_PARAM(0x0b010500),
					DWORD_PARAM(0x03010600),// Connect Unit3, Out0 -> Unit6, In0

					// UNPACKER
					DWORD_PARAM(0x04010800),// Connect Unit4, Out0 -> Chain, In0
					DWORD_PARAM(0x05010900),// Connect Unit5, Out0 -> Chain, In1
					DWORD_PARAM(0x06010a00),// Connect Unit6, Out0 -> Chain, In2
					
					PARAMS_DONE,
		VDRUID_MPEGPROGRAM_DEMUX_REPLICATOR,				PARAMS_DONE,
		VDRUID_MPEGPROGRAM_DEMUX_VIDEO_SPLITTER,			PARAMS_DONE,
		VDRUID_MPEGPROGRAM_DEMUX_AUDIO_SPLITTER,			PARAMS_DONE,
		VDRUID_MPEGPROGRAM_DEMUX_SUBPICTURE_SPLITTER,	PARAMS_DONE,
		VDRUID_MPEGPROGRAM_DEMUX_VIDEO_UNPACKER,			PARAMS_DONE,
		VDRUID_MPEGPROGRAM_DEMUX_AUDIO_UNPACKER,			PARAMS_DONE,
		VDRUID_MPEGPROGRAM_DEMUX_SUBPICTURE_UNPACKER,	PARAMS_DONE,

		VDRUID_STREAMING_DEBUG_1,					PARAMS_DONE,
		VDRUID_STREAMING_DEBUG_2,					PARAMS_DONE,
		VDRUID_STREAMING_DEBUG_3,					PARAMS_DONE,
		VDRUID_STREAMING_DEBUG_4,					PARAMS_DONE,
		VDRUID_STREAMING_DEBUG_5,					PARAMS_DONE,
		VDRUID_STREAMING_DEBUG_6,					PARAMS_DONE,
		VDRUID_STREAMING_DEBUG_7,					PARAMS_DONE,

		MAPPING_DONE,

#else // #if DEBUG_DEMULTIPLEXER_STREAMING
		/*
	CREATE_UNIT (VDRUID_DVD_DEMULTIPLEXER, CreateDVDStreamDemux),
					PARAMS_DONE,
		VDRUID_DVD_DEMUX_REPLICATOR,				PARAMS_DONE,
		VDRUID_DVD_DEMUX_VIDEO_SPLITTER,			PARAMS_DONE,
		VDRUID_DVD_DEMUX_AUDIO_SPLITTER,			PARAMS_DONE,
		VDRUID_DVD_DEMUX_SUBPICTURE_SPLITTER,	PARAMS_DONE,
		VDRUID_DVD_DEMUX_VIDEO_UNPACKER,			PARAMS_DONE,
		VDRUID_DVD_DEMUX_AUDIO_UNPACKER,			PARAMS_DONE,
		VDRUID_DVD_DEMUX_SUBPICTURE_UNPACKER,	PARAMS_DONE,
		MAPPING_DONE,		  
		*/

	CREATE_UNIT (VDRUID_DVD_DEMULTIPLEXER, CreateGenericStreamingChainUnit),
					DWORD_PARAM(1),	// num inputs
					DWORD_PARAM(3),	// num outputs

					// REPLICATOR
					DWORD_PARAM(0xff000000),// Connect Unit7, Out1 -> Unit0, In0					
					DWORD_PARAM(0x00010100),// Connect Unit0, Out1 -> Unit1, In0
					DWORD_PARAM(0x00020200),// Connect Unit0, Out2 -> Unit2, In0
					DWORD_PARAM(0x00030300),// Connect Unit0, Out3 -> Unit3, In0

					// SPLITTER to UNPACKER		
					DWORD_PARAM(0x01010400),// Connect Unit1, Out0 -> Unit4, In0
					DWORD_PARAM(0x02010500),// Connect Unit2, Out0 -> Unit5, In0
					DWORD_PARAM(0x03010600),// Connect Unit3, Out0 -> Unit6, In0

					// UNPACKER
					DWORD_PARAM(0x0401ff01),// Connect Unit4, Out0 -> Chain, In0
					DWORD_PARAM(0x0501ff02),// Connect Unit5, Out0 -> Chain, In1
					DWORD_PARAM(0x0601ff03),// Connect Unit6, Out0 -> Chain, In2
					
					PARAMS_DONE,
		VDRUID_DVD_DEMUX_REPLICATOR,				PARAMS_DONE,
		VDRUID_DVD_DEMUX_VIDEO_SPLITTER,			PARAMS_DONE,
		VDRUID_DVD_DEMUX_AUDIO_SPLITTER,			PARAMS_DONE,
		VDRUID_DVD_DEMUX_SUBPICTURE_SPLITTER,	PARAMS_DONE,
		VDRUID_DVD_DEMUX_VIDEO_UNPACKER,			PARAMS_DONE,
		VDRUID_DVD_DEMUX_AUDIO_UNPACKER,			PARAMS_DONE,
		VDRUID_DVD_DEMUX_SUBPICTURE_UNPACKER,	PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_MPEGPROGRAM_DEMULTIPLEXER, CreateGenericStreamingChainUnit),
					DWORD_PARAM(1),	// num inputs
					DWORD_PARAM(3),	// num outputs

					// REPLICATOR
					DWORD_PARAM(0xff000000),// Connect Unit7, Out1 -> Unit0, In0					
					DWORD_PARAM(0x00010100),// Connect Unit0, Out1 -> Unit1, In0
					DWORD_PARAM(0x00020200),// Connect Unit0, Out2 -> Unit2, In0
					DWORD_PARAM(0x00030300),// Connect Unit0, Out3 -> Unit3, In0

					// SPLITTER to UNPACKER		
					DWORD_PARAM(0x01010400),// Connect Unit1, Out0 -> Unit4, In0
					DWORD_PARAM(0x02010500),// Connect Unit2, Out0 -> Unit5, In0
					DWORD_PARAM(0x03010600),// Connect Unit3, Out0 -> Unit6, In0

					// UNPACKER
					DWORD_PARAM(0x0401ff01),// Connect Unit4, Out0 -> Chain, In0
					DWORD_PARAM(0x0501ff02),// Connect Unit5, Out0 -> Chain, In1
					DWORD_PARAM(0x0601ff03),// Connect Unit6, Out0 -> Chain, In2
					
					PARAMS_DONE,
		VDRUID_MPEGPROGRAM_DEMUX_REPLICATOR,				PARAMS_DONE,
		VDRUID_MPEGPROGRAM_DEMUX_VIDEO_SPLITTER,			PARAMS_DONE,
		VDRUID_MPEGPROGRAM_DEMUX_AUDIO_SPLITTER,			PARAMS_DONE,
		VDRUID_MPEGPROGRAM_DEMUX_SUBPICTURE_SPLITTER,	PARAMS_DONE,
		VDRUID_MPEGPROGRAM_DEMUX_VIDEO_UNPACKER,			PARAMS_DONE,
		VDRUID_MPEGPROGRAM_DEMUX_AUDIO_UNPACKER,			PARAMS_DONE,
		VDRUID_MPEGPROGRAM_DEMUX_SUBPICTURE_UNPACKER,	PARAMS_DONE,

		MAPPING_DONE,
#endif // #if DEBUG_DEMULTIPLEXER_STREAMING

	CREATE_UNIT (VDRUID_DVD_STREAM_TRANSDUCER, CreateGenericStreamingChainUnit),
				DWORD_PARAM(1),	// num inputs
				DWORD_PARAM(1),	// num outputs

				// chain connection
				DWORD_PARAM(0xff000000),// Connect Chain, Out(CID0) -> Unit0, In(CID0) com. data -> Demultiplexer
				DWORD_PARAM(0x0101ff01),// Connect Unit1, Out(CID1) -> Chain, In(CID1) Prim.Vid. -> frame-grab output 

				// Demultiplexer -> Transducer
				DWORD_PARAM(0x00010100),// Connect Unit0, Out(CID1) -> Unit1, In(CID0) Demux -> Prim.Vid.Transducer
				DWORD_PARAM(0x00020200),// Connect Unit0, Out(CID2) -> Unit2, In(CID0) Demux -> Audio Transducer
				DWORD_PARAM(0x00030300),// Connect Unit0, Out(CID3) -> Unit2, In(CID0) Demux -> Sec.Vid.Transducer

				PARAMS_DONE,
		VDRUID_DVD_DEMULTIPLEXER,					PARAMS_DONE,
		VDRUID_PRIMARY_VIDEO_TRANSDUCER,			PARAMS_DONE,
		VDRUID_AUDIO_PLAYER,							PARAMS_DONE,
		VDRUID_SECONDARY_VIDEO_TRANSDUCER,		PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_DVD_STREAM_TRANSDUCER_PROXY, CreateSingleStreamingProxyUnit),
					 PARAMS_DONE,
		VDRUID_MESSAGE_DISPATCHER,					PARAMS_DONE,
		VDRUID_DVD_STREAM_TRANSDUCER,				PARAMS_DONE,
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

	CREATE_UNIT (VDRUID_MPEGPROGRAM_STREAM_TRANSDUCER, CreateGenericStreamingChainUnit),
				DWORD_PARAM(1),	// num inputs
				DWORD_PARAM(1),	// num outputs

				// chain connection
				DWORD_PARAM(0xff000000),// Connect Chain, Out(CID0) -> Unit0, In(CID0) com. data -> Demultiplexer
				DWORD_PARAM(0x0101ff01),// Connect Unit1, Out(CID1) -> Chain, In(CID1) Prim.Vid. -> frame-grab output 

				// Demultiplexer -> Transducer
				DWORD_PARAM(0x00010100),// Connect Unit0, Out(CID1) -> Unit1, In(CID0) Demux -> Prim.Vid.Transducer
				DWORD_PARAM(0x00020200),// Connect Unit0, Out(CID2) -> Unit2, In(CID0) Demux -> Audio Transducer
				DWORD_PARAM(0x00030300),// Connect Unit0, Out(CID3) -> Unit2, In(CID0) Demux -> Sec.Vid.Transducer

				PARAMS_DONE,
		VDRUID_MPEGPROGRAM_DEMULTIPLEXER,		PARAMS_DONE,
		VDRUID_PRIMARY_VIDEO_TRANSDUCER,			PARAMS_DONE,
		VDRUID_AUDIO_PLAYER,							PARAMS_DONE,
		VDRUID_SECONDARY_VIDEO_TRANSDUCER,		PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_MPEG_PROGRAM_STREAM_TRANSDUCER_PROXY, CreateSingleStreamingProxyUnit),
					 PARAMS_DONE,
		VDRUID_MESSAGE_DISPATCHER,					PARAMS_DONE,
		VDRUID_MPEGPROGRAM_STREAM_TRANSDUCER,				PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_MPEGPROGRAM_DEMUX_REPLICATOR, CreateStreamReplicatorStreamingUnit),
				DWORD_PARAM(3),
				PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_MPEGPROGRAM_DEMUX_VIDEO_SPLITTER, CreateMPEGProgramStreamVideoSplitterUnit),
				PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_MPEGPROGRAM_DEMUX_AUDIO_SPLITTER, CreateMPEGProgramStreamAudioSplitterUnit),
				PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_MPEGPROGRAM_DEMUX_SUBPICTURE_SPLITTER, CreateMPEGProgramStreamSubpictureSplitterUnit),
				PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_MPEGPROGRAM_DEMUX_VIDEO_UNPACKER, CreateMPEGProgramStreamUnpackerUnit),
				DWORD_PARAM(16),
				PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_MPEGPROGRAM_DEMUX_AUDIO_UNPACKER, CreateMPEGProgramStreamUnpackerUnit),
				DWORD_PARAM(2),
				PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_MPEGPROGRAM_DEMUX_SUBPICTURE_UNPACKER, CreateMPEGProgramStreamUnpackerUnit),
				DWORD_PARAM(1),
				PARAMS_DONE,
		MAPPING_DONE,

	//ASV Demux Replicator - one input and 2 output for Video and Sub Pic
	CREATE_UNIT (VDRUID_ASV_DEMUX_REPLICATOR, CreateStreamReplicatorStreamingUnit),
				DWORD_PARAM(2),
				PARAMS_DONE,
		MAPPING_DONE,

	//ASV Demux - one input and two outputs for Video and SubPic
	CREATE_UNIT (VDRUID_ASV_DEMULTIPLEXER, CreateGenericStreamingChainUnit),
				DWORD_PARAM(1),	// num inputs
				DWORD_PARAM(2),	// num outputs

				// chain connection
				DWORD_PARAM(0xff000000),// Connect Chain, Out0 -> Unit0, In0 i/p -> Replicator Inp
				DWORD_PARAM(0x0301ff01),// Connect Unit3, Out0 -> Chain, V-Un    -> o/p video
				DWORD_PARAM(0x0401ff02),// Connect Unit4, Out0 -> Chain, Sp-Un   -> o/p SubPic

				// Replicator -> Splitter
				DWORD_PARAM(0x00010100),// Connect Unit0, Out1 -> Unit1, In0 Rep -> V-Spl
				DWORD_PARAM(0x00020200),// Connect Unit0, Out2 -> Unit2, In0 Rep -> Sp-Spl

				// Splitter -> Unpacker
				DWORD_PARAM(0x01010300),// Connect Unit1, Out0 -> Unit3, V-Spl  -> V-Un
				DWORD_PARAM(0x02010400),// Connect Unit2, Out0 -> Unit4, Sp-Spl -> Sp-Un
				PARAMS_DONE,

		VDRUID_ASV_DEMUX_REPLICATOR,				PARAMS_DONE,
		VDRUID_DVD_DEMUX_VIDEO_SPLITTER,			PARAMS_DONE,
		VDRUID_DVD_DEMUX_SUBPICTURE_SPLITTER,	PARAMS_DONE,
		VDRUID_DVD_DEMUX_VIDEO_UNPACKER,			PARAMS_DONE,
		VDRUID_DVD_DEMUX_SUBPICTURE_UNPACKER,	PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_ASV_TRANSDUCER, CreateGenericStreamingChainUnit),
				DWORD_PARAM(1),	// num inputs
				DWORD_PARAM(0),	// num outputs

				// ASV Demux (Unit 0)
				DWORD_PARAM(0xff000000),	// Connect Chain, In0  -> ASVDemux, Inp0

				// ASV Demux -> Video  chain (Unit 1)
				DWORD_PARAM(0x00010100),	// Connect Demux, Out0 -> Video Chain, In0

				// ASV Demux -> SubPic chain (Unit 2)
				DWORD_PARAM(0x00020200),	// Connect Demux, Out1 -> SubPic Chain, In0
				PARAMS_DONE,

		VDRUID_ASV_DEMULTIPLEXER,					PARAMS_DONE,
		VDRUID_PRIMARY_VIDEO_TRANSDUCER,			PARAMS_DONE,
		VDRUID_SECONDARY_VIDEO_TRANSDUCER,		PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_ASV_TRANSDUCER_PROXY, CreateSingleStreamingProxyUnit),
				PARAMS_DONE,

		VDRUID_MESSAGE_DISPATCHER,				PARAMS_DONE,
		VDRUID_ASV_TRANSDUCER,					PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_DVDAUDIO_DEMULTIPLEXER, CreateGenericStreamingChainUnit),
				DWORD_PARAM(1),	// num inputs
				DWORD_PARAM(1),	// num outputs - Future need to be Two when RTI support is added

				//No Replicator because only Audio chain is supported
				//Need to add the Replicator when we are supporting RTI
				//Audio Splitter + Audio Unpacker

				//chain connection
				DWORD_PARAM(0xff000000),// Connect Chain, Out0 -> Unit0, In0  i/p -> Au-Spl
				DWORD_PARAM(0x0101ff01),// Connect Unit1, Out0 -> Chain, In0 Au-Un -> o/p Audio chain

				// Splitter -> Unpacker
				DWORD_PARAM(0x00010100),// Connect Unit0, Out0 -> Unit1, In0 Au-Spl  -> Au-Un
				PARAMS_DONE,

		VDRUID_DVD_DEMUX_AUDIO_SPLITTER,			PARAMS_DONE,
		VDRUID_DVD_DEMUX_AUDIO_UNPACKER,			PARAMS_DONE,
		MAPPING_DONE,

		CREATE_UNIT (VDRUID_DVDAUDIO_STREAM_TRANSDUCER, CreateGenericStreamingChainUnit),
					DWORD_PARAM(1),	// num inputs
					DWORD_PARAM(0),	// num outputs

					// DVDAudio Demux (Unit 0)
					DWORD_PARAM(0xff000000),	// Connect Chain, In0  -> Demux, Inp0

					// DVDAudio Demux -> AudioPlayer
					DWORD_PARAM(0x00010100),	// Connect Demux, Out0 -> AudioPlayer, In0
					PARAMS_DONE,

		VDRUID_DVDAUDIO_DEMULTIPLEXER,	PARAMS_DONE,
		VDRUID_AUDIO_PLAYER,					PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_DVDAUDIO_STREAM_TRANSDUCER_PROXY, CreateSingleStreamingProxyUnit),
					 PARAMS_DONE,

		VDRUID_MESSAGE_DISPATCHER,				PARAMS_DONE,
		VDRUID_DVDAUDIO_STREAM_TRANSDUCER,			PARAMS_DONE,
		MAPPING_DONE,

	////////////////////////////////////////////////////////////////////////////
	// DV Capture units
	////////////////////////////////////////////////////////////////////////////

#if 0 /* Disabled by Nico 16-04-2007 */
	// DV Decoder streaming chain unit when streaming from hard disk

	CREATE_UNIT(VDRUID_WIN32_DV_DECODER, CreateWin32DVDecoder),
				DWORD_PARAM(TCTP_WIN32_DV_DECODER),		// Thread priority
				DWORD_PARAM(TCSS_WIN32_DV_DECODER),		// Stack size
				PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT(VDRUID_DV_AUDIO_DECODER, CreateDVAudioDecoder),
				DWORD_PARAM(TCTP_DV_AUDIO_DECODER),		// Thread priority
				DWORD_PARAM(TCSS_DV_AUDIO_DECODER),		// Stack size
				PARAMS_DONE,
		VDRUID_RECORDING_LINEAR_MEMORY_POOL,	PARAMS_DONE,
		VDRUID_WIN32_DV_AUDIO_DECODER,			PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT(VDRUID_WIN32_DV_AUDIO_DECODER, CreateWin32DVAudioTranscoder),
				PARAMS_DONE,
		MAPPING_DONE,


	////////////////////////////////////////////////////////////////////////////
	// DV Video Pre Processor units
	////////////////////////////////////////////////////////////////////////////

	CREATE_UNIT(VDRUID_DV_VIDEO_PREPROCESSOR_LINK_OUTPUT, CreateChainLinkOutput),
					 PARAMS_DONE,
		MAPPING_DONE,

#endif /* if 0 */

	////////////////////////////////////////////////////////////////////////////
	// Interrupt units
	////////////////////////////////////////////////////////////////////////////

	// VSYNC interrupt unit
	CREATE_UNIT(VDRUID_VSYNC_INTERRUPT, CreateInterruptUnit),
				DWORD_PARAM(IRQ_DISP_0),
				PARAMS_DONE,
		VDRUID_INTERRUPT_CONTROLLER, PARAMS_DONE,
		VDRUID_INTERRUPT_LEVEL_7, PARAMS_DONE,
		MAPPING_DONE, 

	CREATE_UNIT (VDRUID_INTERRUPT_CONTROLLER, CreateWin32InterruptController),
					 DWORD_PARAM(TCTP_WIN32_INTERRUPT_CONTROLLER),		// Thread priority
					 DWORD_PARAM(TCSS_WIN32_INTERRUPT_CONTROLLER),		// Stack size
					 PARAMS_DONE,
		MAPPING_DONE,

	//////////////////////////////////////////////////////////////////////////
	// Interrupt Levels
	//////////////////////////////////////////////////////////////////////////

	// Interrupt Unit for all necessary levels
	CREATE_UNIT(VDRUID_INTERRUPT_LEVEL_7, CreateInterruptLevel),
				DWORD_PARAM(IRQ_ILC_7),
				PARAMS_DONE,
		VDRUID_INTERRUPT_CONTROLLER, PARAMS_DONE,
		MAPPING_DONE, 

	
	CREATE_UNIT(VDRUID_INTERRUPT_LEVEL_6, CreateInterruptLevel),
				DWORD_PARAM(IRQ_ILC_6),
				PARAMS_DONE,
		VDRUID_INTERRUPT_CONTROLLER, PARAMS_DONE,
		MAPPING_DONE, 

	////////////////////////////////////////////////////////////////////////////
	// Support units for Win32
	////////////////////////////////////////////////////////////////////////////

	CREATE_UNIT (VDRUID_WIN32_APPLICATIONWINDOW, CreateWin32ApplicationWindowUnit),
					 DWORD_PARAM(TCTP_WIN32_APPLICATION_WINDOW),		// Thread priority
					 DWORD_PARAM(TCSS_WIN32_APPLICATION_WINDOW),		// Stack size
					 PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_WIN32_WINDOWCONTROL, CreateWin32WindowControlUnit),
					 PARAMS_DONE,
		VDRUID_WIN32_APPLICATIONWINDOW,			PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_WIN32_EVENTPROVIDER , CreateWin32EventMessageProviderUnit), 
					PARAMS_DONE, 
		VDRUID_WIN32_APPLICATIONWINDOW, PARAMS_DONE, 
		MAPPING_DONE, 

	CREATE_UNIT (VDRUID_DEFAULT_REMOTE_CONTROL, CreateWin32RemoteControlUnit), 
						DWORD_PARAM(sizeof(rcSt5911CodeTable)),
						POINTER_PARAM(&rcSt5911CodeTable),
					 PARAMS_DONE, 
		VDRUID_WIN32_EVENTPROVIDER, PARAMS_DONE, 
		VDRUID_MESSAGE_DISPATCHER, PARAMS_DONE, 
		MAPPING_DONE, 	

	/* CREATE_UNIT(VDRUID_WIN32REMOTE, CreateWin32RemoteControl), 
					   PARAMS_DONE, 
		MAPPING_DONE, */


	CREATE_UNIT( VDRUID_FRONT_PANEL_DISPLAY_PROXY, CreateFrontPanelDisplayProxy),
					 DWORD_PARAM(5), 
					 PARAMS_DONE, 
	   VDRUID_FRONT_PANEL_STRING_OPERATIONS, PARAMS_DONE,
		VDRUID_FRONT_PANEL_PIE_OPERATIONS, PARAMS_DONE,
		VDRUID_FRONT_PANEL_ICONCONTROL, PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT( VDRUID_FRONT_PANEL_STRING_OPERATIONS, CreateFrontPanelStringOperationsDecoder),
					 PARAMS_DONE, 
	   VDRUID_WIN32_FRONTPANEL, PARAMS_DONE, 
		MAPPING_DONE,

	CREATE_UNIT( VDRUID_FRONT_PANEL_PIE_OPERATIONS, CreateSpinningDiscOperationsDecoder),
					 PARAMS_DONE, 
	   VDRUID_WIN32_FRONTPANEL, PARAMS_DONE, 
		MAPPING_DONE,

	CREATE_UNIT( VDRUID_FRONT_PANEL_ICONCONTROL, CreateFrontPanelIconControlOperationsDecoder),
					 PARAMS_DONE, 
	   VDRUID_WIN32_FRONTPANEL, PARAMS_DONE, 
		MAPPING_DONE,
		
	CREATE_UNIT( VDRUID_WIN32_FRONTPANEL, CreateWin32FrontPanel), 
					 PARAMS_DONE,
		MAPPING_DONE,

	

		/*
	CREATE_UNIT (VDRUID_WIN32_RUNTIMECONFIGURATOR, CreateWin32GraphicalRuntimeConfigurator),
					 DWORD_PARAM(TCTP_WIN32_GRAPHICAL_RUNTIME_CONFIGURATOR),		// Thread priority
					 DWORD_PARAM(TCSS_WIN32_GRAPHICAL_RUNTIME_CONFIGURATOR),		// Stack size
					 PARAMS_DONE,
					 VDRUID_WIN32_WINDOWCONTROL, PARAMS_DONE,
					 VDRUID_WIN32_APPLICATIONWINDOW, PARAMS_DONE,
		MAPPING_DONE,
*/



		
////////////////////////////////////////////////////////////////////////////
// Still Frame Decoder Units
////////////////////////////////////////////////////////////////////////////


	CREATE_UNIT (VDRUID_STILL_FRAME_SPECIALFX_UNIT, CreateStillFrameSpecialFXUnit),
		DWORD_PARAM(2),									// how many additional frame buffers to use
		PARAMS_DONE,
		MAPPING_DONE,


	CREATE_UNIT (VDRUID_MME_JPEG_FRAME_DECODER, CreateMMEJPEGFrameDecoder),
					 DWORD_PARAM(1),					// How many output buffers to queue max
					 DWORD_PARAM(0xffffffff),		// Max input frame size  0xffffffff marks "multiple input buffer mode"
					 DWORD_PARAM(3 * 1024 * 1024),// Max output frame size 
					 DWORD_PARAM(0),					// Want to Linearize i/p data before decoding
					 DWORD_PARAM(8),					// How many input buffers max
					 DWORD_PARAM(1),					// How many scatters per input buffer max
					 PARAMS_DONE,
		VDRUID_MME_MANAGER,						   PARAMS_DONE,
		MAPPING_DONE,


	CREATE_UNIT (VDRUID_JPEG_FRAME_STREAM_DECODER, CreateJPEGFrameStreamDecoder),
					 DWORD_PARAM(TCTP_JPEG_FRAME_STREAM_DECODER),		// Thread priority
					 DWORD_PARAM(TCSS_JPEG_FRAME_STREAM_DECODER),		// Stack size
					 STRING_PARAM(TCTN_JPEG_FRAME_STREAM_DECODER),		// Thread name
					DWORD_PARAM(8),	// Number of frames after which to generate an output data packet
					DWORD_PARAM(1),	// allocated output frames
					PARAMS_DONE,
		VDRUID_MME_JPEG_FRAME_DECODER,	   	PARAMS_DONE,
		MAPPING_DONE,

		

	CREATE_UNIT (VDRUID_VIDEO_FRAME_MIXER_INPUT_5, CreateStreamMixerInput),
					 DWORD_PARAM(TCTP_VIDEO_STREAMMIXER_INPUT),		// Thread priority
					 DWORD_PARAM(TCSS_VIDEO_STREAMMIXER_INPUT),		// Stack size
					 STRING_PARAM(TCTN_VIDEO_STREAMMIXER_INPUT),		// Thread name
					 DWORD_PARAM(MIT_JPEG),
					 PARAMS_DONE,
		VDRUID_VIDEO_MIXER,		PARAMS_DONE,
		MAPPING_DONE,
			 
#if _JPEG_DEBUG_UNITS		 // JPEG decoder Streaming chain without Debuging Units at in/out
	CREATE_UNIT (VDRUID_STREAMING_JPEG_DEBUG_1, CreateLoggingStreamingUnit),
					STRING_PARAM("JPIN"),
					PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_STREAMING_JPEG_DEBUG_2, CreateLoggingStreamingUnit),
					STRING_PARAM("JPOU"),
					PARAMS_DONE,
		MAPPING_DONE,

	CREATE_UNIT (VDRUID_JPEG_STREAMING_CHAIN, CreateGenericStreamingChainUnit),
					DWORD_PARAM(1),	// num inputs
					DWORD_PARAM(0),	// num outputs
					// Chain Input to JPEG Frame Stream Decoder Input
					DWORD_PARAM(0xff000200),	// 
					DWORD_PARAM(0x02010000),	// 
					// JPEG Frame Stream Decoder Output to Still Frame FX unit
					DWORD_PARAM(0x00010300),	// 
					DWORD_PARAM(0x03010400),	// 
					// Still frame FX unit to Frame Mixer input
					DWORD_PARAM(0x04010100),
					PARAMS_DONE,
		VDRUID_JPEG_FRAME_STREAM_DECODER,		PARAMS_DONE,
		VDRUID_VIDEO_FRAME_MIXER_INPUT_5,		PARAMS_DONE,
		VDRUID_STREAMING_JPEG_DEBUG_1,			PARAMS_DONE,
		VDRUID_STREAMING_JPEG_DEBUG_2,			PARAMS_DONE,
		VDRUID_STILL_FRAME_SPECIALFX_UNIT,      PARAMS_DONE,
		MAPPING_DONE,

#else		 // JPEG decoder Streaming chain with Debuging Units at in/out
	CREATE_UNIT (VDRUID_JPEG_STREAMING_CHAIN, CreateGenericStreamingChainUnit),
					DWORD_PARAM(1),	// num inputs
					DWORD_PARAM(0),	// num outputs
					// Chain Input to JPEG Frame Stream Decoder Input
					DWORD_PARAM(0xff000000),	// Connect Chain, In0  -> Unit0, In0
					// JPEG Frame Stream Decoder Output to StillFrameSpecialFX input
					DWORD_PARAM(0x00010200),	// Connect Unit0, Out0 -> Unit1, In0
					//StillFrameSpecialFX output to Frame Mixer input
					DWORD_PARAM(0x02010100),
					PARAMS_DONE,
		VDRUID_JPEG_FRAME_STREAM_DECODER,		PARAMS_DONE,
		VDRUID_VIDEO_FRAME_MIXER_INPUT_5,		PARAMS_DONE,
		VDRUID_STILL_FRAME_SPECIALFX_UNIT,      PARAMS_DONE,
		MAPPING_DONE,
#endif

	CREATE_UNIT (VDRUID_JPEG_DECODER_PROXY, CreateSingleStreamingProxyUnit),
					PARAMS_DONE,
		VDRUID_MESSAGE_DISPATCHER,			PARAMS_DONE,
		VDRUID_JPEG_STREAMING_CHAIN,		PARAMS_DONE,
		MAPPING_DONE,



	UNITS_DONE
	};
