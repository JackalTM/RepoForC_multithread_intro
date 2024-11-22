#ifdef INC_PHI2_H

#include <stdio.h>
#include <windows.h>

#define NO_PHIL 5

HANDLE hForks[NO_PHIL];
HANDLE hDinningRoom;

DWORD WINAPI philosopher(LPVOID param)
{
    int id = *((int*)param);
    int id_right = id;
    int id_left = (id+1) % NO_PHIL;

    for (int i=0; i<100; i++)
    {
        printf("Philosopher %d is thinking\n", id);
        Sleep(1);

        printf("Philosopher %d wants to eat\n", id);

        WaitForSingleObject(hDinningRoom, INFINITE);
        WaitForSingleObject(hForks[id_right], INFINITE);
        Sleep(1);
        WaitForSingleObject(hForks[id_left], INFINITE);

        printf("Philosopher %d is eating\n", id);
        Sleep(1);

        ReleaseMutex(hForks[id_right]);
        ReleaseMutex(hForks[id_left]);
        ReleaseSemaphore(hDinningRoom, 1, NULL);
    }

    return 0;
}

int main()
{
    for (int i=0; i<NO_PHIL; i++)
    {
        hForks[i] = CreateMutex(NULL, FALSE, NULL);
    }

    hDinningRoom = CreateSemaphore(NULL, NO_PHIL-1, NO_PHIL-1, NULL);

    HANDLE hPhils[NO_PHIL];
    int ids[NO_PHIL];

    for (int i=0; i<NO_PHIL; i++)
    {
        ids[i] = i;
        hPhils[i] = CreateThread(NULL, 0, philosopher, &ids[i], 0, NULL);
    }

    WaitForMultipleObjects(NO_PHIL, hPhils, TRUE, INFINITE);

    for (int i=0; i<NO_PHIL; i++)
    {
        CloseHandle(hPhils);
        CloseHandle(hForks[i]);
    }
    CloseHandle(hDinningRoom);

    return 0;
}

#endif // INC_PHI2_H