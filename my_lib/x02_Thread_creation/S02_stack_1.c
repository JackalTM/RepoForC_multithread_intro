#include "S02_stack_1.h"
#ifdef INC_S02_STACK_1_H

/***************************************************************
 * @brief Test recurency function for thread stact overflow
 */
void recurrent(int x)
{
    if (x <= 0)
    {
        return;
    }
    else
    {
        recurrent(x-1);
    }
}

DWORD WINAPI thread1(LPVOID params)
{
    recurrent(1024);
    Sleep(1000);
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

int CALL_Stack_test1(void)
{
    // W tym wypadku będzie przydzielone 128 MB stosu.
    // Wartości te są zaokrągląglane w górę.
    //                              (NULL, stact size[MB], function pointer, NULL, 0, NULL )
    HANDLE hThread1 = CreateThread(NULL, 128, thread1, NULL, 0, NULL);
    DWORD err = WaitForSingleObject(hThread1, 2000);

    LPSTR errMsg = GetErrorMessage(err);

    if (errMsg != NULL)
    {
        printf("Error: %s\n", errMsg);
        LocalFree(errMsg);
    }

    return 0;
}

#endif // INC_S02_STACK_1_H