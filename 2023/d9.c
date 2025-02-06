#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 180

long scan_input(char l);
void make_array(char *arrin, long *arrout);
long predict(long* arr, char d);

int main(int argc, char* argv[])
{
    char letter = 'F';
    if(argv[1][0] == 'B') letter = 'B';
    printf("%li \n", scan_input(letter));
    return 0;
}

long scan_input(char l)
{
    char filename[100] = "./inputs/d9.txt";
    char buffer[BUFFER_SIZE];
    long arrint[30];
    int line_no = 0;
    long result = 0;
    FILE *fp;
    fp = fopen(filename,"r");
    if( fp == NULL) return 0;
    while (fgets(buffer, sizeof(buffer), fp) != NULL )
    {
        short cnt = 0;
        make_array(buffer, arrint);
        result += predict(arrint, l);
    }
    return result;
}

void make_array(char *arrin, long *arrout)
{
    short arrc = 1;
    short tempc = 0;
    char temp[16];
    for(int i = 0; i<BUFFER_SIZE; i++)
    {
        temp[tempc] = arrin[i];
        if( arrin[i] == 32 )
        {
            temp[tempc] = '\0';
            arrout[arrc] = atoi(temp);
            tempc = -1;
            arrc++;
        }
        if( arrin[i] == '\n' || arrin[i] == EOF )
        {
            temp[tempc] = '\0';
            arrout[arrc] = atoi(temp);
            arrout[0] = arrc;
            break;
        }
        tempc++;
    }
}

long predict(long* arr, char d)
{
    short go = 1;
    short sw = 1;
    short i;
    long fark = 0;
    long preB = arr[1];
    long preF = 0;
    while(go == 1 && arr[0] > 1)
    {
        go = 0;
        for( i=1; i < arr[0]; i++ )
        {
            fark = arr[(i+1)] - arr[i];
            arr[i] = fark;
            if(fark != 0) go = 1;
        }
        arr[0] = i-1;
        preF += arr[i];
        if(sw == 0)
        {
            preB += arr[1];
            sw = 1;
        }
        else
        {
            preB -= arr[1];
            sw = 0;
        }
    }
    if( d == 'B') return preB; // Backward prediction
    return preF;               // Forward prediction
}