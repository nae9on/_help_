/*
 * complex.h
 *
 *  Created on: Aug 21, 2019
 *      Author: akadar
 */

#ifndef COMPLEX_H_
#define COMPLEX_H_

/*
 * Note: #define is a preprocessor token which the compiler will never see.
 * This replacement is performed by the preprocessor, and happens before the program is compiled,
 * thus causing a sort of blind replacement. The validity of the types or syntax involved is not
 * checked in any way.
 */
#define my_double double

// Note: typedef and using are compiler tokens which the preprocessor won't touch.
//typedef double my_double;

class cx{
public:
	cx(){real = 0; imag = 0;}
	cx(my_double r, my_double i);
private:
	my_double real;
	my_double imag;
};

#endif /* COMPLEX_H_ */
