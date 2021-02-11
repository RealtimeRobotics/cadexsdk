#
# Regular cron jobs for the cadexsdk package
#
0 4	* * *	root	[ -x /usr/bin/cadexsdk_maintenance ] && /usr/bin/cadexsdk_maintenance
