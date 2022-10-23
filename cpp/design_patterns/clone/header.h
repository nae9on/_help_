#pragma once

#include <iostream>

// ---------------------------------------------------------------------------
class IExtWTObject
{
public:
    virtual ~IExtWTObject() = default;
    virtual IExtWTObject* clone() const = 0;
    virtual void print() const = 0;

    virtual int GetX() const = 0;
    virtual int GetY() const = 0;
};

// ---------------------------------------------------------------------------
class IWTObject : virtual public IExtWTObject
{
public:
    virtual IWTObject* original_clone() const = 0;

    virtual int GetG() const = 0;
    virtual void SetX(int x_) = 0;
    virtual void SetY(int y_) = 0;
    virtual void SetG(int g_) = 0;
};

// ---------------------------------------------------------------------------
class CExtWTObject : virtual public IExtWTObject
{
public:
    CExtWTObject* clone() const override
    {
        //std::cout<<"New ext CWTObject\n";
        // slicing!
        return new CExtWTObject(*this);
    };

    int GetX() const override { return x; }
    int GetY() const override { return y; }

    void print() const override
    {
        std::cout<<"Print CExtWTObject : ";
        std::cout << GetX() << " " << GetY() << std::endl;
    }

protected:
    int x{};
    int y{};
};
