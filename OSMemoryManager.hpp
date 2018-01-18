//
//  OSMemoryManager.hpp
//  pa
//
//  Created by Mark Lawrence on 10/19/17.
//  Copyright © 2017 Mark Lawrence. All rights reserved.
//

#ifndef OSMemoryManager_hpp
#define OSMemoryManager_hpp

#include <stdio.h>
#include "Program.hpp"


//struct Program{
//    Program data;
//    Program *next;
//};


class OSMemoryManager{
private:
    Program *head;
    Program *tail;
public:
    OSMemoryManager()
    {
        head=NULL;
        tail=NULL;
    }
    
    void append(string programName, int programSize);
    void addBestFit(string programName, int programSize);
    void addWorstFit(string programName, int programSize);
    void print();
    void killProgram(string programName);
    bool checkIfNewProgramName(string newProgramName);
    void fragmentation();
};


#endif /* OSMemoryManager_hpp */
