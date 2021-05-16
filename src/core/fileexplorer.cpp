#include "core/fileexplorer.h"

void FileExplorer::ReadAllFiles(const string& folder) { // modified this method to use std::string instead of char*...change back if needed
    
    DIR* directory = opendir(folder.c_str());
    
    if (!directory) return;
    
    File file;
    while ((file_opener_=readdir(directory)) != NULL) {    // For each directory recurses down to the files
        string str = file_opener_->d_name;
        if(str[0] != '.') {
            string path = folder + "/" + file_opener_->d_name;

            // If it is a c++ extension then we want to add it to the set of files
            // (used later in order to easily access relative paths from file names)
            string extension = GetFileExt(file_opener_->d_name);

            // if we include standard C++ header (something like <iostream>) with no extension, should not be creating a node for that
            if (std::find(kFileExtensions.begin(), kFileExtensions.end(), extension) != kFileExtensions.end()) { 
                file.file_name_ = file_opener_->d_name;
                file.file_dir_ = path;
                file_system_.insert(file);
            }

            ReadAllFiles(path);
       }
    }

    closedir(directory);
    
}

string FileExplorer::GetPathToFile(const string& file) {
    // @TODO: figure out a way to split directories and avoid naming collisions for files of same name in different dirs
    
    set<File>::iterator it = file_system_.find(file);
    if (it == file_system_.end()) return "";
    return it->file_dir_;
}

string FileExplorer::GetAbsPathFromRelative(const string& relative) {
    if (relative == "") {
        return "";
    }

    std::stringstream sstream(relative);
    string word;
    vector<string> words; // each word within a single line ex: #include, file_name, etc
    
    while (std::getline(sstream, word, '/')){
        words.push_back(word);
    }
    
    string file_name = words[words.size()-1];
    
    return GetPathToFile(file_name);
}

FileExplorer::File FileExplorer::GetFirstFile() {
    return *(file_system_.begin());
}

std::set<FileExplorer::File> FileExplorer::GetFileDirectories() {
    return file_system_;
}

std::ostream& operator<<(std::ostream& os, FileExplorer& file_exp) {
    set<FileExplorer::File>::iterator it;
    for(it=file_exp.file_system_.begin(); it!=file_exp.file_system_.end(); ++it) {
        os << "DIR PATH:     " << (*it).file_dir_ << std::endl;;
        os << "NAME:     " <<  (*it).file_name_ << std::endl;
    }
    return os;
}

//src: https://www.oreilly.com/library/view/c-cookbook/0596007612/ch10s14.html
string FileExplorer::GetFileExt(const string& s) {

   size_t i = s.rfind('.', s.length());
   if (i != string::npos) {
      return(s.substr(i+1, s.length() - i));
   }

   return("");
}

void FileExplorer::clear() {
    file_system_.clear();
}