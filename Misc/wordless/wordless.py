#!/usr/bin/env python2.7
from string import *
import re

del __builtins__.__import__

banned = letters + digits + whitespace + re.escape('_.+=;\\')
code = raw_input('>>> ')

if not re.findall(r'[%s]' % banned, code):
    try:
        exec('exec %s' % code, {'__builtins__': None}, {})
    except:
        pass