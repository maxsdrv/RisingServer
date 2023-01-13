#include "AbonentMode.h"
#include "MainBus.h"
#include "MMKOErrors.h"

namespace
{
	constexpr int max_send_words = 32;
}
AbonentMode::AbonentMode(MainBus* object_mmko, BUSLINE bus_line, uint32_t address) :
		bus_line(bus_line),
		abonent_session(object_mmko->get_mko_session()),
		abonent_addr(address)
{
	unmmko1_rt_configure(abonent_session, abonent_addr,
			UNMMKO1_RT_DEFAULT | UNMMKO1_RT_BUS_A_AND_B | UNMMKO1_RT_DEFAULT_RESPONSES);
	/*try {
		abonent_status = MkoExceptions::check_functions("ABONENT_CONFIGURE",
				abonent_session, unmmko1_rt_configure, abonent_session, abonent_addr,
				UNMMKO1_RT_DEFAULT | UNMMKO1_RT_BUS_A_AND_B | UNMMKO1_RT_DEFAULT_RESPONSES);
	}
	catch(const MkoExceptions& ex) {
		std::cerr << ex.what();
	}*/
	std::cout << "AbonentMode()\n";
}
void AbonentMode::set_data(uint16_t sub_addr, int data_words_count, std::vector<uint16_t> &data_words) const
{
	if (data_words_count > max_send_words) {
		std::cerr << "Try to send data more than size of word in abonent mode " << max_send_words << '\n';
		stop_abonent();
		return;
	}
	/*ThrowErrorIf(unmmko1_rt_set_subaddress_data(abonent_session, abonent_addr,
			sub_addr, data_words_count, data_words.data()) < 0, abonent_session, abonent_status);*/
}
void AbonentMode::set_data_f5(uint16_t command_code, uint16_t data_word) const
{
	/*ThrowErrorIf(unmmko1_rt_set_command_data(abonent_session, abonent_addr, command_code, data_word) < 0,
			abonent_session, abonent_status);*/
}
AbonentMode::~AbonentMode()
{
	std::cout << "~AbonentMode()\n";
}
void AbonentMode::stop_abonent() const
{
	unmmko1_rt_stop(abonent_session);
}
void AbonentMode::start_abonent() const
{
	unmmko1_rt_start(abonent_session);
}
uint32_t AbonentMode::get_address() const {
	return abonent_addr;
}
