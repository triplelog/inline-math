std::string inputLogic(char c, std::string s, int ii, std::string child, char lastOp);
std::string codeLogic(char c, std::string s, int ii, std::string child, char lastOp);

int lev(std::string ss, std::string st){
    int i,j,m,n,temp,tracker;
    
	m = ss.length(); 
    char s[m + 1]; 
    strcpy(s, ss.c_str());
    n = st.length(); 
    char t[n + 1]; 
    strcpy(t, st.c_str());
    
    int d[n+1][m+1];

    for(i=0;i<=m;i++){
    	d[0][i] = i;
    }

    for(j=0;j<=n;j++){
    	d[j][0] = j;
    }


    for (j=1;j<=m;j++) {

        for(i=1;i<=n;i++) {

            if(s[i-1] == t[j-1])

            {

                tracker = 0;

            }

            else

            {

                tracker = 1;

            }
			if ( (d[i-1][j]+1) < (d[i][j-1]+1) ){
				temp = (d[i-1][j]+1);
			}
			else {
				temp = (d[i][j-1]+1);
			}
            
			if (temp < (d[i-1][j-1]+tracker) ){
				d[i][j] = temp;
			}
			else {
				d[i][j] = (d[i-1][j-1]+tracker);
			}

        }

    }
    return d[n][m];

}

int autoDistance(std::string ss, std::string control) {
	int d = lev(ss,control)*1000;
	int ssl = ss.length();
	int cl = control.length();
	if (ssl == 0 || cl == 0){return 2000;}
	if (cl < ssl){
		ss.replace(cl,ssl-cl,"");
		d /= (ssl+3);
		d += lev(ss,control)*1000/(cl+3);
	}
	else {
		d /= (ssl+3);
		d += lev(ss,control)*1000/(cl+3);
	}
	return d;
}

std::string codify(std::string pfstr) {
	int i; int ii; int iii;
	std::map<std::string,std::string> listMap;
	std::map<std::string,char> lastOpMap;
	int idx = 0;
	bool startOperands = false;
	std::string currentOperator = "";
	std::map<int,std::string> originalMap;
	int iidx = 0;

	for (i=0;i<pfstr.length();i++){
		if (pfstr.at(i) == '@'){
			startOperands = true;
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



	std::map<int,std::string> operandMap;
	std::string lastInput = "";
	std::string soFarLeft = "";
	std::string soFarRight = "";
	for (i=0;i<pfstr.length();i++){
		soFarLeft += pfstr.at(i);
		
		if (pfstr.at(i) == '@'){
			break;
		}
		else if (pfstr.at(i) != '#'){
			
			bool foundFull = false;
			std::string fullStr = "";
			for (ii=0;ii<i+1;ii++){
				std::string s = "";
				std::string t = "";
				for (iii=ii;iii<i+1;iii++){
					s += pfstr.at(iii);
					if (pfstr.at(iii) == '#'){
						t += operandMap[iii] + '_';
					}
				}
				if (listMap.find(s + '@' + t) != listMap.end()){
					foundFull = true;
					fullStr = s + '@' + t;
					break;
				}
			}
			if (foundFull){
				lastInput = listMap[fullStr];
				continue;
			}
			
			
			std::string secondStr = "";
			std::string secondTtr = "";
			std::string secondChild = "";
			int maxi = i-1;
		
			for (ii=0;ii<i;ii++){
				std::string s = "";
				std::string t = "";
				for (iii=ii;iii<i;iii++){
					s += pfstr.at(iii);
					if (pfstr.at(iii) == '#'){
						t += operandMap[iii] + '_';
					}
				}
				if (listMap.find(s + '@' + t) != listMap.end()){
					secondStr = s;
					secondTtr = t;
					secondChild = s + '@' + t;
					maxi = ii;
					break;
				}
			}
			std::string firstStr = "";
			std::string firstTtr = "";
			std::string firstChild = "";
		
			if (pfstr.at(i) != '-' && pfstr.at(i) != '/' && (pfstr.at(i) >= 0 || pfstr.at(i) <= -69 )){ // Is at least binary function
			
				for (ii=0;ii<maxi;ii++){
					std::string s = "";
					std::string t = "";
					for (iii=ii;iii<maxi;iii++){
						s += pfstr.at(iii);
						if (pfstr.at(iii) == '#'){
							t += operandMap[iii] + '_';
						}
					}
					if (listMap.find(s + '@' + t) != listMap.end()){
						firstStr = s;
						firstTtr = t;
						firstChild = s + '@' + t;
						break;
					}
				}
			
			
			}
			fullStr = firstStr + secondStr + pfstr.at(i) + '@' + firstTtr + secondTtr;
			
			std::string s = "";
			if (listMap.find(fullStr) != listMap.end()){
				lastInput = listMap[fullStr];
				continue;
			}
			for (ii=0;ii<2;ii++){
				std::string child = secondChild;
				if (ii==0 && firstChild != ""){
					child = firstChild;
				}
				else if (ii==1 && firstChild == ""){
					break;
				}
				s = codeLogic(pfstr.at(i),s,ii,listMap[child],lastOpMap[child]);
			}
		
			listMap[fullStr]=s;
			lastOpMap[fullStr]=pfstr.at(i);
			lastInput = s;
		
		
		}
		else {
			soFarRight += originalMap[idx] + '_';
			listMap["#@" + originalMap[idx] + "_"]=originalMap[idx];
			lastOpMap["#@" + originalMap[idx] + "_"]='#';
			operandMap[i]=originalMap[idx];
			lastInput = originalMap[idx];
			idx++;
		}
	
	}
	return lastInput;

}

char charFromIntString(bool neg, std::string x) {
	int i = 0;
	i += 100*(x.at(0)-'0');
	i += 10*(x.at(1)-'0');
	i += 1*(x.at(2)-'0');
	if (neg){
		i *= -1;
	}
	char c = i;
	return c;
}
std::string charredPost(std::string pfstr) {
	std::string outString = "";
	int i;
	for (i=0;i<pfstr.length();i++){
		if (pfstr.at(i) == '@'){
			outString += pfstr.substr(i,pfstr.length()-i);
			break;
		}
		else if (pfstr.at(i) == '#'){
			outString += '#';
		}
		else if (pfstr.at(i) == '-'){
			outString += charFromIntString(true,pfstr.substr(i+1,3));
			i+=3;
		}
		else if (pfstr.at(i) == '+'){
			outString += charFromIntString(false,pfstr.substr(i+1,3));
			i+=3;
		}
	}
	return outString;
}

std::string inputifyOne(std::string pfstr) {
	int i; int ii; int iii;
	std::map<std::string,std::string> listMap;
	std::map<std::string,char> lastOpMap;
	int idx = 0;
	bool startOperands = false;
	std::string currentOperator = "";
	std::map<int,std::string> originalMap;
	int iidx = 0;


	for (i=0;i<pfstr.length();i++){
		if (pfstr.at(i) == '@'){
			startOperands = true;
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



	std::map<int,std::string> operandMap;
	std::string lastInput = "";
	std::string soFarLeft = "";
	std::string soFarRight = "";
	for (i=0;i<pfstr.length();i++){
		soFarLeft += pfstr.at(i);
		
		if (pfstr.at(i) == '@'){
			break;
		}
		else if (pfstr.at(i) != '#'){
			
			bool foundFull = false;
			std::string fullStr = "";
			for (ii=0;ii<i+1;ii++){
				std::string s = "";
				std::string t = "";
				for (iii=ii;iii<i+1;iii++){
					s += pfstr.at(iii);
					if (pfstr.at(iii) == '#'){
						t += operandMap[iii] + '_';
					}
				}
				if (listMap.find(s + '@' + t) != listMap.end()){
					foundFull = true;
					fullStr = s + '@' + t;
					break;
				}
			}
			if (foundFull){
				lastInput = listMap[fullStr];
				continue;
			}
			
			
			std::string secondStr = "";
			std::string secondTtr = "";
			std::string secondChild = "";
			int maxi = i-1;
		
			for (ii=0;ii<i;ii++){
				std::string s = "";
				std::string t = "";
				for (iii=ii;iii<i;iii++){
					s += pfstr.at(iii);
					if (pfstr.at(iii) == '#'){
						t += operandMap[iii] + '_';
					}
				}
				if (listMap.find(s + '@' + t) != listMap.end()){
					secondStr = s;
					secondTtr = t;
					secondChild = s + '@' + t;
					maxi = ii;
					break;
				}
			}
			std::string firstStr = "";
			std::string firstTtr = "";
			std::string firstChild = "";
		
			if (pfstr.at(i) != '-' && pfstr.at(i) != '/' && (pfstr.at(i) >= 0 || pfstr.at(i) <= -69 )){ // Is at least binary function
			
				for (ii=0;ii<maxi;ii++){
					std::string s = "";
					std::string t = "";
					for (iii=ii;iii<maxi;iii++){
						s += pfstr.at(iii);
						if (pfstr.at(iii) == '#'){
							t += operandMap[iii] + '_';
						}
					}
					if (listMap.find(s + '@' + t) != listMap.end()){
						firstStr = s;
						firstTtr = t;
						firstChild = s + '@' + t;
						break;
					}
				}
			
			
			}
			fullStr = firstStr + secondStr + pfstr.at(i) + '@' + firstTtr + secondTtr;
			
			std::string s = "";
			if (listMap.find(fullStr) != listMap.end()){
				lastInput = listMap[fullStr];
				continue;
			}
			for (ii=0;ii<2;ii++){
				std::string child = secondChild;
				if (ii==0 && firstChild != ""){
					child = firstChild;
				}
				else if (ii==1 && firstChild == ""){
					break;
				}
				s = inputLogic(pfstr.at(i),s,ii,listMap[child],lastOpMap[child]);
			}
		
			listMap[fullStr]=s;
			lastOpMap[fullStr]=pfstr.at(i);
			lastInput = s;
		
		
		}
		else {
			soFarRight += originalMap[idx] + '_';
			listMap["#@" + originalMap[idx] + "_"]=originalMap[idx];
			lastOpMap["#@" + originalMap[idx] + "_"]='#';
			operandMap[i]=originalMap[idx];
			lastInput = originalMap[idx];
			idx++;
		}
	
	}
	return lastInput;
}

void inputify() {
	int i; int ii; int iii;
	std::map<std::string,std::string> listMap;
	std::map<std::string,char> lastOpMap;
	for (std::map<std::string,Answer>::iterator iter = answerMap.begin(); iter != answerMap.end(); ++iter){
		std::string pfstr = iter->first;
		int idx = 0;
		bool startOperands = false;
		std::string currentOperator = "";
		std::map<int,std::string> originalMap;
		int iidx = 0;
		if (listMap.find(pfstr) != listMap.end()){
			answerMap[pfstr].input = listMap[pfstr];
			continue;
		}
	
		for (i=0;i<pfstr.length();i++){
			if (pfstr.at(i) == '@'){
				startOperands = true;
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
	
	
	
		std::map<int,std::string> operandMap;
		std::string lastInput = "";
		std::string soFarLeft = "";
		std::string soFarRight = "";
		for (i=0;i<pfstr.length();i++){
			soFarLeft += pfstr.at(i);
			
			if (pfstr.at(i) == '@'){
				break;
			}
			else if (pfstr.at(i) != '#'){
				
				bool foundFull = false;
				std::string fullStr = "";
				for (ii=0;ii<i+1;ii++){
					std::string s = "";
					std::string t = "";
					for (iii=ii;iii<i+1;iii++){
						s += pfstr.at(iii);
						if (pfstr.at(iii) == '#'){
							t += operandMap[iii] + '_';
						}
					}
					if (listMap.find(s + '@' + t) != listMap.end()){
						foundFull = true;
						fullStr = s + '@' + t;
						break;
					}
				}
				if (foundFull){
					lastInput = listMap[fullStr];
					continue;
				}
				
				
				std::string secondStr = "";
				std::string secondTtr = "";
				std::string secondChild = "";
				int maxi = i-1;
			
				for (ii=0;ii<i;ii++){
					std::string s = "";
					std::string t = "";
					for (iii=ii;iii<i;iii++){
						s += pfstr.at(iii);
						if (pfstr.at(iii) == '#'){
							t += operandMap[iii] + '_';
						}
					}
					if (listMap.find(s + '@' + t) != listMap.end()){
						secondStr = s;
						secondTtr = t;
						secondChild = s + '@' + t;
						maxi = ii;
						break;
					}
				}
				std::string firstStr = "";
				std::string firstTtr = "";
				std::string firstChild = "";
			
				if (pfstr.at(i) != '-' && pfstr.at(i) != '/' && (pfstr.at(i) >= 0 || pfstr.at(i) <= -69 )){ // Is at least binary function
				
					for (ii=0;ii<maxi;ii++){
						std::string s = "";
						std::string t = "";
						for (iii=ii;iii<maxi;iii++){
							s += pfstr.at(iii);
							if (pfstr.at(iii) == '#'){
								t += operandMap[iii] + '_';
							}
						}
						if (listMap.find(s + '@' + t) != listMap.end()){
							firstStr = s;
							firstTtr = t;
							firstChild = s + '@' + t;
							break;
						}
					}
				
				
				}
				fullStr = firstStr + secondStr + pfstr.at(i) + '@' + firstTtr + secondTtr;
				
				std::string s = "";
				if (listMap.find(fullStr) != listMap.end()){
					lastInput = listMap[fullStr];
					continue;
				}
				for (ii=0;ii<2;ii++){
					std::string child = secondChild;
					if (ii==0 && firstChild != ""){
						child = firstChild;
					}
					else if (ii==1 && firstChild == ""){
						break;
					}
					s = inputLogic(pfstr.at(i),s,ii,listMap[child],lastOpMap[child]);
				}
			
				listMap[fullStr]=s;
				lastOpMap[fullStr]=pfstr.at(i);
				lastInput = s;
			
			
			}
			else {
				soFarRight += originalMap[idx] + '_';
				listMap["#@" + originalMap[idx] + "_"]=originalMap[idx];
				lastOpMap["#@" + originalMap[idx] + "_"]='#';
				operandMap[i]=originalMap[idx];
				lastInput = originalMap[idx];
				idx++;
			}
		
		}
		answerMap[iter->first].input = lastInput;
	}



}

struct Autocomplete {
	int d = 2000;
	std::string answer = "";
	//inline Cppdata operator+=(Cppdata const &b);
};
inline bool operator<(const Autocomplete a, const Autocomplete b){
	if (a.d < b.d){return true;}
	return false;
}

std::vector<std::string> autocomplete(std::string newPostfix,std::string rawAnswer){

	std::vector<Autocomplete> answers;
	std::vector<Autocomplete> shortAnswers;
	int i;
	int ias = 0;
	for (std::map<std::string,Answer>::iterator iter = answerMap.begin(); iter != answerMap.end(); ++iter){
		
		ias++;
	}
	//std::cout << "ias: " << ias << "\n";
	answers.resize(ias);
	//shortAnswers.resize(ias);
	
	i = 0;
	for (std::map<std::string,Answer>::iterator iter = answerMap.begin(); iter != answerMap.end(); ++iter){
	
		
		std::string ca = iter->second.input;
		
		Autocomplete answer;
		answer.d = autoDistance(ca,rawAnswer);
		answer.answer = iter->first;
		answers[i] = answer;
		i++;
		//std::cout << "distance: " << autoDistance(ca,rawAnswer) << " of "<< iter->first << "\n";
		
	}
	if (ias > 12){
		ias = 12;
	}

	std::partial_sort(answers.begin(),answers.begin()+ias,answers.end());

	
	std::vector<std::string> returnAnswers;
	returnAnswers.resize(ias);
	for (i=0;i<ias;i++){
		returnAnswers[i] = answers[i].answer;
		//std::cout << answers[i].answer << " with d="<< answers[i].d <<"\n";
	}
	return returnAnswers;
	
	//std::cout << "question: " << inputify(newPostfix) << "with " << answers.size() << "\n";
	//std::cout << "user answer: " << rawAnswer << "\n";
	
}

std::string inputLogic(char c, std::string s, int ii, std::string child, char lastOp){
	switch (c){
		case '^': {
			if (ii > 0){
				s += "^";
				if (prec[lastOp] < 100){
					s += "("+child+")";
				}
				else {
					s += child;
				}
			}
			else {
				if (prec[lastOp] < 100){
					s += "("+child+")";
				}
				else {
					s += child;
				}
			}
			break;
		}
		case -69: {
			if (ii > 0){
				s += child+"]";
			}
			else {
				s += "d/d"+child+"[";
			}
			break;

		}
		case -85: {
			if (ii > 0){
				s.replace(6,0,child+" d");
			}
			else {
				s += "int "+child+"}";
			}
			break;

		}
		case -89: {
			if (ii > 0){
				s += child+")";
			}
			else {
				s += child+"(";
			}
			break;

		}
		case -34:
			s += "|"+child+"|";
			break;
		case -64:
			s += "sin("+child+")";
			break;
		case -63:
			s += "cos("+child+")";
			break;
		case -62:
			s += "tan("+child+")";
			break;
		case -61:
			s += "csc("+child+")";
			break;
		case -60:
			s += "sec("+child+")";
			break;
		case -59:
			s += "cot("+child+")";
			break;
		case -32:
			s += "sin^(-1)("+child+")";
			break;
		case -31:
			s += "cos^(-1)("+child+")";
			break;
		case -30:
			s += "tan^(-1)("+child+")";
			break;
		case -29:
			s += "csc^(-1)("+child+")";
			break;
		case -28:
			s += "sec^(-1)("+child+")";
			break;
		case -27:
			s += "cot^(-1)("+child+")";
			break;
		case -16:
			s += "sinh("+child+")";
			break;
		case -15:
			s += "cosh("+child+")";
			break;
		case -14:
			s += "tanh("+child+")";
			break;
		case -13:
			s += "csch("+child+")";
			break;
		case -12:
			s += "sech("+child+")";
			break;
		case -11:
			s += "coth("+child+")";
			break;
		case -67:
			s += "sqrt("+child+")";
			break;
		case -84: {
			if (ii > 0){
				s += child+")";
			}
			else {
				s += "sqrt["+child+"](";
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
					s += "ln";
				}
				else {
					s += "log_{"+child+"}";
				}
			}
			break;

		}
		case '-': {
			if (prec[c] >= prec[lastOp]){
				s += "-("+child+")";
			}
			else {
				s += "-"+child;
			}
			break;
		}
		case '/': {
			s += "1/("+child+")";
			/*
			if (prec[c] >= prec[lastOp]){
				s += "/("+child+")";
			}
			else {
				s += "/"+child;
			}*/
			break;
		}
		case -101: {
			if (ii > 0){
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
					s += "max("+child;
				}
				
			}
			break;
		}
		case -100: {
			if (ii > 0){
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
					s += "min("+child;
				}
				
			}
			break;
		}
		case -97: {
			if (ii > 0){
				s += ",";
				s += child+")";
			}
			else {
				s += "comb("+child;
			}
			break;
		}
		case -98: {
			if (ii > 0){
				s += ",";
				s += child+")";
			}
			else {
				s += "perm("+child;
			}
			break;
		}
		case -99: {
			if (ii > 0){
				s += ",";
				s += child+")";
			}
			else {
				s += "gcd("+child;
			}
			break;
		}
		case -125: {
			if (ii > 0){
				s += "(";
				s += child+")";
			}
			else {
				s += child;
			}
			break;
		}
		default: {
			if (prec[c] > prec[lastOp]){
				if (ii > 0){
					if (c == '*'){
						s += "*("+child+")";
					}
					else {
						s += c+"("+child+")";
					}
				}
				else {
					s += "("+child+")";
				}
			}
			else if (prec[c] == prec[lastOp] && c != lastOp){
				if (ii > 0){
					if (c == '*'){
						s += "*"+child;//want to move this into numerator somehow
					}
					else if (c == '+'){
						s += child;
					}
					else {
						s += c+"("+child+")";
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
						s += "("+child+")";
					}
				}
			}
			else {
				if (ii > 0){
					if (c == '*'){
						s += "*"+child;
					}
					else {
						s += c+child;
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

std::string codeLogic(char c, std::string s, int ii, std::string child, char lastOp){
	if (child == "\\pi"){
		child = "Math.PI";
	}
	else if (child == "e"){
		child = "Math.E";
	}
	switch (c){
		case '^': {
			if (ii > 0){
				s += ","+child+")";
			}
			else {
				s += "Math.pow("+child;
			}
			break;
		}
		case -34:
			s += "Math.abs("+child+")";
			break;
		case -64:
			s += "Math.sin("+child+")";
			break;
		case -63:
			s += "Math.cos("+child+")";
			break;
		case -62:
			s += "Math.tan("+child+")";
			break;
		case -61:
			s += "Math.csc("+child+")";
			break;
		case -60:
			s += "Math.sec("+child+")";
			break;
		case -59:
			s += "Math.cot("+child+")";
			break;
		case -32:
			s += "Math.asin("+child+")";
			break;
		case -31:
			s += "Math.acos("+child+")";
			break;
		case -30:
			s += "Math.atan("+child+")";
			break;
		case -29:
			s += "Math.acsc("+child+")";
			break;
		case -28:
			s += "Math.asec("+child+")";
			break;
		case -27:
			s += "Math.acot("+child+")";
			break;
		case -16:
			s += "Math.sinh("+child+")";
			break;
		case -15:
			s += "Math.cosh("+child+")";
			break;
		case -14:
			s += "Math.tanh("+child+")";
			break;
		case -13:
			s += "Math.csch("+child+")";
			break;
		case -12:
			s += "Math.sech("+child+")";
			break;
		case -11:
			s += "Math.coth("+child+")";
			break;
		case -67:
			s += "Math.sqrt("+child+")";
			break;
		case -84: {
			if (ii > 0){
				s += child+")";
			}
			else {
				s += "Math.root["+child+"](";
			}
			break;

		}
		case -93: {
			if (ii > 0){
				s += "("+child+")";
	
			}
			else {
				if (child == "e"){
					s += "Math.ln";
				}
				else if (child == "10"){
					s += "Math.log10";
				}
				else if (child == "2"){
					s += "Math.log2";
				}
				else {
					s += "Math.log_"+child;
				}
			}
			break;

		}
		case -101: {
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
					s += "Math.max("+child;
				}
				
			}
			break;
		}
		case -100: {
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
					s += "Math.min("+child;
				}
				
			}
			break;
		}
		case -97: {
			if (ii > 0){
				s += ",";
				s += child+")";
			}
			else {
				s += "Math.comb("+child;
			}
			break;
		}
		case -98: {
			if (ii > 0){
				s += ",";
				s += child+")";
			}
			else {
				s += "Math.perm("+child;
			}
			break;
		}
		case -99: {
			if (ii > 0){
				s += ",";
				s += child+")";
			}
			else {
				s += "Math.gcd("+child;
			}
			break;
		}
		default: {
			return inputLogic(c, s, ii, child, lastOp);
		}
	}
	return s;
}

