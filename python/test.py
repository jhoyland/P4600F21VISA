# -*- coding: utf-8 -*-
"""
Created on Thu Nov  4 09:51:35 2021

@author: texas
"""
# -*- coding: utf-8 -*-

import datalink as dl
scope_handle = None
func_handle = None
frequency = 200

status, scope, funcGen = dl.openInstruments()

print(scope, " ", funcGen)

