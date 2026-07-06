#include <linux/init.h>
#include <linux/module.h>

MODULE_AUTHOR("biggvladik");
MODULE_DESCRIPTION("hello_world module");
MODULE_LICENSE("Dual MIT/GPL");
MODULE_VERSION("0.1");


static int __init helloworld_lkm_init(void) {
	pr_debug("Hello, world!\n");
	return 0;
	
}

static void __exit helloworld_lkm_exit(void) {
	
	pr_debug("Goodbye, world!\n");
	}
	
module_init(helloworld_lkm_init);
module_exit(helloworld_lkm_exit);
