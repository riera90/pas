#!/bin/bash
for it in $(cat IPs.txt | grep -E ^[0-9]); do ping -c 1 $it ; done
