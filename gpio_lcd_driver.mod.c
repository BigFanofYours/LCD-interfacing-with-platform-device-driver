#include <linux/module.h>
#include <linux/export-internal.h>
#include <linux/compiler.h>

MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};



static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x3cc75249, "device_create_with_groups" },
	{ 0x9b1de7cb, "_dev_info" },
	{ 0x9b1de7cb, "_dev_err" },
	{ 0x653aa194, "class_create" },
	{ 0x223cc85c, "__platform_driver_register" },
	{ 0x4695bf9b, "platform_driver_unregister" },
	{ 0xa1dacb42, "class_destroy" },
	{ 0xd272d446, "__fentry__" },
	{ 0xd272d446, "__x86_return_thunk" },
	{ 0x7d74049b, "device_unregister" },
	{ 0xdd6830c7, "sprintf" },
	{ 0xe8213e80, "_printk" },
	{ 0x79fd4f39, "devm_kmalloc" },
	{ 0x8d6a2b09, "devm_gpiod_get" },
	{ 0x9f222e1e, "alloc_chrdev_region" },
	{ 0xd5f66efd, "cdev_init" },
	{ 0x8ea73856, "cdev_add" },
	{ 0xbebe66ff, "module_layout" },
};

static const u32 ____version_ext_crcs[]
__used __section("__version_ext_crcs") = {
	0x3cc75249,
	0x9b1de7cb,
	0x9b1de7cb,
	0x653aa194,
	0x223cc85c,
	0x4695bf9b,
	0xa1dacb42,
	0xd272d446,
	0xd272d446,
	0x7d74049b,
	0xdd6830c7,
	0xe8213e80,
	0x79fd4f39,
	0x8d6a2b09,
	0x9f222e1e,
	0xd5f66efd,
	0x8ea73856,
	0xbebe66ff,
};
static const char ____version_ext_names[]
__used __section("__version_ext_names") =
	"device_create_with_groups\0"
	"_dev_info\0"
	"_dev_err\0"
	"class_create\0"
	"__platform_driver_register\0"
	"platform_driver_unregister\0"
	"class_destroy\0"
	"__fentry__\0"
	"__x86_return_thunk\0"
	"device_unregister\0"
	"sprintf\0"
	"_printk\0"
	"devm_kmalloc\0"
	"devm_gpiod_get\0"
	"alloc_chrdev_region\0"
	"cdev_init\0"
	"cdev_add\0"
	"module_layout\0"
;

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "E5064B5CE14CDCCDB35F8EE");
