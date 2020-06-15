#include "state_machine.h"

extern uint8_t pc_uart_data_rx[37];
extern volatile bool flg_tx_rx_complete;
extern uint8_t ppm_spi_data_rx[32];
extern uint8_t ppm_spi_data_tx[32];
extern EVENT_t event;

void state_idle() {

}

void state_rqst_ppm_status() {
	if( (pc_uart_data_rx[2] | (pc_uart_data_rx[3] << 8) ) == get_crc16_modbus(pc_uart_data_rx, (LEN_MSG_REQUEST_STATUS_PPM_RX - 2)) )
		send_ppm_status();
	else
		send_answer(ERROR_CRC);
	
	event = EVENT_NONE;
}	

void state_echo() {
	send_echo();
	
	event = EVENT_NONE;
}

void state_information_command() {
	if( (pc_uart_data_rx[35] | (pc_uart_data_rx[36] << 8) ) == get_crc16_modbus(pc_uart_data_rx, (LEN_MSG_INFORMATION_RX - 2)) ) {
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

void state_check_answer_ppm() {
	if (ppm_check_tx_rx_arrays())
		send_answer(ERROR_NONE);
	else
		send_answer(ERROR_PPM_ANSWER);
	
	event = EVENT_NONE;
}
