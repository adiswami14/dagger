#pragma once
#include <string>
#include <sstream>

namespace utils {
    using std::string;

    inline char* makeCharPointer(const string& str) {
        char* chars = new char[str.size() + 1];

        for(int i = 0; i < str.length(); i++) {
            chars[i] = str[i];
        }
        chars[str.size()] = '\0';

        return chars;
    }

    inline string getFileName(const string& path) {
        int beginIdx = path.rfind('/');
        string filename = path.substr(beginIdx + 1);
        return filename;
    }

    inline char* getColorCode(int index, int max){
        double hue = (double (index) / double (max));
        std::ostringstream hue_str;
        hue_str.precision(4);
        hue_str << std::fixed << hue;
        return makeCharPointer(hue_str.str().append(" 1.000 1.000"));
//        return "0.000 1.000 1.000";
    }

}