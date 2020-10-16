/*
 * main.cpp
 *
 *  Created on: 28 Aug 2020
 *      Author:
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>

#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

#include <boost/filesystem.hpp>

using namespace cv;
using namespace std;
using namespace boost::filesystem;

struct Snapshot
{
    std::string Name{};
    std::size_t Start_Time_In_ms{};
};

int ReadVideoAndTakeSnapshot(const std::string& InPath, const std::string& OutPath, const Snapshot& Snap)
{
    // Video input
    VideoCapture InputVideo;
    InputVideo.open(InPath+Snap.Name);
    if (!InputVideo.isOpened())
    {
        cout<<"Video capture could not be initialized for file: "<<Snap.Name<<endl;
        return -1;
    }

    Mat InputFrame;

    //InputVideo.set(CAP_PROP_POS_FRAMES, 1);  // go to the 1st frame in the video
    //InputVideo.set(CAP_PROP_POS_MSEC, 1000); // go to the 1st second in the video

    std::string PreDotFilename = OutPath+Snap.Name.substr(0,Snap.Name.find("."));
    std::string Extension = ".jpg";

    InputVideo.set(CAP_PROP_POS_MSEC, Snap.Start_Time_In_ms+0);
    InputVideo >> InputFrame;
    imwrite(PreDotFilename+"_After0Sec"+Extension, InputFrame);
    InputVideo.set(CAP_PROP_POS_MSEC, Snap.Start_Time_In_ms+5000);
    InputVideo >> InputFrame;
    imwrite(PreDotFilename+"_After5Sec"+Extension, InputFrame);
    InputVideo.set(CAP_PROP_POS_MSEC, Snap.Start_Time_In_ms+10000);
    InputVideo >> InputFrame;
    imwrite(PreDotFilename+"_After10Sec"+Extension, InputFrame);
    InputVideo.set(CAP_PROP_POS_MSEC, Snap.Start_Time_In_ms+15000);
    InputVideo >> InputFrame;
    imwrite(PreDotFilename+"_After15Sec"+Extension, InputFrame);

    return 0;
}

int main()
{
    std::size_t Time_In_Sec1 = 10;

    std::string InPath{"/home/akadar/Desktop/input/"};
    std::string OutPath{"/home/akadar/Desktop/output/"};

    boost::filesystem::create_directory(OutPath.c_str()); // does nothing if dir exists

    std::cout<<"Directory path and filename: ";
    std::size_t TotalFiles{0};
    std::size_t TotalFilesReadWithNoErrors{0};
    for(directory_iterator itr{InPath}; itr!=directory_iterator(); ++itr)
    {
        std::cout<<"File "<<itr->path().string()<<" "<<itr->path().filename().string()<<std::endl;
        auto err = ReadVideoAndTakeSnapshot(InPath, OutPath, Snapshot{itr->path().filename().string(), Time_In_Sec1*1000});
        if(err==0)
        {
            ++TotalFilesReadWithNoErrors;
        }
        ++TotalFiles;
    }

    std::cout<<"TotalFiles = "<<TotalFiles<<std::endl;
    std::cout<<"TotalFilesReadWithNoErrors = "<<TotalFilesReadWithNoErrors<<std::endl;

    return 0;
}
