#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");

int module_start()
{
	printf("hello");
	return 0;
}

void module_end()
{
	printf("bye");
}

module_init(module_start);
module_exit(module_end);
