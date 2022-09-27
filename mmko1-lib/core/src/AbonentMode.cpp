#include "AbonentMode.h"
#include "MMKOInterface.h"
#include "defines.h"

AbonentMode::AbonentMode(MMKOInterface* mmko, int address) :
										objMmko(mmko),
										abonentAddr(address)
{
	abonentSession = MMKOInterface::getMkoSession();
	auto errStatus = MkoValidation(__FUNCTION__, abonentSession,
			(unmmko1_rt_configure(abonentSession, abonentAddr, UNMMKO1_RT_TRANSFORM | UNMMKO1_RT_DEFAULT_RESPONSES)));
	if (errStatus < 0)
		throw MMKOErrors("Error config abonent", errStatus);
}
