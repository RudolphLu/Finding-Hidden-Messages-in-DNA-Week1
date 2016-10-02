/*
 *  The reverse complement of a string Pattern
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char    UINT8;
typedef int              INT32;
typedef unsigned int     UINT32;


#define MAX_ARRAY_SIZE  1000000
#define SCAN_GENOME     0

UINT8  DNA_SRC[MAX_ARRAY_SIZE];
UINT32 DNA_TOTAL_LENGTH = 0;


void print_reverse_pattern(UINT8 *src)
{
    INT32 i;
    for(i=DNA_TOTAL_LENGTH-1;i>=0;i--){
        if(DNA_SRC[i] == 'A')    printf("T");
        if(DNA_SRC[i] == 'T')    printf("A");
        if(DNA_SRC[i] == 'C')    printf("G");
        if(DNA_SRC[i] == 'G')    printf("C");                        
    }
}


void read_test_data (const char* file_name,UINT8 *src,int maxsize) 
{
    UINT8 c;
    UINT32 phase = SCAN_GENOME;
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
          
        if((0xa==c) || (0xd==c)){
            break;
        }
        
        if( phase == SCAN_GENOME){
            if( (c == 'G') || (c == 'C') || (c=='A') || (c=='T'))
                src[src_cnt++] = c;
        }                 
    }while(1);

    fclose (file);
    
    DNA_TOTAL_LENGTH = src_cnt;
    
}
 
 
void main()
{
    read_test_data("dataset_3_2.txt",DNA_SRC,MAX_ARRAY_SIZE);
    print_reverse_pattern(DNA_SRC);
}