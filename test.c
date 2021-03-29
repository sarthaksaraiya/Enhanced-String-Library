#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "esl.h"

int main(void)
{/*

  char str1[]=""; 
  char str2[]="baby"; 
  char s0[]=""; 
  
  printf("Enter your string");
  string s1 = string_create(gets(str1)); //creating the dynamic string 
  //string can be inputed using gets/fgets
  printf("s1:%s\n", s1);
  printf("Size s1: %d\n\n", string_size(s1));//size of our string*/
    
/*//TESTING STRING_REPLACE FUNCTION
   string_replace(&s1, 7, 5, "Saraiya");
  printf("Replaced String:%s\n", s1);
  printf("Size s1: %d\n", string_size(s1));*/
 /*
  //TESTING STRING_INSERT 
  string_insert(&s1, 3, "_Inserted_");
  printf("s1:%s\n", s1);
  printf("Size s1: %d\n", string_size(s1));*/
  
 /*
  // TESTING STRING_CONCAT
  printf("Enter string to be concatinated:");
  gets(s0 );
  string_cat(&s1,  s0);
  //strcat(s1,s0);
  printf("concatinated string: %s\n", s1);
  printf("Size of concatinated string s1: %d\n", string_size(s1));
 */
   
  
   // TESTING STRING_COPY
  printf("Enter string to be copied:");
  gets(s0 );
  string_copy(&s1, s0);
  printf("copied strings: %s\n", s1);
  printf("sizeof copied string s1: %d\n\n",string_size(s1));
  /*
  // TESTING STRCPY
   printf("size of destination string str2: %d\n",sizeof(str2));
   printf("size of string to be copied : %d\n\n",strlen("babyboo"));
   strcpy(str2,"babyboo");
   printf("copied string: %s\n", str2);
   printf("sizeof copied string str2: %d\n",sizeof(str2));
 
 */
 /*
  //TESTING STRING_NCOPY
   printf("Enter your strings for copyn function");
   gets(str1);  
  string_ncopy(&s1,str1,10);//alter function for memory sizeof
  printf("Copied using string_copyn:%s\n", s1);
  printf("sizeof copied string s1: %d\n",string_size(s1));
  *//*
  //example 2
     printf("\n EXAMPLE 2: \n");
  	string dst= string_create("00000");
    //char src[] = "abcdefghijk";
	char src[] = "abcd";
 
    int buffer_length = string_ncopy(&dst, src, string_size(dst));
 
    if (buffer_length >=string_size(dst)) {
        printf ("String: %s too long: %d (%d expected)\n",src,buffer_length,string_size(dst )-1);
    } 
    printf ("String copied: %s\n", dst);*/
/*
//TESTING STRING_NCAT
  printf("Enter your strings for catn function");
  gets(str1); 
  string_ncat(&s1,str1,10);//alter function for memory sizeof
  printf("Concatinated using string_ncat:%s\n", s1);
  printf("sizeof concat string s1: %d\n",string_size(s1));
  */  
   //TESTING STRING_SPRINTF

char* s1;
char* s2;
int x = 100;
float y = 300; 
char *str = NULL;
char *fmt = "this is a %s";
int size = string_sprintf(&str, fmt, "string");
//convert integer and float values to strings.
string_sprintf(&s1, "%d", x);
string_sprintf(&s2, "%f", y);
printf("s1 = %s\n", s1);
printf("s2 = %s\n", s2);
//printing 
printf("%s\n", str); // this is a string
printf("%d\n", size); // 16

 /*
//TESTING STRING_SEP

	string s= string_create("foobarfoobarfoobar") ;
	string sep = string_create("bar") ;
    char** strings = string_sep(s, sep);

    while(*strings){
        printf("%s ", *(strings));
        free(*(strings++));
    }
	*/
 	 return 0;
}
