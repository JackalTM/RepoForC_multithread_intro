#include "race2.h"
#ifdef INC_RACE_2_H

int sum;

int flag1 = 0;
int flag2 = 0;

DWORD WINAPI kernel1(LPVOID params)
{
    for (int i=0; i<100000; i++)
    {
        while(flag2 == 1);

        flag1 = 1;
        sum = sum + 1;
        flag1 = 0;
    }

    return 0;
}

DWORD WINAPI kernel2(LPVOID params)
{
    for (int i=0; i<100000; i++)
    {
        while(flag1 == 1);

        flag2 = 1;
        sum = sum + 1;
        flag2 = 0;
    }

    return 0;
}


int CALL_race2_main(void)
{
    sum = 0;

    HANDLE hThread1 = CreateThread(NULL, 0, kernel1, NULL, 0, NULL);
    HANDLE hThread2 = CreateThread(NULL, 0, kernel2, NULL, 0, NULL);

    WaitForSingleObject(hThread1, INFINITE);
    WaitForSingleObject(hThread2, INFINITE);

    CloseHandle(hThread1);
    CloseHandle(hThread2);

    printf("sum = %d\n", sum);

    return 0;
}

#endif // INC_RACE_2_H