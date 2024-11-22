#include "race3.h"
#ifdef INC_RACE_3_H

uint8_t _LOCK;
critical_t myCritical;

DWORD WINAPI kernel_test0(LPVOID params)
{
    uint32_t i;
    critical_t* pCritical = (critical_t*)params;

    for(i=0; i<THREAD_MAX_N; i++)
    {
        pCritical->counter = pCritical->counter + 1;
    }
}

DWORD WINAPI kernel_test11(LPVOID params)
{
    uint32_t i;
    critical_t* pCritical = (critical_t*)params;

    for(i=0; i<THREAD_MAX_N; i++)
    {
        while(pCritical->lock == TRUE){;}

        pCritical->lock = TRUE;

        pCritical->counter = pCritical->counter + 1;
        pCritical->cntT1 = pCritical->cntT1 + 1;

        pCritical->lock = FALSE;
    }
}
DWORD WINAPI kernel_test12(LPVOID params)
{
    uint32_t i;
    critical_t* pCritical = (critical_t*)params;

    for(i=0; i<THREAD_MAX_N; i++)
    {
        while(pCritical->lock == TRUE){;}

        pCritical->lock = TRUE;

        pCritical->counter = pCritical->counter + 1;
        pCritical->cntT2 = pCritical->cntT2 + 1;

        pCritical->lock = FALSE;
    }
}

DWORD WINAPI kernel_test21(LPVOID params)
{
    uint32_t i;
    critical_t* pCritical = (critical_t*)params;

    for(i=0; i<THREAD_MAX_N; i++)
    {
        while(_LOCK == 0x22){ pCritical->nonBussy++;}
        _LOCK = 0x21;

        pCritical->counter = pCritical->counter + 1;
        pCritical->cntT1 = pCritical->cntT1 + 1;

        _LOCK = 0x22;
    }
}
DWORD WINAPI kernel_test22(LPVOID params)
{
    uint32_t i;
    critical_t* pCritical = (critical_t*)params;

    for(i=0; i<THREAD_MAX_N; i++)
    {
        while(_LOCK == 0x21){ pCritical->nonBussy++;}
        _LOCK = 0x22;

        pCritical->counter = pCritical->counter + 1;
        pCritical->cntT2 = pCritical->cntT2 + 1;

        _LOCK = 0x21;
    }
}

DWORD WINAPI kernel_test31(LPVOID params)
{
    uint32_t i;
    critical_t* pCritical = (critical_t*)params;

    for(i=0; i<THREAD_MAX_N; i++)
    {
        Sleep(1000);
        while(_LOCK != 0x31)
        { pCritical->nonBussy++; }

        pCritical->counter = pCritical->counter + 1;
        pCritical->cntT1 = pCritical->cntT1 + 1;

        _LOCK = 0x32;
    }
}
DWORD WINAPI kernel_test32(LPVOID params)
{
    uint32_t i;
    critical_t* pCritical = (critical_t*)params;

    for(i=0; i<THREAD_MAX_N; i++)
    {
        Sleep(10);
        while(_LOCK != 0x32){ pCritical->nonBussy++;}
        _LOCK = 0x22;

        pCritical->counter = pCritical->counter + 1;
        pCritical->cntT2 = pCritical->cntT2 + 1;

        _LOCK = 0x31;
    }
}

int CALL_race3_main0(void)
{
    myCritical.counter = 0;
    myCritical.lock = FALSE;

    printf("-- CALL_race3_main0() - started \n");

    HANDLE hThread_1 = CreateThread(NULL, 0, kernel_test0, &myCritical, 0, NULL);
    HANDLE hThread_2 = CreateThread(NULL, 0, kernel_test0, &myCritical, 0, NULL);

    WaitForSingleObject(hThread_1, INFINITE);
    WaitForSingleObject(hThread_2, INFINITE);

    CloseHandle(hThread_1);
    CloseHandle(hThread_2);

    printf("-- Resoult: \n");
    printf("-- CNT= %d \n", myCritical.counter);
    printf("-- lock= %x \n", myCritical.lock);

    return 0;
}

int CALL_race3_main1(void)
{
    myCritical.counter = 0;
    myCritical.lock = FALSE;
    myCritical.cntT1 = 0;
    myCritical.cntT2 = 0;

    printf("-- CALL_race3_main1() - started \n");

    HANDLE hThread_1 = CreateThread(NULL, 0, kernel_test11, &myCritical, 0, NULL);
    HANDLE hThread_2 = CreateThread(NULL, 0, kernel_test12, &myCritical, 0, NULL);

    WaitForSingleObject(hThread_1, INFINITE);
    WaitForSingleObject(hThread_2, INFINITE);

    CloseHandle(hThread_1);
    CloseHandle(hThread_2);

    printf("-- Resoult: \n");
    printf("-- CNT= %d \n", myCritical.counter);
    printf("-- c_T1= %d \n", myCritical.cntT1);
    printf("-- c_T2= %d \n", myCritical.cntT2);

    printf("-- CALL_race3_main1() - end \n \n");

    return 0;
}

int CALL_race3_main2(void)
{
    myCritical.counter = 0;
    _LOCK = 0x21;
    myCritical.cntT1 = 0;
    myCritical.cntT2 = 0;
    myCritical.nonBussy = 0;

    printf("-- CALL_race3_main2() - started \n");

    HANDLE hThread_1 = CreateThread(NULL, 0, kernel_test21, &myCritical, 0, NULL);
    HANDLE hThread_2 = CreateThread(NULL, 0, kernel_test22, &myCritical, 0, NULL);

    WaitForSingleObject(hThread_1, INFINITE);
    WaitForSingleObject(hThread_2, INFINITE);

    CloseHandle(hThread_1);
    CloseHandle(hThread_2);

    printf(">> CNT= %x | c_T1= %x | c_T2= %x \n", myCritical.counter, myCritical.cntT1, myCritical.cntT2);
    printf(">> nonBussy= %x \n", myCritical.nonBussy);
    printf("-- CALL_race3_main2() - end \n \n");

    return 0;
}

int CALL_race3_main3(void)
{
    // Starvation problem for less time concuming thread
    myCritical.counter = 0;
    _LOCK = 0x31;
    myCritical.cntT1 = 0;
    myCritical.cntT2 = 0;
    myCritical.nonBussy = 0;

    printf("-- CALL_race3_main3() - started \n");

    HANDLE hThread_1 = CreateThread(NULL, 0, kernel_test31, &myCritical, 0, NULL);
    HANDLE hThread_2 = CreateThread(NULL, 0, kernel_test32, &myCritical, 0, NULL);

    WaitForSingleObject(hThread_1, INFINITE);
    WaitForSingleObject(hThread_2, INFINITE);

    CloseHandle(hThread_1);
    CloseHandle(hThread_2);

    printf(">> CNT= %x | c_T1= %x | c_T2= %x \n", myCritical.counter, myCritical.cntT1, myCritical.cntT2);
    printf(">> nonBussy= %x \n", myCritical.nonBussy);
    printf("-- CALL_race3_main3() - end \n \n");

    return 0;
}

#endif // INC_RACE_3_H