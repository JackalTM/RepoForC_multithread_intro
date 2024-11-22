#include "S02_return.h"
#ifdef INC_S02_RETURN_H

DWORD WINAPI thread1(LPVOID params)
{
    return 123;
}

int CALL_main(void)
{
    HANDLE hThread1 = CreateThread(NULL, 0, thread1, NULL, 0, NULL);
    WaitForSingleObject(hThread1, INFINITE);

    DWORD ret;
    BOOL errval;
    errval = GetExitCodeThread(hThread1, &ret); //ret = GetExitCodeThread();

    printf("-- thread1() return value = %d, ExitCodeThread = %x \n", ret, errval);
    CloseHandle(hThread1);
    return 0;
}

#endif // INC_S02_RETURN_H