std::string arrayToString(int n, char input[]) { 
    int i; 
    std::string s = ""; 
    for (i = 0; i < n; i++) { 
        s = s + input[i]; 
    } 
    return s; 
}

std::vector<std::string> makePostVector(char infixexpr[]) {
	int i;
	
	//std::string displayinp = "";
	//for (i=0;infixexpr[i];i++){
	//	if (infixexpr[i]<0){displayinp += "?";}
	//	else {displayinp += infixexpr[i];}
	//}
	//string_log(displayinp.c_str());
	followAMap["expstr"] = "";
	std::string intstr = "";
	std::string expstr = "";
	char topToken;
	std::vector<std::string> postfixList;
	int pfidx =0;
	std::vector<char> opStack;
	int osidx = 0;
	std::vector<std::string> tokenList;
	int idx = 0;
	int len=0;
	
	for (i = 0; infixexpr[i]; i++) 
    {
    	len = 2*i+1;
    }
	char temptoken[len];
	tokenList.resize(len);
	postfixList.resize(len);
	opStack.resize(len);
	
	
	std::vector<char> opStackFollow;
	opStackFollow.resize(len);
	char temptokenFollow[len];
	std::vector<std::string> tokenListFollow;
	std::vector<std::string> postfixListFollow;
	tokenListFollow.resize(len);
	postfixListFollow.resize(len);
	char topTokenFollow;
	
	int iidx = 0;
	
	if (followAMap.find("original") == followAMap.end()){
		followAMap["original"]="";
	}
	int sz = followAMap["original"].length();
	for (i = 0; infixexpr[i]; i++) {
		if (i >= sz){
			followAMap["original"]+='0';
		}
	}

	for (i = 0; infixexpr[i]; i++) {
		char ie = infixexpr[i];
		char aie = followAMap["original"].at(i);
		if (prec.find(ie) == prec.end()){
			if (iidx > 0){
				if (temptoken[iidx-1] >= '0' && temptoken[iidx-1] <= '9'){
					if (ie >= 'a' && ie <= 'z'){//Number followed by ( is multiplication
						tokenList[idx] = arrayToString(iidx,temptoken);
						tokenListFollow[idx] = arrayToString(iidx,temptokenFollow);
						idx++;
						std::string s(1,'*');
						tokenList[idx] = s;
						tokenListFollow[idx] = "0";
						idx++;
						
						temptoken[0] = '\0';
						temptokenFollow[0] = '\0';
						iidx=0;
					}
				}
			}
			temptoken[iidx] = ie;
			temptoken[iidx+1] = '\0';
			temptokenFollow[iidx] = aie;
			temptokenFollow[iidx+1] = '\0';
			iidx++;
		}
		else{
			if (iidx != 0){
				if (temptoken[iidx-1] >= '0' && temptoken[iidx-1] <= '9'){
					if (ie == '('){//Number followed by ( is multiplication
						tokenList[idx] = arrayToString(iidx,temptoken);
						tokenListFollow[idx] = arrayToString(iidx,temptokenFollow);
						idx++;
						std::string s(1,'*');
						tokenList[idx] = s;
						tokenListFollow[idx] = "0";
						idx++;
					}
					else {
						tokenList[idx] = arrayToString(iidx,temptoken);
						tokenListFollow[idx] = arrayToString(iidx,temptokenFollow);
						idx++;
					}
				}
				else if ((temptoken[iidx-1] >= 'a' && temptoken[iidx-1] <= 'z') || (temptoken[iidx-1] >= 'A' && temptoken[iidx-1] <= 'Z')){
					if (ie == '('){//Letter followed by ( is function
						tokenList[idx] = arrayToString(iidx,temptoken);
						tokenListFollow[idx] = arrayToString(iidx,temptokenFollow);
						//string_log(tokenList[idx].c_str());
						dependentFunctions.push_back(tokenList[idx]);
						idx++;
						int iie;
						int openPar = 0;
						int commas = 0;
						for (iie = i; infixexpr[iie]; iie++) {
							if (infixexpr[iie] == '('){
								openPar++;
							}
							else if (infixexpr[iie] == ')'){
								openPar--;
							}
							else if (openPar == 1 && infixexpr[iie] == ',' && infixexpr[iie-1] == ','){
								infixexpr[iie-1] = ')';
								infixexpr[iie] = '(';
								followAMap["original"][iie-1] = '0';
								followAMap["original"][iie] = '0';
								commas++;
							}
							if (openPar == 0){
								break;
							}
						}
						
						if (commas>0){
							std::string s(1,-126);
							tokenList[idx] = s;
							tokenListFollow[idx] = "0";
						}
						else {
							std::string s(1,-125);
							tokenList[idx] = s;
							tokenListFollow[idx] = "0";
						}
						idx++;
					}
					else {
						tokenList[idx] = arrayToString(iidx,temptoken);
						tokenListFollow[idx] = arrayToString(iidx,temptokenFollow);
						idx++;
					}
				}
				
			}
			std::string s(1,ie);
			tokenList[idx] = s;
			tokenListFollow[idx] = aie;
			idx++;
			temptoken[0] = '\0';
			temptokenFollow[0] = '\0';
			iidx=0;
		}
	}
	if (iidx != 0){
		tokenList[idx] = arrayToString(iidx,temptoken);
		tokenListFollow[idx] = arrayToString(iidx,temptokenFollow);
		idx++;
	}
	
	tokenList.resize(idx);
	tokenListFollow.resize(idx);
	

	
	bool previousOperand = false;
	int p;
	for (i=0;i<idx;i++){
		std::string token = tokenList[i];
		std::string tokenFollow = tokenListFollow[i];
		char firstChar = token.at(0);
		char firstCharFollow = tokenFollow.at(0);
		
		if (firstChar == '('){
			opStack[osidx] = firstChar;
			opStackFollow[osidx] = firstCharFollow;
			osidx++;
			previousOperand = false;
		}
		else if (firstChar == ')'){
			topToken = opStack[osidx-1];
			topTokenFollow = opStackFollow[osidx-1];
			osidx--;
			
			while (topToken != '('){
				
				osidx--;
				std::string s(1,topToken);
				postfixList[pfidx] = s;
				postfixListFollow[pfidx] = topTokenFollow;
				pfidx++;
				topToken = opStack[osidx];
				topTokenFollow = opStackFollow[osidx];
				
			}
			previousOperand = true;
			
		}
		else if (firstChar < 0 || firstChar == '^' || firstChar == '*' || firstChar == '+' || firstChar == '/' || firstChar == '-' || firstChar == '>' || firstChar == '<' || firstChar == '=' || firstChar == '!' || firstChar == '[' || firstChar == ']' || firstChar == '&' || firstChar == '|' || firstChar == '%') {
			p = prec[firstChar];
			if (firstChar == '-' && !previousOperand){
				p = prec['~'];
			}
			if (firstChar == '/' && !previousOperand){
				p = prec['`'];
			}
			while ((osidx > 0) && (prec[opStack[osidx-1]] >= p)){
				topToken = opStack[osidx-1];
				topTokenFollow = opStackFollow[osidx-1];
				osidx--;
				std::string s(1,topToken);
				postfixList[pfidx] = s;
				postfixListFollow[pfidx] = topTokenFollow;
				pfidx++;
			}
			
			opStack[osidx] = firstChar;
			opStackFollow[osidx] = firstCharFollow;
			if (firstChar == '-' && !previousOperand){
				opStack[osidx] = '~';
				opStackFollow[osidx] = '0';
			}
			if (firstChar == '/' && !previousOperand){
				opStack[osidx] = '`';
				opStackFollow[osidx] = '0';
			}
			osidx++;
			previousOperand = false;
		}
		else {
			postfixList[pfidx] = token;
			postfixListFollow[pfidx] = tokenFollow;
			pfidx++;
			previousOperand = true;
		}
	}
	while (osidx > 0){
		topToken = opStack[osidx-1];
		topTokenFollow = opStackFollow[osidx-1];
		osidx--;
		std::string s(1,topToken);
		postfixList[pfidx] = s;
		postfixListFollow[pfidx] = topTokenFollow;
		pfidx++;
	}
	

	for (i=0;i<pfidx;i++){
		
		std::string ci = postfixList[i];
		std::string ciFollow = postfixListFollow[i];
		char firstChar = ci.at(0);
		char firstCharFollow = ciFollow.at(0);
		if (firstChar == '~'){
			//expstr += "-";
			expstr += "-";
			followAMap["expstr"] += firstCharFollow;
		}
		else if (firstChar == '-'){
			//expstr += "-";
			expstr += "-+";
			followAMap["expstr"] += firstCharFollow;
			followAMap["expstr"] += firstCharFollow;
		}
		else if (firstChar == '/'){
			//expstr += "-";
			expstr += "/*";
			followAMap["expstr"] += firstCharFollow;
			followAMap["expstr"] += firstCharFollow;
		}
		else if (firstChar == '`'){
			//expstr += "-";
			expstr += "/";
			followAMap["expstr"] += firstCharFollow;
		}
		else if (firstChar < 0 || firstChar == '^' || firstChar == '*' || firstChar == '+' || firstChar == '>' || firstChar == '<' || firstChar == '=' || firstChar == '!' || firstChar == '[' || firstChar == ']' || firstChar == '&' || firstChar == '|' || firstChar == '%') {
			expstr += ci;
			followAMap["expstr"] += ciFollow;
		}
		else {
			
			
			bool addHash = true;
			if (ci == "alpha"){
				intstr += "\\alpha";
			}
			else if (ci == "beta"){
				intstr += "\\beta";
			}
			else if (ci == "delta"){
				intstr += "\\delta";
			}
			else if (ci == "Delta"){
				intstr += "\\Delta";
			}
			else if (ci == "theta"){
				intstr += "\\theta";
			}
			else if (ci == "mu"){
				intstr += "\\mu";
			}
			else if (ci == "sigma"){
				intstr += "\\sigma";
			}
			else if (ci == "pi" || ci == "Pi" || ci == "PI"){
				intstr += "\\pi";
			}
			else if (ci.at(0) == '\\'){
				intstr += ci;
			}
			else if (ci.at(ci.length()-1) <= 'z' && ci.at(ci.length()-1) >= 'A'){
				if (ci.length() > 2){
					if (ci.at(ci.length()-2) == 'p' || ci.at(ci.length()-2) == 'P'){
						if (ci.at(ci.length()-1) == 'I' || ci.at(ci.length()-1) == 'i'){
							if (ci.at(ci.length()-3) == '\\'){
								intstr += ci.substr(0,ci.length()-3) + "_\\pi";
								expstr += "##*";
								followAMap["expstr"] += ciFollow[0];
								followAMap["expstr"] += ciFollow[ci.length()-3];
								followAMap["expstr"] += ciFollow[ci.length()-3];
							}
							else {
								intstr += ci.substr(0,ci.length()-2) + "_\\pi";
								expstr += "##*";
								followAMap["expstr"] += ciFollow[0];
								followAMap["expstr"] += ciFollow[ci.length()-2];
								followAMap["expstr"] += ciFollow[ci.length()-2];
							}
							addHash = false;
						}
						else {
							intstr += ci;
						}
					}
					else {
						intstr += ci;
					}
				}
				else {
					intstr += ci;
				}
			}
			else {
				intstr += ci;
			}
			intstr += "_";
			if (addHash){ expstr += "#"; followAMap["expstr"] += ciFollow[0]; }
			
		}

	}
	//std::string displayexp = "";
	//for (i=0;i<expstr.length();i++){
	//	if (expstr.at(i)<0){displayexp += "?";}
	//	else {displayexp += expstr.at(i);}
	//}
	//string_log(displayexp.c_str());
	//string_log(intstr.c_str());
	return {expstr,intstr};


}

std::string makePost(char infixexpr[]) {
	std::vector<std::string> v = makePostVector(infixexpr);
	
	std::string retstr = v[0]+ "@" + v[1];
	return retstr;


}

std::string replaceFunctions(std::string input_str){

	if (followAMap.find("original") == followAMap.end()){
		followAMap["original"]="";
	}
	int sz = followAMap["original"].length();
	int szi;
	for (szi = 0; szi<input_str.length(); szi++) {
		if (szi >= sz){
			followAMap["original"]+='0';
		}
	}
	
	std::map<std::string,std::string> replacements2;
	std::map<std::string,std::string> replacements3;
	std::map<std::string,std::string> replacements4;
	std::map<std::string,std::string> replacements5;
	std::map<std::string,std::string> replacements6;
	std::map<std::string,std::string> replacements7;
	std::map<std::string,std::string> replacements8;
	
	std::map<std::string,std::string> rawrep6;
	std::map<std::string,std::string> rawrep5;
	std::map<std::string,std::string> rawrep4;
	std::map<std::string,std::string> rawrep3;
	std::map<std::string,std::string> rawrep2;
	
	std::map<std::string,std::string> query7;
	std::map<std::string,std::string> query6;
	std::map<std::string,std::string> query5;
	std::map<std::string,std::string> query4;
	std::map<std::string,std::string> query3;
	std::map<std::string,std::string> query2;
	
	char ddx{-69};
	char idx{-85};
	char sub{-102};
	char solve{-89};
	std::string solveStr = "";
	solveStr += solve;
	int i; int ii;
	replacements3["ddx"]="x";
	replacements3["ddx"]+=ddx;

	query3["dd?"]="";
	query3["dd?"]+=ddx;
	query3["der"]="";
	query3["der"]+=ddx;
	replacements3["idx"]="x";
	replacements3["idx"]+=idx;

	query3["id?"]="";
	query3["id?"]+=idx;
	query3["int"]="";
	query3["int"]+=idx;
	query3["sub"]="";
	query3["sub"]+=sub;
	
	std::vector<std::string> trigFunctions;
	trigFunctions.push_back("sin");
	trigFunctions.push_back("cos");
	trigFunctions.push_back("tan");
	trigFunctions.push_back("csc");
	trigFunctions.push_back("sec");
	trigFunctions.push_back("cot");

	for (i=0;i<6;i++){
		char c{-64};
		c += i;
		char ci{-32};
		ci += i;
		char ch{-16};
		ch += i;
		replacements3[trigFunctions[i]]="";
		replacements3[trigFunctions[i]]+=c;
		replacements4[trigFunctions[i]+"h"]="";
		replacements4[trigFunctions[i]+"h"]+=ch;
		replacements6["arc"+trigFunctions[i]]="";
		replacements6["arc"+trigFunctions[i]]+=ci;
		replacements6[trigFunctions[i]+"^-1"]="";
		replacements6[trigFunctions[i]+"^-1"]+=ci;
		replacements8[trigFunctions[i]+"^(-1)"]="";
		replacements8[trigFunctions[i]+"^(-1)"]+=ci;
		replacements8[trigFunctions[i]+"^{-1}"]="";
		replacements8[trigFunctions[i]+"^{-1}"]+=ci;
		replacements5[trigFunctions[i]+"-1"]="";
		replacements5[trigFunctions[i]+"-1"]+=ci;
		query4[trigFunctions[i]+"^"]="";
		query4[trigFunctions[i]+"^"]+=c;
	}
	
	
	char sqrt{-67};
	char root{-84};
	replacements4["sqrt"]="";
	replacements4["sqrt"]+=sqrt;
	replacements4["root"]="";
	replacements4["root"]+=sqrt;
	//TODO: add nth roots
	
	
	
	char log{-93};
	replacements3["log"]="e";
	replacements3["log"]+=log;
	replacements2["ln"]="e";
	replacements2["ln"]+=log;
	query3["log"]="";
	query3["log"]+=log;
	query2["ln"]="";
	query2["ln"]+=log;
	//TODO: add other bases
	
	char abs{-34};
	replacements3["abs"]="";
	replacements3["abs"]+=abs;
	
	char element{-95};
	query4[" in "]="";
	query4[" in "]+=element;
	
	
	query5["slope"]="slope";
	query6["slopey"]="slopey";
	
	rawrep5[" AND "]="&";
	rawrep5[" And "]="&";
	rawrep5[" and "]="&";
	rawrep4[" OR "]="|";
	rawrep4[" Or "]="|";
	rawrep4[" or "]="|";
	char plusequal{-105};
	char minusequal{-106};
	char plusminus{-79};
	std::string pestr(1,plusequal);
	std::string mestr(1,minusequal);
	std::string pmstr(1,plusminus);
	rawrep3["+= "]= pestr;
	rawrep3["-= "]= mestr;
	rawrep3["== "]= "= ";
	rawrep3["!= "]= "!";
	rawrep3["<= "]= "[";
	rawrep3[">= "]= "]";
	rawrep3["\\pm"]= pmstr;
	rawrep2["+-"]= "-";
	char factorial{-41};
	std::string factorialstr(1,factorial);
	rawrep2["!!"]= factorialstr;
	
	char maxc{-101};
	std::string maxstr(1,maxc);
	rawrep5[" max "]= maxstr;
	char minc{-100};
	std::string minstr(1,minc);
	rawrep5[" min "]= minstr;
	char permc{-98};
	std::string permstr(1,permc);
	rawrep6[" perm "]= permstr;
	char combc{-97};
	std::string combstr(1,combc);
	rawrep6[" comb "]= combstr;
	char gcdc{-99};
	std::string gcdstr(1,gcdc);
	rawrep5[" gcd "]= gcdstr;
	rawrep5[" mod "]= "%";
	
	std::string twoChars = "..";
	std::string threeChars = "...";
	std::string fourChars = "....";
	std::string fiveChars = ".....";
	std::string sixChars = "......";
	std::string sevenChars = ".......";
	std::string eightChars = "........";
	
	
	for (i=0;i<input_str.length()-1;i++){
		twoChars.replace(0,1,"");
		twoChars += input_str.at(i);
		threeChars.replace(0,1,"");
		threeChars += input_str.at(i);
		fourChars.replace(0,1,"");
		fourChars += input_str.at(i);
		fiveChars.replace(0,1,"");
		fiveChars += input_str.at(i);
		sixChars.replace(0,1,"");
		sixChars += input_str.at(i);
		sevenChars.replace(0,1,"");
		sevenChars += input_str.at(i);
		eightChars.replace(0,1,"");
		eightChars += input_str.at(i);
		
		
		if (query4.find(fourChars) != query4.end() && query4[fourChars].at(0) == element){

			input_str.replace(i-3,4,query4[fourChars]);
			std::string sNew = std::string(query4[fourChars].length(),followAMap["original"].at(i-3));
			followAMap["original"].replace(i-3,4,sNew);
			fourChars = "....";
			i += -3;
			//std::cout << i << " : " << input_str << " char: " << element << '\n';
			
		}
		else if (rawrep6.find(sixChars) != rawrep6.end()){
			input_str.replace(i-5,6,rawrep6[sixChars]);
			std::string sNew = std::string(rawrep6[sixChars].length(),followAMap["original"].at(i-5));
			followAMap["original"].replace(i-5,6,sNew);
			sixChars = "......";
			i+= rawrep6[sixChars].length() - 6;
		}
		else if (rawrep5.find(fiveChars) != rawrep5.end()){
			input_str.replace(i-4,5,rawrep5[fiveChars]);
			std::string sNew = std::string(rawrep5[fiveChars].length(),followAMap["original"].at(i-4));
			followAMap["original"].replace(i-4,5,sNew);
			fiveChars = ".....";
			i+= rawrep5[fiveChars].length() - 5;
		}
		else if (rawrep4.find(fourChars) != rawrep4.end()){
			input_str.replace(i-3,4,rawrep4[fourChars]);
			std::string sNew = std::string(rawrep4[fourChars].length(),followAMap["original"].at(i-3));
			followAMap["original"].replace(i-3,4,sNew);
			fourChars = "....";
			i+= rawrep4[fourChars].length() - 4;
		}
		else if (rawrep3.find(threeChars) != rawrep3.end()){
			input_str.replace(i-2,3,rawrep3[threeChars]);
			std::string sNew = std::string(rawrep3[threeChars].length(),followAMap["original"].at(i-2));
			followAMap["original"].replace(i-2,3,sNew);
			threeChars = "...";
			i+= rawrep3[threeChars].length() - 3;
		}
		else if (rawrep2.find(twoChars) != rawrep2.end()){
			input_str.replace(i-1,2,rawrep2[twoChars]);
			std::string sNew = std::string(rawrep2[twoChars].length(),followAMap["original"].at(i-1));
			followAMap["original"].replace(i-1,2,sNew);
			twoChars = "..";
			i+= rawrep2[twoChars].length() - 2;
		}
		else if (input_str.at(i+1) == '('){
			//std::cout << i << " : " << input_str << " 3chars: " << threeChars << '\n';
			if (replacements8.find(eightChars) != replacements8.end()){
				input_str.replace(i-7,8,replacements8[eightChars]);
				std::string sNew = std::string(replacements8[eightChars].length(),followAMap["original"].at(i-7));
				followAMap["original"].replace(i-7,8,sNew);
				eightChars = "........";
				i+= replacements8[eightChars].length() - 8;
			}
			else if (replacements7.find(sevenChars) != replacements7.end()){
				input_str.replace(i-6,7,replacements7[sevenChars]);
				std::string sNew = std::string(replacements7[sevenChars].length(),followAMap["original"].at(i-6));
				followAMap["original"].replace(i-6,7,sNew);
				sevenChars = ".......";
				i+= replacements7[sevenChars].length() - 7;
			}
			else if (replacements6.find(sixChars) != replacements6.end()){
				input_str.replace(i-5,6,replacements6[sixChars]);
				std::string sNew = std::string(replacements6[sixChars].length(),followAMap["original"].at(i-5));
				followAMap["original"].replace(i-5,6,sNew);
				sixChars = "......";
				i+= replacements6[sixChars].length() - 6;
			}
			else if (replacements5.find(fiveChars) != replacements5.end()){
				input_str.replace(i-4,5,replacements5[fiveChars]);
				std::string sNew = std::string(replacements5[fiveChars].length(),followAMap["original"].at(i-4));
				followAMap["original"].replace(i-4,5,sNew);
				fiveChars = ".....";
				i+= replacements5[fiveChars].length() - 5;
			}
			else if (replacements4.find(fourChars) != replacements4.end()){
				input_str.replace(i-3,4,replacements4[fourChars]);
				std::string sNew = std::string(replacements4[fourChars].length(),followAMap["original"].at(i-3));
				followAMap["original"].replace(i-3,4,sNew);
				fourChars = "....";
				i+= replacements4[fourChars].length() - 4;
			}
			else if (replacements3.find(threeChars) != replacements3.end()){
				input_str.replace(i-2,3,replacements3[threeChars]);
				std::string sNew = std::string(replacements3[threeChars].length(),followAMap["original"].at(i-2));
				followAMap["original"].replace(i-2,3,sNew);
				threeChars = "...";
				i+= replacements3[threeChars].length() - 3;
			}
			else if (replacements2.find(twoChars) != replacements2.end()){
				input_str.replace(i-1,2,replacements2[twoChars]);
				std::string sNew = std::string(replacements2[twoChars].length(),followAMap["original"].at(i-1));
				followAMap["original"].replace(i-1,2,sNew);
				twoChars = "..";
				i+= replacements2[twoChars].length() - 2;
			}
			else if (query6.find(sixChars) != query6.end()){
				if (query6[sixChars] == "slopey"){ 
					//std::cout << i << " : " << input_str << " 3chars: " << threeChars << '\n';
					std::string inside = "";
					std::string var = "";
					int openPar = 0;
					bool isVar = false;
					int repLen = 6;
					for (ii=i+1;ii<input_str.length();ii++){
						repLen++;
						if (input_str.at(ii) == '('){
							openPar++;
						}
						else if (input_str.at(ii) == ')'){
							openPar--;
						}
						else if (input_str.at(ii) == ';'){
							isVar = true;
						}
						else if (isVar){
							var += input_str.at(ii);
						}
						else {
							inside += input_str.at(ii);
						}
				
						if (openPar == 0){
							break;
						}
					}
					input_str.replace(i-5,repLen, "slopey"+solveStr + "("+inside+")");
					std::string sNew = std::string(8+solveStr.length()+inside.length(),followAMap["original"].at(i-5));
					followAMap["original"].replace(i-5,repLen,sNew);
					sixChars = "......";
					i += -6;
					//std::cout << i << " : " << input_str << " 3chars: " << threeChars << '\n';
				}
				
			}
			else if (query5.find(fiveChars) != query5.end()){
				if (query5[fiveChars] == "slope"){ 
					//std::cout << i << " : " << input_str << " 3chars: " << threeChars << '\n';
					std::string inside = "";
					std::string var = "";
					int openPar = 0;
					bool isVar = false;
					int repLen = 5;
					for (ii=i+1;ii<input_str.length();ii++){
						repLen++;
						if (input_str.at(ii) == '('){
							openPar++;
						}
						else if (input_str.at(ii) == ')'){
							openPar--;
						}
						else if (input_str.at(ii) == ';'){
							isVar = true;
						}
						else if (isVar){
							var += input_str.at(ii);
						}
						else {
							inside += input_str.at(ii);
						}
				
						if (openPar == 0){
							break;
						}
					}
					input_str.replace(i-4,repLen, "slope"+solveStr + "("+inside+")");
					std::string sNew = std::string(7+solveStr.length()+inside.length(),followAMap["original"].at(i-4));
					followAMap["original"].replace(i-4,repLen,sNew);
					fiveChars = ".....";
					i += -5;
					//std::cout << i << " : " << input_str << " 3chars: " << threeChars << '\n';
				}
				
			}
			else if (query3.find(threeChars) != query3.end()){
				if (query3[threeChars].at(0) == ddx){ //is a derivative with respect to something
					//std::cout << i << " : " << input_str << " 3chars: " << threeChars << '\n';
					std::string inside = "";
					std::string var = "";
					int openPar = 0;
					bool isVar = false;
					int repLen = 3;
					for (ii=i+1;ii<input_str.length();ii++){
						repLen++;
						if (input_str.at(ii) == '('){
							openPar++;
						}
						else if (input_str.at(ii) == ')'){
							openPar--;
						}
						else if (input_str.at(ii) == ';'){
							isVar = true;
						}
						else if (isVar){
							var += input_str.at(ii);
						}
						else {
							inside += input_str.at(ii);
						}
				
						if (openPar == 0){
							break;
						}
					}
					input_str.replace(i-2,repLen,"("+var+")"+ddx+"("+inside+")");
					std::string sNew = std::string(4+var.length()+1+inside.length(),followAMap["original"].at(i-2));
					followAMap["original"].replace(i-2,repLen,sNew);
					threeChars = "...";
					i += -3;
					//std::cout << i << " : " << input_str << " 3chars: " << threeChars << '\n';
				}
				else if (query3[threeChars].at(0) == idx){ //is a derivative with respect to something
					//std::cout << i << " : " << input_str << " 3chars: " << threeChars << '\n';
					std::string inside = "";
					std::string var = "";
					int openPar = 0;
					bool isVar = false;
					int repLen = 3;
					for (ii=i+1;ii<input_str.length();ii++){
						repLen++;
						if (input_str.at(ii) == '('){
							openPar++;
						}
						else if (input_str.at(ii) == ')'){
							openPar--;
						}
						else if (input_str.at(ii) == ';'){
							isVar = true;
						}
						else if (isVar){
							var += input_str.at(ii);
						}
						else {
							inside += input_str.at(ii);
						}
				
						if (openPar == 0){
							break;
						}
					}
					input_str.replace(i-2,repLen,"("+var+")"+idx+"("+inside+")");
					threeChars = "...";
					i += -3;
					//std::cout << i << " : " << input_str << " 3chars: " << threeChars << '\n';
				}
				else if (query3[threeChars].at(0) == sub){ //is a derivative with respect to something
					//std::cout << i << " : " << input_str << " 3chars: " << threeChars << '\n';
					std::string inside = "";
					std::string var = "";
					int openPar = 0;
					bool isVar = false;
					int repLen = 3;
					for (ii=i+1;ii<input_str.length();ii++){
						repLen++;
						if (input_str.at(ii) == '('){
							if (openPar >0){
								if (isVar){
									var += input_str.at(ii);
								}
								else {
									inside += input_str.at(ii);
								}
							}
							openPar++;
						}
						else if (input_str.at(ii) == ')'){
							openPar--;
							if (openPar >0){
								if (isVar){
									var += input_str.at(ii);
								}
								else {
									inside += input_str.at(ii);
								}
							}
						}
						else if (input_str.at(ii) == ';'){
							isVar = true;
						}
						else if (isVar){
							var += input_str.at(ii);
						}
						else {
							inside += input_str.at(ii);
						}
				
						if (openPar == 0){
							break;
						}
					}
					input_str.replace(i-2,repLen,"("+var+")"+sub+"("+inside+")");
					threeChars = "...";
					i += -3;
					//std::cout << i << " : " << input_str << " 3chars: " << threeChars << '\n';
				}
			
			}
			//std::cout << i << " : " << input_str << " 3chars: " << threeChars << '\n';
		}
		else if (query4.find(fourChars) != query4.end() && input_str.length() > i+2 && input_str.at(i+1)!='-' && input_str.at(i+2)!='-'){
			
			if (input_str.at(i)=='^'){ //is trig function to a power--unless add more
				//std::cout << i << " : " << input_str << " 4chars: " << fourChars << '\n';
				std::string inside = "";
				std::string var = "";
				int openPar = 0;
				bool isVar = true;
				int repLen = 4;
				for (ii=i+1;ii<input_str.length();ii++){
					repLen++;
					if (input_str.at(ii) == '('){
						openPar++;
						isVar = false;
					}
					else if (input_str.at(ii) == ')'){
						openPar--;
					}
					else if (isVar){
						var += input_str.at(ii);
					}
					else {
						inside += input_str.at(ii);
					}
			
					if (openPar == 0 && !isVar){
						break;
					}
				}
				input_str.replace(i-3,repLen,"("+query4[fourChars]+"("+inside+"))^("+var+")");
				std::string sNew = std::string(7+var.length()+query4[fourChars].length()+inside.length(),followAMap["original"].at(i-3));
				followAMap["original"].replace(i-3,repLen,sNew);
				fourChars = "....";
				i += -4;
				//std::cout << i << " : " << input_str << " char: " << query4[fourChars] << '\n';
			}
			
		
		}
		else if (query3.find(threeChars) != query3.end()){
			if (query3[threeChars].at(0) == log){
				if (input_str.at(i+1)=='^'){
					std::string inside = "";
					std::string var = "";
					int openPar = 0;
					bool isVar = true;
					int repLen = 4;
					for (ii=i+2;ii<input_str.length();ii++){
						repLen++;
						if (input_str.at(ii) == '('){
							if (openPar >0){
								if (isVar){
									var += input_str.at(ii);
								}
								else {
									inside += input_str.at(ii);
								}
							}
							openPar++;
							isVar = false;
						}
						else if (input_str.at(ii) == ')'){
							openPar--;
							if (openPar >0){
								if (isVar){
									var += input_str.at(ii);
								}
								else {
									inside += input_str.at(ii);
								}
							}
						}
						else if (isVar){
							var += input_str.at(ii);
						}
						else {
							inside += input_str.at(ii);
						}
			
						if (openPar == 0 && !isVar){
							break;
						}
					}
					input_str.replace(i-2,repLen,"(e"+query3[threeChars]+"("+inside+"))^("+var+")");
					std::string sNew = std::string(8+var.length()+query3[threeChars].length()+inside.length(),followAMap["original"].at(i-2));
					followAMap["original"].replace(i-2,repLen,sNew);
					fourChars = "....";
					i += -3;
					//std::cout << i << " : " << input_str << " char: " << query3[threeChars] << '\n';
				}
				else if (input_str.at(i+1)=='_'){
					std::string inside = "";
					std::string var = "";
					int openPar = 0;
					bool isVar = true;
					int repLen = 4;
					for (ii=i+2;ii<input_str.length();ii++){
						repLen++;
						if (input_str.at(ii) == '('){
							openPar++;
							isVar = false;
						}
						else if (input_str.at(ii) == ')'){
							openPar--;
						}
						else if (isVar){
							var += input_str.at(ii);
						}
						else {
							inside += input_str.at(ii);
						}
			
						if (openPar == 0 && !isVar){
							break;
						}
					}
					input_str.replace(i-2,repLen,var+query3[threeChars]+"("+inside+")");
					std::string sNew = std::string(2+var.length()+query3[threeChars].length()+inside.length(),followAMap["original"].at(i-2));
					followAMap["original"].replace(i-2,repLen,sNew);
					threeChars = "...";
					i += -3;
					//std::cout << i << " : " << input_str << " char: " << query3[threeChars] << '\n';
				}
				else if (input_str.length()>i+3 && input_str.at(i+1) == 'l' && input_str.at(i+2) == 'o' && input_str.at(i+3) == 'g'){
					std::string inside = "";
					std::string var = "";
					int openPar = 0;
					bool isVar = false;
					bool isInside = false;
					int repLen = 3;
					//std::cout << i << " : " << input_str << " char: " << query3[threeChars] << '\n';
					for (ii=i+1;ii<input_str.length();ii++){
						repLen++;
						inside += input_str.at(ii);
						if (input_str.at(ii) == '('){
							openPar++;
							isInside = true;
							isVar = false;
						}
						else if (input_str.at(ii) == ')'){
							openPar--;
						}
						else if (input_str.at(ii) == '_'){
							isVar = true;
						}
						else if (isVar){
							var += input_str.at(ii);
						}
						
			
						if (openPar == 0 && isInside){
							break;
						}
					}
					//std::cout << var << " : " << inside << " char: " << query3[threeChars] << '\n';
					if (var == ""){var = "e";}
					input_str.replace(i-2,repLen,var+log+"("+inside+")");
					std::string sNew = std::string(3+var.length()+inside.length(),followAMap["original"].at(i-2));
					followAMap["original"].replace(i-2,repLen,sNew);
					threeChars = "...";
					i += -3;
					//std::cout << i << " : " << input_str << " char: " << query3[threeChars] << '\n';
				}
				else {
					std::string inside = "";
					std::string var = "";
					int openPar = 0;
					bool isVar = true;
					int repLen = 3;
					for (ii=i+1;ii<input_str.length();ii++){
						repLen++;
						if (input_str.at(ii) == '('){
							openPar++;
							isVar = false;
						}
						else if (input_str.at(ii) == ')'){
							openPar--;
						}
						else if (isVar){
							var += input_str.at(ii);
						}
						else {
							inside += input_str.at(ii);
						}
			
						if (openPar == 0 && !isVar){
							break;
						}
					}
					input_str.replace(i-2,repLen,var+query3[threeChars]+"("+inside+")");
					std::string sNew = std::string(2+var.length()+query3[threeChars].length()+inside.length(),followAMap["original"].at(i-2));
					followAMap["original"].replace(i-2,repLen,sNew);
					threeChars = "...";
					i += -3;
					//std::cout << i << " : " << input_str << " char: " << query3[threeChars] << '\n';
				}
			}
		}
		else if (query2.find(twoChars) != query2.end()){
			if (query2[twoChars].at(0) == log){
				if (input_str.at(i+1)=='^'){
					std::string inside = "";
					std::string var = "";
					int openPar = 0;
					bool isVar = true;
					int repLen = 3;
					for (ii=i+2;ii<input_str.length();ii++){
						repLen++;
						if (input_str.at(ii) == '('){
							openPar++;
							isVar = false;
						}
						else if (input_str.at(ii) == ')'){
							openPar--;
						}
						else if (isVar){
							var += input_str.at(ii);
						}
						else {
							inside += input_str.at(ii);
						}
			
						if (openPar == 0 && !isVar){
							break;
						}
					}
					input_str.replace(i-1,repLen,"(e"+query2[twoChars]+"("+inside+"))^("+var+")");
					std::string sNew = std::string(8+var.length()+query2[twoChars].length()+inside.length(),followAMap["original"].at(i-1));
					followAMap["original"].replace(i-1,repLen,sNew);
					twoChars = "..";
					i += -2;
					//std::cout << i << " : " << input_str << " char: " << query2[twoChars] << '\n';
				}
				else if (input_str.length()>i+2 && input_str.at(i+1) == 'l' && input_str.at(i+2) == 'n'){
					std::string inside = "";
					std::string var = "";
					int openPar = 0;
					bool isVar = false;
					bool isInside = false;
					int repLen = 2;
					for (ii=i+1;ii<input_str.length();ii++){
						repLen++;
						inside += input_str.at(ii);
						if (input_str.at(ii) == '('){
							openPar++;
							isInside = true;
							isVar = false;
						}
						else if (input_str.at(ii) == ')'){
							openPar--;
						}
						else if (input_str.at(ii) == '_'){
							isVar = true;
						}
						
			
						if (openPar == 0 && isInside){
							break;
						}
					}
					input_str.replace(i-1,repLen,"e" + query2[twoChars] +"("+inside+")");
					std::string sNew = std::string(2+query2[twoChars].length()+inside.length(),followAMap["original"].at(i-1));
					followAMap["original"].replace(i-1,repLen,sNew);
					twoChars = "..";
					i += -2;
					//std::cout << i << " : " << input_str << " char: " << query2[twoChars] << '\n';
				}
			}
			
		}
	}
	std::string output_str = "";
	followAMap["original2"] = "";
	for (i=0;i<input_str.length();i++){
		switch (input_str.at(i)) 
		{ 
			case '+': {
				if (i+1<input_str.length() && input_str.at(i+1) == '+'){output_str += pestr + "1"; i++; break;}
				else {output_str += input_str.at(i);followAMap["original2"] += followAMap["original"].at(i); break;}
				}
			case '-': {
				if (i+1<input_str.length() && input_str.at(i+1) == '-'){output_str += mestr + "1"; i++; break;}
				else {output_str += input_str.at(i);followAMap["original2"] += followAMap["original"].at(i); break;}
				}
			case '!': {
				if (i+1<input_str.length() && input_str.at(i+1) == '!'){output_str += factorialstr; i++; break;}
				else {output_str += input_str.at(i);followAMap["original2"] += followAMap["original"].at(i); break;}
				}
			case ' ': break;
			case '\t': break;
			case '\n': break;
			default: output_str += input_str.at(i); followAMap["original2"] += followAMap["original"].at(i);
		}
	}
	followAMap["original"] = followAMap["original2"];
	return output_str;
}




std::string postfixify(std::string input_str) {
	/*input_str = input_str.toUpperCase();
	input_str = input_str.replace(/\[/g,'(');
	input_str = input_str.replace(/]/g,')');
	input_str = input_str.replace(/{/g,'(');
	input_str = input_str.replace(/}/g,')');
	input_str = input_str.replace(/\+-/g,'-');
	input_str = input_str.replace(/--/g,'+');*/
	
	input_str = replaceFunctions(input_str);
	
	char infixexpr[input_str.length() + 1]; 
    strcpy(infixexpr, input_str.c_str()); 

	infixexpr[input_str.length()] = '\0';
	//std::cout << makePost(infixexpr) << '\n';
	

	return makePost(infixexpr);
}

std::vector<std::string> postfixifyVector(std::string input_str, bool checkComputations){

	
	int iii;
	if (followAMap.find("original") == followAMap.end()){
		followAMap["original"]="";
	}
	int sz = followAMap["original"].length();
	if (sz < input_str.length()){
		for (iii=sz;iii<input_str.length();iii++){
			followAMap["original"]+='0';
			
		}
	}
	
	input_str = replaceFunctions(input_str);
	
	std::map<std::string,std::string> repMap;
	//std::cout <<"pv: "<< input_str << "\n";
	
	
	if (checkComputations){
		char repl = 'A';
		
		
		for (iii=0;iii+2<input_str.length();iii++){
			if (input_str.at(iii) == '=' && input_str.at(iii+1) == '(' && (iii==0 || input_str.at(iii-1) == '(' || input_str.at(iii-1) == '=' || prec.find(input_str.at(iii-1)) != prec.end())){
				int i = iii;
				int ii; int openPar = 0;
				std::string inside = "";
				std::string insideFollow = "";
				std::string type = "Q";
				std::string typeFollow = "0";
				for (ii=i+1;ii<input_str.length();ii++){
					if (input_str.at(ii) == '('){
						if (openPar > 0){
							inside += input_str.at(ii);
							insideFollow += followAMap["original"].at(ii);
						}
						openPar++;
					}
					else if (input_str.at(ii) == ')'){
						openPar--;
						if (openPar > 0){
							inside += input_str.at(ii);
							insideFollow += followAMap["original"].at(ii);
						}
					}
					else {
						inside += input_str.at(ii);
						insideFollow += followAMap["original"].at(ii);
					}
					if (openPar == 0){
						if (ii+3<input_str.length()){
							if (input_str.at(ii+1) == '['){
								int ci;
								type = "";
								typeFollow = "";
								for (ci=ii+2;ci<input_str.length();ci++){
									if (input_str.at(ci) >= 'A' && input_str.at(ci) <= 'Z'){
										type += input_str.at(ci);
										typeFollow += followAMap["original"].at(ci);
									}
									else if (input_str.at(ci) == ']'){
										ii = ci;
										break;
									}
									else {
										type = "";
										typeFollow = "";
										break;
									}
								}
							} 
							
						}
						break;
					}
				}
				std::string key = type;
				std::string keyFollow = typeFollow;
				key += repl;
				keyFollow += "0";
				repl++;
				input_str.replace(i,ii+1-i,key);
				followAMap["original"].replace(i,ii+1-i,keyFollow);
				repMap[key]=inside;
				followAMap[key]=insideFollow;
				//std::cout << "found: " << input_str << "\n";
			}
		
		}
	}
	
	char infixexpr[input_str.length() + 1]; 
    strcpy(infixexpr, input_str.c_str()); 

	infixexpr[input_str.length()] = '\0';
	
	bool showFAM = false;
	
	if (followAMap["original"].length() > 2){
		for (iii=0;iii<followAMap["original"].length();iii++){
			if (followAMap["original"].at(iii) != '0'){
				showFAM = true;
				break;
			}
		}
	}
	if (showFAM){
		std::string visOriginal = "";
		std::string visNew = "";
		for (iii=0;iii<followAMap["original"].length();iii++){
			int s000 = followAMap["original"].at(iii);
			visOriginal += std::to_string(s000)+",";
		}
		for (iii=0;iii<followAMap["expstr"].length();iii++){
			int s000 = followAMap["expstr"].at(iii);
			visNew += std::to_string(s000)+",";
		}
		string_log("NonZero1");
		string_log(visOriginal.c_str());
		string_log(visNew.c_str());
		string_log(infixexpr);
	}
	
	std::vector<std::string> postVector = makePostVector(infixexpr);
	//std::cout <<"pv: "<< postVector[0] << " and " << postVector[1] << "\n";

	
	
	if (checkComputations){
		std::string checkChars = "";
		for (iii=0;iii<postVector[1].length();iii++){
			if (postVector[1].at(iii) < 'A' || postVector[1].at(iii) > 'Z' ){
				
				if (checkChars.length()>1 && repMap.find(checkChars) != repMap.end()){
					//std::cout << "rmtc: " << repMap[twoChars] << "\n";
					std::string repText = postfixify(repMap[checkChars]);
					if (checkChars.at(0) != 'Q'){
						repText.replace(0,0,checkChars.substr(0,checkChars.length()-1));
					}
				
					postVector[1].replace(iii-checkChars.length(),checkChars.length(),"("+repText+")");
					iii += 2+repText.length() - checkChars.length();
				}
				checkChars = "";
			}
			else {
				checkChars += postVector[1].at(iii);
			}
			
		}
	}
	
	showFAM = false;
	
	if (followAMap["original"].length() > 2){
		for (iii=0;iii<followAMap["original"].length();iii++){
			if (followAMap["original"].at(iii) != '0'){
				showFAM = true;
				break;
			}
		}
	}
	if (showFAM){
		std::string visOriginal = "";
		std::string visNew = "";
		for (iii=0;iii<followAMap["original"].length();iii++){
			int s000 = followAMap["original"].at(iii);
			visOriginal += std::to_string(s000)+",";
		}
		for (iii=0;iii<followAMap["expstr"].length();iii++){
			int s000 = followAMap["expstr"].at(iii);
			visNew += std::to_string(s000)+",";
		}
		string_log("NonZero");
		string_log(visOriginal.c_str());
		string_log(visNew.c_str());
		string_log(infixexpr);
		string_log(postVector[0].c_str());
	}
	
	//std::cout <<"pv: "<< postVector[1] << "\n";
	return postVector;
}

bool checkPostfix(std::string postfix) {
	
	int i;
  	int currentIndex = 0;
  	int arrayIndex = 0;
  	std::vector<int> stack;
  	std::vector<int> intArray;
  	std::string currentOperand = "";
	int openPar = 0;
	int intArraySz = 0;
  	for (i=0; i<postfix.length(); i++) 
    {
    	if (postfix.at(i) == '{' || postfix.at(i) == '('){
    		openPar++;
    	}
    	else if (postfix.at(i) == '}' || postfix.at(i) == ')'){
    		openPar--;
    	}
    	else if (openPar > 0){
    		continue;
    	}
    	else if (openPar < 0){
    		return false;
    	}
        else if (postfix.at(i) == '_') {
			intArray.push_back(1);
			stack.push_back(1);
			intArraySz++;

        }
    }
	if (openPar != 0){return false;}
    for (i=0; i<postfix.length(); i++) { 
    	//std::cout << "pfi: " << i << "\n";
        if (postfix.at(i) == '#') {
        	intArraySz--;
        	if (intArraySz <0){
        		return false;
        	}
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
	            case '+': break;
	            case '-': currentIndex++; break; 
	            case '*': break; 
	            case '/': currentIndex++; break;
	            case '^': break;
	            case '%': break; 
	            case -41: currentIndex++; break;
	            case -93: break;
	            case -84: break;
	            case -82: currentIndex++; break;
	            case -67: currentIndex++; break;
	            case -64: currentIndex++; break;
	            case -63: currentIndex++; break;
	            case -62: currentIndex++; break;
	            case -61: currentIndex++; break;
	            case -60: currentIndex++; break;
	            case -59: currentIndex++; break;
	            case -34: currentIndex++; break;
	            case -32: currentIndex++; break;
	            case -31: currentIndex++; break;
	            case -30: currentIndex++; break;
	            case -29: currentIndex++; break;
	            case -28: currentIndex++; break;
	            case -27: currentIndex++; break;
	            case -16: currentIndex++; break;
	            case -15: currentIndex++; break;
	            case -14: currentIndex++; break;
	            case -13: currentIndex++; break;
	            case -12: currentIndex++; break;
	            case -11: currentIndex++; break;
	            case '=': break;
	            case '>': break;
	            case '<': break;
	            case ']': break;
	            case '[': break;
	            case '!': break;
	            case -125: break;
	            case -126: currentIndex--; break;
	            default: {
	            	if (postfix.at(i) <= -69){
	            		break;
	            	}
	            	else if (postfix.at(i) < 0){
	            		currentIndex++; break;
	            	}
	            	else {
	            		return false;
	            	}
	            }
	            //case '!': stack[currentIndex - 2] = stack[currentIndex - 2] != stack[currentIndex - 1]; break;
	            //case '%': stack[currentIndex - 2] = stack[currentIndex - 2] % stack[currentIndex - 1]; break; 
	            //case '&': stack[currentIndex - 2].w = (stack[currentIndex - 2].w + stack[currentIndex - 1].w > 1) ? 1 : 0; stack[currentIndex - 2].t = (stack[currentIndex - 2].t == 'B' && stack[currentIndex - 1].t == 'B') ? 'B' : 'N'; break; 
	            //case '|': stack[currentIndex - 2].w = (stack[currentIndex - 2].w + stack[currentIndex - 1].w == 0) ? 0 : 1; stack[currentIndex - 2].t = (stack[currentIndex - 2].t == 'B' && stack[currentIndex - 1].t == 'B') ? 'B' : 'N'; break; 
	            //multiandcase '&': if (stack[currentIndex - 5] > 0 && stack[currentIndex - 4] > 0 && stack[currentIndex - 3] > 0 && stack[currentIndex - 2] > 0 && stack[currentIndex - 1] > 0) {stack[currentIndex - 5] = 1;} else {stack[currentIndex - 5] = -1;}; currentIndex--; currentIndex--; currentIndex--; currentIndex--; break; 
            
            }
            
            currentIndex--;
            if (currentIndex < 0){
            	return false;
            }
        } 
    } 
	if (currentIndex == 1 && intArraySz ==0){
		return true;
	}
	else {
		return false;
	}
	return false;
}

