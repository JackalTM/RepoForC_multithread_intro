#include "named_mutex.h"
#ifdef INC_NAMED_MUTEX_H

HANDLE hMutex;

DWORD WINAPI kernel(LPVOID param)
{
    while(1)
    {
        WaitForSingleObject(hMutex, INFINITE);
        for (int i=0; i<10; i++)
        {
            printf("%d\n", i);
            Sleep(500);
        }
        ReleaseMutex(hMutex);
    }
    return 0;
}

int CALL_NamedMutex_test1(void)
{
    hMutex = CreateMutex(NULL, FALSE, TEXT("SharedMutex"));

    HANDLE hThread = CreateThread(NULL, 0, kernel, NULL, 0, NULL);
    WaitForSingleObject(hThread, INFINITE);
    CloseHandle(hThread);
    CloseHandle(hMutex);

    return 0;
}

#endif // INC_NAMED_MUTEX_H