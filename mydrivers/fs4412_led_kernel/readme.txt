/*  difference between 2.4 and 2.6 */

API
  2.2-->2.4-->2.6-->3.x API
NAME
  对于使用模块的授权用户而言，模块最直观的改变应是模块后缀由原先的 .o 文件（即 object）变成了 .ko 文件（即 kernel object）。

TOOL
  在 Linux 2.6 中，模块使用了新的装卸载工具集 module-init-tools（工具 insmod 和 rmmod 被重新设计）。


/***************************

	Module.symvers

****************************/

http://www.ibm.com/developerworks/cn/linux/l-cn-kernelmodules/index.html

可装载模块还为内核节省了内存空间，因为模块一般是在真正需要时才被加载。根据模块作用，可装载模块还可分三大类型：设备驱动、文件系统和系统调用。


动态模块构建指导：
Documents/kbuild/modules.txt，
Module versioning is enabled by the CONFIG_MODVERSIONS tag, and is used
as a simple ABI consistency check. A CRC value of the full prototype
for an exported symbol is created. When a module is loaded/used, the
CRC values contained in the kernel are compared with similar values in
the module; if they are not equal, the kernel refuses to load the module.
Module.symvers contains a list of all exported symbols from a kernel build.


 /* include/linux/module.h */ 
 struct modversion_info 
 { 
     unsigned long crc; 
     char name[MODULE_NAME_LEN]; 
 };

结构体 modversion_info 中保存了用于模块校验的 CRC（Cyclic Redundancy Check，即循环冗余码校验）值。


通常，内核与模块的导出符号的 CRC 值被保存在文件 Module.symvers 中，该文件需在开启内核配置选项 CONFIG_MODVERSIONS 之后并完全编译内核获得
（或者您也可在编译外部模块后获得该文件，保存的是模块的导出符号的 CRC 信息），其信息的保存格式如清单 5 所示。

清单 5. 导出符号的 CRC 值
 0x1de386dd  module_layout   vmlinux  EXPORT_SYMBOL 
  <CRC>        <Symbol>      <module>


Example:

Freescale i.MX Community,

Module.symvers:


0x00000000	unregister_vt_notifier	vmlinux	EXPORT_SYMBOL_GPL
0x00000000	generic_file_splice_write	vmlinux	EXPORT_SYMBOL
0x00000000	set_anon_super	vmlinux	EXPORT_SYMBOL
0x00000000	kmem_cache_alloc	vmlinux	EXPORT_SYMBOL
0x00000000	__cond_resched_softirq	vmlinux	EXPORT_SYMBOL
0x00000000	i2c_put_adapter	vmlinux	EXPORT_SYMBOL
0x00000000	rtc_class_open	vmlinux	EXPORT_SYMBOL_GPL
0x00000000	scsi_sense_key_string	vmlinux	EXPORT_SYMBOL
0x00000000	request_firmware	vmlinux	EXPORT_SYMBOL
0x00000000	unblock_all_signals	vmlinux	EXPORT_SYMBOL
0x00000000	dev_uc_sync	vmlinux	EXPORT_SYMBOL
0x00000000	dev_mc_sync	vmlinux	EXPORT_SYMBOL
0x00000000	hwmon_device_unregister	vmlinux	EXPORT_SYMBOL_GPL
0x00000000	register_timer_hook	vmlinux	EXPORT_SYMBOL_GPL
0x00000000	csum_partial	vmlinux	EXPORT_SYMBOL
0x00000000	unregister_timer_hook	vmlinux	EXPORT_SYMBOL_GPL
0x00000000	ps2_end_command	vmlinux	EXPORT_SYMBOL
0x00000000	scsi_execute	vmlinux	EXPORT_SYMBOL
0x00000000	proc_net_remove	vmlinux	EXPORT_SYMBOL_GPL
0x00000000	raw_seq_open	vmlinux	EXPORT_SYMBOL_GPL
0x00000000	device_add	vmlinux	EXPORT_SYMBOL_GPL
0x00000000	device_del	vmlinux	EXPORT_SYMBOL_GPL
0x00000000	crypto_hash_walk_done	vmlinux	EXPORT_SYMBOL_GPL
0x00000000	profile_event_unregister	vmlinux	EXPORT_SYMBOL_GPL
0x00000000	init_uts_ns	vmlinux	EXPORT_SYMBOL_GPL
0x00000000	dst_release	vmlinux	EXPORT_SYMBOL
0x00000000	sock_no_mmap	vmlinux	EXPORT_SYMBOL
0x00000000	mxs_saif_dai	vmlinux	EXPORT_SYMBOL_GPL
0x00000000	disk_map_sector_rcu	vmlinux	EXPORT_SYMBOL_GPL
0x00000000	sysfs_update_group	vmlinux	EXPORT_SYMBOL_GPL
0x00000000	tcp_initialize_rcv_mss	vmlinux	EXPORT_SYMBOL



/***************************

	Module.symvers

****************************/

modules.order：这个文件记录了Makefile中模块出现的顺序。
modprobe通过它来确定解决多个模块匹配的别名（指定模块的绝对路径）。

