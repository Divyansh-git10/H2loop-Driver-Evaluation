#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "llm_char_dev"
#define BUFFER_SIZE 1024
#define MAJOR_NUM 240

static char device_buffer[BUFFER_SIZE];
static int device_open = 0;

static int dev_open(struct inode *inode, struct file *file) {
    if (device_open)
        return -EBUSY;
    device_open++;
    printk(KERN_INFO "LLM: Device opened\n");
    return 0;
}

static int dev_release(struct inode *inode, struct file *file) {
    device_open--;
    printk(KERN_INFO "LLM: Device closed\n");
    return 0;
}

static ssize_t dev_read(struct file *file, char __user *buffer, size_t len, loff_t *offset) {
    int bytes_read = 0;
    if (*offset >= BUFFER_SIZE)
        return 0;
    if (*offset + len > BUFFER_SIZE)
        len = BUFFER_SIZE - *offset;

    if (copy_to_user(buffer, device_buffer + *offset, len) != 0)
        return -EFAULT;

    *offset += len;
    bytes_read = len;

    printk(KERN_INFO "LLM: Read %d bytes\n", bytes_read);
    return bytes_read;
}

static ssize_t dev_write(struct file *file, const char __user *buffer, size_t len, loff_t *offset) {
    int bytes_written = 0;
    if (*offset >= BUFFER_SIZE)
        return -ENOMEM;
    if (*offset + len > BUFFER_SIZE)
        len = BUFFER_SIZE - *offset;

    if (copy_from_user(device_buffer + *offset, buffer, len) != 0)
        return -EFAULT;

    *offset += len;
    bytes_written = len;

    printk(KERN_INFO "LLM: Wrote %d bytes\n", bytes_written);
    return bytes_written;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .read = dev_read,
    .write = dev_write,
    .open = dev_open,
    .release = dev_release
};

static int __init llm_char_init(void) {
    int result = register_chrdev(MAJOR_NUM, DEVICE_NAME, &fops);
    if (result < 0) {
        printk(KERN_ALERT "LLM: Failed to register device\n");
        return result;
    }
    printk(KERN_INFO "LLM: Device registered with major number %d\n", MAJOR_NUM);
    return 0;
}

static void __exit llm_char_exit(void) {
    unregister_chrdev(MAJOR_NUM, DEVICE_NAME);
    printk(KERN_INFO "LLM: Device unregistered\n");
}

module_init(llm_char_init);
module_exit(llm_char_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ChatGPT");
MODULE_DESCRIPTION("LLM-Generated Character Device Driver");
