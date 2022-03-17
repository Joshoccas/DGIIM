#!/bin/bash
/usr/bin//valgrind --leak-check=full ./dist/Debug/GNU-Linux/shopping4 -input ./data/ECommerce41.dataset -events 30 -index-by UserID -report-by Type -output ./data/ECommerce41-hit2.dataset < ./tests/validation/ECommerce41.keyboard 1> /dev/null 2>> ./tests/output/ECommerce41.mleaks.full
