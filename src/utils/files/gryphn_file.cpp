#include "gryphn_file.h"
#include "fstream"
#include "iostream"

gnFile gnLoadFile(const gnString& path, gnFileType type) {
    gnFile new_file = gnFile();

    if (type == gnFileType::Text) {
        std::ifstream file(gnToCString(path));
        if (!file.is_open()) throw std::runtime_error("failed to open text file!"); //  thats right I wont use std::vector but il use std::runtime_error my priorities are straight
                                                                                    // not as straight as me around ethan mooney, il see myself out now. (PS i actually did go to bed these will stop now)

        std::string line;
        while(std::getline(file, line)) {
            gnListAdd(new_file.lines, gnCreateString(line.c_str()));
        }
    } else if (type == gnFileType::Binary) {
        std::ifstream file(gnToCString(path), std::ios::ate | std::ios::binary);

        if (!file.is_open()) throw std::runtime_error("failed to open file!");

        size_t file_size = (size_t)file.tellg();
        new_file.bytes = gnCreateList<gnChar>(file_size);

        file.seekg(0);
        file.read(gnListData(new_file.bytes), file_size);

        file.close(); // straight from vulkan-tutorial.com, not as strai, imma stop myself now
    }
    new_file.path = path;

    return new_file;
}

gnString gnGetFileData(const gnFile& file) {
    gnString file_data;
    for (int i = 0; i < gnListLength(file.lines); i++) {
        file_data += gnListGet(file.lines, i) + '\n';
    }
    return file_data;
} //  why I dont just return the file as a list of lines, cuz thats the easy way this way revealed so many errors in my string class,
  // dont you love it when you dont actually copy a string and then the data gets lost and you dont know why because your an idiot
  // thats never happened to me...... yea so im an idiot shouve actually copied the bytes over not just haphazardly asigned them to a string.

gnString gnGetFilePath(const gnFile& file) {
    return file.path;
}

gnList<gnChar> gnGetFileBytes(const gnFile& file) { return file.bytes; }
