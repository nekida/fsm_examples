/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "crc16.h"
#include "state_machine.h"

/* USER CODE BEGIN 0 */
STATE_t state = STATE_IDLE;
volatile EVENT_t event = EVENT_NONE;

void (*const transition_table[STATE_MAX][EVENT_MAX])(void) = {
	[STATE_IDLE]			[EVENT_RQST_STATUS] 		= state_rqst_status,
	[STATE_IDLE]			[EVENT_INFORMATION_COMMAND]	= state_information_command,
	[STATE_IDLE]			[EVENT_ECHO]			= state_echo,
	[STATE_IDLE]			[EVENT_SEND_ANSWER]		= state_send_answer,
	[STATE_IDLE]			[EVENT_NONE]			= state_idle,
	[STATE_RQST_STATUS]		[EVENT_NONE]			= state_idle,
	[STATE_INFORMATION_COMMAND]	[EVENT_NONE]			= state_check_answer,
	[STATE_CHECK_ANSWER]		[EVENT_NONE]			= state_idle,
	[STATE_ECHO]			[EVENT_NONE]			= state_idle,
	[STATE_SEND_ANSWER]		[EVENT_NONE]			= state_idle
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

  /* Enable I-Cache---------------------------------------------------------*/
  SCB_EnableICache();

  /* Enable D-Cache---------------------------------------------------------*/
  SCB_EnableDCache();

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	transition_table[state][event]();
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}
