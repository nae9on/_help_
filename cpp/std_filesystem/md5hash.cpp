#include "experimental/filesystem"

namespace fs = std::experimental::filesystem;

void GetDirMD5Hash(std::string DirPath, std::string& MD5Hash)
{
    if(!fs::exists(DirPath))
    {
        std::cout << "Info: directory does not exist : " << DirPath << std::endl;
        std::terminate();
    }

    std::vector<fs::path> FilePaths;
    std::copy_if(fs::directory_iterator(DirPath), fs::directory_iterator(), std::back_inserter(FilePaths), [](fs::path p){ return fs::is_regular_file(p); });
    std::sort(FilePaths.begin(), FilePaths.end());

    std::string Data;
    for(auto& FilePath: FilePaths)
    {
        std::cout << FilePath << std::endl;
        std::ifstream InputFile(FilePath);
        std::string FileData= std::string(std::istreambuf_iterator<char>(InputFile), std::istreambuf_iterator<char>());
        Data.append(FileData);
    }

    //CMD5Encoder MD5Encoder(Data);
    //MD5Hash = MD5Encoder.GetEncodedString();
}
