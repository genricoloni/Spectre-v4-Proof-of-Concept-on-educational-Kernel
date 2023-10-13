8,9d7
< #include <stdint.h>
< 
279,285d276
< extern "C" void c_victim_function(int idx, unsigned char** memory_slot_ptr, unsigned char* public_key, unsigned char** memory_slot, char* probe){
< 	unsigned char **memory_slot_slow_ptr = memory_slot_ptr;
< 	*memory_slot_slow_ptr = *memory_slot;
< 	memory_slot_slow_ptr[idx] = &public_key[idx];
< 
< 	char tmp = probe[(*memory_slot)[idx] * 4096];
< }
2005,2006d1995
< 
< // TESI
