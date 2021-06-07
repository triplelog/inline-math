#include "graphing.cpp"

std::string removeIdentities(std::string s, std::map<std::string, std::string>& followAMap){
	
	clearRules();
	rules = rulesMap["identities"];
	ruleIndex = ruleIndexMap["identities"];
	maxDepth = "4";
	maxDepthn1 = "3";
	//std::vector<std::string> rows = createIdentities();
	//makeRulesNew(rows);
	

	
	finishedAnswers.resize(0);
	answerListMap.clear();
	answerListMapF.clear();
	correctSolutionList.clear();
	incorrectSolutionList.clear();
	answerMap.clear();
	reverseMap.clear();
	reverseMapCorrect.clear();
	unfinishedOptions.clear();
	foundOneAnswer = false;
	startedWrong = false;

	std::string newPostfix = removeBracketsOne(s, followAMap);

	bool foundNext = true;
	int counter = 0;
	while (foundNext){
		if (killNow.check() || counter >100){
			return newPostfix;
		}
		foundNext = false;
		std::vector<Step> someStrings = makeTree(newPostfix,1)[0];
		if (someStrings.size()>0){
			foundNext = true;
			char rep = followAMap["original"].at(someStrings[0].startNode);
			std::string repText = std::string(someStrings[0].endNode-someStrings[0].startL+1,rep);
			followAMap["original"].replace(someStrings[0].startL,someStrings[0].startNode-someStrings[0].startL+1,repText);
			
			//std::map<std::string, std::string> followBMap;
			//followBMap["original"]=someStrings[0].next;
			newPostfix = removeBracketsOne(someStrings[0].next, followAMap);
		}
		counter++;
	}
	return newPostfix;
}

std::string solveArithmetic(std::string s, std::map<std::string, std::string>& followAMap){
	auto a1 = std::chrono::high_resolution_clock::now();
	
	clearRules();
	rules = rulesMap["arithmetic"];
	ruleIndex = ruleIndexMap["arithmetic"];
	maxDepth = "4";
	maxDepthn1 = "3";
	//std::vector<std::string> rows = createIdentities();
	//makeRulesNew(rows);
	//rows = createArithmetic();
	//makeRulesNew(rows);
	
	auto a2 = std::chrono::high_resolution_clock::now();
	int duration = std::chrono::duration_cast<std::chrono::milliseconds>( a2 - a1 ).count();
	//console_log(duration);
	
	finishedAnswers.resize(0);
	answerListMap.clear();
	answerListMapF.clear();
	correctSolutionList.clear();
	incorrectSolutionList.clear();
	answerMap.clear();
	reverseMap.clear();
	reverseMapCorrect.clear();
	unfinishedOptions.clear();
	foundOneAnswer = false;
	startedWrong = false;
	
	std::string newPostfix = removeBracketsOne(s, followAMap);
	
	if (2 ==2 ){
		std::string visOriginal = "";
		int iii;
		for (iii=0;iii<followAMap["original"].length();iii++){
			int s000 = followAMap["original"].at(iii);
			visOriginal += std::to_string(s000)+",";
		}
		string_log("NonZero5a");
		string_log(visOriginal.c_str());
	}
	
	bool foundNext = true;
	int counter = 0; int ii; int iii;
	while (foundNext){
		if (killNow.check() || counter >100){
			newPostfix = removeType11(newPostfix, followAMap);
			newPostfix = removeIdentities(newPostfix, followAMap);
			return newPostfix;
		}
		foundNext = false;
		std::vector<Step> someStrings = makeTree(newPostfix,10)[0];
		std::string newPostfixFollow = followAMap["original"];
		if (someStrings.size()>0){
			
			int minLeft = 1000;
			for (ii=0;ii<someStrings.size();ii++){
				std::map<std::string, std::string> followBMap;
				//followBMap["original"]=someStrings[ii].next;
				followBMap["original"]=followAMap["original"];
				char rep = followBMap["original"].at(someStrings[ii].startNode);
				std::string repText = std::string(someStrings[ii].endNode-someStrings[ii].startL+1,rep);
				followBMap["original"].replace(someStrings[ii].startL,someStrings[ii].startNode-someStrings[ii].startL+1,repText);
				
				std::string tempPF = removeBracketsOne(someStrings[ii].next, followBMap);
				for (iii=0;iii<tempPF.length();iii++){
					if (tempPF.at(iii)=='@'){
						if (iii<minLeft){
							foundNext = true;
							newPostfix = tempPF;
							newPostfixFollow=followBMap["original"];
							minLeft = iii;
							break;
						}
					}
				}
			}
		}
		followAMap["original"] = newPostfixFollow;
		counter++;
	}
	newPostfix = removeType11(newPostfix, followAMap);
	newPostfix = removeIdentities(newPostfix, followAMap);
	return newPostfix;
}

std::string toCanonical(std::string s){
	auto a1 = std::chrono::high_resolution_clock::now();
	
	clearRules();
	rules = rulesMap["canonical"];
	ruleIndex = ruleIndexMap["canonical"];
	maxDepth = "4";
	maxDepthn1 = "3";
	//std::vector<std::string> rows = createCanonical();
	//makeRulesNew(rows);
	
	auto a2 = std::chrono::high_resolution_clock::now();
	int duration = std::chrono::duration_cast<std::chrono::milliseconds>( a2 - a1 ).count();
	//console_log(duration);
	
	finishedAnswers.resize(0);
	answerListMap.clear();
	answerListMapF.clear();
	correctSolutionList.clear();
	incorrectSolutionList.clear();
	answerMap.clear();
	reverseMap.clear();
	reverseMapCorrect.clear();
	unfinishedOptions.clear();
	foundOneAnswer = false;
	startedWrong = false;
	
	std::map<std::string, std::string> followAMap;
	std::string newPostfix = removeBracketsOne(s, followAMap);

	bool foundNext = true;
	int counter = 0;
	while (foundNext){
		if (killNow.check() || counter >100){
			newPostfix = removeType11(newPostfix, followAMap);
			newPostfix = removeIdentities(newPostfix, followAMap);
			return newPostfix;
		}
		foundNext = false;
		std::vector<Step> someStrings = makeTree(newPostfix,1)[0];
		if (someStrings.size()>0){
			foundNext = true;
			newPostfix = removeBracketsOne(someStrings[0].next, followAMap);
		}
		else if (maxDepth == "4"){
			maxDepth = "5";
			maxDepthn1 = "4";
			foundNext = true;
		}
		counter++;
	}
	newPostfix = removeType11(newPostfix, followAMap);
	newPostfix = removeIdentities(newPostfix, followAMap);
	return newPostfix;
}

/*
std::string doCalculus(std::string s){
	auto a1 = std::chrono::high_resolution_clock::now();
	
	clearRules();
	rules = rulesMap["calculus"];
	ruleIndex = ruleIndexMap["calculus"];
	maxDepth = "4";
	maxDepthn1 = "3";
	//std::vector<std::string> rows = createCanonical();
	//makeRulesNew(rows);
	
	auto a2 = std::chrono::high_resolution_clock::now();
	int duration = std::chrono::duration_cast<std::chrono::milliseconds>( a2 - a1 ).count();
	//console_log(duration);
	
	finishedAnswers.resize(0);
	answerListMap.clear();
	answerListMapF.clear();
	correctSolutionList.clear();
	incorrectSolutionList.clear();
	answerMap.clear();
	reverseMap.clear();
	reverseMapCorrect.clear();
	unfinishedOptions.clear();
	foundOneAnswer = false;
	startedWrong = false;
	
	
	std::string newPostfix = removeBracketsOne(s);

	bool foundNext = true;
	int counter = 0; int ii; int iii;
	while (foundNext){
		if (killNow.check() || counter >100){
			newPostfix = removeType11(newPostfix);
			newPostfix = removeIdentities(newPostfix);
			return newPostfix;
		}
		foundNext = false;
		std::vector<Step> someStrings = makeTree(newPostfix,10)[0];
		if (someStrings.size()>0){
			
			
			int minLeft = 1000;
			for (ii=0;ii<someStrings.size();ii++){
				
				std::string tempPF = removeBracketsOne(someStrings[ii].next);
				for (iii=0;iii<tempPF.length();iii++){
					if (tempPF.at(iii)=='@'){
						if (iii<minLeft){
							foundNext = true;
							newPostfix = tempPF;
							minLeft = iii;
							break;
						}
					}
				}
			}
		}
		counter++;
	}
	
	newPostfix = removeType11(newPostfix);
	newPostfix = removeIdentities(newPostfix);
	return newPostfix;

}
*/


