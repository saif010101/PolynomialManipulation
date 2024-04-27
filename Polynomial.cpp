#include <iostream>
#include <string>
#include <vector>
#include "Polynomial.h"
#include "Helper.h"

using namespace std;


Polynomial::Polynomial()
{
    // initilize data members
}

Polynomial::Polynomial(Term* values, int size)
{
    for (int i = 0; i < size; i ++)
        terms.push_back(values[i]);    // we can initilize our Polynomial with an array of type Term    
}


// Polynomial::Polynomial(string equation)
// {
//     // TO DO: HANDLE CONSTANT CASES SUCH AS : x^2 + 1 or 1 + x^2
//     // MAKE LOGIC MORE READABLE
//     // SORT THE ARRAYS TO MAKE COFF AND POW DESCENDING
//     // IMPROVE DISPLAY FUNCTION

//     //  x^2 - 2 + x  (start to +-,+- to end,between signs +-   +-)
//     //  2 - x^2
//     //  x^2 - 2
//     //  x^2 + 2x^3 + 2 - x^2


//     /*The  purpose of this function is to extract coeffecients and power 
//     from a string.
    
//     The convience of this that user can freely enter a polynomial
//     let's say 2x^5 - 3x^8 - 3x
//     then we can extract coff : [2,-3,-3], pow : [5,8,1]*/

//     /* idea behind the logic

//     we can use string substr function to extract data, but
//     we need position and length of coeffecients and power
//     so we use one variable to hold position and other to hold length


//     for coeffecients, 
//     look between
//     start and x
//     +- to x


//     for power look between 
//     '^' and x
//     ^ and \0  : special case when last term or only term is x^n, where greater than 1
    
//     */
    
//     int coff_pos = 0;   // position of the start of the coeffecient
//     int coff_len = 0;  // length of the coeffecient
//     int pow_pos = 0;   // position of the start of the power
//     int pow_len = 0;   // length of power

//     // multiply p1,p2
//     // add p1,p2
//     // integrate p1 from 2 to 5
//     // integrate p1
//     // differentiate p1 at x0 or differentiate p1
//     // subtract p1,p2
//     // linearize p1 at x0

//     int i = 0;
//     Term temp;

//     while (i <= equation.length())
//     {
        
        
//         // variables means x,y or z
//         if (VariableIsEncountered(equation,i))
//         {
//             // when power is one, we dont use '^' to show 1
//             // if there no power, it is assumed 1, so it is here to check
//             // see definition in "Helper.h"
//             if (PowerIsOne(equation,i))
//             {
//                 temp.exponent(1);
//                 pow.push_back(1);
//             }
    
        
//             string temp = equation.substr(coff_pos,coff_len);
//             remove_spaces_from_string(temp);


        
//       // ---------------------------------- /
//       // for cases when the coefficient is 1 or -1 and we dont explicitly
//       // specify it, for example: "x^2","-x^2","-   x^2","x^2 - x"
//       // so anything between +- and x will be either "","+","-" because 
//       // space is removed by the remove_spaces_from_string() function


//             if (CoeffiecientIsOne(temp))
//                 assign_if_coefficient_is_one(temp,coff);

//             else
//                 coff.push_back(stod(temp));



//             coff_len = -1;   // set to -1 because we need to count for the next coefficient from the beginning
//         }

//         // if "^" is encountered
//         else if (PowerIsEncountered(equation,i))
//         {
//             pow_pos = i + 1;    // set start position for power
//             pow_len = -1; // start counting again
//         }

//         else if (SignIsEncountered(equation,i)) // it also returns true when '\0' is encountered
//         {
//             // DoWhenSignIsEncountered();
         

//             string temp = equation.substr(pow_pos,pow_len);
//             // we used stoi because power is always whole numbers
//             pow.push_back(stoi(temp));   //stoi is string to integer
        
            
//             pow_len = -1;     // it is set -1 because at the end of loop we increment it so -1 + 1 makes it zero for next power 
//             coff_len = 0;     // we set it equal to zero because coeffecients can be negative and we don't want to go beyond the length
//             coff_pos = i;   // set coeffecient initial position just after the sign
//         }


//         coff_len++;
//         pow_len++;
//         i++;
//     }

// } 








void Polynomial::display()
{
    cout << "\n";

    for (int i = 0; i < terms.size(); i ++)
    {
        
        cout << " " << terms[i].coefficient() << "x^" << terms[i].exponent();
    }

    cout << "\n";
}

double Polynomial::evaluate(double x0)
{
    /* This function evaluates the Polynomial at x = x0
    It multiplies the the coefficient of ith term with exponent of ith term 
    and adding them.*/
    
    double sum = 0.0;

    for (int i = 0; i < terms.size(); i ++)
        sum += terms[i].coefficient() * power(x0,terms[i].exponent());    // ith coeffecient multiplied by x0 raised to ith power, power and coeffecent are related

    return sum;
}





// rules
// there must be no space between x and ^ 
// no extra space at the end of the string

void Polynomial::test()
{
    cout << "coff: ";
    for (int i = 0; i < terms.size(); i ++)
    {
        cout << terms[i].coefficient() << " ";
    }

    cout << endl << "exponent: " ;

    for (int i = 0; i < terms.size(); i ++)
    {
        cout << terms[i].exponent() << " ";
    }
}

Polynomial Polynomial::take_derivative()
{

   Polynomial p_prime;  // p'(x)

   // for each term
   for (int i = 0; i < terms.size(); i ++)
   {
        Term temp = terms[i].differentiate();   // differentiate individual terms and add to p_prime terms array

        // check if the differentiated term's coefficient is not zero, because if its zero, no need to add the term
        if (temp.coefficient() != 0)
        {      
            p_prime.terms.push_back(temp);  // add the term to the last of the array
        }
   }

    return p_prime; // returns the object
}

Polynomial Polynomial::operator*(Polynomial &p2)
{
    // (*this) means p1 or polynomial 1

    Polynomial p3;  // product of p1 * p2   

    // for each term of p1
    for (int i = 0; i < (*this).terms.size(); i ++)
    {
        // multiply with every other term of p2
        for (int j = 0; j < p2.terms.size(); j ++)
        {
            Term p3_term = (*this).terms[i] * p2.terms[i];  // 4x^3 * 5x^3  = 20x^6
            p3.terms.push_back(p3_term);
        }
    }

    return p3;
}


