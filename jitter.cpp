//
//  main.cpp
//  proj5
//
//  Created by Swetha S on 5/12/22.
//

#include <iostream>
#include <cctype>
#include <cstring>
#include <cassert>
using namespace std;
const int MAX_WORD_LENGTH = 20;
// parameters represent collection of match standards, located in 0 to nStandards-1
// negative nStandards is treated as 0
// when it returns, arrays represent a set of match standards in standard form
// returns the number of standards in that set
// transforms upper case letters in standards' words to lower
// removes match standards for which
// - distance is not positive
// - or a word in the standard contains no chars, or contains a char that is not a letter
// if two standards have same w1 and w2, removes the one whose distance value is lower
// if more than one match standards have the same w1, w2, and distance values, remove all but 1
int editStandards(int distance[],
                  char word1[][MAX_WORD_LENGTH+1],
                  char word2[][MAX_WORD_LENGTH+1],
                  int nStandards){

   
    // if nStandards is 0 or negative, return 0

    int validStandards = nStandards;
    if (nStandards <= 0){
        return 0;
    }
    
    //for word1 and word2, make all cstrings lower case
    
    for (int i = 0; i<nStandards; i++){
        for (int j = 0; j<MAX_WORD_LENGTH; j++){
            word1[i][j]=tolower(word1[i][j]);
            word2[i][j]=tolower(word2[i][j]);
        }
    }

    // if word has no chars, contains non letter, remove, shift all after back, nStandards--
    
    for (int i = 0; i < validStandards; ){
        if ((distance[i] <= 0) || strcmp(word1[i],"") == 0 || strcmp(word2[i],"") == 0){
            for (int j = i; j < nStandards-1; j++){
                distance[j] = distance[j+1];
                strcpy(word1[j], word1[j+1] );
                strcpy(word2[j], word2[j+1]);
            }
            validStandards--;
        } else i++;
    }
    
    // we have to search through each of the words until the null byte, if there is a non letter we delete that row and move everything up
    int word1AlphaFlag = 0;
    for (int i = 0; i < validStandards; ){
        word1AlphaFlag = 0;
        for (int j = 0; word1[i][j] != '\0'; j++){
                if (!(isalpha(word1[i][j]))){
                    for (int k = i; k < nStandards-1; k++){
                        distance[k] = distance[k+1];
                        strcpy(word1[k], word1[k+1] );
                        strcpy(word2[k], word2[k+1]);
                    }
                    validStandards--;
                    word1AlphaFlag = 1;
                    break;

                }
        }
        if (word1AlphaFlag == 0) i++;

    }

    int word2AlphaFlag = 0;
    for (int i = 0; i < validStandards; ){
        word2AlphaFlag = 0;
        for (int j = 0; word2[i][j] != '\0'; j++){
                if (!(isalpha(word2[i][j]))){
                    for (int k = i; k < nStandards-1; k++){
                        distance[k] = distance[k+1];
                        strcpy(word1[k], word1[k+1] );
                        strcpy(word2[k], word2[k+1]);
                    }
                    validStandards--;
                    word2AlphaFlag = 1;
                    break;

                }
        }
        if (word2AlphaFlag == 0) i++;
    }

    // go through and check if any standards after the current one have same w1 & w2
        // if they do, check if distance value is lower, if it is then remove, shift all after back, nStandards--
        // if they do, and distance is higher, remove the current one, shift everything after current back, nStandards--
        // if they do, and distance is the same , remove, shift all after back, nStandards--


int outerLoopFlag = 0;
    for (int i = 0; i < validStandards; ){
     outerLoopFlag = 0;
        for (int j = i+1; j < validStandards; ){
            if (strcmp(word1[i], word1[j]) == 0 && strcmp(word2[i], word2[j]) == 0){

                if (distance[i] < distance[j]){
                    for (int k = i; k < nStandards-1; k++){
                        distance[k] = distance[k+1];
                        strcpy(word1[k], word1[k+1] );
                        strcpy(word2[k], word2[k+1]);
                    }
                    validStandards--;
                    outerLoopFlag = 1;
                    break;
                    
                }

                if (distance[i] > distance[j]){
                    for (int k = j; k < nStandards-1; k++){
                        distance[k] = distance[k+1];
                        strcpy(word1[k], word1[k+1] );
                        strcpy(word2[k], word2[k+1]);
                    }
                    validStandards--;
                
                }

                if (distance[i] == distance[j]){
                   
                    for (int k = j; k < nStandards-1; k++){
                        distance[k] = distance[k+1];
                        strcpy(word1[k], word1[k+1] );
                        strcpy(word2[k], word2[k+1]);
                    }
                    validStandards--;

            
                }
            } else j++;
        }
        if (outerLoopFlag == 0) i++;

    }
    return validStandards;
}

// takes in a set of match standards in standard form, and cstring of a jeet
// max length of jeet is 281
// returns match level of jeet (number of match standards it matches)
// negative nStandards/ 0 return 0
// in jeet
   // words are seperated by one or more space
    // upper case letters are treated as lower
    //non alphabetic characters are to be ignore
// jeet matches standard if
    // w2 appears at least 1 word and no more than distance words after w1
    // it can only match a standard once
    //
int determineMatchLevel(const int distance[],
                        const char word1[][MAX_WORD_LENGTH+1],
                        const char word2[][MAX_WORD_LENGTH+1],
                        int nStandards,
                        const char jeet[]){
    // if nStandards 0 or -, return 0
    // make copy of jeet, removing non alpha chars, and any extra spaces between words, and making all letters lowercase
    // creat a 2d char array, with one word on each row
   
    
    // if nStandards 0 or -, return 0
    
    if (nStandards <= 0){
        return 0;
    }
    
    // make copy of jeet, removing non alpha chars, and any extra spaces between words, and making all letters lowercase
    char jeetCopy[281];
    int j = 0;
    for (int i = 0; jeet[i] != '\0'; i++){
        if (!isalpha(jeet[i]) && jeet[i] != ' '){
            continue;
        }
        if (isalpha(jeet[i])){
            jeetCopy[j] = tolower(jeet[i]);
            j++;
        }
        // if i is not 0, check if the the thing before is a 0, if it is continue
        // if it is not, add the space
        if (jeet[i] == ' '){
            if (j == 0){
                continue;
            }
            else {
                if (jeetCopy[j-1] != ' '){
                    jeetCopy[j] = jeet[i];
                    j++;
                }
            }
            
        }
    }
    jeetCopy[j] = '\0';
    
    //prints jeetCopy
//    for (int i = 0; jeetCopy[i] != '\0'; i++){
//        cout << jeetCopy[i];
//    }
//    cout << endl;
 
    // make jeetList array, go through jeetCopy
    // add chars from jeetCopy to jeetlist array row 1
    // if you come across a space, go to next row
    
    char jeetList[141][281] = {};
    int r = 0;
    int c = 0;
    for (int i = 0 ; jeetCopy[i] != '\0' ; i++){
        if (jeetCopy[i] != ' '){
            jeetList[r][c] = jeetCopy[i];
            c++;
        }
        else if (jeetCopy[i] == ' '){
            jeetList[r][c] = '\0';
            c = 0;
            r++;
        }
    }
    
    //print out jeetList
//    for (int i = 0; i < 141; i++){
//        cout << jeetList[i] << endl;
//    }
    
    // for each standard
        // go through jeetList and see if w1 appears
        // if it does, search through the next distance number words to see if they are w2
            // if it is, count++, break out of this standard
        //if not break out of this standard
    // return count
    int matches = 0;
    
    for (int i = 0; i < nStandards; i++){
        int matchFlag = 0;
        if (distance[i] == 0)
            continue;
        for (int j = 0; j < 141; j++){
            if (strcmp(word1[i],jeetList[j]) == 0){
                // found word1[i] at jeetList[j], see if we can find word2[i] after in jeetList within distance[i]
                for (int k = j+1; k<= j+distance[i]; k++){
                    if (strcmp(word2[i], jeetList[k]) == 0){
                        matches++;
                        matchFlag = 1;
                        break;
                    }
                }
            }
            if (matchFlag == 1){
                break;
            }
        }
    }
    return matches;
}

int main() {
//    const int TEST1_NSTANDARDS = 7;
//               int test1dist[TEST1_NSTANDARDS] = {
//                   1,             4,         2,         3, 2, 1, 13
//               };
//               char test1w1[TEST1_NSTANDARDS][MAX_WORD_LENGTH+1] = {
//                   "eccentric",   "space",  "that", "tunnelboring", "brandnew", "electric", "were"
//               };
//               char test1w2[TEST1_NSTANDARDS][MAX_WORD_LENGTH+1] = {
//                   "billionaire", "capsule", "on",     "equipment", "is", "car", "eccentric"
//               };

//    for (int i = 0; i<TEST1_NSTANDARDS; i++){
//        cout << test1dist[i] << " "<<test1w1[i] << " "<< test1w2 [i] << endl;
//    }

//    cout << endl;

    //cout <<  editStandards(test1dist,
//                          test1w1,
//                          test1w2,
//                          TEST1_NSTANDARDS) << endl;
   
//    cout << endl;
//    for (int i = 0; i<TEST1_NSTANDARDS; i++){
//        cout << test1dist[i] << " "<<test1w1[i] << " "<< test1w2 [i] << endl;
//    }
//    cout << endl;
    
//    char jeetTest [] = " I'm upset    that on Apr. 29th, 2022, THAT  my ON 2 brand-new    BMW i7s were stolen!! That on";
//   cout << "matches are " << determineMatchLevel(test1dist,
//                            test1w1,
//                            test1w2,
//                            TEST1_NSTANDARDS,
//                        jeetTest);
    const int TEST1_NSTANDARDS = 4;
              int test1dist[TEST1_NSTANDARDS] = {
                  2,             4,         1,         13
              };
              char test1w1[TEST1_NSTANDARDS][MAX_WORD_LENGTH+1] = {
                  "eccentric",   "space",  "electric", "were"
              };
              char test1w2[TEST1_NSTANDARDS][MAX_WORD_LENGTH+1] = {
                  "billionaire", "capsule", "car",     "eccentric"
              };
              assert(determineMatchLevel(test1dist, test1w1, test1w2, TEST1_NSTANDARDS,
                  "The eccentric outspoken billionaire launched a space station cargo capsule.") == 2);
              assert(determineMatchLevel(test1dist, test1w1, test1w2, TEST1_NSTANDARDS,
                  "The eccentric outspoken billionaire launched    a space capsule.") == 2);
              assert(determineMatchLevel(test1dist, test1w1, test1w2, TEST1_NSTANDARDS,
                  "**** 2022 ****") == 0);
              assert(determineMatchLevel(test1dist, test1w1, test1w2, TEST1_NSTANDARDS,
                  "  It's an ELECTRIC car!") == 1);
              assert(determineMatchLevel(test1dist, test1w1, test1w2, TEST1_NSTANDARDS,
                  "space space capsule space capsule capsule") == 1);
              assert(determineMatchLevel(test1dist, test1w1, test1w2, TEST1_NSTANDARDS,
                  "Two eccentric billionaires were space-capsule riders.") == 0);
              cout << "All tests succeeded" << endl;
    

    return 0;
}
