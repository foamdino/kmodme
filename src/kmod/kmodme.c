/* 
 * kmodme.c - The simplest kernel module.
 * Start with something simple to test compiling in github workflows
 * https://sysprog21.github.io/lkmpg/#the-simplest-module
 */ 
#include <linux/module.h> /* Needed by all modules */ 
#include <linux/printk.h> /* Needed for pr_info() */ 
#include <linux/init.h> /* Needed for the macros */ 

#include <linux/irq.h>
#include <linux/proc_fs.h> 
 
static int __init in(void) 
{ 
    unsigned int irq;

    pr_info("Hello world 1.\n"); 
    irq = 8;

    struct irq_data *d = irq_get_irq_data(irq);
    pr_info("irq: %du, hwirq: %lu\n", d->irq, d->hwirq);


    /* A non 0 return means init_module failed; module can't be loaded. */ 
    return 0; 
} 
 
static void __exit ex(void) 
{ 
    pr_info("Goodbye world 1.\n"); 
} 
 

module_init(in); 
module_exit(ex); 
MODULE_LICENSE("GPL");