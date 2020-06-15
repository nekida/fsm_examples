#include "state_machine.h"

extern uint8_t pc_uart_data_rx[37];
extern volatile bool flg_tx_rx_complete;
extern uint8_t ppm_spi_data_rx[32];
extern uint8_t ppm_spi_data_tx[32];
extern EVENT_t event;

void *state_idle() {
	if (event == EVENT_RQST_PPM_STATUS)
		return state_rqst_ppm_status;
	if (event == EVENT_INFORMATION_COMMAND)
		return state_information_command;
	if (event == EVENT_ECHO)
		return state_echo;
	if (event == EVENT_SEND_ANSWER)
		return state_send_answer;
	
	return state_idle;
}

void *state_rqst_ppm_status() {
	if ( (pc_uart_data_rx[2] | (pc_uart_data_rx[3] << 8) ) == get_crc16_modbus(pc_uart_data_rx, (LEN_MSG_REQUEST_STATUS_PPM_RX - 2)) )
		send_ppm_status();
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
	if ( (pc_uart_data_rx[35] | (pc_uart_data_rx[36] << 8) ) == get_crc16_modbus(pc_uart_data_rx, (LEN_MSG_INFORMATION_RX - 2)) ) {
		ppm_parcing_data();
		HAL_SPI_TransmitReceive_IT(&hspi1, ppm_spi_data_tx, ppm_spi_data_rx, 32);
		while(!flg_tx_rx_complete);
		ppm_le_push_pull();
		ppm_set_operating_mode();
		ppm_set_att();
		ppm_set_active_channel();
		ppm_set_rx_standby_control();
		ppm_set_tx_standby_control();
		flg_tx_rx_complete = false;
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
	if (ppm_check_tx_rx_arrays())
		send_answer(ERROR_NONE);
	else
		send_answer(ERROR_PPM_ANSWER);
	
	event = EVENT_NONE;
	return state_idle;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	static volatile int8_t bytes_counter = 0;
	
	if (huart == &huart1) {
		pc_uart_data_rx[bytes_counter++] = rx_byte;
		if (pc_uart_data_rx[0] == ADDR) {
			if ( (bytes_counter == LEN_MSG_REQUEST_STATUS_PPM_RX) && (pc_uart_data_rx[1] == CODE_FUNC_REQUEST_STATUS_PPM) ) {
				event = EVENT_RQST_PPM_STATUS;
				bytes_counter = 0;
			} else if (bytes_counter == LEN_MSG_INFORMATION_RX && pc_uart_data_rx[1] == CODE_FUNC_INFORMATION) {	
				event = EVENT_INFORMATION_COMMAND;
				bytes_counter = 0;
			} else if (bytes_counter == LEN_MSG_ECHO_RX && pc_uart_data_rx[1] == CODE_FUNC_ECHO) {
				event = EVENT_ECHO;
				bytes_counter = 0;
			} else if ( bytes_counter > LEN_MSG_ECHO_RX && \
						( (pc_uart_data_rx[1] != CODE_FUNC_REQUEST_STATUS_PPM) && (pc_uart_data_rx[1] != CODE_FUNC_INFORMATION) && (pc_uart_data_rx[1] != CODE_FUNC_ECHO) ) ) {
				event = EVENT_SEND_ANSWER;
				bytes_counter = 0;
			}
		}
		HAL_UART_Receive_IT(&huart1, &rx_byte, 1);
	}
}