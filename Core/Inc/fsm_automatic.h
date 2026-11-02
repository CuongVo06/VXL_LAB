#ifndef INC_FSM_AUTOMATIC_H_
#define INC_FSM_AUTOMATIC_H_

#include "global.h"
#include "software_timer.h"
#include "traffic_display.h"

typedef enum {
    AUTO_RED1_GREEN2,
    AUTO_RED1_YELLOW2,
    AUTO_GREEN1_RED2,
    AUTO_YELLOW1_RED2
} AutoState;

void fsm_automatic_init(void);
void fsm_automatic_run(void);

#endif /* INC_FSM_AUTOMATIC_H_ */
