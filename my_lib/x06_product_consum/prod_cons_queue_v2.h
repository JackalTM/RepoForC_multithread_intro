//#define INC_PRODUCER_CONSUMER_QUEUE_V2_H
#ifdef INC_PRODUCER_CONSUMER_QUEUE_V2_H

#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <stdint.h>

#define PROD_TIME 333
#define CONS_TIME 1000
#define QUEUE_SIZE 5

#define QUEUE_IXD_MIN 0x00
#define QUEUE_IXD_MAX (QUEUE_SIZE + 1)

struct dataElement_t
{
    uint8_t byteArray[16];
    uint16_t lenght;
};

#define SINGLE_ELEMENT_T char
//#define SINGLE_ELEMENT_T uint8_t
//#define SINGLE_ELEMENT_T uint16_t
//#define SINGLE_ELEMENT_T uint32_t
//#define SINGLE_ELEMENT_T uint64_t
//#define SINGLE_ELEMENT_T int8_t
//#define SINGLE_ELEMENT_T int16_t
//#define SINGLE_ELEMENT_T int32_t
//#define SINGLE_ELEMENT_T int64_t

struct queueBufor_t 
{
    uint8_t iHead;
    uint8_t iTail;
    SINGLE_ELEMENT_T dataBuffor[QUEUE_IXD_MAX];
};
void Queue_PrintElementts(struct queueBufor_t* pQue, char data);

enum QUEUE_Enum{QUEUE_empty= 0x00, QUEUE_ok, QUEUE_full= 0xFF};

enum QUEUE_Enum Queue_AddElement(SINGLE_ELEMENT_T inData);
enum QUEUE_Enum Queue_GetElement(SINGLE_ELEMENT_T* pData);

DWORD WINAPI ThreadProducer(LPVOID params);
DWORD WINAPI ThreadConsumer(LPVOID params);

int CALL_ProducentConsumerQuque_test1(void);

#endif // INC_PRODUCER_CONSUMER_QUEUE_V2_H