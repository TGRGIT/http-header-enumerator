#!/bin/bash
 for i in `seq 1 90000`; do
     echo $((RANDOM%256)).$((RANDOM%256)).$((RANDOM%256)).$((RANDOM%256))
 done
