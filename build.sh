#!/bin/bash
clear && gcc src/*.c -std=c11 -Wall -Iinclude/ -lGL -lGLU -lglut -lm -obin/sandbox.x86_64  # XXX RELEASE [ -s ]
chmod a+x bin/sandbox.x86_64 && ./bin/sandbox.x86_64
