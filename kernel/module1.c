/*************************************************************************
	> File Name: module1.c
	> Author: 
	> Mail: 
	> Created Time: Fri Sep 15 17:25:44 2017
 ************************************************************************/

#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>

static int __init lkp_init(void) {

    printk("<1>Hello World!");
    return 0;
}

static int __exit lkp_exit(void) {

    printk("<1>GoodBye!");
    return 0;
}

module_init(lkp_init);

module_exit(lkp_exit);

MODULE_LICENSE("GPL");
