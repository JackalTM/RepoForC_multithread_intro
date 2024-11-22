#include "prod_cons_evens.h"
#ifdef INC_PRODUCER_CONSUMER_H

static struct commonData_t _commonData = {0,0};

static CRITICAL_SECTION csData;

static HANDLE _hEvent_producer;
static HANDLE _hEvent_consumer;
static HANDLE _hEvent_kill;

DWORD WINAPI Producer(LPVOID pParams)
{
    printf(">> thProducer \n");
    unsigned char tByte = 'A';
    unsigned int tn = 0;

    while(TRUE)
    {
        WaitForSingleObject(_hEvent_producer, INFINITE);

        Sleep(100);

        if(tByte > 'Z') tByte = 'A';
        else{;}

        EnterCriticalSection(&csData);
            _commonData.byte = tByte;
            _commonData.n = tn;
        LeaveCriticalSection(&csData);

        tByte++;
        tn++;

        if(tn > 26) SetEvent(_hEvent_kill);
        else        SetEvent(_hEvent_consumer);
    }

    return 0;
}

DWORD WINAPI Consumer(LPVOID pParams)
{
    printf(">> thConsumer \n");
    unsigned char tByte;
    unsigned int tn;
    while(TRUE)
    {
        WaitForSingleObject(_hEvent_consumer, INFINITE);

        Sleep(100);

        EnterCriticalSection(&csData);
            tByte = _commonData.byte;
            tn = _commonData.n;
            printf("|%c %d|, ", tByte, tn);
        LeaveCriticalSection(&csData);

        if(tn > 25) SetEvent(_hEvent_kill);
        else        SetEvent(_hEvent_producer);
    }
    return 0;
}

DWORD WINAPI KillTherads(LPVOID pParams)
{
    printf(">> thKillTherads \n");

    WaitForSingleObject(_hEvent_kill, INFINITE);
    printf("\n>> Threads ended! \n");

    return 0;
}

void CALL_ProducerConsEvents(void)
{
    printf(">> CALL_ProducerConsEvents() \n");

    InitializeCriticalSection(&csData);

    _hEvent_producer = CreateEvent(NULL, FALSE, TRUE, "Producer");
    _hEvent_consumer = CreateEvent(NULL, FALSE, FALSE, "Consumer");
    _hEvent_kill = CreateEvent(NULL, FALSE, FALSE, "Kill proceses");

    HANDLE thProducer = CreateThread(NULL, 0, Producer, NULL, 0, NULL);
    HANDLE thConsumer = CreateThread(NULL, 0, Consumer, NULL, 0, NULL);
    HANDLE thKillThre = CreateThread(NULL, 0, KillTherads, NULL, 0, NULL);

    //WaitForSingleObject(evProducer, INFINITE);
    //WaitForSingleObject(evConsumer, INFINITE);
    WaitForSingleObject(thKillThre, INFINITE);

    CloseHandle(thProducer);
    CloseHandle(thConsumer);
    CloseHandle(thKillThre);

    DeleteCriticalSection(&csData);

    //CloseHandle(_hEvent_kill);
}

#endif // INC_PRODUCER_CONSUMER_H