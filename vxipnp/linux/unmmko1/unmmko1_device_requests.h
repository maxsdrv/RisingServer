#ifndef UNMMKO1_DEVICE_REQUESTS_H
#define UNMMKO1_DEVICE_REQUESTS_H

#include "unmmko1.h"
#include "internal/unmmko1_device_data.h"

#ifndef MIN
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#endif

#ifndef MAX
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#endif

ViStatus set_current_mode(ViSession session, unmmko1_mode mode);
ViStatus get_current_mode(ViSession session, unmmko1_mode* mode);

ViStatus set_connection_type(ViSession session, unmmko1_connection_type type);
ViStatus get_connection_type(ViSession session, unmmko1_connection_type* type);

ViStatus get_current_timestamp(ViSession session, ViUInt64* timestamp);

ViStatus start_bc(ViSession session, ViUInt16 messages_index);
ViStatus stop_bc(ViSession session);
ViStatus set_bc_command(ViSession session, ViUInt16 command_index, unmmko1_command command, ViBoolean is_last, ViUInt16 next_command_index);
ViStatus start_bc_mon(ViSession session);
ViStatus transmit_bc_command(ViSession session, unmmko1_command command);

ViStatus start_rt(ViSession session, unmmko1_bus_usage bus_usage);
ViStatus stop_rt(ViSession session);
ViStatus turn_rt(ViSession session, ViUInt32 addresses_mask);
ViStatus build_rt(ViSession session, ViUInt32 addresses_mask, ViBoolean build_default_responses);
ViStatus set_status_word(ViSession session, ViUInt16 address, ViUInt16 status_word);
ViStatus set_rt_configuration(ViSession session, ViUInt16 address, ViBoolean on, ViUInt16 status_word, ViUInt16 vector_word, ViUInt16 selftest_word);
ViStatus get_rt_configuration(ViSession session, ViUInt16 address, ViBoolean* on, ViUInt16* status_word, ViUInt16* vector_word, ViUInt16* selftest_word);
ViStatus set_rt_data(ViSession session, ViUInt16 address, ViUInt16 subaddress, unmmko1_rt_subaddress_options options, ViUInt16 data_words_count, ViUInt32* packed_data_words);
ViStatus get_rt_data(ViSession session, ViUInt16 address, ViUInt16 subaddress, unmmko1_rt_subaddress_options* options, ViUInt16* data_words_count, ViUInt32* packed_data_words);
ViStatus update_rt_data(ViSession session, ViUInt16 address, ViUInt16 subaddress, ViUInt16 data_words_count, ViUInt16* data_words);

ViStatus start_mon(ViSession session, unmmko1_bus_usage bus_usage);
ViStatus stop_mon(ViSession session);

ViStatus self_test(ViSession session);

#endif // UNMMKO1_DEVICE_REQUESTS_H
