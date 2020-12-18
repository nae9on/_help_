#include "base64.h"

#include <opencv2/highgui.hpp>

#include <iostream>
#include <iterator>
#include <fstream>
#include <string>

void Write2File(const std::string& String2Write, const std::string& FileName)
{
    std::ofstream ofs(FileName, std::ofstream::out | std::ofstream::ate); // use ::app for append
    if(!ofs)
    {
        throw std::invalid_argument(FileName+" file does not exist\n");
    }
    std::ostream_iterator<char> begin(ofs,"");
    std::copy(String2Write.cbegin(), String2Write.cend(), begin);
    ofs.close();
}

std::string ReadFile(const std::string& FileName)
{
    std::ifstream File(FileName.c_str());
    return std::string(std::istreambuf_iterator<char>(File), std::istreambuf_iterator<char>());
}

using namespace cv;

int main()
{
    const std::string current_dir{"/home/akadar/Desktop/_help_/opencv/base64_encoding"};

    // Read image into a Mat object
    Mat ImageObject = imread(current_dir+"/dexter.jpg");

    // Encode image as a string
    unsigned char* Data = ImageObject.data;
    std::string EncodedImageAsString = base64_encode(Data, static_cast<std::size_t>(ImageObject.rows*ImageObject.cols*ImageObject.channels()));

    // Write string to a file
    Write2File(EncodedImageAsString, current_dir+"/data.txt");

    // Read string from the same file
    std::string ReadString = ReadFile(current_dir+"/data.txt");
    std::string DecodedImageAsString = base64_decode(ReadString, false);
    cv::Mat DecodedImage = cv::Mat(ImageObject.rows, ImageObject.cols, ImageObject.type(), reinterpret_cast<std::uint8_t*>(const_cast<char*>(DecodedImageAsString.data())));

    // Show the Decoded image
    cv::imshow("DecodedImage", DecodedImage);
    cv::waitKey(0);

    // Optional (jpeg compression)
    std::vector<unsigned char> Buffer;
    cv::imencode(".jpg", ImageObject, Buffer); // compress the image in jpeg format
    std::string Base64EncodedJpegImage = base64_encode(Buffer.data(), Buffer.size()); // base64 encode the compressed image and write to disk
    Write2File(Base64EncodedJpegImage, current_dir+"/image.jpg");
    // After writing to disk, open the image.jpg in notepad++ and decode using Plugins->MIME Tools->Base64 Decode
    // Now the jpeg image is ready for visualization

    return 0;
}
