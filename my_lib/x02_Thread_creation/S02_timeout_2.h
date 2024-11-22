//#define INC_S02_TIMEOUT_2_H
#ifdef INC_S02_TIMEOUT_2_H

#include <stdio.h>
#include <windows.h>

DWORD WINAPI thread1(LPVOID params);
LPSTR GetErrorMessage(DWORD err);
int CALL_Timeout2(void);

#endif // INC_S02_TIMEOUT_2_H