#!/bin/bash
cansend can0 601#40406000           # read control word
cansend can0 601#2B4060000600       # set control word enable voltage
cansend can0 601#2B4060000700       # set control word switch on
cansend can0 601#2B4060000F00       # set control word enable motor
