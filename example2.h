#ifndef __STATE_MACHINE_H
#define __STATE_MACHINE_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stdio.h"
#include "ppm.h"
#include "crc16.h"
#include <string.h>

typedef void *(*STATE_FUNC_PTR_t)();

typedef enum {
	EVENT_NONE,
	EVENT_RQST_PPM_STATUS,
	EVENT_INFORMATION_COMMAND,
	EVENT_ECHO,
	EVENT_SEND_ANSWER,
} EVENT_t;

void *state_idle(void);
void *state_rqst_ppm_status(void);
void *state_echo(void);
void *state_information_command(void);
void *state_send_answer(void);
void *state_check_answer(void);

#endif /*__STATE_MACHINE_H */
