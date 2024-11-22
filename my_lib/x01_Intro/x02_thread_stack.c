#include "x02_thread_stack.h"
#ifdef INC_S02_THRERAD_STACK_H


int *ptr = NULL;

DWORD WINAPI thread1(LPVOID params)
{
    int x = 0;
    ptr = &x;

    while(1)
    {
        printf("x=%d\n", x);
        Sleep(1000);
    }

    return 0;
}

DWORD WINAPI thread2(LPVOID params)
{
    while(1)
    {
        if (ptr!=NULL)
        {
            *ptr = (*ptr)+1;
        }
        Sleep(1000);
    }

    return 0;
}

void CALL_ThreadStack(void)
{
    HANDLE hThread1 = CreateThread(NULL, 0, thread1, NULL, 0, NULL);
    HANDLE hThread2 = CreateThread(NULL, 0, thread2, NULL, 0, NULL);

    WaitForSingleObject(hThread1, INFINITE);
    WaitForSingleObject(hThread2, INFINITE);

    CloseHandle(hThread1);
    CloseHandle(hThread2);

    return 0;
}

#endif // INC_THRERAD_STACK_H