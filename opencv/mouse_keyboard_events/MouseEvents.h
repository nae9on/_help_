#pragma once

#include <opencv2/highgui.hpp>
#include "opencv2/imgproc.hpp"

#include <iostream>
#include <vector>

namespace MouseEvents
{

std::ostream& operator<<(std::ostream& OS, const cv::Point& P);

bool operator==(const cv::Point& P1, const cv::Point& P2);

bool operator!=(const cv::Point& P1, const cv::Point& P2);

void MyFilledCircle(cv::Mat Img, const cv::Point& Center);

void MyLine(cv::Mat Img, const cv::Point& Start, const cv::Point& End);

void DrawText(cv::Mat Img, const cv::Point& P);

class CMouseEvents
{
public:
    CMouseEvents(const std::string& WinName)
        : m_WinName{WinName}
    {
        cv::namedWindow(m_WinName, cv::WINDOW_AUTOSIZE);
        cv::setMouseCallback(m_WinName, OnMouse);
    }

    // Show the current frame
    void Show(cv::Mat& Frame)
    {
        ++m_FrameNum;
        m_CurrentFramePtr = &Frame;
        AddLines();
        Draw();
        cv::imshow(m_WinName, Frame);
        cv::waitKey(m_Delay);
    }

    // Add lines to the vector of lines
    void AddLines();

    // Draw lines on the current frame
    void Draw();

private:
    // Static members used in the Callback function for mouse events
    static void OnMouse(int Event, int X, int Y, int Flag, void* Param);
    static cv::Point m_P1, m_P2;
    static bool m_LeftClicked;
    static bool m_RightClicked;
    static cv::MouseEventFlags m_Flag;

    bool m_LastLeftClicked{false};
    bool m_LastRightClicked{false};

    const std::string m_WinName{};
    cv::Mat* m_CurrentFramePtr;
    int m_FrameNum{-1}; // Frame counter
    int m_Delay{33}; // Corresponds to 30 FPS
    std::vector<std::pair<cv::Point, cv::Point>> m_Lines;
};

}
