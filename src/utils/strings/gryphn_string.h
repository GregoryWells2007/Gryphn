#pragma once
#include <stdlib.h>
#include <string.h>
#include "../gryphn_bool.h"

static char* add_string_to_string(char* str1, char* str2) {
    char* buffer = (char*)malloc(sizeof(char) * (strlen(str1) + strlen(str2) + 1));
    strcpy(buffer, str1);
    strcat(buffer, str2);
    buffer[strlen(str1) + strlen(str2)] = '\0';
    return buffer;
}
// add char to char buffer
// better name
static char* add_char_to_string(char* str1, char str2) {
    char* buffer = (char*)malloc(sizeof(char) * (strlen(str1) + 2));
    strcpy(buffer, str1);
    buffer[strlen(str1)] = str2;
    buffer[strlen(str1) + 1] = '\0';
    return buffer;
}


typedef char gnChar;

typedef struct gnString {
    gnChar* value;
#ifdef GN_UTILS_CPP
    gnString(const gnChar* input) {
        this->value = new gnChar[strlen(input) + 1]; // so like my dumbass forgot to put this earlier and some shit was broken but now it fixed
                                                     // I was wondering why one specific string crashed my program, it was my fault
        strcpy(this->value, input);
        this->value[strlen(input)] = '\0';
    }
    gnString(gnChar* input) {
        this->value = new gnChar[strlen(input) + 1];
        strcpy(this->value, input);
        this->value[strlen(input)] = '\0';
    }
    gnString(gnChar input) {
        this->value = new char[2];
        this->value[0] = input;
        this->value[1] = '\0';
    }
    gnString() {
        this->value = new char[1];
        this->value[0] = '\0';
    }

    operator const char*() const { return value; }

    char operator[](int index) { return value [index]; }
    const char operator[](int index) const { return value [index]; }
    void operator +=(gnChar val) { value = add_char_to_string(value, val); }
    void operator +=(gnChar* val) { value = add_string_to_string(value, val); }
    void operator +=(const gnChar* val) { value = add_string_to_string(value, const_cast<char*>(val)); }
    void operator +=(const gnString& string) { value = add_string_to_string(value, string.value); }

    gnString operator +(gnChar val) { return gnString(add_char_to_string(value, val)); }
    gnString operator +(gnChar* val){ return gnString(add_string_to_string(value, val)); }
    gnString operator +(const gnChar* val) { return gnString(add_string_to_string(value, const_cast<char*>(val))); }
    gnString operator +(const gnString& val) { return gnString(add_string_to_string(value, val.value)); }

    gnBool operator ==(char* val) { return (strcmp(value, val) == 0); }
    gnBool operator ==(const char* val) { return (strcmp(value, const_cast<char*>(val)) == 0); }
    gnBool operator ==(const gnString& val) { return (strcmp(value, val.value) == 0); }

    void operator =(char val) {
        this->value = new char[2];
        this->value[0] = val;
        this->value[1] = '\0';
    }
    void operator =(char* val) { this->value = val; }
    void operator =(const char* val) { this->value = const_cast<char*>(val); }
    void operator =(const gnString& val) { this->value = val.value; }
#endif
} gnString;

static gnString gnCreateStringFromConstCharPtr(const gnChar* input) {
    gnString string;
    string.value = (char*)malloc(sizeof(char) * (strlen(input) + 1));
    strcpy(string.value, input);
    string.value[strlen(input)] = '\0';
    return string;
}
static gnString gnCreateStringFromCharPtr(gnChar* input) {
    gnString sting;
    sting.value = (char*)malloc(sizeof(char) * (strlen(input) + 1));
    strcpy(sting.value, input);
    sting.value[strlen(input)] = '\0';
    return sting;
}
static gnString gnCreateStringFromChar(gnChar input) {
    gnString string;
    string.value = (char*)malloc(sizeof(char) * 2);
    string.value[0] = input;
    string.value[1] = '\0';
    return string;
}
static gnString gnCreateEmptyString() {
    gnString string;
    string.value = (char*)malloc(sizeof(char));
    string.value[0] = '\0';
    return string;
}

#define gnCreateString(input) _Generic((input), \
    const gnChar*: gnCreateStringFromConstCharPtr, \
    gnChar*: gnCreateStringFromCharPtr, \
    gnChar: gnCreateStringFromChar \
)(input)

static const char* gnToCString(const gnString string) { return string.value; }
static int gnStringLength(const gnString string) { return strlen(string.value); }
static int gnStringFindChar(const gnString string, const gnChar letter) {
    for (int i = 0; i < strlen(string.value); i++)
        if (string.value[i] == letter)
            return i;
    return -1;
}
static int gnStringFindString(const gnString string, const gnString value) {
    char first_char = value.value[0];
    for (int i = 0; i < strlen(string.value); i++)
        if (string.value[i] == first_char) {
            gnBool same = gnTrue;
            for (int c = 1; c < strlen(value.value); c++)
                if (string.value[i + c] != value.value[c]) {
                    same = gnFalse;
                    break;
                }

            if (same)
                return i;
        }
    return -1;
}
static gnString gnSubstring(const gnString string, int index1, int index2) {
    if (index2 == -1) index2 = gnStringLength(string);
    char* out_value = (char*)malloc(sizeof(char) * ((index2 - index1) + 1));
    for (int i = 0; i < (index2 - index1); i++)
        out_value[i] = string.value[i + index1];
    out_value[(index2 - index1)] = '\0';
    return gnCreateString(out_value); // zero error checking on this function should really add that in later but like I dont have a logging library that I want to use
                                      // my code never breaks either so I dont need error checks, il just not make errors cuz im not tim
}
static int gnLetterCount(const gnString string, const gnChar letter) {
    int count = 0;
    for (int i = 0; i < gnStringLength(string); i++) if (string.value[i] == letter) count++;
    return count;
}

#define gnStringFind(string, value) _Generic((value), \
    const gnChar: gnStringFindChar, \
    const gnString: gnStringFindValue \
)(string, value)

static void gnAddCharToString(gnString* string, gnChar val) {
    string->value = add_char_to_string(string->value, val);
}
static void gnAddCharPtrToString(gnString* string, gnChar* val) {
    string->value = add_string_to_string(string->value, val);
}
static void gnAddConstCharPtrToString(gnString* string, const gnChar* val) {
    string->value = add_string_to_string(string->value, (gnChar*)val);
}
static void gnAddContGnStringToString(gnString* string, gnString val) {
    string->value = add_string_to_string(string->value, val.value);
}

#define gnAddToString(string, value) _Generic((value), \
    gnChar: gnAddCharToString, \
    int: gnAddCharToString, \
    gnChar*: gnAddCharPtrToString, \
    const gnChar*: gnAddConstCharPtrToString, \
    gnString: gnAddContGnStringToString \
)(string, value)

static gnString gnCombineStringsChar(const gnString string, gnChar val) {
     return gnCreateString(add_char_to_string(string.value, val));
}
static gnString gnCombineStringsCharPtr(const gnString string, gnChar* val) {
    return gnCreateString(add_string_to_string(string.value, val));
}
static gnString gnCombineStringsConstCharPtr(const gnString string, const gnChar* val) {
    return gnCreateString(add_string_to_string(string.value, (gnChar*)val));
}
static gnString gnCombineStringsString(const gnString string, const gnString val) {
    return gnCreateString(add_string_to_string(string.value, val.value));
}

#define gnCombineStrings(string, value) _Generic((value), \
    gnChar: gnCombineStringsChar, \
    int: gnCombineStringsChar, \
    gnChar*: gnCombineStringsCharPtr, \
    const gnChar*: gnCombineStringsConstCharPtr, \
    gnString: gnCombineStringsString \
)(string, value)

static gnBool gnStringEqualsCharPtr(const gnString string, gnChar* val) { return (strcmp(string.value, val) == 0); }
static gnBool gnStringEqualsConstCharPtr(const gnString string,const gnChar* val) { return (strcmp(string.value, (gnChar*)val) == 0); }
static gnBool gnStringEqualsString(const gnString string, const gnString val) { return (strcmp(string.value, val.value) == 0); }

#define gnStringEquals(string, value) _Generic((value), \
    gnChar*: gnStringEqualsCharPtr, \
    const gnChar*: gnStringEqualsConstCharPtr, \
    gnString: gnStringEqualsString \
)(string, value)

static gnChar gnGetCharAt(const gnString string, int index) { return string.value[0]; }
static void gnSetCharAt(gnString* string, int index, gnChar letter) { string->value[0] = letter; }

static void gnSetStringToChar(gnString* string, gnChar input) {
    string->value = (gnChar*)malloc(sizeof(gnChar) * 2);
    string->value[0] = input;
    string->value[1] = '\0';
}
static void gnSetStringToCharPtr(gnString* string, gnChar* input) {
    string->value = (gnChar*)malloc(sizeof(gnChar) * (strlen(input) + 1));
    strcpy(string->value, input);
    string->value[strlen(input)] = '\0';
}
static void gnSetStringToConstCharPtr(gnString* string, const gnChar* input) {
    string->value = (gnChar*)malloc(sizeof(gnChar) * (strlen(input) + 1));
    strcpy(string->value, input);
    string->value[strlen(input)] = '\0';
}
static void gnSetStringToString(gnString* string, const gnString input) {
    string->value = (gnChar*)malloc(sizeof(gnChar) * (strlen(input.value) + 1));
    strcpy(string->value, input.value);
    string->value[strlen(input.value)] = '\0';
}

#define gnSetString(string, value) _Generic((value), \
    gnChar: gnSetStringToChar, \
    int: gnSetStringToChar, \
    gnChar*: gnSetStringToCharPtr, \
    const gnChar*: gnSetStringToConstCharPtr, \
    gnString: gnSetStringToString \
)(string, value)
