#include "graphing.cpp"

std::string removeIdentities(std::string s){
	
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
	
	
	std::string newPostfix = removeBracketsOne(s);

	bool foundNext = true;
	while (foundNext){
		foundNext = false;
		std::vector<Step> someStrings = makeTree(newPostfix,1)[0];
		if (someStrings.size()>0){
			foundNext = true;
			newPostfix = removeBracketsOne(someStrings[0].next);
		}
	}
	return newPostfix;
}

std::string solveArithmetic(std::string s){
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
	int duration = std::chrono::duration_cast<std::chrono::microseconds>( a2 - a1 ).count();
	console_log(duration);
	
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
	while (foundNext){
		foundNext = false;
		std::vector<Step> someStrings = makeTree(newPostfix,1)[0];
		if (someStrings.size()>0){
			foundNext = true;
			newPostfix = removeBracketsOne(someStrings[0].next);
		}
	}
	return newPostfix;
}

std::string toCanonical(std::string s){
	auto a1 = std::chrono::high_resolution_clock::now();
	
	clearRules();
	rules = rulesMap["arithmetic"];
	ruleIndex = ruleIndexMap["arithmetic"];
	maxDepth = "4";
	maxDepthn1 = "3";
	//std::vector<std::string> rows = createCanonical();
	//makeRulesNew(rows);
	
	auto a2 = std::chrono::high_resolution_clock::now();
	int duration = std::chrono::duration_cast<std::chrono::microseconds>( a2 - a1 ).count();
	console_log(duration);
	
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
	while (foundNext){
		foundNext = false;
		std::vector<Step> someStrings = makeTree(newPostfix,1)[0];
		if (someStrings.size()>0){
			foundNext = true;
			newPostfix = removeBracketsOne(someStrings[0].next);
			maxDepth = "4";
			maxDepthn1 = "3";
		}
		else if (maxDepth == "4"){
			maxDepth = "5";
			maxDepthn1 = "4";
			foundNext = true;
		}
	}
	return newPostfix;
}



