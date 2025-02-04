#include <stdio.h>
#include <stdlib.h>

#define NUM_ROWS 800
char filename[100] = "./inputs/d8.txt";

void get_dirs(char *line, char *dirs);
short scan_input(char *filename, char codes[NUM_ROWS][9], char *dirs);
void find(char letters[10][3], int ind, char tlc[NUM_ROWS][9], char dir);
short findAendings(char look[10][3],  char codes[NUM_ROWS][9]);
/**
 * Three letter code list
 * tlc[0] = "GLR"
 * tlc[1] = "LDM"
 * ...
 * tlc[769] = "PJP"
 */
char tlc[NUM_ROWS][9];
char directions[300];

int main()
{
    int noAs = 0;
    char dirL;
    char look[10][3];
    scan_input(filename, tlc, directions);
    noAs = findAendings(look, tlc);
    // part II was disappointing
    for(int i = 0; i<noAs; i++)
    {
        int dirC = 0;
        int cnt = 1;
        int cntZ = 0;
        while( cntZ < 3 )
        {
            if(directions[dirC] == '\0') dirC = 0;
            find( look, i, tlc, dirL);
            if(look[i][2] == 'Z')
            {
                printf("%d for %d\n", cnt,i);
                cntZ++;
            } 
            dirL = directions[dirC];
            cnt++;
            dirC++;
        }
    }
    

    /* 
     * This was part I
     * -----------------------------
    char look[3] = {'A','A','A'};
    int dirC = 0;
    while( look[0]!='Z' || look[1]!='Z' || look[2]!='Z' )
    {
        if(directions[dirC] == '\0') dirC = 0;
        dirL = directions[dirC];
        find(look , tlc, dirL);
        cnt++;
        dirC++;
    }
    printf("Count %d for %c%c%c\n",cnt, look[0],look[1],look[2]);
    * --------------------------------
    */
    return 0;
}

short findAendings(char look[10][3],  char codes[NUM_ROWS][9] )
{
    int noAs = 0;
    for(int i = 0; i<NUM_ROWS; i++)
    {
        if(codes[i][2] == 'A')
        {
            noAs++;
            look[(noAs-1)][0] = codes[i][0];
            look[(noAs-1)][1] = codes[i][1];
            look[(noAs-1)][2] = codes[i][2];
        }
    }
    return noAs;
}
void find(char letters[10][3], int ind, char tlc[NUM_ROWS][9], char dir)
{
    for( int i = 0; i < NUM_ROWS; i++ )
    {
        if( letters[ind][0] != tlc[i][0] ) continue;
        if( letters[ind][1] != tlc[i][1] ) continue;
        if( letters[ind][2] != tlc[i][2] ) continue;
        if( dir == 'L')
        {
            letters[ind][0] = tlc[i][3];
            letters[ind][1] = tlc[i][4];
            letters[ind][2] = tlc[i][5];
            break;
        }
        if( dir == 'R')
        {
            letters[ind][0] = tlc[i][6];
            letters[ind][1] = tlc[i][7];
            letters[ind][2] = tlc[i][8];
            break;
        }
    }
}
short scan_input(char *filename, char codes[NUM_ROWS][9], char *dirs)
{
    FILE *file;
    char line[300];
    int line_no = 0;
    file = fopen(filename, "r");
    if (file == NULL) 
    {
        perror("Error opening file");
        return 0;
    }

    while (fgets(line, sizeof(line), file) != NULL) 
    {
        if( line_no == 0 )
        {
            // assign directions
            int i = 0;
            do 
            {
                if( line[i] == '\n' ) line[i] = '\0';
                dirs[i] = line[i];
                i++;
            } 
            while ( line[i] != '\0');
            // burada i-1 kadar talimat bulunur

        }
        else if ( line_no > 1 )
        {
            codes[line_no-2][0] = line[0];
            codes[line_no-2][1] = line[1];
            codes[line_no-2][2] = line[2];
            codes[line_no-2][3] = line[7];
            codes[line_no-2][4] = line[8];
            codes[line_no-2][5] = line[9];
            codes[line_no-2][6] = line[12];
            codes[line_no-2][7] = line[13];
            codes[line_no-2][8] = line[14];
        }
        line_no++;
    }
    fclose(file);
    return 1;
}