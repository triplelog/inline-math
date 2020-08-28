

std::string RemoveIdentities(std::string s){
	
	clearRules();
	std::vector<std::string> rows = createIdentities();
	makeRulesNew(rows);
	
	v8::Isolate* isolate = info.GetIsolate();
	v8::String::Utf8Value s(isolate, info[0]);
	std::string filen(*s);
	
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
	maxSteps = 25;
	
	auto a1 = std::chrono::high_resolution_clock::now();
	maxFound = 0;
	
	//std::cout << "mf:" << maxFound << " times: " << duration1 << " and " << duration2 << " and " << duration3 << "\n";
	
	std::string error = fullAnswer(currentQuestion.comp,filen);
	
	
	auto a2 = std::chrono::high_resolution_clock::now();
	duration3 += std::chrono::duration_cast<std::chrono::microseconds>( a2 - a1 ).count();
	//std::cout << "times: " << duration1 << " and " << duration2 << " and " << duration3 << "\n";
	
	
	std::string newPostfix = removeBracketsOne(s);
	//std::cout << "\n\nStarting the Loop @$*&^@$*&^@*$&^@*$&^\n\n";
	
	auto a1 = std::chrono::high_resolution_clock::now();
	
	//maxSteps = 5;
	//getAnswerList(newPostfix,0);
	maxSteps = 15;
	getAnswerList(newPostfix,0);
	//maxSteps = 15;
	//getAnswerList(newPostfix,0);
	auto a2 = std::chrono::high_resolution_clock::now();
	//std::cout << "\n\n\n\nCompleted the InCorrect Loop @$*&^@$*&^@*$&^@*$&^\n\n\n\n" << " and " << std::chrono::duration_cast<std::chrono::microseconds>( a2 - a1 ).count() << "\n\n\n";
	//std::cout << "total answers: "<< totalAnswers << "\n";
	//duration2 += std::chrono::duration_cast<std::chrono::microseconds>( a2 - a1 ).count();
	//std::cout << "\n\nCompleted the Loop @$*&^@$*&^@*$&^@*$&^\n\n";
	int i; int ii; int iii; int iiii;
	
	a1 = std::chrono::high_resolution_clock::now();
	//std::cout << "finished answers: " << finishedAnswers.size() << "\n";
	

	unfinishedOptions.clear();
	
	for (ii=0;ii<finishedAnswers.size();ii++){
		////std::cout << "f: " << finishedAnswers[ii] << "\n";
		if (doubleCheckAnswer(finishedAnswers[ii])){
			////std::cout << "cf: " << finishedAnswers[ii] << "\n";
			std::vector<Step> v = makeSolutionList(finishedAnswers[ii],newPostfix);
			int vsz = v.size();
			if (vsz > 0){
				
				Answer answer;
				answer.finished = true;
				answer.correct = true;
				if (vsz > 1){
					answer.next = v[vsz-2].next;
				}
				answer.solution = v;
				answerMap[finishedAnswers[ii]]=answer;
				
			}
			else {
				v = makeIncorrectSolutionList(finishedAnswers[ii],newPostfix);
				vsz = v.size();
				
				Answer answer;
				answer.finished = true;
				answer.correct = false;
				if (vsz > 1){
					answer.next = v[vsz-2].next;
				}
				answer.solution = v;
				answerMap[finishedAnswers[ii]]=answer;
			}
		}
	}
	int uos = 0;
	for (std::map<std::string,bool>::iterator iter = unfinishedOptions.begin(); iter != unfinishedOptions.end(); ++iter){
		if (answerMap.find(iter->first) != answerMap.end()){
			continue;
		}
		uos++;
		
		std::vector<Step> v = makeSolutionList(iter->first,newPostfix);
		int vsz = v.size();
		if (vsz > 0){
			Answer answer;
			answer.finished = false;
			answer.correct = true;
			if (vsz > 1){
				answer.next = v[vsz-2].next;
			}
			answer.solution = v;
			answerMap[iter->first]=answer;
		}
		else {
			std::vector<Step> vv = makeIncorrectSolutionList(iter->first,newPostfix);
			vsz = vv.size();
			if (vsz > 0){
				
				Answer answer;
				answer.finished = false;
				answer.correct = false;
				if (vsz > 1){
					answer.next = vv[vsz-2].next;
				}
				answer.solution = v;
				answerMap[iter->first]=answer;
			}
			else {
				//std::cout << "no solution found? " << iter->first << "\n";
			}
		}

		
	}
	
	//std::cout << "unfinished answers: " << uos << "\n";

	

	
	
	
	//for (std::map<std::string,std::vector<std::string>>::iterator iter = reverseMapCorrect.begin(); iter != reverseMapCorrect.end(); ++iter){
	//	//std::cout << "rm: " << iter->first << " and " << iter->second.size() << "\n";		
	//}
	
	
	a2 = std::chrono::high_resolution_clock::now();
	//std::cout << "time to find correct answers: " << " and " << std::chrono::duration_cast<std::chrono::microseconds>( a2 - a1 ).count() << "\n\n\n";
	
	std::string error = "Don't know.";
	int ui = 0;
	
	
	
	
	//for (std::map<std::string,Answer>::iterator iter = answerMap.begin(); iter != answerMap.end(); ++iter){
	//	inputArray.push_back(inputify(iter->first));
	//}
	auto a3 = std::chrono::high_resolution_clock::now();
	//std::cout << "time to inputify answers: " << " and " << std::chrono::duration_cast<std::chrono::microseconds>( a3 - a2 ).count() << "\n\n\n";
	
	
	
	

	return error;
}