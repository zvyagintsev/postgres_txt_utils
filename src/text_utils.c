#include <postgres.h>
#include <string.h>
#include <fmgr.h>
#include "utils/builtins.h"

#ifdef PG_MODULE_MAGIC
PG_MODULE_MAGIC;
#endif

PG_FUNCTION_INFO_V1(common_prefix);
Datum common_prefix(PG_FUNCTION_ARGS)
{
    char *str1, *str2, *common_str;
    text *text1 = PG_GETARG_TEXT_PP(0);
    text *text2 = PG_GETARG_TEXT_PP(1);
    int32 len1  = VARSIZE_ANY_EXHDR(text1);
    int32 len2  = VARSIZE_ANY_EXHDR(text2);
    int32 common_len = 0;
    int32 min_len = len1 > len2 ? len2 : len1;
    if(min_len == 0)
        PG_RETURN_TEXT_P(CStringGetTextDatum(""));

    str1 = VARDATA(text1);
    str2 = VARDATA(text2);

    for(int i = 0; i < min_len; i++) {
        if(str1[i] == str2[i])
            common_len++;
        else break;
    }

    if(common_len == 0)
        PG_RETURN_TEXT_P(CStringGetTextDatum(""));

    common_str = (char *) palloc((common_len + 1) * sizeof(char));
    common_str[common_len] = '\0';
    strncpy(common_str, str1, common_len);
    PG_RETURN_TEXT_P(CStringGetTextDatum(common_str));
}

PG_FUNCTION_INFO_V1(common_end);
Datum common_end(PG_FUNCTION_ARGS)
{
    char *str1, *str2, *common_str;
    text *text1 = PG_GETARG_TEXT_PP(0);
    text *text2 = PG_GETARG_TEXT_PP(1);
    int32 len1  = VARSIZE_ANY_EXHDR(text1);
    int32 len2  = VARSIZE_ANY_EXHDR(text2);
    int32 common_len = 0;
    int32 min_len = len1 > len2 ? len2 : len1;
    
    if(min_len == 0)
        PG_RETURN_TEXT_P(CStringGetTextDatum(""));
    
    str1 = VARDATA(text1);
    str2 = VARDATA(text2);

    for(int i = 1; i <= min_len; i++) {
        if(str1[len1 - i] == str2[len2 - i])
            common_len++;
        else break;
    }

    if(common_len == 0)
        PG_RETURN_TEXT_P(CStringGetTextDatum(""));

    common_str = (char *) palloc((common_len + 1) * sizeof(char));
    common_str[common_len] = '\0';
    strncpy(common_str, str1 + (len1 - common_len), common_len);
    PG_RETURN_TEXT_P(CStringGetTextDatum(common_str));
}

PG_FUNCTION_INFO_V1(diff_index);
Datum diff_index(PG_FUNCTION_ARGS)
{
    text *text1 = PG_GETARG_TEXT_PP(0);
    text *text2 = PG_GETARG_TEXT_PP(1);
    int32 len1  = VARSIZE_ANY_EXHDR(text1);
    int32 len2  = VARSIZE_ANY_EXHDR(text2);
    int32 min_len = len1 > len2 ? len2 : len1;
    char *str1 = VARDATA(text1);
    char *str2 = VARDATA(text2);
    int32 common_len = 0;

     if (len1 == 0 || len2 == 0)
        PG_RETURN_INT32(0);

    for(int i = 0; i < min_len; i++) {
        if(str1[i] == str2[i])
            common_len++;
        else break;
    }

    PG_RETURN_INT32(common_len);
}

PG_FUNCTION_INFO_V1(count_matches);
Datum count_matches(PG_FUNCTION_ARGS)
{
    char *str1, *str2, *match;
    int32 count = 0;
    text *arg1 = PG_GETARG_TEXT_PP(0);
    text *arg2 = PG_GETARG_TEXT_PP(1);
    int32 len1  = VARSIZE_ANY_EXHDR(arg1);
    int32 len2  = VARSIZE_ANY_EXHDR(arg2);
    if(len1 == 0 || len2 == 0 || len1 < len2)
        PG_RETURN_INT32(count);
    str1 = VARDATA(arg1);
    str2 = VARDATA(arg2);
    match = strstr(str1, str2);
    while(match != NULL)
    {
        count++;
        match = strstr(match + len2, str2);
    }
    PG_RETURN_INT32(count);
}
