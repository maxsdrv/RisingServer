#include <iostream>

#include "MainBus.h"

void test()
{
	/* Example how to work Transmitting Message by MKO1 */
	uint16_t dataWords[5]{ 1, 2, 3, 4, 5 };
	auto test = std::make_unique<MainBus>(UNMMKO1_BUS_A);
}
/*
class Module {
public:
	Module() { std::cout << "Module created" << '\n'; }
};
class GeneralDevice {
public:
	virtual Module* CreateModule() = 0;
};
class ModuleFactory : public GeneralDevice {
public:
	Module* CreateModule() override {
		return new Module;
	}
};
class MmkoImp {
public:
	MmkoImp() {
		gD = new ModuleFactory;
		mD = gD->CreateModule();
	}
private:
	GeneralDevice* gD;
	Module* mD;
};
*/

int main(int argc, char* argv[])
{
	test();

	return 0;
}
















