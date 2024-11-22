//#define INC_PHILIZOPHER_V1_H
#ifdef INC_PHILIZOPHER_V1_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h> 
#include "stdint.h"

#define TIME_RANDOM_MAX 0xFF
#define GET_RANDOM_BETWEEN(retRand, maxVal) (retRand % (maxVal+1))

#define PHILIZOPHER_ANOUNT (uint8_t)5
#define FORK_AMOUNT (uint8_t)5
#define FREE_PLACE (PHILIZOPHER_ANOUNT - 1)

#define THREADS_MAX PHILIZOPHER_ANOUNT
#define CALC_MUTEX1(th_n, th_max) (th_n)
#define CALC_MUTEX2(th_n, th_max) ((th_n+1) % th_max)



typedef struct 
{
    uint8_t thread_n;
    uint8_t mutex1_n;
    uint8_t mutex2_n;
    uint8_t sleepTime;
}threadData_t;

DWORD WINAPI ThreadPhilizopher(LPVOID pParam);

void CALL_PhilozopherProblem(void);

#endif // INC_PHILIZOPHER_V1_H