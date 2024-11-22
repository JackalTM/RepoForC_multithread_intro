//#define INC_MUTEX2_H
#ifdef INC_MUTEX2_H

#include <windows.h>
#include <stdio.h>

DWORD WINAPI kernel(LPVOID params);
DWORD WINAPI MyKerel_Test1(LPVOID params);
DWORD WINAPI MyKerel_Test2(LPVOID params);
int CALL_Mutex2_test1(void);

#endif // INC_MUTEX2_H