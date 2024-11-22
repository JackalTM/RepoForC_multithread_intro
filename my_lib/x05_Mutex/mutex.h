//#define INC_MUTEX_H
#ifdef INC_MUTEX_H

#include <windows.h>
#include <stdio.h>

DWORD WINAPI kernel(LPVOID params);
int CALL_Mutex_test1(void);

#endif // INC_MUTEX_H