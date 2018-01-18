//
//  Program.hpp
//  pa
//
//  Created by Mark Lawrence on 10/19/17.
//  Copyright © 2017 Mark Lawrence. All rights reserved.
//

#ifndef Program_hpp
#define Program_hpp

#include <string>
using namespace std;

class Program{
private:
    string programName;
    int programSize;
public:
    Program *next;
    Program(){}
    Program(string programName, int programSize);
    string getProgramName();
    int getProgramSize();
    void setProgramName(string programName);
    void setProgramSize(int porgramSize);
};

#include <stdio.h>

#endif /* Program_hpp */
