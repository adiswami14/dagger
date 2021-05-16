#include <core/textparser.h>

TextParser::TextParser() {
    //include_paths_ = vector<string>();
}

vector<string> TextParser::ParseText(const std::string& fp) {
    std::ifstream file_stream;
    file_stream.open(fp);
    while (file_stream.good()) {
        file_stream >> *this;
    }

    return include_paths_;
}

std::istream& operator >> (std::istream& in, TextParser& parser) {
    parser.include_paths_.clear();
    string line;
    while(getline(in, line)) { // singular line from text file
        if (line != "") {
            std::stringstream sstream(line);
            string word;
            vector<string> words; // each word within a single line ex: #include, file_name, etc
            
            while (std::getline(sstream, word, ' ')){
                words.push_back(word);
            }
            
            // Accounts for extra spaces in between #include and the filename
            std::remove(words.begin(), words.end(), "");
            
            if (words[0] == "#include") {
                // Removes "", <, and > from the file path. Ex: "file_name" -> file_name
                string s = words[1];
                string chars = "\"<>";
                s.erase(remove_if(s.begin(), s.end(), 
                                            [&chars](const char &c) {
                                                return chars.find(c) != std::string::npos;
                                            }), s.end());
                parser.include_paths_.push_back(s); // Push_back path associated with #include
            }
        }
    }
    return in;
}

