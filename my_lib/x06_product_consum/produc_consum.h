//#define INC_PRODUCTION_COMSUMPTION_H
#ifdef INC_PRODUCTION_COMSUMPTION_H

#include <stdio.h>
#include <windows.h>
#include <stdint.h>
#include "my_helper.h"

#define PRODUCER_TIME (uint16_t)500U
struct producer_t
{
    char arrChar[16];
    uint8_t len;
};
DWORD WINAPI Producer(LPVOID pParams);

#define CONSUMER_TIME (uint16_t)700U
struct consmer_t
{
    char arrChar[16];
    uint8_t len;
};
DWORD WINAPI Consumer(LPVOID pParams);

struct commomData_t
{
    char arrChar[16];
    uint8_t len;
};

struct threadsHandlers_t
{
    HANDLE hProducer;
    HANDLE hConsumer;
};
DWORD WINAPI ThreadControl(LPVOID pParams);

int CALL_ProducerAndConsumer_test1(void);

#endif // INC_PRODUCTION_COMSUMPTION_H