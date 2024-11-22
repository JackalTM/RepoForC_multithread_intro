#include "abandoned_mutex.h"
#ifdef INC_ABANDONED_MUTEX_H

HANDLE hMutex;

LPSTR GetErrorMessage(DWORD err)
{
    LPTSTR errorMsg = NULL;

    FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM
   |FORMAT_MESSAGE_ALLOCATE_BUFFER
   |FORMAT_MESSAGE_IGNORE_INSERTS,  
   NULL,    
   err,
   MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
   (LPTSTR)&errorMsg, 
   0,
   NULL);  

    return errorMsg;
}

DWORD WINAPI kernel(LPVOID param)
{
    while(1)
    {
        DWORD errCode = WaitForSingleObject(hMutex, INFINITE);

        LPTSTR errMsg = GetErrorMessage(errCode);

        if (errMsg!=NULL)
        {
            printf("Error: %s\n", errMsg);
            LocalFree(errMsg);
        }

        for (int i=0; i<10; i++)
        {
            printf("%d\n", i);
            Sleep(500);
        }
        ReleaseMutex(hMutex);
    }
    return 0;
}

int CALL_AbandonedMutex_test1(void)
{
    hMutex = CreateMutex(NULL, FALSE, TEXT("SharedMutex"));

    HANDLE hThread = CreateThread(NULL, 0, kernel, NULL, 0, NULL);
    WaitForSingleObject(hThread, INFINITE);
    CloseHandle(hThread);
    CloseHandle(hMutex);

    return 0;
}

#endif // INC_ABANDONED_MUTEX_H