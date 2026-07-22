#include <linux/debugfs.h>
#include <linux/err.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/jiffies.h>
#include <linux/kernel.h>
#include <linux/mm.h>
#include <linux/module.h>
#include <linux/mutex.h>
#include <linux/slab.h>
#include <linux/uaccess.h>

#define EUDYPTULA_ID "biggvladik"

static struct dentry *eudyptula_dir;

static char *foo_buffer;

static size_t foo_size;

static DEFINE_MUTEX(foo_mutex);


static ssize_t id_read(struct file *file, char __user *user_buffer,
                       size_t count, loff_t *ppos)
{
    return simple_read_from_buffer(user_buffer,
                                   count,
                                   ppos,
                                   EUDYPTULA_ID,
                                   strlen(EUDYPTULA_ID));
}

static ssize_t id_write(struct file *file, const char __user *user_buffer,
                        size_t count, loff_t *ppos)
{
    char input[sizeof(EUDYPTULA_ID)];
    size_t id_length = strlen(EUDYPTULA_ID);

    
    if (count != id_length)
        return -EINVAL;

    
    if (copy_from_user(input, user_buffer, count))
        return -EFAULT;

    if (memcmp(input, EUDYPTULA_ID, id_length) != 0)
        return -EINVAL;

    return count;
}



static const struct file_operations id_fops = {
    .owner  = THIS_MODULE,
    .read   = id_read,
    .write  = id_write,
    .llseek = default_llseek,
};



static ssize_t jiffies_read(struct file *file, char __user *user_buffer,
                            size_t count, loff_t *ppos)
{
    char buffer[32];
    int length;

    length = scnprintf(buffer, sizeof(buffer), "%lu\n", jiffies);

    return simple_read_from_buffer(user_buffer,
                                   count,
                                   ppos,
                                   buffer,
                                   length);
}


static const struct file_operations jiffies_fops = {
    .owner  = THIS_MODULE,
    .read   = jiffies_read,
    .llseek = default_llseek,
};

static ssize_t foo_read(struct file *file, char __user *user_buffer,
                        size_t count, loff_t *ppos)
{
    ssize_t result;
    
    if (mutex_lock_interruptible(&foo_mutex))
        return -ERESTARTSYS;

    result = simple_read_from_buffer(user_buffer,
                                     count,
                                     ppos,
                                     foo_buffer,
                                     foo_size);

    mutex_unlock(&foo_mutex);

    return result;
}

static ssize_t foo_write(struct file *file,
                         const char __user *user_buffer,
                         size_t count,
                         loff_t *ppos)
{
  
    if (count > PAGE_SIZE)
        return -EINVAL;

    
    if (*ppos != 0)
        return -EINVAL;

    if (mutex_lock_interruptible(&foo_mutex))
        return -ERESTARTSYS;

    
    if (copy_from_user(foo_buffer, user_buffer, count)) {
        mutex_unlock(&foo_mutex);
        return -EFAULT;
    }

    
    if (count < PAGE_SIZE)
        memset(foo_buffer + count, 0, PAGE_SIZE - count);

    foo_size = count;

    
    *ppos += count;

    mutex_unlock(&foo_mutex);

    return count;
}


static const struct file_operations foo_fops = {
    .owner  = THIS_MODULE,
    .read   = foo_read,
    .write  = foo_write,
    .llseek = default_llseek,
};



static int __init task08_init(void)
{
    struct dentry *entry;
    int ret = 0;

    foo_buffer = kzalloc(PAGE_SIZE, GFP_KERNEL);
    if (!foo_buffer)
        return -ENOMEM;

    foo_size = 0;

    
    eudyptula_dir = debugfs_create_dir("eudyptula", NULL);
    if (IS_ERR_OR_NULL(eudyptula_dir)) {
        ret = eudyptula_dir ? PTR_ERR(eudyptula_dir) : -ENOMEM;
        pr_err("task08: failed to create debugfs directory\n");
        goto free_buffer;
    }

    entry = debugfs_create_file("id",
                                0666,
                                eudyptula_dir,
                                NULL,
                                &id_fops);
    if (IS_ERR_OR_NULL(entry)) {
        ret = entry ? PTR_ERR(entry) : -ENOMEM;
        pr_err("task08: failed to create id file\n");
        goto remove_debugfs;
    }

    entry = debugfs_create_file("jiffies",
                                0444,
                                eudyptula_dir,
                                NULL,
                                &jiffies_fops);
    if (IS_ERR_OR_NULL(entry)) {
        ret = entry ? PTR_ERR(entry) : -ENOMEM;
        pr_err("task08: failed to create jiffies file\n");
        goto remove_debugfs;
    }

    entry = debugfs_create_file("foo",
                                0644,
                                eudyptula_dir,
                                NULL,
                                &foo_fops);
    if (IS_ERR_OR_NULL(entry)) {
        ret = entry ? PTR_ERR(entry) : -ENOMEM;
        pr_err("task08: failed to create foo file\n");
        goto remove_debugfs;
    }

    pr_info("task08: module loaded\n");
    pr_info("task08: debugfs files created in /sys/kernel/debug/eudyptula\n");

    return 0;

remove_debugfs:
    
    debugfs_remove_recursive(eudyptula_dir);
    eudyptula_dir = NULL;

free_buffer:
    kfree(foo_buffer);
    foo_buffer = NULL;
    foo_size = 0;

    return ret;
}

static void __exit task08_exit(void)
{
    
    debugfs_remove_recursive(eudyptula_dir);
    eudyptula_dir = NULL;

    kfree(foo_buffer);
    foo_buffer = NULL;
    foo_size = 0;

    pr_info("task08: module unloaded\n");
}

module_init(task08_init);
module_exit(task08_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("biggvladik");
MODULE_DESCRIPTION("Eudyptula Challenge Task 08 debugfs module");
MODULE_VERSION("1.0");















