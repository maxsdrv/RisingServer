#include "AbonentMode.h"
#include "Mmko.h"

namespace
{
	const int maxSendWords = 32;
}

AbonentMode::AbonentMode(Mmko* objectMmko, uint32_t address) :
										m_objectMmko(objectMmko),
										abonentSession(objectMmko->getMkoSession()),
										abonentStatus(objectMmko->getMkoStatus()),
										abonentAddr(address)
{
	ThrowErrorIf(unmmko1_rt_configure(abonentSession, abonentAddr,
			UNMMKO1_RT_TRANSFORM | UNMMKO1_RT_DEFAULT_RESPONSES) < 0, abonentSession, abonentStatus,
					ErDevices::UNMMKO);
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
					ErDevices::UNMMKO);
}
void AbonentMode::setDataF5(uint16_t commandCode, uint16_t dataWord) const
{
	ThrowErrorIf(unmmko1_rt_set_command_data(abonentSession, abonentAddr, commandCode, dataWord) < 0,
			abonentSession, abonentStatus, ErDevices::UNMMKO);
}
AbonentMode::~AbonentMode()
{
	StopAbonent();
	MkoText("~AbonentMode()");
}
void AbonentMode::StopAbonent() const
{
	unmmko1_rt_stop(abonentSession);
}
void AbonentMode::StartAbonent() const
{
	unmmko1_rt_start(abonentSession);
}
