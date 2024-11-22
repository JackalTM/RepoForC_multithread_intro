#include "race1.h"
#ifdef INC_RACE_1_H

int sum;

DWORD WINAPI kernel(LPVOID params)
{
    for (int i=0; i<100000; i++)
    {
        sum = sum + 1;
    }

    return 0;
}

int CALL_race_main(void)
{
    sum = 0;

    HANDLE hThread1 = CreateThread(NULL, 0, kernel, NULL, 0, NULL);
    HANDLE hThread2 = CreateThread(NULL, 0, kernel, NULL, 0, NULL);

    WaitForSingleObject(hThread1, INFINITE);
    WaitForSingleObject(hThread2, INFINITE);

    CloseHandle(hThread1);
    CloseHandle(hThread2);

    printf("sum = %d\n", sum);

    return 0;
}

#endif // INC_RACE_1_H