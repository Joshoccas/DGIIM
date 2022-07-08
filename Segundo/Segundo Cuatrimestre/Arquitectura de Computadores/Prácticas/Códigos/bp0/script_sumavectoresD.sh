#!/bin/bash

for (( CONTADOR=65536; CONTADOR<=67108864; CONTADOR*=2)) ; do
  ./SumaVectoresD $CONTADOR
done
