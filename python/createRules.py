initial = ['std::vector<std::string> createIdentities(){\nstd::vector<std::string> identities;\n']
end = ['return identitites;\n}\n']
file1 = open('../cpp/rules/identities.cpp', 'w')
file1.writelines(initial) 
 
  
# Using readlines() 
file2 = open('identities.txt', 'r') 
lines = file2.readlines() 
  
count = 0
# Strips the newline character 
for line in lines:
	line = 'identities.push_back("'+line.strip()+'");\n'
	file1.writelines([line])

file1.writelines(end)
file1.close()