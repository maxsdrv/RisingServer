#include "AbonentMode.h"
#include "Mmko.h"

namespace
{
	const int maxSendWords = 32;
}

AbonentMode::AbonentMode(Mmko* mmko, uint32_t address) :
										objMmko(mmko),
										abonentAddr(address)
{
	abonentSession = Mmko::getMkoSession();
	auto errStatus = MkoValidation(__FUNCTION__, abonentSession,
			(unmmko1_rt_configure(abonentSession, abonentAddr, UNMMKO1_RT_TRANSFORM | UNMMKO1_RT_DEFAULT_RESPONSES)));
	if (errStatus < 0)
	{
		stopAbonent();
		throw MMKOErrors("Error config abonent", errStatus);
	}
	state = State::START;
}
void AbonentMode::setData(uint16_t subAddr, int dataWordsCount, std::vector<uint16_t> &dataWords) const
{
	if (dataWordsCount > maxSendWords)
		throw MMKOErrors("try to send data more than size of word in abonent mode ", maxSendWords);

	MkoValidation(__FUNCTION__, abonentSession,
				  unmmko1_rt_set_subaddress_data(abonentSession, abonentAddr,
												 subAddr, dataWordsCount, dataWords.data()));
}
void AbonentMode::setDataF5(uint16_t commandCode, uint16_t dataWord) const
{
	MkoValidation(__FUNCTION__, abonentSession,
			unmmko1_rt_set_command_data(abonentSession, abonentAddr,
					commandCode, dataWord));
}
AbonentMode::~AbonentMode()
{
	stopAbonent();
	MkoText("~AbonentMode()");
}
void AbonentMode::stopAbonent()
{
	MkoValidation(__FUNCTION__, abonentSession, unmmko1_rt_stop(abonentSession));
	state = State::STOP;
}
