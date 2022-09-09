#include "MkoErrors.h"

#include <utility>

MkoErrors::MkoErrors(std::string msg, int32_t status, std::string error_) :
					textMsg(std::move(msg)),
					mStatus(status),
					error(std::move(error_))
{

}
std::string MkoErrors::what()
{
	return textMsg + " " + std::to_string(mStatus) + " " + error;
}
