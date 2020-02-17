#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/kernel.h> 
#include <linux/sched.h> 
 
static int process_id=10;
module_param(process_id,int,0644); //only user can write else read
 
static int test_module_init(void)
{
	printk(KERN_INFO "Process ID : %d\n",process_id);
	struct task_struct *task_list;
	for_each_process(task_list) {

		if(task_list->pid == process_id){
    			printk("Process name : %s]\n", task_list->comm);
			printk("Process state: %d\n", task_list->state);
			printk("CPU allowed: %d\n", task_list->nr_cpus_allowed);
		
		}
	}
	return 0;
}
 
static void test_module_cleanup(void)
{
	printk(KERN_INFO "Returning, details of Process ID: %d shared\n",process_id);
}
 
module_init(test_module_init);
module_exit(test_module_cleanup)
