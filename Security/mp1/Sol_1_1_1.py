import sys
import Crypto

with open('1.1.2_value.hex') as f :
    file_content=f.read().strip()

print (len(binary_content))
integer_parsed =int(file_content,16)
binary_content=bin(integer_parsed)[2:]

solution_file1=open('sol_1.1.2_decimal.txt','w+')
solution_file1.write(str(integer_parsed))
solution_file1.close()

solution_file2=open('sol_1.1.2_binary.txt','w+')
solution_file2.write(str(binary_content))
solution_file2.close()
