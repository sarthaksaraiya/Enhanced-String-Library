#ifndef esl_h
#define esl_h
#include <stdlib.h>
#include <stdbool.h>

typedef char* string;
typedef size_t str_size;



string string_create(const char* str);

void string_add_char(string* s, char c);

void string_cat(string* s, const char* str);

void string_insert(string* s, str_size pos, const char* str);

void string_replace(string* s, str_size pos, str_size len, const char* str);

void string_remove(string s, str_size pos, str_size len); 

void string_free(string s);

str_size string_size(string s);

str_size string_ncopy(string* dst , const char* src , str_size maxlen);

str_size string_get_alloc(string s);

str_size string_ncat(string* dst , const char* src , str_size maxlen);

void string_copy(string* s, const char* str);

int string_vsprintf (char **, const char *, va_list);

int string_sprintf (char **, const char *, ...);

char **string_sep(const char *buf, const char *sep);

#endif /* esl_h */

