#! /usr/bin/expect -f
set timeout 1              
spawn setserial /dev/servo low_latency
interact
