#define INC_RACE_2_H
#ifdef INC_RACE_2_H

#include <windows.h>
#include <stdio.h>

DWORD WINAPI kernel1(LPVOID params);
DWORD WINAPI kernel2(LPVOID params);
int CALL_race2_main(void);

#endif // INC_RACE_2_H