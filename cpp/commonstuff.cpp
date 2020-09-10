bool checkAnswer(std::string answer);
std::string makeInt(std::string input);
std::map<char,int> prec;

std::map<std::string,std::vector<int>> constraintsMet;
//std::map<std::string,std::vector<std::string>> allListMapFull;
//std::map<std::string,std::vector<std::vector<std::string>>> allListMapBottom;
std::map<std::string,bool> constraintMap;

std::string jsonmessage;
int duration1;
int duration2;
int duration3;
int yesC;
int noC;
int mapSave;
int mapMake;
int overallScore;
bool answerIsFinished;
std::map<int,int> eloMap;



struct Dewey {
	std::string subject = ".";
	std::string topic = ".";
	std::string lesson = ".";
	std::string id = ".";
};
struct RawQuestion {
	std::string qH = "";
	std::string qC = "";
	std::map<char,std::string> rangeMap;
	std::vector<std::vector<std::string>> rawRules;
	Dewey dewey;
};
struct Question {
	std::string text = "";
	std::string comp = "";
	std::vector<std::vector<std::string>> rawRules;
	Dewey dewey;
};

struct Rule {
	std::string key = "";
	std::string operands = "";
	std::string out = "";
	std::string type = "";
	std::string explanation = "";
	std::vector<std::string> constraints;
	int score = 0;
	int k = 1000;
	int id;
};
struct Step {
	std::string next = "";
	int rule;
	int startNode;
	int endNode;
	std::vector<int> endNodes;
	std::vector<int> startNodes;
	std::map<char,std::string> partMap;
	
};
struct Answer {
	bool finished = false;
	bool correct = false;
	std::string next = "";
	std::string input = "";
	std::vector<Step> solution;
};
struct OperatorProxy
{
    int op = 0;
    Dewey dewey;
};

struct Number {
	int type = 0;
	std::string top = "";
	std::string bottom = "";
};
struct Range {
	std::vector<Number> left;
	std::vector<Number> right;
	std::vector<char> incexc;
};
struct Function {
	std::string var;
	std::string postfix;
	std::vector<int> rightIdx;
	std::vector<int> leftIdx;
};
struct KillNow {
	long maxTime; //in 1/1000000 of second
	long startTime;
	bool check() {
		auto nanos = std::chrono::high_resolution_clock::now().time_since_epoch();
		long nowTime = duration_cast<nanoseconds>(nanos).count();
		if (nowTime - startTime > maxTime){
			return false;
		}
		return true;
	}
};
std::map<std::string,Function> functionMap;
Range makeRange(std::string input);
Number solvePostfix(std::string postfix);
std::string outputNumber(Number n);
std::string substitute(std::string input);
std::string solveFunction(std::string input);
std::string numberType(std::string input);
Number mulTwo(Number numA, Number numB);
Number invertOne(Number numA);
Number negateOne(Number numA);
KillNow killNow;
inline bool operator>(const Number& a, const Number& b){
	if (a.type == 0 || b.type == 0){return false;}
	if (a.type == 1){
		if (b.type == 1){
			if (a.top.length()>b.top.length()){
				return true;
			}
			else if (a.top.length()<b.top.length()){
				return false;
			}
			else {
				int ii;
				for (ii=0;ii<a.top.length();ii++){
					if (a.top.at(ii) > b.top.at(ii)){
						return true;
					}
					else if (a.top.at(ii) < b.top.at(ii)){
						return false;
					}
				}
				return false;
			}
		}
		else if (b.type == 2 || b.type == 3){
			if (a.top.length()>b.top.length()){
				return true;
			}
			else {
				Number n;
				n.type = 2;
				n.top = a.top;
				n.bottom = "1";
				return n > b;
			}
		}
		else if (b.type < 0){
			return true;
		}
	}
	else if (a.type == 2 || a.type == 3){
		if (b.type == 1){
			if (a.top.length()<b.top.length()){
				return false;
			}
			else {
				Number n;
				n.type = 2;
				n.top = b.top;
				n.bottom = "1";
				return a > n;
			}
		}
		else if (b.type == 2 || b.type == 3){
			if (a.top.length() + b.bottom.length() > a.bottom.length()+b.top.length()+1){
				return true;
			}
			else if (a.top.length() + b.bottom.length() + 1 < a.bottom.length()+b.top.length()){
				return false;
			}
			else if (a.top == "0"){
				return false;
			}
			else if (b.top == "0"){
				return true;
			}
			else {
				Number n = mulTwo(a,invertOne(b));
				if (n.top.length()>n.bottom.length()){
					return true;
				}
				else if (n.top.length()<n.bottom.length()){
					return false;
				}
				else {
					int ii;
					for (ii=0;ii<n.top.length();ii++){
						if (n.top.at(ii) > n.bottom.at(ii)){
							return true;
						}
						else if (n.top.at(ii) < n.bottom.at(ii)){
							return false;
						}
					}
					return false;
				}
			}
		}
		else if (b.type < 0){
			return true;
		}
	}
	else if (a.type < 0){
		if (b.type < 0){
			return negateOne(b) > negateOne(a);
		}
		else if (b.type > 0){
			return false;
		}
	}
	return true;
}
inline bool operator<(const Number& a, const Number& b){
	if (a.type == 0 || b.type == 0){return false;}
	return b > a;
	/*
	if (a.type == 1){
		if (b.type == 1){
			if (a.top.length()<b.top.length()){
				return true;
			}
			else if (a.top.length()>b.top.length()){
				return false;
			}
			else {
				int ii;
				for (ii=0;ii<a.top.length();ii++){
					if (a.top.at(ii) < b.top.at(ii)){
						return true;
					}
					else if (a.top.at(ii) > b.top.at(ii)){
						return false;
					}
				}
				return false;
			}
		}
		else if (b.type == 2 || b.type == 3){
			if (a.top.length()<b.top.length()){
				return true;
			}
			else {
				Number n;
				n.type = 2;
				n.top = a.top;
				n.bottom = "1";
				return n < b;
			}
		}
		else if (b.type < 0){
			return false;
		}
	}
	else if (a.type == 2 || a.type == 3){
		if (b.type == 1){
			if (a.top.length()>b.top.length()){
				return false;
			}
			else {
				Number n;
				n.type = 2;
				n.top = b.top;
				n.bottom = "1";
				return a < n;
			}
		}
		else if (b.type == 2 || b.type == 3){
			if (a.top.length() + b.bottom.length() +1 < a.bottom.length()+b.top.length()){
				return true;
			}
			else if (a.top.length() + b.bottom.length() > a.bottom.length()+b.top.length() + 1){
				return false;
			}
			else if (b.top == "0"){
				return false;
			}
			else if (a.top == "0"){
				return true;
			}
			else {
				Number n = mulTwo(a,invertOne(b));
				if (n.top.length()<n.bottom.length()){
					return true;
				}
				else if (n.top.length()>n.bottom.length()){
					return false;
				}
				else {
					int ii;
					for (ii=0;ii<n.top.length();ii++){
						if (n.top.at(ii) < n.bottom.at(ii)){
							return true;
						}
						else if (n.top.at(ii) > n.bottom.at(ii)){
							return false;
						}
					}
					return false;
				}
			}
		}
		else if (b.type < 0){
			return false;
		}
	}
	else if (a.type < 0){
		if (b.type < 0){
			return negateOne(b) < negateOne(a);
		}
		else if (b.type > 0){
			return true;
		}
	}
	return true;
	*/
}
inline bool operator>=(const Number& a, const Number& b){
	if (a.type == 0 || b.type == 0){return false;}
	if (a < b){return false;}
	else {return true;}
}
inline bool operator<=(const Number& a, const Number& b){
	if (a.type == 0 || b.type == 0){return false;}
	if (a > b){return false;}
	else {return true;}
}
inline bool operator==(const Number& a, const Number& b){
	if (a.type == 0 || b.type == 0){return false;}
	if (a<b || a>b){
		return false;
	}
	return true;
}

std::map<std::string,Number> numbers;

OperatorProxy operator<(const Dewey& a, const OperatorProxy& b){
	OperatorProxy c;
	c.dewey = a;
	c.op = b.op;
	return c;
}
OperatorProxy subjectEq;
OperatorProxy topicEq;
OperatorProxy ruleEq;
OperatorProxy idEq;
OperatorProxy minEq;
inline bool operator>(const OperatorProxy& a, const Dewey& b){
	if (a.op == 0){
		if (a.dewey.subject == b.subject && a.dewey.topic == b.topic && a.dewey.lesson == b.lesson && a.dewey.id == b.id){
			return true;
		}
		return false;
	}
	else if (a.op == 1){
		if (a.dewey.subject == b.subject){
			return true;
		}
		return false;
	}
	else if (a.op == 2){
		if (a.dewey.subject == b.subject && a.dewey.topic == b.topic){
			return true;
		}
		return false;
	}
	else if (a.op == 3){
		if (a.dewey.subject == b.subject && a.dewey.topic == b.topic && a.dewey.lesson == b.lesson){
			return true;
		}
		return false;
	}
	else if (a.op == 4){
		if (a.dewey.subject == "." || b.subject == "."){
			return true;
		}
		else if (a.dewey.topic == "." || b.topic == "."){
			return (a.dewey <subjectEq> b);
		}
		else if (a.dewey.lesson == "." || b.lesson == "."){
			return (a.dewey <topicEq> b);
		}
		else if (a.dewey.id == "." || b.id == "."){
			return (a.dewey <ruleEq> b);
		}
		else {
			return (a.dewey <idEq> b);
		}
		return false;
	}
	
	return false;
}
std::vector<Step> applyRulesVectorOnePart(std::string onePart,std::vector<int> oneIndex, std::string userFullString, bool isCorrect);
Question currentQuestion;


std::map<std::string,std::vector<Rule>> rules;
std::map<int,Rule> ruleIndex;

std::map<std::string,std::map<std::string,std::vector<Rule>>> rulesMap;
std::map<std::string,std::map<int,Rule>> ruleIndexMap;

std::vector<char> dependentChars;
std::vector<char> dependentFunctions;
std::map<char,std::string> currentV;
int ridx;
std::map<std::string,std::vector<Rule>> answerConstraints;
std::string maxDepth;
std::string maxDepthn1;


std::string removeBracketsOne(std::string input) {
	std::map<int,int> operandToIndex;
	int iii; int iiii;
	bool foundBracket = false;
	bool foundAt = false;
	int idx = 0;
	int iidx = 0;
	std::vector<std::string> bracketStrings;
	std::string tempString = "";
	int bracketLength = 0;
	int secondIndex;
	char mychar;
	int len = input.length();
	for (iii=0;iii<len;iii++){
		mychar = input.at(iii);
		if (mychar == '{'){
			foundBracket = true;
			bracketLength = 1;
			secondIndex = iii;
		}
		else if (mychar == '}') {
			bracketStrings.push_back(tempString);
			bracketLength++;
			break;
		}
		else if (mychar == '#' && !foundBracket) {
			operandToIndex[idx]=iii;
			idx++;
		}
		else if (mychar == '_' && !foundBracket) {
			iidx++;
		}
		else if (mychar == '@' && !foundBracket) {
			foundAt = true;
		}
		else if (mychar == '@' && foundBracket) {
			//tempString += input.at(iii);
			bracketStrings.push_back(tempString);
			tempString = "";
			bracketLength++;
		}
		else if (foundBracket){
			tempString += mychar;
			bracketLength++;
		}
	}
	if (!foundBracket){
		return input;
	}
	
	int firstIndex = operandToIndex[iidx];
	//std::cout << input << " --a\n";
	input.replace(secondIndex,bracketLength+1,bracketStrings[1]);
	//std::cout << input << " --b\n";
	input.replace(firstIndex,1,bracketStrings[0]);
	//std::cout << input << " --c\n";
	if (killNow.check()){return input;}
	return removeBracketsOne(input);
	
	
	
}

std::string removeParOne(std::string input) {
	std::map<int,int> operandToIndex;
	int iii; int iiii;
	bool foundBracket = false;
	bool foundAt = false;
	int idx = 0;
	int iidx = 0;
	std::vector<std::string> bracketStrings;
	std::string tempString = "";
	int bracketLength = 0;
	int secondIndex;
	char mychar;
	int len = input.length();
	bool interiorBrackets = false;
	for (iii=0;iii<len;iii++){
		mychar = input.at(iii);
		if (mychar == '('){
			foundBracket = true;
			bracketLength = 1;
			secondIndex = iii;
		}
		else if (mychar == ')') {
			bracketStrings.push_back(tempString);
			bracketLength++;
			break;
		}
		else if (mychar == '{'){ //Must always be inside of a par
			interiorBrackets = true;
			tempString += mychar;
			bracketLength++;
		}
		else if (mychar == '}') {
			interiorBrackets = false;
			tempString += mychar;
			bracketLength++;
		}
		else if (mychar == '#' && !foundBracket && !interiorBrackets) {
			operandToIndex[idx]=iii;
			idx++;
		}
		else if (mychar == '_' && !foundBracket && !interiorBrackets) {
			iidx++;
		}
		else if (mychar == '@' && !foundBracket && !interiorBrackets) {
			foundAt = true;
		}
		else if (mychar == '@' && foundBracket && !interiorBrackets) {
			//tempString += input.at(iii);
			bracketStrings.push_back(tempString);
			tempString = "";
			bracketLength++;
		}
		else if (foundBracket){
			tempString += mychar;
			bracketLength++;
		}
	}
	if (!foundBracket){
		return input;
	}
	
	int firstIndex = operandToIndex[iidx];
	//std::cout << input << " --a\n";
	input.replace(secondIndex,bracketLength+1,bracketStrings[1]);
	//std::cout << input << " --b\n";
	input.replace(firstIndex,1,bracketStrings[0]);
	//std::cout << input << " --c\n";
	if (killNow.check()){return input;}
	return removeParOne(input);
	
	
	
}

std::string removeType11(std::string input) {
	std::map<int,int> operandToIndex;
	int iii; int iiii;
	bool foundAt = false;
	int idx = 0;
	int iidx = 0;
	std::string tempString = "";
	std::string leftString = "";
	std::string rightString = "";
	int bracketLength = 0;
	int secondIndex;
	char mychar;
	int len = input.length();
	bool foundBracket = false;
	for (iii=0;iii<len;iii++){
		mychar = input.at(iii);
		if (mychar == '#') {
			operandToIndex[idx]=iii;
			idx++;
		}
		else if (mychar == '_') {
			if (numbers.find(tempString) != numbers.end()){
				if (tempString == "e" || tempString == "\\pi" || tempString == "i"){
				
				}
				else {
					Number n = numbers[tempString];
					if (n.type == 11){
						std::vector<std::string> postfixedV = postfixifyVector(outputNumber(n),false);
						leftString = postfixedV[0];
						rightString = postfixedV[1];
						bracketLength = tempString.length();
						foundBracket = true;
						break;
					}
				}
			}
			iidx++;
			tempString = "";
			secondIndex = iii+1;
		}
		else if (mychar == '@') {
			tempString = "";
			foundAt = true;
			secondIndex = iii+1;
		}
		else {
			tempString += mychar;
		}
	}
	if (!foundBracket){
		return input;
	}
	
	int firstIndex = operandToIndex[iidx];
	std::string retInput = input;
	input.replace(secondIndex,bracketLength+1,rightString);
	input.replace(firstIndex,1,leftString);
	//return retInput;
	if (killNow.check()){return input;}
	return removeType11(input);
	
	
	
}

void grabFunction(std::string input){ //should have no brackets when inputting
	int iii;
	int len = input.length();
	std::string independentVar = "";
	std::string functionName = "";
	std::string postfix = "";
	int idx = 0;
	std::string currentOperand = "";
	if (len<4){return;}
	if (input.at(0) != '#' || input.at(1) != '#' || input.at(2) != -125 ){return;}
	std::map<int,int> operandMap;
	int iidx = 2;
	std::vector<int> varOperands;
	std::vector<int> rightIdx;
	std::vector<int> leftIdx;
	int diff = 3;
	for (iii=3;iii<len;iii++){
		if (input.at(iii) == '='){
			diff++;
		}
		else if (input.at(iii) == '@'){
			currentOperand += "@";
			postfix += currentOperand;
			currentOperand = "";
		}
		else if (input.at(iii) == '_'){
			if (idx == 0){
				functionName = currentOperand;
				diff += currentOperand.length()+1;
			}
			else if (idx == 1){
				independentVar = currentOperand;
				diff += currentOperand.length()+1;
			}
			else {
				if (currentOperand == independentVar){
					rightIdx.push_back(iii-diff-currentOperand.length());
					leftIdx.push_back(operandMap[idx]);
				}
				postfix += currentOperand + "_";
			}
			currentOperand = "";
			idx++;
			
		}
		else {
			currentOperand += input.at(iii);
			if (input.at(iii) == '#'){
				operandMap[iidx]=iii-diff;//skips 1st 3 chars
				iidx++;
			}
		}
	}
	Function f;
	f.var = independentVar;
	f.postfix = postfix;
	f.rightIdx = rightIdx;
	f.leftIdx = leftIdx;
	functionMap[functionName]=f;
}
std::string removeSolves(std::string input) {
	std::map<int,int> operandToIndex;
	int iii; int iiii;
	bool foundBracket = false;
	bool foundAt = false;
	int idx = 0;
	int iidx = 0;
	std::vector<std::string> bracketStrings;
	std::string tempString = "";
	int bracketLength = 0;
	int secondIndex;
	char mychar;
	int len = input.length();
	bool interiorBrackets = false;
	for (iii=0;iii<len;iii++){
		mychar = input.at(iii);
		if (mychar == '('){
			foundBracket = true;
			bracketLength = 1;
			secondIndex = iii;
		}
		else if (mychar == ')') {
			bracketStrings.push_back(tempString);
			bracketLength++;
			break;
		}
		else if (mychar == '{' && foundBracket){ //Must always be inside of a par
			interiorBrackets = true;
			tempString += mychar;
			bracketLength++;
		}
		else if (mychar == '}' && foundBracket) {
			interiorBrackets = false;
			tempString += mychar;
			bracketLength++;
		}
		else if (mychar == '{' && !foundBracket){ //Must always be inside of a par
			interiorBrackets = true;
		}
		else if (mychar == '}' && !foundBracket) {
			interiorBrackets = false;
		}
		else if (mychar == '#' && !foundBracket && !interiorBrackets) {
			operandToIndex[idx]=iii;
			idx++;
		}
		else if (mychar == '_' && !foundBracket && !interiorBrackets) {
			iidx++;
		}
		else if (mychar == '@' && !foundBracket && !interiorBrackets) {
			foundAt = true;
		}
		else if (mychar == '@' && foundBracket && !interiorBrackets) {
			//tempString += input.at(iii);
			bracketStrings.push_back(tempString);
			tempString = "";
			bracketLength++;
		}
		else if (foundBracket){
			tempString += mychar;
			bracketLength++;
		}
	}
	if (!foundBracket){
		return input;
	}
	
	int firstIndex = operandToIndex[iidx];
	std::string oldPostfix = bracketStrings[0] + "@" + bracketStrings[1];
	char solveType = '0';
	if (bracketStrings[0].at(0) >= 'A' && bracketStrings[0].at(0) <= 'Z'){
		solveType = bracketStrings[0].at(0);
		oldPostfix.replace(0,1,"");
	}
	oldPostfix = removeBracketsOne(oldPostfix);
	if (solveType == 'A'){
		//string_log("solving arithmetic");
		//int si;
		//for (si=0;si<oldPostfix.length();si++){
		//	std::string ssi(1,oldPostfix.at(si));
		//	string_log(ssi.c_str());
		//}
		oldPostfix = solveArithmetic(oldPostfix);
	}
	else if (solveType == 'R'){
		maxDigits = 2;
		oldPostfix = solveArithmetic(oldPostfix);
		maxDigits = -1;
	}
	else if (solveType == 'I'){
		oldPostfix = removeIdentities(oldPostfix);
	}
	else if (solveType == 'C'){
		oldPostfix = toCanonical(oldPostfix);
	}
	else if (solveType == 'S'){
		oldPostfix = doCalculus(oldPostfix);
	}
	else if (solveType == 'D'){
		grabFunction(oldPostfix);
	}
	
	std::string newLeft = "";
	std::string newRight = "";
	bool pastKey = false;
	for (iii=0;iii<oldPostfix.length();iii++){
		if (oldPostfix.at(iii)=='@'){
			pastKey = true;
		}
		else if (pastKey){
			newRight += oldPostfix.at(iii);
		}
		else {
			newLeft += oldPostfix.at(iii);
		}
	}
	input.replace(secondIndex,bracketLength+1,newRight);
	input.replace(firstIndex,1,newLeft);
	if (killNow.check()){return input;}
	return removeSolves(input);
	
	
	
}

std::string removeBORP(std::string input){
	int len = input.length();
	int iii;
	for (iii=0;iii<len;iii++){
		char mychar = input.at(iii);
		if (mychar == '{'){
			if (killNow.check()){return input;}
			std::string newInput = removeBracketsOne(input);
			if (killNow.check()){return newInput;}
			return removeBORP(newInput);
		}
		else if (mychar == '('){
			if (killNow.check()){return input;}
			std::string newInput = removeParOne(input);
			if (killNow.check()){return newInput;}
			return removeBORP(newInput);
		}
	}
	return input;
}

std::vector<char> getDependents(std::string second){
	int i;
	std::string currentOperand = "";
	std::vector<char> dependents;
	for (i=0;i<second.length();i++){
		if (second.at(i) == '_'){
			if (currentOperand.length() == 1 && currentOperand.at(0) >= 'A' && currentOperand.at(0) <= 'Z'){
				bool foundMatch = false; int ii;
				for (ii=0;ii<dependents.size();ii++){
					if (dependents[ii] == currentOperand.at(0)){
						foundMatch = true;
						break;
					}
				}
				if (!foundMatch){
					dependents.push_back(currentOperand.at(0));
				}
				
			}
			currentOperand = "";
		}
		else if (second.at(i) == '{' || second.at(i) == '}' || second.at(i) == '(' || second.at(i) == ')'){
			//skip these
		}
		else if (second.at(i) == '@'){
			currentOperand = "";
		}
		else {
			currentOperand += second.at(i);
		}
	}
	return dependents;
}

std::string removeDependents(std::string second){
	int i;
	std::string currentOperand = "";
	std::vector<char> dependents;
	std::string newsecond = "";
	for (i=0;i<second.length();i++){
		if (second.at(i) == '_'){
			if (currentOperand.length() == 1 && currentOperand.at(0) >= 'A' && currentOperand.at(0) <= 'Z'){
				if (currentV.find(currentOperand.at(0)) != currentV.end()){
					newsecond += "{"+currentV[currentOperand.at(0)]+"}_";
				}
				else {
					newsecond += currentOperand+"_";
				}
				
			}
			else {
				newsecond += currentOperand+"_";
			}
			currentOperand = "";
		}
		else if (second.at(i) == '@'){
			newsecond += currentOperand+"@";
			currentOperand = "";
		}
		else {
			currentOperand += second.at(i);
		}
	}
	return newsecond;
}

std::string fromOriginal(std::string input,std::map<int,std::string> originalMap) {
	int i;
	bool startOperands = false;
	std::vector<std::string> indexes;
	int currentOperator = 0;
	int startIndex = 0;
	for (i=0;i<input.length();i++){
		if (input.at(i) == '@'){
			startOperands = true;
			startIndex = i;
		}
		else if (startOperands){
			if (input.at(i) == '_'){
				indexes.push_back(std::to_string(startIndex+1));
				indexes.push_back(std::to_string(i - (startIndex+1)));
				indexes.push_back(originalMap[currentOperator]);
				currentOperator = 0;
				startIndex = i;
			}
			else {
				currentOperator = currentOperator*10 + (input.at(i) - '0');
			}
		}
	}
	for (i=indexes.size()/3-1;i>=0;i--){
		input.replace(std::stoi(indexes[i*3]),std::stoi(indexes[i*3+1]),indexes[i*3+2]);
	}
	return input;
}

std::map<int,int> removeParList(std::map<int,int> nodes, std::string input);

#include "latexify.cpp"

#include "postfixify.cpp"

#include "makerules.cpp"

#include "makequestions.cpp"

#include "makeanswers.cpp"

#include "applyrules.cpp"

#include "makenumbers.cpp"

std::string displayOne(Step step,std::string start,std::string end){
	std::map<char,std::string> partMap = step.partMap;
	if (step.rule < 0){
		return "";
	}
	std::string oneStep = "{\"start\":\""+latexOne(start,step.startNode,{})+"\",";
	std::string oldString = ruleIndex[step.rule].key + "@" + ruleIndex[step.rule].operands;
	
	oneStep += "\"input\":\""+latexOne(oldString)+"\",\"map\":[";

	for (std::map<char,std::string>::iterator iter = partMap.begin(); iter != partMap.end(); ++iter){
		std::string s(1,iter->first);
		std::string sec = iter->second;
		if (sec.length()>0 && sec.at(0) == '{'){
			sec = sec.substr(1,sec.length()-2);
			sec = latexOne(sec);
		}
		if (oneStep.at(oneStep.length()-1)=='['){
			oneStep += "\"" + s +"\",\""+ sec +"\"";
		}
		else {
			oneStep += ",\"" + s +"\",\""+ sec +"\"";
		}
		
	}
	oneStep += "],";
	oneStep += "\"output\":\""+latexOne(ruleIndex[step.rule].out)+"\",";
	int eNode = step.endNode;
	if (step.endNodes.size() > 0){
		eNode = step.endNodes[step.endNodes.size()-1];
	}
	oneStep += "\"final\":\""+latexOne(removeBracketsOne(end),eNode,{})+"\"}";
	
	return oneStep;
}

std::string outputTree(Step stepS,Step stepE){
	std::string pfstr = stepS.next;
	//std::cout << "pfstr: " << pfstr << " and ";
	int i; int ii; int iii;
	//for (i=0;i<stepS.startNodes.size();i++){
	//	std::cout << stepS.startNodes[i] << " ; ";
	//}
	//std::cout << "\n";
	std::vector<std::string> treeOptions;
	std::map<std::string,std::vector<std::string>> listMap;
	std::map<int,std::string> operandMap;
	std::map<int,std::string> originalMap;
	std::vector<std::string> finalList;
	std::vector<std::string> orderedKeyList;
	std::map<std::string,std::vector<std::string>> nodeList;
	std::string startNode = "";
	std::string endNode = "";
	std::map<std::string,bool> startNodes;
	std::map<std::string,bool> endNodes;
	
    
    
	
	int idx =0;
	bool startOperands = false;
	std::string currentOperator = "";
	int iidx = 0;
	bool midBrackets = false;
	for (i=0;i<pfstr.length();i++){
		if (pfstr.at(i) == '@'){
			startOperands = true;
		}
		else if (startOperands && !midBrackets){
			if (pfstr.at(i) == '_'){
				originalMap[iidx] = currentOperator;
				iidx++; 
				currentOperator = "";
			}
			else if (pfstr.at(i) == '{'){
				midBrackets = true;
				currentOperator += pfstr.at(i);
			}
			else {
				currentOperator += pfstr.at(i);
			}
		}
		else if (startOperands && midBrackets){
			if (pfstr.at(i) == '}'){
				midBrackets = false;
				currentOperator += pfstr.at(i);
			}
			else {
				currentOperator += pfstr.at(i);
			}
		}
	}
	

    
    
    
	int treeIdx = 0;
	//std::cout << "before third: " << pfstr << "\n";

	for (i=0;i<pfstr.length();i++){
		if (killNow.check()){return "killed";}
		if (pfstr.at(i) == '@'){
			break;
		}
		else if (pfstr.at(i) != '#'){
			std::string secondStr = "";
			std::string secondTtr = "";
			
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
					maxi = ii;
					break;
				}
			}
			std::string firstStr = "";
			std::string firstTtr = "";
			std::vector<std::string> fullTrees;
			
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
						break;
					}
				}
				
				
			}

			std::string fullStr = firstStr + secondStr + pfstr.at(i) + '@' + firstTtr + secondTtr;
			
			
			//Parent Node
			std::string opStr = "";
			opStr += pfstr.at(i);
			std::string name = "node"+std::to_string(treeIdx)+"f";
			if (i==stepS.startNode){startNode = name;}
			if (i==stepE.endNode){endNode = name;}
			for (ii=0;ii<stepS.startNodes.size();ii++){
				if (i==stepS.startNodes[ii]){
					startNodes[name]=true;
					break;
				}
			}
			for (ii=0;ii<stepE.endNodes.size();ii++){
				if (i==stepE.endNodes[ii]){
					endNodes[name]=true;
					break;
				}
			}
			treeIdx++;
			std::string parent = "";
			std::string nodeText = fullStr;
			std::string pname = name;
			nodeList[fullStr]={pname,parent,opStr};
			
			
			//Child 1
			nodeText = secondStr + '@' + secondTtr;
			if (nodeList.find(nodeText) != nodeList.end()){
				
				if (secondStr.at(secondStr.length()-1) == pfstr.at(i) && ( pfstr.at(i) == '+' || pfstr.at(i) == '*') ){
					std::vector<std::string> revList;
					for (std::map<std::string,std::vector<std::string>>::iterator iter = nodeList.begin(); iter != nodeList.end(); ++iter){
						if (iter->second[1] == nodeList[nodeText][0]){
							nodeList[iter->first][1] = pname;
							revList.push_back(iter->first);
						}
					}
					int okSz = orderedKeyList.size();
					for (ii=0;ii<okSz;ii++){
						for (iii=revList.size()-1;iii>=0;iii--){
							if (orderedKeyList[ii] == revList[iii]){
								orderedKeyList.push_back(revList[iii]);
							}
						}
					}
					
				}
				else {
					nodeList[nodeText][1] = pname;
					orderedKeyList.push_back(nodeText);
				}
				
			}
			else {
				//name = "node"+std::to_string(treeIdx)+"f";
				treeIdx++;
				if (secondStr.at(secondStr.length()-1) == pfstr.at(i) && ( pfstr.at(i) == '+' || pfstr.at(i) == '*')){
					std::vector<std::string> revList;
					for (std::map<std::string,std::vector<std::string>>::iterator iter = nodeList.begin(); iter != nodeList.end(); ++iter){
						if (iter->second[1] == name){
							nodeList[iter->first][1] = pname;
							revList.push_back(iter->first);
						}
					}
					int okSz = orderedKeyList.size();
					for (ii=0;ii<okSz;ii++){
						for (iii=revList.size()-1;iii>=0;iii--){
							if (orderedKeyList[ii] == revList[iii]){
								orderedKeyList.push_back(revList[iii]);
							}
						}
					}
				}
				else {
					nodeList[nodeText] = {name,pname,opStr};
					orderedKeyList.push_back(nodeText);
				}
				
			}
			
			if (firstStr.length() > 0){
				//Child 2
				nodeText = firstStr + '@' + firstTtr;
				if (nodeList.find(nodeText) != nodeList.end()){
					if (firstStr.at(firstStr.length()-1) == pfstr.at(i) && ( pfstr.at(i) == '+' || pfstr.at(i) == '*')){
						std::vector<std::string> revList;
						for (std::map<std::string,std::vector<std::string>>::iterator iter = nodeList.begin(); iter != nodeList.end(); ++iter){
							if (iter->second[1] == nodeList[nodeText][0]){
								nodeList[iter->first][1] = pname;
								revList.push_back(iter->first);
							}
						}
						int okSz = orderedKeyList.size();
						for (ii=0;ii<okSz;ii++){
							for (iii=revList.size()-1;iii>=0;iii--){
								if (orderedKeyList[ii] == revList[iii]){
									orderedKeyList.push_back(revList[iii]);
								}
							}
						}
					}
					else {
						nodeList[nodeText][1] = pname;
						orderedKeyList.push_back(nodeText);
					}
				
				}
				else {
					//name = "node"+std::to_string(treeIdx)+"f";
					treeIdx++;
					if (firstStr.at(firstStr.length()-1) == pfstr.at(i) && ( pfstr.at(i) == '+' || pfstr.at(i) == '*')){
						std::vector<std::string> revList;
						for (std::map<std::string,std::vector<std::string>>::iterator iter = nodeList.begin(); iter != nodeList.end(); ++iter){
							if (iter->second[1] == name){
								nodeList[iter->first][1] = pname;
								revList.push_back(iter->first);
							}
						}
						int okSz = orderedKeyList.size();
						for (ii=0;ii<okSz;ii++){
							for (iii=revList.size()-1;iii>=0;iii--){
								if (orderedKeyList[ii] == revList[iii]){
									orderedKeyList.push_back(revList[iii]);
								}
							}
						}
					}
					else {
						nodeList[nodeText] = {name,pname,opStr};
						orderedKeyList.push_back(nodeText);
					}
				
				}
				
			}
			orderedKeyList.push_back(fullStr);
			

			
			listMap[fullStr]={"#","_"};
			
		}
		else {
			listMap["#@" + std::to_string(idx) + "_"]={"#","_"};
			operandMap[i]=std::to_string(idx);
			
			std::string name = "node"+std::to_string(treeIdx);
			if (i==stepS.startNode){startNode = name;}
			if (i==stepE.endNode){endNode = name;}
			for (ii=0;ii<stepS.startNodes.size();ii++){
				if (i==stepS.startNodes[ii]){
					startNodes[name]=true;
					break;
				}
			}
			for (ii=0;ii<stepE.endNodes.size();ii++){
				if (i==stepE.endNodes[ii]){
					endNodes[name]=true;
					break;
				}
			}
			treeIdx++;
			nodeList["#@" + std::to_string(idx) + "_"] = {name,"","#"};
			orderedKeyList.push_back("#@" + std::to_string(idx) + "_");
			idx++;
		}
		
	}
		
	
	//std::cout << "\n\n---start Original-----\n";
	int iiii;
	
	//for (std::map<int,std::string>::iterator iter = originalMap.begin(); iter != originalMap.end(); ++iter){
	//	std::cout << iter->first << " and " << iter->second << '\n';
	//}
	

	//std::cout << " ENd bracketless\n";
	//for (std::map<int,std::string>::iterator iter = bracketlessMap.begin(); iter != bracketlessMap.end(); ++iter){
	//	std::cout << iter->first << " and " << iter->second << '\n';
	//}
	
	std::map<std::string,std::string> skipList;
	std::string nodes = "{";
	std::string allNodes = "[";
	//std::cout << "-DOJS-\nnodes = {};\n";
	
	std::vector<std::string> forLatex;
	
	for (ii=orderedKeyList.size()-1;ii>=0;ii--){
		//std::cout << "anything: " << orderedKeyList[ii] << " and node: " << nodeList[orderedKeyList[ii]][0] << "\n";
		if (skipList.find(orderedKeyList[ii]) != skipList.end()){
			//std::cout << "skip: " << nodeList[orderedKeyList[ii]][0] << "\n";
			continue;
		}
		else {
			skipList[orderedKeyList[ii]] = "";
		}
		
		std::string name = nodeList[orderedKeyList[ii]][0];
		std::string parent = nodeList[orderedKeyList[ii]][1];
		std::string postfix = fromOriginal(orderedKeyList[ii],originalMap);
		forLatex.push_back(name);
		forLatex.push_back(parent);
		forLatex.push_back(postfix);
		
		
	}
	std::map<std::string,std::string> latexMap =toLatex(forLatex);
	
	
	skipList.clear();
	for (ii=orderedKeyList.size()-1;ii>=0;ii--){
		if (skipList.find(orderedKeyList[ii]) != skipList.end()){
			//std::cout << "skip: " << nodeList[orderedKeyList[ii]][0] << "\n";
			continue;
		}
		else {
			skipList[orderedKeyList[ii]] = "";
		}
		
		std::string name = nodeList[orderedKeyList[ii]][0];
		std::string parent = nodeList[orderedKeyList[ii]][1];
		std::string postfix = fromOriginal(orderedKeyList[ii],originalMap);

		if (latexMap.find(name) != latexMap.end()){
			std::string outText = "\""+name + "\": {\"text\":";
			outText += "\"" + latexMap[name] + "\",";
			if (name == startNode){
				outText += "\"startNode\": true,";
			}
			else if (startNodes.find(name) != startNodes.end()){
				outText += "\"startNodes\": true,";
			}
			if (name == endNode){
				outText += "\"endNode\": true,";
			}
			else if (endNodes.find(name) != endNodes.end()){
				outText += "\"endNodes\": true,";
			}
			
			outText += "\"op\": \"" + nodeList[orderedKeyList[ii]][2] + "\",";
			outText += "\"parent\": \""+ parent + "\"}";
		

			if (nodes == "{"){
				nodes += outText;
			}
			else {
				nodes += ","+outText;
			}
			//std::cout << outText << "\n";
			if (allNodes == "["){
				allNodes += "\""+nodeList[orderedKeyList[ii]][0] + "\"";
			}
			else {
				allNodes += ",\""+nodeList[orderedKeyList[ii]][0] + "\"";
			}
		}
		
		
	}
	
	allNodes += "]";
	nodes += "}";
	
	std::string treeStr = "\"nodes\":"+nodes+",\"allNodes\":"+allNodes;
	//std::cout <<  treeStr << "\n";
	return treeStr;
}


bool firstCorrect;
#include "rules/identities.cpp"
#include "rules/arithmetic.cpp"
#include "rules/canonical.cpp"
#include "rules/calculus.cpp"


void initialRun(){
	prec['~'] = 101;
	prec['#'] = 100;
	int i;
	for (i=-128;i<0;i++){
		prec[i]=7;
	}
    prec['^'] = 5;
	prec['*'] = 4;
	prec['/'] = 4;
	prec['+'] = 3;
	prec['-'] = 3;
	prec['>'] = 2;
	prec['<'] = 2;
	prec['='] = 2;
	prec['!'] = 2;
	prec['['] = 2;
	prec[']'] = 2;
	prec[-94] = 2;//does not contain
	prec[-87] = 2;//contains
	prec[-111] = 2;//is
	prec[-110] = 2;//is not
	prec[-95] = 2;//in
	prec[-96] = 2;//not in
	prec['&'] = 1;
	prec['|'] = 1;
	prec['('] = -1;
	prec[')'] = -1;
	eloMap[1]=19956; eloMap[2]=16902; eloMap[3]=15097; eloMap[4]=13802; eloMap[5]=12788; eloMap[6]=11950; eloMap[7]=11234; eloMap[8]=10607; eloMap[9]=10048; eloMap[10]=9542; eloMap[11]=9080; eloMap[12]=8653; eloMap[13]=8256; eloMap[14]=7884; eloMap[15]=7533; eloMap[16]=7202; eloMap[17]=6886; eloMap[18]=6585; eloMap[19]=6297; eloMap[20]=6021; eloMap[21]=5754; eloMap[22]=5497; eloMap[23]=5248; eloMap[24]=5006; eloMap[25]=4771; eloMap[26]=4543; eloMap[27]=4320; eloMap[28]=4102; eloMap[29]=3889; eloMap[30]=3680; eloMap[31]=3475; eloMap[32]=3274; eloMap[33]=3076; eloMap[34]=2881; eloMap[35]=2688; eloMap[36]=2499; eloMap[37]=2311; eloMap[38]=2126; eloMap[39]=1943; eloMap[40]=1761; eloMap[41]=1581; eloMap[42]=1402; eloMap[43]=1224; eloMap[44]=1047; eloMap[45]=872; eloMap[46]=696; eloMap[47]=522; eloMap[48]=348; eloMap[49]=174; eloMap[50]=0; eloMap[51]=-174; eloMap[52]=-348; eloMap[53]=-522; eloMap[54]=-696; eloMap[55]=-872; eloMap[56]=-1047; eloMap[57]=-1224; eloMap[58]=-1402; eloMap[59]=-1581; eloMap[60]=-1761; eloMap[61]=-1943; eloMap[62]=-2126; eloMap[63]=-2311; eloMap[64]=-2499; eloMap[65]=-2688; eloMap[66]=-2881; eloMap[67]=-3076; eloMap[68]=-3274; eloMap[69]=-3475; eloMap[70]=-3680; eloMap[71]=-3889; eloMap[72]=-4102; eloMap[73]=-4320; eloMap[74]=-4543; eloMap[75]=-4771; eloMap[76]=-5006; eloMap[77]=-5248; eloMap[78]=-5497; eloMap[79]=-5754; eloMap[80]=-6021; eloMap[81]=-6297; eloMap[82]=-6585; eloMap[83]=-6886; eloMap[84]=-7202; eloMap[85]=-7533; eloMap[86]=-7884; eloMap[87]=-8256; eloMap[88]=-8653; eloMap[89]=-9080; eloMap[90]=-9542; eloMap[91]=-10048; eloMap[92]=-10607; eloMap[93]=-11234; eloMap[94]=-11950; eloMap[95]=-12788; eloMap[96]=-13802; eloMap[97]=-15097; eloMap[98]=-16902; eloMap[99]=-19956;
	overallScore = 0;
	subjectEq.op = 1; topicEq.op = 2; ruleEq.op = 3; idEq.op = 0; minEq.op = 4;
	maxDepth = "5";
	maxDepthn1 = "4";

	firstCorrect = false;
	auto t1 = std::chrono::high_resolution_clock::now();
	ridx = 0;
	std::vector<std::string> rows1 = createIdentities();
	makeRulesNew(rows1);
	rulesMap["identities"]=rules;
	ruleIndexMap["identities"]=ruleIndex;

	std::vector<std::string> rows2 = createArithmetic();
	makeRulesNew(rows2);
	rulesMap["arithmetic"]=rules;
	ruleIndexMap["arithmetic"]=ruleIndex;
	
	rules.clear();
	ruleIndex.clear();
	ridx = 0;
	makeRulesNew(rows1);
	std::vector<std::string> rows3 = createCanonical();
	makeRulesNew(rows3);
	rulesMap["canonical"]=rules;
	ruleIndexMap["canonical"]=ruleIndex;
	
	rules.clear();
	ruleIndex.clear();
	ridx = 0;
	makeRulesNew(rows1);
	makeRulesNew(rows2);
	std::vector<std::string> rows4 = createCalculus();
	makeRulesNew(rows4);
	rulesMap["calculus"]=rules;
	ruleIndexMap["calculus"]=ruleIndex;

	auto t2 = std::chrono::high_resolution_clock::now();
}

