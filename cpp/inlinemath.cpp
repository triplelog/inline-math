#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include <limits.h>
#include <time.h>
#include <string.h> 
#include <ctype.h>
#include <cmath>
#include <variant>
#include <map>
#include <numeric>
#include <chrono>
#include <thread>
#include <array>
#include <vector>
#include <unistd.h>
#include <thread>
#include <future>


using namespace std::chrono;
std::string solveArithmetic(std::string s);
std::string removeIdentities(std::string s);
std::string toCanonical(std::string s);
std::string doCalculus(std::string s);
std::vector<std::string> postfixifyVector(std::string input_str, bool checkComputations);
int maxDigits;
int exactDigits;
#include <emscripten/emscripten.h>

EM_JS(void, console_log, (int x), {
  console.log(x);
});

EM_JS(void, string_log, (const char* x), {
  console.log(UTF8ToString(x));
});

EM_JS(void, graph_svg, (const char* x), {
  addSVG(UTF8ToString(x));
});

EM_JS(void, output_latex, (const char* x), {
  addLatex(UTF8ToString(x));
});

EM_JS(void, output_dependents, (const char* x), {
  setDependents(UTF8ToString(x));
});

EM_JS(void, output_dependent_functions, (const char* x), {
  setDependentFunctions(UTF8ToString(x));
});

EM_JS(void, send_ready, (), {
  cpp_ready();
});

#include "partialstuff.cpp"


#include "removeIdentities.cpp"





extern "C" {

void MakeLesson(char* aa) {
	std::string a = std::string(aa);
	clearRules();
	oneLesson(a);
}

void OneRule(char* aa) {
	std::string a = std::string(aa);

	std::string postfixed = postfixify(a);
	std::vector<std::vector<Step>> steps = partialTree(postfixed);
	std::string jsonmessage = "[";
	int i;
	std::map<std::string,bool> uniqueSteps;
	int idx = 0;
	for (i=0;i<steps[0].size();i++){
		std::map<char,std::string> partMap = steps[0][i].partMap;
		if (steps[0][i].rule < 0){
			continue;
		}
		
		
		std::string oneStep = displayOne(steps[0][i],postfixed,steps[0][i].next);
		
		
		if (uniqueSteps.find(oneStep) == uniqueSteps.end()){
			if (idx ==0){
				jsonmessage += oneStep;
			}
			else {
				jsonmessage += ","+oneStep;
			}
			uniqueSteps[oneStep]=true;
			idx++;
		}
		
	}
	jsonmessage += "]";
	
}






void LatexIt(char* aa) {
	auto a1 = std::chrono::high_resolution_clock::now();
	std::string a = std::string(aa);
	char varName = ' ';
	if (a.length()>4 && a.at(0) == '|' && a.at(2) == ':' && a.at(3) == '='){
		
		varName = a.at(1);
		char* out = new char[1];
		out[0] = varName;
		out[1] = '\0';
		a = a.substr(4,a.length()-4);
	}
	
	dependentChars.clear();
	int i;
	for (i=0;i<a.length();i++){
		if (a.at(i) == '{'){
			a[i] = '(';
		}
		else if (a.at(i) == '}'){
			a[i] = ')';
		}
		else if (a.at(i) < 0){
			return;
		}
		else if (a.at(i) == '\\'){
			return;
		}
	}
	dependentFunctions.clear();
	std::vector<std::string> postfixedV = postfixifyVector(a,true);
	if (!checkPostfix(postfixedV[0]+"@"+postfixedV[1])){
		return;
	}
	int sz = dependentFunctions.size();
	char* df = new char[sz];
	for (i=0;i<sz;i++){
		df[i]=dependentFunctions[i];
	}
	df[sz]='\0';
	output_dependent_functions(df);
	//string_log("postfixing");
	//string_log(postfixedV[0].c_str());
	//string_log(postfixedV[1].c_str());
	
	dependentChars = getDependents(postfixedV[1]);
	sz = dependentChars.size();
	char* dc = new char[sz];
	for (i=0;i<sz;i++){
		dc[i]=dependentChars[i];
	}
	dc[sz]='\0';
	output_dependents(dc);
	

	postfixedV[1] = removeDependents(postfixedV[1]);
	//string_log(postfixedV[1].c_str());
	std::string postfixed = postfixedV[0]+"@"+postfixedV[1];
	//string_log("postfixed");
	//int si;
	//for (si=0;si<postfixed.length();si++){
	//	std::string ssi(1,postfixed.at(si));
	//	string_log(ssi.c_str());
	//}
	postfixed = removeSolves(postfixed);
	//string_log("solved");
	//for (si=0;si<postfixed.length();si++){
	//	std::string ssi(1,postfixed.at(si));
	//	string_log(ssi.c_str());
	//}
	postfixed = removeBracketsOne(postfixed);
	
	//string_log(postfixed.c_str());
	if (varName >= 'A' && varName <= 'Z'){
		currentV[varName]=removeBORP(postfixed);
	}
	
	
	
	//console_log(sz);
	//std::string noIdentities = removeIdentities(postfixed);
	
	//std::string noIdentities = solveArithmetic(postfixed);
	
	//std::string noIdentities = toCanonical(postfixed);
	
	//std::string noIdentities = doCalculus(postfixed);
	
	std::string latexed = latexOne(postfixed);
	postfixed = "\0";
	//noIdentities = "\0";
	latexed += "\0";
	output_latex(latexed.c_str());
	latexed = "\0";
	auto a2 = std::chrono::high_resolution_clock::now();
	int duration = std::chrono::duration_cast<std::chrono::microseconds>( a2 - a1 ).count();

	//console_log(duration);
}

void TreeIt(char* aa) {
	auto a1 = std::chrono::high_resolution_clock::now();
	std::string a = std::string(aa);
	char varName = ' ';
	if (a.length()>4 && a.at(0) == '|' && a.at(2) == ':' && a.at(3) == '='){
		
		varName = a.at(1);
		char* out = new char[1];
		out[0] = varName;
		out[1] = '\0';
		a = a.substr(4,a.length()-4);
	}
	
	dependentChars.clear();
	int i;
	for (i=0;i<a.length();i++){
		if (a.at(i) == '{'){
			a[i] = '(';
		}
		else if (a.at(i) == '}'){
			a[i] = ')';
		}
		else if (a.at(i) < 0){
			return;
		}
		else if (a.at(i) == '\\'){
			return;
		}
	}
	dependentFunctions.clear();
	std::vector<std::string> postfixedV = postfixifyVector(a,true);
	int sz = dependentFunctions.size();
	char* df = new char[sz];
	for (i=0;i<sz;i++){
		df[i]=dependentFunctions[i];
	}
	df[sz]='\0';
	output_dependent_functions(df);
	
	
	dependentChars = getDependents(postfixedV[1]);
	sz = dependentChars.size();
	char* dc = new char[sz];
	for (i=0;i<sz;i++){
		dc[i]=dependentChars[i];
	}
	dc[sz]='\0';
	output_dependents(dc);
	

	postfixedV[1] = removeDependents(postfixedV[1]);
	//string_log(postfixedV[1].c_str());
	std::string postfixed = postfixedV[0]+"@"+postfixedV[1];
	string_log(postfixed.c_str());
	
	
	postfixed = removeSolves(postfixed);
	//string_log(postfixed.c_str());
	postfixed = removeBracketsOne(postfixed);
	
	
	Step step;
	step.next = postfixed;
	step.rule = 0;
	step.startNode = 0;
	step.endNode = 0;
	//std::vector<int> endNodes;
	//std::vector<int> startNodes;
	//std::map<char,std::string> partMap;
	std::string treeStr = outputTree(step,step);
	
	
	//string_log(postfixed.c_str());
	if (varName >= 'A' && varName <= 'Z'){
		currentV[varName]=removeBORP(postfixed);
	}
	

	postfixed = "\0";
	//noIdentities = "\0";
	treeStr += "\0";
	output_latex(treeStr.c_str());
	treeStr = "\0";
	auto a2 = std::chrono::high_resolution_clock::now();
	int duration = std::chrono::duration_cast<std::chrono::microseconds>( a2 - a1 ).count();

	//console_log(duration);
}

void PlotIt(char* aa,double left,double right, double bottom, double top) {
	auto a1 = std::chrono::high_resolution_clock::now();
	std::string fn = std::string(aa);
	std::string iV = "x";
	std::string dV = "y";
	if (fn.length()>2){
		if (fn.at(0)=='y' && fn.at(1) == '='){
			fn = fn.substr(2,fn.length()-2);
		}
		else if (fn.at(0)=='x' && fn.at(1) == '='){
			fn = fn.substr(2,fn.length()-2);
			iV = "y";
			dV = "x";
		}
		else {
			fn = fn;
		}
	}
	
	
	dependentChars.clear();
	int i;
	for (i=0;i<fn.length();i++){
		if (fn.at(i) == '{'){
			fn[i] = '(';
		}
		else if (fn.at(i) == '}'){
			fn[i] = ')';
		}
		else if (fn.at(i) < 0){
			return;
		}
		else if (fn.at(i) == '\\'){
			return;
		}
	}
	dependentFunctions.clear();
	std::vector<std::string> postfixedV = postfixifyVector(fn,true);
	int sz = dependentFunctions.size();
	char* df = new char[sz];
	for (i=0;i<sz;i++){
		df[i]=dependentFunctions[i];
	}
	df[sz]='\0';
	output_dependent_functions(df);
	
	dependentChars = getDependents(postfixedV[1]);
	sz = dependentChars.size();
	char* dc = new char[sz];
	for (i=0;i<sz;i++){
		dc[i]=dependentChars[i];
	}
	dc[sz]='\0';
	output_dependents(dc);
	
	postfixedV[1] = removeDependents(postfixedV[1]);
	
	std::string postfixed = postfixedV[0]+"@"+postfixedV[1];
	
	
	postfixed = removeSolves(postfixed);
	//string_log(postfixed.c_str());
	postfixed = removeBracketsOne(postfixed);
	
	postfixedV[0] = "";
	postfixedV[1] = "";
	bool isRight = false;
	for (i=0;i<postfixed.length();i++){
		if (postfixed.at(i)=='@'){
			isRight = true;
		}
		else if (isRight){
			postfixedV[1] += postfixed.at(i);
		}
		else {
			postfixedV[0] += postfixed.at(i);
		}
	}
	
	std::string plot = makeGraph(postfixedV,iV,dV,left,right,bottom,top);
	plot += "\0";
	graph_svg(plot.c_str());
	plot = "\0";
	auto a2 = std::chrono::high_resolution_clock::now();
	int duration = std::chrono::duration_cast<std::chrono::microseconds>( a2 - a1 ).count();

	
	console_log(duration);
}

void AddRules(char* aa,char* bb) {
	auto a1 = std::chrono::high_resolution_clock::now();
	
	std::string ruleType = std::string(aa);
	int i;
	std::vector<std::string> ruleText;
	std::string oneLine = "";
	for (i =0;bb[i] != '\0';i++){
		if (bb[i] == '\n'){
			ruleText.push_back(oneLine);
			oneLine = "";
		}
		else {
			oneLine += bb[i];
		}
	}
	if (oneLine != ""){
		ruleText.push_back(oneLine);
		oneLine = "";
	}
	
	if (ruleType == "identities"){
		rules = rulesMap["identities"];
		ruleIndex = ruleIndexMap["identities"];
		ridx = rules.size();
		makeRulesNew(ruleText);
		rulesMap["identities"]=rules;
		ruleIndexMap["identities"]=ruleIndex;
	}
	else if (ruleType == "arithmetic"){
		rules.clear();
		ruleIndex.clear();
		ridx = 0;
		std::vector<std::string> rows1 = createIdentities();
		makeRulesNew(rows1);

		std::vector<std::string> rows2 = createArithmetic();
		makeRulesNew(rows2);
		makeRulesNew(ruleText);
		rulesMap["arithmetic"]=rules;
		ruleIndexMap["arithmetic"]=ruleIndex;
	}
	else if (ruleType == "canonical"){
		rules.clear();
		ruleIndex.clear();
		ridx = 0;
		std::vector<std::string> rows1 = createIdentities();
		makeRulesNew(rows1);
		std::vector<std::string> rows3 = createCanonical();
		makeRulesNew(rows3);
		
		makeRulesNew(ruleText);
		rulesMap["canonical"]=rules;
		ruleIndexMap["canonical"]=ruleIndex;
	}
	else if (ruleType == "calculus"){
		rules.clear();
		ruleIndex.clear();
		ridx = 0;
		std::vector<std::string> rows1 = createIdentities();
		makeRulesNew(rows1);
		std::vector<std::string> rows2 = createArithmetic();
		makeRulesNew(rows2);
		std::vector<std::string> rows4 = createCalculus();
		makeRulesNew(rows4);
		
		makeRulesNew(ruleText);
		rulesMap["calculus"]=rules;
		ruleIndexMap["calculus"]=ruleIndex;
	}
	
	
	auto a2 = std::chrono::high_resolution_clock::now();
	int duration = std::chrono::duration_cast<std::chrono::microseconds>( a2 - a1 ).count();

	
	console_log(duration);
}

}




int main() {
	//std::string jsonmessage = "var rule = {};";
	srand(time(NULL));
	maxDigits = -1;
	exactDigits = -1;
	initialRun();
	send_ready();
	return 1;
}

