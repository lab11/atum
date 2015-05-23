#!/usr/bin/env python3

import asyncio
import aiocoap.resource as aiocoapresource
import aiocoap
import serial

import datetime

#s = serial.Serial('/dev/ttyUSB1', 115200)
s = serial.Serial('/dev/tty.usbserial-0000111DB', 115200)


def test_serial():
	'''
	read a line and print.
	'''
	text = ""
	msg = s.read().decode()
	while (msg != '\n'):
		text += msg
		msg = s.read().decode()

	fields = text.split('=')

	if len(fields) == 2:
		param = fields[0].strip()
		val = fields[1].strip()
		print('{} :: {}'.format(param, val))

		vals = val.split()

		if param == 'VDD':
			vdd = int(vals[0])
			vdd_res.new_data(vdd)

		elif param == 'Temperature':
			temp = int(vals[0])/1000
			temp_res.new_data(temp)

		elif param == 'Ambient light sensor':
			light = int(vals[0])
			light_res.new_data(light)


class obs_resource (aiocoapresource.ObservableResource):
	def __init__ (self):
		super(obs_resource, self).__init__()
		self.val = ''

	@asyncio.coroutine
	def render_get (self, request):
		payload = '{}'.format(self.val).encode('ascii')
		return aiocoap.Message(code=aiocoap.CONTENT, payload=payload)

	def new_data (self, val):
		self.val = val
		self.updated_state()


root = aiocoapresource.Site()

vdd_res = obs_resource()
temp_res = obs_resource()
light_res = obs_resource()

root.add_resource(('vdd',), vdd_res)
root.add_resource(('temp',), temp_res)
root.add_resource(('light',), light_res)

asyncio.async(aiocoap.Context.create_server_context(root))

loop = asyncio.get_event_loop()
loop.add_reader(s, test_serial)
try:
	loop.run_forever()
except KeyboardInterrupt:
	pass
finally:
	loop.close()

