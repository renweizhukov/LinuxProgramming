#!/usr/bin/env python
# -*- coding: utf-8 -*-

import subprocess
proc = subprocess.Popen(['./helloworld'], stdout=subprocess.PIPE)
#works in python 3.0+
#for line in proc.stdout:
for line in iter(proc.stdout.readline,''):
   print line.rstrip()
