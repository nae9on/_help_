// https://stackoverflow.com/questions/20353210/what-is-the-purpose-of-stdfunction-and-how-to-use-it

#include <functional>
#include <iostream>

#include <boost/type_index.hpp>

using boost::typeindex::type_id_with_cvr;

template<typename T>
class GeneralCalculator
{
public:
    using op_type = T;
    GeneralCalculator(op_type Op)
        : m_Op{Op}
    {}

    void Apply(int Num)
    {
        std::cout << type_id_with_cvr<op_type>().pretty_name() << " " << m_Op(Num) << std::endl;
    }

private:
    op_type m_Op;
};

class Calculator
{
public:
    using op_type = std::function<int (int)>;
    Calculator(op_type Op)
        : m_Op{Op}
    {}

    void Apply(int Num)
    {
        std::cout << type_id_with_cvr<decltype(m_Op)>().pretty_name() << " " << m_Op(Num) << std::endl;
    }

private:
    op_type m_Op;
};

class CMult
{
public:
    CMult(int Factor)
        : m_Factor(Factor)
    {}
    int operator()(int Num){ return m_Factor*Num; }
private:
    int m_Factor;
};

int Mult5(int Num)
{
    return 5 * Num;
}

int main()
{
    CMult Mult2(2), Mult3(3);

    int Num7 = 7;
    auto Mult7 = [Num7](int Num)
    {
        return Num7 * Num;
    };

    float Fraction = 7.555555;
    auto MultFraction = [Fraction](int Num)
    {
        return Fraction * Num;
    };

    auto MultString = [](int Num)
    {
        return "Dummy";
    };

    // All types are the same because std::function erases type
    Calculator CalcMultTwo(Mult2), CalcMultFive(Mult5), CalcMultSeven(Mult7);

    // std::function supports storing any function-like object whose arguments can
    // be converted-from its argument list, and whose return value can be converted-to its return value.
    Calculator CalcMultFraction(MultFraction);
    // Calculator CalcMultString(MultString); //  Compilation error because above comment is not true

    CalcMultTwo.Apply(10);
    CalcMultFive.Apply(10);
    CalcMultSeven.Apply(10);
    CalcMultFraction.Apply(10); // Loss of precision

    // Template preserves the type
    GeneralCalculator CalcMultTwoAgain(Mult2);
    GeneralCalculator CalcMultFiveAgain(Mult5);
    GeneralCalculator CalcMultSevenAgain(Mult7);
    GeneralCalculator CalcMultFractionAgain(MultFraction);
    GeneralCalculator CalcMultStringAgain(MultString);
    CalcMultTwoAgain.Apply(10);
    CalcMultFiveAgain.Apply(10);
    CalcMultSevenAgain.Apply(10);
    CalcMultFractionAgain.Apply(10);
    CalcMultStringAgain.Apply(10);


//    std::function<int(int)> Func = LambdaMult;
//    std::function<int(int)> Func2 = Mult5;


//    GeneralCalculator FFour(LambdaMult);
//    GeneralCalculator FFour2(Func);
//    GeneralCalculator FFive(Mult5);
//    FTwo.Apply(10);
//    FThree.Apply(10);
//    FFour.Apply(10);
//    FFour2.Apply(10);
//    FFive.Apply(10);

    return 0;
}

