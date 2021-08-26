// Example program
#include <regex>
#include <string>
#include <iostream>

int main()
{
    std::string RawString= R"(<xs:schema xmlns:xs="http://www.w3.org/2001/XMLSchema">
                                  <xs:element name="Message" type="MessageType"/>
                                  <xs:complexType name="MessageType">
                                      <xs:all>
                                          <xs:element name="Body" type="BodyType"/>
                                      </xs:all>
                                      <xs:attribute name="Type" type="xs:string" fixed="GetBackgroundImage"/>
                                  </xs:complexType>
                              </xs:schema>)";


    std::regex Pattern{">\\s*<"}; // Replace zero or more whitespace characters between ><
    std::string ReplacementText {"><"};
    std::string Constraints;
    std::regex_replace(std::back_inserter(Constraints), RawString.begin(), RawString.end(), Pattern, ReplacementText);
    std::string Expected = R"(<xs:schema xmlns:xs="http://www.w3.org/2001/XMLSchema"><xs:element name="Message" type="MessageType"/><xs:complexType name="MessageType"><xs:all><xs:element name="Body" type="BodyType"/></xs:all><xs:attribute name="Type" type="xs:string" fixed="GetBackgroundImage"/></xs:complexType></xs:schema>)";
    if(Expected==Constraints)
    {
        std::cout << "Success";
    }    
}
