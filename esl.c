
#include "esl.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

typedef struct string_data string_data;

struct string_data {
	str_size alloc; // stores the number of bytes allocated
	str_size length;
	char buff[];
};
/*The dangling pointer errors can be avoided by initializing the pointer to the NULL value. If we assign the NULL value to the pointer, then the pointer will not point to the de-allocated memory. Assigning NULL value to the pointer means that the pointer is not pointing to any memory location.*/
string_data* string_alloc(str_size length) 
{
	string_data* s_data = malloc(sizeof(string_data) + length + 1); // plus 1 for null terminator
	if (s_data!=NULL){//The allocation may fail if the memory is not sufficient. In this case, it returns a NULL pointer. So, you should include code to check for a NULL pointer.
	s_data->alloc = length+1;
	s_data->length = length;}
	return s_data;
 }

 string_data* string_realloc(string_data* s_data,str_size length)
 {
	 s_data = realloc(s_data,sizeof(string_data) + length + 1); // plus 1 for null terminator
	if(s_data == NULL) 
     printf("Couldn't allocate memory!") ;
 else { 
	s_data->alloc = length+1;
    s_data->length = length;}
	return s_data;
	  }

string_data* string_get_data(string s) {
	return (string_data*)&s[-sizeof(string_data)];
}

string string_create(const char* str) {
	string_data* s_data = NULL;
	
	if (str != NULL) {
		str_size str_length = strlen(str);
		s_data = string_alloc(str_length);
		memcpy(&s_data->buff, str, str_length);
		s_data->buff[str_length] = '\0';
	} else {
		s_data = string_alloc(0); // will only allocate enough for a null terminator
		s_data->buff[0] = '\0';
	}
	
	return s_data->buff;
}

bool string_has_space(string_data* s_data) {
	// allocate based on s_data->length + 1 to account for the null terminator
	return s_data->alloc - (s_data->length + 1) > 0;
}

void string_add_char(string* s, char c) {
	string_data* s_data = string_get_data(*s);
	
	if (!string_has_space(s_data)) {
		str_size new_alloc = s_data->alloc * 2;
		s_data = realloc(s_data, sizeof(string_data) + new_alloc);
		if(s_data == NULL) 
     printf("Couldn't allocate memory!") ;
 else { 
	s_data->alloc = new_alloc;}
	}
	s_data->buff[s_data->length++] = c;
	s_data->buff[s_data->length] = '\0'; // add the new null terminator
	
	*s = s_data->buff;
}

void string_cat(string* s, const char* str) {
	string_data* s_data = string_get_data(*s);
	str_size str_length = strlen(str);
	str_size new_length = s_data->length + str_length;
	str_size oldL=s_data->length;
	
	// make sure there is enough room for new characters and null terminator
	if (s_data->alloc <= new_length + 1) {
		string_realloc( s_data,new_length);
	}	
	// copy str chars
	memcpy(&s_data->buff[oldL], str, str_length);
	
	s_data->buff[new_length] = '\0'; // add new null terminator
	*s = s_data->buff;
	
	
	
}

void string_insert(string* s, str_size pos, const char* str) {
	string_data* s_data = string_get_data(*s);
	str_size str_length = strlen(str);
	str_size new_length = s_data->length + str_length;
	// make sure there is enough room for new characters and null terminator
	if (s_data->alloc <= new_length + 1) {
		string_data* new_s_data = string_alloc(new_length);
		memcpy(new_s_data->buff, s_data->buff, pos); // copy leading characters
		memcpy(&new_s_data->buff[pos+str_length], &s_data->buff[pos], s_data->length-pos); // copy trailing characters
		free(s_data);
		s_data = new_s_data;
		
	} else {
		memmove(&s_data->buff[pos], &s_data->buff[pos+str_length], s_data->length - pos); // move trailing characters
	}
	
	s_data->length = new_length;
	
	// copy str chars
	memcpy(&s_data->buff[pos], str, str_length);
	
	s_data->buff[new_length] = '\0'; // add new null terminator
	
	*s = s_data->buff;
}

void string_replace(string* s, str_size pos, str_size len, const char* str) {
	string_data* s_data = string_get_data(*s);
	str_size str_length = strlen(str);
	
	str_size new_length = s_data->length + str_length - len;
	
	// make sure there is enough room for new characters and null terminator
	if (s_data->alloc <= new_length + 1) {
		string_data* new_s_data = string_alloc(new_length);
		memcpy(new_s_data->buff, s_data->buff, pos); // copy leading characters
		memcpy(&new_s_data->buff[pos+str_length], &s_data->buff[pos+len], s_data->length-pos-len); // copy trailing characters
		free(s_data);
		s_data = new_s_data;
		
	} else {
		memmove(&s_data->buff[pos+str_length], &s_data->buff[pos+len], s_data->length-pos-len); // move trailing characters
	}
	
	s_data->length = new_length;
	
	// copy str chars
	memcpy(&s_data->buff[pos], str, str_length);
	
	s_data->buff[new_length] = '\0'; // add new null terminator
	
	*s = s_data->buff;
}

void string_remove(string s, str_size pos, str_size len) {
	string_data* s_data = string_get_data(s);
	// anyone who puts in a bad index can face the consequences on their own
	memmove(&s_data->buff[pos], &s_data->buff[pos+len], s_data->length - pos);
	s_data->length -= len;
	s_data->buff[s_data->length] = '\0';
}

void string_free(string s) {
	free(string_get_data(s));
}

str_size string_len(string s) {
	return ((str_size*)s)[-1];//to exclude the null character 3
}
str_size string_size(string s) {
	return ((str_size*)s)[-2];//to exclude the null character 4
}

str_size string_get_alloc(string s) {
	return ((str_size*)s)[-2];
}


str_size string_ncat(string* dst , const char* src , str_size maxlen)
{
	string_data* s_data=string_get_data(*dst) ;
	str_size src_length = strlen(src);	
	if (src_length+s_data->length+1 < maxlen)
		maxlen=src_length+s_data->length+1 ;
	string_realloc( s_data,maxlen-1);
	char *d = s_data->buff;
	const char *s = src;
	str_size n = maxlen;
	str_size dlen;

	/* Find the end of dst and adjust bytes left but don't go past end */
	while (n-- != 0 && *d != '\0')
		d++;
	dlen = d - s_data->buff;
	n = maxlen - dlen;

	if (n == 0)
		return(dlen + strlen(s));
	while (*s != '\0') {
		if (n != 1) {
			*d++ = *s;
			n--;
		}
		s++;
	}
	*d = '\0';
	*dst=s_data->buff;
	return(dlen + (s - src));	/* count does not include NUL */
}

str_size string_ncopy(string* dst , const char* src , str_size maxlen)
{
	string_data* s_data=string_get_data(*dst) ;
	str_size src_length = strlen(src);	
	if (src_length+1 < maxlen)
		maxlen=src_length+1;
	string_realloc( s_data,maxlen-1);
	char *d = s_data->buff;
	const char *s = src;
	size_t n = maxlen;
	/* Copy as many bytes as will fit */
	if (n != 0) {
		while (--n != 0) {
			if ((*d++ = *s++) == '\0')
				break;
		}
  }
	/* Not enough room in dst, add NUL and traverse rest of src */
	if (n == 0) {
		if (maxlen != 0)
			*d = '\0';		/* NUL-terminate dst */
		while (*s++)
			;
	}
	*dst=s_data->buff;
	return(s - src - 1);	/* count does not include NUL */
}

void string_copy(string* s, const char* str) {
	string_data* s_data = string_get_data(*s);
	
	str_size str_length = strlen(str);
	//s_data->length=str_length;
		
	// make sure there is enough room for new characters and null terminator
   	s_data = realloc(s_data,( sizeof(string_data)+str_length));      //reallocating the space would not lead to bufferoverflow problems
	if(s_data == NULL) 
       printf("Couldn't allocate memory!") ;
    else { 
		s_data->length = str_length;
		s_data->alloc = str_length + 1;
	
	// copy str  
	memcpy(&s_data->buff, str, str_length);
	
	s_data->buff[str_length] = '\0'; // add new null terminator
	
	*s = s_data->buff;}
}




int string_vsprintf (char **str, const char *fmt, va_list args) {
  int size = 0;
  va_list tmpa;
    va_copy(tmpa, args);// copy
  // apply variadic arguments to sprintf with format to get size
  size = vsnprintf(NULL, 0, fmt, tmpa);
   va_end(tmpa); // toss args
  // return -1 to be compliant if size is less than 0
  if (size < 0) { return -1; }
  *str = (char *) malloc(size + 1);  // alloc with size plus 1 for `\0'
  if (NULL == *str) { return -1; }  // return -1 to be compliant if pointer is `NULL'
  size = vsprintf(*str, fmt, args);  // format string with original variadic arguments and set new size
  return size;
}

int string_sprintf(char **str, const char *fmt, ...)
 {	 
  int size = 0;
  va_list args;
  va_start(args, fmt);   // init variadic argumens
  size =string_vsprintf (str, fmt, args);  // format and get size
  va_end(args);// toss args
  return size;
}


char **string_sep(const char *buf, const char *sep){
    int i = 0, j = 0, k = 0, l = 0, stringCount = 0;
    /* If separator > buffer, return NULL */
    while (buf[i]) i++;
    while (sep[j]) j++;
    if (j > i) return NULL;
    char **strings = malloc(0);
    /* While we're not at the end of the buffer */
    while (*(buf+k)){
        /* If the characters match, check to see if it is the separator */
        if (*(buf+k) == *(sep)){
            for (l = 0; l < j; l++){
                /* If it isn't the separator, break */
                if (*(buf+k+l) != *(sep+l)) break;
                /* If it is the separator and the separator isn't the
                    beginning, add buf to buf+k bytes as a string */
                if (l == j-1 && k != 0){
                    strings = realloc(strings, (stringCount+1)*sizeof (char *));
                    strings[stringCount] = malloc(k+1);
                    memcpy(strings[stringCount++], buf, k);
                    buf += (j + k), k = -1;
                /* If it is the separator, but it's the beginning
                    of the string, skip it */
                } else if (l == j-1 && k == 0) {
                    buf += j, k = -1;
                }
            }
        }
        k++;
    }
    /* Add a string for the left over bytes if sep isn't the end */
    if (i != k && *(buf)){
        while (buf[l]) l++;
        strings = realloc(strings, (stringCount+1) * sizeof (char *));
        strings[stringCount] = malloc(l+1);
        memcpy(strings[stringCount++], buf, l);
    }
    /* Append NULL to array of strings */
    strings = realloc(strings, (stringCount+1) * sizeof (char *));
    strings[stringCount] = malloc(sizeof NULL);
    strings[stringCount] = NULL;
    return strings;
}
