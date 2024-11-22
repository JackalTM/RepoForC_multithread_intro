#include "my_helper.h"
#ifdef INC_MY_HELPER_H

/********************************************************
 * @name    PrintProducer
 * @param   pProd Pointer to print structure 
 */
void InitCharArray(const char pCharSRC[], char pCharDST[])
{
    uint8_t i;
    for(i=0; i<15; i++)
    {
        if(pCharSRC[i] == '\0')
        {
            pCharDST[i] = '\0';
            break;
        }
        else    
        {   pCharDST[i] = pCharSRC[i]; } 
    }
    printf("-- Init str: %s \n", pCharDST);
}
//=======================================================

/********************************************************
 * @name    PrintProducer
 * @param   pProd Pointer to print structure 
 */
void PrintFormat(const char ARR_CHAR[], char data[], uint8_t len)
{
    printf("-- %s: \n", ARR_CHAR);
    char tChar, i;

    for(i=0; i<len; i++)
    {
        tChar = data[i];
        if(tChar != '\0')
        {
            putchar(' '); putchar(tChar);
        }
        else{;}
    }
    putchar('\n');
}
//=======================================================

#endif // INC_MY_HELPER_H