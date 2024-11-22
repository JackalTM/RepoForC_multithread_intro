#ifdef INC_MANUAL_RESET_H

#include <stdio.h>
#include <windows.h>

#define NO_CONSUMERS 3

HANDLE hEvent;
char data = '@';

DWORD WINAPI producer(LPVOID param)
{
    char c = 'a';
    
    data = c;
    SetEvent(hEvent);

    return 0;
}

DWORD WINAPI consumer(LPVOID param)
{
    
    WaitForSingleObject(hEvent, INFINITE);
    Sleep(100);
    ResetEvent(hEvent);
    printf("%c\n", data);
  
    return 0;
}

int main()
{
    hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    HANDLE hProd = CreateThread(NULL, 0, producer, NULL, 0, NULL);

    HANDLE hCons[NO_CONSUMERS];

    for (int i=0; i<NO_CONSUMERS; i++)
    {
        hCons[i] = CreateThread(NULL, 0, consumer, NULL, 0, NULL);
    }

    WaitForSingleObject(hProd, INFINITE);
    WaitForMultipleObjects(NO_CONSUMERS, hCons, TRUE, INFINITE);

    CloseHandle(hEvent);
    CloseHandle(hProd);
    for (int i=0; i<NO_CONSUMERS; i++)
    {
        CloseHandle(hCons[i]);
    }

    return 0;
}

#endif // INC_MANUAL_RESET_H