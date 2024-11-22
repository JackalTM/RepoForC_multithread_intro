#include "prod3_cons_ev_restart.h"
#ifdef INC_PRODUCER3_CONSUMER_EVRESTART_H

static int arrRand[5];
static struct commonData_t _commonData;

static CRITICAL_SECTION csData;

static HANDLE _hEvent_speed;
static HANDLE _hEvent_aceler;
static HANDLE _hEvent_gyrosc;

static HANDLE _hEvent_consumer;

DWORD WINAPI Producer_Speed(LPVOID pParams)
{
    WaitForSingleObject(_hEvent_speed, INFINITE);
    Sleep(100);

    EnterCriticalSection(&csData);
    if(_commonData.done == DONE_null)
    {  
        _commonData.velocity = GEN_RANDOM(arrRand[0], 0xFFF);
        _commonData.done = DONE_1_VEL; 
        printf(">> Producer1: speed done \n");
    }
    LeaveCriticalSection(&csData);

    SetEvent(_hEvent_aceler);

    return 0;
}

DWORD WINAPI Producer_Acceler(LPVOID pParams)
{
    WaitForSingleObject(_hEvent_aceler, INFINITE);
    Sleep(100);

    EnterCriticalSection(&csData);
    if(_commonData.done == DONE_1_VEL)
    {
        _commonData.accelerat = GEN_RANDOM(arrRand[1], 0xFF);
        _commonData.done = DONE_2_AC;
        printf(">> Producer2: acceleration done \n");
    }
    LeaveCriticalSection(&csData);

    SetEvent(_hEvent_gyrosc);

    return 0;
}

DWORD WINAPI Producer_Gyro(LPVOID pParams)
{
    WaitForSingleObject(_hEvent_gyrosc, INFINITE);
    Sleep(100);

    EnterCriticalSection(&csData);
    if(_commonData.done == DONE_2_AC)
    {
        _commonData.gyro_x = GEN_RANDOM(arrRand[2], 0xFFF);
        _commonData.done = DONE_3_GYRO_X;

        _commonData.gyro_y = GEN_RANDOM(arrRand[3], 0xFFF);
        _commonData.done = DONE_3_GYRO_Y;

        _commonData.gyro_z = GEN_RANDOM(arrRand[4], 0xFFF);
        _commonData.done = DONE_3_GYRO_Z;
        printf(">> Producer3: gyroscope done\n");
    }
    LeaveCriticalSection(&csData);

    SetEvent(_hEvent_gyrosc);

    return 0;
}

DWORD WINAPI Consumer(LPVOID pParams)
{
    WaitForSingleObject(_hEvent_gyrosc, INFINITE);
    Sleep(100);

    EnterCriticalSection(&csData);
    printf("-- Sensors data:\n");
    printf("-- velocity= %d, acceleration= %d \n", _commonData.velocity, _commonData.accelerat);
    printf("-- Gyroscope: x= %d, y= %d, z= %d \n", _commonData.gyro_x, _commonData.gyro_y, _commonData.gyro_z);
    LeaveCriticalSection(&csData);

    return 0;
}

void CALL_ProducerConsEventsRestart(void)
{
    srand(time(0));
    arrRand[0] = rand(); 
    arrRand[1] = rand(); 
    arrRand[2] = rand(); 
    arrRand[3] = rand();
    arrRand[4] = rand();

    InitializeCriticalSection(&csData);

    _hEvent_speed = CreateEvent(NULL, FALSE, TRUE, "Speed");
    _hEvent_aceler = CreateEvent(NULL, FALSE, FALSE, "Acceleration");
    _hEvent_gyrosc = CreateEvent(NULL, FALSE, FALSE, "Gyroscope");
    _hEvent_consumer = CreateEvent(NULL, FALSE, FALSE, "Consumer");

    HANDLE thSpeed = CreateThread(NULL, 0, Producer_Speed, NULL, 0, NULL);
    HANDLE thAccel = CreateThread(NULL, 0, Producer_Acceler, NULL, 0, NULL);
    HANDLE thGyroX = CreateThread(NULL, 0, Producer_Gyro, NULL, 0, NULL);
    HANDLE thPrint = CreateThread(NULL, 0, Consumer, NULL, 0 , NULL);

    //WaitForSingleObject(evProducer, INFINITE);
    //WaitForSingleObject(evConsumer, INFINITE);
    WaitForSingleObject(thPrint, INFINITE);

    CloseHandle(thSpeed); 
    CloseHandle(thAccel); 
    CloseHandle(thGyroX);
    CloseHandle(thPrint);

    DeleteCriticalSection(&csData);
}

#endif // INC_PRODUCER3_CONSUMER_EVRESTART_H