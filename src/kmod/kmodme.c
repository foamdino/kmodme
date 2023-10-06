/* 
 * kmodme.c - The simplest kernel module.
 * Start with something simple to test compiling in github workflows
 * https://sysprog21.github.io/lkmpg/#the-simplest-module
 */ 
#include <linux/module.h> /* Needed by all modules */ 
#include <linux/printk.h> /* Needed for pr_info() */ 
#include <linux/init.h> /* Needed for the macros */ 

#include <linux/kernel.h>
#include <linux/irq.h>
#include <linux/proc_fs.h>
#include <linux/netdevice.h>
#include <linux/net_namespace.h>
 
static int __init in(void) 
{ 
    unsigned int irq;
    struct net *net;
    unsigned int ifindex;

    pr_info("Hello world 1.\n"); 
    irq = 8;

    struct irq_data *d = irq_get_irq_data(irq);
    pr_info("irq: %du, hwirq: %lu\n", d->irq, d->hwirq);

    /* From net/ethtool/netlink.c
    		dev = netdev_get_by_index(net, ifindex, &req_info->dev_tracker,
					  GFP_KERNEL);
    */

    net = &init_net;
    
    ifindex = 2;

    struct net_device *dev = dev_get_by_index(net, ifindex);

    if (dev) {
        pr_info("Found network device: %s with irq: %d\n", dev->name, dev->irq);
    } else {
        pr_info("Network device with index %d not found\n", ifindex);
    }

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