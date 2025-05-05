#pragma once
#include <utils/gryphn_access_level.h>
#include <utils/gryphn_bool.h>
#include <cstring>

typedef char gnChar; // OpenGL does it so I do it

struct gnString;
static const char* gnToCString(const gnString& string);

// apis for char buffers togethers
// wack ass name idk what it means but im keepin it
// this just adds to char buffers into one big buffer
static char* add_string(char* str1, char* str2) {
    char* buffer = new char[strlen(str1) + strlen(str2) + 1];
    strcpy(buffer, str1);
    strcat(buffer, str2);
    buffer[strlen(str1) + strlen(str2)] = '\0';
    return buffer;
}
// add char to char buffer
// better name
static char* add_string(char* str1, char str2) {
    char* buffer = new char[strlen(str1) + 2];
    strcpy(buffer, str1);
    buffer[strlen(str1)] = str2;
    buffer[strlen(str1) + 1] = '\0';
    return buffer;
}

struct gnString {
ACCESS_LEVEL:
    gnChar* value = new gnChar[1]{ '\0' };
public:
    gnString(const gnChar* input) {
        this->value = new gnChar[strlen(input) + 1]; // so like my dumbass forgot to put this earlier and some shit was broken but now it fixed
                                                     // I was wondering why one specific string crashed my program, it was my fault

        char* converted_input = const_cast<char*>(input); // yea un const that const value, this line cost me hours cuz I cant read error codes
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

    friend int gnStringLength(const gnString& length);
    friend int gnStringFind(const gnString& string, const gnChar& letter);
    friend int gnStringFind(const gnString& string, const gnString& value);
    friend const char* gnToCString(const gnString& string); // dumb ass name but this shit gets used so much
    friend gnString gnSubstring(const gnString& string, int index1, int index2);

    friend int gnLetterCount(const gnString& string, const gnChar& letter);
    friend gnChar gnGetCharAt(const gnString& string, int index);
    friend void gnSetCharAt(gnString& string, int index, gnChar letter);

    friend void gnAddToString(gnString& string, char val);
    friend void gnAddToString(gnString& string, char* val);
    friend void gnAddToString(gnString& string, const char* val);
    friend void gnAddToString(gnString& string, const gnString& val);

    friend gnString gnCombineStrings(const gnString& string, char val); // this shit is not combining a string but im lazy, fuck off
    friend gnString gnCombineStrings(const gnString& string, char* val);
    friend gnString gnCombineStrings(const gnString& string, const char* val);
    friend gnString gnCombineStrings(const gnString& string, const gnString& val);

    friend gnBool gnStringEquals(const gnString& string, char* val);
    friend gnBool gnStringEquals(const gnString& string, const char* val);
    friend gnBool gnStringEquals(const gnString& string, const gnString& val);

    friend void gnSetString(gnString& string, const gnString& input);
    friend void gnSetString(gnString& string, const gnChar* input);
    friend void gnSetString(gnString& string, gnChar* input);
    friend void gnSetString(gnString& string, gnChar input);
public:
    char operator[](int index) { return value [index]; }
    const char operator[](int index) const { return value [index]; }
    void operator +=(char val) { value = add_string(value, val); }
    void operator +=(char* val) { value = add_string(value, val); }
    void operator +=(const char* val) { value = add_string(value, const_cast<char*>(val)); }
    void operator +=(const gnString& string) { value = add_string(value, const_cast<char*>(gnToCString(string))); }

    gnString operator +(char val) { return gnString(add_string(value, val)); }
    gnString operator +(char* val){ return gnString(add_string(value, val)); }
    gnString operator +(const char* val) { return gnString(add_string(value, const_cast<char*>(val))); }
    gnString operator +(const gnString& val) { return gnString(add_string(value, const_cast<char*>(val.value))); }

    gnBool operator ==(char* val) { return (strcmp(value, val) == 0); }
    gnBool operator ==(const char* val) { return (strcmp(value, const_cast<char*>(val)) == 0); }
    gnBool operator ==(const gnString& val) { return (strcmp(value, const_cast<char*>(val.value)) == 0); }

    void operator =(char val) {
        this->value = new char[2];
        this->value[0] = val;
        this->value[1] = '\0';
    }
    void operator =(char* val) { this->value = val; }
    void operator =(const char* val) { this->value = const_cast<char*>(val); }
    void operator =(const gnString& val) { this->value = val.value; }
};

inline gnString gnCreateString(const gnChar* input) { return gnString(input); }
inline gnString gnCreateString(gnChar* input) { return gnString(input); }
inline gnString gnCreateString(gnChar input) { return gnString(input); }
inline gnString gnCreateString() { return gnString(); }

inline int gnStringLength(const gnString& string) { return strlen(string.value); }
inline const char* gnToCString(const gnString& string) { return string.value; } // this is what Bjarne Stroustrup Sausage man intented me to do with his language

inline int gnStringFind(const gnString& string, const gnChar& letter) {
    for (int i = 0; i < strlen(string.value); i++)
        if (string.value[i] == letter)
            return i;
    return -1;
}
inline int gnStringFind(const gnString& string, const gnString& value) {
    char first_char = value.value[0];
    for (int i = 0; i < strlen(string.value); i++)
        if (string.value[i] == first_char) {
            bool same = true;
            for (int c = 1; c < strlen(value.value); c++)
                if (string.value[i + c] != value.value[c]) {
                    same = false;
                    break;
                }

            if (same)
                return i;
        }
    return -1;
}

inline gnString gnSubstring(const gnString& string, int index1, int index2) {
    if (index2 == -1) index2 = gnStringLength(string);
    char* out_value = new char[(index2 - index1) + 1];
    for (int i = 0; i < (index2 - index1); i++)
        out_value[i] = string.value[i + index1];
    out_value[(index2 - index1)] = '\0';
    return gnCreateString(out_value); // zero error checking on this function should really add that in later but like I dont have a logging library that I want to use
                                      // my code never breaks either so I dont need error checks, il just not make errors cuz im not tim
}

inline int gnLetterCount(const gnString& string, const gnChar& letter) {
    int count = 0;
    for (int i = 0; i < gnStringLength(string); i++) if (string.value[i] == letter) count++;
    return count;
}

inline void gnAddToString(gnString& string, char val) { string += val; }
inline void gnAddToString(gnString& string, char* val) { string += val; }
inline void gnAddToString(gnString& string, const char* val) { string += val; }
inline void gnAddToString(gnString& string, const gnString& val) { string += val; }

inline gnString gnCombineStrings(const gnString& string, char val) { return gnCreateString(add_string(string.value, val)); }
inline gnString gnCombineStrings(const gnString& string, char* val) { return gnCreateString(add_string(string.value, val)); }
inline gnString gnCombineStrings(const gnString& string, const char* val) { return gnCreateString(add_string(string.value, const_cast<char*>(val))); }
inline gnString gnCombineStrings(const gnString& string, const gnString& val) { return gnCreateString(add_string(string.value, const_cast<char*>(val.value))); }

inline gnBool gnStringEquals(const gnString& string, char* val) { return (strcmp(string.value, val) == 0); }
inline gnBool gnStringEquals(const gnString& string,const char* val) { return (strcmp(string.value, const_cast<char*>(val)) == 0); }
inline gnBool gnStringEquals(const gnString& string, const gnString& val) { return (strcmp(string.value, const_cast<char*>(val.value)) == 0); }

inline gnChar gnGetCharAt(const gnString& string, int index) { return string.value[0]; }
inline void gnSetCharAt(gnString& string, int index, gnChar letter) { string.value[0] = letter; }

inline void gnSetString(gnString& string, const gnString& input) { string.value = input.value; }
inline void gnSetString(gnString& string, const gnChar* input) { string.value = const_cast<char*>(input); }
inline void gnSetString(gnString& string, gnChar* input) { string.value = input; }
inline void gnSetString(gnString& string, gnChar input) { string = input; }
