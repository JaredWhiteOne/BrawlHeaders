#pragma once

#include "__mem.h"
#include "extras.h"
#include "stddef.h"
#include "strtoul.h"
#include "types.h"

class String {
    const char* m_string;

public:
    int strcmp(const String str2);
    static String strncpy(String destination, const char* source, size_t num);

    inline String(const char* ss)
    {
        m_string = ss;
    };

    // bool operator==(const String str2);

    inline String operator[](const u32 index)
    {
        String out = " ";
        return strncpy(out, &m_string[index], 1);
    };

    inline int length()
    {
        return strlen(m_string);
    }
    inline int stoi()
    {
        return atoi(m_string);
    };

    template <int I>
    inline static String to_string(int ii)
    {
        char ss[I];
        itoa(ii, ss, 10);
        String scoreStr(ss);
        return scoreStr;
    };
};

int strcmp(const char* str1, const char* str2);
int strncmp(const char* str1, const char* str2, size_t num);
char* strcpy(char* destination, const char* source);
char* strncpy(char* destination, const char* source, size_t num);
char* strcat(char* output, char* append);
char* strstr(char* haystack, char* needle);