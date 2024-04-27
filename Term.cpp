#include <iostream>
#include <string>
#include <vector>
#include "Term.h"

using namespace std;

Term Term::differentiate()
{
    // here we are using the power rule
    // The power rule states that, p(x) = nx^m, then p'(x) = (n*m)x^(m-1);
    // i.e multiply exponent with coefficient and decrease power by 1
    // we are adding an if condition because polynomials exponent are non-negative integers
    if ((*this).exponent() > 0)
    {
        double _coff = (*this).exponent()   *   (*this).coefficient();
        double _exp =  (*this).exponent() - 1;

        return Term(_coff,_exp);  // intialize with new values and return
    }

    return Term(0.0,0); // returns a zero term
}

Term Term::integrate()
{
    // 3x^2 + 4x
    // x^3 + 2x^2
    // here we are using the power rule for integration
    // The power rule states that, p(x) = nx^m, then p'(x) = (n*m)x^(m-1);
    // i.e multiply exponent with coefficient and decrease power by 1
    // we are adding an if condition because polynomials exponent are non-negative integers
    if ((*this).coefficient() != 0)
    {
        
        double _exp =  (*this).exponent() + 1;     
        double _coff = (*this).coefficient() / _exp; 

        return Term(_coff,_exp);  // intialize with new values and return
    }

    return Term(0.0,0); // returns a zero term
}

// 5x^2
// 10 x
Term Term::operator*(Term &p2_term)
{
    // this function multiply object of class Term in such a way that 
    // the resulting term coeffiecient is product of both terms coff and 
    // the result term exponent is addition of both terms's exp
    // for example:
    // 2x^3 * 4x^2 = 8x^5

    double p3_coff = (*this).coefficient() * p2_term.coefficient();
    double p3_exp  = (*this).exponent() + p2_term.exponent();

    return Term(p3_coff,p3_exp); // creates an object and initiliases it with values and returns it
}