#define INC_PRODUCER3_CONSUMER_EVRESTART_H
#ifdef INC_PRODUCER3_CONSUMER_EVRESTART_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define PRODUCER_AMOUNT 3U
#define GEN_RANDOM(inRand,inMax) (inRand % (inMax + 1))

enum done_en
{
    DONE_null,
    DONE_1_VEL,
    DONE_2_AC,
    DONE_3_GYRO_X,
    DONE_3_GYRO_Y,
    DONE_3_GYRO_Z
};

struct commonData_t
{
    enum done_en done;
    int velocity;
    int accelerat;
    int gyro_x;
    int gyro_y;
    int gyro_z;
};

DWORD WINAPI Producer_Speed(LPVOID pParams);
DWORD WINAPI Producer_Acceler(LPVOID pParams);
DWORD WINAPI Producer_Gyro(LPVOID pParams);
DWORD WINAPI Consumer(LPVOID pParams);
DWORD WINAPI KillTherads(LPVOID pParams);

void CALL_ProducerConsEventsRestart(void);

#endif // INC_PRODUCER3_CONSUMER_EVRESTART_H