#include <linux/fs.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/string.h>
#include <linux/uaccess.h>

#define EUDYPTULA_ID "biggvladik"
#define EUDYPTULA_ID_LEN (sizeof(EUDYPTULA_ID) - 1)

MODULE_AUTHOR("biggvladik");
MODULE_DESCRIPTION("Eudyptula Task 06 misc character device");
MODULE_LICENSE("Dual MIT/GPL");
MODULE_VERSION("0.1");

static ssize_t eudyptula_read(struct file *file,
			      char __user *buf,
			      size_t count,
			      loff_t *ppos)
{
	return simple_read_from_buffer(buf,
				       count,
				       ppos,
				       EUDYPTULA_ID,
				       EUDYPTULA_ID_LEN);
}
							

static ssize_t eudyptula_write(struct file *file,
			       const char __user *buf,
			       size_t count,
			       loff_t *ppos)
{
	char input[EUDYPTULA_ID_LEN];

	
	if (count != EUDYPTULA_ID_LEN)
		return -EINVAL;

	if (copy_from_user(input, buf, EUDYPTULA_ID_LEN))
		return -EFAULT;

	if (memcmp(input, EUDYPTULA_ID, EUDYPTULA_ID_LEN) != 0)
		return -EINVAL;

	return count;
}


static const struct file_operations eudyptula_fops = {
	.owner = THIS_MODULE,
	.read = eudyptula_read,
	.write = eudyptula_write,
};

static struct miscdevice eudyptula_device = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "eudyptula",
	.fops = &eudyptula_fops,
};


static int __init helloworld_lkm_init(void)
{
	int ret;

	ret = misc_register(&eudyptula_device);
	if (ret) {
		pr_err("eudyptula: misc_register failed: %d\n", ret);
		return ret;
	}

	pr_info("eudyptula: /dev/eudyptula registered\n");
	return 0;
}

static void __exit helloworld_lkm_exit(void)
{
	misc_deregister(&eudyptula_device);
	pr_info("eudyptula: /dev/eudyptula unregistered\n");
}

module_init(helloworld_lkm_init);
module_exit(helloworld_lkm_exit);

