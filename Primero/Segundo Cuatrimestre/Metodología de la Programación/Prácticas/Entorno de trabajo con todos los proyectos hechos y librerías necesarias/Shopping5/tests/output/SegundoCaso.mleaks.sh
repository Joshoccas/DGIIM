#!/bin/bash
/usr/bin//valgrind --leak-check=full ./dist/Debug/GNU-Linux/shopping5 -input ./data/SegundoCaso.dataset -events 400 -K 100 -type cart < ./tests/validation/SegundoCaso.keyboard 1> /dev/null 2>> ./tests/output/SegundoCaso.mleaks.full
