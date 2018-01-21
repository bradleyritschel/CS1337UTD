//
//  main.cpp
//  CS 1337 Project 2
//
//  Created by Bradley Ritschel on 9/25/17.
//  Copyright © 2017 Bradley Ritschel. All rights reserved.
// NetID: bsr160130

#include <iostream>
#include <algorithm> // for sort()
#include <fstream> // for file operations
#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include <ostream>
#include <stdlib.h>

using namespace std;

long findLineLength(vector<string> contestant) {
    long lineLength = (contestant.size() - 2)/3;
    
    cout << "lineLength: " << lineLength;
    return lineLength;
}

long howManyLines() {

    ifstream contestantsFile("contestants.txt", ios::in);

    // new lines will be skipped unless we stop it from happening:
    contestantsFile.unsetf(ios_base::skipws);

    // count the newlines with an algorithm specialized for counting:
    long line_count = count(
                                 istream_iterator<char>(contestantsFile),
                                 istream_iterator<char>(),
                                 '\n');
    
    cout << "line_count: " << line_count;
    return line_count;
}

vector<string> parseString(string toParse) { //contestant answer file and key file parsing function
    
    vector<string> PARSED; // declare vector
    size_t pos = 0, found;
    
    while((found = toParse.find_first_of(' ', pos)) != string::npos) {
        PARSED.push_back(toParse.substr(pos, found - pos));
        pos = found+1;
    }
    
    PARSED.push_back(toParse.substr(pos));
    
    cout << "parsed string: ";
    for (auto i = PARSED.begin(); i != PARSED.end(); i++) { //print elements of parsed string
        cout << *i << " ";
    }
    return PARSED;
}

vector<string> getContestantInfo(int line) {
    
    vector<string> contestantReport; // declare vector to return
    
    ifstream contestantsFile; //declare object
    contestantsFile.open("contestants.txt", ios::in); //open and associate file
    
    if (!contestantsFile) {
        cout << "Unable to open file";
        exit(1);   // call system to stop if file did not open
    }
    
    contestantsFile.seekg((line - 1) * 31); //set pointer to desired line
    
    string aContestant; //declare string to write file input to
    getline(contestantsFile,aContestant); // get line from file and assign to string
    
    contestantsFile.close(); //close file
    
    string id = aContestant.substr(0, 10); //pull ID
    
    contestantReport.push_back(id); //push id to vector
    
    aContestant.erase(0,11); // erase ID, leaving answers
    
    vector<string> parsedContestant = parseString(aContestant); // parse line of contestant answers
    
    cout << "parsed contestant info: ";
    for (auto i = parsedContestant.begin(); i != parsedContestant.end(); i++) //print elements of parsed string
        cout << *i << " ";
    
    ifstream keyFile; //declare object
    keyFile.open("answers.txt", ios::in); //open and associate file
        
    if (!keyFile) {
        cout << "Unable to open file";
        exit(1);   // call system to stop if file did not open
    }
        
    string keys; //declare string to write file input to
    getline(keyFile,keys); // get line from file and assign to string
        
    keyFile.close(); //close file
        
    vector<string> parsedKey = parseString(keys); //parse line of correct answers
    
    cout << "parsed key: ";
    for (auto i = parsedKey.begin(); i != parsedKey.end(); i++) //print elements of parsed string
        cout << *i << " ";
        
    vector<int> incorrectQuestions; //declare vector for incorrect questions
        
    for(int i = 0; i < 10; i++) // push incorrect answers indices to vector
        if(parsedContestant[i] != parsedKey[i]) {
            incorrectQuestions.push_back(i);
        }
    
        cout << "incorrect questions: ";
    for (auto i = incorrectQuestions.begin(); i != incorrectQuestions.end(); i++) //print elements of parsed string
        cout << *i << " ";
        
    string score = to_string((10 - incorrectQuestions.size()) * 10); // calculate score
        cout << "score: " << score << endl;
    
    contestantReport.push_back(score); // push score to vector
    
    for (auto i = incorrectQuestions.begin(); i != incorrectQuestions.end(); i++) { //push question #'s missed to vector
        contestantReport.push_back(to_string(*i + 1));
    }
        
    for (auto i = incorrectQuestions.begin(); i != incorrectQuestions.end(); i++) { //push incorrect answers given by contestant to vector
        contestantReport.push_back(parsedContestant[*i]);
    }
        
    for (auto i = incorrectQuestions.begin(); i != incorrectQuestions.end(); i++) { //push correct answers to vector
        contestantReport.push_back(parsedKey[*i]);
    }
    
    cout << "id and score: ";
    for (int i = 0; i < 2; i++) { //print id and score
        cout << contestantReport[i] << endl;
    }
    
    cout << "question numbers missed: ";
    for (int i = 2; i < (2 + findLineLength(contestantReport)); i++) { //print question #'s missed
        cout << contestantReport[i] << " ";
    }
    
    cout << endl;
    
    cout << "correct answers: ";
    for (long i = (2 + findLineLength(contestantReport)); i < (2 + (2 * findLineLength(contestantReport))); i++) { //print correct answers
        cout << contestantReport[i] << " ";
    }
    
    cout << endl;
    
    cout << "incorrect answers: ";
    for (long i = (2 + (2 * findLineLength(contestantReport))); i < (2 + (3 * findLineLength(contestantReport))); i++) { //print incorrect answers
        cout << contestantReport[i] << " ";
    }
    
    cout << "all contestant report elements: ";
    for (auto i = contestantReport.begin(); i != contestantReport.end(); i++) { //print all vector elements
        cout << *i << endl;
    }
    
    cout << endl;
    
    return contestantReport;
}

long findAverage() {
    int totalPoints = 0;
    for(int i = 1; i < (howManyLines() + 1); i++) {
        totalPoints +=  atoi(getContestantInfo(i)[1].c_str());
    }
    long average = totalPoints/howManyLines();
    
    cout << "average: " << average << endl;
    return average;
}

vector<long> makeSortedScoresVector() {
    vector<long> sortedScoresVector;
    for(int i = 1; i < (howManyLines() + 1); i++) {
        sortedScoresVector.push_back(atoi(getContestantInfo(i)[1].c_str()));
    }
    sort(sortedScoresVector.begin(), sortedScoresVector.end()); //sort the strings

    cout << "sorted scores: ";
    for (auto i = sortedScoresVector.begin(); i != sortedScoresVector.end(); i++) { //print all vector elements
        cout << *i << endl;
    }
    return sortedScoresVector;
}

long findMedian()
{
    long median;
    size_t size = makeSortedScoresVector().size();
    
    if (size  % 2 == 0)
    {
        median = ((makeSortedScoresVector()[size / 2 - 1]) + makeSortedScoresVector()[size / 2]) / 2;
    }
    else
    {
        median = makeSortedScoresVector()[size / 2];
    }
    
    cout << "median: " << median << endl;
    return median;
}

long grabModes() {

    vector<long> frequencies;

    vector<long> scores;
    
    long modes;

for (auto i = 0; i < 100; i++) //for all possible scores
    for (auto j = 0; j < makeSortedScoresVector().size(); j++) { //for all scores in the vector
        if (i == makeSortedScoresVector()[j]) { // if the possible score = the current element
            scores.push_back(makeSortedScoresVector()[j]); //push the matched score to the scores vector
            long frequency = 1; //declare the frequency of that number to be 1
            auto k = j++; // declare k to check if the scores after the matched score are the same as the current score
                while (i == makeSortedScoresVector()[k]) {//if the next element is the same , increment the frequency, and check the next element
                    frequency++; //increment frequency
                    k++; // increment to check next element
                    frequencies.push_back(frequency); //once all elements are checked, push the frequency to the frequency vector
                }
            cout << "frequency: " << frequency;
        }
    }
    modes = scores[*max_element(frequencies.begin(), frequencies.end())];
    return modes;
}

void writeToFile() {
    
    ofstream reportFile; //declare object
    reportFile.open("report.txt", ios::out); //open and associate file
    
    if (!reportFile) {
        cout << "Unable to create file";
        exit(1);   // call system to stop if file did not open
    }
    
    for (int j = 1; j < howManyLines() + 1; j++) {
        for (int i = 0; i < 2; i++) { //write id and score
            reportFile << getContestantInfo(j)[i] << endl;
            }
        
        for (int i = 2; i < (2 + findLineLength(getContestantInfo(j))); i++) { //write question #'s missed
            reportFile << getContestantInfo(j)[i] << " ";
            }
             
            reportFile << endl;
             
        for (long i = (2 + findLineLength(getContestantInfo(j))); i < (2 + (2 * findLineLength(getContestantInfo(j)))); i++) { //write correct answers
            reportFile << getContestantInfo(j)[i] << " ";
            }
             
            reportFile << endl;
             
        for (long i = (2 + (2 * findLineLength(getContestantInfo(j)))); i < (2 + (3 * findLineLength(getContestantInfo(j)))); i++) //write incorrect answers
            reportFile << getContestantInfo(j)[i] << " ";
            
        reportFile << endl; // return after writing incorrect answers
        reportFile << endl; // write blank line
        
        reportFile << findAverage() << endl; // write mean
        
        reportFile << findMedian() << endl; // write median
        
        reportFile << grabModes() << endl; // write modes
        
        reportFile << endl; // write blank line to start next contestant report
    }
    
    reportFile.close();// close reportFile
    
    cout << "File written successfully" << endl;
        
    }

int main() {
    
    writeToFile();

    return 0;
    
}
