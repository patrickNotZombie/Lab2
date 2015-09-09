/* Author: Garrett Scholtes
 * Date:   2015-09-09
 *
 * Lab2 - CS4029
 * 
 * This module performs the same function as the sample
 * timer module, but this module uses work queues.
 *
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/workqueue.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");

static struct workqueue_struct *queue;
static struct delayed_work *dwork;
static int count;

void function( struct work_struct *work ) {
    printk(KERN_EMERG "function called -> work queue says (%ld).\n", jiffies);
    count++;

    if(count <= 10) {
        queue_delayed_work(queue, dwork, HZ);
    }

    return;
}

int init_module( void ) {
    count = 1;
    queue = create_workqueue("queue");
    dwork = (struct delayed_work*)kmalloc(sizeof(struct delayed_work), GFP_KERNEL);

    printk("Timer module installing\n");

    INIT_DELAYED_WORK((struct delayed_work*)dwork, function);

    queue_delayed_work(queue, dwork, HZ);

    return 0;
}

void cleanup_module( void ) {
    if(dwork && delayed_work_pending(dwork)) {
        cancel_delayed_work(dwork);
        printk("Delayed work canceled\n");
    } else {
        printk("No delayed work to cancel\n");
    }
    flush_workqueue(queue);
    destroy_workqueue(queue);

    printk("Timer module uninstalling\n");

    return;
}