
std::string opstart = "<div class=\"operator\">";
std::string imcssLogic(char c, std::string s, int ii, std::string child, char lastOp, std::string outputStr){
	switch (c){
		case '^': {
			if (ii > 0){
				//s += "^{";
				//s += child+"}";
				s += "<div class=\"number noflow\">";
				s += child+"\n</div>\n</div>";
			}
			else {
				if (prec[lastOp] < 100){
					//s += "("+child+")";
					s += "<div class=\"power\" data-original=\""+outputStr+"\">\n<div class=\"parentheses\">"+child+"\n</div>";
				}
				else {
					//s += child;
					s += "<div class=\"power\" data-original=\""+outputStr+"\">\n<div class=\"number\">"+child+"\n</div>";
				}
			}
			break;
		}
		case -69: {//Derivative
			if (ii > 0){
				s += child+"]";
			}
			else {
				s += "\\frac{d}{d"+child+"}[";
			}
			break;

		}
		case -85: {//Integral
			if (ii > 0){
				s.replace(5,0,child+" \\text{d");
			}
			else {
				s += "\\int "+child+"}";
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
		case -34: //absolute value
			//s += "|"+child+"|";
			s += "<div class=\"abs\" data-original=\""+outputStr+"\">"+child+"\n</div>";
			break;
		case -64:
			s += "\\sin("+child+")";
			break;
		case -63:
			s += "\\cos("+child+")";
			break;
		case -62:
			s += "\\tan("+child+")";
			break;
		case -61:
			s += "\\csc("+child+")";
			break;
		case -60:
			s += "\\sec("+child+")";
			break;
		case -59:
			s += "\\cot("+child+")";
			break;
		case -32:
			s += "\\sin^{-1}("+child+")";
			break;
		case -31:
			s += "\\cos^{-1}("+child+")";
			break;
		case -30:
			s += "\\tan^{-1}("+child+")";
			break;
		case -29:
			s += "\\csc^{-1}("+child+")";
			break;
		case -28:
			s += "\\sec^{-1}("+child+")";
			break;
		case -27:
			s += "\\cot^{-1}("+child+")";
			break;
		case -16:
			s += "\\text{sinh}("+child+")";
			break;
		case -15:
			s += "\\text{cosh}("+child+")";
			break;
		case -14:
			s += "\\text{tanh}("+child+")";
			break;
		case -13:
			s += "\\text{csch}("+child+")";
			break;
		case -12:
			s += "\\text{sech}("+child+")";
			break;
		case -11:
			s += "\\text{coth}("+child+")";
			break;
		case -67:
			//s += "\\sqrt{"+child+"}";
			s += "<div class=\"root\" data-original=\""+outputStr+"\"><svg viewBox=\"0 0 50 100\" width=\"50\" height=\"100\"><path d=\"M0 60 15 60 25 100 50 0\" fill=\"none\" stroke=\"black\" stroke-width=\"5\"/></svg><div class=\"number margin\">"+child+"\n</div>\n</div>";
			break;
		case -84: {
			if (ii > 0){
				//s += child+"}";
				s += "<div class=\"number\">"+child+"\n</div>\n</div>";
			}
			else {
				//s += "\\sqrt["+child+"]{";
				s += "<div class=\"root\" data-original=\""+outputStr+"\"><svg viewBox=\"0 0 50 100\" width=\"50\" height=\"100\"><path d=\"M0 60 15 60 25 100 50 0\" fill=\"none\" stroke=\"black\" stroke-width=\"5\"/></svg><div class=\"number margin\">"+child+"\n</div>";
			}
			break;

		}
		case -105: {
			if (ii > 0){
				s += "\\pluseq "+child;
			}
			else {
				s += child;
			}
			break;
		}
		case -106: {
			if (ii > 0){
				s += "\\minuseq"+child;
			}
			else {
				s += child;
			}
			break;
		}
		case -125: {
			if (ii > 0){
				s += child+")";
			}
			else {
				s += "\\text{"+child+"}(";
			}
			break;
		}
		case -126: {
			if (ii > 1){
				s += child+")";
			}
			else if (ii == 1){
				s += child+",";
			}
			else {
				s += "\\text{"+child+"}(";
			}
			break;
		}
		case -93: {
			if (ii > 0){
				if (prec[lastOp] < 100){
					s += "("+child+")";
				}
				else {
					s += child;
				}
	
			}
			else {
				if (child == "e"){
					s += "\\ln ";
				}
				else {
					s += "\\log_{"+child+"} ";
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
				s += "<div class=\"number\">"+child+"\n</div>\n</div>";
			}
			else {
				//s += child+"\\neq ";
				s += "<div class=\"comparison\"><div class=\"number\">"+child+"\n</div><div class=\"number\">&ne;\n</div>";

			}
			break;
		}
		case '[': {
			if (ii > 0){
				//s += child;
				s += "<div class=\"number\">"+child+"\n</div>\n</div>";
			}
			else {
				//s += child + "\\leq ";
				s += "<div class=\"comparison\"><div class=\"number\">"+child+"\n</div><div class=\"number\">&lte;\n</div>";
			}
			break;
		}
		case ']': {
			if (ii > 0){
				//s += child;
				s += "<div class=\"number\">"+child+"\n</div>\n</div>";
			}
			else {
				//s += child + "\\geq ";
				s += "<div class=\"comparison\"><div class=\"number\">"+child+"\n</div><div class=\"number\">&gte;\n</div>";
			}
			break;
		}
		case '<': {
			if (ii > 0){
				//s += child;
				s += "<div class=\"number\">"+child+"\n</div>\n</div>";
			}
			else {
				//s += child+"< ";
				s += "<div class=\"comparison\"><div class=\"number\">"+child+"\n</div><div class=\"number\">&lt;\n</div>";
			}
			break;
		}
		case '>': {
			if (ii > 0){
				//s += child;
				s += "<div class=\"number\">"+child+"\n</div>\n</div>";
			}
			else {
				//s += child+"> ";
				s += "<div class=\"comparison\"><div class=\"number\">"+child+"\n</div><div class=\"number\">&gt;\n</div>";
			}
			break;
		}
		case '=': {
			if (ii > 0){
				//s += child;
				s += "<div class=\"number\">"+child+"\n</div>\n</div>";
			}
			else {
				//s += child+"= ";
				s += "<div class=\"comparison\"><div class=\"number\">"+child+"\n</div><div class=\"number\">=\n</div>";
			}
			break;
		}
		case -79: {
			if (ii>0){
				if (prec[-79] > prec[lastOp]){
					s += "\\pm ("+child+")";
				}
				else {
					s += "\\pm"+child;
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
				s += "-<div class=\"parentheses\">"+child+"\n</div>";
			}
			else {
				s += "-"+child;
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
					s += "<div class=\"parentheses\">"+child+"\n</div>";
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
							s += "<div class=\"parentheses\">"+child+"\n</div>";
						}
						else {
							s += "\\cdot ("+child+")";//want to move this into numerator somehow
						}
					
					}
					else if (c == '&'){
						s += " AND ("+child+")";
					}
					else if (c == '|'){
						s += " OR ("+child+")";
					}
					else {
						s += c+"("+child+")";
					}
				}
				else {
					if (lastOp == '-'){
						//s += child;
						s += "<div class=\"number\">"+child+"\n</div>";
					}
					else {
						//s += "("+child+")";
						s += "<div class=\"parentheses\">"+child+"\n</div>";
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
						s += "\\text{ AND }("+child+")";
					}
					else if (c == '|'){
						s += "\\text{ OR }("+child+")";
					}
					else {
						s += "<div class=\"operation\">";
						s += c+"\n</div>";
						s += "<div class=\"parentheses\">"+child+"\n</div>";
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
						s += "<div class=\"parentheses\">"+child+"\n</div>";
					}
				}
			}
			else {
				if (ii > 0){
					if (c == '*'){
						//TODO: deal with fraction in s or child
						if (s == "-1"){
							s = "-"+child;
						}
						else if (s.length()>0 && (s.at(s.length()-1) >= '0' && s.at(s.length()-1) <= '9')){
							if (child.length()>0 && (child.at(0) >= '0' && child.at(0) <= '9')){
								//digit followed by digit
								s += "\\cdot "+child;
							}
							else{
								//digit followed by not a digit
								//s += child;
								s += "<div class=\"number\">"+child+"\n</div>";
							}
						}
						else {
							s += "\\cdot "+child;
						}
					}
					else if (c == '&'){
						s += "\\text{ AND }"+child;
					}
					else if (c == '|'){
						s += "\\text{ OR }"+child;
					}
					else {
						//s += c+child;
						s += "<div class=\"number\">";
						s += c;
						s += "</div><div class=\"number\">"+child+"\n</div>";
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
					s = imcssLogic(lastOpMap[input[i*3]], s, ii, imcssMap[child],lastOpMap[child], outputStr);
					
					
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

std::string imcssOne(std::string input,int startNode,std::map<int,bool> bMap) {

	int i; int ii; int iii; int idx = 0;
	bool startOperands = false;
	std::string currentOperator = "";
	std::map<int,std::string> originalMap;
	int iidx = 0;
	std::string pfstr = input;
	int startAt =0;
	for (i=0;i<pfstr.length();i++){
		if (pfstr.at(i) == '@'){
			startOperands = true;
			startAt = i;
		}
		else if (pfstr.at(i) == '('){
			std::map<int,int> m = removeParList({},pfstr);
			pfstr = removeParOne(pfstr);
			
			int offset = 0;
			std::map<int,bool> mm;
			for (iii=0;iii<startAt;iii++){
				if (m.find(iii+offset) != m.end()){
					offset += m[iii+offset]-1;
					mm[iii+offset]=true;
				}
			}
					
			return imcssOne(pfstr,-1,mm);
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
	
	std::map<int,std::string> operandMap;
	std::string lastInput = "";
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
			
			for (ii=0;ii<i;ii++){
				std::string s = "";
				std::string t = "";
				std::string s0 = "";
				std::string t0 = "";
				for (iii=ii;iii<i;iii++){
					s += pfstr.at(iii);
					
					if (pfstr.at(iii) == '#'){
						s0 += pfstr.at(iii);
						t += operandMap[iii] + '_';
						t0 += originalMap[std::stoi(operandMap[iii])] + '_';
					}
					else {
						s0 += std::to_string(pfstr.at(iii) - '0');
					}
				}
				if (listMap.find(s + '@' + t) != listMap.end()){
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
					for (iii=ii;iii<maxi;iii++){
						s += pfstr.at(iii);
						
						if (pfstr.at(iii) == '#'){
							s0 += pfstr.at(iii);
							t += operandMap[iii] + '_';
							t0 += originalMap[std::stoi(operandMap[iii])] + '_';
						}
						else {
							s0 += std::to_string(pfstr.at(iii) - '0');
						}
					}
					if (listMap.find(s + '@' + t) != listMap.end()){
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
						for (iii=ii;iii<maxi;iii++){
							s += pfstr.at(iii);
							
							if (pfstr.at(iii) == '#'){
								s0 += pfstr.at(iii);
								t += operandMap[iii] + '_';
								t0 += originalMap[std::stoi(operandMap[iii])] + '_';
							}
							else {
								s0 += std::to_string(pfstr.at(iii) - '0');
							}
						}
						if (listMap.find(s + '@' + t) != listMap.end()){
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
			outputStr = secondStr0 + pfstr.at(i) + '@' + outputStr;
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
				s = imcssLogic(pfstr.at(i), s, ii, listMap[child],lastOpMap[child], outputStr);
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
			std::string s = "<div class=\"number\">"+originalMap[idx]+"</div>";
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
	
	//std::cout << lastInput << "\n";
	return lastInput;


}

std::string imcssOne(std::string input){
	return imcssOne(input,-1,{});
}



