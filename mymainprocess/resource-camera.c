#include "resources.h"

void *camera_fun()
{
	system("/usr/sbin/motion -c /etc/motion.conf & ");
}
