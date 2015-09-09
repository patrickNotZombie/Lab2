/* Author: Garrett Scholtes
 * Date:   2015-09-09
 *
 * Lab2 - CS4029
 * 
 * This module performs the same function as the sample
 * timer module, but this module uses kthreads.
 *
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kthread.h>

MODULE_LICENSE("GPL");

static struct task_struct *ts;
static int id;
static int count;
static bool kthread_alive;

int function( void *data ) {
    int n = *(int*)data;

    printk(KERN_EMERG "function called with data (%d)\n", n);
    while( count <= 10 ) {
        // If cleanup_module has told us that it
        // is time to stop then we need to stop
        if( kthread_should_stop() ) {
            return 0;
        }

        set_current_state(TASK_INTERRUPTIBLE);
        schedule_timeout(HZ);

        printk(KERN_EMERG "kthread says (%ld).\n", jiffies);

        count++;
    }
    
    kthread_alive = false;
    return 0;
}

int init_module( void ) {
    id = 101;
    count = 1;
    kthread_alive = true;

    printk("Timer module installing\n");

    ts = kthread_run(function, (void*)&id, "spawn");

    return 0;
}

void cleanup_module( void ) {
    int threadfn;

    if( kthread_alive ) {
        threadfn = kthread_stop(ts);
        printk("kthread_stop invoked\n");
        if( threadfn ) { printk("The timer is a zombie...\n"); }
    } else {
        printk("kthread already finished -- not invoking kthread_stop\n");
    }
    printk("Timer module uninstalling\n");

    return;
}