
std::string opstart = "<div class=\"operator\">";
std::string parstart = "<div class=\"parentheses\"><svg viewBox=\"0 0 30 100\" width=\"30\" height=\"100\"><path d=\"M30 0 Q 0 50 30 100\" fill=\"none\" stroke=\"black\" stroke-width=\"3\"/></svg>";
std::string parend = "<svg viewBox=\"0 0 30 100\" width=\"30\" height=\"100\"><path d=\"M0 0 Q 30 50 0 100\" fill=\"none\" stroke=\"black\" stroke-width=\"3\"/></svg>\n</div>";
std::string bracketstart = "<div class=\"parentheses\"><svg viewBox=\"0 0 20 100\" width=\"20\" height=\"100\"><path d=\"M20,0 0,0 0,100 20,100\" fill=\"none\" stroke=\"black\" stroke-width=\"3\"/></svg>";
std::string bracketend = "<svg viewBox=\"0 0 20 100\" width=\"20\" height=\"100\"><path d=\"M0,0 20,0 20,100 0,100\" fill=\"none\" stroke=\"black\" stroke-width=\"3\"/></svg>\n</div>";
std::string divend = "\n</div>";
std::string integralsvg = "<svg viewBox=\"0 0 30 100\" width=\"30\" height=\"100\"><path d=\"m 29 20 Q 25 0 17 20 Q 15 50 13 80 Q 5 95 1 80\" fill=\"none\" stroke=\"black\" stroke-width=\"5\"/></svg>";

std::string charCodeToString(int x){
	std::string s = "-";
	if (x >= 0){s = "+";}
	else {x *= -1;}
	if (x < 10){s+= "0";}
	if (x < 100){s+= "0";}
	s += std::to_string(x);
	return s;
}
std::string imcssLogic(char c, std::string s, int ii, std::string child, char lastOp, std::string outputStr, std::string outputID){
	switch (c){
		case '^': {
			if (ii > 0){
				//s += "^{";
				//s += child+"}";
				s += "<div class=\"noflow\">";
				s += child+"\n</div>\n</div>";
			}
			else {
				if (prec[lastOp] < 100){
					//s += "("+child+")";
					s += "<div class=\"power\" id=\""+outputID+"\" data-original=\""+outputStr+"\">\n("+child+")";
				}
				else {
					//s += child;
					s += "<div class=\"power\" id=\""+outputID+"\" data-original=\""+outputStr+"\">\n<div class=\"number\">"+child+"\n</div>";
				}
			}
			break;
		}
		case -69: {//Derivative
			if (ii > 0){
				s += "<div class=\"margin\">"+child+divend+"]"+divend;
			}
			else {
				//s += "\\frac{d}{d"+child+"}[";
				s += "<div class=\"derivative\" id=\""+outputID+"\" data-original=\""+outputStr+"\"><div class=\"fraction\"><div class=\"operator\">d</div><div class=\"bar\"></div><div class=\"operator\"><div class=\"margin\">d"+child+divend+"</div>"+divend+"[";
			}
			break;

		}
		case -85: {//Integral
			if (ii > 0){
				//s.replace(5,0,child+" \\text{d");
				std::string dx = s;
				s = "<div class=\"integral\" id=\""+outputID+"\" data-original=\""+outputStr+"\">"+integralsvg;
				s += "<div class=\"margin\">"+child+divend;
				s += "<div class=\"number margin\">0</div><div class=\"number margin\">10</div><div class=\"number margin\">"+dx+"</div>"+divend;
			}
			else {
				s += child;
			}
			break;

		}
		case -101: {//max
			if (ii > 1){
				s.replace(s.length()-1,1,"");
				if (lastOp == -101){
					s += ","+child.substr(5,child.length()-6)+")";
				}
				else {
					s += ",";
					s += child+")";
				}
			}
			else if (ii > 0){
				if (lastOp == -101){
					s += ","+child.substr(5,child.length()-6)+")";
				}
				else {
					s += ",";
					s += child+")";
				}
			}
			else {
				if (lastOp == -101){
					s += child.substr(0,child.length()-1);
				}
				else {
					s += "\\max("+child;
				}
				
			}
			break;
		}
		case -100: {//min
			if (ii > 1){
				s.replace(s.length()-1,1,"");
				if (lastOp == -100){
					s += ","+child.substr(5,child.length()-6)+")";
				}
				else {
					s += ",";
					s += child+")";
				}
			}
			else if (ii > 0){
				if (lastOp == -100){
					s += ","+child.substr(5,child.length()-6)+")";
				}
				else {
					s += ",";
					s += child+")";
				}
			}
			else {
				if (lastOp == -100){
					s += child.substr(0,child.length()-1);
				}
				else {
					s += "\\min("+child;
				}
				
			}
			break;
		}
		case -97: { //combinations
			if (ii > 0){
				s += " \\choose ";
				s += child+"}";
			}
			else {
				s += "{"+child;
			}
			break;
		}
		case -98: { //permutations
			if (ii > 0){
				s += "}\\!P_{";
				s += child+"}";
			}
			else {
				s += "{}^{"+child;
			}
			break;
		}
		case -99: { //gcd
			if (ii > 0){
				s += ",";
				s += child+")";
			}
			else {
				s += "\\gcd("+child;
			}
			break;
		}
		case -34: {//absolute value
			//s += "|"+child+"|";
			s += "<div class=\"abs margin\" id=\""+outputID+"\" data-original=\""+outputStr+"\">"+child+"\n</div>";
			break;}
		case -64:{
			//s += "\\sin("+child+")";
			s += "<div class=\"trig\" id=\""+outputID+"\" data-original=\""+outputStr+"\">"+opstart+"sin"+divend+"("+"<div class=\"margin\">"+child+divend+")"+divend;
			break;}
		case -63:{
			s += "<div class=\"trig\" id=\""+outputID+"\" data-original=\""+outputStr+"\">"+opstart+"cos"+divend+"("+"<div class=\"margin\">"+child+divend+")"+divend;
			break;}
		case -62:{
			s += "<div class=\"trig\" id=\""+outputID+"\" data-original=\""+outputStr+"\">"+opstart+"tan"+divend+"("+"<div class=\"margin\">"+child+divend+")"+divend;
			break;}
		case -61:{
			//s += "\\csc("+child+")";
			s += "<div class=\"trig\" id=\""+outputID+"\" data-original=\""+outputStr+"\">"+opstart+"csc"+divend+"("+"<div class=\"margin\">"+child+divend+")"+divend;
			break;}
		case -60:{
			//s += "\\sec("+child+")";
			s += "<div class=\"trig\" id=\""+outputID+"\" data-original=\""+outputStr+"\">"+opstart+"sec"+divend+"("+"<div class=\"margin\">"+child+divend+")"+divend;
			break;}
		case -59:{
			//s += "\\cot("+child+")";
			s += "<div class=\"trig\" id=\""+outputID+"\" data-original=\""+outputStr+"\">"+opstart+"cot"+divend+"("+"<div class=\"margin\">"+child+divend+")"+divend;
			break;}
		case -32:{
			//s += "\\sin^{-1}("+child+")";
			s += "<div class=\"trig\" id=\""+outputID+"\" data-original=\""+outputStr+"\">"+opstart+"sin<sup>-1</sup>"+divend+"("+"<div class=\"margin\">"+child+divend+")"+divend;
			break;}
		case -31:{
			//s += "\\cos^{-1}("+child+")";
			s += "<div class=\"trig\" id=\""+outputID+"\" data-original=\""+outputStr+"\">"+opstart+"cos<sup>-1</sup>"+divend+"("+"<div class=\"margin\">"+child+divend+")"+divend;
			break;}
		case -30:{
			//s += "\\tan^{-1}("+child+")";
			s += "<div class=\"trig\" id=\""+outputID+"\" data-original=\""+outputStr+"\">"+opstart+"tan<sup>-1</sup>"+divend+"("+"<div class=\"margin\">"+child+divend+")"+divend;
			break;}
		case -29:{
			//s += "\\csc^{-1}("+child+")";
			s += "<div class=\"trig\" id=\""+outputID+"\" data-original=\""+outputStr+"\">"+opstart+"csc<sup>-1</sup>"+divend+"("+"<div class=\"margin\">"+child+divend+")"+divend;
			break;}
		case -28:{
			//s += "\\sec^{-1}("+child+")";
			s += "<div class=\"trig\" id=\""+outputID+"\" data-original=\""+outputStr+"\">"+opstart+"sec<sup>-1</sup>"+divend+"("+"<div class=\"margin\">"+child+divend+")"+divend;
			break;}
		case -27:{
			//s += "\\cot^{-1}("+child+")";
			s += "<div class=\"trig\" id=\""+outputID+"\" data-original=\""+outputStr+"\">"+opstart+"cot<sup>-1</sup>"+divend+"("+"<div class=\"margin\">"+child+divend+")"+divend;
			break;}
		case -16:{
			//s += "\\text{sinh}("+child+")";
			s += "<div class=\"trig\" id=\""+outputID+"\" data-original=\""+outputStr+"\">"+opstart+"sinh"+divend+"("+"<div class=\"margin\">"+child+divend+")"+divend;
			break;}
		case -15:{
			//s += "\\text{cosh}("+child+")";
			s += "<div class=\"trig\" id=\""+outputID+"\" data-original=\""+outputStr+"\">"+opstart+"cosh"+divend+"("+"<div class=\"margin\">"+child+divend+")"+divend;
			break;}
		case -14:{
			//s += "\\text{tanh}("+child+")";
			s += "<div class=\"trig\" id=\""+outputID+"\" data-original=\""+outputStr+"\">"+opstart+"tanh"+divend+"("+"<div class=\"margin\">"+child+divend+")"+divend;
			break;}
		case -13:{
			//s += "\\text{csch}("+child+")";
			s += "<div class=\"trig\" id=\""+outputID+"\" data-original=\""+outputStr+"\">"+opstart+"csch"+divend+"("+"<div class=\"margin\">"+child+divend+")"+divend;
			break;}
		case -12:{
			//s += "\\text{sech}("+child+")";
			s += "<div class=\"trig\" id=\""+outputID+"\" data-original=\""+outputStr+"\">"+opstart+"sech"+divend+"("+"<div class=\"margin\">"+child+divend+")"+divend;
			break;}
		case -11:{
			//s += "\\text{coth}("+child+")";
			s += "<div class=\"trig\" id=\""+outputID+"\" data-original=\""+outputStr+"\">"+opstart+"coth"+divend+"("+"<div class=\"margin\">"+child+divend+")"+divend;
			break;}
		case -67:{
			//s += "\\sqrt{"+child+"}";
			s += "<div class=\"root\" id=\""+outputID+"\" data-original=\""+outputStr+"\"><svg viewBox=\"0 0 50 100\" width=\"50\" height=\"100\"><path d=\"M0 60 15 60 25 100 50 0\" fill=\"none\" stroke=\"black\" stroke-width=\"5\"/></svg><div class=\"margin\">"+child+"\n</div>\n</div>";
			break;}
		case -84: {
			if (ii > 0){
				//s += child+"}";
				s += "<div class=\"margin\">"+child+"\n</div>\n</div>";
			}
			else {
				//s += "\\sqrt["+child+"]{";
				s += "<div class=\"root\" data-original=\""+outputStr+"\"><svg viewBox=\"0 0 50 100\" width=\"50\" height=\"100\"><path d=\"M0 60 15 60 25 100 50 0\" fill=\"none\" stroke=\"black\" stroke-width=\"5\"/></svg><div class=\"margin\">"+child+"\n</div>";
			}
			break;

		}
		case -105: {
			if (ii > 0){
				//s += "\\pluseq "+child;
				s += opstart+"+="+divend+child;
			}
			else {
				s += child;
			}
			break;
		}
		case -106: {
			if (ii > 0){
				//s += "\\minuseq"+child;
				s += opstart+"-="+divend+child;
			}
			else {
				s += child;
			}
			break;
		}
		case -125: {
			if (ii > 0){
				s += child+")"+divend;
			}
			else {
				//s += "\\text{"+child+"}(";
				s += "<div class=\"function\" id=\""+outputID+"\" data-original=\""+outputStr+"\">"+child+"(";
			}
			break;
		}
		case -126: {
			if (ii > 1){
				s += child+")"+divend;
			}
			else if (ii == 1){
				s += child+",";
			}
			else {
				//s += "\\text{"+child+"}(";
				s += "<div class=\"function\" id=\""+outputID+"\" data-original=\""+outputStr+"\">"+child+"(";
			}
			break;
		}
		case -93: {
			if (ii > 0){
				if (prec[lastOp] < 100){
					s += "("+child+")"+divend;
				}
				else {
					s += child+divend;
				}
	
			}
			else {
				if (child == "<div class=\"number\">e</div>"){
					//s += "\\ln ";
					s += "<div class=\"log\" id=\""+outputID+"\" data-original=\""+outputStr+"\">ln";
				}
				else {
					//s += "\\log_{"+child+"} ";
					s += "<div class=\"log\" id=\""+outputID+"\" data-original=\""+outputStr+"\">log<sub>"+child+"</sub>";
				}
			}
			break;

		}
		case -41: {
			if (prec[-41] >= prec[lastOp]){
				s += "("+child + ")!";
			}
			else {
				s += child + "!";
			}
			break;
		}
		case '!': {
			if (ii > 0){
				//s += child;
				s += child+divend;
			}
			else {
				//s += child+"\\neq ";
				s += "<div class=\"comparison\" id=\""+outputID+"\" data-original=\""+outputStr+"\"><div class=\"number\">"+child+"\n</div><div class=\"number\">&ne;\n</div>";

			}
			break;
		}
		case '[': {
			if (ii > 0){
				//s += child;
				s += child+divend;
			}
			else {
				//s += child + "\\leq ";
				s += "<div class=\"comparison\" id=\""+outputID+"\" data-original=\""+outputStr+"\"><div class=\"number\">"+child+"\n</div><div class=\"number\">&lte;\n</div>";
			}
			break;
		}
		case ']': {
			if (ii > 0){
				//s += child;
				s += child+divend;
			}
			else {
				//s += child + "\\geq ";
				s += "<div class=\"comparison\" id=\""+outputID+"\" data-original=\""+outputStr+"\"><div class=\"number\">"+child+"\n</div><div class=\"number\">&gte;\n</div>";
			}
			break;
		}
		case '<': {
			if (ii > 0){
				//s += child;
				s += child+divend;
			}
			else {
				//s += child+"< ";
				s += "<div class=\"comparison\" id=\""+outputID+"\" data-original=\""+outputStr+"\"><div class=\"number\">"+child+"\n</div><div class=\"number\">&lt;\n</div>";
			}
			break;
		}
		case '>': {
			if (ii > 0){
				//s += child;
				s += child+divend;
			}
			else {
				//s += child+"> ";
				s += "<div class=\"comparison\" id=\""+outputID+"\" data-original=\""+outputStr+"\"><div class=\"number\">"+child+"\n</div><div class=\"number\">&gt;\n</div>";
			}
			break;
		}
		case '=': {
			if (ii > 0){
				//s += child;
				s += child+divend;
			}
			else {
				//s += child+"= ";
				s += "<div class=\"comparison\" id=\""+outputID+"\" data-original=\""+outputStr+"\"><div class=\"number\">"+child+"\n</div><div class=\"number\">=\n</div>";
			}
			break;
		}
		case -79: {
			if (ii>0){
				if (prec[-79] > prec[lastOp]){
					s += "&plusmn;("+child+")";
				}
				else {
					s += "&plusmn;"+child;
				}
			}
			else {
				if (child == "0"){
					//skip
				}
				else {
					if (prec[-79] > prec[lastOp]){
						s += "("+child+")";
					}
					else {
						s += child;
					}
				}
				
			}
			break;
		}
		case '-': {
			if (prec['-'] >= prec[lastOp]){
				//s += "-("+child+")";
				s += opstart+"-"+divend+"("+child+")";
			}
			else {
				s += opstart+"-"+divend+child;
			}
			break;
		}
		case '/': {
			//TODO: check if child is \\frac{}{}
			s += "\\frac{1}{"+child+"}";
			
			
		
		
			/*
			if (prec['/'] >= prec[lastOp]){
				s += "/("+child+")";
			}
			else {
				s += "/"+child;
			}*/
			break;
		}
		case '%': {
			if (ii>0){
				if (prec['%'] > prec[lastOp]){
					s += "\\pmod{("+child+")}";
				}
				else {
					s += "\\pmod{"+child+"}";
				}
			}
			else {
				if (prec['%'] > prec[lastOp]){
					//s += "("+child+")";
					s += "("+child+")";
				}
				else {
					s += child;
				}
			}
			break;
		}
		default: {
			if (prec[c] > prec[lastOp]){
				if (ii > 0){
					if (c == '*'){
						if (s.length()>0 && (s.at(s.length()-1) >= '0' && s.at(s.length()-1) <= '9')){
							//s += "("+child+")";
							s += "("+child+")";
						}
						else {
							s += "&middot;("+child+")";//want to move this into numerator somehow
						}
					
					}
					else if (c == '&'){
						s += "<div class=\"text\"> AND </div>("+child+")";
					}
					else if (c == '|'){
						s += "<div class=\"text\"> OR </div>("+child+")";
					}
					else {
						//s += c+"("+child+")";
						s += opstart;
						s += c + divend + "("+child+")";
					}
				}
				else {
					if (lastOp == '-'){
						//s += child;
						s += child;
					}
					else {
						//s += "("+child+")";
						s += "("+child+")";
					}
				}
			}
			else if (prec[c] == prec[lastOp] && c != lastOp){
				if (ii > 0){
					if (c == '*'){
						//This is the * right after /
						//TODO: deal with fraction in s
						//TODO: deal with non-1 in numerator of child
						int iii; int openBracket = 0;
						
						for (iii=0;iii<s.length();iii++){
							if (s.at(iii) == ')' && iii != 0){openBracket--;}
							else if (s.at(iii) == '(' && iii < s.length()-1){openBracket++;}
							else if (iii == 0 || iii == s.length()-1){
								break;
							}
							
							if (openBracket == 0 && iii == s.length()-1){
								s.replace(0,1,"");
								s.replace(s.length()-1,1,"");
								break;
							}
						}
						std::string numer = s;
						std::string denom = "1";
						openBracket = 1;
						int startDenom = 0;
						for (iii=6;iii<child.length();iii++){
							if (child.at(iii) == '}'){openBracket--;}
							else if (child.at(iii) == '{'){openBracket++;}
							
							if (openBracket == 0 && startDenom == 0){
								startDenom = iii+2;
							}
							else if (openBracket == 0){
								denom = child.substr(startDenom,iii-startDenom);
								break;
							}
						}
						//child = \\frac{1}{denom}
						//s = numer
						s = "<div class=\"fraction\" data-original=\""+outputStr+"\"><div class=\"number margin numer1\">"+numer+"</div><div class=\"bar\"></div><div class=\"number margin denom1\">";
						s += denom;
						s += "\n</div>\n</div>";
					
					}
					else if (c == '+'){
						//s += child;
						s += child;
					}
					else if (c == '&'){
						s += "<div class=\"text\"> AND </div>("+child+")";
					}
					else if (c == '|'){
						s += "<div class=\"text\"> OR </div>("+child+")";
					}
					else {
						s += "<div class=\"operation\">";
						s += c+"\n</div>";
						s += "("+child+")";
					}
				}
				else {
					if (c == '*'){
						s += child;
					}
					else if (c == '+'){
						s += child;
					}
					else {
						//s += "("+child+")";
						s += "("+child+")";
					}
				}
			}
			else {
				if (ii > 0){
					if (c == '*'){
						//TODO: deal with fraction in s or child
						if (s == "-1"){
							s = opstart+"-"+divend+child;
						}
						else if (s.length()>0 && (s.at(s.length()-1) >= '0' && s.at(s.length()-1) <= '9')){
							if (child.length()>0 && (child.at(0) >= '0' && child.at(0) <= '9')){
								//digit followed by digit
								s += "&middot;"+child;
							}
							else{
								//digit followed by not a digit
								//s += child;
								s += child;
							}
						}
						else {
							s += "&middot;"+child;
						}
					}
					else if (c == '&'){
						s += "<div class=\"text\"> AND </div>"+child;
					}
					else if (c == '|'){
						s += "<div class=\"text\"> OR </div>"+child;
					}
					else {
						//s += c+child;
						s += opstart + c + divend;
						s += child;
					}
				}
				else {
					s += child;
				}
			}
		}
	}
	return s;
}

std::map<std::string,std::string> toImcss(std::vector<std::string> input){
	int i; int ii;
	std::map<std::string,std::string> imcssMap;
	std::map<std::string,char> lastOpMap;
	std::map<std::string,std::vector<std::string>> childMap;
	childMap[""]={};
	for (i=0;i<input.size()/3;i++){
		//std::cout << input[i*3] << "\n";
		//std::cout << input[i*3+1] << "\n";
		//std::cout << input[i*3+2] << "\n";
		char lastOp = '#';
		bool foundAt = false;
		std::string firstOperand = "";
		for (ii=0;ii<input[i*3+2].size();ii++){
			if (input[i*3+2].at(ii) == '@'){
				foundAt = true;
			}
			else if (!foundAt){
				lastOp = input[i*3+2].at(ii);
			}
			else if (input[i*3+2].at(ii) == '_'){
				break;
			}
			else {
				firstOperand += input[i*3+2].at(ii);
			}
		}
		imcssMap[input[i*3]]="";
		childMap[input[i*3]]={};
		childMap[input[i*3+1]].push_back(input[i*3]);
		if (lastOp == '#'){
			imcssMap[input[i*3]]=firstOperand;
			lastOpMap[input[i*3]]='#';
			//std::cout << firstOperand << " is first s of: " << input[i*3] <<"\n";
		}
		else {
			lastOpMap[input[i*3]]=lastOp;
		}
	}
	int newImcss = 1;
	int count =0;
	while (newImcss>0 && count < 1000){
		newImcss = 0;
		for (i=0;i<input.size()/3;i++){
			bool allChildren = true;
			std::string s = "";
			std::string outputStr = "";
			for (ii=0;ii<childMap[input[i*3]].size();ii++){
				std::string child = childMap[input[i*3]][ii]; //is name of child
				//std::cout << "child: " << child << " imcss of child: " << imcssMap[child] << " and s: " << s << "\n";
				if (imcssMap[child] == ""){
					allChildren = false;
					break;
				}
				else {
					s = imcssLogic(lastOpMap[input[i*3]], s, ii, imcssMap[child],lastOpMap[child], outputStr, "");
					
					
				}
			}
			if (allChildren && imcssMap[input[i*3]]=="" && s != ""){
				newImcss++;
				imcssMap[input[i*3]]=s;
				//std::cout << "\ns: "<< s << " is s for " << input[i*3] << "\n";
			}
		}
		count++;
	}

	
	return imcssMap;
}

std::string imcssOne(std::string input,int startNode,std::map<int,bool> bMap, std::string followA, std::string userInput) {

	int i; int ii; int iii; int idx = 0;
	bool startOperands = false;
	std::string currentOperator = "";
	std::map<int,std::string> originalMap;
	int iidx = 0;
	std::string pfstr = input;
	int startAt =0;
	std::string fullUser = "";
	std::map<int,int> fullUserMap;
	
	
	for (i=userInput.length()-1;i>=0;i--){
		int largestLess = 0;
		if (i == userInput.length()-1){fullUserMap[i]=0;}
		else {fullUserMap[i]=fullUserMap[i+1];}
		
		if (userInput.at(i) != '(' && userInput.at(i) != '[' && userInput.at(i) != '{'){
			for (ii=0;ii<followA.length();ii++){
				int c = followA.at(ii);
				if (c < i+2 && c > largestLess){
					fullUserMap[i]=ii;
					largestLess = c;
				}
			}
		}
		
	}
	for (i=0;i<pfstr.length();i++){
		if (pfstr.at(i) == '@'){
			startOperands = true;
			startAt = i;
		}
		else if (pfstr.at(i) == '('){
			std::map<int,int> m = removeParList({},pfstr);
			std::map<std::string, std::string> followAMap;
			followAMap["original"]=followA;
			pfstr = removeParOne(pfstr,followAMap);
			
			int offset = 0;
			std::map<int,bool> mm;
			for (iii=0;iii<startAt;iii++){
				if (m.find(iii+offset) != m.end()){
					offset += m[iii+offset]-1;
					mm[iii+offset]=true;
				}
			}
					
			return imcssOne(pfstr,-1,mm,followAMap["original"],userInput);
		}
		else if (startOperands){
			if (pfstr.at(i) == '_'){
				originalMap[iidx] = currentOperator;
				iidx++; 
				currentOperator = "";
			}
			else {
				currentOperator += pfstr.at(i);
			}
		}
	}
	
	std::map<std::string,std::string> listMap;
	std::map<std::string,char> lastOpMap;
	
	int startLeft = 0;
	int endLeft = 0;
	std::map<int,std::string> operandMap;
	std::string lastInput = "";
	int oidx; int s00;
	for (i=0;i<pfstr.length();i++){
		if (pfstr.at(i) == '@'){
			break;
		}
		else if (pfstr.at(i) != '#'){
			std::string secondStr = "";
			std::string secondTtr = "";
			std::string secondStr0 = "";
			std::string secondTtr0 = "";
			std::string secondChild = "";
			int maxi = i-1;
			int rightStart = i;
			int rightEnd = -1;
			
			for (ii=0;ii<i;ii++){
				std::string s = "";
				std::string t = "";
				std::string s0 = "";
				std::string t0 = "";
				int rightStartT = i;
				int rightEndT = -1;
				for (iii=ii;iii<i;iii++){
					s += pfstr.at(iii);
					
					if (pfstr.at(iii) == '#'){
						s0 += pfstr.at(iii);
						t += operandMap[iii] + '_';
						oidx = std::stoi(operandMap[iii]);
						if (oidx < rightStartT){rightStartT = oidx;}
						if (oidx > rightEndT){rightEndT = oidx;}
						t0 += originalMap[oidx] + '_';
					}
					else {
						s00 = pfstr.at(iii);
						s0 += charCodeToString(s00);
					}
				}
				if (listMap.find(s + '@' + t) != listMap.end()){
					if (rightStartT < rightStart){rightStart = rightStartT;}
					if (rightEndT > rightEnd){rightEnd = rightEndT;}
					secondStr = s;
					secondTtr = t;
					secondStr0 = s0;
					secondTtr0 = t0;
					secondChild = s + '@' + t;
					maxi = ii;
					break;
				}
			}
			std::vector<std::string> firstStr;
			std::vector<std::string> firstTtr;
			std::vector<std::string> firstStr0;
			std::vector<std::string> firstTtr0;
			std::vector<std::string> firstChild;
			
			if (pfstr.at(i) != '-' && pfstr.at(i) != '/' && (pfstr.at(i) >= 0 || pfstr.at(i) <= -69 )){ // Is at least binary function
				
				for (ii=0;ii<maxi;ii++){
					std::string s = "";
					std::string t = "";
					std::string s0 = "";
					std::string t0 = "";
					int rightStartT = i;
					int rightEndT = -1;
					for (iii=ii;iii<maxi;iii++){
						s += pfstr.at(iii);
						
						if (pfstr.at(iii) == '#'){
							s0 += pfstr.at(iii);
							t += operandMap[iii] + '_';
							oidx = std::stoi(operandMap[iii]);
							if (oidx < rightStartT){rightStartT = oidx;}
							if (oidx > rightEndT){rightEndT = oidx;}
							t0 += originalMap[oidx] + '_';
						}
						else {
							s00 = pfstr.at(iii);
							s0 += charCodeToString(s00);
						}
					}
					if (listMap.find(s + '@' + t) != listMap.end()){
						if (rightStartT < rightStart){rightStart = rightStartT;}
						if (rightEndT > rightEnd){rightEnd = rightEndT;}
						firstStr.push_back(s);
						firstTtr.push_back(t);
						firstStr0.push_back(s0);
						firstTtr0.push_back(t0);
						firstChild.push_back(s + '@' + t);
						maxi = ii;
						break;
					}
				}
				if (pfstr.at(i) == -126){
					for (ii=0;ii<maxi;ii++){
						std::string s = "";
						std::string t = "";
						std::string s0 = "";
						std::string t0 = "";
						int rightStartT = i;
						int rightEndT = -1;
						for (iii=ii;iii<maxi;iii++){
							s += pfstr.at(iii);
							
							if (pfstr.at(iii) == '#'){
								s0 += pfstr.at(iii);
								t += operandMap[iii] + '_';
								oidx = std::stoi(operandMap[iii]);
								if (oidx < rightStartT){rightStartT = oidx;}
								if (oidx > rightEndT){rightEndT = oidx;}
								t0 += originalMap[oidx] + '_';
							}
							else {
								s00 = pfstr.at(iii);
								s0 += charCodeToString(s00);
							}
						}
						if (listMap.find(s + '@' + t) != listMap.end()){
							if (rightStartT < rightStart){rightStart = rightStartT;}
							if (rightEndT > rightEnd){rightEnd = rightEndT;}
							firstStr.push_back(s);
							firstTtr.push_back(t);
							firstStr0.push_back(s0);
							firstTtr0.push_back(t0);
							firstChild.push_back(s + '@' + t);
							maxi = ii;
							break;
						}
					}
				}
				
				
			}
			
			std::string fullStr =  "";
			std::string outputStr =  "";
			std::string userStr =  "";
			for (ii=0;ii<userInput.length();ii++){
				if (fullUserMap[ii]>= maxi && fullUserMap[ii]< i+1){
					userStr += userInput.at(ii);
				}
			}
			std::string outputID = std::to_string(maxi)+"-"+std::to_string(i+1)+"-"+std::to_string(rightStart)+"-"+std::to_string(rightEnd+1);
			if (firstTtr.size() == 2){
				fullStr += firstTtr[1];
				fullStr += firstTtr[0];
				outputStr += firstTtr0[1];
				outputStr += firstTtr0[0];
			}
			if (firstTtr.size() == 1){
				fullStr += firstTtr[0];
				outputStr += firstTtr0[0];
			}
			fullStr += secondTtr;
			outputStr += secondTtr0;
			
			fullStr = secondStr + pfstr.at(i) + '@' + fullStr;
			s00 = pfstr.at(i);
			outputStr = secondStr0 + charCodeToString(s00) + '@' + outputStr;
			if (firstStr.size() == 2){
				fullStr = firstStr[1]+firstStr[0] + fullStr;
				outputStr = firstStr0[1]+firstStr0[0] + outputStr;
			}
			if (firstStr.size() == 1){
				fullStr = firstStr[0] + fullStr;
				outputStr = firstStr0[0] + outputStr;
			}
			
			//std::string s = "<div data-id=\""+fullStr+"\">";
			std::string s = "";
			for (ii=0;ii<3;ii++){
				std::string child = secondChild;
				if (ii > firstChild.size()){
					break;
				}
				else if (ii==0 && firstChild.size() == 2){
					child = firstChild[1];
				}
				else if (ii==0 && firstChild.size() == 1){
					child = firstChild[0];
				}
				else if (ii==1 && firstChild.size() == 2){
					child = firstChild[0];
				}
				if (userStr.length() == 0){
					outputID = "";
				}
				s = imcssLogic(pfstr.at(i), s, ii, listMap[child],lastOpMap[child], userStr,outputID);
			}
			//s += "\n</div>";
			if (i == startNode){
				s = "\\boxed{"+s+"}";
			}
			else if (bMap.find(i) != bMap.end()){
				s = "\\{\\{"+s+"\\}\\}";
			}
			listMap[fullStr]=s;
			lastOpMap[fullStr]=pfstr.at(i);
			lastInput = s;
			
		}
		else {
			std::string userStr =  "";
			for (ii=0;ii<userInput.length();ii++){
				if (fullUserMap[ii]>= i && fullUserMap[ii]< i+1){
					userStr += userInput.at(ii);
				}
			}
			std::string outputID = std::to_string(i)+"-"+std::to_string(i+1)+"-"+std::to_string(idx)+"-"+std::to_string(idx+1);
			std::string s = "";
			if (userStr.length()> 0){
				s = "<div class=\"number\" id=\""+outputID+"\" data-original=\""+userStr+"\">"+originalMap[idx]+"</div>";
			}
			else {
				s = "<div class=\"number\">"+originalMap[idx]+"</div>";
			}
			
			if (i == startNode){
				s = "\\boxed{"+s+"}";
			}
			else if (bMap.find(i) != bMap.end()){
				s = "\\{\\{"+s+"\\}\\}";
			}
			listMap["#@" + std::to_string(idx) + "_"]=s;
			lastOpMap["#@" + std::to_string(idx) + "_"]='#';
			operandMap[i]=std::to_string(idx);
			lastInput = s;
			idx++;
		}
		
	}
	
	
	int inTag = 0;
	for (i=lastInput.length()-1;i>=0;i--){
		if (lastInput.at(i) == '<'){
			inTag++;
		}
		else if (lastInput.at(i) == '>'){
			inTag--;
		}
		else if (inTag == 0){
			if (lastInput.at(i) == ')'){
				lastInput.replace(i,1,parend);
			}
			else if (lastInput.at(i) == '('){
				lastInput.replace(i,1,parstart);
			}
			else if (lastInput.at(i) == ']'){
				lastInput.replace(i,1,bracketend);
			}
			else if (lastInput.at(i) == '['){
				lastInput.replace(i,1,bracketstart);
			}
			else if (lastInput.at(i) == '\\'){
				std::string greek = "";
				for (ii=i;ii<i+8 && ii < lastInput.length();ii++){
					greek += lastInput.at(ii);
					if (greekHTML.find(greek) != greekHTML.end()){
						lastInput.replace(i,ii-i+1,greekHTML[greek]);
						break;
					}
				}
			
			}
		}
	}
	
	std::string outFull = "";
	for (i=0;i<pfstr.length();i++){
		if (pfstr.at(i) == '@'){
			outFull += pfstr.substr(i,pfstr.length()-i);
			break;
		}
		else if (pfstr.at(i) != '#'){
			s00 = pfstr.at(i);
			outFull += charCodeToString(s00);
		}
		else {
			outFull += '#';
		}
	}
	lastInput = "<div class=\"imcss\" data-user=\""+userInput+"\" data-original=\""+outFull+"\">" +lastInput+ "\n</div>";
	//std::cout << lastInput << "\n";
	return lastInput;


}

std::string imcssOne(std::string input, std::string followA, std::string userInput){
	return imcssOne(input,-1,{}, followA, userInput);
}



