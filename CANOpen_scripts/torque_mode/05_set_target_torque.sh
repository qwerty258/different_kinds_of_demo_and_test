#!/bin/bash
cansend can0 601#2B716000D9FD       # set target torque
sleep 5
cansend can0 601#40646000
cansend can0 601#2B7160002C01
sleep 5
cansend can0 601#40646000
cansend can0 601#2B7160000000
