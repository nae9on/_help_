#include <QCoreApplication>
#include <iostream>

class IDetectionProcess
{
public:
    virtual void print(float /*x*/){
        std::cout<<"In IDetectionProcess x\n";
    }
    virtual void print(std::string /*str*/){
        std::cout<<"In IDetectionProcess str\n";
    }
};

template<class ProcessType>
class CDetectionProcess : public IDetectionProcess
{
public:
    CDetectionProcess(ProcessType* DetectionProcess)
    : m_Storage(DetectionProcess){}
    void print(float x) override{
        std::cout<<"In CDetectionProcess x\n";
        m_Storage->print(x);
    }
    void print(std::string str) override{
        std::cout<<"In CDetectionProcess str\n";
        m_Storage->print(str);
    }
private:
    ProcessType* m_Storage;
};

class IAlgo : public IDetectionProcess{};

class CAlgo1: public IAlgo
{
public:
    using IDetectionProcess::print;
    void print(float) override{
        std::cout<<"In CAlgo1 x\n";
    }
    /*void print(std::string) override{
        std::cout<<"In CAlgo1 str\n";
    }*/
};

class CAlgo2: public IAlgo
{
public:
    using IDetectionProcess::print;
    /*void print(float) override{
        std::cout<<"In CAlgo2 x\n";
    }*/
    void print(std::string) override{
        std::cout<<"In CAlgo2 str\n";
    }
};


int main_detection()
{
    std::cout<<"Hello Qt\n\n";

    IDetectionProcess* ptr1 = new CDetectionProcess<CAlgo1>(new CAlgo1);
    ptr1->print(1.0f);
    ptr1->print("Hello");

    std::cout<<"\n\n";

    IDetectionProcess* ptr2 = new CDetectionProcess<CAlgo2>(new CAlgo2);
    ptr2->print("Hello");
    ptr2->print(1.0f);

    return 0;
}
