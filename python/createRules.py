initial = ['std::vector<std::string> createIdentities(){\nstd::vector<std::string> identities;\n']
end = ['return identities;\n}\n']
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

initial = ['std::vector<std::string> createArithmetic(){\nstd::vector<std::string> arithmetic;\n']
end = ['return arithmetic;\n}\n']
file1 = open('../cpp/rules/arithmetic.cpp', 'w')
file1.writelines(initial) 
 
  
# Using readlines() 
file2 = open('arithmetic.txt', 'r') 
lines = file2.readlines() 
  
count = 0
# Strips the newline character 
for line in lines:
	line = 'arithmetic.push_back("'+line.strip()+'");\n'
	file1.writelines([line])

file1.writelines(end)
file1.close()

initial = ['std::vector<std::string> createCanonical(){\nstd::vector<std::string> canonical;\n']
end = ['return canonical;\n}\n']
file1 = open('../cpp/rules/canonical.cpp', 'w')
file1.writelines(initial) 
 
  
# Using readlines() 
file2 = open('canonical.txt', 'r') 
lines = file2.readlines() 
  
count = 0
# Strips the newline character 
for line in lines:
	line = 'canonical.push_back("'+line.strip()+'");\n'
	file1.writelines([line])

file1.writelines(end)
file1.close()

