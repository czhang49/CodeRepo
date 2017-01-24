
input_string='801fa18410cecf55ca85cef014633d9d4895addaac5cfe9077baaa80853ef0d0'
perturbed_string='a12817ab7a0b711d07ac2a58de44e7a4c75cdab338d382364886451e055c5795'

input_number =int(input_string,16)
perturbed_number=int(perturbed_string,16)

input_binary=bin(input_number)[2:]
perturbed_binary=bin(perturbed_number)[2:]

print(input_binary)
print(perturbed_binary)
