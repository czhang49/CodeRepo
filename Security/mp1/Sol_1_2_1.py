import sys
import Crypto

with open('1.2.1_sub_key.txt') as f1 :
    sub_key=f1.read().strip()
with open('1.2.1_sub_ciphertext.txt') as f2:
    sub_text=f2.read().strip()
alphabet=['A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z']

solution_file1=open('sol_1.2.1.txt','w')
for i in range (0,len(sub_text)-1):
    orig_let=sub_text[i]
    new_let=orig_let
    for k in range (0,len(alphabet)-1):
        if orig_let==sub_key[k]:
            new_let=alphabet[k]
    solution_file1.write(str(new_let))
solution_file1.close()
