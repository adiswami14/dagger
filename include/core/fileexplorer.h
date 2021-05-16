#pragma once

#include "core/textparser.h"
#include <dirent.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <set>

using std::string;
using std::set;

// Used to read all the files and create a way 
// to determine the absolute path of a file from a given filename.
// This is needed in order to properly parse the text of any file within a repository.
class FileExplorer{
    public:
        FileExplorer() = default;

        void ReadAllFiles(const string& folder);

        struct File {
            
            // Constructor created so that just a file name can be passed in (creates a dummy File when you call set::find)
            File(const string& name = "", const string& dir = "") : file_name_(name), file_dir_(dir){} 
            
            string file_name_;  // Name of the file
            string file_dir_; // Directory or longer path to file (not a completely absolute path but enough to allow the TextParser to find it)
            
            bool operator<(const File& rhs) const
            {
                return file_name_ < rhs.file_name_;
            }

            bool operator==(const File& rhs) const
            {
                return file_name_ == rhs.file_name_;
            }
        };

        std::set<File> GetFileDirectories();

        friend std::ostream& operator<<(std::ostream& os, FileExplorer& file_exp);

        // Given a file name, returns a relative path to the file
        string GetPathToFile(const string& file);
        
        string GetAbsPathFromRelative(const string& relative);

        File GetFirstFile();

        void clear();
        
        // Given a string file name, it returns the extension (Ex: game_engine.cc would return cc)
        string GetFileExt(const string& s);

    private:

        const std::vector<string> kFileExtensions = {"cc", "cpp", "h", "hpp"}; // Used to check if it is a c++ file

        

        struct dirent *file_opener_; 
        set<File> file_system_; // set of all the Files for easy lookup when a path is needed to be sent into the text parser
};
                                