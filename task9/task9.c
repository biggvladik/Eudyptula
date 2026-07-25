#include <linux/init.h>
#include <linux/jiffies.h>
#include <linux/kernel.h>
#include <linux/kobject.h>
#include <linux/mm.h>
#include <linux/module.h>
#include <linux/mutex.h>
#include <linux/string.h>
#include <linux/sysfs.h>

#define EUDYPTULA_ID "biggvladik"

static struct kobject *eudyptula_kobj;

static char foo_buffer[PAGE_SIZE];
static size_t foo_size;
static DEFINE_MUTEX(foo_mutex);

static ssize_t id_show(struct kobject *kobj,
                       struct kobj_attribute *attr,
                       char *buf)
{
    return sysfs_emit(buf, "%s\n", EUDYPTULA_ID);
}

static ssize_t id_store(struct kobject *kobj,
                        struct kobj_attribute *attr,
                        const char *buf,
                        size_t count)
{
    if (!sysfs_streq(buf, EUDYPTULA_ID))
        return -EINVAL;

    return count;
}

static ssize_t jiffies_show(struct kobject *kobj,
                            struct kobj_attribute *attr,
                            char *buf)
{
    return sysfs_emit(buf, "%lu\n", jiffies);
}

static ssize_t foo_show(struct kobject *kobj,
                        struct kobj_attribute *attr,
                        char *buf)
{
    ssize_t ret;

    if (mutex_lock_interruptible(&foo_mutex))
        return -ERESTARTSYS;

    memcpy(buf, foo_buffer, foo_size);
    ret = foo_size;

    mutex_unlock(&foo_mutex);

    return ret;
}

static ssize_t foo_store(struct kobject *kobj,
                         struct kobj_attribute *attr,
                         const char *buf,
                         size_t count)
{
    if (count > PAGE_SIZE)
        return -EINVAL;

    if (mutex_lock_interruptible(&foo_mutex))
        return -ERESTARTSYS;

    memcpy(foo_buffer, buf, count);

    if (count < PAGE_SIZE)
        memset(foo_buffer + count, 0, PAGE_SIZE - count);

    foo_size = count;

    mutex_unlock(&foo_mutex);

    return count;
}

static struct kobj_attribute id_attribute =
    __ATTR(id, 0664, id_show, id_store);

static struct kobj_attribute jiffies_attribute =
    __ATTR(jiffies, 0444, jiffies_show, NULL);

static struct kobj_attribute foo_attribute =
    __ATTR(foo, 0644, foo_show, foo_store);

static struct attribute *eudyptula_attrs[] = {
    &id_attribute.attr,
    &jiffies_attribute.attr,
    &foo_attribute.attr,
    NULL,
};

static const struct attribute_group eudyptula_group = {
    .attrs = eudyptula_attrs,
};

static int __init task09_init(void)
{
    int ret;

    eudyptula_kobj =
        kobject_create_and_add("eudyptula", kernel_kobj);
    if (!eudyptula_kobj) {
        pr_err("task09: failed to create "
               "/sys/kernel/eudyptula\n");
        return -ENOMEM;
    }

    ret = sysfs_create_group(eudyptula_kobj,
                             &eudyptula_group);
    if (ret) {
        pr_err("task09: failed to create "
               "sysfs attributes: %d\n",
               ret);

        kobject_put(eudyptula_kobj);
        eudyptula_kobj = NULL;

        return ret;
    }

    pr_info("task09: module loaded\n");
    pr_info("task09: sysfs attributes created in "
            "/sys/kernel/eudyptula\n");

    return 0;
}

static void __exit task09_exit(void)
{
    kobject_put(eudyptula_kobj);
    eudyptula_kobj = NULL;

    pr_info("task09: module unloaded\n");
}

module_init(task09_init);
module_exit(task09_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("biggvladik");
MODULE_DESCRIPTION(
    "Eudyptula Challenge Task 09 sysfs module"
);
MODULE_VERSION("1.0");
