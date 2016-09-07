/*******************************************************************
Name : Rahul Krishna Dendukuri                          FALL 2015
Z-ID : Z1749863
Course : CSCI 580-02
Instructor : Harry Hutchins
TA : Sweta Thota
Program : Assignment 5
Desciption : A C++ program that simulates the Memory management using Best-fit and First fit algorithms
Due Date : 10/28/2015
*********************************************************************/
#include "Assign5.h"
#include "block.h"
int deallocate(string s1,string s2);
Block* InUse=0;
Block* Avail=0;
/*
Function : Main
Paramenters : int argc - No. of command line arguments
              char **argv-Array of pointers for the the command line arguments
Returns : int
*********************************************************************/

int main(int argc,char** argv)
{
	int i;
	int c=0;

  	if (argc!=3)//Checking if right number of command line arguments have been entered while executing the program
        {

        	        cerr<<"usage:_"<<argv[0]<<"_inputFile_B/F\n"; //Printing out the error message with correct usage of the Program
               		 return -1;
        }

	Avail=(Block*) new Block();
	Avail->size=1*MB;
	Avail->startAddress=3*MB;
	Avail->next=0;
	Block* t=Avail;
	for(i=0;i<2;i++)
	{//Initializing Available list
		t->next=(Block*) new Block();
		(t->next)->size=2*MB;
		(t->next)->startAddress=t->startAddress + t->size;
		t=t->next;

	}

	for(i=0;i<2;i++)
	{//Initializing the Available list

		 t->next=(Block*) new Block();
                (t->next)->size=4*MB;
                (t->next)->startAddress=t->startAddress + t->size;
                t=t->next;

		
	}
	 t->next=0;
         ifstream In;
         int k;
         int size;
         string trans,s1,s2;
         In.open(argv[1]);
	if(In==NULL)
	{//print error message and exit if file not found
		cerr<<"File not found"<<endl;
		exit(-1);
	}
         In >> trans;
         while (trans != "?")
         {//Loading untill ? is reached in the file
		if((c++)%HOW_OFTEN==0)
		{
			cerr<<endl<<"Counter:"<<c-1;
			cerr<<endl<<"The Blocks of memory AVAILABLE"<<endl;
			Avail->printBlocks();
			cerr<<endl;
			cerr<<"The Blocks of memory IN USE are as follows"<<endl<<endl;
			InUse->printBlocks();
		}
               
		if(trans=="L"||trans=="A")
		{
			/*Search the Avail list for the best-fitting block.Create a new block of the correct size, recording the process */
			In>>s1;
			In>>k;
			 cerr<<endl<<"Transaction:Loading/Allocation of PID"<<s1<<" with memory size"<<k<<endl;
			if((t=Avail->searchBF(k,argv[2]))!=0)
			{
				
				Block* b= new Block();
//				updating the deatails of the block to allocated
				b->size=k;
				b->Pid=s1;
				In>>b->Bid;
				t->size=t->size-k;// Decrease the block found on Avail by that amount
				b->startAddress=t->startAddress;
				t->startAddress=t->startAddress+k;
				if(t->size==0)
				{// If the block on Avail is now of size 0,Delete it
					Avail->deleteBlock(t);
				}
				b->next=InUse;
				InUse=b;
				cerr<<endl<<"Process loaded/allocated with PID:"<<b->Pid<<endl;//success
			}
			else
				cerr<<endl<<"Could not find suitable block"<<endl;
					
				
		}
		else if(trans=="D")
		{

			In>>s1;
			In>>s2;
			cerr<<endl<<"Transacrion:Deallocation of Process of PID"<<s1<<" "<<"BID:"<<s2<<endl;
			if(deallocate(s1,s2)==1)//if deallcation successfull print success message
				cerr<<"Succesfull deallocation"<<endl;
			Avail->consolidate();

		}
		else if(trans=="T")
		{
		
		
			In>>s1;
			cerr<<"Termination request for: "<<s1<<endl;
			int m=0;
			t=InUse;
			while(t!=0)
			{//loop to weed out the blocks that are allocated to Process to be terminated
				if(t->Pid==s1)
				{
					m=1;
					s2=t->Bid;
					if(deallocate(s1,s2)==1)
						cerr<<"Block"<<s2<<"of Process ID:"<<s1<<" succesfull deallocated"<<endl;
					Avail->consolidate();
					t=InUse;
				}
				
				else
					t=t->next;
			}
			if(m==1)
				cerr<<endl<<"Process ID :"<<s1<<" Terminated"<<endl;
			else
				cerr<<endl<<"Process ID :"<<s1<<"Could not be located"<<endl;
		

		}
		In>>trans;
		
         }
        In.close();	
	cerr<<endl<<"The run has ended"<<endl<<endl;
	cerr<<"The Blocks of memory available are follows"<<endl<<endl;
        Avail->printBlocks();
        cerr<<endl;
        cerr<<"The Blocks of memory in use are as follows"<<endl<<endl;
        InUse->printBlocks();
	
	return 0;	
}
/*
Function : deleteBlock
Paramenters : Block* p - Reference to the block that is to be deleted
Description:The  block that occupies the memory is freed              
Returns : void
*********************************************************************/

void Block::deleteBlock(Block* p)
{

        Block* t=this;
        if(t==p)
        {
		
                Avail=this->next;
               
        }
        else
        {
		
                 while(t->next!=p)
                 {
         
                        t=t->next;
                 }
                 t->next=(t->next)->next;
//		 t=0;
        }
        delete p;
}
/******************************************************************
Function : deallocate
Paramenters : string s1 - PID of the processs in the block
              string s2-BID of the block in memory
Pseudo Code: 
Search the InUse list for the block with the correct process ID
and block ID.  (The combination of the two should be unique.)

If it is not found
  return 0
Else
  Detach the block from InUse
  Insert it into Avail in order by starting address
  Traverse the Avail list combining any two consecutive blocks
  for which the ending address of the first block is the starting
  address of the second block, provided the combined block is no
   more than 4 MB
  return 1
End-If.

Returns : int
*********************************************************************/
int deallocate(string s1,string s2)
{
	Block* t=InUse;
	if(t->next==0 && t->Pid==s1 && t->Bid==s2)
	{//deallocation if there is only one block in the List to be deallocated
		
		Block* p=t;
		p->Pid="";
		p->Bid="";
		t=0;
		InUse=0;
		if(Avail->startAddress>p->startAddress)
		{//attaching to head of Available list
			
                        p->next=Avail;
                        Avail=p;
			
                }
		  else
                {
			
			t=Avail;
                        while(!((t->next)->startAddress>p->startAddress && (t->startAddress<p->startAddress)))
                        {
                                t=t->next;
                                if(t->next==0)
                                        break;
                        }
                                p->next=t->next;
                                t->next=p;
               }

		return 1;	
	}
	
	if(t->Pid==s1 && t->Bid==s2)
	{//IF the block to be deallocated is the first block
		Block* p =t;
		p->Pid="";	
		p->Bid="";
		InUse=InUse->next;
		 if(Avail->startAddress>p->startAddress)
                {//attaching to head of avail
                        
                        p->next=Avail;
                        
                        Avail=p;
                        
                }
                  else
                {//attaching the block somewhere in between the Available List
                        
                        t=Avail;
                        while(!((t->next)->startAddress>p->startAddress && (t->startAddress<p->startAddress)))
                        {
                                t=t->next;
                                if(t->next==0)
                                        break;
                        }
                                p->next=t->next;
                                t->next=p;
               }

                return 1;

			
	}
	
//	The rest of the part is executed if the block is somewhere in betwen the list

        while(!((t->next)->Pid==s1 && (t->next)->Bid==s2))
	{//Searching and reaching the block that is just before the one that needs to deallocated
		t=t->next;
		if(t->next==0)
			break;
	}
	if(t->next==0)
	{//if required block not found,return 0 and print error message
		cerr<<"Could not deallocate the block"<<endl;
		return 0;
	}

                Block* p1=t->next;
                t->next=(t->next)->next;
		p1->Pid="";
		p1->Bid="";
                if(Avail->startAddress>p1->startAddress)
                {
                	p1->next=Avail;
                        Avail=p1;
                }
                else
                {
                        t=Avail;
                        while(!((t->next)->startAddress>p1->startAddress && (t->startAddress<p1->startAddress)))
                        {
                        	t=t->next;
                                if(t->next==0)
                                	break;
                        }
                                p1->next=t->next;
                                t->next=p1;
               }
	return 1;
}
