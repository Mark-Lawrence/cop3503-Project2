//
//  OSMemoryManager.cpp
//  pa
//
//  Created by Mark Lawrence on 10/19/17.
//  Copyright © 2017 Mark Lawrence. All rights reserved.
//

#include <stdio.h>

#include "OSMemoryManager.hpp"
#include "iostream"
#include <string>
using namespace std;

void OSMemoryManager::append(string programName, int programSize){
   //Extends the linked list, adds a new node to the end with prorgamName and programSize
    Program *temp=new Program;
    temp->setProgramName(programName);
    temp->setProgramSize(programSize);
    
    temp->next=NULL;
    if(head==NULL)
    {
        head=temp;
        tail=temp;
        temp=NULL;
    }
    else
    {
        tail->next=temp;
        tail=temp;
    }
}

void OSMemoryManager::print(){
    Program *temp=new Program;
    temp=head;
    int count = 0;
    //Print until reach the end of the linked list
    while(temp!=NULL){
        if (temp->getProgramName() != "FREE"){
            std::cout<<" "<<temp->getProgramName()+" "<<"\t";
        }
        else {
            std::cout<<temp->getProgramName()<<"\t";
        }
        temp=temp->next;
        count++;
        //creates a grid of 8 by 4
        if (count == 8){
            std::cout<<"\n";
            count=0;
        }
    }
}



void OSMemoryManager::addBestFit(string programName, int programSize){
    int count = 0;
    int lengthOfCurrentBestFit = 0;
    Program *current = new Program;
    Program *couldBeBestFit = new Program;
    Program *bestFit = new Program;
    int numberOfPages = programSize/4;
    int numberOfPagesCarry = programSize%4;
    
    int lengthOfBestFit = 0;
    bool thereIsSpace = false;
    bool lookingForLargerGap = false;
    bool bestFitIsEmpty = true;
    current = head;
    
    //Makes the correct number of pages needed in case there is a carry
    if (numberOfPagesCarry != 0){
        numberOfPages = numberOfPages+1;
    }
    
    for (int i =0; i<32; i++) {
        //If the current name is Free, add to length of best fit to find teh shortest space
        if (current->getProgramName() == "FREE") {
            lengthOfBestFit++;
            if (lookingForLargerGap == false){
                count++;
                couldBeBestFit = current;
                lookingForLargerGap = true;
            }
        }
        
        //If current is no longer 'Free' and there is space, set couldBeBestFit to current best fit. This can only
        //be overridden if a smaller gap is found
        if (count != 0 && current->getProgramName() != "FREE"){
            if (count > lengthOfCurrentBestFit && count>=numberOfPages){
                lengthOfCurrentBestFit = count;
                bestFit = couldBeBestFit;
                bestFitIsEmpty = false;
                thereIsSpace = true;
                lengthOfBestFit = 0;
            }
            count = 0;
            lookingForLargerGap = false;
        }
        current = current->next;
    }
    
    //If best fit is empty, meaning that the memory is completely free, set it to the top node
    if (bestFitIsEmpty){
        bestFit = couldBeBestFit;
    }
     
    if (lengthOfBestFit>=numberOfPages){
        //Change the name and size of the memory as long as there is enough space for it
        //Loop until all the pages are changed
        if (thereIsSpace || bestFitIsEmpty){
            for (int i = 0; i<numberOfPages; i++) {
                bestFit->setProgramName(programName);
                bestFit->setProgramSize(programSize);
                bestFit = bestFit->next;
            }
            std::cout<<"\nProgram "<<programName<<" added successfully: "<<numberOfPages<<" page(s) used.\n\n";
        }
    }
    //Print error message if there is not enough space
    else{
        std::cout<<"\nError, not enough memory for Program "<<programName<<"\n\n";
    }
    
}

void OSMemoryManager::addWorstFit(string programName, int programSize){
    int lengthOfCurrentWorstFit = 0;
    Program *current = new Program;
    Program *couldBeWorstFit = new Program;
    Program *worstFit = new Program;
    int numberOfPages = programSize/4;
    int numberOfPagesCarry = programSize%4;
    
    int lengthOfPotentialCurrentWorstFit = 0;
    bool thereIsSpace = false;
    bool firstEmptySpot = false;
    bool worstFitIsEmpty = true;
    current = head;
    
    //Makes the correct number of pages needed in case there is a carry
    if (numberOfPagesCarry != 0){
        numberOfPages = numberOfPages+1;
    }
    //Loop through the entire memory linked list
    for (int i =0; i<32; i++) {
        
        //If the current name is Free, add to length of best fit to find the biggest space
        if (current->getProgramName() == "FREE") {
            lengthOfPotentialCurrentWorstFit++;
            // Adds the current node to only the first 'FREE' spot
            if (firstEmptySpot==false){
                couldBeWorstFit = current;
                firstEmptySpot = true;
            }
        }
        //Continue only if the current page is not free and if the number of free spaces is bigger than number
        //of pages need; or if we are at the last page in memory
        if ((current->getProgramName() != "FREE" && lengthOfPotentialCurrentWorstFit>=numberOfPages) || i==31){
            //Add the latest saved couldBeWorstFit to the worst fit. This can be overridden if a bigger gap is found
            if (lengthOfPotentialCurrentWorstFit>lengthOfCurrentWorstFit){
                worstFit=couldBeWorstFit;
                lengthOfCurrentWorstFit = lengthOfPotentialCurrentWorstFit;
                lengthOfPotentialCurrentWorstFit = 0;
                worstFitIsEmpty = false;
                thereIsSpace = true;
                firstEmptySpot = false;
            }
        }
        current = current->next;
    }
    
    
    //If best fit is empty, meaning that the memory is completely free, set it to the top node
    if (worstFitIsEmpty){
        worstFit = couldBeWorstFit;
        lengthOfCurrentWorstFit = numberOfPages;
    }
    
    
    if (lengthOfCurrentWorstFit>=numberOfPages){
        if (thereIsSpace || worstFitIsEmpty){
            //Change the name and size of the memory as long as there is enough space for it
            //Loop until all the pages are changed
            for (int i = 0; i<numberOfPages; i++) {
                worstFit->setProgramName(programName);
                worstFit->setProgramSize(programSize);
                worstFit = worstFit->next;
            }
            std::cout<<"\nProgram "<<programName<<" added successfully: "<<numberOfPages<<" page(s) used.\n\n";
        }
    }
    else{
        std::cout<<"\nError, not enough memory for Program "<<programName<<"\n\n";
    }
    
    
}
void OSMemoryManager::killProgram(string programName){
    Program *current = new Program;
    Program *programToDelete = new Program;
    int programsDeleted = 0;
    current=head;
    
    //First checks to make sure that the user is trying to kill a program that actually exists
    if (!checkIfNewProgramName(programName)){
        for (int i = 0; i<32; i++) {
            //Loops through the memory, checks if it can find a program matching the name entered by user
            //If a match is found, its name is rewritten to 'FREE' and size back to 0
            if (current->getProgramName() == programName){
                programToDelete = current;
                programToDelete->setProgramName("FREE");
                programToDelete->setProgramSize(0);
                programsDeleted++;
            }
            current = current->next;
        }
        std::cout<<"\nProgram "<<programName<<" sucessfully killed, "<<programsDeleted<<" page(s) reclaimed\n\n";
    }
    else{
        std::cout<<"\nProgram "<<programName<<" does not exist.\n\n";
    }
    
    
}

void OSMemoryManager::fragmentation(){
    Program *current = new Program;
    current=head;
    int numberOfFragments=0;
    bool streakOfFree = false;
    for (int i = 0; i<32; i++) {
        
        //If there a bit of memory named "FREE" and there has been a streak of free, add on to number of fragments
        if (current->getProgramName()=="FREE" && !streakOfFree){
            numberOfFragments++;
            streakOfFree = true;
        }
        if (streakOfFree && current->getProgramName() != "FREE"){
            streakOfFree = false;
        }
        current = current->next;
    }
    std::cout<<"\nThere are "<<numberOfFragments<<" fragment(s).\n\n";
}

bool OSMemoryManager::checkIfNewProgramName(string newProgramName){
    Program *current = new Program;
    current=head;
    for (int i = 0; i<32; i++) {
        //Checks if the program name is new or not 
        if (current->getProgramName() == newProgramName){
            return false;
        }
    current = current->next;
    }
    return true;
}


