#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 256 // Maximum characters to read per line
#define CNT_MAPS 7
char filename[100] = "./inputs/d5.txt";
char map_names[CNT_MAPS][12] = {
    "soil",
    "fertilizer",
    "water",
    "light",
    "temperature",
    "humidity",
    "location"
    };

int seedCount = 0; // total number of seeds given
long long seeds[20]; // The limit is 20 seeds
short row_index = 0; // Consecutive numbers of rows that read the figures. This is used to define the x in map_rows[x][3] (below)
long long map_rows[250][3]; // The container of all map figure reads
short s_index = -1; // This the starting row_index of a map e.g. if map_limits[4] is [12,15] then the s_index is 12.
int map_limits[CNT_MAPS][2]; // Keeps starting/ending indices (row_index) of each map
int current_map = 0; // if the map name is found then we know the current map index
int parsing = 0; // Shows parsing state. It reads zero when no map name is found during line scanning.

/*
 * Scans the whole input and assign necessary values to variables
*/
short scan_the_input();
int find_seeds( char *line );
int read_line( char *line );
void parse_map_rows( char *line );
void append_limits();
void find_the_min();
long long get_min( long long source);
long long reverse_scan(long long dest );
short does_seed_exist(long long seed );


int main() 
{
    if(scan_the_input())
    {
        //find_the_min();
        reverse_scan(0);
        return 0;
    }
    return 1;
    
}

short scan_the_input()
{
    FILE *file;
    char line[MAX_LINE_LENGTH];
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 0;
    }
    while (fgets(line, sizeof(line), file) != NULL) 
    {
        if (seedCount == 0)
        {
            find_seeds( line );
        }
        else
        {
            read_line( line );
        }
    }
    append_limits();     // the last map's limits
    fclose(file);
    return 1;
}
int read_line( char *line )
{
    char *position = NULL;
    if( strlen(line) < 2)
    {
        if(row_index > 0) 
        {
            // it means we already found some map figures
            // and came a blank row which means end of this map
            append_limits();
            current_map++;  
        }
        parsing = 0;
        return 0;
    }
    if(parsing)
    {
        parse_map_rows( line );
        return 1;
    }
    else
    {
        position = strstr(line, map_names[current_map]);
    }
    // Check if the line has a map name
    if (position == NULL) 
    {
        return 0;
    }
    else
    {
        // Map is found then let the parsing begin
        s_index=-1;
        parsing = 1;
        return 1;
    }
}
int find_seeds( char *line )
{
    long long seed;
    char *token;
    // Check if the line starts with "seeds:"
    if (strncmp(line, "seeds:", 6) == 0) 
    {
        // Tokenize the line (split it into words) using spaces as delimiter
        token = strtok(line + 6, " "); // Skip the "seeds:" prefix
        while (token != NULL) {
            // Check if token is a digit, ignoring leading whitespace
             int i = 0;
             while(isspace(token[i]))
             {
                 i++;
             }
            if(isdigit(token[i]))
            {
                // Convert the token to an integer
                seed = atoll(token);
                seeds[seedCount++] = seed;
            }
            token = strtok(NULL, " ");
        }
        return 1;
    }
    return 0;
}
void parse_map_rows( char *line )
{
    char *token;
    long long figure;
    // Tokenize the line (split it into words) using spaces as delimiter
    token = strtok(line, " ");
    short i = 0;
    long long tokens[3];
    if(s_index == -1 ) s_index = row_index;
    while (token != NULL) 
    {
        figure = atoll(token);
        tokens[i] = figure;
        token = strtok(NULL, " ");
        i++;
    }
    // Append map_rows with the read values
    map_rows[row_index][0] = tokens[0];
    map_rows[row_index][1] = tokens[1];
    map_rows[row_index][2] = tokens[2];
    row_index++;
};
void append_limits()
{
    map_limits[current_map][0] = s_index;
    map_limits[current_map][1] = row_index-1;
}
void find_the_min()
{
    long long location = 0;
    long long result = 9000000000;
    for(short y=0; y<seedCount; y++)
    {
        location = get_min(seeds[y]);
        if( result > location ) 
        {
            result = location;
        }
    }
    printf("Min %lli\n",result);
}
long long get_min( long long source)
{
    short i = 0;
    short t = 0;
    long long lmax = 0;
    long long lmin = 0;
    for(short t = 0; t<7; t++) // for each map
    {
        for(short z = map_limits[t][0]; z <= map_limits[t][1]; z++) // for each row
        {   /*
            map_rows[0][0] // destination
            map_rows[0][1] // source
            map_rows[0][2] // range
            */
           lmin = map_rows[z][1];
           lmax = map_rows[z][2] + map_rows[z][1];
           if(source >= lmin && source < lmax)
           {
                source = map_rows[z][0] + (source - map_rows[z][1]);
                break;
           }
        }
    }
    return source;
}
long long reverse_scan(long long dest )
{
    short found = 0;
    long long step = 0;
    long long start = dest;
    while( found == 0 )
    {
        dest = start + step;
        printf("%lli x\n", dest);
        short i = 0;
        short t = 0;
        long long lmax = 0;
        long long lmin = 0;
        for(short t = 6; t > -1; t--) // for each map
        {
            for(short z = map_limits[t][0]; z <= map_limits[t][1]; z++) // for each row
            {   /*
                map_rows[0][0] // destination
                map_rows[0][1] // source
                map_rows[0][2] // range
                */
               lmin = map_rows[z][0];
               lmax = map_rows[z][2] + map_rows[z][0];
               if(dest >= lmin && dest < lmax)
               {
                    dest = map_rows[z][1] + (dest - map_rows[z][0]);
                    break;
               }
            }
        }
        if(does_seed_exist( dest ))
        {
            printf("Location found: %lli", start + step);
            found = 1;
        }
        else
        {
            step++;
        }
    }
}

short does_seed_exist(long long seek )
{
    for(short i = 0; i < 20; i=i+2)
    {
        long long lmax = 0;
        long long lmin = 0;
        lmin = seeds[i];
        lmax = seeds[i] + seeds[i+1];
        if( seek >= lmin && seek < lmax)
        {
            printf("Seed is: %lli\n",seek);
            return 1;
        }
    }
    return 0;
}