#include "state_machine.h"

extern EVENT_t event;

void *state_idle() {
	if (event == EVENT_RQST_STATUS)
		return state_rqst_status;
	if (event == EVENT_INFORMATION_COMMAND)
		return state_information_command;
	if (event == EVENT_ECHO)
		return state_echo;
	if (event == EVENT_SEND_ANSWER)
		return state_send_answer;
	
	return state_idle;
}

void *state_rqst_ppm_status() {
	if (get_crc16_modbus() )
		send_status();
	else
		send_answer(ERROR_CRC);
	
	event = EVENT_NONE;
	return state_idle;
}	

void *state_echo() {
	send_echo();
	
	event = EVENT_NONE;
	return state_idle;
}

void *state_information_command() {
	if ( get_crc16_modbus() ) {
		send_answer(ERROR_NONE);
	} else
		send_answer(ERROR_CRC);
	
		return state_check_answer;
}

void *state_send_answer() {
	send_answer(ERROR_LEN);
	
	event = EVENT_NONE;
	return state_idle;
}

void *state_check_answer() {
	if (check_arrays())
		send_answer(ERROR_NONE);
	else
		send_answer(ERROR_ANSWER);
	
	event = EVENT_NONE;
	return state_idle;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	static volatile int8_t bytes_counter = 0;
	
	if (huart == &huart1) {
		pc_uart_data_rx[bytes_counter++] = rx_byte;
		if (pc_uart_data_rx[0] == ADDR) {
			if (bytes_counter == LEN_MSG_REQUEST) {
				event = EVENT_RQST_STATUS;
				bytes_counter = 0;
			} else if (bytes_counter == LEN_MSG_INFORMATION) {	
				event = EVENT_INFORMATION_COMMAND;
				bytes_counter = 0;
			} else if (bytes_counter == LEN_MSG_ECHO) {
				event = EVENT_ECHO;
				bytes_counter = 0;
			} else  {
				event = EVENT_SEND_ANSWER;
				bytes_counter = 0;
			}
		}
		HAL_UART_Receive_IT(&huart1, &rx_byte, 1);
	}
}
