#include <iostream>
#include <cmath>
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


Polynomial::Polynomial(string equation)
{
    // PROBLEMS AT THE MOMENT
    // cannot handle '-' at the start
    // cannot handle constant
    // when sign comes before ^
    
//     /* idea behind the logic

//     we can use string substr function to extract data, but
//     we need position and length of coeffecients and exponent
//     so we use one variable to hold position and other to hold length

// A term is always between
// +-       to   \0
// +-       to   +-
// start    to   +-
// start    to   \0

// A coefficient is always between
// start   to   x
// +-      to   x
// +-      to   \0  (When there is constant in the last such as 3x^2 + 1)


//     for power look between 
//     '^' and x
//     ^ and \0  : special case when last term or only term is x^n, where greater than 1
    
//     
    
    int coff_pos = 0;   // position of the start of the coeffecient
    int coff_len = 0;  // length of the coeffecient
    int pow_pos = 0;   // position of the start of the power
    int pow_len = 0;   // length of power

    int exp_count = 0;  // represent number of exp added till now
    int coff_count = 0;; // represent number of coff added till now
    int i = 0;

    Term term_temp; // it is used to collect coefficients and exponent temporarilily

    //3.5x^7 - 76x^2
    while (i <= equation.length())
    {
        
        
        // variables means x,y or z
        if (VariableIsEncountered(equation,i))
        {
            
    
        
            string temp = equation.substr(coff_pos,coff_len);
            remove_spaces_from_string(temp);


        
      // ---------------------------------- /
      // for cases when the coefficient is 1 or -1 and we dont explicitly
      // specify it, for example: "x^2","-x^2","-   x^2","x^2 - x"
      // so anything between +- and x will be either "","+","-" because 
      // space is removed by the remove_spaces_from_string() function


            if (CoeffiecientIsOne(temp))
                assign_if_coefficient_is_one(temp,term_temp);

            else
                term_temp.coefficient(stod(temp));

            coff_count++;   // means we just added a coff to term_temp object

            // when power is one, we dont use '^' to show 1
            // if there no power, it is assumed 1, so it is here to check
            // see definition in "Helper.h"
            if (PowerIsOne(equation,i))
            {
                term_temp.exponent(1);  // set exp to one
                exp_count++;
                 (*this).terms.push_back(term_temp);
            }

            coff_len = -1;   // set to -1 because we need to count for the next coefficient from the beginning
        }

        // if "^" is encountered
        else if (PowerIsEncountered(equation,i))
        {
            pow_pos = i + 1;    // set start position for power
            pow_len = -1; // start counting again
        }

        else if (SignIsEncountered(equation,i)) // it also returns true when '\0' is encountered
        {
            // DoWhenSignIsEncountered();
         

            string temp = equation.substr(pow_pos,pow_len);
            // we used stoi because power is always whole numbers
            term_temp.exponent(stoi(temp));   //stoi is string to integer
            exp_count++;
        
            
            pow_len = -1;     // it is set -1 because at the end of loop we increment it so -1 + 1 makes it zero for next power 
            coff_len = 0;     // we set it equal to zero because coeffecients can be negative and we don't want to go beyond the length
            coff_pos = i;   // set coeffecient initial position just after the sign

            // since sign has been encoutered we can now put our term in to Polynomial
            (*this).terms.push_back(term_temp);
        }

        else if (equation[i] == '\0')   // terminator is encountered means term is completeed
        {
            // if number of coff and exp do not match
            // i.e no_of_exp < no_of_coff
            // it mean an exponent is missing an we should extract it
            // else if they do match
            // it means we have a constant in the end
            // lets say x^2 + 56.2x
            if (exp_count != coff_count)
            {
                string temp = equation.substr(pow_pos,pow_len);
                // we used stoi because power is always whole numbers
                term_temp.exponent(stoi(temp));   //stoi is string to integer
                exp_count++;
                (*this).terms.push_back(term_temp);

            }

            

            
        }

        //+ 32x^n333 
        

        coff_len++;
        pow_len++;
        i++;
    }

} 








void Polynomial::display()
{
    cout << "\n";

    for (int i = 0; i < terms.size(); i ++)
    {
        terms[i].display();
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
        cout << terms[i].coefficient() << " ";

    cout << endl << "exponent: " ;

    for (int i = 0; i < terms.size(); i ++)
        cout << terms[i].exponent() << " ";

}

int Polynomial::degree()
{
    // to find the degree of the polynomial, find maximum exponent in terms arrray

    int max = -1;

    for (int i = 0; i < this->terms.size(); i ++)
    {
        if (max < terms[i].exponent())
            max = terms[i].exponent();
    }

    return max;
}

Polynomial Polynomial::differentiate()
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

Polynomial Polynomial::integrate()
{
    Polynomial P;  // Anti-derivative

   // for each term
   for (int i = 0; i < terms.size(); i ++)
   {
        Term temp = terms[i].integrate();   // differentiate individual terms and add to p_prime terms array
        P.terms.push_back(temp);  // add the term to the last of the array
   }

    return P; // returns the object
}

double Polynomial::integrate(double a, double b)
{
    // calculates anti-derivative and evaluate P at both ends
    // using FTOC part 2
    Polynomial P = (*this).integrate();
    return (P.evaluate(b) - P.evaluate(a));  

}

double Polynomial::differentiate(double x0)
{
    // calculates slope of the tangent line to the curve (*this) at point x = x0
    // and evaluates the derivative at x0
    Polynomial P_prime = (*this).differentiate(); // P = anti-derivative
    return P_prime.evaluate(x0);
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

    // use addition wali logic to solve the same exponent problem

    return p3;
}

Polynomial Polynomial::operator+(Polynomial &p2)
{

    Polynomial p3;

   /* Concatenate Both Term Together */

// --------------------------------------------------
    for (int i = 0; i < this->terms.size(); i ++)
        p3.terms.push_back(this->terms[i]);

    for (int j = 0; j < p2.terms.size(); j ++)
        p3.terms.push_back(p2.terms[j]);
// ---------------------------------------------------

    

    vector<int> temp;   // it will be used to store indices of the elements having same exponent

    // iterate on all the terms
    for (int i = 0; i < p3.terms.size(); i ++)
    { 
        
        // store the current exponent in some variable  
        int exp = p3.terms[i].exponent();

        // compare ith term exponent with all other term's exponent
        for (int j = i + 1; j < p3.terms.size(); j ++)
        {
                // if they happen to match add the terms and store the result back in the ith term, this way we will have the added term at ith position
                if (exp == p3.terms[j].exponent())
                {
                    p3.terms[i] = p3.terms[i] + p3.terms[j];
                    temp.push_back(j);  // store the index in temp
                }
        }

        // iterate through the temp array and erase terms at those indexes
        for (int k = 0; k < temp.size(); k ++)
        {
            p3.terms.erase(p3.terms.begin() + temp[k]);

            // since we delete an element, all the indices on the right will be shift to lefy by 1 unit so we will decrement every index by 1
            for (int l = k + 1; l < temp.size(); l++)
                temp[l] = temp[l] - 1;
            // end for
        
        }

        temp.clear();   // clear the array for a different exponent
    }

    return p3;
}

Polynomial Polynomial::operator-(Polynomial p2)
{
    // multiply negative with each coefficient of right side
    // we used pass by value because we did not wanted to change
    // p2's original values
    for (int i = 0; i < p2.terms.size(); i ++)
    {
        int exp = p2.terms[i].coefficient();
        p2.terms[i].coefficient(-exp);
    }

     return ((*this) + p2);      // p1 + p2
    //return p2;
}

void Quadratic::calculateRoots()
{
    // three cases in quadratic equations
    // case 1 : b^2 - 4ac > 0
    // case 2 : b^2 - 4ac < 0
    // case 3 : b^2 - 4ac = 0
    double x1;
    double x2; 

    // case 1
    if (discriminant() > 0) 
    {
        cout << "Here\n";
        roots = new Root[2];

        x1 = (b + sqrt(discriminant()) / 2*a); 
        x2 = (b - sqrt(discriminant()) / 2*a); 

        roots[0] = Root(x1,0);
        roots[1] = Root(x2,0);

        roots_count = 2;
    }

    // case 2
    else if (discriminant() < 0)
    {
        roots = new Root[2];

        double _real = -b / 2*a;
        double _imag = sqrt(-discriminant()); // i multiplied a minus because want the magnitude

        roots[0] = Root(_real,_imag);
        roots[1] = Root(_real,-_imag);

        roots_count = 2;

    }

    // case 3
    else
    {
        roots = new Root[1];

        double _real = -b/2*a;
        *roots = Root(_real,0);

        roots_count = 1;
    }

}

void Root::display()
{
    if (imag > 0)
        std::cout << real << " + " << imag << "i" << std::endl;
    else    
        std::cout << real << " - " << imag << "i" << std::endl;
}

void Quadratic::displayRoots()
{
    for (int i = 0; i < roots_count; i ++)
    {
        roots[i].display();
    }
}

Quadratic::Quadratic(Term* _terms,int size): Polynomial(_terms,size),roots(NULL),roots_count(0)
{
    // by default all a,b and c should be zero, so if one of them is not found it is set to zero by default
    this->a = 0; this->b = 0; this->c = 0;
    // Iterate through each element and find corressponding coefficient
    // purpose of this is to extract coefficients corresspoding to a,b and c
    for (int i = 0; i < terms.size(); i ++)
    {
        switch(terms[i].exponent())
        {
            case 2:
                a = terms[i].exponent(); 
                break;
            case 1:
                b = terms[i].exponent();
                break;
            case 0:
                c = terms[i].exponent();
                break;
            default:
                break;
        }
    
    }
}


/*Polynomial Addition Logic : Pseudocode

Assume we are adding p1 and p2 together to make p3

for i = 0 to i = p3.terms.size() - 1:
    for j = i + 1 to j = p3.terms.size() - 1:
        if p3's ith term exponent = p3's jth term exponent:
            add p3's jth term with p3's ith term and store it again in p3's ith term
            store the index with exponent matched and save it in some array
        end if
    end for

    for k = 0 to k = temp.size() - 1:
        erase p3's temp[kth] term

        for l = k + 1 to l = temp.size() - 1:
            since  we deleted an element, every element on the right must shift left by one so we will decrement the index by 1 for each element
            temp[l] = temp[l] - 1
        end for
    end for

    temp.clear() :: clear array
end for

Approach:

Store the indices (plural of index) of all the elements that can be added
then add those terms to the first occurence of the the and delete all others with
the help of the indices we stored. we will store indices in a vector<int>
we will also need to shift indices because deleting an element will cause 
the polynomial to shrink hence each indices will be shift by one to sync with old position


*/
