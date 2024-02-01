#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <regex>

#ifdef _WIN32
char *strtok_r(char *str, const char *delim, char **save);
#endif

void findAndReplaceAll( std::string& data,const std::string& match, const std::string& replace);

bool isNumber( std::string token );
