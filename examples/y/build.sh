#!/bin/bash
# Compile Console Library
mono yc.exe console.y console.lib -lib
# Compile Program
mono yc.exe helloy.y ./bin/helloy.asm