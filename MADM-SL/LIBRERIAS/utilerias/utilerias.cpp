#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include "utilerias.hpp"

#ifdef _WIN32
char *strtok_r(char *str, const char *delim, char **save)
{
    char *res, *last;

    if( !save )
        return strtok(str, delim);
    if( !str && !(str = *save) )
        return NULL;
    last = str + strlen(str);
    if( (*save = res = strtok(str, delim)) )
    {
        *save += strlen(res);
        if( *save < last )
            (*save)++;
        else
            *save = NULL;
    }
    return res;
}
#endif

void findAndReplaceAll( std::string& data,const std::string& match, const std::string& replace)
{
   size_t pos = data.find(match);
   while( pos != std::string::npos)
    {
        data.replace(pos, match.size(), replace);
        pos = data.find(match, pos+replace.size());
    }
}

bool isNumber( std::string token )
{
    return std::regex_match( token, std::regex( ( "((\\+|-)?[[:digit:]]+)(\\.(([[:digit:]]+)?))?" ) ) );
}


