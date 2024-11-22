#include "prod_cons_queue.h"
#ifdef INC_PRODUCER_CONSUMER_QUEUE_H

static HANDLE hSemaphore;
static CRITICAL_SECTION myCriticalSection;
static struct queueBufor_t myQueBufor;

inline void Queue_PrintElementts(struct queueBufor_t* pQue)
{
    uint8_t i;
    printf("-- BUFOR= [ ");
    for(i=0; i<QUEUE_IXD_MAX; i++)
    {
        putchar(pQue->dataBuffor[i]);
        putchar(','); putchar(' ');
    }
    printf(" ] \t");
    printf(" | head= %x, tail= %x \n", pQue->iHead, pQue->iTail);
}

/***********************************************************
 * @name        Queue_AddElement
 * @param[in]   inData Inputelement of type SINGLE_ELEMENT_T
 */
inline enum QUEUE_Enum Queue_AddElement(SINGLE_ELEMENT_T inData)
{
    uint8_t retval;
    EnterCriticalSection(&myCriticalSection);

        //printf(">> AddElement= %c \n", inData);
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
        //Queue_PrintElementts(&myQueBufor);

    LeaveCriticalSection(&myCriticalSection);

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

    EnterCriticalSection(&myCriticalSection);

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
        //Queue_PrintElementts(&myQueBufor);
        //printf(">> GetElement= %c \n", *pData);

    LeaveCriticalSection(&myCriticalSection);

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
            retval = Queue_AddElement(tChar);
        ReleaseSemaphore(hSemaphore, 1, NULL);

        if(retval != QUEUE_full)
        {   tChar = _CreateNextElement(tChar); }
        else{;}
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
        WaitForSingleObject(hSemaphore, INFINITE);
            retval = Queue_GetElement(&tChar);
            Sleep(CONS_TIME);

            if(retval == QUEUE_ok)
                _PrintCreatedElement(tChar);
            else if(retval == QUEUE_empty)
                printf("_,");
            else if(retval == QUEUE_full)
                printf("x,");
            else{;}
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

    hSemaphore = CreateSemaphore(NULL, 0, QUEUE_SIZE, NULL);
    InitializeCriticalSection(&myCriticalSection);

    HANDLE hProd = CreateThread(NULL, 0, ThreadProducer, NULL, 0, NULL);
    HANDLE hCons = CreateThread(NULL, 0, ThreadConsumer, NULL, 0, NULL);

    WaitForSingleObject(hProd, INFINITE);
    WaitForSingleObject(hCons, INFINITE);

    CloseHandle(hProd);
    CloseHandle(hCons);
    CloseHandle(hSemaphore);

    DeleteCriticalSection(&myCriticalSection);

    return 0;
}

#endif // INC_PRODUCER_CONSUMER_QUEUE_H