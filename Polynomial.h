#include <iostream>
#include <vector>
#include <string>
#include "Term.h"



class Polynomial
{
    protected:
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
        int degree();  // degree of polynomial  

        //   
        double integrate(double from,double to); // area under the curve
        double differentiate(double x0); // slope of the tangent line to the curve (*this) at point x = x0   


        // operations
        Polynomial differentiate();
        Polynomial integrate();
        Polynomial operator* (Polynomial& p2);
        Polynomial operator+ (Polynomial& p2);
        Polynomial operator- (Polynomial p2);
};

class Root
{
    private:
        double real;
        double imag;
    public:
        Root(){}
        Root(double _real,double _imag):real(_real),imag(_imag){}

        void display();
};

class Cubic : public Polynomial
{
    private:
        Root* roots;
    public:
        Cubic(){}
        Cubic(Term* _terms,int size): Polynomial(_terms,size)
        {

        } 
};

class Quadratic: public Polynomial
{
    private:
        double a; double b; double c;
        Root* roots;
        int roots_count;

        double discriminant()
        {
            std::cout << a << b << c << std::endl;
            return b*b - 4*a*c;     // discriminant = b^2 - 4ac
        }
        void calculateRoots();
    public:
        Quadratic():roots(NULL),a(0),b(0),c(0),roots_count(0){}
        Quadratic(Term* _terms,int size);
        Quadratic(std::string equation):Polynomial(equation){ }

        // member functions       
        
        void displayRoots();

        // destructor
        ~Quadratic()
         {           
            delete[] roots;
         }

        
};

