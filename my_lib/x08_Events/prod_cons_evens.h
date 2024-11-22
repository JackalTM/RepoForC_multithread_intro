//#define INC_PRODUCER_CONSUMER_H
#ifdef INC_PRODUCER_CONSUMER_H

#include <stdio.h>
#include <windows.h>

struct commonData_t
{
    unsigned char byte;
    unsigned char exit;
    unsigned int n;
};

DWORD WINAPI Producer(LPVOID pParams);
DWORD WINAPI Consumer(LPVOID pParams);
DWORD WINAPI KillTherads(LPVOID pParams);

void CALL_ProducerConsEvents(void);

#endif // INC_PRODUCER_CONSUMER_H