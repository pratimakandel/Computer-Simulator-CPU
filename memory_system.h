void memory_store(int address, unsigned char value);
void memory_store_word(int address, unsigned int value);
unsigned char memory_fetch(int address);
unsigned int memory_fetch_word(int address);
void memory_fill(int start_address, unsigned char value, int num_bytes);
void memory_dump(int start_address, int num_bytes);
void load_memory(char *filename);
