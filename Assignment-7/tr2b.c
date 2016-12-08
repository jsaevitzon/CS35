#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

  if (argc!=3)
    {
      printf("Need two strings");
      exit(0);
    }
  if(strlen(argv[1])!=strlen(argv[2]))
    {
      printf("Need same string size");
      exit(0);
    }

  char* chf = argv[1];
  char* cht = argv[2];
  
  int ch;
  int lengthf = strlen(chf);
  
  while((ch=getchar())!=EOF)
    {
      for(int i = 0; i < lengthf; i++)
	{
	  if(chf[i]==ch)
	    {
	      ch=cht[i];
	      break;
	    }
	}
      putchar(ch);
    }


  
  return 0;
}
