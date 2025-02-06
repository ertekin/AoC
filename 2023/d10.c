#include <stdio.h>
#define COLS 140
#define ROWS 140
/**
 * char* in ['U','D','L','R']
 */
void trace(char* in, char* board, short* offset);
short scan_input(char* board, short* os);
short scan_dots(char* board, short* path);
short is_inside(char* board, short* path, short index);
short is_in_path(short* path, short index);

int main()
{
    char board[(COLS*ROWS)];
    short path[COLS*100]; // tum gezilen noktalarin koordinatlari
    short offset = 0;
    if(scan_input(board, &offset) == 1) return 1;
    short sAddr = offset;
    char direction = 'U';
         offset   += COLS;

    path[0] = offset; // yolun ilk adimi S'den bir sonraki koordinat

    int steps = 1;
    while( board[offset] != 83 && steps<COLS*ROWS)
    {
        trace(&direction, board, &offset);
        if(offset == -1)
        {
            printf("Failed after %d steps.\n", steps);
            return 0;
        }
        path[steps] = offset;
        steps++;
    }
    if(direction == 'U') board[sAddr] = '|';
    if(direction == 'R') board[sAddr] = 'F';
    if(direction == 'L') board[sAddr] = '7';
    path[steps] = -1; // mark for the last step
    printf("Success after %d steps. The farthest point is %d. \n", steps, steps/2);
    printf("There are %d tiles inside the loop. \n", scan_dots(board,path) );
    return 0;
}

void trace(char* in, char* brd, short* os)
{
    char x = *(brd+*os);
    switch (*in)
    {
    case 'U':
        if( x == '|')
        {
            *os+=COLS;
        } else if ( x == 'L')
        {
            *os+=1;
            *in = 'L';
        } else if ( x == 'J')
        {
            *os-=1;
            *in = 'R';
        } else 
        {
            *os = -1;
        }
        break;
    case 'D':
        if( x == '|')
        {
            *os-=COLS;
        } else if ( x == 'F')
        {
            *os+=1;
            *in = 'L';
        } else if ( x == '7')
        {
            *os-=1;
            *in = 'R';
        } else 
        {
            *os = -1;
        }
        break;
    case 'L':
        if( x == '-')
        {
            *os+=1;
        } else if ( x == '7')
        {
            *os+=COLS;
            *in = 'U';
        } else if ( x == 'J')
        {
            *os-=COLS;
            *in = 'D';
        } else 
        {
            *os = -1;
        }
        break;
    case 'R':
        if( x == '-')
        {
            *os-=1;
        } else if ( x == 'F')
        {
            *os+=COLS;
            *in = 'U';
        } else if ( x == 'L')
        {
            *os-=COLS;
            *in = 'D';
        } else 
        {
            *os = -1;
        }
        break;
    }
}


short scan_input(char* board, short* os)
{
    FILE* fp = fopen("./inputs/d10.txt", "r");
    if (!fp) { 
        perror("Error opening file");
        return 1;
    }
    int ch;
    short i = 0;
    while ((ch = fgetc(fp)) != EOF) 
    {
        if(ch == 10) continue; // new line
        if(ch == 83) *os = i;  // if it's an S
        board[i] = ch;
        i++;
    }
    fclose(fp);
}

short scan_dots(char* board, short* path)
{
    short cnt = 0;
    for( short i=COLS+1; i<COLS*(ROWS-1); i++ )
    {
        //  D O N T   L O O K   A T    //
        //  Leftmost   || rightmost    //
        if( i%COLS == 0 || (i+1)%COLS == 0 ) continue;
        if( !is_in_path(path, i) ) 
        {
            if( is_inside(board, path, i) ) cnt++;
        }
    }
    return cnt;
}

short is_inside(char* board, short* path, short index)
{
    // check upward
    short t = index;
    short cnt = 0;
    short inc = 1;
    while(t >= 0)
    {
        t-=COLS;
        inc = 1;
        if( board[t] == '|' || board[t] == '.' ) continue;
        if( board[t] == '7' || board[t] == 'J' ) inc=2;
        if( is_in_path(path, t) ) cnt+=inc;
    }
    if( cnt%2 == 0 ) return 0;

    // check downward
    short bottom = COLS * ROWS;
    t = index;
    cnt = 0;
    while(t <= bottom )
    {
        t+=COLS;
        inc = 1;
        if( board[t] == '|' || board[t] == '.' ) continue;
        if( board[t] == '7' || board[t] == 'J' ) inc=2;
        if( is_in_path(path, t) ) cnt+=inc;
    }
    if( cnt%2 == 0 ) return 0;


    // check leftward
    t = index;
    cnt = 0;
    short leftB = index - (index%COLS);
    while(t > leftB)
    {
        t--;
        inc = 1;
        if( board[t] == '-' || board[t] == '.' ) continue;
        if( board[t] == '7' || board[t] == 'F' ) inc=2;
        if( is_in_path(path, t) ) cnt+=inc;
    }
    if( cnt%2 == 0 ) return 0;

    // check rightward
    t = index;
    cnt = 0;
    short rightB = COLS * ( (index/COLS)+1 )-1;
    while(t < rightB)
    {
        t++;
        inc = 1;
        if( board[t] == '-' || board[t] == '.' ) continue;
        if( board[t] == '7' || board[t] == 'F' ) inc=2;
        if( is_in_path(path, t) ) cnt+=inc;
    }
    if( cnt%2 == 0 ) return 0;

    return 1;
}

short is_in_path(short* path, short index)
{
    short i = 0;
    while( path[i] != -1 )
    {
        if( index == path[i] ) return 1;
        i++;
    }
    return 0;
}