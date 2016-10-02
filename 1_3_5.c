/*
 *  Code Challenge: Solve the Pattern Matching Problem.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char    UINT8;
typedef int              INT32;
typedef unsigned int     UINT32;


#define MAX_ARRAY_SIZE   1000000
#define MAX_PATTERN_SIZE 256
#define SCAN_GENOME      0
#define SCAN_PATTERN     1

UINT8  DNA_SRC[MAX_ARRAY_SIZE];
UINT32 DNA_TOTAL_LENGTH = 0;
UINT8  DNA_Pattern[MAX_PATTERN_SIZE];
UINT32 PATTERN_TOTAL_LENGTH;


void read_test_data (const char* file_name,UINT8 *src,UINT8 *pattern ,int maxsize) 
{
    unsigned char c;
    unsigned int phase = SCAN_PATTERN;
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
        if(0xa==c || 0xd == c){
            phase = SCAN_GENOME;
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
    UINT32 i=0;
    read_test_data("dataset_3_5.txt",DNA_SRC,DNA_Pattern,MAX_ARRAY_SIZE);
    
    for(i=0;i<=DNA_TOTAL_LENGTH-PATTERN_TOTAL_LENGTH;i++)
        if(!memcmp(DNA_Pattern,DNA_SRC+i,PATTERN_TOTAL_LENGTH))
            printf("%d ",i);
    
}