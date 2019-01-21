// 	Hari Kharel - 40312824
// 	23/02/2018
//	This program is designed to take in an input and an output file to process.
//	It gets every word from the input file and modifies it by removing any punctuations
//  or capital letters, if specified by the user. 
//  


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DynamicArray.c"
#include "WC_Header.h"

char Input_File[50];
char Output_File[50];
int Output_Path=0;
int Ignore_Case=0;
int Word_Count =0;
int Print_To_Console=0;

int main(int argc, char **argv) {

	//A loop to check the actual arguments and take apportiate path

	for(int i=0; i < argc; i++)
	{	
		if(strcmp(argv[i], "-i")==0 && argv[i+1] != NULL)
		{
			strcpy(Input_File, argv[i+1]);
		}
		else if(strcmp(argv[i], "-o")==0 && argv[i+1] != NULL)
		{
			strcpy(Output_File, argv[i+1]);
		}
		else if(strcmp(argv[i], "-c")==0)
		{
			Ignore_Case=1;
			printf("Case will be ignored!\n");
		}	
	}
	while(strcmp(Input_File, "")==0)
	{
		printf("Please provide an input file name, with its extension\n");
		scanf("%s", Input_File);
	}

	File_Processor();
	Print_All(Output_File);
}
//a Function thats reads each word from the file, removes punctuations and capital letters if required, then it calls Add to array function 
int File_Processor()
{
	//opening the File reader here
	FILE* File_Editor;
	File_Editor = fopen(Input_File, "r");
	
	//just a check in place to see if the specified file is real or not
	if(File_Editor==NULL)
	{
		printf("The file is not found, The program will now terminate\n");
		exit(0);
	}
	//a loop that runs through the entire text file and gets the number of total words, needed for dynamic memory allocation 
	while(!feof(File_Editor))
	{
		char Temp_Word[50];
		fscanf(File_Editor, "%s", Temp_Word);
		Word_Count++;
	}
	fclose(File_Editor);
	//calling the create array function that creates an array big enough to hold all the words 
	Create_Array(Word_Count);
	//opening the input file again, this time, to process the words
	File_Editor = fopen(Input_File, "r");
	while(!feof(File_Editor))
	{
		
		char Raw_Word[50];
		fscanf(File_Editor, "%s", Raw_Word);
		
		//Removing Punctuation
		char Edited_Word[50]="";
		int Edit_Count=0;
		//a loop that runs through the enire word to process it
		for(int i=0; i<Raw_Word[i]; i++)
			{
				//A simple if statement to check if the current character is a punctuation
				if(isalpha(Raw_Word[i]))
				{
					//checking if the case needs to be ignored
					if(Ignore_Case==1)
					{
						Raw_Word[i] = tolower(Raw_Word[i]);
					}
				
					Edited_Word[Edit_Count] = Raw_Word[i];
					Edit_Count++;
				}
			}
		//calling the add to array function to store the edited word 
		Add_To_Array(Edited_Word);
	}
	//closing the file
	fclose(File_Editor);
	return 0;
}