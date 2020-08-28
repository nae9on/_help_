/*
 * csv2vec.cpp
 *
 *  Created on: 01 Nov 2019
 *      Author: ahkad
 *
 * Note: I have used istreambuf_iterator which never skips any characters (including whitespaces
 * such as '\n'). It grabs whatever 's next in the stream buffer unlike istream_iterator which
 * skips whitespaces. Also istream_iterator is useful when performing formatted input and is slower
 * than the istreambuf_iterator. Reference: Item 29, Effective STL, Scott Meyers.
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>

void txt2VecOfString(const std::string& filename,
                     std::vector<std::vector<std::string>>& result,
                     char delimiter=',') {

    std::ifstream in(filename);

    std::istreambuf_iterator<char> first(in);
    std::istreambuf_iterator<char> last;

    std::string temp;
    unsigned i{0};
    while(1) {
        do{
            if(*first == '\n') break;
            temp.push_back(*first);
            ++first;
        }while(*first != delimiter && first != last);
        result[i].push_back(temp);
        if(*first == '\n') {
            ++i;
            result.resize(i+1);
        }
        temp.clear();
        if(first == last) break;
        ++first;
    }
}

void txt2VecOfInts(const std::string& filename,
                     std::vector<std::vector<int>>& result,
                     char delimiter=',') {

    std::ifstream in(filename);

    std::istreambuf_iterator<char> first(in);
    std::istreambuf_iterator<char> last;

    std::string temp;
    unsigned i{0};
    while(1) {
        do{
            if(*first == '\n') break;
            temp.push_back(*first);
            ++first;
        }while(*first != delimiter && first != last);
        int value = std::stoi(temp, nullptr, 0);
        result[i].push_back(value);
        if(*first == '\n') {
            ++i;
            result.resize(i+1);
        }
        temp.clear();
        if(first == last) break;
        ++first;
    }
}

int main(void) {

    std::cout<<"Begin of main\n";

    std::vector<std::vector<std::string>> StringVec(1);
    txt2VecOfString("/home/akadar/Desktop/_help_/cpp/IO/data.txt", StringVec, ',');
    for(const auto& vecouter : StringVec) {
        for(const auto& elem : vecouter){
            std::cout<<elem<<" ";
        }
        std::cout<<"\n";
    }

    std::vector<std::vector<int>> NumVec(1);
    txt2VecOfInts("/home/akadar/Desktop/_help_/cpp/IO/numbers.txt", NumVec, ' ');
    for(const auto& vecouter : NumVec) {
        for(const auto& elem : vecouter){
            std::cout<<elem<<" ";
        }
        std::cout<<"\n";
    }

    std::cout<<"End of main\n";

   return 0;
}
