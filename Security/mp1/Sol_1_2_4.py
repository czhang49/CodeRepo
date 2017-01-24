from Crypto.PublicKey import RSA
import math

with open('1.2.4_private_key.hex') as f1 :
    private_key_hex=f1.read().strip()
with open('1.2.4_RSA_modulo.hex') as f2 :
    private_modulo_hex=f2.read().strip()
with open('1.2.4_RSA_ciphertext.hex') as f3 :
    private_ciphertext=f3.read().strip()

key=int(private_key_hex,16)
modulo=int(private_modulo_hex,16)
cipher=int(private_ciphertext,16)


print(key)
print(modulo)
print(cipher)
