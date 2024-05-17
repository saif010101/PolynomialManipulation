#include <iostream>
#include <string>
#include <vector>
#include "Polynomial.h"
#include "Helper.h"

using namespace std;

// Definitions of Polynomial.h
//---------------------------------------------------------//
Polynomial::Polynomial()
{
    // initilize data members
}

Polynomial::Polynomial(string equation)
{

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
    //     '^' and +-
    //     ^ and \0  : special case when last term or only term is x^n, where greater than 1

    //

    int coff_pos = 0; // position of the start of the coeffecient
    int coff_len = 0; // length of the coeffecient
    int pow_pos = 0;  // position of the start of the power
    int pow_len = 0;  // length of power

    int exp_count = 0; // represent number of exp added till now
    int coff_count = 0;
    ; // represent number of coff added till now
    int i = 0;

    Term term_temp; // it is used to collect coefficients and exponent temporarilily

    // 3.5x^7 - 76x^2
    while (i <= equation.length())
    {

        // variables means x,y or z
        if (VariableIsEncountered(equation, i))
        {

            string temp = equation.substr(coff_pos, coff_len);
            remove_spaces_from_string(temp);

            // ---------------------------------- /
            // for cases when the coefficient is 1 or -1 and we dont explicitly
            // specify it, for example: "x^2","-x^2","-   x^2","x^2 - x"
            // so anything between +- and x will be either "","+","-" because
            // space is removed by the remove_spaces_from_string() function

            if (CoeffiecientIsOne(temp))
                assign_if_coefficient_is_one(temp, term_temp);

            else
                term_temp.coefficient(stod(temp));

            coff_count++; // means we just added a coff to term_temp object

            // when power is one, we dont use '^' to show 1
            // if there no power, it is assumed 1, so it is here to check
            // see definition in "Helper.h"
            if (PowerIsOne(equation, i))
            {
                term_temp.exponent(1); // set exp to one
                exp_count++;
                (*this).terms.push_back(term_temp);
            }

            coff_len = -1; // set to -1 because we need to count for the next coefficient from the beginning
        }

        // if "^" is encountered
        else if (PowerIsEncountered(equation, i))
        {
            pow_pos = i + 1; // set start position for power
            pow_len = -1;    // start counting again;
        }

        else if (SignIsEncountered(equation, i)) // it also returns true when '\0' is encountered
        {

            // DoWhenSignIsEncountered();

            if (exp_count != coff_count)
            {
                string temp = equation.substr(pow_pos, pow_len);
                // we used stoi because power is always whole numbers
                term_temp.exponent(stoi(temp)); // stoi is string to integer
                exp_count++;
                (*this).terms.push_back(term_temp);
            }

            // special case for constant
            if (NoVariableFound(equation, i))
            {
                coff_len = 0;
                coff_pos = i;
                string temp = equation.substr(i, equation.length() - +1);
                remove_spaces_from_string(temp);
                term_temp.coefficient(stod(temp));
                term_temp.exponent(0);
                this->terms.push_back(term_temp);
                break;
            }

            pow_len = -1; // it is set -1 because at the end of loop we increment it so -1 + 1 makes it zero for next power
            coff_len = 0; // we set it equal to zero because coeffecients can be negative and we don't want to go beyond the length
            coff_pos = i; // set coeffecient initial position just after the sign

            // since sign has been encoutered we can now put our term in to Polynomial
        }

        else if (equation[i] == '\0') // terminator is encountered means term is completeed
        {
            // if number of coff and exp do not match
            // i.e no_of_exp < no_of_coff
            // it mean an exponent is missing an we should extract it
            // else if they do match
            // it means we have a constant in the end
            // lets say x^2 + 56.2x
            if (exp_count != coff_count)
            {
                string temp = equation.substr(pow_pos, pow_len);
                // we used stoi because power is always whole numbers
                term_temp.exponent(stoi(temp)); // stoi is string to integer
                exp_count++;
                (*this).terms.push_back(term_temp);
            }
        }

        coff_len++;
        pow_len++;
        i++;
    }
}
void Polynomial::display()
{
    // cout << terms.size() << endl;
    for (int i = 0; i < terms.size(); i++)
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

    for (int i = 0; i < terms.size(); i++)
        sum += terms[i].coefficient() * power(x0, terms[i].exponent()); // ith coeffecient multiplied by x0 raised to ith power, power and coeffecent are related

    return sum;
}

int Polynomial::degree()
{
    // to find the degree of the polynomial, find maximum exponent in terms arrray

    int max = -1;

    for (int i = 0; i < this->terms.size(); i++)
    {  
        if (max < terms[i].exponent())
            max = terms[i].exponent();
    }

    return max;
}

Polynomial Polynomial::differentiate()
{

    Polynomial p_prime; // p'(x)

    // for each term
    for (int i = 0; i < terms.size(); i++)
    {
        Term temp = terms[i].differentiate(); // differentiate individual terms and add to p_prime terms array

        // check if the differentiated term's coefficient is not zero, because if its zero, no need to add the term
        if (temp.coefficient() != 0)
        {
            p_prime.terms.push_back(temp); // add the term to the last of the array
        }
    }

    return p_prime; // returns the object
}

Polynomial Polynomial::integrate()
{
    Polynomial P; // Anti-derivative

    // for each term
    for (int i = 0; i < terms.size(); i++)
    {
        Term temp = terms[i].integrate(); // differentiate individual terms and add to p_prime terms array
        P.terms.push_back(temp);          // add the term to the last of the array
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

    Polynomial p3; // product of p1 * p2

    // for each term of p1
    for (int i = 0; i < (*this).terms.size(); i++)
    {
        // multiply with every other term of p2
        for (int j = 0; j < p2.terms.size(); j++)
        {
            Term p3_term = (*this).terms[i] * p2.terms[j]; // 4x^3 * 5x^3  = 20x^6
            p3.terms.push_back(p3_term);
        }
    }

    // use addition wali logic to solve the same exponent problem

    vector<int> temp; // it will be used to store indices of the elements having same exponent

    // iterate on all the terms
    for (int i = 0; i < p3.terms.size(); i++)
    {

        // store the current exponent in some variable
        int exp = p3.terms[i].exponent();

        // compare ith term exponent with all other term's exponent
        for (int j = i + 1; j < p3.terms.size(); j++)
        {
            // if they happen to match add the terms and store the result back in the ith term, this way we will have the added term at ith position
            if (exp == p3.terms[j].exponent())
            {
                p3.terms[i] = p3.terms[i] + p3.terms[j];
                temp.push_back(j); // store the index in temp
            }
        }

        // iterate through the temp array and erase terms at those indexes
        for (int k = 0; k < temp.size(); k++)
        {
            p3.terms.erase(p3.terms.begin() + temp[k]);

            // since we delete an element, all the indices on the right will be shift to lefy by 1 unit so we will decrement every index by 1
            for (int l = k + 1; l < temp.size(); l++)
                temp[l] = temp[l] - 1;
            // end for
        }

        temp.clear(); // clear the array for a different exponent
    }

    return p3;
}

Polynomial Polynomial::operator+(Polynomial &p2)
{

    Polynomial p3;

    /* Concatenate Both Term Together */

    // --------------------------------------------------
    for (int i = 0; i < this->terms.size(); i++)
        p3.terms.push_back(this->terms[i]);

    for (int j = 0; j < p2.terms.size(); j++)
        p3.terms.push_back(p2.terms[j]);
    // ---------------------------------------------------

    vector<int> temp; // it will be used to store indices of the elements having same exponent

    // iterate on all the terms
    for (int i = 0; i < p3.terms.size(); i++)
    {

        // store the current exponent in some variable
        int exp = p3.terms[i].exponent();

        // compare ith term exponent with all other term's exponent
        for (int j = i + 1; j < p3.terms.size(); j++)
        {
            // if they happen to match add the terms and store the result back in the ith term, this way we will have the added term at ith position
            if (exp == p3.terms[j].exponent())
            {
                p3.terms[i] = p3.terms[i] + p3.terms[j];
                temp.push_back(j); // store the index in temp
            }
        }

        // iterate through the temp array and erase terms at those indexes
        for (int k = 0; k < temp.size(); k++)
        {
            p3.terms.erase(p3.terms.begin() + temp[k]);

            // since we delete an element, all the indices on the right will be shift to lefy by 1 unit so we will decrement every index by 1
            for (int l = k + 1; l < temp.size(); l++)
                temp[l] = temp[l] - 1;
            // end for
        }

        temp.clear(); // clear the array for a different exponent
    }

    return p3;
}

Polynomial Polynomial::operator-(Polynomial p2)
{
    // multiply negative with each coefficient of right side
    // we used pass by value because we did not wanted to change
    // p2's original values
    for (int i = 0; i < p2.terms.size(); i++)
    {
        int exp = p2.terms[i].coefficient();
        p2.terms[i].coefficient(-exp);
    }

    return ((*this) + p2); // p1 + p2
    // return p2;
}

// End of the Definition of Polynomial
// --------------------------------------------------------------//

void Quadratic::calculateRoots()
{
    // call discrimanant function to store discriminant
    calcDiscriminant();
    // three cases in quadratic equations
    // case 1 : b^2 - 4ac > 0
    // case 2 : b^2 - 4ac < 0
    // case 3 : b^2 - 4ac = 0

    double x1;
    double x2;

    // case 1
    if (discriminant > 0)
    {
        x1 = (-b + sqrt(discriminant)) / (2 * a);
        x2 = (-b - sqrt(discriminant)) / (2 * a);
        //cout << x1 << " " << x2 << "\n";
        roots.push_back(Root(x1, 0));
        roots.push_back(Root(x2, 0));
    }

    // case 2
    else if (discriminant < 0)
    {

        double _real = -b / (2 * a);
        double _imag = sqrt(-discriminant) / (2 * a); // i multiplied a minus because want the magnitude

        roots.push_back(Root(_real, _imag));
        roots.push_back(Root(_real, -_imag));
    }

    // case 3
    else
    {
        double _real = -b / (2 * a);
        roots.push_back(Root(_real, 0));
    }
}

void Root::display() // needs improvement
{
    
    if (imag > 0)
        std::cout << real << " + " << imag << "i";
    else if (imag < 0)
        std::cout << real << " - " << -imag << "i";
    else   // (real roots) 
        std::cout << real;
    
}

void Quadratic::displayRoots()
{
    cout << "Set of Root(s) : {";
    for (int i = 0; i < this->roots.size(); i++)
    {
        // means don't put a comma before the first root
        if (i != 0)
            cout << " , ";

        this->roots[i].display();     
    }
    cout << "}" << endl;
}


Quadratic::Quadratic(string equation) : Polynomial(equation)
{
    for (int i = 0; i < terms.size(); i++)
    {
        switch (terms[i].exponent())
        {
        case 2:
            a = terms[i].coefficient();
            break;
        case 1:
            b = terms[i].coefficient();
            break;
        case 0:
            c = terms[i].coefficient();
            break;
        default:
            break;
        }
    }

    calculateRoots();
}

Quadratic::Quadratic(vector<Term>& terms)
{
    for (int i = 0; i < terms.size(); i++)
    {
        switch (terms[i].exponent())
        {
        case 2:
            this->a = terms[i].coefficient();
            break;
        case 1:
            this->b = terms[i].coefficient();
            break;
        case 0:
            this->c = terms[i].coefficient();
            break;
        default:
            break;
        }
    }

    calculateRoots();
}

void Quadratic::calcDiscriminant()
{
    this->discriminant = b * b - 4 * a * c; // discriminant = b^2 - 4ac
}


Cubic::Cubic(string equation) : Polynomial(equation)
{

    for (int i = 0; i < terms.size(); i++)
    {

        switch (terms[i].exponent())
        {
        case 3:
            this->a = terms[i].coefficient();
            break;
        case 2:
            this->b = terms[i].coefficient();
            break;
        case 1:
            this->c = terms[i].coefficient();
            break;
        case 0:
            this->d = terms[i].coefficient();
            break;
        default:
            break;
        }
    }
}

Cubic::Cubic(vector<Term>& terms)
{
    
    this->terms = terms;
 
    for (int i = 0; i < terms.size(); i++)
    {       

        switch (terms[i].exponent())
        {
        case 3:
            this->a = terms[i].coefficient();
            break;
        case 2:
            this->b = terms[i].coefficient();
            break;
        case 1:
            this->c = terms[i].coefficient();
            break;
        case 0:
            this->d = terms[i].coefficient();
            break;
        default:
            break;
        }
    }

    calculateRoots();
}

void Cubic::displayRoots()
{
    cout << "Set of Root(s) : {";
    for (int i = 0; i < this->roots.size(); i++)
    {
        // means don't put a comma before the first root
        if (i != 0)
            cout << " , ";

        this->roots[i].display();     
    }
    cout << "}" << endl;
}

void Cubic::calculateRoots()
{
    // case 1 :
    // discriminant < 0
    // means there is no local minimum or maximum for the cubic equation

    // case 2 :
    // discriminant == 0
    // means there is one point at which cubic equation has a horizontal line
    // but it cannot be a maximum or minimum

    // differentiate cubic equation to find extreme values
    Polynomial p = this->differentiate();

    Quadratic quad(p.getTerms()); // initilize Quadratic object with polynomial terms

    // case 1:
    if (quad.getDiscriminant() < 0)
    {

        double r = newtonMethod(*this, 0);
        // create a root with real part r and imag part zero and add it to the array
        this->roots.push_back(Root(r, 0));
    }

    // case 2:
    else if (quad.getDiscriminant() == 0)
    {
        double r;
        // if a > 0 then root lies to the right infliction point
        if (this->a > 0)
            r = newtonMethod(*this, quad.roots[0].real + 1);
        // if a < 0 then root lies to the left infliction point
        else
            r = newtonMethod(*this, quad.roots[0].real - 1);

        // create a root with imag part zero and real part equal to root
        // and add it to the roots array
        this->roots.push_back(Root(r, 0));
    }

    // case 3:
    else // if getDiscriminant() > 0
    {
        // store roots in respective variables
        double r1 = quad.roots[0].real;
        double r2 = quad.roots[1].real;

        arrange(r1, r2); // arrange r1 and r2 so r1 is min(r1,r2) and r2 is max(r1,r2)
        cout << r1 << " " << r2 << "\n";
        double sign = this->evaluate(r1) * this->evaluate(r2); // take product of function values to deterime sign

        if (sign < 0) // negative sign
        {
             // calculate roots
             double _root1 = newtonMethod(*this, r1 - 1);
             double _root2 = newtonMethod(*this, (r1 + r2) / 2);
             double _root3 = newtonMethod(*this, r2 + 1);

             // store in roots array
             this->roots.push_back(Root(_root1,0));
             this->roots.push_back(Root(_root2,0));
             this->roots.push_back(Root(_root3,0));
        }

        else if (sign > 0) // positive sign
        {

            double _root;

            if (this->a > 0)
                _root = newtonMethod(*this, r1 - 1);          
            else
                _root = newtonMethod(*this, r2 + 1);


            // add root to roots array
            this->roots.push_back(Root(_root,0));

        }

        else // product is zero
        {
            // create vars to store roots
            double _root1;
            double _root2;
            double _root3;

            if (this->a > 0)
            {
                _root1 = r2;
                _root2 = r2;
                _root3 = newtonMethod(*this, r1 - 1);
            }

            else
            {
                _root1 = r1;
                _root2 = r1;
                _root3 = newtonMethod(*this, r2 + 1);
            }

            // store in roots array
             this->roots.push_back(Root(_root1,0));
             this->roots.push_back(Root(_root2,0));
             this->roots.push_back(Root(_root3,0));
        }
    }
}

ostream &operator<<(ostream &out, Polynomial &p)
{
    p.display();
    return out;
}





/* Polynomial Addition Logic : Pseudocode

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
