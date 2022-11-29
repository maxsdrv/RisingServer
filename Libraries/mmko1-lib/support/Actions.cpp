#include "Actions.h"

namespace {
	const std::string search_pattern{"?*[0-9]?*::?*::INSTR"};
	const std::string idStr{"*IDN?\n"};
	const std::string tab{"%t"};
}

Common::Common()
		:
		status(VI_SUCCESS),
		position(0),
		session(0),
		resourceManagerSession(0), findList(0), index(0),
		count(0), deviceSession(0),
		carrierSession(0), interfaceType(0), mezzanineNumber(1)
{
}
Common::~Common()
{
	MkoText("~Common()");
}

int32_t Common::search()
{
	MkoText("Debug information about search MKO");
	/* Lambdas instead goto definitions in C implementation common.h */
	auto Error = [this]() {
	  if (resourceManagerSession)
		  viClose(resourceManagerSession);
	};
	auto CloseDevice = [this]() {
	  viClose(deviceSession);
	  if (VI_SUCCESS == found)
		  return;
	};

	//  Open Session with VISA
	if (viOpenDefaultRM(&resourceManagerSession) < 0)
		Error();

	// Find devices
	if (viFindRsrc(resourceManagerSession, const_cast<char*>(search_pattern.c_str()), &findList, &count, address)<0)
		Error();

	// Pass to all found devices
	for (index = 0; index<count; ++index) {
		// Devices not found
		if (index && viFindNext(findList, address)<0)
			Error();

		// Open device
		if (viOpen(resourceManagerSession, address, VI_NULL, VI_NULL, &deviceSession)<0)
			continue;

		// Read interface type
		viGetAttribute(deviceSession, VI_ATTR_INTF_TYPE, &interfaceType);

		// Interface type VXI или GPIB-VXI
		if (VI_INTF_VXI==interfaceType || VI_INTF_GPIB_VXI==interfaceType) {
			ViUInt32 slot_number = 0;
			ViUInt16 manufactory_id = 0, model_code = 0;

			// Don't work in slot number 0
			if (viGetAttribute(deviceSession, VI_ATTR_SLOT, &slot_number)<0 || 0==slot_number)
				CloseDevice();

			// Request the manufacturer's identifier and device model code
			if (viGetAttribute(deviceSession, VI_ATTR_MANF_ID, &manufactory_id)<0)
				CloseDevice();
			if (viGetAttribute(deviceSession, VI_ATTR_MODEL_CODE, &model_code)<0)
				CloseDevice();

			//Compare ID with ID any version Carriers Mezzanines
			if (UN_MANUFACTURER_ID!=manufactory_id)
				CloseDevice();

			model_code &= 0x0fff;
			if (UNMBASE_MODEL_CODE!=model_code && UNMBASEU_MODEL_CODE!=model_code
					&& UNMBASE_MODEL_ARMVXI!=model_code)
				CloseDevice();
		}
			//Interface type VXI or GPIB-VXI
		else if (VI_INTF_TCPIP==interfaceType || VI_INTF_USB==interfaceType || VI_INTF_GPIB==interfaceType
				|| VI_INTF_ASRL==interfaceType) {
			ViChar idn[256];

			if (viLock(deviceSession, VI_EXCLUSIVE_LOCK, 2000, nullptr, nullptr)<0)
				CloseDevice();

			status = viQueryf(deviceSession, const_cast<char*>(idStr.c_str()),
					const_cast<char*>(tab.c_str()), idn);
			viUnlock(deviceSession);

			if (status < 0)
				CloseDevice();

			if (0!=strncmp(idn, UNMBASE_MEZABOX_IDN, strlen(UNMBASE_MEZABOX_IDN)))
				CloseDevice();
		}

		// Initialise Carrier Mezzanine and read code of mezzanines
		if (unmbase_init(address, VI_ON, VI_ON, &carrierSession) < 0)
			CloseDevice();

		for (mezzanineNumber = 1; mezzanineNumber<=8; ++mezzanineNumber) {
			ViInt16 present, model_code;
			if (unmbase_m_type_q(carrierSession, mezzanineNumber, &present, &model_code)<0 || 0==present)
				continue;

			if (UNMMKO1_MODEL_CODE==(model_code & 0x0fff)) {
				strcpy(resourceName, address);
				position = (ViUInt16)mezzanineNumber;
				found = VI_SUCCESS;
				break;
			}
		}

		unmbase_close(carrierSession);

	}

	if (VI_SUCCESS == found)
		  printf("Mezzanine MKO found at %s on %d position\n", resourceName, position);
	status = found;

	return this->found;
}



