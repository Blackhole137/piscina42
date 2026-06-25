#!/bin/sh
head -c 40 /dev/zero > testShell00
touch -t 06012342 testShell00
chmod 455 testShell00
tar -cf testShell00.tar testShell00
