# Linux Device Driver development using proc file system

**Output**: driver interaction

**ubuntu@primary:~/sample_driver$** echo "Linux Device Driver" > /proc/sample_file 

**ubuntu@primary:~/sample_driver$** cat /proc/sample_file

Linux Device Driver

**ubuntu@primary:~/sample_driver$** echo -n "sample " > /proc/sample_file 

**ubuntu@primary:~/sample_driver$** cat /proc/sample_file

Linux Device Driver

**sample ubuntu@primary:~/sample_driver$** echo -n "Implementations" > /proc/sample_file 

bash: echo: write error: No space left on device

**ubuntu@primary:~/sample_driver$** sudo dmesg -c

**[ 4854.422578]** Error copying data or not enough space to write data

# 

**Explanation:**
Blog: https://embedded-electronicsproject.blogspot.com/2025/09/linux-device-driver-development-using.html

Read and write from or to user space and kernel space (using proc file system)

1) Write data provided by user to proc file system in kernel space as long as there is enough space, else return respective error

2) Read back the written data from kernel space to user space

Functions used: proc_create(), proc_write(), proc_read(), proc_remove()

proc_fs.h: https://github.com/torvalds/linux/blob/master/include/linux/proc_fs.h

**Linux commands:**

**Installation:**

1. sudo apt update

2. sudo apt upgrade

3. sudo apt install -y build-essential liunx-headers-$(uname -r) kmod  

   (build essentials like make, GCC .,. |  linux header - for compiling kernel modules  | kmod - provides utilities for handling kernel modules)

4. sudo apt install git-all (linux  - git install)

**Make Automation:**

5. make

6. make clean

**Module commands:**

7. sudo insmod driver.ko  (insert our generated object file into kernel)

8. lsmod                  (list kernel modules - check wheter our module is listed after successful insertion)

   lsmod | grep <module_name>

9. sudo dmesg -c          (print kernel module messages form log)

10. modinfo driver.ko     (get information about module)

11. sudo rmmod driver     (remove the module from kernel)

**Git commands:** (config email and name)

$ git init . -b main

$ git add .

$ git commit -m "commit msg"

$ git status

$ git diff

$ tree .git/

$ git log

/* Push using HTTP url - create new repo in github w/o additional files */

$ git remote add origin <http-url>

$ git push -u origin main 
