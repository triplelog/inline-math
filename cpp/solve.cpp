Number mulTwo(const Number numA, const Number numB);
Number reduceFraction(const Number numA);
std::vector<int> factorList(Number n){
	std::vector<int> list;
	if (n.type != 1 && n.type != 1){
		return list;
	}
	long nn = std::stoi(n.top);
	int p = 2;
	while (p <= nn){
		if (nn%p == 0){
			nn /= p;
			list.push_back(p);
		}
		p++;
	}
	return list;
}
std::vector<int> factorFull(Number n){
	std::vector<int> list;
	if (n.type != 1 && n.type != 1){
		return list;
	}
	long nn = std::stoi(n.top);
	int p = 2;
	while (p <= nn){
		if (nn%p == 0){
			nn /= p;
			list.push_back(p);
		}
		else {
			p++;
		}
	}
	return list;
}

std::string numberType(std::string input){
	Number n;
	n.type = 0;
	n.top = input;
	//TODO: add strings to numbers map with type==0
	if (input.length()==0){
		numbers[""]=n;
		return "string";
	}
	if (functionMap.find(input) != functionMap.end()){
		n.type = 16;
		n.top = input;
		n.bottom = "1";
		numbers[input]=n;
		return "num";
	}
	else if (input == "\\pi"){
		n.type = 11;
		n.top = "1";
		n.bottom = "\\pi";
		numbers[input]=n;
		//std::cout << "n1: " << outputNumber(n) << "\n";
		return "num";
	}
	else if (input == "i"){
		n.type = 11;
		n.top = "0,1";
		n.bottom = "complex";
		numbers[input]=n;
		//std::cout << "n1: " << outputNumber(n) << "\n";
		return "num";
	}
	else if (input == "e"){
		n.type = 11;
		n.top = "1:1,";
		n.bottom = "e";
		numbers[input]=n;
		//std::cout << "n1: " << outputNumber(n) << "\n";
		return "num";
	}
	else if (input.length()>3 && input.at(input.length()-2) == 'p' && input.at(input.length()-1) == 'i'){
		n.type = 11;
		if (numbers.find(input.substr(0,input.length()-3)) == numbers.end()){
			numberType(input.substr(0,input.length()-3));
		}
		n.top = outputNumber(numbers[input.substr(0,input.length()-3)]);
		n.bottom = "\\pi";
		numbers[input]=n;
		//std::cout << "n2: " << outputNumber(n) << "\n";
		return "num";
	}
	else if (input.length()>1 && input.at(input.length()-1) == 'i'){
		n.type = 11;
		if (numbers.find(input.substr(0,input.length()-1)) == numbers.end()){
			numberType(input.substr(0,input.length()-1));
		}
		Number nn = numbers[input.substr(0,input.length()-1)];
		if (nn.type == 0){
			n.type = 0;
			numbers[input]=n;
			return "string";
		}
		else if (nn.type > 9){
			n.type = 0;
			numbers[input]=n;
			return "string";
		}
		n.top = "0,"+outputNumber(nn);
		n.bottom = "complex";
		numbers[input]=n;
		//std::cout << "n2: " << outputNumber(n) << "\n";
		return "num";
	}
	else if (input.length()>1 && input.at(input.length()-1) == 'e'){
		n.type = 11;
		if (numbers.find(input.substr(0,input.length()-1)) == numbers.end()){
			numberType(input.substr(0,input.length()-1));
		}
		Number nn = numbers[input.substr(0,input.length()-1)];
		if (nn.type == 0){
			n.type = 0;
			numbers[input]=n;
			return "string";
		}
		else if (nn.type > 9){
			n.type = 0;
			numbers[input]=n;
			return "string";
		}
		n.top = "1:"+outputNumber(nn)+",";
		n.bottom = "e";
		numbers[input]=n;
		//std::cout << "n2: " << outputNumber(n) << "\n";
		return "num";
	}
	else if (input.length()>5 && input.at(0) == 's' && input.at(1) == 'q' && input.at(2) == 'r' && input.at(3) == 't'){
		int openPar = 0;
		int i;
		std::string root = "";
		if (input.at(4) == '(' && input.at(input.length()-1)==')'){
			for (i=4;i<input.length();i++){
				if (input.at(i)=='('){
					openPar++;
				}
				else if (input.at(i)==')'){
					openPar--;
				}
				else if (openPar > 0){
					root += input.at(i);
				}
			}
		}
		else {
			for (i=4;i<input.length();i++){
				if (input.at(i)=='('){
					openPar++;
					numbers[input]=n;
					return "string";
				}
				else if (input.at(i)==')'){
					openPar--;
					numbers[input]=n;
					return "string";
				}
				root += input.at(i);
			}
		}
		if (numbers.find(root) == numbers.end()){
			numberType(root);
		}
		Number nn = numbers[root];
		if (nn.type == 0){
			numbers[input]=n;
			return "string";
		}
		else {
			n.type = 11;
			n.top = outputNumber(nn)+":1";
			n.bottom = "sqrt";
			numbers[input]=n;
			return "num";
		}
		
	}
	
	if (input.at(0) == '-'){
		input.replace(0,1,"");
		std::string rest = "";
		if (input == "1"){
			n.type = -1;
			n.top = "1";
			n.bottom = "1";
			numbers["-1"]=n;
			return "num";
		}
		if (numbers.find(input) == numbers.end()){
			numberType(input);
		}
		Number nn = negateOne(numbers[input]);
		if (nn.type == 0){
			numbers["-"+input]= n;
			return "string";
		}
		else {
			numbers["-"+input]= nn;
			return "num";
		}
		
		
	}
	int ii;
	std::string currentType = "int";
	int idx = -1;
	for(ii=0;ii<input.length();ii++){
		switch(input.at(ii)){
			case '.': {
				if (currentType == "int"){currentType = "dec";}
				else if (currentType == "dec"){numbers[input]=n; return "string";}
				else if (currentType == "red"){numbers[input]=n; return "string";}
				else if (currentType == "rep"){numbers[input]=n; return "string";}
				else if (currentType == "fra"){numbers[input]=n; return "string";}
				else if (currentType == "sci" || currentType == "scn"){numbers[input]=n; return "string";}
				n.top = input.substr(0,ii);
				n.bottom = input.substr(ii+1,input.length()-ii-1);
				idx = ii;
				break;
			}
			case '_': {
				if (currentType == "int"){
					//currentType = "rep";
					//n.top = input.substr(0,ii);
					//n.bottom = input.substr(ii+1,input.length()-ii-1);
					numbers[input]=n; return "string";
				}
				else if (currentType == "dec"){currentType = "red"; idx = ii - idx;}
				else if (currentType == "red"){numbers[input]=n; return "string";}
				else if (currentType == "rep"){numbers[input]=n; return "string";}
				else if (currentType == "fra"){numbers[input]=n; return "string";}
				else if (currentType == "sci" || currentType == "scn"){numbers[input]=n; return "string";}
				break;
			}
			case 'e': {
				if (currentType == "int"){currentType = "sci";}
				else if (currentType == "dec"){currentType = "sci";}
				else if (currentType == "red"){currentType = "sci";}
				else if (currentType == "rep"){currentType = "sci";}
				else if (currentType == "fra"){numbers[input]=n; return "string";}
				else if (currentType == "sci" || currentType == "scn"){numbers[input]=n; return "string";}
				n.top = input.substr(0,ii);
				n.bottom = input.substr(ii+1,input.length()-ii-1);
				break;
			}
			case '-': {
				if (currentType == "int"){numbers[input]=n; return "string";}
				else if (currentType == "dec"){numbers[input]=n; return "string";}
				else if (currentType == "red"){numbers[input]=n; return "string";}
				else if (currentType == "rep"){numbers[input]=n; return "string";}
				else if (currentType == "fra"){numbers[input]=n; return "string";}
				else if (currentType == "sci"){currentType = "scn";}
				else if (currentType == "scn"){numbers[input]=n; return "string";}
				break;
			}
			case '/': {
				if (currentType == "int"){currentType = "fra";
					n.top = input.substr(0,ii);
					n.bottom = input.substr(ii+1,input.length()-ii-1);
					idx = ii;
				}
				else if (currentType == "dec"){numbers[input]=n; return "string";}
				else if (currentType == "red"){numbers[input]=n; return "string";}
				else if (currentType == "rep"){numbers[input]=n; return "string";}
				else if (currentType == "fra"){numbers[input]=n; return "string";}
				else if (currentType == "sci"){numbers[input]=n; return "string";}
				else if (currentType == "scn"){numbers[input]=n; return "string";}
				break;
			}
			case '0': break;
			case '1': break;
			case '2': break;
			case '3': break;
			case '4': break;
			case '5': break;
			case '6': break;
			case '7': break;
			case '8': break;
			case '9': break;
			default: numbers[input]=n; return "string";

		}
	}
	
	if (currentType == "int"){
		n.type = 1;
		n.top = input;
		n.bottom = "1";
		numbers[input]=n;
		return "int";
	}
	else if (currentType == "dec"){
		n.type = 2;
		std::string nb = n.bottom;
		n.top = n.top+n.bottom;
		int nbl = n.bottom.length();
		n.bottom = "1";
		int lastZero = -1;
		for (ii=0;ii<nbl;ii++){
			n.bottom += "0";
			if (nb.at(ii) != '0'){
				lastZero = ii;
			}
		}
		if (lastZero < nbl-1){
			n.top = n.top.substr(0,n.top.length()-(nbl-1-lastZero));
			n.bottom = n.bottom.substr(0,n.bottom.length()-(nbl-1-lastZero));
		}
		if (n.bottom == "1"){
			n.type = 1;
		}
		numbers[input]=n;
		return "dec";
	}
	else if (currentType == "fra"){
		n.type = 3;
		numbers[input]=n;
		if (n.bottom == "1"){
			n.type = 1;
		}
		return "fra";
	}
	else if (currentType == "red"){
		/*
		n.type = 5;
		//TODO: make correct top and bottom
		int repLen = n.bottom.length()-idx;
		int repTop = std::stoi(n.bottom.substr(idx,n.bottom.length()-idx));
		std::string repBot = "";
		for (ii=0;ii<repLen;ii++){
			repBot += "9";
		}
		if (numbers.find(repBot) == numbers.end()){
			numberType(repBot);
		}
		std::vector<int> fList = factorList(numbers[repBot]);
		numbers[input]=n;
		return "rep";
		*/
		numbers[input]=n;
		return "string";
	}
	else if (currentType == "sci" || currentType == "scn"){
		n.type = 4;
		numbers[input]=n;
		return "sci";
	}
	else {numbers[input]=n; return "string";}
	numbers[input]=n;
	return "string";
}

Number negateOne(const Number numA){
	Number n;
	if (numA.type == 11){
		n = mulTwo(numbers["-1"],numA);
		return n;
	}
	n.type = -1*numA.type;
	n.top = numA.top;
	n.bottom = numA.bottom;
	return n;
}

std::vector<Number> sqrtToN(const std::string top){
	std::string coef = "";
	std::string root = "";
	int i;
	bool isCoef = false;
	for (i=0;i<top.length();i++){
		if (top.at(i)==':'){
			isCoef = true;
		}
		else if (isCoef){
			coef += top.at(i);
		}
		else {
			root += top.at(i);
		}
	}
	
	if (numbers.find(coef) == numbers.end()){
		numberType(coef);
	}
	if (numbers.find(root) == numbers.end()){
		numberType(root);
	}
	std::vector<Number> vals;
	vals.push_back(numbers[root]);
	vals.push_back(numbers[coef]);
	return vals;
}

Number invertOne(const Number numA){
	Number n;
	if (numA.type == 0){
		n.type = 0; return n;
	}
	else if (numA.type == 1 || numA.type == -1){//integer
		if (numA.top == "1"){n = numA; return n;}
		if (numA.top == "0"){n.type = 0; return n;}
		n.type = 3*numA.type;
		n.top = "1";
		n.bottom = numA.top;
		return n;
	}
	else if (numA.type == 2 || numA.type == -2){//decimal
		//TODO: create decimal unless == 0
		if (numA.top == "0"){n.type = 0; return n;}
		if (numA.top == "1"){n.type = 1*numA.type/2; n.top = numA.bottom; n.bottom = "1"; return n;}
		n.type = numA.type;
		n.top = numA.bottom;
		n.bottom = numA.top;
		return n;
	}
	else if (numA.type == 3 || numA.type == -3){//fraction
		//TODO: create decimal unless == 0
		if (numA.top == "0"){n.type = 0; return n;}
		if (numA.top == "1"){n.type = 1*numA.type/3; n.top = numA.bottom; n.bottom = "1"; return n;}
		n.type = numA.type;
		n.top = numA.bottom;
		n.bottom = numA.top;
		return n;
	}
	else if (numA.type == 4 || numA.type == -4){//sci not
		//TODO: create sci not unless == 0
	}
	else if (numA.type == 5 || numA.type == -5){//rep decimal
		//TODO: do rep decimal inversion
	}
	else if (numA.type == 11 && numA.bottom == "sqrt"){
		std::vector<Number> rootCoef = sqrtToN(numA.top);
		string_log("rootCoef");
		string_log(numA.top.c_str());
		string_log(outputNumber(rootCoef[0]).c_str());
		string_log(outputNumber(rootCoef[1]).c_str());
		string_log(outputNumber(invertOne(rootCoef[0])).c_str());
		string_log(outputNumber(invertOne(rootCoef[1])).c_str());
		Number coef = mulTwo(invertOne(rootCoef[1]), invertOne(rootCoef[0]));
		string_log(outputNumber(coef).c_str());
		if (coef.type == 3 || coef.type == -3){
			coef = reduceFraction(coef);
		}
		else if (coef.type == 0){
			return n;
		}
		n.type = 11;
		n.top = outputNumber(rootCoef[0])+":"+outputNumber(coef);
		n.bottom = "sqrt";
		return n;
	}
	//TODO: create number type for division by zero
	return n;
}

bool isDecimal(Number n){
	int i;
	if (n.bottom.length()<1){
		return false;
	}
	if (n.bottom.at(0) != '1'){
		return false;
	}
	for (i=1;i<n.bottom.length();i++){
		if (n.bottom.at(i) != '0'){
			return false;
		}
	}
	return true;
}


std::string outputNumber(Number n){
	if (n.type == 1){
		return n.top;
	}
	else if (n.type == -1){
		if (n.top == "0"){
			return "0";
		}
		return "-"+n.top;
	}
	else if (n.type == 2){
		double d = std::stod(n.top);
		d /= std::stod(n.bottom);
		return std::to_string(d);
	}
	else if (n.type == -2){
		double d = std::stod(n.top);
		d /= std::stod(n.bottom);
		return "-"+std::to_string(d);
	}
	else if (n.type == 3){
		return n.top + "/"+n.bottom;
	}
	else if (n.type == -3){
		return "-"+n.top + "/"+n.bottom;
	}
	else if (n.type == 11){
		if (n.bottom == "complex"){
			int i; bool isReal = true;
			std::string realA = "";
			std::string imA = "";
			for (i=0;i<n.top.length();i++){
				if (n.top.at(i) == ','){
					isReal = false;
				}
				else if (isReal){
					realA += n.top.at(i);
				}
				else {
					imA += n.top.at(i);
				}
			}
			return realA+"+"+imA+"i";
		}
		else if (n.bottom == "\\pi"){
			return n.top+"\\pi";
		}
		else if (n.bottom == "e"){
			std::string outputE = "";
			int i; bool isReal = true;
			std::string realA = "";
			std::string imA = "";
			for (i=0;i<n.top.length();i++){
				if (n.top.at(i) == ':'){
					isReal = false;
				}
				else if (n.top.at(i) == ','){
					isReal = true;
					if (outputE.length()>0){
						outputE += "+";
					}
					outputE += imA+"*e^"+realA+"";
					realA = "";
					imA = "";
				}
				else if (isReal){
					realA += n.top.at(i);
				}
				else {
					imA += n.top.at(i);
				}
			}
			return outputE;
		}
		else if (n.bottom == "sqrt"){
			char sqrt{-67};
			std::string sqrtstr(1,sqrt);
			std::string outputE = "";
			int i; bool isCoef = false;
			std::string root = "";
			std::string coef = "";
			for (i=0;i<n.top.length();i++){
				if (n.top.at(i) == ':'){
					isCoef = true;
				}
				else if (isCoef){
					coef += n.top.at(i);
				}
				else {
					root += n.top.at(i);
				}
			}
			if (coef == "1"){
				outputE = sqrtstr+root;
			}
			else if (coef == "-1"){
				outputE = "-1*"+sqrtstr+root;
			}
			else {
				outputE = coef+"*"+sqrtstr+root;
			}
			
			return outputE;
		}
		return n.top + n.bottom;
	}
	return "";
}



Number reduceFraction(const Number numA){
	long long la = std::stoll(numA.top);
	long long lb = std::stoll(numA.bottom);
	while (la > 1000000000 || lb > 1000000000 || la < -1000000000 || lb < -1000000000){
		la /= 10;
		lb /= 10;
		//TODO: convert to decimal
	}
	int a = la;
	int b = lb;
	
	std::vector<int> primes = {2,3,5,7,11,13,17,19,23,29};
	int i;
	for (i=0;i<10;i++){
		while (a%primes[i] == 0 && b%primes[i] == 0){
			a = a/primes[i];
			b = b/primes[i];
		}
		if (b == 1){
			Number n;
			if (numA.type < 0){
				n.type = -1;
			}
			else {
				n.type = 1;
			}
			n.top = std::to_string(a);
			n.bottom = "1";
			return n;
		}
	}
	Number n;
	n.type = numA.type;
	n.top = std::to_string(a);
	n.bottom = std::to_string(b);
	return n;
	
}
std::vector<Number> eToArray(Number numA){
	std::string realA = "";
	std::string imA = "";
	int i;
	bool isReal = true;
	std::vector<Number> arrayA;
	for (i=0;i<numA.top.length();i++){
		if (numA.top.at(i) == ':'){
			isReal = false;
		}
		else if (numA.top.at(i) == ','){
			isReal = true;
			if (numbers.find(realA) == numbers.end()){
				numberType(realA);
			}
			if (numbers.find(imA) == numbers.end()){
				numberType(imA);
			}
			arrayA.push_back(numbers[realA]);
			arrayA.push_back(numbers[imA]);
			realA = "";
			imA = "";
		}
		else if (isReal){
			realA += numA.top.at(i);
		}
		else {
			imA += numA.top.at(i);
		}
	}
	return arrayA;
}
Number arrayToE(std::vector<Number> arrayA){
	int i;
	std::string outputA ="";
	for (i=0;i<arrayA.size()/2;i++){
		outputA += outputNumber(arrayA[i*2])+":"+outputNumber(arrayA[i*2+1])+",";
	}
	Number n;
	n.type = 11;
	n.top = outputA;
	n.bottom = "e";
	return n;
}

Number addTwo(const Number numA, const Number numB){
	std::string revsum = "";
	Number n;
	int base = 10;
	
	if ((numA.type == 11 && numA.bottom == "complex") || (numB.type == 11 && numB.bottom == "complex")){
		std::string realA = "";
		std::string realB = "";
		std::string imA = "";
		std::string imB = "";
		int i;
		bool isReal = true;
		if (numA.type == 11){
			for (i=0;i<numA.top.length();i++){
				if (numA.top.at(i) == ','){
					isReal = false;
				}
				else if (isReal){
					realA += numA.top.at(i);
				}
				else {
					imA += numA.top.at(i);
				}
			}
			if (numbers.find(realA) == numbers.end()){
				numberType(realA);
			}
			if (numbers.find(imA) == numbers.end()){
				numberType(imA);
			}
		}
		else if ((numA.type > 0 && numA.type <9) || (numA.type < 0 && numA.type > -9)){
			realA = outputNumber(numA);
			imA = "0";
		}
		if (numB.type == 11){
			isReal = true;
			for (i=0;i<numB.top.length();i++){
				if (numB.top.at(i) == ','){
					isReal = false;
				}
				else if (isReal){
					realB += numB.top.at(i);
				}
				else {
					imB += numB.top.at(i);
				}
			}
			if (numbers.find(realB) == numbers.end()){
				numberType(realB);
			}
			if (numbers.find(imB) == numbers.end()){
				numberType(imB);
			}
		}
		else if ((numB.type > 0 && numB.type <9) || (numB.type < 0 && numB.type > -9)){
			realB = outputNumber(numB);
			imB = "0";
		}
		if (imB.length()==0 && imA.length() == 0){
			return n;
		}
		Number realN;
		Number imN;
		
		realN = addTwo(numbers[realA],numbers[realB]);
		imN = addTwo(numbers[imA],numbers[imB]);
		n.type = 11;
		n.top = outputNumber(realN)+","+outputNumber(imN);
		n.bottom = "complex";
	}
	else if ((numA.type == 11 && numA.bottom == "\\pi") || (numB.type == 11 && numB.bottom == "\\pi")){
		std::string realA = "";
		std::string realB = "";
		int i;
		if (numA.type == 11 && numA.bottom == "\\pi"){
			realA = numA.top;
			if (numbers.find(realA) == numbers.end()){
				numberType(realA);
			}
		}
		else if ((numA.type > 0 && numA.type <9) || (numA.type < 0 && numA.type > -9)){
			realA = outputNumber(numA);
			if (realA != "0"){
				return n;
			}
			if (numbers.find(realA) == numbers.end()){
				numberType(realA);
			}
		}
		if (numB.type == 11 && numB.bottom == "\\pi"){
			realB = numB.top;
			if (numbers.find(realB) == numbers.end()){
				numberType(realB);
			}
		}
		else if ((numB.type > 0 && numB.type <9) || (numB.type < 0 && numB.type > -9)){
			realB = outputNumber(numB);
			if (realB != "0"){
				return n;
			}
			if (numbers.find(realB) == numbers.end()){
				numberType(realB);
			}
		}
		Number realN;
		realN = addTwo(numbers[realA],numbers[realB]);
		n.type = 11;
		n.top = outputNumber(realN);
		n.bottom = "\\pi";
		return n;
	}
	else if ((numA.type == 11 && numA.bottom == "e") || (numB.type == 11 && numB.bottom == "e")){
		std::string realA = "";
		std::string realB = "";
		std::string imA = "";
		std::string imB = "";
		int i;
		bool isReal = true;
		std::vector<Number> arrayA;
		std::vector<Number> arrayB;
		if (numA.type == 11 && numA.bottom == "e"){
			arrayA = eToArray(numA);
		}
		else if ((numA.type > 0 && numA.type <9) || (numA.type < 0 && numA.type > -9)){
			realA = outputNumber(numA);
		}
		else {
			return n;
		}
		if (numB.type == 11 && numB.bottom == "e"){
			arrayB = eToArray(numB);
		}
		else if ((numB.type > 0 && numB.type <9) || (numB.type < 0 && numB.type > -9)){
			realB = outputNumber(numB);
		}
		else {
			return n;
		}
		
		
		if (realB.length()>0){
			arrayA.push_back(numbers["0"]);
			arrayA.push_back(numB);
			n = arrayToE(arrayA);
			return n;
		}
		else if (realA.length()>0){
			arrayB.push_back(numbers["0"]);
			arrayB.push_back(numA);
			n = arrayToE(arrayB);
			return n;
		}
		else {
			for (i=0;i<arrayB.size()/2;i++){
				arrayA.push_back(arrayB[i*2]);
				arrayA.push_back(arrayB[i*2+1]);
			}
			n = arrayToE(arrayA);
		}
		
		return n;
	}
	else if (numA.type == 1){
		if (numB.type == 1){
			std::string a = numA.top;
			std::string b = numB.top;
			if (b.length() > a.length()){
				std::string c = a;
				a = b;
				b = c;
			}
			int len = a.length();
			while (len > b.length()){
				b = "0"+b;
			}
			int i;
			int charSum =0;
			int carry = 0;
			for (i=0;i<a.length();i++){
				int aa = a.at(len-1-i) - '0';
				int bb = b.at(len-1-i) - '0';
				charSum = aa + bb + carry;
				carry = 0;
				while (charSum >= base){
					charSum -= base;
					carry++;
				}
				revsum += std::to_string(charSum);
			}
			while (carry > 0){
				charSum = carry;
				carry = 0;
				while (charSum >= base){
					charSum -= base;
					carry++;
				}
				revsum += std::to_string(charSum);
			}
			std::string sum = "";
			for (i=revsum.length()-1;i>=0;i--){
				sum += revsum.at(i);
			}
			if (sum == ""){sum = "0";}
			if (numbers.find(sum) == numbers.end()){
				numberType(sum);
			}
			return numbers[sum];
		}
		else if (numB.type == -1){
			n.type = 1;
			n.top = numB.top;
			if (n > numA){
				return negateOne(addTwo(n,negateOne(numA)));
			}
			
			std::string a = numA.top;
			std::string b = numB.top;

			int len = a.length();
			while (len > b.length()){
				b = "0"+b;
			}
			int i;
			int charSum =0;
			int carry = 0;
			for (i=0;i<a.length();i++){
				int aa = a.at(len-1-i) - '0';
				int bb = b.at(len-1-i) - '0';
				charSum = aa - bb + carry;
				carry = 0;
				while (charSum < 0){
					charSum += base;
					carry--;
				}
				revsum += std::to_string(charSum);
			}
			while (carry < 0){
				charSum = carry;
				carry = 0;
				while (charSum < 0){
					charSum += base;
					carry--;
				}
				revsum += std::to_string(charSum);
			}
			std::string sum = "";
			bool pastZero = false;
			for (i=revsum.length()-1;i>=0;i--){
				if (!pastZero){
					if (revsum.at(i) == '0'){continue;}
					else {pastZero = true;}
				}
				sum += revsum.at(i);
			}
			if (sum == ""){sum = "0";}
			if (numbers.find(sum) == numbers.end()){
				numberType(sum);
			}
			return numbers[sum];
		}
		else if (numB.type == 2 || numB.type == -2){
			n.type = 2; n.top = numA.top; n.bottom = "1";
			return addTwo(n,numB);
		}
		else if (numB.type == 3 || numB.type == -3){
			n.type = 3; n.top = numA.top; n.bottom = "1";
			return addTwo(n,numB);
		}
	}
	else if (numA.type == 2){
		if (numB.type == 2){
			Number nb;
			nb.type = 1;
			if (isDecimal(numA) && isDecimal(numB)){
				int blenDiff = numB.bottom.length() - numA.bottom.length();
				int i;
				if (blenDiff > 0){
					nb.top = numB.top;
					n.type = 1;
					n.top = numA.top;
					for (i=0;i<blenDiff;i++){
						n.top += "0";
					}
					n = addTwo(n,nb);
					n.bottom = numB.bottom;
					n.type = 2;
				}
				else if (blenDiff < 0){
					nb.top = numB.top;
					n.type = 1;
					n.top = numA.top;
					for (i=0;i<-1*blenDiff;i++){
						nb.top += "0";
					}
					n = addTwo(n,nb);
					n.bottom = numA.bottom;
					n.type = 2;
				}
				else {
					nb.top = numB.top;
					n.type = 1;
					n.top = numA.top;
					n = addTwo(n,nb);
					n.bottom = numA.bottom;
					n.type = 2;
					while (n.top.at(n.top.length()-1)=='0' && n.bottom.length()>1){
						n.top = n.top.substr(0,n.top.length()-1);
						n.bottom = n.bottom.substr(0,n.bottom.length()-1);
					}
					if (n.bottom == "1"){
						n.type = 1;
					}
				}
			}
			else {
				if (numbers.find(numA.top) == numbers.end()){
					numberType(numA.top);
				}
				if (numbers.find(numB.top) == numbers.end()){
					numberType(numB.top);
				}
				if (numbers.find(numA.bottom) == numbers.end()){
					numberType(numA.bottom);
				}
				if (numbers.find(numB.bottom) == numbers.end()){
					numberType(numB.bottom);
				}
				
				n = addTwo(mulTwo(numbers[numA.top],numbers[numB.bottom]),mulTwo(numbers[numB.top],numbers[numA.bottom]));
				
				nb = mulTwo(numbers[numA.bottom],numbers[numB.bottom]);
				n.type = 2;
				n.top = n.top;
				n.bottom = nb.top;
				n = reduceFraction(n);
			}
		}
		else if (numB.type == -2){
			Number nb;
			nb.type = -1;
			if (isDecimal(numA) && isDecimal(numB)){
				int blenDiff = numB.bottom.length() - numA.bottom.length();
				int i;
				if (blenDiff > 0){
					nb.top = numB.top;
					n.type = 1;
					n.top = numA.top;
					for (i=0;i<blenDiff;i++){
						n.top += "0";
					}
					n = addTwo(n,nb);
					n.bottom = numB.bottom;
					n.type = 2 * n.type;
				}
				else if (blenDiff < 0){
					nb.top = numB.top;
					n.type = 1;
					n.top = numA.top;
					for (i=0;i<-1*blenDiff;i++){
						nb.top += "0";
					}
					n = addTwo(n,nb);
					n.bottom = numA.bottom;
					n.type = 2 * n.type;
				}
				else {
					nb.top = numB.top;
					n.type = 1;
					n.top = numA.top;
					n = addTwo(n,nb);
					n.bottom = numA.bottom;
					
					while (n.top.length() >= 1 && n.top.at(n.top.length()-1)=='0' && n.bottom.length()>1){
						n.top = n.top.substr(0,n.top.length()-1);
						n.bottom = n.bottom.substr(0,n.bottom.length()-1);
					}
					if (n.bottom != "1"){
						n.type = 2 * n.type;
					}
				}
			}
			else {
				
				double topa = std::stod(numA.top);
				double topb = std::stod(numB.top);
				double bota = std::stod(numA.bottom);
				double botb = std::stod(numB.bottom);
				double top = topa*botb-topb*bota;
				double bot = bota*botb;
				std::string nd = std::to_string(top/bot);
				if (numbers.find(nd) == numbers.end()){
					numberType(nd);
				}
				n = numbers[nd];
			}
		}
		else if (numB.type == 1 || numB.type == -1){
			n.type = 2 * numB.type; n.top = numB.top; n.bottom = "1";
			return addTwo(numA,n);
		}
		else if (numB.type == 3 || numB.type == -3){
			n.type = 2 * numB.type / 3; n.top = numB.top; n.bottom = numB.bottom;
			return addTwo(numA,n);
		}
	}
	else if (numA.type == 3){
		if (numB.type == 3){
			Number nb;
			nb.type = 2;
			nb.top = numB.top;
			nb.bottom = numB.bottom;
			n.type = 2;
			n.top = numA.top;
			n.bottom = numA.bottom;
			n = addTwo(n,nb);
			n.type = 3;
		}
		else if (numB.type == -3){
			Number nb;
			nb.type = -2;
			nb.top = numB.top;
			nb.bottom = numB.bottom;
			n.type = 2;
			n.top = numA.top;
			n.bottom = numA.bottom;
			n = addTwo(n,nb);
			n.type = 3 * n.type/2;
		}
		else if (numB.type == 1 || numB.type == -1){
			n.type = 3 * numB.type; n.top = numB.top; n.bottom = "1";
			return addTwo(n,numA);
		}
		else if (numB.type == 2 || numB.type == -2){
			n.type = 2; n.top = numA.top; n.bottom = numA.bottom;
			return addTwo(n,numB);
		}
	}
	else if (numA.type < 0){
		if (numB.type > 0){
			return addTwo(numB,numA);
		}
		else if (numB.type < 0){
			return negateOne(addTwo(negateOne(numA),negateOne(numB)));
		}
	}
	return n;

}

Number reduceRoot(const Number numA){
	std::vector<Number> rootCoef = sqrtToN(numA.top);
	
	if (rootCoef[0].type == 1){
		std::vector<int> factors = factorFull(rootCoef[0]);
		int i;
		int f = 1;
		int sqroot = 1;
		int notsq = 1;
		for (i=0;i<factors.size();i++){
			if (factors[i] == f){
				sqroot *= f;
				notsq /= f;
				f = 1;
			}
			else {
				f = factors[i];
				notsq *= f;
			}
		}
		rootCoef[0].top = std::to_string(notsq);
		std::string s = std::to_string(sqroot);
		if (numbers.find(s) == numbers.end()){
			numberType(s);
		}
		rootCoef[1] = mulTwo(rootCoef[1],numbers[s]);
		if (rootCoef[0].top == "1"){
			return rootCoef[1];
		}
		Number n;
		n.type = 11;
		n.top = outputNumber(rootCoef[0])+":"+outputNumber(rootCoef[1]);
		n.bottom = "sqrt";
		return n;
	}
	return numA;
}

Number mulTwo(const Number numA, const Number numB){
	int base = 10;
	int neg = 1;
	Number n;
	if ((numA.type == 11 && numA.bottom == "complex") || (numB.type == 11 && numB.bottom == "complex")){
		std::string realA = "";
		std::string realB = "";
		std::string imA = "";
		std::string imB = "";
		int i;
		bool isReal = true;
		if (numA.type == 11 && numA.bottom == "complex"){
			for (i=0;i<numA.top.length();i++){
				if (numA.top.at(i) == ','){
					isReal = false;
				}
				else if (isReal){
					realA += numA.top.at(i);
				}
				else {
					imA += numA.top.at(i);
				}
			}
			if (numbers.find(realA) == numbers.end()){
				numberType(realA);
			}
			if (numbers.find(imA) == numbers.end()){
				numberType(imA);
			}
		}
		else if ((numA.type > 0 && numA.type <9) || (numA.type < 0 && numA.type > -9)){
			realA = outputNumber(numA);
			imA = "0";
		}
		if (numB.type == 11 && numB.bottom == "complex"){
			isReal = true;
			for (i=0;i<numB.top.length();i++){
				if (numB.top.at(i) == ','){
					isReal = false;
				}
				else if (isReal){
					realB += numB.top.at(i);
				}
				else {
					imB += numB.top.at(i);
				}
			}
			if (numbers.find(realB) == numbers.end()){
				numberType(realB);
			}
			if (numbers.find(imB) == numbers.end()){
				numberType(imB);
			}
		}
		else if ((numB.type > 0 && numB.type <9) || (numB.type < 0 && numB.type > -9)){
			realB = outputNumber(numB);
			imB = "0";
		}
		if (imB.length()==0 && imA.length() == 0){
			return n;
		}
		Number realN;
		Number imN;
		
		realN = addTwo(mulTwo(numbers[realA],numbers[realB]),negateOne(mulTwo(numbers[imA],numbers[imB])));
		imN = addTwo(mulTwo(numbers[realA],numbers[imB]),mulTwo(numbers[imA],numbers[realB]));
		n.type = 11;
		n.top = outputNumber(realN)+","+outputNumber(imN);
		n.bottom = "complex";
		return n;
	}
	else if ((numA.type == 11 && numA.bottom == "\\pi") || (numB.type == 11 && numB.bottom == "\\pi")){
		std::string realA = "";
		std::string realB = "";
		if ((numA.type == 11 && numA.bottom == "\\pi") && (numB.type == 11 && numB.bottom == "\\pi")){
			return n;
		}
		int i;
		if (numA.type == 11 && numA.bottom == "\\pi"){
			realA = numA.top;
			if (numbers.find(realA) == numbers.end()){
				numberType(realA);
			}
		}
		else if ((numA.type > 0 && numA.type <9) || (numA.type < 0 && numA.type > -9)){
			realA = outputNumber(numA);
			if (numbers.find(realA) == numbers.end()){
				numberType(realA);
			}
		}
		else {
			return n;
		}
		if (numB.type == 11 && numB.bottom == "\\pi"){
			realB = numB.top;
			if (numbers.find(realB) == numbers.end()){
				numberType(realB);
			}
		}
		else if ((numB.type > 0 && numB.type <9) || (numB.type < 0 && numB.type > -9)){
			realB = outputNumber(numB);
			if (numbers.find(realB) == numbers.end()){
				numberType(realB);
			}
		}
		else {
			return n;
		}
		Number realN;
		realN = mulTwo(numbers[realA],numbers[realB]);
		n.type = 11;
		n.top = outputNumber(realN);
		n.bottom = "\\pi";
		return n;
	}
	else if ((numA.type == 11 && numA.bottom == "e") || (numB.type == 11 && numB.bottom == "e")){
		std::string realA = "";
		std::string realB = "";
		std::string imA = "";
		std::string imB = "";
		int i;
		bool isReal = true;
		std::vector<Number> arrayA;
		std::vector<Number> arrayB;
		if (numA.type == 11 && numA.bottom == "e"){
			arrayA = eToArray(numA);
		}
		else if ((numA.type > 0 && numA.type <9) || (numA.type < 0 && numA.type > -9) ){
			realA = outputNumber(numA);
		}
		else {
			return n;
		}
		if (numB.type == 11 && numB.bottom == "e"){
			arrayB = eToArray(numB);
		}
		else if ((numB.type > 0 && numB.type <9) || (numB.type < 0 && numB.type > -9)){
			realB = outputNumber(numB);
		}
		else {
			return n;
		}
		
		
		if (realB.length()>0){
			//mul each part of arrayA
			for (i=0;i<arrayA.size()/2;i++){
				arrayA[i*2+1]=mulTwo(arrayA[i*2+1],numB);
			}
			n = arrayToE(arrayA);
			return n;
		}
		else if (realA.length()>0){
			//mul each part of arrayA
			for (i=0;i<arrayB.size()/2;i++){
				arrayB[i*2+1]=mulTwo(arrayB[i*2+1],numA);
			}
			n = arrayToE(arrayB);
			return n;
		}
		else {
			std::vector<Number> outputArray;
			int ii;
			for (i=0;i<arrayA.size()/2;i++){
				for (ii=0;ii<arrayB.size()/2;ii++){
					outputArray.push_back(addTwo(arrayA[i*2],arrayB[ii*2]));
					outputArray.push_back(mulTwo(arrayA[i*2+1],arrayB[ii*2+1]));
				}
			}
			n = arrayToE(outputArray);
		}
		
		return n;
	}
	else if ((numA.type == 11 && numA.bottom == "sqrt") || (numB.type == 11 && numB.bottom == "sqrt")){
		std::string realA = "";
		std::string realB = "";
		Number newRoot;
		Number newCoef;
		
		if ((numA.type == 11 && numA.bottom == "sqrt") && (numB.type == 11 && numB.bottom == "sqrt")){
			std::vector<Number> rootCoefA = sqrtToN(numA.top);
			std::vector<Number> rootCoefB = sqrtToN(numB.top);
			newRoot = mulTwo(rootCoefA[0],rootCoefB[0]);
			newCoef = mulTwo(rootCoefA[1],rootCoefB[1]);
			n.type = 11;
			n.top = outputNumber(newRoot)+":"+outputNumber(newCoef);
			n.bottom = "sqrt";
			n = reduceRoot(n);
			return n;
			//TODO: pull out perfect squares
			
		}
		int i;
		if (numA.type == 11 && numA.bottom == "sqrt"){
			std::vector<Number> rootCoef = sqrtToN(numA.top);
			newRoot = rootCoef[0];
			newCoef = rootCoef[1];
		}
		else if ((numA.type > 0 && numA.type <9) || (numA.type < 0 && numA.type > -9)){
			newCoef = numA;
		}
		else {
			return n;
		}
		if (numB.type == 11 && numB.bottom == "sqrt"){
			std::vector<Number> rootCoef = sqrtToN(numB.top);
			newRoot = rootCoef[0];
			newCoef = mulTwo(newCoef,rootCoef[1]);
		}
		else if ((numB.type > 0 && numB.type <9) || (numB.type < 0 && numB.type > -9)){
			newCoef = mulTwo(newCoef,numB);
		}
		else {
			return n;
		}
		
		n.type = 11;
		n.top = outputNumber(newRoot)+":"+outputNumber(newCoef);
		n.bottom = "sqrt";
		return n;
	}
	else if (numA.type == 1){
		if (numB.type == 1){
			n.type = 1;
			int prod = std::stoi(numA.top);
			prod *= std::stoi(numB.top);
			n.top = std::to_string(prod);
			return n;
		}
		else if (numB.type == -1){
			n.type = -1;
			int prod = std::stoi(numA.top);
			prod *= std::stoi(numB.top);
			n.top = std::to_string(prod);
			return n;
		}
		else if (numB.type == 2 || numB.type == -2 || numB.type == 3 || numB.type == -3){
			n.type = numB.type;
			int prod = std::stoi(numA.top);
			prod *= std::stoi(numB.top);
			n.top = std::to_string(prod);
			n.bottom = numB.bottom;
			n = reduceFraction(n);
			return n;
		}
		else if (numB.type == 11){
			Number nn;
			nn = mulTwo(numA,numbers[numB.top]);
			n.type = 11;
			n.top = outputNumber(nn);
			n.bottom = numB.bottom;
			return n;
		}
	}
	else if (numA.type == 2){
		if (numB.type == 1 || numB.type == -1){
			n.type = 2 * numB.type;
			int prod = std::stoi(numA.top);
			prod *= std::stoi(numB.top);
			n.top = std::to_string(prod);
			n.bottom = numA.bottom;
			n = reduceFraction(n);
			return n;
		}
		else if (numB.type == 2 || numB.type == -2 || numB.type == 3 || numB.type == -3){
			n.type = 2;
			if (numB.type < 0){
				n.type = -2;
			}
			int prod = std::stoi(numA.top);
			prod *= std::stoi(numB.top);
			n.top = std::to_string(prod);
			prod = std::stoi(numA.bottom);
			prod *= std::stoi(numB.bottom);
			n.bottom = std::to_string(prod);
			n = reduceFraction(n);
			return n;
		}
	}
	else if (numA.type == 3){
		if (numB.type == 1 || numB.type == -1){
			n.type = 3 * numB.type;
			int prod = std::stoi(numA.top);
			prod *= std::stoi(numB.top);
			n.top = std::to_string(prod);
			n.bottom = numA.bottom;
			n = reduceFraction(n);
			return n;
		}
		else if (numB.type == 2 || numB.type == -2 || numB.type == 3 || numB.type == -3){
			n.type = numB.type;
			int prod = std::stoi(numA.top);
			prod *= std::stoi(numB.top);
			n.top = std::to_string(prod);
			prod = std::stoi(numA.bottom);
			prod *= std::stoi(numB.bottom);
			n.bottom = std::to_string(prod);
			n = reduceFraction(n);
			return n;
		}
	}
	else if (numA.type < 0){
		if (numB.type > 0){
			return mulTwo(numB,numA);
		}
		else if (numB.type < 0){
			return mulTwo(negateOne(numA),negateOne(numB));
		}
	}
	return n;
}

Number expTwo(const Number numA, const Number numB){
	int base = 10;
	int neg = 1;
	Number n;
	if (numB.type < 0){
		n.type = -1*numB.type;
		n.top = numB.top;
		n.bottom = numB.bottom;
		return invertOne(expTwo(numA,n));
	}
	if (numA.type == 11 && numA.bottom == "e"){
		if (numB.type > 0 && numB.type < 9){
			std::vector<Number> arrayA = eToArray(numA);
			int i;
			for (i=0;i<arrayA.size()/2;i++){
				arrayA[i*2]=mulTwo(arrayA[i*2],numB);
			}
			n = arrayToE(arrayA);
			return n;
		}
		return n;
	}
	else if (numA.type == 11 && numA.bottom == "complex"){
		if (numB.type == 1){
			if (numA.top.substr(0,2) == "0,"){
				std::string imA = numA.top.substr(2,numA.top.length()-2);
				if (numbers.find(imA) == numbers.end()){
					numberType(imA);
				}
				Number newIm = expTwo(numbers[imA],numB);
				int nb = std::stoi(numB.top);
				if (nb%4 == 0){
					n = newIm;
					return n;
				}
				else if (nb%4 == 1){
					if (numbers.find("i") == numbers.end()){
						numberType("i");
					}
					n = mulTwo(numbers["i"],newIm);
					return n;
				}
				else if (nb%4 == 2){
					n = newIm;
					n.type *= 1;
					return n;
				}
				else if (nb%4 == 3){
					if (numbers.find("i") == numbers.end()){
						numberType("i");
					}
					n = mulTwo(numbers["i"],negateOne(newIm));
					return n;
				}
			}
			else {
				int nb = std::stoi(numB.top);
				int i;
				if (nb == 0){
					n.type = 1;
					n.top = "1";
					n.bottom = "1";
					return n;
				}
				else if (nb == 1){
					n = numA;
					return n;
				}
				n.type = numA.type;
				n.top = numA.top;
				n.bottom = numA.bottom;
				if (nb<20){
					for (i=1;i<nb;i++){
						n = mulTwo(n,numA);
					}
					return n;
				}
				else {
					return n;
				}
			}
			return n;
		}
		return n;
	}
	else if (numA.type == 1){
		if (numB.type == 1){
			n.type = 1;
			double a = std::stoi(numA.top);
			double b = std::stoi(numB.top);
			std::string prod = std::to_string(pow(a,b));
			if (numbers.find(prod) == numbers.end()){
				numberType(prod);
			}
			n = numbers[prod];
			return n;
		}
		else if (numB.type == 2){
			n.type = 2;
			double a = std::stoi(numA.top);
			double b = std::stod(numB.top) / std::stod(numB.bottom);
			std::string prod = std::to_string(pow(a,b));
			if (numbers.find(prod) == numbers.end()){
				numberType(prod);
			}
			n = numbers[prod];
			return n;
		}
	}
	else if (numA.type == 2){
		if (numB.type == 1){
			n.type = 1;
			double a = std::stod(numA.top) / std::stod(numA.bottom);
			double b = std::stoi(numB.top);
			std::string prod = std::to_string(pow(a,b));
			if (numbers.find(prod) == numbers.end()){
				numberType(prod);
			}
			n = numbers[prod];
			return n;
		}
		else if (numB.type == 2){
			n.type = 2;
			double a = std::stod(numA.top) / std::stod(numA.bottom);
			double b = std::stod(numB.top) / std::stod(numB.bottom);
			std::string prod = std::to_string(pow(a,b));
			if (numbers.find(prod) == numbers.end()){
				numberType(prod);
			}
			n = numbers[prod];
			return n;
		}
	}
	else if (numA.type < 0){
		if (numB.type == 1){
			char lastDigit = numB.top.at(numB.top.length()-1);
			if (lastDigit == '0' || lastDigit == '2' || lastDigit == '4' || lastDigit == '6' || lastDigit == '8'){
				n.type = -1*numA.type;
				n.top = numA.top;
				n.bottom = numA.bottom;
				return expTwo(n,numB);
			}
			else {
				n.type = -1*numA.type;
				n.top = numA.top;
				n.bottom = numA.bottom;
				return negateOne(expTwo(n,numB));
			}
		}
		else if (numB.type == 2){
			return n;
		}
		else if (numB.type == 3){
			char lastDigitB = numB.bottom.at(numB.bottom.length()-1);
			if (lastDigitB == '0' || lastDigitB == '2' || lastDigitB == '4' || lastDigitB == '6' || lastDigitB == '8'){
				return n;
			}
			else {
				char lastDigit = numB.top.at(numB.top.length()-1);
				if (lastDigit == '0' || lastDigit == '2' || lastDigit == '4' || lastDigit == '6' || lastDigit == '8'){
					n.type = -1*numA.type;
					n.top = numA.top;
					n.bottom = numA.bottom;
					return expTwo(n,numB);
				}
				else {
					n.type = -1*numA.type;
					n.top = numA.top;
					n.bottom = numA.bottom;
					return negateOne(expTwo(n,numB));
				}
			}
		}
		

	}
	return n;
}

Number logTwo(const Number numA, const Number numB){ //numA is base and numB is inside part, of course
	int base = 10;
	int neg = 1;
	Number n;
	if (numB.type <= 0 || numA.type <= 0){
		return n;
	}
	if (numB.top == "0"){
		return n;
	}
	if (numB.type == 1 && numB.top == "1"){
		n.type = 1;
		n.top = "0";
		n.bottom = "1";
		return n;
	}
	
	if (numA.type == 11 && numA.bottom == "e" && numB.type == 11 && numB.bottom == "e"){
		if (numA.top == "1:1,"){
			std::vector<Number> arrayB = eToArray(numB);
			if (arrayB.size() == 2){
				
				if (arrayB[1].type == 1 && arrayB[1].top == "1"){
					n = arrayB[0];
					return n;
				}
				else {
					return addTwo(logTwo(numA,arrayB[1]), arrayB[0]);
				}
			}
		}
	}
	else if (numA.type == 1){
		if (numB.type == 1){
			double a = std::stoi(numA.top);
			double b = std::stoi(numB.top);
			std::string prod = std::to_string(log(b)/log(a));
			if (numbers.find(prod) == numbers.end()){
				numberType(prod);
			}
			n = numbers[prod];
			return n;
		}
		else if (numB.type == 2){
			double a = std::stoi(numA.top);
			double b = std::stod(numB.top) / std::stod(numB.bottom);
			std::string prod = std::to_string(log(b)/log(a));
			if (numbers.find(prod) == numbers.end()){
				numberType(prod);
			}
			n = numbers[prod];
			return n;
		}
		else if (numB.type == 3){
			n.type = 1;
			n.top = numB.top;
			Number nb;
			nb.type = 1;
			nb.top = numB.bottom;
			return addTwo(logTwo(numA,n),negateOne(logTwo(numA,nb)));
		}
	}
	else if (numA.type == 2){
		if (numB.type == 1){
			double a = std::stod(numA.top) / std::stod(numA.bottom);
			double b = std::stoi(numB.top);
			std::string prod = std::to_string(log(b)/log(a));
			if (numbers.find(prod) == numbers.end()){
				numberType(prod);
			}
			n = numbers[prod];
			return n;
		}
		else if (numB.type == 2){
			double a = std::stod(numA.top) / std::stod(numA.bottom);
			double b = std::stod(numB.top) / std::stod(numB.bottom);
			std::string prod = std::to_string(log(b)/log(a));
			if (numbers.find(prod) == numbers.end()){
				numberType(prod);
			}
			n = numbers[prod];
			return n;
		}
		else if (numB.type == 3){
			double a = std::stod(numA.top) / std::stod(numA.bottom);
			double b = std::stod(numB.top) / std::stod(numB.bottom);
			std::string prod = std::to_string(log(b)/log(a));
			if (numbers.find(prod) == numbers.end()){
				numberType(prod);
			}
			n = numbers[prod];
			return n;
		}
	}
	else if (numA.type == 3){
		if (numB.type == 1){
			double a = std::stoi(numA.top);
			double aa = std::stoi(numA.bottom);
			double b = std::stoi(numB.top);
			std::string prod = std::to_string(log(b)/(log(a)-log(aa)));
			if (numbers.find(prod) == numbers.end()){
				numberType(prod);
			}
			n = numbers[prod];
			return n;
		}
		else if (numB.type == 2){
			double a = std::stod(numA.top) / std::stod(numA.bottom);
			double b = std::stod(numB.top) / std::stod(numB.bottom);
			std::string prod = std::to_string(log(b)/log(a));
			if (numbers.find(prod) == numbers.end()){
				numberType(prod);
			}
			n = numbers[prod];
			return n;
		}
		else if (numB.type == 3){
			double a = std::stoi(numA.top);
			double aa = std::stoi(numA.bottom);
			double b = std::stoi(numB.top);
			double bb = std::stoi(numB.bottom);
			std::string prod = std::to_string((log(b)-log(bb))/(log(a)-log(aa)));
			if (numbers.find(prod) == numbers.end()){
				numberType(prod);
			}
			n = numbers[prod];
			return n;
		}
	}
	return n;
}

Number trigTwo(char fn, const Number numA){ 
	int base = 10;
	int neg = 1;
	Number n;
	if (numbers.find("\\pi") == numbers.end()){
		numberType("\\pi");
	}
	if (numbers.find("3.14159") == numbers.end()){
		numberType("3.14159");
	}
	if (numbers.find("1/2") == numbers.end()){
		numberType("1/2");
	}
	Number halfpi = mulTwo(numbers["\\pi"],numbers["1/2"]);
	Number nn = addTwo(halfpi,negateOne(numA));
	Number nna;
	if (maxDigits >=0){
		nna = addTwo(mulTwo(numbers["3.14159"],numbers["1/2"]),negateOne(numA));
	}
	if (fn == -63){//cosine
		if (nn.type == 11 && nn.bottom == "\\pi"){
			return trigTwo(-64,nn);
		}
		else if (nna.type != 0 && maxDigits >= 0){
			return trigTwo(-64,nna);
		}
		else {
			return n;
		}
	}
	else if (fn == -62){//tangent

		if (nn.type == 11 && nn.bottom == "\\pi"){
			Number cosa = trigTwo(-64,nn);
			if (outputNumber(cosa) == "0" || cosa.type == 0){
				return n; //replace with infinity
			}
			Number sina = trigTwo(-64,numA);
			if (sina.type == 0){
				return n;
			}
			return mulTwo(sina,invertOne(cosa));
		}
		else if (nna.type != 0 && maxDigits >= 0){
			Number cosa = trigTwo(-64,nna);
			if (outputNumber(cosa) == "0" || cosa.type == 0){
				return n; //replace with infinity
			}
			Number sina = trigTwo(-64,numA);
			if (sina.type == 0){
				return n;
			}
			return mulTwo(sina,invertOne(cosa));
		}
		else {
			return n;
		}
	}
	else if (fn == -61){//cosecant
		Number sina = trigTwo(-64,numA);
		if (outputNumber(sina) == "0" || sina.type == 0){
			return n;
		}
		else {
			return invertOne(sina);
		}
	}
	else if (fn == -60){//secant
		Number nn = addTwo(halfpi,negateOne(numA));
		if (nn.type == 11 && nn.bottom == "\\pi"){
			Number cosa = trigTwo(-64,nn);
			if (outputNumber(cosa) == "0" || cosa.type == 0){
				return n; //replace with infinity
			}
			else {
				return invertOne(cosa);
			}
			
		}
		else if (nna.type != 0 && maxDigits >= 0){
			Number cosa = trigTwo(-64,nna);
			if (outputNumber(cosa) == "0" || cosa.type == 0){
				return n; //replace with infinity
			}
			else {
				return invertOne(cosa);
			}
		}
		else {
			return n;
		}
	}
	else if (fn == -59){//cotangent
		Number nn = addTwo(halfpi,negateOne(numA));
		if (nn.type == 11 && nn.bottom == "\\pi"){
			Number cosa = trigTwo(-64,nn);
			Number sina = trigTwo(-64,numA);
			if (outputNumber(sina) == "0" || sina.type == 0){
				return n; //replace with infinity
			}
			if (cosa.type == 0){
				return n;
			}
			return mulTwo(cosa,invertOne(sina));
		}
		else if (nna.type != 0 && maxDigits >= 0){
			Number cosa = trigTwo(-64,nna);
			Number sina = trigTwo(-64,numA);
			if (outputNumber(sina) == "0" || sina.type == 0){
				return n; //replace with infinity
			}
			if (cosa.type == 0){
				return n;
			}
			return mulTwo(cosa,invertOne(sina));
		}
		else {
			return n;
		}
	}
	else if (fn != -64){
		return n;
	}
			
	//Rest assumes function is sine		
	if (numA.type == 0){
		return n;
	}
	double a;
	if (numA.type == 1 || numA.type == -1){
		if (numA.top == "0"){
			return numA;
		}
		a = std::stod(numA.top);
	}
	else if (numA.type == 2 || numA.type == 3 || numA.type == -2 || numA.type == -3){
		a = std::stod(numA.top) / std::stod(numA.bottom);
		if (numA.type < 0){
			a *= -1;
		}
	}
	else if (numA.type == 11){
		//std::cout << "n3: " << outputNumber(numA) << " and " << numA.top << " and " << numA.bottom << "\n";
		
		if (numA.bottom == "\\pi"){
			if (numbers.find(numA.top) == numbers.end()){
				numberType(numA.top);
			}
			n = numbers[numA.top];
			if (n.type < 0){
				std::string nn = outputNumber(negateOne(n))+"\\pi";
				if (numbers.find(nn) == numbers.end()){
					numberType(nn);
				}
				return negateOne(trigTwo(-64,numbers[nn]));
			}
			//assume type is positive
			if (n.type == 1){
				return numbers["0"];
			}
			else if (n.type == 3){
				std::string sqrt3 = "sqrt(3)";
				if (numbers.find(sqrt3) == numbers.end()){
					numberType(sqrt3);
				}
				std::string sqrt2 = "sqrt(2)";
				if (numbers.find(sqrt2) == numbers.end()){
					numberType(sqrt2);
				}
				std::string sqrt6 = "sqrt(6)";
				if (numbers.find(sqrt6) == numbers.end()){
					numberType(sqrt6);
				}
					
				n = reduceFraction(n);
				int nb = std::stoi(n.bottom);
				int nt = std::stoi(n.top) % 48;
				if (nb == 1){
					return numbers["0"];
				}
				else if (nb == 2){
					if (nt%4 == 1){
						return numbers["1"];
					}
					else if (nt%4 == 3){
						return numbers["-1"];
					}
				}
				else if (nb == 3){
					Number base = mulTwo(numbers["sqrt(3)"],numbers["1/2"]);
					if (nt%6 == 1 || nt%6 == 2){
						return base;
					}
					else if (nt%6 == 5 || nt%6 == 4){
						return negateOne(base);
					}
				}
				else if (nb == 4){
					Number base = mulTwo(numbers["sqrt(2)"],numbers["1/2"]);
					if (nt%8 == 1 || nt%8 == 3){
						return base;
					}
					else if (nt%8 == 7 || nt%8 == 5){
						return negateOne(base);
					}
				}
				else if (nb == 6){
					Number base = numbers["1/2"];
					if (nt%12 == 1 || nt%12 == 5){
						return base;
					}
					else if (nt%12 == 11 || nt%12 == 7){
						return negateOne(base);
					}
				}
				/*
				else if (nb == 12){
					std::string base = "(sqrt(6)-sqrt(2))/4";
					if (numbers.find(base) == numbers.end()){
						numberType(base);
					}
					if (nt%24 == 1 || nt%24 == 11){
						return numbers[base];
					}
					else if (nt%24 == 23 || nt%24 == 13){
						return negateOne(numbers[base]);
					}
				}
				else if (nb == 24){
					std::string base = "(sqrt(2-sqrt(2+sqrt(3))))/2";
					if (numbers.find(base) == numbers.end()){
						numberType(base);
					}
					if (nt%48 == 1 || nt%48 == 23){
						return numbers[base];
					}
					else if (nt%48 == 3 || nt%48 == 25){
						return negateOne(numbers[base]);
					}
				}*/
			}
			else {
				return n;
			}
		}
		else {
			return n;
		}
	}
	else {
		return n;
	}
	if (maxDigits < 0){
		return n;
	}
	std::string prod = "";
	if (fn == -64){prod = std::to_string(sin(a));}
	
	if (numbers.find(prod) == numbers.end()){
		numberType(prod);
	}
	n = numbers[prod];
	return n;

}

Number invTrigTwo(char fn, const Number numA){ //numA is base and numB is inside part, of course
	int base = 10;
	int neg = 1;
	Number n;
	if (numA.type == 0){
		return n;
	}
	double a;
	if (numA.type == 1 || numA.type == -1){
		a = std::stoi(numA.top);
	}
	else if (numA.type == 2 || numA.type == -2 ){
		a = std::stod(numA.top) / std::stod(numA.bottom);
		if (numA.type < 0){
			a *= -1;
		}
	}
	else if (numA.type == 3 || numA.type == -3){
		if (2 == 2){
			a = std::stod(numA.top) / std::stod(numA.bottom);
			if (numA.type < 0){
				a *= -1;
			}
		}
		else {
			a = std::stod(numA.top) / std::stod(numA.bottom);
			if (numA.type < 0){
				a *= -1;
			}
		}
	}
	else {
		return n;
	}

	std::string prod = "";
	if (fn == -32){ //arcsin
		if (a > 1 || a < -1) {return n;}
		prod = std::to_string(asin(a));
	}
	else if (fn == -31){
		if (a > 1 || a < -1) {return n;}
		prod = std::to_string(acos(a));
	}
	else if (fn == -30){
		prod = std::to_string(atan(a));
	}
	else if (fn == -29){
		if (a < 1 && a > -1) {return n;}
		prod = std::to_string(asin(1.0/a));
	}
	else if (fn == -28){
		if (a < 1 && a > -1) {return n;}
		prod = std::to_string(acos(1.0/a));
	}
	else if (fn == -27){
		if (a == 0) {return n;}
		prod = std::to_string(atan(1.0/a));
	}
	
	if (numbers.find(prod) == numbers.end()){
		numberType(prod);
	}
	n = numbers[prod];
	return n;

}

Number hypTrigTwo(char fn, const Number numA){ //numA is base and numB is inside part, of course
	int base = 10;
	int neg = 1;
	Number n;
	if (numA.type == 0){
		return n;
	}
	double a;
	if (numA.type == 1 || numA.type == -1){
		a = std::stoi(numA.top);
	}
	else if (numA.type == 2 || numA.type == 3 || numA.type == -2 || numA.type == -3){
		a = std::stod(numA.top) / std::stod(numA.bottom);
	}
	else {
		return n;
	}

	std::string prod = "";
	if (fn == -16){prod = std::to_string(sinh(a));}
	else if (fn == -15){prod = std::to_string(cosh(a));} 
	else if (fn == -14){double ca = cosh(a); if (ca != 0){prod = std::to_string(sinh(a)/ca);}} 
	else if (fn == -13){double sa = sinh(a); if (sa != 0){prod = std::to_string(1.0/sa);}} 
	else if (fn == -12){double ca = cosh(a); if (ca != 0){prod = std::to_string(1.0/ca);}} 
	else if (fn == -11){double sa = sinh(a); if (sa != 0){prod = std::to_string(cosh(a)/sa);}} 
	
	if (numbers.find(prod) == numbers.end()){
		numberType(prod);
	}
	n = numbers[prod];
	return n;

}

Number factorialOne(const Number numA){
	Number n;
	int nn = 1;
	int i;
	if (numA.type == 1){
		int na = std::stoi(numA.top);
		for (i=2;i<na+1;i++){
			nn *= i;
		}
		n.type = 1;
		n.top = std::to_string(nn);
		n.bottom = "1";
	}
	else {
		n.type = 0;
	}
	
	return n;
}

Number roundOne(const Number numA){
	int base = 10;
	int neg = 1;
	Number n;
	if (numA.type == 0){
		return n;
	}
	if (numA.type == 1 || numA.type == -1){
		n = numA;
		return n;
	}
	else if (numA.type == 2 || numA.type == -2 || numA.type == 3 || numA.type == -3){
		double a = std::stod(numA.top) / std::stod(numA.bottom);
		int aa = round(a);
		Number n;
		if (aa < 0){
			n.type = -1;
			n.top = std::to_string(aa*-1);
			n.bottom = "1";
		}
		else {
			n.type = 1;
			n.top = std::to_string(aa);
			n.bottom = "1";
		}
		return n;
	}
	
	
	return n;
}

Number rootNth(const Number numA, const Number numB){ //numA is type of root, numB is inside
	int base = 10;
	int neg = 1;
	Number n;

	if (numA.type == 1){
		int a = std::stoi(numA.top);
		if (a == 2){
			if (maxDigits < 0){
				//todo: check if is perfect power or can pull out perfect power
				n.type = 11;
				n.top = outputNumber(numB)+":1";
				n.bottom = "sqrt";
				n = reduceRoot(n);
				return n;
			}
		}
		else {
			if (maxDigits < 0){
				//todo: check if is perfect power or can pull out perfect power
				return n;
			}
		}
		
		double b;
		if (numB.type == 1){
			b = std::stoi(numB.top);
		}
		else if (numB.type == 2 || numB.type == 3){
			b = std::stod(numB.top) / std::stod(numB.bottom);
		}
		else if (numB.type < 0){
			if (a%2 == 0){n.type = 0; return n;}
			else {
				return negateOne(rootNth(numA,negateOne(numB)));
			}
		}
		double aa = 1.0;
		aa /= a;
		std::string prod = std::to_string(pow(b,aa));
		if (numbers.find(prod) == numbers.end()){
			numberType(prod);
		}
		n = numbers[prod];
		return n;
	}

	return n;
	
}

Number sqrtOne(const Number numA){
	if (numbers.find("2") == numbers.end()){
		numberType("2");
	}
	return rootNth(numbers["2"],numA);
}

Number functionTwo(const Number numA, const Number numB){
	if (numA.type == 16){
		Function f = functionMap[numA.top];
		std::string input = outputNumber(numB);
		int i;
		std::string newPostfix = f.postfix;
		for (i=f.rightIdx.size()-1;i>=0;i--){
			newPostfix.replace(f.rightIdx[i],f.var.length(),input);
		}
		//for (i=f.leftIdx.size()-1;i>=0;i--){
		//	postfix.replace(f.leftIdx[i],f.var.length(),input);
		//}
		return solvePostfix(newPostfix);
	}
	Number n;
	return n;
}

Number roundNumber(const Number n){
	if (n.type == 0 || n.type == 1 || n.type == -1 || n.type == 2 || n.type == -2){
		return n;
	}
	else if (n.type == 3){
		return n;
	}
	else if (n.type == -3){
		return n;
	}
	else if (n.type == 11){
		if (n.bottom == "complex"){
			return n;
		}
		else if (n.bottom == "\\pi"){
			if (numbers.find(n.top) == numbers.end()){
				numberType(n.top);
			}
			if (numbers.find("3.14159") == numbers.end()){
				numberType("3.14159");
			}
			Number nn = mulTwo(numbers[n.top],numbers["3.14159"]);
			return nn;
		}
		else if (n.bottom == "e"){
			Number outputE = numbers["0"];
			if (numbers.find("2.718") == numbers.end()){
				numberType("2.718");
			}
			int i; bool isReal = true;
			std::string realA = "";
			std::string imA = "";
			for (i=0;i<n.top.length();i++){
				if (n.top.at(i) == ':'){
					isReal = false;
				}
				else if (n.top.at(i) == ','){
					isReal = true;
					if (numbers.find(imA) == numbers.end()){
						numberType(imA);
					}
					if (numbers.find(realA) == numbers.end()){
						numberType(realA);
					}
					outputE = addTwo(outputE,mulTwo(numbers[imA],expTwo(numbers["2.718"],numbers[realA])));
					realA = "";
					imA = "";
				}
				else if (isReal){
					realA += n.top.at(i);
				}
				else {
					imA += n.top.at(i);
				}
			}
			return outputE;
		}
		return n;
	}
	return n;
}

std::map<std::string,Number> solvedPostfixMap;
Number solvePostfix(std::string postfix) {
	if (solvedPostfixMap.find(postfix) != solvedPostfixMap.end()){
		return solvedPostfixMap[postfix];
	}
	int i;
  	int currentIndex = 0;
  	int arrayIndex = 0;
  	std::vector<Number> stack;
  	std::vector<Number> intArray;
  	std::string currentOperand = "";
  	Number n;
  	if (numbers.find("") == numbers.end()){
		numberType("");
	}
	if (numbers.find("-1") == numbers.end()){
		numberType("-1");
	}
	if (numbers.find("1") == numbers.end()){
		numberType("1");
	}
	if (numbers.find("0") == numbers.end()){
		numberType("0");
	}
  	for (i=0; i<postfix.length(); i++) 
    {
    	if (postfix.at(i) == '{'){
    		solvedPostfixMap[postfix] = n;
    		return n;
    	}
    	else if (postfix.at(i) == '@') {
        	currentOperand = "";
        }
        else if (postfix.at(i) == '_') {
			//TODO: convert to number here
			if (numbers.find(currentOperand) == numbers.end()){
				numberType(currentOperand);
			}
			intArray.push_back(numbers[currentOperand]);
			stack.push_back(numbers[""]);

        	currentOperand = "";
        }
        else {
        	currentOperand += postfix.at(i);
        }
    }

    for (i=0; i<postfix.length(); i++) 
    { 
    	//std::cout << "pfi: " << i << "\n";
        if (postfix.at(i) == '#') {
        	stack[currentIndex] = intArray[arrayIndex];
        	currentIndex++;
        	arrayIndex++;
  
        } 
        else if (postfix.at(i) == '@') {
        	break;
        }
        else 
        { 
            switch (postfix.at(i)) 
            { 
	            //case '>': stack[currentIndex - 2].w = (stack[currentIndex - 2] > stack[currentIndex - 1]) ? 1 : 0; stack[currentIndex - 2].t = 'B'; break; 
	            //case '<': stack[currentIndex - 2].w = (stack[currentIndex - 2] < stack[currentIndex - 1]) ? 1 : 0; stack[currentIndex - 2].t = 'B'; break;
	            //case ']': stack[currentIndex - 2].w = (stack[currentIndex - 2] >= stack[currentIndex - 1]) ? 1 : 0; stack[currentIndex - 2].t = 'B'; break; 
	            //case '[': stack[currentIndex - 2].w = (stack[currentIndex - 2] <= stack[currentIndex - 1]) ? 1 : 0; stack[currentIndex - 2].t = 'B'; break;
	            case '+': stack[currentIndex - 2] = addTwo(stack[currentIndex - 2],stack[currentIndex - 1]); break;
	            case '-': stack[currentIndex - 1] = negateOne(stack[currentIndex - 1]); currentIndex++; break; 
	            case '*': stack[currentIndex - 2] = mulTwo(stack[currentIndex - 2],stack[currentIndex - 1]); break; 
	            case '/': stack[currentIndex - 1] = invertOne(stack[currentIndex - 1]); currentIndex++; break;
	            case '^': stack[currentIndex - 2] = expTwo(stack[currentIndex - 2],stack[currentIndex - 1]); break;
	            case -41: stack[currentIndex - 1] = factorialOne(stack[currentIndex - 1]); currentIndex++; break;
	            case -93: stack[currentIndex - 2] = logTwo(stack[currentIndex - 2],stack[currentIndex - 1]); break;
	            case -84: stack[currentIndex - 2] = rootNth(stack[currentIndex - 2],stack[currentIndex - 1]); break;
	            case -82: stack[currentIndex - 1] = roundOne(stack[currentIndex - 1]); currentIndex++; break;
	            case -67: stack[currentIndex - 1] = sqrtOne(stack[currentIndex - 1]); currentIndex++; break;
	            case -64: stack[currentIndex - 1] = trigTwo(-64,stack[currentIndex - 1]); currentIndex++; break;
	            case -63: stack[currentIndex - 1] = trigTwo(-63,stack[currentIndex - 1]); currentIndex++; break;
	            case -62: stack[currentIndex - 1] = trigTwo(-62,stack[currentIndex - 1]); currentIndex++; break;
	            case -61: stack[currentIndex - 1] = trigTwo(-61,stack[currentIndex - 1]); currentIndex++; break;
	            case -60: stack[currentIndex - 1] = trigTwo(-60,stack[currentIndex - 1]); currentIndex++; break;
	            case -59: stack[currentIndex - 1] = trigTwo(-59,stack[currentIndex - 1]); currentIndex++; break;
	            case -32: stack[currentIndex - 1] = invTrigTwo(-32,stack[currentIndex - 1]); currentIndex++; break;
	            case -31: stack[currentIndex - 1] = invTrigTwo(-31,stack[currentIndex - 1]); currentIndex++; break;
	            case -30: stack[currentIndex - 1] = invTrigTwo(-30,stack[currentIndex - 1]); currentIndex++; break;
	            case -29: stack[currentIndex - 1] = invTrigTwo(-29,stack[currentIndex - 1]); currentIndex++; break;
	            case -28: stack[currentIndex - 1] = invTrigTwo(-28,stack[currentIndex - 1]); currentIndex++; break;
	            case -27: stack[currentIndex - 1] = invTrigTwo(-27,stack[currentIndex - 1]); currentIndex++; break;
	            case -16: stack[currentIndex - 1] = hypTrigTwo(-16,stack[currentIndex - 1]); currentIndex++; break;
	            case -15: stack[currentIndex - 1] = hypTrigTwo(-15,stack[currentIndex - 1]); currentIndex++; break;
	            case -14: stack[currentIndex - 1] = hypTrigTwo(-14,stack[currentIndex - 1]); currentIndex++; break;
	            case -13: stack[currentIndex - 1] = hypTrigTwo(-13,stack[currentIndex - 1]); currentIndex++; break;
	            case -12: stack[currentIndex - 1] = hypTrigTwo(-12,stack[currentIndex - 1]); currentIndex++; break;
	            case -11: stack[currentIndex - 1] = hypTrigTwo(-11,stack[currentIndex - 1]); currentIndex++; break;
	            case '=': {
	            	if (stack[currentIndex - 2] == stack[currentIndex - 1]){
	            		Number nn;
	            		nn.type = 1;
	            		nn.top = "1";
	            		stack[currentIndex - 2] = nn;
	            		break;
	            	}
	            	else {
	            		Number nn;
	            		nn.type = 1;
	            		nn.top = "0";
	            		stack[currentIndex - 2] = nn;
	            		break;
	            	}
	            }
	            case '>': {
	            	if (stack[currentIndex - 2] > stack[currentIndex - 1]){
	            		Number nn;
	            		nn.type = 1;
	            		nn.top = "1";
	            		stack[currentIndex - 2] = nn;
	            		break;
	            	}
	            	else {
	            		Number nn;
	            		nn.type = 1;
	            		nn.top = "0";
	            		stack[currentIndex - 2] = nn;
	            		break;
	            	}
	            }
	            case '<': {
	            	if (stack[currentIndex - 2] > stack[currentIndex - 1]){
	            		Number nn;
	            		nn.type = 1;
	            		nn.top = "1";
	            		stack[currentIndex - 2] = nn;
	            		break;
	            	}
	            	else {
	            		Number nn;
	            		nn.type = 1;
	            		nn.top = "0";
	            		stack[currentIndex - 2] = nn;
	            		break;
	            	}
	            }
	            case ']': {
	            	if (stack[currentIndex - 2] < stack[currentIndex - 1]){
	            		Number nn;
	            		nn.type = 1;
	            		nn.top = "0";
	            		stack[currentIndex - 2] = nn;
	            		break;
	            	}
	            	else {
	            		Number nn;
	            		nn.type = 1;
	            		nn.top = "1";
	            		stack[currentIndex - 2] = nn;
	            		break;
	            	}
	            }
	            case '[': {
	            	if (stack[currentIndex - 2] > stack[currentIndex - 1]){
	            		Number nn;
	            		nn.type = 1;
	            		nn.top = "0";
	            		stack[currentIndex - 2] = nn;
	            		break;
	            	}
	            	else {
	            		Number nn;
	            		nn.type = 1;
	            		nn.top = "1";
	            		stack[currentIndex - 2] = nn;
	            		break;
	            	}
	            }
	            case '!': {
	            	if (stack[currentIndex - 2] == stack[currentIndex - 1]){
	            		Number nn;
	            		nn.type = 1;
	            		nn.top = "0";
	            		stack[currentIndex - 2] = nn;
	            		break;
	            	}
	            	else {
	            		Number nn;
	            		nn.type = 1;
	            		nn.top = "1";
	            		stack[currentIndex - 2] = nn;
	            		break;
	            	}
	            }
	            //case -125: stack[currentIndex - 2] = functionTwo(stack[currentIndex - 2],stack[currentIndex - 1]); break;
	            default: n.type = 0; solvedPostfixMap[postfix] = n; return n;
	            //case '!': stack[currentIndex - 2] = stack[currentIndex - 2] != stack[currentIndex - 1]; break;
	            //case '%': stack[currentIndex - 2] = stack[currentIndex - 2] % stack[currentIndex - 1]; break; 
	            //case '&': stack[currentIndex - 2].w = (stack[currentIndex - 2].w + stack[currentIndex - 1].w > 1) ? 1 : 0; stack[currentIndex - 2].t = (stack[currentIndex - 2].t == 'B' && stack[currentIndex - 1].t == 'B') ? 'B' : 'N'; break; 
	            //case '|': stack[currentIndex - 2].w = (stack[currentIndex - 2].w + stack[currentIndex - 1].w == 0) ? 0 : 1; stack[currentIndex - 2].t = (stack[currentIndex - 2].t == 'B' && stack[currentIndex - 1].t == 'B') ? 'B' : 'N'; break; 
	            //multiandcase '&': if (stack[currentIndex - 5] > 0 && stack[currentIndex - 4] > 0 && stack[currentIndex - 3] > 0 && stack[currentIndex - 2] > 0 && stack[currentIndex - 1] > 0) {stack[currentIndex - 5] = 1;} else {stack[currentIndex - 5] = -1;}; currentIndex--; currentIndex--; currentIndex--; currentIndex--; break; 
            
            } 
            if (maxDigits >= 0){
            	stack[currentIndex - 2] = roundNumber(stack[currentIndex - 2]);
            }
            
            currentIndex--;
        } 
    } 
	
	solvedPostfixMap[postfix] = stack[0];
	return stack[0];
}

std::vector<std::string> factorList(std::string input) {

	int i;
	int n = std::stoi(input);
	if (n<1){
		return {};
	}
	std::vector<std::string> list;
	list.push_back("1");
	for (i=2;i<n;i++){
		if (n%i == 0){
			list.push_back(std::to_string(i));
		}
	}
	list.push_back(input);
	return list;
}
std::map<std::string,std::string> conditionalPostfixList;

std::string solveConditionalPostfix(std::string var){
	if (conditionalPostfixList.find(var) != conditionalPostfixList.end()){
		return conditionalPostfixList[var];
	}
	std::vector<Number> possibleValues;
	std::string x = "";
	std::string xxl = "";
	std::string xxr = "";
	std::string expressionl = "";
	std::string expressionr = "";
	bool pastKey = false;
	bool pastFirst = false;
	int idx = 1;
	int i;
	std::string currentOperand = "";
	for (i=1;i<var.length();i++){
		if (var.at(i) == '@'){
			pastKey = true;
			pastFirst = false;
		}
		else if (var.at(i) == -95){
			pastFirst = true;
		}
		else if (var.at(i) == '&'){
		
		}
		else if (!pastFirst && !pastKey){
			xxl += var.at(i);
			if (var.at(i)=='#'){
				idx++;
			}
		}
		else if (pastFirst && !pastKey){
			expressionl += var.at(i);
		}
		else if (!pastFirst && pastKey){
			if (var.at(i) == '_'){
				pastFirst = true;
				idx--;
			}
			else {
				x += var.at(i);
			}
		}
		else {
			if (idx > 0){
				xxr += var.at(i);
			}
			else {
				expressionr += var.at(i);
			}
			if (var.at(i) == '_'){
				idx--;
			}
		}
	}
	std::string xxrp = xxr.substr(0,xxr.length()-1);
	if (numbers.find(xxrp) == numbers.end()){
		numberType(xxrp);
	}
	if (numbers[xxrp].type != 1 && numbers[xxrp].type != -1){
		conditionalPostfixList[var]="##@";
		return "##@";
	}

		
		std::vector<std::string> list = factorList(xxrp);
		int ii;
		for (ii=0;ii<list.size();ii++){
			std::string currentOperand = "";
			std::string newPostfix = expressionl+"@";
			for (i=0;i<expressionr.length();i++){
				if (expressionr.at(i) == '_'){
					if (currentOperand == x){
						newPostfix += list[ii]+"_";
					}
					else {
						if (numbers.find(currentOperand) == numbers.end()){
							numberType(currentOperand);
						}
						if (numbers[currentOperand].type != 1 && numbers[currentOperand].type != -1){
							conditionalPostfixList[var]="##@";
							return "##@";
						}
						newPostfix += currentOperand+"_";
					}
					currentOperand = "";
				}
				else {
					currentOperand += expressionr.at(i);
				}
			}
			Number n = solvePostfix(newPostfix);
			if (n.type == 1 && n.top == "1"){
				//std::cout << "npf: " << newPostfix << " and " << "true"<< "\n";
				conditionalPostfixList[var]="##=@C_"+list[ii]+"_";
				return "##=@C_"+list[ii]+"_";
			}
			
		}
		//std::cout << "var: " << var << " and " << x << " and " << xxl << " and " << xxr << " and " << expressionl << " and " << expressionr << "\n";
	
	conditionalPostfixList[var]="##@";
	return "##@";
}

std::vector<std::string> varToX(std::string var) {
	std::string x = "";
	std::string xxl = "";
	std::string xxr = "";
	bool pastKey = false;
	int idx = 0;
	int i;
	for (i=1;i<var.length();i++){
		if (var.at(i) == '@'){
			if (i>0 && var.at(i-1) == '&'){
				var = solveConditionalPostfix(var);
				return varToX(var);
			}
			if (i>0 && var.at(i-1) != '='){
				return {};
			}
			pastKey = true;
		}
		else if (var.at(i) == '_'){
			if (idx == 0){
				
			}
			else {
				xxr += var.at(i);
			}
			idx++;
		}
		else if (var.at(i) == '=' && !pastKey){
			if (i+1<var.length() && var.at(i+1) == '@'){
			
			}
			else {
				xxl += var.at(i);
			}
		}
		else {
			if (pastKey && idx>0){
				xxr += var.at(i);
			}
			else if (pastKey){
				x += var.at(i);
			}
			else {
				xxl += var.at(i);
			}
		}
	}
	return {x,xxl,xxr};
}

std::string substitute(std::string input){
	std::string returnStr = "("+input+")";
	if (input.length() < 4){
		return returnStr;
	}
	std::string var = "";
	int i;
	if (input.at(0) != '#' || input.at(1) != '#' || input.at(2) != -102 || input.at(3) != '@'){
		//TODO: grab the part up to & and convert to format
		std::string left = "";
		std::string right = "";
		std::string left2 = "";
		std::string right2 = "";
		bool pastKey= false;
		bool pastAnd= false;
		int idx = 0;
		for (i=0;i<input.length();i++){
			if (input.at(i)=='{'){
				return returnStr;
			}
			
			
			if (input.at(i)=='&'){
				pastAnd = true;
				left += input.at(i);
			}
			else if (input.at(i)=='@'){
				pastKey = true;
			}
			else if (!pastAnd){
				left += input.at(i);
				if (input.at(i)=='#'){
					idx++;
				}
			}
			else if (pastAnd && !pastKey){
				if (input.at(i) != -102){
					left2 += input.at(i);
				}
			}
			else if (pastKey && input.at(i)=='_'){
				if (idx >0){
					right += input.at(i);
				}
				else {
					right2 += input.at(i);
				}
				idx--;
				
			}
			else if (pastKey && idx > 0){
				right += input.at(i);
			}
			else if (pastKey){
				right2 += input.at(i);
			}
		}
		//std::cout << "l: " << left << " and " << right << "\n";
		//std::cout << "l2: " << left2 << " and " << right2 << "\n";
		var = solveConditionalPostfix(left + "@" + right);
		if (var == "##@"){
			//std::cout << "fin: nothing" << "\n";
			return returnStr;
		}
		char sub{-102};
		std::string substr = "";
		substr += sub;
		input = "##"+substr+"@{"+var+"}_{"+left2+"@"+right2+"}_";
		//std::cout << "fin: "<< input << "\n";
	}
	var = "";
	std::string expression = "";
	bool isExpression = false;
	bool inBrackets = false;
	for (i=4;i<input.length();i++){
		if (input.at(i)=='{'){
			inBrackets = true;
		}
		else if (input.at(i)=='}'){
			inBrackets = false;
		}
		else if (input.at(i)=='_'){
			if (inBrackets){
				if (isExpression){
					expression += input.at(i);
				}
				else {
					var += input.at(i);
				}
			}
			else {
				isExpression = true;
			}
		}
		else {
			if (isExpression){
				expression += input.at(i);
			}
			else {
				var += input.at(i);
			}
		}
	}
	//std::cout << "var: " << var << " and " << expression << "\n";
	std::string x = "";
	std::string xxl = "";
	std::string xxr = "";
	bool pastKey = false;
	int idx = 0;
	std::vector<std::string> xv = varToX(var);
	if (xv.size() < 3){
		return returnStr;
	}
	x = xv[0]; xxl = xv[1]; xxr = xv[2];

	std::string currentOperand = "";
	pastKey = false;
	idx=0;
	std::string newPostfix = "";
	//std::cout << "x: " << x << " and " << xxl << " and " << xxr << "\n";
	for (i=0;i<expression.length();i++){
		if (expression.at(i) == '@'){
			pastKey = true;
			newPostfix += "@";
		}
		else if (expression.at(i) == '_'){
			if (currentOperand == x){
				newPostfix += "{"+xxl+"@"+xxr+"}_";
			}
			else {
				newPostfix += currentOperand+"_";
			}
			currentOperand = "";
		}
		else if (pastKey){
			currentOperand += expression.at(i);
		}
		else {
			newPostfix += expression.at(i);
		}
	}
	//std::cout << "newPostfix: " << newPostfix << "\n";
	if (newPostfix != input){
		//std::cout << input << " andand " << newPostfix << "\n";
	}
	return "("+newPostfix+")";
}


std::string solveFunction(std::string input){
	std::string returnStr = "("+input+")";
	if (input.length() < 4){
		return returnStr;
	}
	std::string var = "";
	int i;
	input = removeBracketsOne(input);
	std::string functionName = "";
	int idx = 0;
	int iidx = 0;
	std::string currentOperand = "";
	std::string inputLeft = "";
	std::string inputRight = "";
	for (i=1;i<input.length();i++){
		if (input.at(i) == '@'){
			if (i>0 && input.at(i-1) != -125){
				return returnStr;
			}
			currentOperand = "";
		}
		else if (input.at(i) == '_'){
			if (idx==0){
				functionName = currentOperand;
			}
			else {
				inputRight += currentOperand + "_";
			}
			currentOperand = "";
			idx++;
		}
		else if (input.at(i) == '#'){
			currentOperand += input.at(i);
		}
		else if (input.at(i) == -125){
			if (i+1<input.length() && input.at(i+1) == '@'){
				inputLeft = currentOperand;
				currentOperand = "";
			}
			else {
				currentOperand += input.at(i);
			}
		}
		else {
			currentOperand += input.at(i);
		}
	}

	if (functionMap.find(functionName) != functionMap.end()){
		Function f = functionMap[functionName];
		
		std::string finput = inputLeft+"@"+inputRight;
		//string_log("function found");
		//string_log(input.c_str());
		//string_log(finput.c_str());
		
		if (inputLeft == "#"){
			if (f.initial.find(finput) != f.initial.end()){
				return "("+f.initial[finput]+")";
			}
			int maxIter = -10001;
			int goalIter = std::stoi(inputRight.substr(0,inputRight.length()-1));
			for (std::map<std::string,std::string>::iterator iter = f.initial.begin(); iter != f.initial.end(); ++iter){
				int v = std::stoi(iter->first.substr(2,iter->first.length()-3));
				if (v == goalIter){
					return "("+iter->second+")";
				}
				if (v > maxIter){
					maxIter = v;
				}
			}
			if (maxIter>-10001 && goalIter > maxIter+1){
				string_log("maxIter");
				console_log(maxIter);
				int ci;
				for (ci=maxIter+1;ci<=goalIter;ci++){
					char fnc{-125};
					std::string fnstr(1,fnc);
					std::string fpostfix = "##"+fnstr+"@f_"+std::to_string(ci)+"_";
					finput = "#@"+std::to_string(ci)+"_";
					std::string solved = solveArithmetic(fpostfix);
					functionMap[functionName].initial["#@"+std::to_string(ci)+"_"] = solved;
				}
				return "("+functionMap[functionName].initial[finput]+")";
			
			}
			
		}
		else if (inputLeft == "##-+"){
			int diff = 0;
			if (inputRight.at(inputRight.length()-3) == '_' && inputRight.at(inputRight.length()-1) == '_'){
				diff = inputRight.at(inputRight.length()-2) - '0';
			}
			else {
				return returnStr;
			}
			int np1 = std::stoi(inputRight.substr(0,inputRight.length()-3));
			finput = "#@"+std::to_string(np1-diff)+"_";
			//string_log("np1");
			//string_log(finput.c_str());
			if (f.initial.find(finput) != f.initial.end()){
				//string_log("function exists");
				//string_log(f.initial[finput].c_str());
				return "("+f.initial[finput]+")";
			}
			int maxIter = -10001;
			int goalIter = np1-diff;
			for (std::map<std::string,std::string>::iterator iter = f.initial.begin(); iter != f.initial.end(); ++iter){
				int v = std::stoi(iter->first.substr(2,iter->first.length()-3));
				if (v == goalIter){
					return "("+iter->second+")";
				}
				if (v > maxIter){
					maxIter = v;
				}
			}
			if (maxIter>-10001 && goalIter > maxIter+1){
			
				int ci;
				for (ci=maxIter+1;ci<=goalIter;ci++){
					char fnc{-125};
					std::string fnstr(1,fnc);
					std::string fpostfix = "##"+fnstr+"@f_"+std::to_string(ci)+"_";
					//string_log("function computing");
					//string_log(fpostfix.c_str());
					finput = "#@"+std::to_string(ci)+"_";
					//string_log(finput.c_str());
					std::string solved = solveArithmetic(fpostfix);
					//string_log(solved.c_str());
					//string_log("function computed");
					functionMap[functionName].initial["#@"+std::to_string(ci)+"_"] = solved;
				}
				return "("+functionMap[functionName].initial[finput]+")";
			
			}
			
		}
		
		else {
			string_log("none");
			string_log(inputLeft.c_str());
			string_log(inputRight.c_str());
			return returnStr;
		}

		std::string newPostfix = f.postfix;
		for (i=f.rightIdx.size()-1;i>=0;i--){
			newPostfix.replace(f.rightIdx[i],f.var.length()+1,inputRight);
		}
		for (i=f.leftIdx.size()-1;i>=0;i--){
			newPostfix.replace(f.leftIdx[i],1,inputLeft);
		}
		return "("+newPostfix+")";
	}
	else {
		return returnStr;
	}
	
	return returnStr;

	//return solvePostfix(newPostfix);
	
	
}

