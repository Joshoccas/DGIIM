#!/bin/bash
/usr/bin//valgrind --leak-check=full ./dist/Debug/GNU-Linux/shopping3 -noargs < ./tests/validation/ErrorSaving.keyboard 1> /dev/null 2>> ./tests/output/ErrorSaving.mleaks.full
