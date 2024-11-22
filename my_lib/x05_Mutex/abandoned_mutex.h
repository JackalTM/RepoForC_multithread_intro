//#define INC_ABANDONED_MUTEX_H
#ifdef INC_ABANDONED_MUTEX_H

#include <stdio.h>
#include <windows.h>

LPSTR GetErrorMessage(DWORD err);
DWORD WINAPI kernel(LPVOID param);
int CALL_AbandonedMutex_test1(void);

#endif // INC_ABANDONED_MUTEX_H