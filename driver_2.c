/***************************************************************************//**
*  \file       driver_2.c
*
*  \details    Passing parameters to linux device driver
*
*  \author     Hari Udayakumar
*
* *******************************************************************************/
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>

int i32_value, i32_array[4] ,i32_cb_value;
char* name;

module_param(i32_value, int, S_IRUSR | S_IWUSR);
module_param(name, charp, S_IRUSR | S_IWUSR);
module_param_array(i32_array, int, NULL, S_IRUSR | S_IWUSR);

int notify_param(const char *val, const struct kernel_param *kp)
{
   int res = param_set_int(val, kp);
   if(res ==0){
	printk(KERN_INFO "Callback function triggered...\n");
	printk(KERN_INFO "New value of i32_cb_value =%d\n", i32_cb_value);
	return 0;
	}
	return -1;
}

const struct kernel_param_ops my_param_ops =
{
	.set = &notify_param,
	.get = &param_get_int
};


module_param_cb(i32_cb_value, &my_param_ops, &i32_cb_value, S_IRUGO | S_IWUSR);

/*-------------------------------------------------------------------------*/
/*
** Module init function
*/
static int __init driver_init(void)
{
        int i;
        printk(KERN_INFO "i32value  = %d  \n", i32_value);
        printk(KERN_INFO "i32_cb_value = %d  \n", i32_cb_value);
        printk(KERN_INFO "Name = %s \n", name);
        for (i = 0; i < (sizeof i32_array / sizeof (int)); i++) {
                printk(KERN_INFO "i32_array[%d] = %d\n", i, i32_array[i]);
        }
        printk(KERN_INFO "Kernel Module Inserted Successfully...\n");
    return 0;
}
/*
** Module Exit function
*/
static void __exit driver_exit(void)
{
    printk(KERN_INFO "Kernel Module Removed Successfully...\n");
}
 
module_init(driver_init);
module_exit(driver_exit);
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hari Udayakumar <hariudkmr@gmail.com>");
MODULE_DESCRIPTION("Driver2 - Passing arguments to Linux Device Driver");
MODULE_VERSION("1.0");


