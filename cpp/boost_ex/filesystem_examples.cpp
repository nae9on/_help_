/*
 * filesystem_examples.cpp
 *
 *  Created on: 23 Aug 2020
 *      Author: ahkad
 */

#include <boost/filesystem.hpp>

#include <iostream>

using namespace boost::filesystem;

int main_filesystem_examples()
{
    std::string FolderPath{"C:\\Users\\ahkad\\Desktop"};
    std::cout<<"Directory path and filename: ";
    for(directory_iterator itr{FolderPath}; itr!=directory_iterator(); ++itr)
    {
        std::cout<<"File "<<itr->path().string()<<" "<<itr->path().filename().string()<<std::endl;
    }

    std::string OutputDirOpenCV{FolderPath+"\\OutputOpenCV\\"};
    boost::filesystem::create_directory(OutputDirOpenCV.c_str()); // does nothing if dir exists

    return 0;
}
