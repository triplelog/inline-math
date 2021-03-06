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
std::string solveArithmetic(std::string s, std::map<std::string,std::string>& followAMap);
std::string removeIdentities(std::string s, std::map<std::string,std::string>& followAMap);
std::string toCanonical(std::string s);
std::string doCalculus(std::string s);
std::vector<std::string> postfixifyVector(std::string input_str, bool checkComputations, std::map<std::string,std::string>& followAMap);
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

EM_JS(void, output_imcss, (const char* x), {
  addImcss(UTF8ToString(x));
});

EM_JS(void, output_input, (const char* x), {
  addInput(UTF8ToString(x));
});

EM_JS(void, output_inputted, (const char* x), {
  addInputted(UTF8ToString(x));
});

EM_JS(void, output_dependents, (const char* x), {
  setDependents(UTF8ToString(x));
});

EM_JS(void, add_dependent_function, (const char* x), {
  addDependentFunction(UTF8ToString(x));
});

EM_JS(void, update_currentF, (const char* x), {
  updateCurrentFunctions(UTF8ToString(x));
});

EM_JS(void, send_ready, (), {
  cpp_ready();
});


#include "partialstuff.cpp"


#include "removeIdentities.cpp"



std::string prepareIt(std::string a, std::map<std::string,std::string>& followAMap){
	dependentChars.clear();
	int i;
	if (a.length()>254){
		return "error";
	}
	
	int openPar = 0;
	int sz = followAMap["original"].length();
	
	for (i=sz;i<a.length();i++){
		followAMap["original"]+='0';
	}
	for (i=0;i<a.length();i++){
		if (a.at(i) == '{'){
			a[i] = '(';
			openPar++;
		}
		else if (a.at(i) == '}'){
			a[i] = ')';
			openPar--;
		}
		else if (a.at(i) == '('){
			openPar++;
		}
		else if (a.at(i) == ')'){
			openPar--;
		}
		else if (a.at(i) < 0){
			return "error";
		}
		else if (a.at(i) == '\\'){
			if (i+2 < a.length() && a.at(i+1) == 'p' && a.at(i+2) == 'm'){
				if (i==0){
					a = "0"+a;
					followAMap["original"] = "0"+followAMap["original"];
				}
				else if (a.at(i-1)=='='){
					a.replace(i,0,"0");
					followAMap["original"].replace(i,0,"0");
				}
				else if (a.at(i-1)=='('){
					a.replace(i,0,"0");
					followAMap["original"].replace(i,0,"0");
				}
				else if (i>1 && a.at(i-1)== ' '){
					if (a.at(i-2)=='='){
						a.replace(i,0,"0");
						followAMap["original"].replace(i,0,"0");
					}
					else if (a.at(i-2)=='('){
						a.replace(i,0,"0");
						followAMap["original"].replace(i,0,"0");
					}
				}
			}
			else {
				return "error";
			}
		}
	}
	dependentFunctions.resize(0);
	while (openPar < 0){
		a.replace(0,0,"(");
		followAMap["original"].replace(0,0,"0");
		openPar++;
	}
	while (openPar > 0){
		a.replace(a.length()-1,0,")");
		followAMap["original"].replace(a.length()-1,0,"0");
		openPar--;
	}
	
	
	
	std::vector<std::string> postfixedV = postfixifyVector(a,true,followAMap);
	string_log("postfixed");
	string_log(postfixedV[0].c_str());
	if (!checkPostfix(postfixedV[0]+"@"+postfixedV[1])){
		return "error"+postfixedV[0]+"@"+postfixedV[1];
	}
	sz = dependentFunctions.size();
	

	for (i=0;i<sz;i++){
		//string_log(dependentFunctions[i].c_str());
		add_dependent_function(dependentFunctions[i].c_str());
	}
	dependentFunctions.resize(0);

	
	dependentChars = getDependents(postfixedV[1]);
	

	
	sz = dependentChars.size();
	char* dc = new char[sz];
	for (i=0;i<sz;i++){
		dc[i]=dependentChars[i];
	}
	dc[sz]='\0';
	output_dependents(dc);
	
	if (!checkPostfix(postfixedV[0]+"@"+postfixedV[1])){
		return "error"+postfixedV[0]+"@"+postfixedV[1];
	}

	postfixedV[1] = removeDependents(postfixedV[1]);
	if (!checkPostfix(postfixedV[0]+"@"+postfixedV[1])){
		return "error"+postfixedV[0]+"@"+postfixedV[1];
	}
	//string_log(postfixedV[1].c_str());
	std::string postfixed = postfixedV[0]+"@"+postfixedV[1];
	//string_log("postfixed");
	//int si;
	//for (si=0;si<postfixed.length();si++){
	//	std::string ssi(1,postfixed.at(si));
	//	string_log(ssi.c_str());
	//}
	
	
	
	
	postfixed = removeSolves(postfixed, followAMap["original"]);
	
	
	
	
	if (!checkPostfix(postfixed)){
		return "error"+postfixed;
	}

	postfixed = removeBracketsOne(postfixed, followAMap);
	if (!checkPostfix(postfixed)){
		return "error"+postfixed;
	}
	
	
	return postfixed;
}


extern "C" {

void MakeLesson(char* aa) {
	std::string a = std::string(aa);
	clearRules();
	oneLesson(a);
}

void OneRule(char* aa) {
	std::string a = std::string(aa);
	std::map<std::string,std::string> followAMap;
	std::string postfixed = postfixify(a,followAMap);
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



void ImcssIt(char* aa) {
	auto a1 = std::chrono::high_resolution_clock::now();
	auto nanos = a1.time_since_epoch();
	killNow.startTime = duration_cast<std::chrono::milliseconds>(nanos).count();
	std::string a = std::string(aa);
	char varName = ' ';
	if (a.length()>4 && a.at(0) == '|' && a.at(2) == ':' && a.at(3) == '='){
		
		varName = a.at(1);
		char* out = new char[1];
		out[0] = varName;
		out[1] = '\0';
		a = a.substr(4,a.length()-4);
	}
	std::map<std::string, std::string> followAMap;
	followAMap["original"]="";
	int i;
	for (i=0;i<a.length();i++){
		char c = i+1;
		if (i > 126){
			c = i - 256;
		}
		followAMap["original"]+=c;
	}
	std::string postfixed = prepareIt(a, followAMap);
	if (postfixed.substr(0,5) == "error"){
		std::string latexed = latexOne(postfixed.substr(5));
		latexed += "\0";
		output_latex(latexed.c_str());
		output_inputted(codify(postfixed.substr(5)).c_str());
		postfixed = "\0";
		latexed = "\0";
		return;
	}
	//string_log(postfixed.c_str());
	if (varName >= 'A' && varName <= 'Z'){
		currentV[varName]=removeBORP(postfixed, followAMap);
	}
	
	
	std::string imcssed = imcssOne(postfixed, followAMap["original"], a);
	
	//noIdentities = "\0";
	imcssed += "\0";
	output_imcss(imcssed.c_str());
	output_inputted(codify(postfixed).c_str());
	postfixed = "\0";
	imcssed = "\0";
	auto a2 = std::chrono::high_resolution_clock::now();
	int duration = std::chrono::duration_cast<std::chrono::milliseconds>( a2 - a1 ).count();

	console_log(duration);
}

void InputIt(char* aa) {
	auto a1 = std::chrono::high_resolution_clock::now();
	auto nanos = a1.time_since_epoch();
	killNow.startTime = duration_cast<std::chrono::milliseconds>(nanos).count();
	std::string a = std::string(aa);
	std::string charred = charredPost(a);
	std::string newInput = inputifyOne(charred);
	output_input(newInput.c_str());
	auto a2 = std::chrono::high_resolution_clock::now();
	int duration = std::chrono::duration_cast<std::chrono::milliseconds>( a2 - a1 ).count();

	console_log(duration);
}

void LatexIt(char* aa) {
	auto a1 = std::chrono::high_resolution_clock::now();
	auto nanos = a1.time_since_epoch();
	killNow.startTime = duration_cast<std::chrono::milliseconds>(nanos).count();
	std::string a = std::string(aa);
	char varName = ' ';
	if (a.length()>4 && a.at(0) == '|' && a.at(2) == ':' && a.at(3) == '='){
		
		varName = a.at(1);
		char* out = new char[1];
		out[0] = varName;
		out[1] = '\0';
		a = a.substr(4,a.length()-4);
	}
	std::map<std::string, std::string> followAMap;
	followAMap["original"]="";
	int i;
	for (i=0;i<a.length();i++){
		char c = i+1;
		if (i > 126){
			c = i - 256;
		}
		followAMap["original"]+=c;
	}
	
	std::string postfixed = prepareIt(a, followAMap);
	
	if (postfixed.substr(0,5) == "error"){
		std::string latexed = latexOne(postfixed.substr(5));
		latexed += "\0";
		output_latex(latexed.c_str());
		output_inputted(codify(postfixed.substr(5)).c_str());
		postfixed = "\0";
		latexed = "\0";
		return;
	}
	//string_log(postfixed.c_str());
	if (varName >= 'A' && varName <= 'Z'){
		currentV[varName]=removeBORP(postfixed, followAMap);
	}
	
	
	std::string latexed = latexOne(postfixed);
	
	//noIdentities = "\0";
	latexed += "\0";
	output_latex(latexed.c_str());
	output_inputted(codify(postfixed).c_str());
	postfixed = "\0";
	latexed = "\0";
	auto a2 = std::chrono::high_resolution_clock::now();
	int duration = std::chrono::duration_cast<std::chrono::milliseconds>( a2 - a1 ).count();

	console_log(duration);
}

void TreeIt(char* aa) {
	auto a1 = std::chrono::high_resolution_clock::now();
	auto nanos = a1.time_since_epoch();
	killNow.startTime = duration_cast<std::chrono::milliseconds>(nanos).count();
	std::string a = std::string(aa);
	char varName = ' ';
	if (a.length()>4 && a.at(0) == '|' && a.at(2) == ':' && a.at(3) == '='){
		
		varName = a.at(1);
		char* out = new char[1];
		out[0] = varName;
		out[1] = '\0';
		a = a.substr(4,a.length()-4);
	}
	std::map<std::string, std::string> followAMap;
	followAMap["original"]="";
	int i;
	for (i=0;i<a.length();i++){
		char c = i+1;
		if (i > 126){
			c = i - 256;
		}
		followAMap["original"]+=c;
	}
	std::string postfixed = prepareIt(a, followAMap);

	if (postfixed.substr(0,5) == "error"){
		postfixed = "\0";
		output_latex("???");
		return;
	}
	
	
	Step step;
	step.next = postfixed;
	step.rule = 0;
	step.startNode = 0;
	step.endNode = 0;
	//std::vector<int> endNodes;
	//std::vector<int> startNodes;
	//std::map<char,std::string> partMap;
	std::string treeStr = outputTree(step,step);
	if (treeStr == "killed"){
		postfixed = "\0";
		//noIdentities = "\0";
		treeStr += "\0";
		output_latex("???");
		treeStr = "\0";
		return;
	}
	
	//string_log(postfixed.c_str());
	if (varName >= 'A' && varName <= 'Z'){
		currentV[varName]=removeBORP(postfixed, followAMap);
	}
	

	postfixed = "\0";
	//noIdentities = "\0";
	treeStr += "\0";
	output_latex(treeStr.c_str());
	treeStr = "\0";
	auto a2 = std::chrono::high_resolution_clock::now();
	int duration = std::chrono::duration_cast<std::chrono::milliseconds>( a2 - a1 ).count();

	//console_log(duration);
}

void PlotIt(char* aa,double left,double right, double bottom, double top) {
	auto a1 = std::chrono::high_resolution_clock::now();
	auto nanos = a1.time_since_epoch();
	killNow.startTime = duration_cast<std::chrono::milliseconds>(nanos).count();
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
	
	int i;
	std::map<std::string, std::string> followAMap;
	followAMap["original"]="";
	for (i=0;i<fn.length();i++){
		char c = i+1;
		if (i > 126){
			c = i - 256;
		}
		followAMap["original"]+=c;
	}
	std::string postfixed = prepareIt(fn, followAMap);

	if (postfixed.substr(0,5) == "error"){
		postfixed = "\0";
		graph_svg("???");
		return;
	}
	
	std::vector<std::string> postfixedV;
	postfixedV.push_back("");
	postfixedV.push_back("");
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
	output_inputted(codify(postfixedV[0]+"@"+postfixedV[1]).c_str());
	output_latex(latexOne(postfixedV[0]+"@"+postfixedV[1]).c_str());
	graph_svg(plot.c_str());
	plot = "\0";
	postfixedV[0] = "\0";
	postfixedV[1] = "\0";
	postfixedV.resize(0);
	auto a2 = std::chrono::high_resolution_clock::now();
	int duration = std::chrono::duration_cast<std::chrono::milliseconds>( a2 - a1 ).count();

	
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
	int duration = std::chrono::duration_cast<std::chrono::milliseconds>( a2 - a1 ).count();

	
	console_log(duration);
}

}//end extern C


void setHTMLcodes() {
	greekHTML["\\pi"]="&pi;";
	greekHTML["\\alpha"]="&alpha;";
	greekHTML["\\beta"]="&beta;";
	greekHTML["\\gamma"]="&gamma;";
	greekHTML["\\delta"]="&delta;";
	greekHTML["\\epsilon"]="&epsilon;";
	greekHTML["\\zeta"]="&zeta;";
	greekHTML["\\eta"]="&eta;";
	greekHTML["\\theta"]="&theta;";
	greekHTML["\\iota"]="&iota;";
	greekHTML["\\kappa"]="&kappa;";
	greekHTML["\\lambda"]="&lambda;";
	greekHTML["\\mu"]="&mu;";
	greekHTML["\\nu"]="&nu;";
	greekHTML["\\xi"]="&xi;";
	greekHTML["\\omicron"]="&omicron;";
	greekHTML["\\rho"]="&rho;";
	greekHTML["\\sigma"]="&sigma;";
	greekHTML["\\tau"]="&tau;";
	greekHTML["\\upsilon"]="&upsilon;";
	greekHTML["\\phi"]="&phi;";
	greekHTML["\\chi"]="&chi;";
	greekHTML["\\psi"]="&psi;";
	greekHTML["\\omega"]="&omega;";
}


int main() {
	//std::string jsonmessage = "var rule = {};";
	srand(time(NULL));
	auto a1 = std::chrono::high_resolution_clock::now();
	auto nanos = a1.time_since_epoch();
	killNow.startTime = duration_cast<std::chrono::milliseconds>(nanos).count();
	killNow.maxTime = 3142; //milliseconds: 1 thousandth of second
	maxDigits = -1;
	exactDigits = -1;
	initialRun();
	auto a2 = std::chrono::high_resolution_clock::now();
	int duration = std::chrono::duration_cast<std::chrono::milliseconds>( a2 - a1 ).count();
	console_log(duration);
	send_ready();
	setHTMLcodes();
	return 1;
}

