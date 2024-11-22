#include "S02_timeout_2.h"
#ifdef INC_S02_TIMEOUT_2_H

DWORD WINAPI thread1(LPVOID params)
{
    Sleep(10000);
    return 0;
}

/****************************************************************************
 * @brief Explanation of WIN code error mesage
 *          More information can be find in documentation
 * 
 * @param[in]   err Error code in DWORD (typedef unsigned long)
 * 
 * @note    Inside errorMsg will be alocated array of char, that contain string message
 * 
 * @return  Proper formated string for error message.
 */
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

int CALL_Timeout2(void)
{
    HANDLE hThread1 = CreateThread(NULL, 0, thread1, NULL, 0, NULL);
    DWORD err = WaitForSingleObject(hThread1, 2000);

    LPSTR errMsg = GetErrorMessage(err);

    if (errMsg != NULL)
    {
        printf("-- Error: %s\n", errMsg);

        // Funkcja zastępcza dla aplikacji WIN
        // Normalnie urzyto by malloc() oraz free()
        // Jednak w tym wypadku urzywana jest funkcja LocalFree()
        LocalFree(errMsg);
    }

    return 0;
}

#endif // INC_S02_TIMEOUT_2_H