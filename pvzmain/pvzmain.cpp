#include "../pvzclass/pvzclass.h"
#include "../pvzclass/include/Events/Events.h"

int main()
{
	DWORD pid = ProcessOpener::Open();
	if (!pid) return 1;
	PVZ::InitPVZ(pid);
	while (PVZ::GetPVZApp().GameState != PVZGameState::MainMenu) Sleep(10);
	PVZ::Memory::immediateExecute = true;
	PVZ::Memory::InjectDll("pvzdll.dll");
	PVZ::Memory::InvokeDllProc("init");
	EnableBackgroundRunning();
	DisableInitialLawnmower();
	DisableIceLevelFailSound();
	PVZEvent::FatalErrorEvent();
	PVZ::QuitPVZ();
	return 0;
}
