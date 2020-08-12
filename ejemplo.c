#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/sysinfo.h>
#include <linux/seq_file.h>
#include <linux/slab.h>
#include <linux/mm.h>
#include <linux/swap.h>


static int open_action(struct seq_file *m, void *v){


 struct task_struct *task;

  seq_printf(m,"Pid,Nombre_Del_Proceso\n");

 for_each_process(task){
   if(task->mm){
     seq_printf(m,"%d,%s\n", task->pid, task->comm);
   }
 }


 return 0;
}


ssize_t write_proc(struct file *filp, const char *buf, size_t count, loff_t *offp){
 return 0;
}

int open_proc(struct inode *inode, struct file *file){
  return single_open(file, open_action , NULL);
}


static struct file_operations proc_fops = {
 read : seq_read,
 write : write_proc,
 open : open_proc,
 release : single_release,
 llseek : seq_lseek
};


static int __init ejemplo_init(void) {
 printk(KERN_INFO "Inicio del Ejemplo de Clase\n");

 struct proc_dir_entry *entry;
 entry = proc_create("ejemplo",0777,NULL,&proc_fops); 

 if (!entry){
   return -1;
 } 


 return 0;
}

static void __exit ejemplo_exit(void) {
 printk(KERN_INFO "Fin de mi Ejemplo\n");
 remove_proc_entry("ejemplo",NULL);
}



module_init(ejemplo_init);
module_exit(ejemplo_exit);



MODULE_LICENSE("GPL");
MODULE_AUTHOR("Franklin Velasquez");
MODULE_DESCRIPTION("CPU");
MODULE_VERSION("0.01");

