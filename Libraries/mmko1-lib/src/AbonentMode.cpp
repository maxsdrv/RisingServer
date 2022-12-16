#include "AbonentMode.h"
#include "MainBus.h"
#include "MMKOErrors.h"

namespace
{
	const int maxSendWords = 32;
}
AbonentMode::AbonentMode(MainBus* objectMmko, const uint32_t& address) :
										m_objectMmko(objectMmko),
										abonentSession(objectMmko->getMkoSession()),
										abonentStatus(objectMmko->getMkoStatus()),
										abonentAddr(address)
{
	/* TODO change arguments on rtOptions and test it */
	ThrowErrorIf(unmmko1_rt_configure(abonentSession, abonentAddr,
			UNMMKO1_RT_DEFAULT | UNMMKO1_RT_BUS_A_AND_B | UNMMKO1_RT_DEFAULT_RESPONSES) < 0,
					abonentSession, abonentStatus,FLAG::UNMMKO);

	StartAbonent();
}
void AbonentMode::setData(uint16_t subAddr, int dataWordsCount, std::vector<uint16_t> &dataWords) const
{
	if (dataWordsCount > maxSendWords) {
		std::cerr << "Try to send data more than size of word in abonent mode " << maxSendWords << '\n';
		StopAbonent();
		return;
	}
	ThrowErrorIf(unmmko1_rt_set_subaddress_data(abonentSession, abonentAddr,
			subAddr, dataWordsCount, dataWords.data()) < 0, abonentSession, abonentStatus,
					FLAG::UNMMKO);
}
void AbonentMode::setDataF5(uint16_t commandCode, uint16_t dataWord) const
{
	ThrowErrorIf(unmmko1_rt_set_command_data(abonentSession, abonentAddr, commandCode, dataWord) < 0,
			abonentSession, abonentStatus, FLAG::UNMMKO);
}
AbonentMode::~AbonentMode()
{
	StopAbonent();
}
void AbonentMode::StopAbonent() const
{
	unmmko1_rt_stop(abonentSession);
}
void AbonentMode::StartAbonent() const
{
	unmmko1_rt_start(abonentSession);
}
