#include "MonitorMode.h"
#include "TestMmko.h"

MonitorMode::MonitorMode(TestMmko* objMko) : mMko(objMko),
					monSession(TestMmko::getMkoSession())
{
	try {
		if (mMko == nullptr) {
		MkoText("TestMmko obj = nullptr");
		throw std::bad_alloc();
	}
	}
	catch(const std::exception& ex) {
		std::cerr << ex.what();
		unmmko1_mon_stop(monSession);
	}
	StartMonitor();

}
int32 MonitorMode::StartMonitor()
{
	int errMonitor = unmmko1_mon_configure(monSession, UNMMKO1_MON_TRANSFORM
	| UNMMKO1_MON_BUS_A_AND_B);
	if (errMonitor < 0) {

	}
	return 0;
}

