#include <map>
#include <fcntl.h>
#include "params.hh"
#include <stdio.h>
#include <unistd.h>

#include <inttypes.h>
#include <stdlib.h>


void verify_phys_to_virt(void * mem_map, uint64_t (*fun)(uint64_t));
void verify_virt_to_phys(void * mem_map, uint64_t (*fun)(uint64_t));
void verify_PPN_VPN_map(void * mem_map, std::map<uint64_t, uint64_t> PPN_VPN_map);
