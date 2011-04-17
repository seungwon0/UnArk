# -*- coding: utf-8 -*-
#
# SConstruct for UnArk

prefix = '/usr/local'
lib_dir = prefix + '/lib'
bin_dir = prefix + '/bin'

unark = Program('unark.cpp', LIBS='dl')

Clean(unark, '테스트.txt')

Default(unark)

Install(lib_dir, 'libark32.so')
Install(bin_dir, unark)

Alias('install', [lib_dir, bin_dir])
