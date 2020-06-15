# fsm_examples
# Example1: 
two leds, one button. Startup -> button polling -> led 1 on - led 2 off -> led 1 off - led 2 on -> all off -> button polling

Шаги:
1. Номера состояний (enum)
2. Функции реализации состояний (array)
3. Коды результата работы (enum)
4. Соотношение состояний с функциями реализации (array of function pointers)
5. Создание таблицы переходов: исходное состояние - результат работы - следующее состояние (struct)
6. Заполнение таблицы переходов (array of struct)
7. В основном цикле проходим по массиву указателей
8. Переключаем состояния в зависимости от текущего и кода результата работы

Таблица переходов
| Текущее состояние | Результат работы | Следующее состояние |
|-------------------|------------------|---------------------|
|     STARTUP       |     OK_FSM       |      BUTTON_POLL    |
|     BUTTON_POLL   |     OK_FSM       |  LED1_ON_LED2_OFF   |
|     BUTTON_POLL   |     REPEAT_FSM   |      BUTTON_POLL    |
| LED1_ON_LED2_OFF  |     OK_FSM       |  LED1_OFF_LED2_ON   |
| LED1_OFF_LED2_ON  |     OK_FSM       |       ALL_OFF       |
|     ALL_OFF       |     OK_FSM       |      BUTTON_POLL    |    
          
# Example2: 
Событийный автомат на указателях на функции

Значение event выставляется в Callback прерывания UART при выполнении определенных условий. 

Шаги:
1. Создание событий (enum) EVENT_t
2. Создание типа указателя на функции: typedef void *(*STATE_FUNC_PTR_t)();
3. Создание функций реализации состояний, возвращающих void *
4. Добавление глобальной переменной, отвечающей за состояние и хранящей адрес вызываемой функции: STATE_FUNC_PTR_t state = state_idle; (находится в файле main.c, в файле примера отсутствует) 
5. В основном цикле while(1) в файле main.c указываем: state = (STATE_FUNC_PTR_t)(*state)();

Таблица состояний
|    Текущее состояние    |          Событие        |   Следующее состояние   |
|-------------------------|-------------------------|-------------------------|
|        state_idle       |  EVENT_RQST_PPM_STATUS  |  state_rqst_ppm_status  |
|        state_idle       |EVENT_INFORMATION_COMMAND|state_information_command|
|        state_idle       |        EVENT_ECHO       |       state_echo        |
|        state_idle       |     EVENT_SEND_ANSWER   |    state_send_answer    |
|  state_rqst_ppm_status  |         EVENT_NONE      |       state_idle        |
|state_information_command|            ---          |    state_check_answer   |
|    state_check_answer   |        EVENT_NONE       |       state_idle        |
|    state_send_answer    |        EVENT_NONE       |       state_idle        |

По сути, вся работа сводится к выставлению своего рода флага в прерывании и последующей обработке, после чего флаг сбрасывается

# Example3: 
Конечный автомат с таблицей переходов

Шаги:
1. Создание событий (enum) EVENT_t
2. Создание состояний (enum) STATE_t
3. Функции реализации состояний: void func_state(void)
4. Создание таблицы состояний: 
void (*const transition_table[STATE_MAX][EVENT_MAX])(void) = {[STATE][EVENT] = func_state
5. Глобальные переменные STATE_t state и EVENT_t event с начальными значениями
6. В основном цикле: transition_table[state][event] ();
