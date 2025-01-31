#include <stdio.h>
#define NUMR 4
/**
 *  Time:        59     79     65     75
    Distance:   597   1234   1032   1328
 */
int scan(long time, long distance);

int main()
{
    /*
    int res = 1;
    int races[NUMR][2] = {{59,597},{79,1234},{65,1032},{75,1328}};
    for (short i=0; i<NUMR; i++)
    {
        res*= scan(races[i][0],races[i][1]);
    }
    */
    printf("%d ", scan(59796575,597123410321328) );
    //printf("%d ", scan(59,597) );
    return 0;
}

int scan(long time, long distance)
{

    long i = 10000000;
    long res = 0;
    while( i*2 < time)
    {
        if( (time-i)*i>distance )
        {
            return i;
        }
        i++;
    }
    res *=2;
    if( i*2 == time) res++;
    return res;
}