///
///	@brief Definition of board specific memory map
///

#ifndef MEMORYMAP_H
#define MEMORYMAP_H

#define EMI_MEMORY_BASE						0x81000000
#define LMI_MEMORY_BASE						0x88000000
#define EMI_MEMORY_NON_CACHED_BASE			0xa1000000
#define LMI_MEMORY_NON_CACHED_BASE			0xa8000000

//
// NOTE: Please update the appropriate MemoryMap.doc and comments below if memory map changes
//

//
// This header file defines Media Data memory map, here defined with MEDIA_DATA_BASE and MEDIA_DATA_SIZE.
// It e.g. assumes following complete memory map:
//
//	Start			End			Size					Owner
//
//	0x80000000		0x807fffff		0x00800000	 8MB		Boot Flash
//	0x80800000		0x80ffffff		0x00800000	 8MB		Flash
//
//	0x81000000		0x817fffff		0x00800000	 8MB		Free
//	0x81800000		0x81ffffff		0x00800000	 8MB		LX0 EMI
//	0x82000000		0x827fffff		0x00800000	 8MB		LX1 EMI
//	0x82800000		0x82ffffff		0x00800000	 8MB		LX1 EMI
//
//	0x83000000		0x84ffffff		0x02000000	32MB		STEM SDRAM
//
//	0x85000000		0x86ffffff		0x02000000	32MB		ATAPI
//
//	0x87000000		0x87efffff		0x01000000	16MB		EPLD
//
//	0x88000000		0x8bffffff		0x04000000	64MB		LMI - see below:
//
//	0x88000000		0x8a5fffff		0x02500000	38MB		Media Data + ST40 Code (for details see below)
//	0x8a600000		0x8a7fffff		0x00200000	 2MB		EMBX LMI
//	0x8a800000		0x8affffff		0x00800000	 8MB		LX0 LMI
//	0x8b000000		0x8b7fffff		0x00800000	 8MB		LX1 LMI
//	0x8b800000		0x8bffffff		0x00800000	 8MB		LX2 LMI
//	0x8c000000		END + 1
//


////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Code base and size is all fake, cause in Linux User Space there are no Physical addresses.
//
// Therefore media data size is enlarged to be able to get some more memory allocated for tests
//
////////////////////////////////////////////////////////////////////////////////////////////////////////

#define PAL_DVD_VIDEO_FRAME_SIZE							((810*1024 + 32 - 1) & ~(32 - 1))
#define PAL_DVD_VIDEO_FRAME_NUMBER							3
#define PAL_DVD_VIDEO_MEMORY_ALIGNMENT_FACTOR_IN_BYTES		32
#define PAL_DVD_VIDEO_FRAME_BLOCK_SIZE						(810*1024)

#define MEDIA_DATA_BASE		0xa8000000
#define MEDIA_DATA_SIZE		0x02300000	// 35MB

#define CODE_BASE			0xaa300000
#define CODE_SIZE			0x00f00000	// 15MB - ST40 application code, heap and stack - address change: adapt board.mem
#define CCODE_BASE			(CODE_BASE & 0xdfffffff)	// cached address for memory overlap detector


///////////////////////////////////
//* MEMORYPARTITION_DRIVE_1
///////////////////////////////////

// The memory partition for the track buffer memory of drive 1.
#define MEMORYPARTITION_DRIVE_1_BASE		MEDIA_DATA_BASE
#define MEMORYPARTITION_DRIVE_1_SIZE		0x00000

///////////////////////////////////
//* MEMORYPARTITION_DRIVE_2
///////////////////////////////////

// The memory partition for the track buffer memory of drive 2
#define MEMORYPARTITION_DRIVE_2_BASE		(MEMORYPARTITION_DRIVE_1_BASE + MEMORYPARTITION_DRIVE_1_SIZE)
#define MEMORYPARTITION_DRIVE_2_SIZE		0x00000

//////////////////////////////////
//* PLAYBACK_MEMORY_PARTITION
//////////////////////////////////

#define PLAYBACK_MEMORY_PARTITION_BASE		(MEMORYPARTITION_DRIVE_2_BASE + MEMORYPARTITION_DRIVE_2_SIZE)
#define PLAYBACK_MEMORY_PARTITION_SIZE		(MEDIA_DATA_SIZE - MEMORYPARTITION_DRIVE_2_SIZE)	// takes what's left

#endif // MEMORYMAP_H

//<EOF>
