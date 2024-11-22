#define INC_RACE_3_H
#ifdef INC_RACE_3_H


#include <stdint.h>
#include <windows.h>
#include <stdio.h>

#define THREAD_MAX_N 0x20U
enum EN_ThreadType{TH_N1, TH_N2};

typedef struct 
{
    uint8_t lock;
    uint32_t counter;
    uint32_t cntT1;
    uint32_t cntT2;
    uint32_t nonBussy;
}critical_t;

DWORD WINAPI kernel_test0(LPVOID params);

DWORD WINAPI kernel_test11(LPVOID params);
DWORD WINAPI kernel_test12(LPVOID params);

DWORD WINAPI kernel_test21(LPVOID params);
DWORD WINAPI kernel_test22(LPVOID params);

DWORD WINAPI kernel_test31(LPVOID params);
DWORD WINAPI kernel_test32(LPVOID params);

int CALL_race3_main0(void);
int CALL_race3_main1(void);
int CALL_race3_main2(void);
int CALL_race3_main3(void);

#endif // INC_RACE_3_H