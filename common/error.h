#include <stdio.h>
void error(char *fmt, ...);
void *emalloc(size_t n);
void *erealloc(void *p, size_t n);
FILE *efopen(const char *file, const char *mode);
char *estrdup(const char *s);
char *estrndup(const char *s, size_t n);
