///
/// @purpose Example of VDR Startup Callbacks implementation
///

#include "VDR/Source/Startup/IStartup.h"
#include "STF/Interface/STFTimer.h"
#include "StreamingEngine.h"

// The app user overloads these global functions which are
// called back during the System Startup Process.
// If the Board Unit Construction process went OK,
// ContinueStartupCallback is called, which is the root
// for all further functionality of the system.
//
// In this particular example, we jump into the DemoApplication().


STFResult PreBoardConstructionCallback(void)
	{
	STFRES_RAISE_OK;
	}

STFResult ContinueStartupCallback(IVDRBase * boardInterface, int argc, char ** argv)
	{
	IVDRBase         *driver;
	//LinuxMediaCenter *DVDtestApp;
	StreamingEngine *DVDtestApp;

	// In a typical system, the following things are done here:
	// 1. Create Navigation Layer & File System
	// 2. Create Multimedia Layer
	// 3. Start UI Code

	// For testing purposes, we call a "Demo Application" here
	// Create an instance of the driver component, and get its interface
	STFRES_REASSERT(VDRCreateDriverInstance((char*)"STCM8k", 0, driver));

	DP("Creating DVD program stream transducer test application.\n");
	//DVDtestApp = new LinuxMediaCenter(driver);
	DVDtestApp = new StreamingEngine(driver);

	DP("DVDtestApp Initialize\n");
	STFRES_REASSERT(DVDtestApp->Initialize(argc, argv));

	DP("DVDtestApp TestStreaming\n");
	STFRES_REASSERT(DVDtestApp->TestStreaming());

	DP("DVDtestApp cleanup\n");
	STFRES_REASSERT(DVDtestApp->Cleanup());

	DP("Exit after cleanup\n");
	STFRES_RAISE_OK;
	}

void	BoardCreationFailureCallback(STFResult result)
	{
	// Do something with the result code... e.g. print on VFD
	}

extern void PreExitCallback(int & exitCode)
	{
	// Do something with the exit Code
	}

