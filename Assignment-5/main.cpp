//
//  main.cpp
//  ass5
//
//  Created by Jaryd Saevitzon on 4/26/16.
//  Copyright © 2016 Jaryd Saevitzon. All rights reserved.
//

#include <iostream>


int rot13cmp(const void *a, const void *b)
{
    const char *string_1 = *(const char **)a;
    const char *string_2 = *(const char **)b;
    
    //for every character in strings
    for(;;)
    {
        
        int str1 = (int) *string_1;
        int str2 = (int) *string_2;
        
        //Check for nullbytes
        if(str1==10 && str2==10)
            return 0;
        if(str1==10)
            return -1;
        if(str2==10)
            return 1;
        
        //first half of alphabet adds 13
        if( (str1>=65 && str1<=77) || (str1>=97 && str1<=109))
            str1 = str1+13;
        //second half subtracs 13
        else if((str1>=78 && str1<=90) || (str1>=110 && str1<=112))
            str1 = str1-13;
        //same rules here
        if( (str2>=65 && str2<=77) || (str2>=97 && str2<=109))
            str2 = str2+13;
        else if((str2>=78 && str2<=90) || (str2>=110 && str2<=112))
            str2 = str2-13;
        
        //if one is greater than the other return 1 or -1
        if(str1>str2)
            return 1;
        else if (str2<str1)
            return -1;
        
        //else, increment and check again
        string_1++;
        string_2++;
        
        
    }
}

int main()
{
    int test = rot13cmp("\0Dhvpx23\n", "\0Whzcf!\n");

    std::cout<<test;
    
    return 0;
}