#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h> //For the character driver support
#include <asm/uaccess.h>

char msg[100] = {0};
int readPos = 0;
int times = 0;

int chardrv_open(struct inode *pinode, struct file *pfile)
{
  times++;
  printk(KERN_ALERT "Device Opened %d times\n", times);
  return 0;
}

ssize_t chardrv_read(struct file *pfile, char __user *buffer, size_t length, loff_t *offset)
{
  printk(KERN_ALERT "Reading the Device\n");
    int count = 0;
    while((int)((ssize_t)length) && (msg[readPos]!=0))
    {
      put_user(msg[readPos],buffer++);
      count++;
      length--;
      readPos++;
    }
  return count;
}

ssize_t chardrv_write(struct file *pfile, const char __user *buffer, size_t length, loff_t *offset)
{
  printk(KERN_ALERT "Writing on Device\n");
  int ind = (int)((ssize_t)(length)) - 1;
  int count = 0;
  memset(msg, 0, 100);
  readPos = 0;
  while(length>0)
  {
    msg[count++] = buffer[ind--];
    length--;
  }
  return count;
}

int chardrv_close(struct inode *pinode, struct file *pfile)
{
  printk(KERN_ALERT "Device Closed\n");
  return 0;
}

/* To hold the file operations performed on this device */
struct file_operations chardrv_file_operations = {
  .owner    = THIS_MODULE,
  .open     = chardrv_open,
  .read     = chardrv_read,
  .write    = chardrv_write,
  .release  = chardrv_close,
};

int chardrv_simple_module_init(void)
{
  printk(KERN_ALERT "Device Registered\n");
  register_chrdev(240, "Simple Char Drv", &chardrv_file_operations);
  return 0;
}

void chardrv_simple_module_exit(void)
{
  printk(KERN_ALERT "Device Unregistered\n");

  /* Unregister the character device driver */
  unregister_chrdev(241, "Simple Char Drv");
}

module_init(chardrv_simple_module_init);
module_exit(chardrv_simple_module_exit); #include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h> //For the character driver support
#include <asm/uaccess.h>

char msg[100] = {0};
int readPos = 0;
int times = 0;

int chardrv_open(struct inode *pinode, struct file *pfile)
{
  times++;
  printk(KERN_ALERT "Device Opened %d times\n", times);
  return 0;
}

ssize_t chardrv_read(struct file *pfile, char __user *buffer, size_t length, loff_t *offset)
{
  printk(KERN_ALERT "Reading the Device\n");
    int count = 0;
    while((int)((ssize_t)length) && (msg[readPos]!=0))
    {
      put_user(msg[readPos],buffer++);
      count++;
      length--;
      readPos++;
    }
  return count;
}

ssize_t chardrv_write(struct file *pfile, const char __user *buffer, size_t length, loff_t *offset)
{
  printk(KERN_ALERT "Writing on Device\n");
  int ind = (int)((ssize_t)(length)) - 1;
  int count = 0;
  memset(msg, 0, 100);
  readPos = 0;
  while(length>0)
  {
    msg[count++] = buffer[ind--];
    length--;
  }
  return count;
}

int chardrv_close(struct inode *pinode, struct file *pfile)
{
  printk(KERN_ALERT "Device Closed\n");
  return 0;
}

/* To hold the file operations performed on this device */
struct file_operations chardrv_file_operations = {
  .owner    = THIS_MODULE,
  .open     = chardrv_open,
  .read     = chardrv_read,
  .write    = chardrv_write,
  .release  = chardrv_close,
};

int chardrv_simple_module_init(void)
{
  printk(KERN_ALERT "Device Registered\n");
  register_chrdev(240, "Simple Char Drv", &chardrv_file_operations);
  return 0;
}

void chardrv_simple_module_exit(void)
{
  printk(KERN_ALERT "Device Unregistered\n");

  /* Unregister the character device driver */
  unregister_chrdev(241, "Simple Char Drv");
}

module_init(chardrv_simple_module_init);
module_exit(chardrv_simple_module_exit);
