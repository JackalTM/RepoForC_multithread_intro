#include "prod_cons3_ev_restart.h"
#ifdef INC_PRODUCER_CONSUMER3_EVRESTART_H

static struct commonData_t _commonData;

static CRITICAL_SECTION csData;

static HANDLE _hEvent_producer;
static HANDLE _hEvent_consumer;
static HANDLE _hEvent_kill;

DWORD WINAPI Producer(LPVOID pParams)
{
    unsigned char tByte;
    unsigned int tn;

    WaitForSingleObject(_hEvent_producer, INFINITE);

    Sleep(100);

    EnterCriticalSection(&csData);
        _commonData.byte = tByte;
        _commonData.n = tn;
    LeaveCriticalSection(&csData);

    tByte++;
    tn++;

    if(tByte > 'Z') tByte = 'A';
    else{;}

    if(tn > 26) SetEvent(_hEvent_kill);
    else        SetEvent(_hEvent_consumer);

    return 0;
}

DWORD WINAPI Consumer(LPVOID pParams)
{
    unsigned char tByte;
    unsigned int tn;

    WaitForSingleObject(_hEvent_consumer, INFINITE);

    Sleep(100);

    EnterCriticalSection(&csData);
        tByte = _commonData.byte;
        tn = _commonData.n;
        printf("|%c %d|, ", tByte, tn);
    LeaveCriticalSection(&csData);

    if(tn > 25) SetEvent(_hEvent_kill);
    else        SetEvent(_hEvent_producer);

    return 0;
}

DWORD WINAPI KillTherads(LPVOID pParams)
{
    printf(">> thKillTherads \n");

    WaitForSingleObject(_hEvent_kill, INFINITE);
    printf("\n>> Threads ended! \n");

    return 0;
}

void CALL_ProducerConsEventsRestart(void)
{
    _commonData.byte = 'A'; _commonData.n = 0; _commonData.exit = FALSE;

    InitializeCriticalSection(&csData);

    _hEvent_producer = CreateEvent(NULL, FALSE, TRUE, "Producer");
    _hEvent_consumer = CreateEvent(NULL, TRUE, FALSE, "Consumer");
    _hEvent_kill = CreateEvent(NULL, FALSE, FALSE, "Kill proceses");

    HANDLE thKillThre = CreateThread(NULL, 0, KillTherads, NULL, 0, NULL);
    HANDLE thProducer = CreateThread(NULL, 0, Producer, NULL, 0, NULL);
    HANDLE thConsumer[CONSUMER_AMOUNT];
    thConsumer[0] = CreateThread(NULL, 0, Consumer, NULL, 0, NULL);
    thConsumer[1] = CreateThread(NULL, 0, Consumer, NULL, 0, NULL);
    thConsumer[2] = CreateThread(NULL, 0, Consumer, NULL, 0, NULL);
    

    //WaitForSingleObject(evProducer, INFINITE);
    //WaitForSingleObject(evConsumer, INFINITE);
    WaitForSingleObject(thKillThre, 2000);

    CloseHandle(thProducer);
    CloseHandle(thConsumer[0]); CloseHandle(thConsumer[1]); CloseHandle(thConsumer[2]);
    CloseHandle(thKillThre);

    DeleteCriticalSection(&csData);

    //CloseHandle(_hEvent_kill);
}

#endif // INC_PRODUCER_CONSUMER3_EVRESTART_H