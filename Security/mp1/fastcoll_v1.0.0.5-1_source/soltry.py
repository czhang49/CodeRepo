#!/usr/bin/python
# -*- coding: utf-8 -*-
blob = """
           ���L>P�3�wx�DD�vv2�o�dd�;�t&�г���h��g>�!>~2'�
D[~��?>�p<��$��e��[��q�I�E��V���i_���_��A���j��[�g��Si�c`��'�Σm�)�B
"""
from hashlib import sha256
aa=sha256(blob).hexdigest()

if aa=="52249adf292338b1a71e177a64c9e646c7adb8613a52acab9706effd3afaeb67":
    print "I come in peace."
if aa=="348be93c6c16936230829b47525b581e60fe4fbad1212a7056dbf2e5aada05ee":
    print "Prepare to be destroyed!"
