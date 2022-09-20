#include "MonitorMode.h"

#include <memory>
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
void MonitorMode::StartMonitor()
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
void MonitorMode::MessagesRead()
{
	uint32 messagesCount{};
	auto lMsg = std::make_unique<unmmko1_message>();
	assert (unmmko1_mon_messages_count(monitorSession, &messagesCount) > 0);
	/* read messages and store into vector */
	unmmko1_mon_messages_read(monitorSession, messagesCount, lMsg.get(), &messagesCount)
	< 0 ? MkoText("Error message read") : messages.push_back(std::move(lMsg));
}
void MonitorMode::ViewMessage()
{
	if (messages.empty()) MkoText("Error view message");

	for (const auto& msg : messages)
	{
		uint64_t timestamp = (static_cast<uint64_t>(msg->timestamp_high) << 32) +
				msg->timestamp_low;

	}
}
void MonitorMode::StopMonitor() const
{
	MkoValidation(__FUNCTION__, monitorSession, unmmko1_mon_stop(monitorSession));
}















