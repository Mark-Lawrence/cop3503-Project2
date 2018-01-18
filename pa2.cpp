//
//  pa2.cpp
//  pa
//
//  Created by Mark Lawrence on 10/18/17.
//  Copyright © 2017 Mark Lawrence. All rights reserved.
//

#include <iostream>
#include <string>
#include "OSMemoryManager.hpp"
#include "Program.hpp"
#include "pa2.h"
using namespace std;



int main(int argc, const char * argv[]) {
    algroithmUsed = argv[1];

    //Initalizing the memory, creating 32 empty pages of memory
    for (int i = 0; i<32; i++){
        memory ->append("FREE", 0);
    }
    
    //Make sure argc only allows one word, best or worst
    if ((algroithmUsed != "best" && algroithmUsed != "worst")|| argc != 2){
        std::cout<<"Failed, please enter valid argument, either 'best' or 'worst'\n";
        return 0;
    }
    else{
        std::cout<<"Using the "<<algroithmUsed<<" fit algorithum\n";
    }
    
    
    std::cout<<"\n1.Add program\n2.Kill program\n3.Fragmentation\n4.Print memory\n5.Exit\n\n";
    
    
    do {
        std::cout<<"choice - ";
        std::cin>>userInput;
        
        //Checks that the user has entered a valid input
        if (userInput != "4" && userInput != "1" && userInput != "2" && userInput != "3" && userInput !="5"){
            std::cout<<"Please enter a valid input\n\n";
            continue;
        }
        
        else{
            intUserInput= atoi(userInput.c_str());
        }
        switch (intUserInput) {
            case 1:
                std::cout<<"Program name - ";
                std::cin>>newProgramName;
                std::cout<<"Program size (KB) - ";
                std::cin>>newProgramSize;
                checkIfNewProgram = memory->checkIfNewProgramName(newProgramName);
                
                //Checks if the program name the user entered has already been used or not
                if (checkIfNewProgram && newProgramName != "FREE"){
                   //Uses the correct algorithm the user entered
                    if (algroithmUsed=="best"){
                        memory->addBestFit(newProgramName, newProgramSize);
                    }
                    else{
                        memory->addWorstFit(newProgramName, newProgramSize);
                    }
                }
                else{
                    //Ensures that the user does not enter their program name as 'FREE'
                    if (newProgramName == "FREE"){
                        std::cout<<"Cannot name program 'FREE'\n\n";
                    }
                    else{
                        std::cout<<"\nError, Program "<<newProgramName<<" already running.\n\n";
                    }
                }
                break;
            case 2:
                std::cout<<"Program name - ";
                std::cin>>newProgramName;
                memory->killProgram(newProgramName);
                break;
            case 3:
                memory->fragmentation();
                break;
            case 4:
                memory->print();
                break;
            case 5:
                endProgram = true;
                break;
                
        }
    } while (endProgram == false);
    
    
    return 0;
}




