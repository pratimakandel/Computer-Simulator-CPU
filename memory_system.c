#include <stdio.h>
#include "bit_functions.h"
#include "memory.h"
#include "decoder.h"




void memory_store(int address, unsigned char value){
	int low_half = address &0x1F;
	int up_half = (address>>5)&0x1F;
	unsigned int lh = decoder(low_half);
	unsigned int uh = decoder(up_half);
	mem_put(lh, uh, value);
	//printf("%d", mem_get(lh,uh));
}
	
void memory_store_word(int address, unsigned int value){
	unsigned char b1 = value&0xFF;
	unsigned char b2 = (value>>8)&0xFF;
	unsigned char b3 = (value>>16)&0xFF;
	unsigned char b4 = (value>>24)&0xFF;
	memory_store(address, b1);
	memory_store(address + 1, b2);
	memory_store(address + 2, b3);
	memory_store(address + 3, b4);
	
	
}

unsigned char memory_fetch(int address){
	int low_half = address &0x1F;
	int up_half = (address>>5)&0x1F;
	unsigned int lh = decoder(low_half);
	unsigned int uh = decoder(up_half);
	return mem_get(lh, uh);
}
unsigned int memory_fetch_word(int address){
	unsigned char byte1 = memory_fetch(address);
	unsigned char b2 = memory_fetch(address+1);
	unsigned char b3 = memory_fetch(address+2);
	unsigned char b4 = memory_fetch(address+3);
	unsigned int w = (b4<<24) | (b3<<16) | (b2<<8) | byte1;
	return w;
}	

void memory_fill(int start_address, unsigned char value, int num_bytes){
	for(int i =0; i<num_bytes; i++){
		memory_store(start_address+i,value);
	}
}
void memory_dump(int start_address, int num_bytes){
	int start_boundary = start_address - (start_address % 8);
    int boundary_bytes = num_bytes + (start_address - start_boundary);
    printf("start_boundary: %d 0x%04x\n", start_boundary, start_boundary);
    for (int i = start_boundary; i < start_boundary+boundary_bytes; i+=8) {
        printf("0x%04x (0d%04d) 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x \n", 
               i, i,
               memory_fetch(i),   memory_fetch(i+1), memory_fetch(i+2), memory_fetch(i+3),
               memory_fetch(i+4), memory_fetch(i+5), memory_fetch(i+6), memory_fetch(i+7));
    }
}
void load_memory(char *filename){
	FILE *fp=fopen(filename , "r");
	int value;
	int address;
	fscanf(fp, "%x", &address);
	int i =0;
	while(fscanf(fp, "%x", &value) != EOF){
		memory_store_word(address + i, value);
		i+=4;
	}
}
		
	
