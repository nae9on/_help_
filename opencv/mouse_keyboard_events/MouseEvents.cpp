#include "MouseEvents.h"

#include <iostream>
#include <stdlib.h>

namespace MouseEvents
{

// Pixels within range [0 10] are considered identical
constexpr int Int_Pixel_Precision{10};

cv::Point CMouseEvents::m_P1{};
cv::Point CMouseEvents::m_P2{};
bool CMouseEvents::m_LeftClicked = false;
bool CMouseEvents::m_RightClicked = false;
cv::MouseEventFlags CMouseEvents::m_Flag = cv::MouseEventFlags::EVENT_FLAG_LBUTTON;

std::ostream& operator<<(std::ostream& OS, const cv::Point& P)
{
    return OS << P.x << " " << P.y;
}

// Compare in integer arithmetic!
bool operator==(const cv::Point& P1, const cv::Point& P2)
{
    return (abs(P1.x-P2.x)<Int_Pixel_Precision &&
            abs(P1.y-P2.y)<Int_Pixel_Precision);
}

bool operator!=(const cv::Point& P1, const cv::Point& P2)
{
    return !(P1==P2);
}

void MyFilledCircle(cv::Mat Img, const cv::Point& Center)
{
    int Radius{4};

    cv::circle(Img,
               Center,
               Radius,
               cv::Scalar(255, 255, 255),
               cv::FILLED,
               cv::LINE_8);
}

void MyLine(cv::Mat Img, const cv::Point& Start, const cv::Point& End)
{
    int Thickness = 2;
    int LineType = cv::LINE_8;

    cv::line(Img,
             Start,
             End,
             cv::Scalar(0, 255, 0),
             Thickness,
             LineType);
}

void DrawText(cv::Mat Img, const cv::Point& P)
{
    std::stringstream ss;
    ss << P;
    cv::putText(Img, ss.str().c_str(), P,
            cv::FONT_HERSHEY_SIMPLEX, 0.5 , cv::Scalar(0,0,0));
}

void CMouseEvents::AddLines()
{
    // Left click drag and drop to add lines
    if(!m_LeftClicked && m_LastLeftClicked)
    {
        // Add only those lines whose start and end points are not close enough
        if(m_P1!=m_P2)
        {
            if(m_Lines.size()>0)
            {
                // Close the loop if the end point of previous line and the start point of new line are close enough
                if(m_P1==m_Lines.back().second)
                {
                    m_Lines.emplace_back(m_Lines.back().second, m_P2);
                }
                else
                {
                    m_Lines.emplace_back(m_P1, m_P2);
                }
            }
            else
            {
                m_Lines.emplace_back(m_P1, m_P2);
            }

        }
    }
    m_LastLeftClicked = m_LeftClicked;

    // Right click to clear all lines
    if(!m_RightClicked && m_LastRightClicked)
    {
        // Close the loop if the end point of last line and the first point of first line are close enough
        if(m_Lines.size()>0)
        {
            if(m_Lines[0].first==m_Lines.back().second)
            {
                m_Lines.back().second = m_Lines[0].first;
            }
        }

        // Print all lines before clearing
        for(const auto& Line : m_Lines)
        {
            std::cout<<Line.first << " " << Line.second << std::endl;
        }
        m_Lines.clear();
    }
    m_LastRightClicked = m_RightClicked;
}

void CMouseEvents::Draw()
{
    if(m_LeftClicked)
    {
        MyFilledCircle(*m_CurrentFramePtr, m_P1);
        MyFilledCircle(*m_CurrentFramePtr, m_P2);
        MyLine(*m_CurrentFramePtr, m_P1, m_P2);
        DrawText(*m_CurrentFramePtr, m_P1);
        DrawText(*m_CurrentFramePtr, m_P2);
    }

    for(const auto& Line : m_Lines)
    {
        MyLine(*m_CurrentFramePtr, Line.first, Line.second);
        DrawText(*m_CurrentFramePtr, Line.first);
        DrawText(*m_CurrentFramePtr, Line.second);
    }
}

void CMouseEvents::DrawROI()
{
    int Radius = 100;
    int Scale = 4;
    cv::Mat& Src = *m_CurrentFramePtr;
    cv::Rect ROI1(m_P1.x-Radius, m_P1.y-Radius, 2*Radius, 2*Radius);
    cv::Rect ROI2(m_P2.x-Radius, m_P2.y-Radius, 2*Radius, 2*Radius);
    cv::Rect ROI = ((ROI1 | ROI2) & cv::Rect(0, 0, Src.cols, Src.rows));
    const cv::Mat& CroppedImage = Src(ROI);
    cv::Mat ScaledImage;
    cv::resize(CroppedImage, ScaledImage, cv::Size(CroppedImage.cols*Scale, CroppedImage.rows*Scale));
    cv::imshow(m_WinNameZoom, ScaledImage);
}

void CMouseEvents::OnMouse(int Event, int X, int Y, int Flag, void* /*Param*/)
{
    m_Flag = static_cast<cv::MouseEventFlags>(Flag);

    switch(Event){

    case  cv::EVENT_LBUTTONDOWN:
        m_LeftClicked = true;
        m_P1.x=X;
        m_P1.y=Y;
        m_P2.x=X;
        m_P2.y=Y;
        break;

    case cv::EVENT_RBUTTONDOWN:
        m_RightClicked = true;
        break;

    case  cv::EVENT_LBUTTONUP:
        m_LeftClicked = false;
        m_P2.x=X;
        m_P2.y=Y;
        break;

    case cv::EVENT_RBUTTONUP:
        m_RightClicked  = false;
        break;

    case cv::EVENT_MOUSEMOVE:
        if(m_LeftClicked)
        {
            m_P2.x=X;
            m_P2.y=Y;
        }
        break;

    default:
        break;
    }
}

}
