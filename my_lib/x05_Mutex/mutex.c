#include "mutex.h"
#ifdef INC_MUTEX_H

HANDLE hMutex;
int sum;

DWORD WINAPI kernel(LPVOID params)
{
    for (int i=0; i<100000; i++)
    {
        WaitForSingleObject(hMutex, INFINITE);
        sum = sum + 1;
        ReleaseMutex(hMutex);
    }

    return 0;
}

int CALL_Mutex_test1(void)
{
    sum = 0;

    hMutex = CreateMutex(NULL, FALSE, NULL);

    HANDLE hThread1 = CreateThread(NULL, 0, kernel, NULL, 0, NULL);
    HANDLE hThread2 = CreateThread(NULL, 0, kernel, NULL, 0, NULL);

    WaitForSingleObject(hThread1, INFINITE);
    WaitForSingleObject(hThread2, INFINITE);

    CloseHandle(hThread1);
    CloseHandle(hThread2);
    CloseHandle(hMutex);

    printf("sum = %d\n", sum);

    return 0;
}

#endif // INC_MUTEX_H