#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_ROWS 1000       // number of rows of the input
#define MAX_LINE_LENGTH 12  // Maximum characters to read per line
char filename[100] = "./inputs/d7.txt";
/**
 * Bir eldeki karların per durumuna göre sırasını belirler
 * hexadecimal string oluşturup onu ulong'a dönüştürüp döner
 */
unsigned long resv_cards(char* cards);
/**
 * Oyundaki kart harflarını hex harflerine dönüştürür
 *  A --> E
 *  K --> D
 *  Q --> C
 *  J --> B (joker ise 1 yapılır)
 *  T --> A
 */
char conv_letter(char let);
/**
 * Verilen hex string'ini unsigned long 
 * olarak döndürür. Örnek 31EDED --> 3272173
 */
unsigned long hex2l(const char *hexStr);
/**
 * Kaynak dosyayı açar satır satır okur ve
 * read_line() metodunu besler
 */
short scan_the_input(void);
/**
 * Gelen satırdaki kartları okur ve resv_cards() ile
 * karşılık gelen büyük puanı hesaplar ve harr[] dizisini oluşturur
 */
short read_line( char* line, int no );
/**
 * read_line() ile oluşturulan harr[] dizisini
 * harr[].rank değerine göre küçükten büyüğe sıralar
 * en düşük puan sıfır (0)
 * en büyük puanı olan 999 indeksine sahip olur.
 */
short sort_harr( void );

typedef struct
{
    unsigned long rank;
    int bid;
} d7_hands;
// Hands array
d7_hands harr[NUM_ROWS];


int main()
{
    unsigned long total = 0;
    scan_the_input();
    sort_harr();
    for(int i=0; i<NUM_ROWS; i++)
    {
        total += harr[i].bid * (i+1);
    }
    printf("Total %lu\n", total);
    return 0;
}


unsigned long resv_cards(char* cards)
{

    char ref;
    short count, fdigit, total;
    char copy_hand[5] = "00000";
    char result[6] = "000000";
    short no_jok = 0;
    // initialize total
    total = 0;

    char fdigits[26];
    fdigits[25] = '7'; // five of a kind
    fdigits[17] = '6'; // for of a kind
    fdigits[13] = '5'; // full house
    fdigits[11] = '4'; // three of a kind
    fdigits[9]  = '3'; // two pair
    fdigits[7]  = '2'; // one pair
    fdigits[5]  = '1'; // high card

    for(short i=0; i<5; i++)
    {
        ref = cards[i];
        result[(i+1)] = conv_letter(ref);
        if( copy_hand[i] == '-') continue;
        count = 1;
        for(short y=i+1; y<5; y++)
        {
            if( ref == cards[y])
            {
                copy_hand[y] = '-';
                count++;
            }
        }
        if( ref == 'J' )
        {
            no_jok = count;
        } 
        total += count*count;
    }
    result[0] = fdigits[total];
    /**
     * ------------------------
     * --- Joker düzeltmesi ---
     * ------------------------
     */
    if( no_jok == 1 )
    {
        if( result[0] == '6' ) result[0] = '7';
        if( result[0] == '4' ) result[0] = '6';
        if( result[0] == '3' ) result[0] = '5';
        if( result[0] == '2' ) result[0] = '4';
        if( result[0] == '1' ) result[0] = '2';
    }
    if( no_jok == 2 )
    {
        if( result[0] == '5' ) result[0] = '7';
        if( result[0] == '3' ) result[0] = '6';
        if( result[0] == '2' ) result[0] = '4';
    }
    if( no_jok == 3 )
    {
        if( result[0] == '5' ) result[0] = '7';
        if( result[0] == '4' ) result[0] = '6';
    }
    if( no_jok == 4 ) result[0] = '7';
    /**
     * ------------------------
     * ---  Düzeltme sonu   ---
     * ------------------------
     */

    return hex2l(result);
}

char conv_letter(char let)
{
    if(let == 'A')
    {
        return 'E';
    } 
    else if ( let == 'K' )
    {
        return 'D';
    }
    else if ( let == 'Q' )
    {
        return 'C';
    }
    else if ( let == 'J' )
    {
        // return 'B'; revised for part 2
        return '1';
    }
    else if ( let == 'T' )
    {
        return 'A';
    }
    else
    {
        return let;
    }
}

unsigned long hex2l(const char *hexStr) 
{
    // Remove the "0x" prefix if present
    const char *str1 = hexStr;
    if(strncmp(str1, "0x", 2) == 0)
    {
        str1 += 2;
    }

    // Convert to unsigned long integers
    char *endptr1;
    unsigned long num1 = strtoul(str1, &endptr1, 16);

    // Error checking for strtoul (only for invalid characters)
    if (*endptr1 != '\0')
    {
         printf("Invalid Hex String format %s\n", str1);
         return 0; //Return 0 since we do not want to process if its invalid
    }
    return num1;
}

short scan_the_input()
{
    FILE *file;
    char line[MAX_LINE_LENGTH];
    int line_no = 0;
    file = fopen(filename, "r");
    if (file == NULL) 
    {
        perror("Error opening file");
        return 0;
    }

    while (fgets(line, sizeof(line), file) != NULL) 
    {
        read_line(line, line_no);
        line_no++;
    }
    fclose(file);
    return 1;
}

short read_line( char* line, int no )
{
    char temp_string[6] = "00000\0";
    short counter = 0;
    for(short i=0; i<12; i++)
    {
        temp_string[counter] = (char)line[i];
        if( line[i] == ' ' )
        {
            temp_string[counter] = '\0';
            harr[no].rank = resv_cards( temp_string );
            counter=0; 
            continue;
        }
        if( line[i] == '\n' )
        {
            temp_string[counter] = '\0';
            harr[no].bid = atoi( temp_string );
            counter=0; 
            return 1;
        }
        counter++;
    }
    return 0;
}

short sort_harr( void )
{
    int offset = NUM_ROWS;
    d7_hands tempo;
    while( offset>1)
    {
        for(int i=1; i<offset; i++)
        {
            if( harr[i].rank < harr[(i-1)].rank )
            {
                tempo.rank = harr[(i-1)].rank;
                tempo.bid  = harr[(i-1)].bid;
                harr[(i-1)].rank = harr[i].rank;
                harr[(i-1)].bid  = harr[i].bid;
                harr[i].rank = tempo.rank;
                harr[i].bid  = tempo.bid;
            }
        }
        offset--;
    }
}