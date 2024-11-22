#include "prod_cons_queue_v2.h"
#ifdef INC_PRODUCER_CONSUMER_QUEUE_V2_H

/******************************************************************
 * Initialization of semaphores
 */
static HANDLE hSemaphore_producer;
static HANDLE hSemaphore_consumer;
//=================================================================

/******************************************************************
 * Initialization of a global data
 */
static CRITICAL_SECTION myCriticalSection_bufor;
static struct queueBufor_t myQueBufor;
//=================================================================

inline void Queue_PrintElementts(struct queueBufor_t* pQue, char data)
{
    uint8_t i;
    uint16_t j=0;
    EnterCriticalSection(&myCriticalSection_bufor);
    printf(">> data= %c | ", data);
    printf("-- BUFOR= [ ");
        for(i=0; i<QUEUE_IXD_MAX; i++)
        {
            data = pQue->dataBuffor[i];
            if(data != '_') j++;
            else{;}
            putchar(data);
            putchar(','); putchar(' ');
        }
        printf(" ] n=%d \n",j);
    LeaveCriticalSection(&myCriticalSection_bufor);
}

/***********************************************************
 * @name        Queue_AddElement
 * @param[in]   inData Inputelement of type SINGLE_ELEMENT_T
 */
inline enum QUEUE_Enum Queue_AddElement(SINGLE_ELEMENT_T inData)
{
    uint8_t retval;
    EnterCriticalSection(&myCriticalSection_bufor);
    // Critical serction!!
        if (myQueBufor.iHead == myQueBufor.iTail)
        {   retval = QUEUE_full; }
        else
        {
            myQueBufor.dataBuffor[myQueBufor.iHead] = inData;
            myQueBufor.iHead++;
            if (myQueBufor.iHead >= QUEUE_IXD_MAX)
            {   myQueBufor.iHead = QUEUE_IXD_MIN;}
            else{;}
            retval = QUEUE_ok;
        }
    // Critical serction!!
    LeaveCriticalSection(&myCriticalSection_bufor);

    return retval;
}
//==========================================================

/***********************************************************
 * @name        Queue_GetElement
 * @return      Return element of type SINGLE_ELEMENT_T
 */
inline enum QUEUE_Enum Queue_GetElement(SINGLE_ELEMENT_T* pData)
{
    uint8_t retval;
    uint8_t t_idx;

    EnterCriticalSection(&myCriticalSection_bufor);
    // Critical serction!!
        t_idx = (myQueBufor.iTail + 1) % QUEUE_IXD_MAX;

        if(t_idx == myQueBufor.iHead)// Error
        {   *pData = 0x00; retval = QUEUE_empty;}
        else
        {
            *pData = myQueBufor.dataBuffor[t_idx];
            myQueBufor.dataBuffor[t_idx] = '_';
            myQueBufor.iTail++;

            if(myQueBufor.iTail >= QUEUE_IXD_MAX) { myQueBufor.iTail = QUEUE_IXD_MIN;}
            else{;}

            retval = QUEUE_ok;
        }
    // Critical serction!!
    LeaveCriticalSection(&myCriticalSection_bufor);

    return retval;
}
//==========================================================

inline static SINGLE_ELEMENT_T _CreateNextElement(SINGLE_ELEMENT_T inData)
{
    if(inData < 'Z') 
        return (inData + 1);
    else 
        return 'A';
}

inline static void _PrintCreatedElement(SINGLE_ELEMENT_T inData)   
{ printf("%c,", inData); }

/***********************************************************
 * @name        ThreadProducer
 * @return      DWORD
 */
DWORD WINAPI ThreadProducer(LPVOID params)
{
    uint8_t retval;
    SINGLE_ELEMENT_T tChar = 'A';    
    while(TRUE)
    {
        Sleep(PROD_TIME);
        WaitForSingleObject(hSemaphore_consumer, INFINITE);

            retval = Queue_AddElement(tChar);
            printf("--ADD= %c \n", tChar);
            tChar = _CreateNextElement(tChar);

        ReleaseSemaphore(hSemaphore_producer, 1, NULL);
    }
    return 0;
}
//==========================================================

/***********************************************************
 * @name        ThreadConsumer
 * @return      DWORD
 */
DWORD WINAPI ThreadConsumer(LPVOID params)
{
    uint8_t retval;
    SINGLE_ELEMENT_T tChar;
    while(1)
    {
        WaitForSingleObject(hSemaphore_producer, INFINITE);

            Queue_PrintElementts(&myQueBufor, tChar);
            retval = Queue_GetElement(&tChar);
            
        ReleaseSemaphore(hSemaphore_consumer, 1, NULL);
        Sleep(CONS_TIME);
    }
    return 0;
}
//==========================================================

/***********************************************************
 * @name        CALL_ProducentConsumerQuque_test1
 * @return      
 */
int CALL_ProducentConsumerQuque_test1(void)
{
    myQueBufor.iHead = 1;
    myQueBufor.iTail = 0;

    hSemaphore_producer = CreateSemaphore(NULL, 0, QUEUE_SIZE, NULL);
    hSemaphore_consumer = CreateSemaphore(NULL, QUEUE_SIZE-1, QUEUE_SIZE, NULL);
    InitializeCriticalSection(&myCriticalSection_bufor);

    HANDLE hProd = CreateThread(NULL, 0, ThreadProducer, NULL, 0, NULL);
    HANDLE hCons = CreateThread(NULL, 0, ThreadConsumer, NULL, 0, NULL);

    WaitForSingleObject(hProd, INFINITE);
    WaitForSingleObject(hCons, INFINITE);

    CloseHandle(hProd); CloseHandle(hCons);
    CloseHandle(hSemaphore_producer); CloseHandle(hSemaphore_consumer);

    DeleteCriticalSection(&myCriticalSection_bufor);

    return 0;
}

#endif // INC_PRODUCER_CONSUMER_QUEUE_V2_H