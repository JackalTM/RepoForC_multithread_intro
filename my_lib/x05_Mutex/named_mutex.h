//#define INC_NAMED_MUTEX_H
#ifdef INC_NAMED_MUTEX_H

#include <stdio.h>
#include <windows.h>

DWORD WINAPI kernel(LPVOID param);
int CALL_NamedMutex_test1(void);

#endif // INC_NAMED_MUTEX_H