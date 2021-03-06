
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

#include "commonstuff.cpp"

#include "solve.cpp"

std::vector<std::vector<Step>> partialTree(std::string pfstr){
	std::map<std::string,std::vector<std::string>> listMap;
	std::map<int,int> operandMap;
	std::map<int,std::string> originalMap;
    std::vector<Step> returnStringsCorrect;
    std::vector<Step> returnStringsIncorrect;
	int i; int ii; int iii;
	int idx =0;
	bool startOperands = false;
	std::string currentOperator = "";
	int iidx = 0;
	bool midBrackets = false;
	answerIsFinished = true;
	
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
	
	
	//std::cout << "before third: " << pfstr << "\n";

	
	for (i=0;i<pfstr.length();i++){
		char mychar = pfstr.at(i);
		if (mychar == '@'){
			break;
		}
		else if (mychar != '#'){
			
			
			std::vector<std::string> secondS;
			std::vector<std::string> secondT;
			std::vector<std::string> secondSBL;
			std::vector<std::string> secondTBL;
			std::string secondStr = "";
			std::string secondTtr = "";
			std::string secondListMapKey = "";
			
			std::vector<std::string> fullTrees;
			int ftSz = 0;
			bool foundFullTrees = false;
			std::string inStr = "";
			int prevLeftIndex = 0;
			int prevRightOperand = 0;

			
			int maxi = i-1;
			int startLeftIndex = maxi;
			int startRightOperand = 10000;
			int endRightOperand = -1;
			for (ii=0;ii<i;ii++){
				std::string s = "";
				std::string t = "";
				int tempStartRightOperand = 10000;
				int tempEndRightOperand = -1;
				for (iii=ii;iii<i;iii++){
					s += pfstr.at(iii);
					if (pfstr.at(iii) == '#'){
						t += originalMap[operandMap[iii]] + '_';
						if (operandMap[iii]<tempStartRightOperand){
							tempStartRightOperand = operandMap[iii];
						}
						if (operandMap[iii]>tempEndRightOperand){
							tempEndRightOperand = operandMap[iii];
						}
					}
				}
				if (listMap.find(s + '@' + t) != listMap.end()){
					secondStr = s;
					secondTtr = t;
					secondListMapKey = s + "@" + t;
					int lms = listMap[s+'@'+t].size()/5;
					secondS.resize(lms);
					secondT.resize(lms);
					secondSBL.resize(lms);
					secondTBL.resize(lms);
					for (iii=0;iii<lms;iii++){
						secondS[iii]=listMap[s+'@'+t][iii*5];
						secondT[iii]=listMap[s+'@'+t][iii*5+1];
						secondSBL[iii]=listMap[s+'@'+t][iii*5+3];
						secondTBL[iii]=listMap[s+'@'+t][iii*5+4];
					}
					maxi = ii;
					startLeftIndex = ii;
					startRightOperand = tempStartRightOperand;
					endRightOperand = tempEndRightOperand;
					break;
				}
				if (ii==i-1){
					//std::cout << "No match 1\n";
				}
			}
			
			
	

			std::vector<std::string> firstS;
			std::vector<std::string> firstT;
			std::vector<std::string> firstSBL;
			std::vector<std::string> firstTBL;
			std::string firstStr = "";
			std::string firstTtr = "";
			std::string firstListMapKey = "";
	
	
	
			if (mychar != '-' && mychar != '/' && (mychar >= 0 || mychar <= -69 )){ // Is at least binary function
				if (maxi == 0){
					//TODO figure out why maxi is ever 0
					returnStringsCorrect.resize(0);
					returnStringsIncorrect.resize(0);
					break;
				}
				for (ii=0;ii<maxi;ii++){
					std::string s = "";
					std::string t = "";
					int tempStartRightOperand = 10000;
					for (iii=ii;iii<maxi;iii++){
						s += pfstr.at(iii);
						if (pfstr.at(iii) == '#'){
							t += originalMap[operandMap[iii]] + '_';
							if (operandMap[iii]<tempStartRightOperand){
								tempStartRightOperand = operandMap[iii];
							}
						}
					}
					if (listMap.find(s + '@' + t) != listMap.end()){
						firstListMapKey = s + "@" + t;
						firstStr = s;
						firstTtr = t;
						int lms = listMap[s+'@'+t].size()/5;
						firstS.resize(lms);
						firstT.resize(lms);
						firstSBL.resize(lms);
						firstTBL.resize(lms);
						for (iii=0;iii<lms;iii++){
							firstS[iii]=listMap[s+'@'+t][iii*5];
							firstT[iii]=listMap[s+'@'+t][iii*5+1];
							firstSBL[iii]=listMap[s+'@'+t][iii*5+3];
							firstTBL[iii]=listMap[s+'@'+t][iii*5+4];
						}
						startLeftIndex = ii;
						startRightOperand = tempStartRightOperand;
						break;
					}
					if (ii==maxi-1){
						//std::cout << "No match 2\n";
					}
				}
				
				
				if (mychar == '+'){
					std::vector<int> allSums ={startLeftIndex,maxi,maxi,i};
					bool moreTerms = true;
					int whileI =0;
					//std::cout << pfstr << " and " << allSums[0] << " and " << allSums[3] << "\n";
					while (moreTerms){
						moreTerms = false;
						for (whileI=0;whileI<allSums.size()/2;whileI++){
							if (pfstr.at(allSums[whileI*2+1]-1) == '+'){
								moreTerms = true;
								int tempMax = allSums[whileI*2+1]-1;
								for (ii=0;ii<tempMax;ii++){
									std::string s = "";
									std::string t = "";
									for (iii=ii;iii<tempMax;iii++){
										s += pfstr.at(iii);
										if (pfstr.at(iii) == '#'){
											t += originalMap[operandMap[iii]] + '_';
										}
									}
									if (listMap.find(s + '@' + t) != listMap.end()){
										allSums[whileI*2+1]=ii;
										allSums.push_back(ii);
										allSums.push_back(tempMax);
										break;
									}
								}
								break;
							}
						}
					}
					//if (allSums.size()>4){
					//	for (ii=0;ii<allSums.size();ii++){
					//		std::cout << ii << " with "<< allSums[ii] << "\n";
					//	}
					//}
					std::vector<std::string> possStr;
					
					
				}
				
				
				int fss = firstS.size();
				int sss = secondS.size();	
				std::string nFirst = "0";
				std::string nSecond = "0";	
				//std::cout << "new size: " << fss << " * " << sss << " by " << firstStr + secondStr + pfstr.at(i) + "@" + firstTtr + secondTtr << "\n";
				fullTrees.resize(ftSz+5+sss*fss*2*5);
				//condensed
				fullTrees[ftSz] = "#";
				ftSz++;

				std::string bless = firstStr + secondStr + pfstr.at(i) + '@' + firstTtr + secondTtr;

			
				fullTrees[ftSz] = "{"+bless+"}_";
				ftSz++;
				fullTrees[ftSz] = "0";
				ftSz++;
				
				fullTrees[ftSz] = firstStr + secondStr + pfstr.at(i);
				ftSz++;
				fullTrees[ftSz] = firstTtr + secondTtr;
				ftSz++;
				
				
				//50 ms to here from recent continue

				
				for (ii=0;ii<fss;ii++){
					nFirst = listMap[firstListMapKey][ii*5+2];
					if (nFirst=="4"){
						continue;
					}
					
					for (iii=0;iii<sss;iii++){
				
						nSecond = listMap[secondListMapKey][iii*5+2];
						if (nSecond=="4"){
							continue;
						}
						
						//2 ms
						
						
						if (nSecond=="3" || nFirst=="3"){
							
							continue;
						}
						
						std::string tempFull = pfstr;
						int iiiii; int operandIdx = -1; int startRightIndex = -1; int rightLength= 0;
		
						for (iiiii=0;iiiii<tempFull.length();iiiii++){
							if (tempFull.at(iiiii) == '_'){
								operandIdx++;
								if (operandIdx <=endRightOperand){
									rightLength++;
								}
								else {
									break;
								}
							}
							else if (tempFull.at(iiiii) == '@'){
								operandIdx++;
							}
							else if (operandIdx==startRightOperand && startRightIndex<0){
								startRightIndex = iiiii;
								rightLength = 1;
							}
							else{
								rightLength++;
							}
						}

						//std::vector<int> tempV;
						//tempV = {startLeftIndex,i+1-startLeftIndex,startRightIndex,rightLength};

						
						auto a1 = std::chrono::high_resolution_clock::now();
						//TODO: make this parallel
						//std::thread th1(apply1,firstS[ii] + secondS[iii] + pfstr.at(i) + '@' + firstT[ii] + secondT[iii],tempV,pfstr,isCorrect);
						//th1.join();
						
						//pp = tp.push(apply1,firstS[ii] + secondS[iii] + pfstr.at(i) + '@' + firstT[ii] + secondT[iii],tempV,pfstr,isCorrect);
						//pp.get();
						//std::future<bool> fut = std::async(apply1,firstS[ii] + secondS[iii] + pfstr.at(i) + '@' + firstT[ii] + secondT[iii],tempV,pfstr,isCorrect);
						//fut.get();
						//apply1(0,firstS[ii] + secondS[iii] + pfstr.at(i) + '@' + firstT[ii] + secondT[iii],tempV,pfstr,isCorrect);
						std::vector<Step> someStringsC = applyRulesVectorOnePart(firstS[ii] + secondS[iii] + pfstr.at(i) + '@' + firstT[ii] + secondT[iii],{startLeftIndex,i+1-startLeftIndex,startRightIndex,rightLength},pfstr,true);
						std::vector<Step> someStringsI = applyRulesVectorOnePart(firstS[ii] + secondS[iii] + pfstr.at(i) + '@' + firstT[ii] + secondT[iii],{startLeftIndex,i+1-startLeftIndex,startRightIndex,rightLength},pfstr,false);
						
						int iiiiii;
						for (iiiiii=0;iiiiii<someStringsC.size();iiiiii++){
							returnStringsCorrect.push_back(someStringsC[iiiiii]);
						}
						for (iiiiii=0;iiiiii<someStringsI.size();iiiiii++){
							returnStringsIncorrect.push_back(someStringsI[iiiiii]);
						}
						auto a2 = std::chrono::high_resolution_clock::now();
						//duration2 += std::chrono::duration_cast<std::chrono::milliseconds>( a2 - a1 ).count();
						
						

						
						int numOperations = 0; int ni;
						for (ni=0;ni<firstS[ii].size();ni++){
							if (firstS[ii].at(ni)=='@'){
								break;
							}
							else if (firstS[ii].at(ni)!='#'){
								numOperations++;
							}
						}
						for (ni=0;ni<secondS[iii].size();ni++){
							if (secondS[iii].at(ni)=='@'){
								break;
							}
							else if (secondS[iii].at(ni)!='#'){
								numOperations++;
							}
						}
						if (numOperations > 10){
							continue;
						}
						
						
						fullTrees[ftSz] = firstS[ii] + secondS[iii]  + pfstr.at(i);
						ftSz++;
						fullTrees[ftSz] = firstT[ii] + secondT[iii];
						ftSz++;
						if (nSecond=="2" || nFirst=="2"){
							fullTrees[ftSz] = "3";
							ftSz++;
						}
						else if (nSecond=="1" || nFirst=="1"){
							fullTrees[ftSz] = "2";
							ftSz++;
						}
						else {
							fullTrees[ftSz] = "1";
							ftSz++;
						}
						fullTrees[ftSz] = firstSBL[ii] + secondSBL[iii]  + pfstr.at(i);
						ftSz++;
						fullTrees[ftSz] = firstTBL[ii] + secondTBL[iii];
						ftSz++;
						
						//18 ms to here from recent continue
						
				
						/*
						if (pfstr.at(i) == '+' || pfstr.at(i) == '*'){
							fullTrees[ftSz] = secondS[iii] + firstS[ii]  + pfstr.at(i);
							ftSz++;
							fullTrees[ftSz] = secondT[iii] + firstT[ii];
							ftSz++;
							if (nSecond=="2" || nFirst=="2"){
								fullTrees[ftSz] = "3";
								ftSz++;
							}
							else if (nSecond=="1" || nFirst=="1"){
								fullTrees[ftSz] = "2";
								ftSz++;
							}
							else {
								fullTrees[ftSz] = "1";
								ftSz++;
							}
							fullTrees[ftSz] = secondSBL[iii] + firstSBL[ii]  + pfstr.at(i);
							ftSz++;
							fullTrees[ftSz] = secondTBL[iii] + firstTBL[ii];
							ftSz++;
					
					

							std::vector<std::string> someStrings = applyRulesVectorOnePart(secondS[iii] + firstS[ii]  + pfstr.at(i) + '@' + secondT[iii] + firstT[ii],{startLeftIndex,i+1-startLeftIndex,startRightIndex,rightLength},pfstr,isCorrect);
							int iiiiii;
							for (iiiiii=0;iiiiii<someStrings.size();iiiiii++){
								returnStrings.push_back(someStrings[iiiiii]);
							}
						}*/
						//62 ms to here from the 18 ms marker
						
					}
					
					
				}
				
				
				
			
			
			}
			else {
				fullTrees.resize(ftSz+5+secondS.size()*1*5);
				
				fullTrees[ftSz] = "#";
				ftSz++;

				std::string bless = secondStr + pfstr.at(i) + '@' + secondTtr;

			
				fullTrees[ftSz] = "{"+bless+"}_";
				ftSz++;
				fullTrees[ftSz] = "0";
				ftSz++;
				
				fullTrees[ftSz] = secondStr + pfstr.at(i);
				ftSz++;
				fullTrees[ftSz] = secondTtr;
				ftSz++;
				
				for (iii=0;iii<secondS.size();iii++){
				
					if (listMap[secondListMapKey][iii*5+2]=="4"){
						continue;
					}
				
					
					
					
					
				
				
				
					if (listMap[secondListMapKey][iii*5+2]=="3"){
						continue;
					}
					
					//std::cout << "possible part: " << secondS[iii] + pfstr.at(i) + '@' + secondT[iii] << " and " << startLeftIndex << " and " << startRightOperand << " and " << endRightOperand << " from " << pfstr << "\n";
				
					std::string tempFull = pfstr;
					int iiiii; int operandIdx = -1; int startRightIndex = -1; int rightLength= 0;
					for (iiiii=0;iiiii<tempFull.length();iiiii++){
						if (tempFull.at(iiiii) == '_'){
							operandIdx++;
							if (operandIdx <=endRightOperand){
								rightLength++;
							}
							else {
								break;
							}
						}
						else if (tempFull.at(iiiii) == '@'){
							operandIdx++;
						}
						else if (operandIdx==startRightOperand && startRightIndex<0){
							startRightIndex = iiiii;
							rightLength = 1;
						}
						else{
							rightLength++;
						}
					}

					auto a1 = std::chrono::high_resolution_clock::now();
					//TODO: make this parallel
					//std::vector<int> tempV;
					//tempV = {startLeftIndex,i+1-startLeftIndex,startRightIndex,rightLength};
					
					//apply2(0,secondS[iii] + pfstr.at(i) + '@' + secondT[iii],tempV,pfstr,isCorrect);
					//pp = tp.push(apply2,secondS[iii] + pfstr.at(i) + '@' + secondT[iii],tempV,pfstr,isCorrect);
					//pp.get();
						
						
					//std::thread th2(apply2,secondS[iii] + pfstr.at(i) + '@' + secondT[iii],tempV,pfstr,isCorrect);
					//th2.join();
					std::vector<Step> someStringsC = applyRulesVectorOnePart(secondS[iii] + pfstr.at(i) + '@' + secondT[iii],{startLeftIndex,i+1-startLeftIndex,startRightIndex,rightLength},pfstr,true);
					std::vector<Step> someStringsI = applyRulesVectorOnePart(secondS[iii] + pfstr.at(i) + '@' + secondT[iii],{startLeftIndex,i+1-startLeftIndex,startRightIndex,rightLength},pfstr,false);
					
					int iiiiii;
					for (iiiiii=0;iiiiii<someStringsC.size();iiiiii++){
						returnStringsCorrect.push_back(someStringsC[iiiiii]);
					}
					for (iiiiii=0;iiiiii<someStringsI.size();iiiiii++){
						returnStringsIncorrect.push_back(someStringsI[iiiiii]);
					}
					auto a2 = std::chrono::high_resolution_clock::now();
					//duration2 += std::chrono::duration_cast<std::chrono::milliseconds>( a2 - a1 ).count();
					
					
					
					int numOperations = 0; int ni;
					for (ni=0;ni<secondS[iii].size();ni++){
						if (secondS[iii].at(ni)=='@'){
							break;
						}
						else if (secondS[iii].at(ni)!='#'){
							numOperations++;
						}
					}
					if (numOperations > 10){
						continue;
					}
					
					fullTrees[ftSz] = secondS[iii] + pfstr.at(i);
					ftSz++;
					fullTrees[ftSz] = secondT[iii];
					ftSz++;
					if (listMap[secondListMapKey][iii*5+2]=="2"){
						fullTrees[ftSz] = "3";
						ftSz++;
					}
					else if (listMap[secondListMapKey][iii*5+2]=="1"){
						fullTrees[ftSz] = "2";
						ftSz++;
					}
					else {
						fullTrees[ftSz] = "1";
						ftSz++;
					}
					fullTrees[ftSz] = secondSBL[iii] + pfstr.at(i);
					ftSz++;
					fullTrees[ftSz] = secondTBL[iii];
					ftSz++;
					
				
					//condensed
					//fullTrees.push_back("#");
					//fullTrees.push_back("{"+std::to_string(iidx)+"}_");
					//originalMap[iidx]= secondS[iii] + pfstr.at(i) + '@' + secondT[iii];
					//iidx++;
				}
			}
		

			

			//std::cout << "fullTrees size: " << fullTrees.size() << " @ " << i << "\n";
			std::string fullStr = firstStr + secondStr + pfstr.at(i) + '@' + firstTtr + secondTtr;
			
		
			//Parent Node
			std::string opStr = "";
			opStr += pfstr.at(i);
			fullTrees.resize(ftSz);
			
			//auto a3 = std::chrono::high_resolution_clock::now();
			
			listMap[fullStr]=fullTrees;
			
			//auto a4 = std::chrono::high_resolution_clock::now();
			//duration3 += std::chrono::duration_cast<std::chrono::milliseconds>( a4 - a3 ).count();
			

			
			

			
			

			
		}
		else {
			std::map<std::string, std::string> followAMap;
			std::string remed = removeBracketsOne("#@"+originalMap[idx]+'_', followAMap);
			std::string firstRemed = "";
			std::string secondRemed = "";
			bool isSecondPart = false;
			for (ii=0;ii<remed.length();ii++){
				if (remed.at(ii) == '@'){
					isSecondPart = true;
				}
				else if (isSecondPart){
					secondRemed += remed.at(ii);
				}
				else {
					firstRemed += remed.at(ii);
				}
			}
			listMap["#@" + originalMap[idx] + "_"]={"#",originalMap[idx]+'_',"0",firstRemed,secondRemed};
			operandMap[i]=idx;
			idx++;
		}
		
	}
		
	
	//std::cout << "\n\n---start Original-----\n";
	int iiii;
	/*
	returnStrings = returnStrings1;
	returnStrings.resize(returnStrings1.size()+returnStrings2.size());
	for (ii=0;ii<returnStrings2.size();ii++){
		returnStrings[ii+returnStrings1.size()]=returnStrings2[ii];
	}
	returnStrings1.resize(0);
	returnStrings2.resize(0);*/

	return {returnStringsCorrect,returnStringsIncorrect};
	

}

void clearRules(){

	int i;

	eloMap[1]=19956; eloMap[2]=16902; eloMap[3]=15097; eloMap[4]=13802; eloMap[5]=12788; eloMap[6]=11950; eloMap[7]=11234; eloMap[8]=10607; eloMap[9]=10048; eloMap[10]=9542; eloMap[11]=9080; eloMap[12]=8653; eloMap[13]=8256; eloMap[14]=7884; eloMap[15]=7533; eloMap[16]=7202; eloMap[17]=6886; eloMap[18]=6585; eloMap[19]=6297; eloMap[20]=6021; eloMap[21]=5754; eloMap[22]=5497; eloMap[23]=5248; eloMap[24]=5006; eloMap[25]=4771; eloMap[26]=4543; eloMap[27]=4320; eloMap[28]=4102; eloMap[29]=3889; eloMap[30]=3680; eloMap[31]=3475; eloMap[32]=3274; eloMap[33]=3076; eloMap[34]=2881; eloMap[35]=2688; eloMap[36]=2499; eloMap[37]=2311; eloMap[38]=2126; eloMap[39]=1943; eloMap[40]=1761; eloMap[41]=1581; eloMap[42]=1402; eloMap[43]=1224; eloMap[44]=1047; eloMap[45]=872; eloMap[46]=696; eloMap[47]=522; eloMap[48]=348; eloMap[49]=174; eloMap[50]=0; eloMap[51]=-174; eloMap[52]=-348; eloMap[53]=-522; eloMap[54]=-696; eloMap[55]=-872; eloMap[56]=-1047; eloMap[57]=-1224; eloMap[58]=-1402; eloMap[59]=-1581; eloMap[60]=-1761; eloMap[61]=-1943; eloMap[62]=-2126; eloMap[63]=-2311; eloMap[64]=-2499; eloMap[65]=-2688; eloMap[66]=-2881; eloMap[67]=-3076; eloMap[68]=-3274; eloMap[69]=-3475; eloMap[70]=-3680; eloMap[71]=-3889; eloMap[72]=-4102; eloMap[73]=-4320; eloMap[74]=-4543; eloMap[75]=-4771; eloMap[76]=-5006; eloMap[77]=-5248; eloMap[78]=-5497; eloMap[79]=-5754; eloMap[80]=-6021; eloMap[81]=-6297; eloMap[82]=-6585; eloMap[83]=-6886; eloMap[84]=-7202; eloMap[85]=-7533; eloMap[86]=-7884; eloMap[87]=-8256; eloMap[88]=-8653; eloMap[89]=-9080; eloMap[90]=-9542; eloMap[91]=-10048; eloMap[92]=-10607; eloMap[93]=-11234; eloMap[94]=-11950; eloMap[95]=-12788; eloMap[96]=-13802; eloMap[97]=-15097; eloMap[98]=-16902; eloMap[99]=-19956;
	overallScore = 0;
	subjectEq.op = 1; topicEq.op = 2; ruleEq.op = 3; idEq.op = 0; minEq.op = 4;
	

	firstCorrect = false;

	rules.clear();
	constraintMap.clear();
	ruleIndex.clear();
	answerConstraints.clear();
	ridx = 0;

}
void oneLesson(std::string s){
	std::vector<std::string> rows;
	std::string currentRow = "";
	int i;
	for (i=0;i<s.length();i++){
		if (s.at(i) == '\n'){
			rows.push_back(currentRow);
			currentRow = "";
		}
		else {
			currentRow += s.at(i);
		}
	}
	if (currentRow.length()>0){
		rows.push_back(currentRow);
	}
	makeRulesNew(rows);
}

std::vector<double> getPoints(std::vector<std::string> postfixedV, std::string indVar, std::string depVar,double domainLeft,double domainRight, int n) {

	std::vector<double> out;
	
	
	
	std::vector<int> xIdx;
	
	int i; int ii;
	std::string currentOperand = "";
	for (i=0;i<postfixedV[1].length();i++){
		if (postfixedV[1].at(i) == '_'){
			if (currentOperand == indVar){
				xIdx.push_back(i);	
			}
			currentOperand = "";
		}
		else {
			currentOperand += postfixedV[1].at(i);
		}
	}
	auto a1 = std::chrono::high_resolution_clock::now();
	out.resize(2*n+2);
	for (i=0;i<n+1;i++){
		if (killNow.check()){
			out.resize(i*2);
			return out;
		}
		double x = domainLeft + i*(domainRight-domainLeft)/n;
		std::string solvableR = postfixedV[1];
		
		for (ii=xIdx.size()-1;ii>=0;ii--){
			solvableR.replace(xIdx[ii]-indVar.length(),indVar.length(),std::to_string(x));
		}
		std::string solvable = postfixedV[0] + "@" + solvableR;
		//std::cout << "solvable: " << solvable << "\n";
		std::string displaySolvable = "";
		for (ii=0;ii<solvable.length();ii++){
			if (solvable.at(ii)<0){
				int si = solvable.at(ii) - '0' + '0';
				displaySolvable += std::to_string(si);
			}
			else {
				displaySolvable += solvable.at(ii);
			}
			
		}
		Number y = solvePostfix(solvable);
		if (depVar == "y"){
			if (y.type == 0){
				out[i*2]=-10001;
				out[i*2+1]=-10001;
			}
			else {
				out[i*2]=x;
				out[i*2+1]=std::stod(outputNumber(y));
			}
			
		}
		else if (depVar == "x"){
			if (y.type == 0){
				out[i*2]=-10001;
				out[i*2]=-10001;
			}
			else {
				out[i*2+1]=x;
				out[i*2]=std::stod(outputNumber(y));
			}
		}
		
	}
	auto a2 = std::chrono::high_resolution_clock::now();
	//std::cout << "time to solve 1000: " << std::chrono::duration_cast<std::chrono::milliseconds>( a2 - a1 ).count() << "\n\n";
	
	return out;
}

