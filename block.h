/*******************************************************************
Name : Rahul Krishna Dendukuri
Z-ID : Z1749863
Course : CSCI 580-02
Program :Header File for  Assignment 5
Desciption : A Header file that contains all the libraries required for writing the logic of the source program
Due Date : 10/28/2015
*********************************************************************/


#ifndef block_H
#define block_H
#include "Assign5.h"

class Block
{
	public:
		int startAddress;
		int size;
		string Pid;
		string Bid;
		Block* next;
		Block();
		void printBlocks();
		void addToTail(Block b);
		Block* searchBF(int size,string mode);
		void deleteBlock(Block* p);
		void consolidate();
};


#endif
