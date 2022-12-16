#include "MmkoModule.h"
#include "ControllerMode.h"

template <typename TContainer, typename TChannel, typename TObject>
static auto addController(TContainer& container, TChannel channel, MainBus* object) ->
	decltype (std::shared_ptr<ControllerMode>()){
	/*return container[channel] = std::shared_ptr<ControllerMode>
	        (new TObject(object, 0, BUSLINE::UNMMKO1_BUS_A, UNMMKO1_BC_DEFAULT));*/
	return [&](auto value) {

	};
}


int main(int argc, char* argv[]) {
	auto mkoModule = new MKOModule();

	delete mkoModule;

	return 0;
}