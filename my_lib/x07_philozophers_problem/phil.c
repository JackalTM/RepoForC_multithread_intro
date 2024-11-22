#ifdef INC_PHI_H
#include <stdio.h>
#include <windows.h>

#define NO_PHIL 5

HANDLE hForks[NO_PHIL];

DWORD WINAPI philosopher(LPVOID param)
{
    int id = *((int*)param);
    int id_right = id;
    int id_left = (id+1) % NO_PHIL;

    printf("Philosopher %d is thinking\n", id);
    Sleep(1);

    printf("Philosopher %d wants to eat\n", id);
    WaitForSingleObject(hForks[id_right], INFINITE);
    Sleep(1);
    WaitForSingleObject(hForks[id_left], INFINITE);

    printf("Philosopher %d is eating\n", id);
    Sleep(1);

    ReleaseMutex(hForks[id_right]);
    ReleaseMutex(hForks[id_left]);

    return 0;
}

int main()
{
    for (int i=0; i<NO_PHIL; i++)
    {
        hForks[i] = CreateMutex(NULL, FALSE, NULL);
    }

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

    return 0;
}

#endif // INC_PHI_H