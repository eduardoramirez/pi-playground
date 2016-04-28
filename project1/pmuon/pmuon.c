#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your name");
MODULE_DESCRIPTION("PMUON");


int init_module(void) {
    unsigned int v, L1_access, L1_miss, L2_access, L2_miss;

    printk("Turn PMU on\n");

    // 1. Enable "User Enable Register"
    asm volatile("mcr p15, 0, %0, c9, c14, 0\n\t" :: "r" (0x00000001)); 

    // 2. Reset Performance Monitor Control Register(PMCR), Count Enable Set Register, and Overflow Flag Status Register
    asm volatile ("mcr p15, 0, %0, c9, c12, 0\n\t" :: "r"(0x00000017));
    asm volatile ("mcr p15, 0, %0, c9, c12, 1\n\t" :: "r"(0x8000000f));
    asm volatile ("mcr p15, 0, %0, c9, c12, 3\n\t" :: "r"(0x8000000f));

    // 3. Disable Interrupt Enable Clear Register
    asm volatile("mcr p15, 0, %0, c9, c14, 2\n\t" :: "r" (~0));

    // 4. Read how many event counters exist 
    asm volatile("mrc p15, 0, %0, c9, c12, 0\n\t" : "=r" (v)); // Read PMCR
    printk("pmuon_init(): have %d configurable event counters.\n", (v >> 11) & 0x1f);


    // 5. Set event counter registers (Project Assignment you need to IMPLEMENT)
    // select the event register with PMSELR   
    // then set the event type using PMXEVTYPER
    // finally read the value using PMXEVCNTR
    asm volatile("mcr p15, 0, %0, c9, c12, 5\n\t" :: "r"(0x00000000));  // PMSELR       set the event register to use
    asm volatile("mcr p15, 0, %0, c9, c13, 1\n\n" :: "r"(0x00000013));  // PMXEVTYPER   Set the event type 
    //asm volatile("mrc p15, 0, %0, c9, c13, 2\n\t" : "=r" (L1_access));  // PMXEVCNTR    Read from register
    //printk("\n\tnpmoun_init(): First event counter %d L1 accesses\n\t", (L1_access));
    
    asm volatile("mcr p15, 0, %0, c9, c12, 5\n\t" :: "r"(0x00000001));
    asm volatile("mcr p15, 0, %0, c9, c13, 1\n\n" :: "r"(0x00000015));
    //asm volatile("mrc p15, 0, %0, c9, c13, 2\n\t" : "=r" (L1_miss));
    //printk("pmoun_init(): Second event counter %d L1 misses\n\t", (L1_miss));
    
    asm volatile("mcr p15, 0, %0, c9, c12, 5\n\t" :: "r"(0x00000002));
    asm volatile("mcr p15, 0, %0, c9, c13, 1\n\n" :: "r"(0x00000016));
    //asm volatile("mrc p15, 0, %0, c9, c13, 2\n\t" : "=r" (L2_access));
    //printk("pmoun_init(): Third event counter %d L2 accesses\n\t", (L2_access));

    asm volatile("mcr p15, 0, %0, c9, c12, 5\n\t" :: "r"(0x00000003));
    asm volatile("mcr p15, 0, %0, c9, c13, 1\n\n" :: "r"(0x00000017));
    //asm volatile("mrc p15, 0, %0, c9, c13, 2\n\t" : "=r" (L2_miss));
    //printk("pmoun_init(): Fourth event counter %d L2 misses\n\t", (L2_miss));

	return 0;
}

void cleanup_module(void) {
	printk("GOODBYE, PMU Off\n");
}


