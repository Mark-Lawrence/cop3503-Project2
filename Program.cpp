//
//  Program.cpp
//  pa
//
//  Created by Mark Lawrence on 10/19/17.
//  Copyright © 2017 Mark Lawrence. All rights reserved.
//

#include <stdio.h>
#include "Program.hpp"


Program::Program(string programName, int programSize){
    this->programName = programName;
    this->programSize = programSize;
}

string Program::getProgramName(){
    return programName;
}
int Program::getProgramSize(){
    return programSize;
}

void Program::setProgramName(string programName){
    this->programName = programName;
}

void Program::setProgramSize(int programSize){
    this-> programSize = programSize;
}


