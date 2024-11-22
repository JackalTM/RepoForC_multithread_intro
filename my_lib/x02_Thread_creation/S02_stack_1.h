//#define INC_S02_STACK_1_H
#ifdef INC_S02_STACK_1_H

#include <stdio.h>
#include <windows.h>

void recurrent(int x);
DWORD WINAPI thread1(LPVOID params);
LPSTR GetErrorMessage(DWORD err);

int CALL_Stack_test1(void);

#endif // INC_S02_STACK_1_H