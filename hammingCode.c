#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int hammingCode(int data[], int hamCode[], int n)
{
    int i, r = 0, j = -1;
    for(i = 1; i <= n + r; ++i)
    {
        if(i == pow(2, r))
            hamCode[i] = 0, ++r;
        else
            hamCode[i] = data[++j];
    }
    return r;
}
int findParity(int hamCode[], int end)
{
    int i, j, xor, t = 0, errpos = 0;
    for(i = 1; i < end; ++i)
    {
        xor = hamCode[i];
        if(i == pow(2, t))
        {
            for(j = i + 1; j <= end; ++j)
                if((i & j) != 0)
                    xor ^= hamCode[j];
            ++t;
            hamCode[i] = xor;
            if(xor)
                errpos += i;
        }
    }
    return errpos;
}

int checkErrorType(int errpos, int r)
{    
    return !(errpos & (errpos - 1));
}

int main()
{
    int n, data[50], r, hamCode[50], i;
    printf("Enter the number of input bits: ");
    scanf("%d", &n);
    printf("Enter bits: ");
    for(i = 0; i < n; ++i)
        scanf("%d", &data[i]);
    
    r = hammingCode(data, hamCode, n);
    printf("redundant bits : %d\n", r);
    findParity(hamCode, n + r);
    
    printf("Transmitted data: ");
    for(i = 1; i <= n + r; ++i)
        printf("%d ", hamCode[i]);
    printf("\n");
    
    int ch, pos;
    printf("\nTransmission : \n");
    printf("Do you want to corrupt the data?\n1. Yes\n2. No\nChoice : ");
    scanf("%d", &ch);
    if(ch == 1)
    {
        printf("Enter the position to corrupt : ");
        scanf("%d", &pos);
        hamCode[pos] = 1 - hamCode[pos];
    }

    printf("\nReceived data: ");
    for(i = 1; i <= n + r; ++i)
        printf("%d ", hamCode[i]);
    printf("\n");
    
    printf("Error check : ");
    int errpos = findParity(hamCode, n + r);
    if(errpos)
    {
        if(checkErrorType(errpos, r)) // modify
            printf("Parity bit at position %d is corrupted but data is fine!\n", errpos);
        else
        {
            printf("Data bit at position %d is corrupted!\n", errpos);
            hamCode[errpos] = 1 - hamCode[errpos];
            printf("Correct data bits with new parity bits : ");
            for(i = 1; i <= n + r; ++i)
                printf("%d ", hamCode[i]);
        }
    } 
    else 
        printf("No error!");
    return 0;
}
