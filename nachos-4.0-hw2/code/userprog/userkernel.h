// userkernel.h
//	Global variables for the Nachos kernel, for the assignment
//	supporting running user programs.
//
//	The kernel supporting user programs is a version of the 
//	basic multithreaded kernel.
//
// Copyright (c) 1992-1996 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#ifndef USERKERNEL_H  
#define USERKERNEL_H

#include "kernel.h"
#include "filesys.h"
#include "machine.h"
#include "synchdisk.h"


class SynchConsoleInput;
class SynchConsoleOutput;
class SynchDisk;
class UserProgKernel : public ThreadedKernel {
  public:
    UserProgKernel(int argc, char **argv);
				// Interpret command line arguments
    ~UserProgKernel();		// deallocate the kernel

    void Initialize();		// initialize the kernel 

    void Run();			// do kernel stuff 

    void SelfTest();		// test whether kernel is working

    //<TRACE
    void ExecAll();

    int Exec(char * name, int priority);

    SynchConsoleInput *synchConsoleIn;
    SynchConsoleOutput *synchConsoleOut;

    bool PhysicalPageUsed[NumPhysPages];
    int availablePhysicalPages(){
        int availablePageCount = 0;
        for(int i = 0; i < NumPhysPages; i++){
            if (PhysicalPageUsed[i] == FALSE)
              availablePageCount++;
        }
        return availablePageCount;
    }
    //TRACE>

    Thread* getThread(int threadID){return t[threadID];}

// These are public for notational convenience.
    Machine *machine;
    FileSystem *fileSystem;


#ifdef FILESYS
    SynchDisk *synchDisk;
#endif // FILESYS

  private:
    bool debugUserProg;		// single step user program
	Thread* t[30];
	char*	execfile[30];

    //<TRACE
    int threadPriority[30];
    int threadNum;
    char *consoleIn;
    char *consoleOut;
    //TRACE>
	int	execfileNum;
};

#endif //USERKERNEL_H
