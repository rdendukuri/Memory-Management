/*******************************************************************
Name : Rahul Krishna Dendukuri
Z-ID : Z1749863
Course : CSCI 580-02
Program :Class definition  File for  Assignment 5
Desciption : A Cpp that contains the defination of constructos and function of the Block class declared in block.h
Due Date : 10/28/2015
*********************************************************************/
#include "Assign5.h"

#include "block.h"
/*
Function : Block(Constructor for the Block class)
Paramenters : void
Returns : void
*********************************************************************/
Block::Block()
{
	startAddress=0;
        size=0;
        Pid="";
        Bid="";
        next=0;

	
}
/*
Function : printBlocks
Paramenters : void
Description:Prints the contents of the List
scope: Block class
Returns : void
*********************************************************************/
void Block::printBlocks()
{
	Block* t=this;
	int sum=0;
	if(t==0)
	{
		cerr<<"Empty list,No blocks"<<endl;
		return;
	}
	while(t!=0)
	{
		
		cerr<<"Starting address of the block:"<<t->startAddress<<endl;
		cerr<<"Size of the block:"<<t->size<<endl;
		sum=sum+t->size;
		t=t->next;
	}
	cerr<<"Total size occupied by the blocks:"<<sum<<endl;
}

/*
Function : searchBF
Paramenters : int size - The size of the required block
              string mode-the Best/First fit algorithm used
Decription :  Returns the pointer to the block that best fits the size taken as argument using either First-Fit or Best -Fit algorithm
Returns : Block*
*********************************************************************/

Block* Block::searchBF(int size,string mode)
{
	
        Block* t=this;
	int i=0;
	int k=0;
	int j=0;
        if(mode=="F")//Searching for the First-Fir block
		while(t!=0)
       		 {
			if(t->size>=size)
				return t;
                	t=t->next;
       		 }
	else if(mode=="B")
	{//Best fit algorithm
		 while(t!=0)
                 {
			
			i++;
                        if(t->size==size){
				//return the block address if you findthe exact block	
				return t;
			

				}
			else if(t->size>size)
			{
				
				if(k==0){
					k=t->size-size;
					j=i;
					}
				else if(k>t->size-size){//code clokc that records the best-fitting block
					k=t->size-size;//the current best fitting measure
					j=i;//j is the index of the best fitting block
				}
			}
                        t=t->next;
                 }
		
		if(k>0){//Traversing the list to get to the best fitting index
			t=this;
			for(i=0;i<j-1;i++)
				t=t->next;
			return t;
			}
	}
	else{//error message of wrong method is choses
		cerr<<"Wrong algorithm:Either B/F should be the third argument"<<endl;
		exit(-1);
	    }
	return 0;//0 i returned if a proper block is not found accourding to the algorithm

}
/******************************************************************************
Function : consolidate
Paramenters : void
Description: Parses through the entire Memory List and joins two blocks that beside each other
scope:Block class object
Returns : void
*********************************************************************/

void Block::consolidate()
{
	
	Block* t=this;
	while(t!=0 && t->next!=0)
	{//main loop runnign through the list
		if((t->startAddress+t->size)==(t->next)->startAddress && ((t->next)->size+t->size<=4*MB))
		{
			cerr<<"Merging the blocks at"<<t->startAddress<<"and"<<(t->next)->startAddress<<endl;
			t->size=t->size+(t->next)->size;//incrementing size of  the block to merged
			t->next=(t->next)->next;//dechaining  the block in between
			
		}
		else
			t=t->next;	//incrementing if block need not be merged wit hany neighbouring block
	}
	
}


