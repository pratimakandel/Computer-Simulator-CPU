#include <stdio.h>
#include "bit_functions.h"

unsigned int mem[32][32]; 


unsigned char mem_get(unsigned int row_selected, unsigned int col_selected){
	return mem[bit_find(row_selected)][bit_find(col_selected)];
}

void mem_put(unsigned int row_selected, unsigned int col_selected, unsigned char b){
		 mem[bit_find(row_selected)][bit_find(col_selected)] = b;
	 }
