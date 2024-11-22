#include "critical_section.h"
#ifdef INC_CRITICAL_SECTION_H

CRITICAL_SECTION cs;
int sum;

DWORD WINAPI kernel(LPVOID params)
{
    for (int i=0; i<100000; i++)
    {
        EnterCriticalSection(&cs);
        sum = sum + 1;
        LeaveCriticalSection(&cs);
    }

    return 0;
}

DWORD WINAPI kernel_test1(LPVOID params)
{
    criticalData_t* pCriticalData = (criticalData_t*)params;
    uint32_t i;
    for(i=0; i<0x20000; ++i)
    {
        EnterCriticalSection(&cs);
        pCriticalData->cnt = pCriticalData->cnt + 1;
        pCriticalData->c_T1 = pCriticalData->c_T1 + 1;
        LeaveCriticalSection(&cs); 
    }
}

DWORD WINAPI kernel_test2(LPVOID params)
{
    struct myCriticalData* pCriticalData = (struct myCriticalData*)params;

    uint32_t i;
    for(i=0; i<0x20000; ++i)
    {
        EnterCriticalSection(&cs);
        pCriticalData->cnt = pCriticalData->cnt + 1;
        pCriticalData->c_T2 = pCriticalData->c_T2 + 1;
        LeaveCriticalSection(&cs); 
    }
}

int CALL_CriticalSection_test1(void)
{
    sum = 0;

    InitializeCriticalSection(&cs);
    //--------------------------------------------------------------------

    HANDLE hThread1 = CreateThread(NULL, 0, kernel, NULL, 0, NULL);
    HANDLE hThread2 = CreateThread(NULL, 0, kernel, NULL, 0, NULL);

    WaitForSingleObject(hThread1, INFINITE);
    WaitForSingleObject(hThread2, INFINITE);

    CloseHandle(hThread1);
    CloseHandle(hThread2);

    //--------------------------------------------------------------------
    DeleteCriticalSection(&cs);

    printf("sum = %d\n", sum);

    return 0;
}

int CALL_CriticalSection_test2(void)
{
    criticalData_t tCD1 = {0,0,0};
    struct myCriticalData tCD2 = {0,0,0};
    
    InitializeCriticalSection(&cs);
    //==========================================================

    HANDLE hThread1;
    HANDLE hThread2;

    hThread1 = CreateThread(NULL, 0, kernel_test1, &tCD1, 0, NULL);
    hThread2 = CreateThread(NULL, 0, kernel_test1, &tCD2, 0, NULL);

    WaitForSingleObject(hThread1, INFINITE);
    WaitForSingleObject(hThread2, INFINITE);

    CloseHandle(hThread1);
    CloseHandle(hThread2);

    //--------------------------------------------------------

    hThread1 = CreateThread(NULL, 0, kernel_test2, &tCD1, 0, NULL);
    hThread2 = CreateThread(NULL, 0, kernel_test2, &tCD2, 0, NULL);

    WaitForSingleObject(hThread1, INFINITE);
    WaitForSingleObject(hThread2, INFINITE);

    CloseHandle(hThread1);
    CloseHandle(hThread2);

    //==========================================================
    DeleteCriticalSection(&cs);

    printf("-- tCD1 cnt= %x | cT1= %x | cT2= %x \n", tCD1.cnt, tCD1.c_T1, tCD1.c_T2);
    printf("-- tCD2 cnt= %x | cT1= %x | cT2= %x \n", tCD2.cnt, tCD2.c_T1, tCD2.c_T2);

    return 0;
}

#endif // INC_CRITICAL_SECTION_H