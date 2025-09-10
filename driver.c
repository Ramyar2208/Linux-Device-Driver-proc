#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>  

MODULE_LICENSE("GPL");

char data[40];
size_t data_size = sizeof(data);

struct proc_dir_entry * create_ret;

static ssize_t	sample_read (struct file * file, char __user * user, size_t size, loff_t * offset) {

    size_t len = strlen(data), ret;
    
    /* check whether all data is read*/
	
    if(*offset >= len) {
	
        return 0;
    }

    ret = copy_to_user(user, data, len);

    *offset += len;
    
	/* return no.of. bytes read */
    return len;
}

static ssize_t	sample_write (struct file * file, const char __user * user, size_t size, loff_t * offset) {

    size_t len = strlen(data), ret;
    char buf[40];

    ret = copy_from_user(buf, user, size);
    
    /* copy_from_user - success & check space availability, +1 for NULL*/

    if((ret == 0) && ((size + 1) <= (data_size - len))) {

        strcat(data, buf);
        
		/* return no.of. bytes written */
        return size;  
    }         

    else {

        printk("Error copying data or not enough space to write data");
        
		/* No room for the data */
		
        return -ENOSPC;  
    }  
}

struct proc_ops op = {
    .proc_read = sample_read,
    .proc_write = sample_write
};

static int sample_driver_init (void) {

    printk("Sample driver init\n");

    create_ret = proc_create("sample_file", 
                             0666,               /* File permission - rw-rw-rw- */
                             NULL,               /* No top-level directory */
                             &op                 /* Struct for file operations on /proc/sample_file */      
                            );
    
    if(! create_ret){
        printk("Error: Can't create sample file\n");
        return -1;
    }
    
    /* return 0 on init success*/
    return 0;                                    
}

static void sample_driver_exit (void) {

    printk("Sample driver exit\n");

    proc_remove(create_ret);
}

module_init(sample_driver_init);
module_exit(sample_driver_exit);

