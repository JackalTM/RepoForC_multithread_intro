#include "S02_args.h"
#ifdef INC_ARGS_H

DWORD WINAPI thread1(LPVOID params)
{
    int offset = *((int*)params);
    int i;

    printf("-- DWORD WINAPI thread1(LPVOID params): ");

    for(i=offset; i<offset+10; i++)
    {
        printf( "%d,",i);
    }

    return 0;
}

int CALL_Args(void)
{
    int x = 2;
    HANDLE hThread1 = CreateThread(NULL, 0, thread1, &x, 0, NULL);
    WaitForSingleObject(hThread1, INFINITE);
    CloseHandle(hThread1);

    return 0;
}

#endif // INC_ARGS_H