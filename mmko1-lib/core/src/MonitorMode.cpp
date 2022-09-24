#include "MonitorMode.h"

#include <memory>
#include <algorithm>

#include "TestMmko.h"

MonitorMode::MonitorMode(TestMmko* objMko)
		: mMko(objMko),
		  monitorSession(Common::getInstance().session)
{
	monitorStatus = mMko->mkoStatus;
	try
	{
		StartMonitor();
	}
	catch(MkoErrors& ex)
	{
		std::cerr << ex.what();
		StopMonitor();
	}
}
void MonitorMode::StartMonitor() const
{
	int errMonitor = unmmko1_mon_configure(Common::getInstance().session, UNMMKO1_MON_TRANSFORM
			| UNMMKO1_MON_BUS_A_AND_B);
	if (errMonitor < 0)
	{
		auto errMsg = MkoErrors::ErrorMessage(Common::getInstance().session, &unmmko1_error_message);
		throw MkoErrors(__FUNCTION__ + std::get<0>(errMsg), std::get<1>(errMsg));
	}
	else
	{
		 MkoValidation(__FUNCTION__, monitorSession,
				 unmmko1_mon_start(monitorSession));
	}
}
bool MonitorMode::MessagesRead()
{
	uint32 messagesCount{};
	auto lMsg = std::make_unique<unmmko1_message>();
	if (unmmko1_mon_messages_count(monitorSession, &messagesCount) < 0)
		return false;
	/* read messages and store into vector */
	auto status = unmmko1_mon_messages_read(monitorSession, messagesCount, lMsg.get(), &messagesCount);
	if (status < 0)
		return false;
	else
		messages.push_back(std::move(lMsg));
	return true;
}
MonitorMode::MonitorMessage& MonitorMode::PullMessage()
{
	if (MessagesRead())
	{
		for (const auto& msg : messages)
		{
			monMessage.timestamp = (static_cast<uint64_t>(msg->timestamp_high) << 32) +
					msg->timestamp_low;
			if (msg->activity & UNMMKO1_MSG_ACT_CWD_1)
				monMessage.commandWord1 = msg->command.command_word_1;
			if (msg->activity & UNMMKO1_MSG_ACT_CWD_2)
				monMessage.commandWord2 = msg->command.command_word_2;

			if (0 != msg->command.data_words_count)
				monMessage.dataWordsCount = msg->command.data_words_count;

			std::copy(std::begin(msg->command.data_words), std::end(msg->command.data_words),
												   std::back_inserter(monMessage.dataWords));

		}
	}

}
void MonitorMode::StopMonitor() const
{
	MkoValidation(__FUNCTION__, monitorSession, unmmko1_mon_stop(monitorSession));
}















