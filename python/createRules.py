initial = ['std::string createIdentities(){\nstd::string identities = "";']
file1 = open('../cpp/rules/identities.txt', 'w')
file1.writelines(initial) 
 
  
# Using readlines() 
file2 = open('identities.txt', 'r') 
lines = file2.readlines() 
  
count = 0
# Strips the newline character 
for line in lines:
	line = 'identities += "'+line+'";'
	file1.writelines([line])
    

file1.close()