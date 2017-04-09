#!/usr/bin/python
import serial
#import time, datetime


#dateString = '%Y/%m/%d , %H:%M:%S' 

ser = serial.Serial('/dev/ttyAMA0',115200)
ser.open()

try:
	while 1:
		response = ser.readline()
		print response
		#f=open('/mnt/4GB_USB/dataLog.csv','a')
		f=open('/var/www/dataLog.csv','a')
		#gettime = datetime.datetime.now().strftime(dateString)
		#f.write(gettime)
		#f.write(" , ")
		f.write(response)
		#print >> f, datetime.datetime.now().strftime(dateString), ',', response
		f.close()

except KeyboardInterrupt:
	print"\ndone"
