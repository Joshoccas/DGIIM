#!/bin/bash
/usr/bin//valgrind --leak-check=full ./dist/Debug/GNU-Linux/shopping4 -noargs < ./tests/validation/ErrorLoading.keyboard 1> /dev/null 2>> ./tests/output/ErrorLoading.mleaks.full
