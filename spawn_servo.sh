#! /usr/bin/expect -f
set timeout 1              
spawn setserial /dev/servo low_latency
send_user "\n It's OK\r"
interact
