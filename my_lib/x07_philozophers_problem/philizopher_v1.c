#include "philizopher_v1.h"
#ifdef INC_PHILIZOPHER_V1_H


CRITICAL_SECTION cs_AsignData;
HANDLE hThreads[PHILIZOPHER_ANOUNT];
HANDLE hMutexes[PHILIZOPHER_ANOUNT];
HANDLE hSemaphore;

DWORD WINAPI ThreadPhilizopher(LPVOID pParam)
{
    uint8_t thread_n = ((threadData_t*)pParam)->thread_n;
    uint8_t mutex1_n = ((threadData_t*)pParam)->mutex1_n;
    uint8_t mutex2_n = ((threadData_t*)pParam)->mutex2_n;
    uint8_t sleepTime = ((threadData_t*)pParam)->sleepTime;

    Sleep(sleepTime);

    WaitForSingleObject(hSemaphore, INFINITE);
    printf(">> t%x enter \n", thread_n);
    Sleep(sleepTime);

    WaitForSingleObject(hMutexes[mutex1_n], INFINITE);
    printf(">> t%x take m%x \n", thread_n, mutex1_n);
    Sleep(sleepTime);
    
    WaitForSingleObject(hMutexes[mutex2_n], INFINITE);
    printf(">> t%x take m%x \n", thread_n, mutex2_n);
    Sleep(sleepTime);

    ReleaseSemaphore(hSemaphore, 1, NULL);
    printf(">> t%x exit \n", thread_n);
    return 0;
}

void CALL_PhilozopherProblem(void)
{
    uint8_t i;
    threadData_t thredsdata[PHILIZOPHER_ANOUNT];

    srand(time(0)); // Ustawianie ziarna jako czas startu progrmau
    hSemaphore = CreateSemaphore(NULL, 4, 4, "hSemaphore");

    for(i=0; i<THREADS_MAX; i++) 
    {
        thredsdata[i].thread_n = i;
        thredsdata[i].mutex1_n = CALC_MUTEX1(i, THREADS_MAX);
        thredsdata[i].mutex2_n = CALC_MUTEX2(i, THREADS_MAX);
        thredsdata[i].sleepTime = GET_RANDOM_BETWEEN(rand(), TIME_RANDOM_MAX);
        hMutexes[i] = CreateMutex(NULL, FALSE, "hMutex[i]");
        printf("-- t%x sleepTime= %x \n", i, thredsdata[i].sleepTime);
    }

    for(i=0; i<THREADS_MAX; i++)
    {   hThreads[i] = CreateThread(NULL, 0, ThreadPhilizopher, &thredsdata[i], 0, NULL); }

    WaitForMultipleObjects(THREADS_MAX, hThreads, TRUE, INFINITE);

    for(i=0; i<THREADS_MAX; i++)
    {
        CloseHandle(hThreads[i]);
        CloseHandle(hMutexes[i]);
    }
}

#endif // INC_PHILIZOPHER_V1_H