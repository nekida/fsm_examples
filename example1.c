/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usart.h"
#include "usb_otg.h"
#include "gpio.h"

//номера состояний
typedef enum{
	STARTUP = 0,
	BUTTON_POLL,
	LED1_ON_LED2_OFF,
	LED1_OFF_LED2_ON,
	ALL_OFF
} FSM_STATE ;

//коды возврата
typedef enum {
	OK_FSM = 0,
	ERROR_FSM,
	REPEAT_FSM
} RET_CODES ;

//таблица переходов
typedef struct {
	FSM_STATE src_state;
	RET_CODES ret_code;
	FSM_STATE dst_state;
} fsm_cell_t;

//менеджер
void fsm_loop(FSM_STATE state);

//функции реализации состояний
RET_CODES startup(void);
RET_CODES button_poll(void);
RET_CODES led1_on_led2_off(void);
RET_CODES led1_off_led2_on(void);
RET_CODES all_off(void);

//связываем коды состояний с подпрограммами
RET_CODES (*state_executer[])(void) = {
	[STARTUP] 		= startup,
	[BUTTON_POLL] 		= button_poll,
	[LED1_ON_LED2_OFF] 	= led1_on_led2_off,
	[LED1_OFF_LED2_ON] 	= led1_off_led2_on,
	[ALL_OFF]		= all_off
};

//заполняем таблицу
//начальное згачение -> результат -> следующее состояние
fsm_cell_t fsm_table[] = {
	{STARTUP, 		OK_FSM, 		BUTTON_POLL},
	{BUTTON_POLL, 		OK_FSM, 		LED1_ON_LED2_OFF},
	{BUTTON_POLL, 		REPEAT_FSM, 		BUTTON_POLL},
	{LED1_ON_LED2_OFF, 	OK_FSM, 		LED1_OFF_LED2_ON},
	{LED1_OFF_LED2_ON,	OK_FSM,			ALL_OFF},
	{ALL_OFF,		OK_FSM,			BUTTON_POLL}
};
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART3_UART_Init();
  MX_USB_OTG_FS_PCD_Init();
  /* USER CODE BEGIN 2 */
	int state = STARTUP;
	RET_CODES ret_code;
	int iter;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
		ret_code = state_executer[state]();
		
		for (iter = 0; iter < sizeof(fsm_table); iter++) {
			if (fsm_table[iter].src_state == state && fsm_table[iter].ret_code == ret_code) {
				state = fsm_table[iter].dst_state;
				break;
			}
		}
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/* USER CODE BEGIN 4 */
RET_CODES startup(void) {
	return OK_FSM;
}

RET_CODES button_poll(void) {
	if(HAL_GPIO_ReadPin(USER_Btn_GPIO_Port, USER_Btn_Pin))
		return OK_FSM;
	else
		return REPEAT_FSM;
}

RET_CODES led1_on_led2_off(void) {
	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);
	return OK_FSM;
}

RET_CODES led1_off_led2_on(void) {
	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_SET);
	return OK_FSM;
}

RET_CODES all_off(void) {
	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);
	return OK_FSM;
}
