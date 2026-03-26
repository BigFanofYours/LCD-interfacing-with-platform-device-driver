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
	{ 0x9f222e1e, "alloc_chrdev_region" },
	{ 0xa61fd7aa, "__check_object_size" },
	{ 0x092a35a2, "_copy_from_user" },
	{ 0x79fd4f39, "devm_kmalloc" },
	{ 0xd2e1e487, "gpiod_set_value" },
	{ 0x4695bf9b, "platform_driver_unregister" },
	{ 0xa1dacb42, "class_destroy" },
	{ 0xd272d446, "__fentry__" },
	{ 0xe8213e80, "_printk" },
	{ 0xbd03ed67, "__ref_stack_chk_guard" },
	{ 0xd272d446, "__stack_chk_fail" },
	{ 0x9b1de7cb, "_dev_info" },
	{ 0x90a48d82, "__ubsan_handle_out_of_bounds" },
	{ 0x8ea73856, "cdev_add" },
	{ 0x9b1de7cb, "_dev_err" },
	{ 0x2bf498f8, "gpiod_direction_input" },
	{ 0x653aa194, "class_create" },
	{ 0xd272d446, "__x86_return_thunk" },
	{ 0x223cc85c, "__platform_driver_register" },
	{ 0xdd6830c7, "sprintf" },
	{ 0x3cc75249, "device_create_with_groups" },
	{ 0x0bc5fb0d, "unregister_chrdev_region" },
	{ 0xcbae5412, "__const_udelay" },
	{ 0x8d6a2b09, "devm_gpiod_get" },
	{ 0x1595e410, "device_destroy" },
	{ 0x546c19d9, "validate_usercopy_range" },
	{ 0x1f55c5b2, "kstrtoll" },
	{ 0xd2e1e487, "gpiod_direction_output" },
	{ 0xd5f66efd, "cdev_init" },
	{ 0x4e54d6ac, "cdev_del" },
	{ 0xbebe66ff, "module_layout" },
};

static const u32 ____version_ext_crcs[]
__used __section("__version_ext_crcs") = {
	0x9f222e1e,
	0xa61fd7aa,
	0x092a35a2,
	0x79fd4f39,
	0xd2e1e487,
	0x4695bf9b,
	0xa1dacb42,
	0xd272d446,
	0xe8213e80,
	0xbd03ed67,
	0xd272d446,
	0x9b1de7cb,
	0x90a48d82,
	0x8ea73856,
	0x9b1de7cb,
	0x2bf498f8,
	0x653aa194,
	0xd272d446,
	0x223cc85c,
	0xdd6830c7,
	0x3cc75249,
	0x0bc5fb0d,
	0xcbae5412,
	0x8d6a2b09,
	0x1595e410,
	0x546c19d9,
	0x1f55c5b2,
	0xd2e1e487,
	0xd5f66efd,
	0x4e54d6ac,
	0xbebe66ff,
};
static const char ____version_ext_names[]
__used __section("__version_ext_names") =
	"alloc_chrdev_region\0"
	"__check_object_size\0"
	"_copy_from_user\0"
	"devm_kmalloc\0"
	"gpiod_set_value\0"
	"platform_driver_unregister\0"
	"class_destroy\0"
	"__fentry__\0"
	"_printk\0"
	"__ref_stack_chk_guard\0"
	"__stack_chk_fail\0"
	"_dev_info\0"
	"__ubsan_handle_out_of_bounds\0"
	"cdev_add\0"
	"_dev_err\0"
	"gpiod_direction_input\0"
	"class_create\0"
	"__x86_return_thunk\0"
	"__platform_driver_register\0"
	"sprintf\0"
	"device_create_with_groups\0"
	"unregister_chrdev_region\0"
	"__const_udelay\0"
	"devm_gpiod_get\0"
	"device_destroy\0"
	"validate_usercopy_range\0"
	"kstrtoll\0"
	"gpiod_direction_output\0"
	"cdev_init\0"
	"cdev_del\0"
	"module_layout\0"
;

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "640E9C30260F6E401EFED97");
