//#define INC_CRITICAL_SECTION_H
#ifdef INC_CRITICAL_SECTION_H

#include <windows.h>
#include <stdio.h>
#include <stdint.h>

typedef struct myCriticalData
{
    uint32_t cnt;
    uint32_t c_T1;
    uint32_t c_T2;
}criticalData_t;

DWORD WINAPI kernel(LPVOID params);

DWORD WINAPI kernel_test1(LPVOID params);
DWORD WINAPI kernel_test2(LPVOID params);

int CALL_CriticalSection_test1(void);
int CALL_CriticalSection_test2(void);

#endif // INC_CRITICAL_SECTION_H