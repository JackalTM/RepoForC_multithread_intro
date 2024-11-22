#include "S01_hello_threads.h"
#ifdef INC_S01_HELLO_THREADS_H

DWORD WINAPI thread1(LPVOID params)
{
    int i = 0;
    while(i<20)
    {
        printf("thread1: %d\n", 2*i);
        i++;
        Sleep(1000);
    }
    return 0;
}

DWORD WINAPI thread2(LPVOID params)
{
    int i = 0;
    while(i<20)
    {
        printf("thread2: %d\n", 2*i+1);
        i++;
        Sleep(1000);
    }
    return 0;
}

void CALL_HelloThreads(void)
{
    HANDLE hThread1 = CreateThread(NULL, 0, thread1, NULL, 0, NULL);
    HANDLE hThread2 = CreateThread(NULL, 0, thread2, NULL, 0, NULL);

    WaitForSingleObject(hThread1, INFINITE);
    WaitForSingleObject(hThread2, INFINITE);

    CloseHandle(hThread1);
    CloseHandle(hThread2);
}

#endif // INC_S01_HELLO_THREADS_H