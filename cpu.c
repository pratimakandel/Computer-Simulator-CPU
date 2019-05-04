#include "bit_functions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "decoder.h"
#include "memory.h"
#include "memory_system.h"
#include "cpu.h"

int registers[16];
int cpsr;

void set_reg(int reg, int value)
{
	registers[reg] = value;
}
int get_reg(int reg)
{
	return registers[reg];
}
int get_cpsr()
{
	return cpsr;
}

void show_regs()
{
	for (int i = 0; i < 15; i++)
	{
		printf("register[%02d]: %x\n", i, get_reg(i));
	}
	printf("register[%02d]: %x\n", PC, get_reg(PC));
}

void step()
{
	unsigned int instruction = memory_fetch_word(registers[15]);
	unsigned int opc = instruction >> 24;
	unsigned int address;
	unsigned int value;
	unsigned int reg;
	unsigned int reg1;
	unsigned int offset;
	unsigned int reg2;

	switch (opc)
	{
	case LDR:
		address = instruction & 0xFFFF;
		if (address > 1023)
		{
			printf("error");
		}
		reg = (instruction >> 16) & 0xFF;
		registers[reg] = memory_fetch_word(address);
		registers[15] += 4;
		break;
	case LDI:
		value = instruction & 0xFFFF;
		reg = (instruction >> 16) & 0XFF;
		if (reg > 15)
		{
			printf("error");
		}
		registers[reg] = value;
		registers[15] += 4;
		break;

	case STR:
		address = instruction & 0xFFFF;
		reg = (instruction >> 16) & 0XFF;
		if (address > 1023 || reg > 15)
		{
			printf("error");
		}
		memory_store_word(address, registers[reg]);
		registers[15] += 4;
		break;

	case LDX:
		offset = instruction & 0xFF;
		reg = (instruction >> 16) & 0XFF;
		reg1 = (instruction >> 8) & 0xFF;
		if (reg > 15)
		{
			printf("error");
		}
		registers[reg] = memory_fetch_word(registers[reg1] + offset);
		registers[15] += 4;
		break;

	case ADD:

		reg = (instruction >> 16) & 0XFF;
		reg1 = (instruction >> 8) & 0xFF;
		reg2 = instruction & 0xFF;
		if (reg > 15)
		{
			printf("error");
		}

		registers[reg] = registers[reg1] + registers[reg2];
		registers[15] += 4;
		break;

	case SUB:
		reg = (instruction >> 16) & 0XFF;
		reg1 = (instruction >> 8) & 0xFF;
		reg2 = instruction & 0xFF;
		if (reg > 15)
		{
			printf("error");
		}

		registers[reg] = registers[reg1] - registers[reg2];

		registers[15] += 4;
		break;

	case MUL:

		reg = (instruction >> 16) & 0XFF;
		reg1 = (instruction >> 8) & 0xFF;
		reg2 = instruction & 0xFF;
		if (reg > 15)
		{
			printf("error");
		}

		registers[reg] = registers[reg1] * registers[reg2];

		registers[15] += 4;
		break;
	case DIV:

		reg = (instruction >> 16) & 0XFF;
		reg1 = (instruction >> 8) & 0xFF;
		reg2 = instruction & 0xFF;
		if (reg > 15)
		{
			printf("error");
		}

		registers[reg] = registers[reg1] / registers[reg2];
		registers[15] += 4;
		break;

	case CMP:
		reg = (instruction >> 8) & 0XFF;
		reg1 = instruction & 0xFF;
		if (registers[reg] == registers[reg1])
		{
			cpsr = 0;
			bit_set(&cpsr, Z);
			registers[PC] += 4;
		}
		else if (registers[reg] < registers[reg1])
		{
			cpsr = 0;
			bit_set(&cpsr, LT);
			registers[PC] += 4;
		}
		else
		{
			cpsr = 0;
			bit_set(&cpsr, GT);
			registers[PC] += 4;
		}
		break;

	case B:
		address = instruction & 0xFFFF;

		registers[PC] = address;
		break;

	case BEQ:
		address = instruction & 0xFFFF;

		if (bit_test(cpsr, Z))
		{
			registers[PC] = address;
		}
		else
		{

			registers[PC] += 4;
		}
		break;

	case BNE:
		address = instruction & 0xFFFF;

		if (!bit_test(cpsr, Z))
		{
			registers[PC] = address;
		}
		else
		{
			registers[PC] += 4;
		}
		break;

	case BLT:
		address = instruction & 0xFFFF;

		if (bit_test(cpsr, LT))
		{
			registers[PC] = address;
		}
		else
		{
			registers[PC] += 4;
		}
		break;

	case BGT:
		address = instruction & 0xFFFF;

		if (bit_test(cpsr, GT))
		{
			registers[PC] = address;
		}
		else
		{
			registers[PC] += 4;
		}
		break;

	case MOV:
		reg = (instruction >> 8) & 0XFF;
		reg1 = instruction & 0xFF;
		registers[reg] = registers[reg1];
		registers[PC] += 4;
		break;

	case BL:
		address = instruction & 0xFFFF;
		registers[LR] = registers[PC] + 4;
		registers[PC] = address;

		break;
	}
}

void step_n(int n)
{
	for (int i = 0; i < n; i++)
	{
		step();
	}
}
