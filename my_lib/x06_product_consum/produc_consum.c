#include "produc_consum.h"
#ifdef INC_PRODUCTION_COMSUMPTION_H

/*******************************************************
 * Initialized variables
 */
struct producer_t   _producer;
struct consmer_t    _consumer;
struct commomData_t _commonData;
uint8_t nCalls;
//=======================================================

/********************************************************
 * Operation system objects
 */
HANDLE hSemaphore;

HANDLE hSema_DataWritten;
HANDLE hSema_DataRead;
//=======================================================

/********************************************************
 * @name    Producer
 * @brief   Thread Producer 
 * @param   pProd Pointer to print structure 
 */
DWORD WINAPI Producer(LPVOID pParams)
{
    struct commomData_t* pCommon = (struct commomData_t*)pParams;
    char tChar, i, letter;

    while(TRUE)
    {
        WaitForSingleObject(hSema_DataRead, INFINITE);

        Sleep(PRODUCER_TIME);
        if(letter == 'A'){ letter = 'a'; }
        else{ letter = 'A'; }                    

        for(i=0; i<16; i++)
        {
            tChar = letter + i;

            _producer.arrChar[i] = tChar;
            pCommon->arrChar[i] = tChar;

            _producer.len = i;
            pCommon->len = i;
        }
        // After procesing data Semaphore is relised, it is like public flag
        // Mutex behave like private flag
        ReleaseSemaphore(hSema_DataWritten, 1, NULL);
        nCalls++;
    }
    return 0;
}
//=======================================================
/********************************************************
 * @name    PrintProducer
 * @brief   Thread Producer 
 * @param   pProd Pointer to print structure 
 */
DWORD WINAPI Consumer(LPVOID pParams)
{
    struct commomData_t* pCommon = (struct commomData_t*)pParams;
    char tChar, i;

    while(TRUE)
    {
        // Wait for semaphore, it can be shaed between multiple functions
        WaitForSingleObject(hSema_DataWritten, INFINITE);

        Sleep(CONSUMER_TIME);
        printf("Call n= %d  \n", (uint16_t)nCalls);
        PrintFormat("Common", (char*)pCommon->arrChar, pCommon->len);
        for(i=0; i<16; i++)
        {
            tChar = pCommon->arrChar[i];
            _consumer.arrChar[i] = tChar;

            pCommon->len = i;
            _consumer.len = i;
        }
        PrintFormat("Consumer", (char*)_consumer.arrChar, _consumer.len);
        ReleaseSemaphore(hSema_DataRead, 1, NULL);
        nCalls++;
    }
    return 0;
}
//=======================================================

/********************************************************
 * @name    ThreadControl
 * @brief   Thread kill control
 * @param   pProd Pointer to print structure 
 */
DWORD WINAPI ThreadControl(LPVOID pParams)
{
    struct threadsHandlers_t* pHandlers = pParams; 

    while(nCalls < 10)
    {   Sleep(100); }

    CloseHandle(pHandlers->hProducer);
    CloseHandle(pHandlers->hConsumer);

    return 0;
}

int CALL_ProducerAndConsumer_test1(void)
{
    LPVOID arrPointers[2];
    nCalls = 0;

    hSemaphore = CreateSemaphore(NULL, 0, 1, NULL);

    hSema_DataRead = CreateSemaphore(NULL, 0, 1, NULL);
    hSema_DataWritten = CreateSemaphore(NULL, 0, 1, NULL);

    ReleaseSemaphore(hSema_DataRead, 1, NULL);

    HANDLE hControl;
    struct threadsHandlers_t myHandlers;
    
    hControl = CreateThread(NULL, 0, ThreadControl, &myHandlers, 0, NULL);
    myHandlers.hProducer = CreateThread(NULL, 0, Producer, &_commonData, 0, NULL);
    myHandlers.hConsumer = CreateThread(NULL, 0, Consumer, &_commonData, 0, NULL);

    WaitForSingleObject(hControl, INFINITE);
    WaitForSingleObject(myHandlers.hProducer, INFINITE);
    WaitForSingleObject(myHandlers.hConsumer, INFINITE);

    //CloseHandle(myHandlers.hProducer);
    //CloseHandle(myHandlers.hConsumer);
    CloseHandle(hControl);

    CloseHandle(hSemaphore);
    CloseHandle(hSema_DataRead);
    CloseHandle(hSema_DataWritten);
}

#endif // INC_PRODUCTION_COMSUMPTION_H