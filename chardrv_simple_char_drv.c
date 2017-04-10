#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h> //For the character driver support
int chardrv_open(struct inode *pinode, struct file *pfile)
{
  printk(KERN_ALERT "Inside the %s function\n", __FUNCTION__);
  return 0;
}

ssize_t chardrv_read(struct file *pfile, char __user *buffer, size_t length, loff_t *offset)
{
  printk(KERN_ALERT "Inside the %s function\n", __FUNCTION__);
  return 0;
}

ssize_t chardrv_write(struct file *pfile, const char __user *buffer, size_t length, loff_t *offset)
{
  printk(KERN_ALERT "Inside the %s function\n", __FUNCTION__);
  return length;
}

int chardrv_close(struct inode *pinode, struct file *pfile)
{
  printk(KERN_ALERT "Inside the %s function\n", __FUNCTION__);
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
  printk(KERN_ALERT "Inside the %s function\n", __FUNCTION__);

  /* Register with the kernel and indicate that we are registering a character device driver */
  register_chrdev(240/* Major NUmber */, "Simple Char Drv"/* Name of the Driver */, &chardrv_file_operations/* File  Operations */);
  return 0;
}

void simple_module_exit(void)
{
  printk(KERN_ALERT "Inside the %s function\n", __FUNCTION__);

  /* Unregister the character device driver */
  unregister_chrdev(240, "Simple Char Drv")
}

module_init(chardrv_simple_module_init);
module_exit(chardrv_simple_module_exit);
