#include <linux/init.h>
#include <linux/module.h>
#include <linux/usb.h>


MODULE_AUTHOR("biggvladik");
MODULE_DESCRIPTION("hello_world module");
MODULE_LICENSE("Dual MIT/GPL");
MODULE_VERSION("0.1");



static const struct usb_device_id mouse_device_table[] = {
	{
		USB_INTERFACE_INFO(
			USB_CLASS_HID,
			1,
			2
		)
	},
	{ }
};



MODULE_DEVICE_TABLE(usb, mouse_device_table);

static int __init helloworld_lkm_init(void)
{
	pr_debug("Hello, world!\n");

	return 0;
}

static void __exit helloworld_lkm_exit(void)
{
	pr_debug("Goodbye, world!\n");
}

module_init(helloworld_lkm_init);
module_exit(helloworld_lkm_exit);
