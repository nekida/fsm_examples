#ifndef __STATE_MACHINE_H
#define __STATE_MACHINE_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stdio.h"
#include <string.h>

typedef enum {
	STATE_IDLE,
	STATE_RQST_STATUS,
	STATE_INFORMATION_COMMAND,
	STATE_CHECK_ANSWER,
	STATE_ECHO,
	STATE_SEND_ANSWER,
	STATE_MAX
} STATE_t;

typedef enum {
	EVENT_NONE,
	EVENT_RQST_STATUS,
	EVENT_INFORMATION_COMMAND,
	EVENT_ECHO,
	EVENT_SEND_ANSWER,
	EVENT_MAX
} EVENT_t;

void state_idle(void);
void state_rqst_status(void);
void state_echo(void);
void state_information_command(void);
void state_send_answer(void);
void state_check_answer(void);

#endif /*__STATE_MACHINE_H */
