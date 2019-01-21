#include<stdio.h>
#include<conio.h>
#include <stdlib.h>
#include "WC_Header.h"
int Array_Size=0;;
int Array_Index=0;
int Unique_Words=0;
FILE *Writer;

// A struct that holds some information about the word
struct WordElement
{
	int Count;
	char Word[50];
	int Printed;
};

struct WordElement *StructPointer; //just a pointer to a structure

// the create array function
int Create_Array(int Size){
//dynamically allocates the memory depending on how many words there are
StructPointer = malloc((Size*50) * sizeof(StructPointer));
if(NULL == StructPointer)
{
   perror("malloc failure");
   exit(EXIT_FAILURE);
}

Array_Size = Size;

return 0;
}
int run_Count=0;
int Add_To_Array(char Word[50]){
	int Word_Found=0;
	
	//a simple loop that runs to check if the current word is already in an array, if it is, just increment its count
	for(int i=0; i < Unique_Words && Word_Found!=1; i++)
	{
		if(strcmp(StructPointer[i].Word, Word)==0)
		{
			StructPointer[i].Count++;
			Word_Found=1;

		}
	
	}
	
	if(Word_Found==0) // if the above if statement doesn't evaluate, this runs and adds the word to the array
	{
		
		strcpy(StructPointer[Array_Index].Word, Word); //copying the word passed by the main function to the struct array at a specific 
		StructPointer[Array_Index].Printed=0; //initializing thee value 
		StructPointer[Array_Index].Count=1; //initializing thee value 
		Array_Index++;
		Unique_Words++;
	}
	return 0;
}

//A function that prints everything thats in the array 
int Print_All(char File_Name[50])
{
	//opening up a file to write to, if no output file is provided, it will simply print to console
	if(strcmp(File_Name, "")==0)
	{
		Writer = stdout;
		Output_Path=1;
	}
	else
	{
	Writer = fopen(File_Name, "w");
	}

	fprintf(Writer, "Total Number of Words: %d , \t Total Number of Unique Words: %d\nWord    :    Count\n\n", Array_Size, Unique_Words);
	
	int printCount=0;
	char Sort_Word[50];
	int Sort_Count=0;
	
	//A simple sorting algorithm that i wrote, it uses nested for loops and if statements
	 for(int i=0; i < Unique_Words ; i++)
	{
		Sort_Count=0;
			for(int j=0; j < Unique_Words; j++)
			{
				
				//If  the count is the same just print the word
				if(StructPointer[j].Count == Sort_Count && StructPointer[j].Printed ==0 )
				{
					fprintf(Writer, "%s    :    %d\n",StructPointer[j].Word, StructPointer[j].Count);
					StructPointer[j].Printed=1;
					printCount=1;
				}
				
				//if the current words count is greater than the previously greater one, replace the values
				
				else if(StructPointer[j].Count > Sort_Count  && StructPointer[j].Printed ==0)
				{
					strcpy(Sort_Word, StructPointer[j].Word);
					Sort_Count = StructPointer[j].Count;
					StructPointer[j].Printed=1; 
					printCount=1;	
				}

			}
			//another check in place that if the 2nd loop prints all the words, it prevents the first loop from printing garbage values
			if(printCount==1){
				
			fprintf(Writer, "%s    :    %d\n",Sort_Word, Sort_Count);
			printCount=0;
			}
	
	} 
	//freeing the memory and closing the stream
	free(StructPointer);
	if(Output_Path==0)
	{
		fclose(Writer);
	}
	printf("Output Saved!\n");
	return 0;
}
