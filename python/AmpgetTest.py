# -*- coding: utf-8 -*-
"""
Created on Tue Nov 23 11:14:55 2021

@author: EPsajd
"""

import datalink as dl 

print("Hello world")

resource_manager = dl.resourceCreate()
scope_handle = dl.initScope(resource_manager)


ch = 1
a = dl.Ampget(scope_handle, ch) 
print(a)