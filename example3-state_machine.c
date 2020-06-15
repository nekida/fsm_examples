#include "state_machine.h"

extern volatile bool flg_tx_rx_complete;
extern EVENT_t event;

void state_idle() {

}

void state_rqst_status() {
	if( get_crc16_modbus() )
		send_status();
	else
		send_answer(ERROR_CRC);
	
	event = EVENT_NONE;
}	

void state_echo() {
	send_echo();
	
	event = EVENT_NONE;
}

void state_information_command() {
	if( get_crc16_modbus() ) {
		flg_tx_rx_complete = false;
		send_answer(ERROR_NONE);
	} else
		send_answer(ERROR_CRC);
	
	event = EVENT_NONE;
}

void state_send_answer() {
	send_answer(ERROR_LEN);
	
	event = EVENT_NONE;
}

void state_check_answer() {
	if (check_arrays())
		send_answer(ERROR_NONE);
	else
		send_answer(ERROR_ANSWER);
	
	event = EVENT_NONE;
}
