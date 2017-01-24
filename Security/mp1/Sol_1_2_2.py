import sys
from Crypto.Cipher import AES

with open('1.2.2_aes_key.hex') as f1 :
    aes_key_text=f1.read().strip()
    aes_key=aes_key_text.decode('hex')
with open('1.2.2_aes_iv.hex') as f2:
    aes_iv_text=f2.read().strip()
    aes_iv=aes_iv_text.decode('hex')
with open('1.2.2_aes_ciphertext.hex') as f3:
    aes_ciphertext=f3.read().strip()
    aes_cipherbinary=aes_ciphertext.decode('hex')

cipher = AES.new(aes_key, AES.MODE_CBC, aes_iv )
new_text=cipher.decrypt(aes_cipherbinary)
print(new_text)
