#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "decoder.h"
#include "memory.h"
#include "memory_system.h"
#include "bit_functions.h"
#include "cpu.h"

int main(int argc, char **argv) {
	//load_memory("mem1.txt");
	//set_reg(PC, 816);
	//step_n(65);
	//memory_dump(0x300, 100);
	//show_regs();
	
    while (1) {
		char cmd[100], file_name[100];
		int num, num1;
		printf("Enter cmd: ");
		scanf("%s", cmd);
		printf("%s\n", cmd);
		if (strcmp(cmd, "set_reg") == 0) {
			printf("Enter reg: ");
			scanf("%d", &num);
			printf("Ender reg value: ");
			scanf("%d", &num1);
			set_reg(num, num1);
		}
		else if (strcmp(cmd, "dump") == 0) {
			printf("Enter address: ");
			scanf("%x", &num);
			printf("Enter num bytes: ");
			scanf("%d", &num1);
			memory_dump(num, num1); 
		}
		else if (strcmp(cmd, "regs") == 0) {
			show_regs();
		}
		else if (strcmp(cmd, "step") == 0) {
			step();
		}
		else if (strcmp(cmd, "step_n") == 0) {
			printf("Enter num of steps: ");
			scanf("%d", &num);
			step_n(num);
		}
		else if (strcmp(cmd, "load") == 0) {
			printf("Enter file name: ");
			scanf("%s", file_name);
			load_memory(file_name);
		}
		else {
			printf("invalid cmd\n");
		}		
	}
	
	
	

}

