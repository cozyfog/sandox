#!/bin/bash
clear && gcc src/*.c -std=c11 -Wall -Iinclude/ -lGL -lGLU -lglut -lm -obin/just_chilln.o  # XXX RELEASE [ -s ]
chmod a+x bin/just_chilln.o && ./bin/just_chilln.o
