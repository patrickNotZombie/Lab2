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

int init_module( void ) {

    printk("Timer module installing\n");

    return 0;
}

void cleanup_module( void ) {

    printk("Timer module uninstalling\n");

    return;
}