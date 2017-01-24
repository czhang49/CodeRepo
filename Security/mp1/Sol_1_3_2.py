with open('1.3.2_input_string.txt') as f :
    input_str=f.read().strip()

input_str='Hlleo wlrod!'
int1=int('0xCC',16)
int2=int('0x33',16)
int3=int('0xAA',16)
int4=int('0x55',16)

Mask=int('0x3FFFFFFF',16)
outHash=0
for byte in input_str:
    integer=ord(byte)
    intermediate= ((integer^int1)<<24) | ((integer^int2)<<16) | ((integer^int3)<<8) | (integer^int4)
    outHash= (outHash & Mask) + (intermediate & Mask)
    #print(bin(outHash)[2:].zfill(32))

print(hex(outHash))
#print(bin(outHash)[2:])
#print(bin(1)[2:])
