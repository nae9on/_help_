/*
 * complex.h
 *
 *  Created on: Aug 21, 2019
 *      Author: akadar
 *
 *  What to put in a header file? Refer [5]
 */

#ifndef COMPLEX_H_
#define COMPLEX_H_

/*
 * Pre-processor directives are statements preceding with #, which the compiler never see's.
 *
 * Pre-processor directives are expanded by the pre-processor before the program is compiled,
 * thus causing a sort of blind replacement. The validity of the types or syntax involved is not
 * checked in any way.
 *
 * There are three main types of pre-processor directives:
 * 1) Headers.
 * 2) Macros.
 * 3) Conditional compilation.
 */

// Example Header
#include <cmath>

class cx{

    // Example Macro
#define my_double double // Note no semicolon needed.
    // Note: Unlike macros typedef and using are compiler tokens which the pre-processor will ignore.
    //typedef double my_double;
    //using my_double=double;

    /*
     * Caution: it is dangerous to use #define, typedef or using in a header file at the global scope,
     * because a header file is typically included by several translation units and therefore it cannot
     * contain definitions that might produce multiple definitions of the same name in those units [5].
     * This can create ambiguity resulting in compilation fail or worse wrong code behavior. If they
     * are to be included, include them in a restricted scope such as class scope.
     *
     * For guidelines on what to put in a header file? Refer [5].
     *
     */

public:
    cx(){real = 0; imag = 0;}
    cx(my_double r, my_double i);
    void print_abs();
    double getReal(){return real;}
    double getImag(){return imag;}
private:
    my_double real;
    my_double imag;
};

#endif /* COMPLEX_H_ */
