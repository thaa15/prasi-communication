#!/bin/bash
ontemp=40
gpio -g mode 12 out
temp=$(vcgencmd measure_temp | egrep -o '[0-9]*\.[0-9]*')
echo $temp
temp0=${temp%.*}
echo $temp0

if [ $temp0 -gt $ontemp ]
then
	echo greater than $ontemp fan on
	gpio -g write 12 1
else
	echo less than or equal to $ontemp fan off
	gpio -g write 12 0
fi
