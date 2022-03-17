#!/bin/bash
/usr/bin//valgrind --leak-check=full ./dist/Debug/GNU-Linux/shopping4 -input ./data/ECommerce5.dataset -events 5 -index-by UserID -report-by DateTime -output ./data/ECommerce5-hit2.dataset < ./tests/validation/ECommerce5.keyboard 1> /dev/null 2>> ./tests/output/ECommerce5.mleaks.full
