#include "tinyxml.h"

#include <iostream>
#include <vector>

int main()
{    
    TiXmlDocument Doc{};
    Doc.LoadFile("/home/akadar/Desktop/_help_/xml_parser/config.xml", TiXmlEncoding::TIXML_ENCODING_UTF8);
    std::cout<<"TiXmlDocument filename = "<<Doc.Value()<<std::endl;
    std::cout<<"TiXmlDocument file content = "<<std::endl;
    Doc.Print();

    float ConfidenceThreshold{};
    std::string ModelName{};
    bool UseTimings{false};
    bool IsCaffeModel{false};
    int Channel{};
    std::vector<std::vector<int>> data;

    TiXmlHandle DocHandle{&Doc};
    TiXmlHandle Handle = DocHandle.FirstChildElement("Configuration").FirstChildElement("DNN").FirstChildElement("DNN");

    if(const TiXmlElement* Element = Handle.ToElement())
    {
        Element->QueryFloatAttribute("ConfidenceThreshold", &ConfidenceThreshold);
        Element->QueryBoolAttribute("UseTimings", &UseTimings);
        Element->QueryBoolAttribute("IsCaffeModel", &IsCaffeModel);
        if (Element->Attribute("ModelName"))
        {
            ModelName = std::string(Element->Attribute("ModelName"));
        }

        if (const TiXmlElement* DisplayElement = Handle.FirstChildElement("Display").ToElement())
        {
            if(DisplayElement->QueryIntAttribute("Channel", &Channel) == TIXML_SUCCESS)
            {
                std::cout<<"Channel read successfully"<<std::endl;
            }
        }

        for (const TiXmlElement* ROIElement = Handle.FirstChildElement("ROI").ToElement(); ROIElement; ROIElement = ROIElement->NextSiblingElement("ROI"))
        {
            int X = 0;
            ROIElement->QueryIntAttribute("X", &X);
            int Y = 0;
            ROIElement->QueryIntAttribute("Y", &Y);
            int Width = 0;
            ROIElement->QueryIntAttribute("Width", &Width);
            int Height = 0;
            ROIElement->QueryIntAttribute("Height", &Height);

            data.push_back(std::vector<int>{Height, Width, X, Y});

        }
    }

    std::cout<<ConfidenceThreshold<<" "<<ModelName<<" "<<UseTimings<<" "<<IsCaffeModel<<" "<<Channel<<std::endl;
    for(const auto& out : data)
    {
        for(const auto& in : out)
        {
            std::cout<<in<<" ";
        }
        std::cout<<std::endl;
    }

    return 0;
}
