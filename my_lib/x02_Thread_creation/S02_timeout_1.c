#include "S02_timeout_1.h"
#ifdef INC_TIMEOUT_1_H

DWORD WINAPI thread0(LPVOID params)
{
    while(1)
    {   Sleep(1000);}
    return 0;
}



DWORD WINAPI thread1(LPVOID params)
{
    Sleep(10000);
    return 0;
}

int CALL_Timeout1_test0(void)
{
    HANDLE hThread0 = CreateThread(NULL, 0, thread0, NULL, 0, NULL);
    DWORD myError = WaitForSingleObject(hThread0, 3000);
    CloseHandle(hThread0);

    if(myError == WAIT_TIMEOUT)
        printf("-- Error WAIT_TIMEOUT code = 0x%x, %d \n", myError, myError); 
    else{;}
}

#endif // INC_TIMEOUT_0_H
