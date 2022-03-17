#!/bin/bash
/usr/bin//valgrind --leak-check=full ./dist/Debug/GNU-Linux/shopping1_s < ./tests/validation/ECommerce5.keyboard 1> /dev/null 2>> ./tests/output/ECommerce5.mleaks.full
