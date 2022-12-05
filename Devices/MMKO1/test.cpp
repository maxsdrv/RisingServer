#include "MmkoModule.h"



int main(int argc, char* argv[]) {
	auto mkoModule = new MKOModule(BUSLINE::MKO_BUS_A);
	delete mkoModule;

	return 0;
}