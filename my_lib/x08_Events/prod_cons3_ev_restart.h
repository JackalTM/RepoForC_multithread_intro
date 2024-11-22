//#define INC_PRODUCER_CONSUMER3_EVRESTART_H
#ifdef INC_PRODUCER_CONSUMER3_EVRESTART_H

#include <stdio.h>
#include <windows.h>

#define CONSUMER_AMOUNT 3U

struct commonData_t
{
    unsigned char byte;
    unsigned char exit;
    unsigned int n;
};

DWORD WINAPI Producer(LPVOID pParams);
DWORD WINAPI Consumer(LPVOID pParams);
DWORD WINAPI KillTherads(LPVOID pParams);

void CALL_ProducerConsEventsRestart(void);

#endif // INC_PRODUCER_CONSUMER3_EVRESTART_H