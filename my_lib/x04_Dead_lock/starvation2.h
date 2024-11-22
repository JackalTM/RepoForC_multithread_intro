//#define INC_STARVATION_H
#ifdef INC_STARVATION_H

#include <windows.h>
#include <stdio.h>

DWORD WINAPI kernel1(LPVOID params);
DWORD WINAPI kernel2(LPVOID params);
int CALL_Starvation_test1(void);

#endif // INC_STARVATION_H