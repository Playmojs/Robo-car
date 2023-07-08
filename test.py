import struct

bytestring = b'\x8d\xb0\x83B\x00\x00\x00\x00rO\xfbA\x00\x00\x00\x00rO\xb5B\x00\x00\x00\x00\x12\x96\xebA\x00\x00\x00\x00\x84\xe5\xb5B\x00\x00\x00\x00{\x1a1B\x00\x00\x00\x005\xc2vB\x00\x00\x00\x00\x8d\xb0\x87B\x00\x00\x00\x00+\xf7~B\x00\x00\x00\x00\x9eF>B\x00\x00\x00\x00\xf74\x9fB\x00\x00\x00\x00X\xeeUB\x00\x00\x00\x00`\xb9]B\x00\x00\x00\x005\xc2\x93B\x00\x00\x00\x00\xb0\xdckB\x00\x00\x00\x00\xe5\x9eJB\x00\x00\x00\x00\xb9\xa7\x8fB\x00\x00\x00\x00j\x84\x83B\x00\x00\x00\x00\x12\x96\x8dB:\r\n'


visual_data = [None]*37
for i in range(0, 37):
    visual_data[i] = struct.unpack('<f', bytestring[4*i:4*i+4])[0]
print(visual_data)

print(visual_data[0] + visual_data[2])