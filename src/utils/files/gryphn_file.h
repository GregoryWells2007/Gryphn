#pragma once
#include <utils/gryphn_access_level.h>

// TODO: this file API is shit
// have you ever wanted to write a file, well too bad cuz that shits a lot of work and im not doing allllll that
// also like im pretty sure something is fucked up in the reading of binary files, what, I dont know but something is
// other than that im pretty happy with it cuz like I still have zero fuckcking clue how it works
// the binary part that is

#include "../strings/gryphn_string.h"
#include "../lists/gryphn_list.h"

enum class gnFileType {
    Text, Binary
};

struct gnFile {
ACCESS_LEVEL:
    gnList<gnString> lines = gnCreateList<gnString>(); // if file type is string
    gnList<gnChar> bytes = gnCreateList<gnChar>(); // if file type is binary
                                                    // ofc dumbass they should know what file type there loading
                                                    // wellllllll actually this is horrible cuz im storing the like 4 bytes it take for an empty list in every loaded file
                                                    // regardless of if there is actually any data in the list
                                                    // buttttt as code astetic once said "premature optimization is like totally the root of all evil bro *procedes to hit bong*"
                                                    // i think i remember that right, i need to fix this but templates are hard and im not

    gnString path = gnCreateString();
    gnFileType type = gnFileType::Text; // who loads binary files anyway *silence*, i do I guess thats why I wrote this
public:
    gnFile() {}
};

gnFile gnLoadFile(const gnString& path, gnFileType type = gnFileType::Text);
// gnFile gnCreateFile(const gnString& path);
// gnFile gnCreateFile();
// gnFile gnWriteFile(const gnFile& file);
// which fucking loser thought they were writing a file writing API
// ...... that was me, im lazy, its 10:30, 2.5 hours after I go to sleep, imma go to sleep.

gnString gnGetFilePath(const gnFile& file);
gnString gnGetFileData(const gnFile& file); // i should rename this
gnList<gnChar> gnGetFileBytes(const gnFile& file);  // fuck object oriented code
                                                    // and fuck error detection the user can get the bytes of a text file if they want to cuz its slow to do error checking, its also smart but im slow
                                                    // so me and this project are one in the same
