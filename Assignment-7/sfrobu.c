#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

//GLOBAL VARS

typedef int bool;
#define true 1
#define false 0

int comparisons = 0;

int sfrob(const void *a, const void *b)
{


  comparisons++;
  const char *string_1 = *(const char **)a;
  const char *string_2 = *(const char **)b;

  //for every character in strings
  while(true)
    {

      int str1 = (int) *string_1;
      int str2 = (int) *string_2;

      //Handles one word subsection of another
      if(str1==' ' && str2==' ')
	return 0;   
      if(str1==' ')
	return -1;
      if(str2==' ')
	return 1;

      //decrypt char
      str1 = str1^42;
      str2 = str2^42;

      //compare size
      if(str1>str2)
	return 1;
      else if (str1<str2)
	return -1;

      //increment pointers
      string_1++;
      string_2++;

      
    }
  
  
}


int main()
{

  
  //allocate enough size
  struct stat f1;
  fstat(0, &f1);

  int allocSize;

  //  if(S_ISREG(f1.st_mode))
  // allocSize = f1.st_size;
  // else
    allocSize = 5; 


  char *p = (char*) malloc(allocSize);

  //If unable to allocate space, return error
  if(p==NULL)
    {
      fprintf( stderr,"Cannot allocate memory");
      exit(1);
    }

  //keep track of count of characters
  //and number of words (number of spaces+1)
  int count = 0;
  int numWords = 0;
  while(true)
    {

      char c;
      //read c from std input
      if(read(0, &c, 1)<=0)
	break;;
 
      if(c==' ') {numWords++;}

     
      p[count] = c;
      count++;

      
      //need to allocate more space
      if(count==allocSize)
	{
	  //Double the size (this will end up growing exponentially
	  allocSize*=2;
	  p = (char*)realloc(p,allocSize);

	  if(p==NULL)
	    {
	      fprintf(stderr,"Cannot allocate memory");
	      exit(1);
	    }
	  
	}
      
    }
  //if no words
  if(count==0)
    return 0;

  //need to add a newline to end so that i can finish off the thing later
  if(p[count-1]!=' ')
    {
      p[count]=' ';
      count++;
      numWords++;
    }

  //pointer to beginning of each word
  char **pToP = (char**)malloc(sizeof(char*)*(numWords+1));
  int pToPIndex = 0;
 
  if(pToP==NULL)
    {
      fprintf(stderr,"Cannot allocate memory");
      exit(1);
    }


  int index = 0;
  //give me an array (pToP) of pointers to the beginning of each word in p
  for(int i = 0; i<numWords; i++)
    {
     
      if(p[index]!=' ')
	{
	  pToP[pToPIndex] = &p[index];
	  pToPIndex++;

	  while(p[index]!=' ')
	    {
	      index++;
	    }
	}
      //this is accounting for multiple spaces in a row
      //and therefore "false" words
      bool countInRow = false; 
     
      while(p[index]==' ')
	{
	  index++;
	  if(countInRow)
	    i++;
	  countInRow=true;
	}
      
      
    }

  qsort(pToP, pToPIndex, sizeof(char*), sfrob);

  //print out each word to standard output
  //Words are seperated by spaces
  char sp = ' ';
  for(int j = 0; j<pToPIndex; j++)
    {
      char *c = pToP[j];
      while((*c)!=' ')
	{
	  // printf("%c", *c);
	  write(1, c, 1);
	  c++;
	}
      write(1,&sp,1);
      
    }

  free(p);
  free(pToP);

  fprintf(stderr, "Comparisons: %d \n", comparisons);
  
  return 0;
}
