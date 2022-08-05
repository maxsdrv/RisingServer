#pragma once

/* This class wrapper for function search_unmmko1 in common.h
 * it necessary because there was goto defines and is not convenient methods used to
 * old C code */

class SearchUnmmko {
public:
	SearchUnmmko(ViChar resource_name_[], ViUInt16* position_)
			:
			resource_name(resource_name_),
			position(position_)
	{
	}
private:
	ViChar* resource_name;
	ViUInt16* position;
public:
	ViSession resource_manager_session = 0;
	ViString search_pattern = "?*[0-9]?*::?*::INSTR";
	ViFindList find_list{};
	ViStatus found = VI_ERROR_RSRC_NFOUND;
	ViUInt32 index = 0, count = 0;
	ViSession device_session = 0, carrier_session = 0;
	ViUInt16 interface_type = 0;
	ViInt16 mezzanine_number = 1;
	ViChar address[256]{};

	int32_t search()
	{
		std::cout << "Debug information about calling method search" << '\n';

	/* Lambdas instead goto definitions in C implementation common.h */
		auto Error = [this](){
		  if (resource_manager_session)
			  viClose(resource_manager_session);

		  if (VI_SUCCESS == found)
			  printf("Mezzanine MKO found at %s on %d position\n", resource_name, *position);
		};
		auto CloseDevice = [this](){
		  viClose(device_session);
		  if (VI_SUCCESS == found)
			  return;
		};

		//  Open Session with VISA
		if (viOpenDefaultRM(&resource_manager_session)<0)
			Error();

		// Find devices
		if (viFindRsrc(resource_manager_session, search_pattern, &find_list, &count, address)<0)
			Error();

		// Pass to all found devices
		for (index = 0; index<count; ++index) {
			// Devices not found
			if (index && viFindNext(find_list, address)<0)
				Error();

			// Open device
			if (viOpen(resource_manager_session, address, VI_NULL, VI_NULL, &device_session)<0)
				continue;

			// Read interface type
			viGetAttribute(device_session, VI_ATTR_INTF_TYPE, &interface_type);

			// Interface type VXI или GPIB-VXI
			if (VI_INTF_VXI==interface_type || VI_INTF_GPIB_VXI==interface_type) {
				ViUInt32 slot_number = 0;
				ViUInt16 manufactory_id = 0, model_code = 0;

				// Don't work in slot number 0
				if (viGetAttribute(device_session, VI_ATTR_SLOT, &slot_number)<0 || 0==slot_number)
					CloseDevice();

				// Request the manufacturer's identifier and device model code
				if (viGetAttribute(device_session, VI_ATTR_MANF_ID, &manufactory_id)<0)
					CloseDevice();
				if (viGetAttribute(device_session, VI_ATTR_MODEL_CODE, &model_code)<0)
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
			else if (VI_INTF_TCPIP==interface_type || VI_INTF_USB==interface_type || VI_INTF_GPIB==interface_type
					|| VI_INTF_ASRL==interface_type) {
				ViChar idn[256];
				ViStatus status = VI_SUCCESS;

				if (viLock(device_session, VI_EXCLUSIVE_LOCK, 2000, 0, 0)<0)
					CloseDevice();

				status = viQueryf(device_session, "*IDN?\n", "%t", idn);
				viUnlock(device_session);

				if (status<0)
					CloseDevice();

				if (0!=strncmp(idn, UNMBASE_MEZABOX_IDN, strlen(UNMBASE_MEZABOX_IDN)))
					CloseDevice();
			}

			// Initialise Carrier Mezzanine and read code of mezzanines
			if (unmbase_init(address, VI_ON, VI_ON, &carrier_session)<0)
				CloseDevice();

			for (mezzanine_number = 1; mezzanine_number<=8; ++mezzanine_number) {
				ViInt16 present, model_code;
				if (unmbase_m_type_q(carrier_session, mezzanine_number, &present, &model_code)<0 || 0==present)
					continue;

				if (UNMMKO1_MODEL_CODE==(model_code & 0x0fff)) {
					strcpy(resource_name, address);
					*position = (ViUInt16)mezzanine_number;
					found = VI_SUCCESS;
					break;
				}
			}

			unmbase_close(carrier_session);

		}

		return this->found;
	}
};
