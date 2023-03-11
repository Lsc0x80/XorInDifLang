import base64, itertools, os
def xor(data, key='myawesomekey', encode=False, decode=False):
	if decode:
		data = base64.b64decode(data).decode('ascii')
	data = "".join([chr(ord(c1) ^ ord(c2)) for (c1,c2) in zip(data, itertools.cycle(key))])
	if encode:
		return base64.b64encode(data.encode('ascii')).decode('ascii')
	return data
def wait():
	input('Press enter to continue')
	os.system('clear')
while True:
	print('What yo want? [E]ncrypt OR [D]ecode')
	chs = input('>>>').lower()[0]
	if chs == 'e':
		print(xor(input('data: '), input('key: '), encode=True))
		wait()
	elif chs == 'd':
		print(xor(input('data: '), input('key: '), decode=True))
		wait()
	else:
		print('Invalid choose')
		wait()
