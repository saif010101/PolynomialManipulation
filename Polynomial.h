#include <iostream>
#include <vector>
#include <string>
#include "Term.h"


class Polynomial
{
    private:
        std::vector<Term> terms;	// a dynamic array of 'Term'
           
    public:
        // constructors
        Polynomial();   // default constructor
        Polynomial(Term* values,int size);   // parametrized ctor, intialize Polynomial with given values
        Polynomial(std::string equation);  

        // member functions
        void display(); // prints polynomial
        double evaluate(double x0); // evaluates polynomial at x = x0
        void test();
        Polynomial take_derivative();

        // operators
        Polynomial operator* (Polynomial& p2);
};
