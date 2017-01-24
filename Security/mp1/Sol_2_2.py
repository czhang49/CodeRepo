import sys
import Crypto

with open('2.2_public_key.hex') as f :
    file_content=f.read().strip()
integer_pubkey =int(file_content,16)

with open('2.2_modulo.hex') as f :
    file_content=f.read().strip()
integer_modulo=int(file_content,16)

with open('2.2_ciphertext.hex') as f :
    file_content=f.read().strip()
integer_cipher =int(file_content,16)

print integer_pubkey
print integer_modulo
print integer_cipher
