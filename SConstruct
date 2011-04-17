# -*- coding: utf-8 -*-
#
# SConstruct for UnArk

unark = Program('unark.cpp', LIBS='dl')
Clean(unark, '테스트.txt')
Default(unark)

prefix = '/usr/local'
lib_dir = prefix + '/lib'
bin_dir = prefix + '/bin'

Install(lib_dir, 'libark32.so')
Install(bin_dir, unark)
Alias('install', [lib_dir, bin_dir])
