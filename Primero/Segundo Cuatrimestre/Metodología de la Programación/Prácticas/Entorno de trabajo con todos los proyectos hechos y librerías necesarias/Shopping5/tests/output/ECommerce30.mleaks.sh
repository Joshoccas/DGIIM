#!/bin/bash
/usr/bin//valgrind --leak-check=full ./dist/Debug/GNU-Linux/shopping4 -input ./data/ECommerce30.dataset -events 30 -index-by Brand -report-by Brand < ./tests/validation/ECommerce30.keyboard 1> /dev/null 2>> ./tests/output/ECommerce30.mleaks.full
