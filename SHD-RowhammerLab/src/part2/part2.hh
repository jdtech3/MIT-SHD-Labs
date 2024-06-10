#include "../shared.hh"
#include "../verif.hh"
#include "../params.hh"
#include "../util.hh"

// Physical Addresses for Specific DRAM Rows
#define VICT_ADDR 0x75380000UL
#define ADDR_A    0x753A2000UL
#define ADDR_B    0x7536E000UL
#define ADDR_C    0x75308000UL
#define ADDR_D    0x75382000UL

bool hammer_addresses(uint64_t vict_phys_addr, uint64_t attacker_phys_addr_1,
                      uint64_t attacker_phys_addr_2);
