/*
 * Code Challenge: Implement PatternCount (reproduced below).
 *   Input: Strings Text and Pattern.
 *   Output: Count(Text, Pattern).
 *
 */
#include <stdio.h>

typedef unsigned char    UINT8;
typedef unsigned int     UINT32;


#define MAX_ARRAY_SIZE   1000000
#define MAX_PATTERN_SIZE 16
#define SCAN_GENOME      0
#define SCAN_PATTEN      1 

UINT8  DNA_SRC[MAX_ARRAY_SIZE];
UINT32 DNA_TOTAL_LENGTH;
UINT8  DNA_Pattern[MAX_PATTERN_SIZE];
UINT32 PATTERN_TOTAL_LENGTH;
 
void read_test_data (const char* file_name,UINT8 *src,UINT8 *pattern ,int maxsize) 
{
    unsigned char c;
    unsigned int phase = SCAN_GENOME;
    FILE* file = fopen (file_name, "r");
    if (!file) return;

    unsigned char i = 0;
    int src_cnt = 0, pattern_cnt=0;

    do
    {
        c = fgetc(file);    
        if( feof(file) )
        {
           break ;
        }        
        if(0xa==c){
            phase = SCAN_PATTEN;
            continue;
        }
        
        if( phase == SCAN_GENOME){
            if( (c == 'G') || (c == 'C') || (c=='A') || (c=='T'))
                src[src_cnt++] = c;
        }else{
            if( (c == 'G') || (c == 'C') || (c=='A') || (c=='T'))
                pattern[pattern_cnt++] = c;
        }                       
    }while(1);

    fclose (file);
    
    DNA_TOTAL_LENGTH = src_cnt;
    PATTERN_TOTAL_LENGTH = pattern_cnt;
}
 
 
void main()
{
    UINT32 i,j;
    UINT32 match_cnt = 0;
    read_test_data("dataset_2_7.txt",DNA_SRC,DNA_Pattern,MAX_ARRAY_SIZE);
    for(i=0;i<=(DNA_TOTAL_LENGTH-PATTERN_TOTAL_LENGTH);i++)
        if(!memcmp(DNA_Pattern,DNA_SRC+i,PATTERN_TOTAL_LENGTH))
            match_cnt++;            
}