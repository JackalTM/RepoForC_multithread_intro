#ifdef INC_MULTIPLE_EVENTS_H

#include <stdio.h>
#include <windows.h>
#include <stdlib.h>

#define NO_SENSORS 3

HANDLE hEvents[NO_SENSORS];

DWORD WINAPI AccelerometerThread(LPVOID params)
{
    Sleep(500);
    printf("Accelerometer data ready\n");
    SetEvent(hEvents[0]);
    return 0;
}

DWORD WINAPI GyroscopeThread(LPVOID params)
{
    Sleep(200);
    printf("Gyroscope data ready\n");
    SetEvent(hEvents[1]);
    return 0;
}

DWORD WINAPI EncoderThread(LPVOID params)
{
    Sleep(1000);
    printf("Encoder data ready\n");
    SetEvent(hEvents[2]);
    return 0;
}

DWORD WINAPI AnalyzerThread(LPVOID params)
{
    WaitForMultipleObjects(NO_SENSORS, hEvents, TRUE, INFINITE);

    Sleep(500);
    printf("Analysis finished\n");
    return 0;
}

int main()
{
    for (int i=0; i<NO_SENSORS; i++)
    {
        hEvents[i] = CreateEvent(NULL, FALSE, FALSE, NULL);
    }

    HANDLE hAccelerometerThread = CreateThread(NULL, 0, AccelerometerThread, NULL, 0, NULL);
    HANDLE hGyroscopeThread = CreateThread(NULL, 0, GyroscopeThread, NULL, 0, NULL);
    HANDLE hEncoderThread = CreateThread(NULL, 0, EncoderThread, NULL, 0, NULL);
    HANDLE hAnalyzerThread = CreateThread(NULL, 0, AnalyzerThread, NULL, 0, NULL);

    WaitForSingleObject(hAnalyzerThread, INFINITE);
    WaitForSingleObject(hAccelerometerThread, INFINITE);
    WaitForSingleObject(hGyroscopeThread, INFINITE);
    WaitForSingleObject(hEncoderThread, INFINITE);

    CloseHandle(hAnalyzerThread);
    CloseHandle(hAccelerometerThread);
    CloseHandle(hGyroscopeThread);
    CloseHandle(hEncoderThread);

    for (int i=0; i<NO_SENSORS; i++)
    {
        CloseHandle(hEvents[i]);
    }

    return 0;
}

#endif // INC_MULTIPLE_EVENTS_H