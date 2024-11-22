#ifdef INC_EVENTS_H

#include <stdio.h>
#include <windows.h>

HANDLE hEvent;
char data = '@';

DWORD WINAPI producer(LPVOID param)
{
    char c = 'a';
    while(1)
    {
        data = c;
        SetEvent(hEvent);

        c++;
        if (c > 'z')
        {
            c = 'a'; 
        }
        Sleep(500);
    }
    return 0;
}

DWORD WINAPI consumer(LPVOID param)
{
    while(1)
    {
        WaitForSingleObject(hEvent, INFINITE);
        printf("%c, ", data);
    }
    return 0;
}

int main()
{
    hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    HANDLE hProd = CreateThread(NULL, 0, producer, NULL, 0, NULL);
    HANDLE hCons = CreateThread(NULL, 0, consumer, NULL, 0, NULL);

    WaitForSingleObject(hProd, INFINITE);
    WaitForSingleObject(hCons, INFINITE);

    CloseHandle(hEvent);
    CloseHandle(hProd);
    CloseHandle(hCons);

    return 0;
}

#endif // INC_EVENTS_H