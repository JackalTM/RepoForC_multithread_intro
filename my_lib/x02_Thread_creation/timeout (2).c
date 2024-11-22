#ifdef INC_TIMEOUT_2_H

#include <stdio.h>
#include <windows.h>

DWORD WINAPI thread1(LPVOID params)
{
    Sleep(10000);
    return 0;
}

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

int main()
{
    HANDLE hThread1 = CreateThread(NULL, 0, thread1, NULL, 0, NULL);
    DWORD err = WaitForSingleObject(hThread1, 2000);

    LPSTR errMsg = GetErrorMessage(err);

    if (errMsg != NULL)
    {
        printf("Error: %s\n", errMsg);
        LocalFree(errMsg);
    }

    return 0;
}

#endif // INC_TIMEOUT_1_H