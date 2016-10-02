/*
 *  The Frequent Words Problem
 *  We say that Pattern is a most frequent k-mer in Text if it maximizes Count(Text, Pattern) among all k-mers.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char    UINT8;
typedef unsigned int     UINT32;


#define MAX_ARRAY_SIZE  1000000
#define SCAN_GENOME     0
#define SCAN_KMER       1 


UINT8  DNA_SRC[MAX_ARRAY_SIZE];
UINT32 DNA_TOTAL_LENGTH = 0;
UINT32 KMER_LENGTH = 0;
UINT32 HASH_TABLE_LENGTH = 1;
UINT8  *pHASH_TABLE;

UINT32 alpha[256] = {0};

void printpattern(unsigned int key)
{
    unsigned int l;
    for(l=0;l<KMER_LENGTH;l++){
        if((key&0x3) == 0x0) printf("A");
        else if((key&0x3) == 0x1) printf("C");
        else if((key&0x3) == 0x2) printf("G");
        else if((key&0x3) == 0x3) printf("T");
        key>>=2;
    }  
}


UINT32 gen_hash_key(unsigned char *p,int len)
{
    unsigned int key = 0;
    unsigned int i=0;
    unsigned int v;
    
    for(i=0;i<len;i++){        
        v = (unsigned int)alpha[p[i]];        
        key |= (v) << (2*i);
    }
    return key;
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
            phase = SCAN_KMER;
            continue;
        }
        
        if( phase == SCAN_GENOME){
            if( (c == 'G') || (c == 'C') || (c=='A') || (c=='T'))
                src[src_cnt++] = c;
        }else{
            KMER_LENGTH *= 10;
            KMER_LENGTH  += c-'0';
        }                       
    }while(1);

    fclose (file);
    
    DNA_TOTAL_LENGTH = src_cnt;
    
    for(i=0;i<KMER_LENGTH;i++)
        HASH_TABLE_LENGTH *= 4;
    
    
}
 
 
void main()
{
    UINT32 i,j,key,subkey;
    UINT32 match_cnt = 0,max_cnt=0;
    read_test_data("dataset_2_10.txt",DNA_SRC,MAX_ARRAY_SIZE);
    
    // Init hash index.
    alpha['A'] = 0;
    alpha['C'] = 1;
    alpha['G'] = 2;
    alpha['T'] = 3;
    
    //Init hash table.
    pHASH_TABLE = malloc(HASH_TABLE_LENGTH);
    memset(pHASH_TABLE,0,HASH_TABLE_LENGTH);
    
    for(i=0;i<(DNA_TOTAL_LENGTH-KMER_LENGTH);i++)
    {
        key = gen_hash_key(DNA_SRC+i,KMER_LENGTH);
        match_cnt = 0;
        if(pHASH_TABLE[key]==0){
            for(j=i;j<(DNA_TOTAL_LENGTH-KMER_LENGTH);j++)
            {
                subkey = gen_hash_key(DNA_SRC+j,KMER_LENGTH);
                if(subkey==key)
                    match_cnt++;
            }
            pHASH_TABLE[key] = match_cnt;
            max_cnt = (match_cnt>max_cnt)?match_cnt:max_cnt;
        }                
    }

    for(i=0;i<HASH_TABLE_LENGTH;i++)
        if(pHASH_TABLE[i] == max_cnt){
            printpattern(i);
            printf(" ");              
        }
            
}