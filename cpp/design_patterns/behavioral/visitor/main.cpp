/*
 * main.cpp
 *
 */

#include <iostream>
#include <memory>
#include <string>
#include <vector>

class CCircle;
class CSquare;

class IVisitor
{
public:
    // A visit can change the node but the visitor should not change
    virtual void VisitCircle(CCircle&) const = 0; // for node 1 - can access only public data of node
    virtual void VisitSquare(CSquare&) const = 0; // for node 2 - can access only public data of node
};

// Node interface
class IShape
{
public:
    virtual std::string Text(void) = 0;
    virtual void Draw(void) = 0;

    // A visitor should not change and and should neither be stored
    // A visit can change the node
    virtual void Accept(const IVisitor& Visitor) = 0;
};

// Concrete node 1
class CCircle : public IShape
{
public:
    std::string Text(void) override { return "Circle"; }
    void Draw() override { /*draw*/ }
    void Accept(const IVisitor& Visitor) override
    {
        Visitor.VisitCircle(*this);
    }
};

// Concrete node 2
class CSquare : public IShape
{
public:
    std::string Text(void) override { return "Square"; }
    void Draw() override { /*draw*/ }
    void Accept(const IVisitor& Visitor) override
    {
        Visitor.VisitSquare(*this);
    }
};

class CXMLExportVisitor : public IVisitor
{
public:
    void VisitCircle(CCircle& Circle) const override
    {
        std::cout << "<" << Circle.Text() << "/>\n";
    }
    void VisitSquare(CSquare& Square) const override
    {
        std::cout << "<" << Square.Text() << "/>\n";
    }
};

class CJSONExportVisitor : public IVisitor
{
public:
    void VisitCircle(CCircle& Circle) const override
    {
        std::cout << "\"" << Circle.Text() << "\"\n";
    }
    void VisitSquare(CSquare& Square) const override
    {
        std::cout << "\"" << Square.Text() << "\"\n";
    }
};

int main()
{
    std::unique_ptr<IShape> Circle = std::make_unique<CCircle>();
    std::unique_ptr<IShape> Square = std::make_unique<CSquare>();

    std::vector<std::unique_ptr<IShape>> Shapes;
    Shapes.push_back(std::move(Circle));
    Shapes.push_back(std::move(Square));

    std::unique_ptr<IVisitor> Visitor1 = std::make_unique<CXMLExportVisitor>();
    std::unique_ptr<IVisitor> Visitor2 = std::make_unique<CJSONExportVisitor>();

    // Client code
    // client simply makes the node hierarchy accept some visitor
    // He knows what a visitor is supposed to do but not exactly how it will visit each node type
    for(const auto& Shape : Shapes)
    {
        Shape->Accept(*Visitor1);
        Shape->Accept(*Visitor2);
    }

    return 0;
}
