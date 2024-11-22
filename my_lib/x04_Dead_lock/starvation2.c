#include "starvation2.h"
#ifdef INC_STARVATION_H

CRITICAL_SECTION cs;

DWORD WINAPI kernel1(LPVOID params)
{
    for (int i=0; i<100000; i++)
    {
        Sleep(1000);

        EnterCriticalSection(&cs);
        printf("Thread1: %d\n", i);
        LeaveCriticalSection(&cs);
    }

    return 0;
}

DWORD WINAPI kernel2(LPVOID params)
{
    for (int i=0; i<100000; i++)
    {
        Sleep(100);

        EnterCriticalSection(&cs);
        printf("Thread2: %d\n", i);
        LeaveCriticalSection(&cs);
    }

    return 0;
}

int CALL_Starvation_test1(void)
{
    InitializeCriticalSection(&cs);
    HANDLE hThread1 = CreateThread(NULL, 0, kernel1, NULL, 0, NULL);
    HANDLE hThread2 = CreateThread(NULL, 0, kernel2, NULL, 0, NULL);

    WaitForSingleObject(hThread1, INFINITE);
    WaitForSingleObject(hThread2, INFINITE);

    CloseHandle(hThread1);
    CloseHandle(hThread2);
    DeleteCriticalSection(&cs);

    return 0;
}

#endif // INC_STARVATION_H