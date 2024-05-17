#include <iostream>
#include <vector>
#include <string>
#include "Term.h"

using namespace std;

class Root;
class Polynomial;
class Quadratic;
class Cubic;

class Root
{
    public:
        double real;
        double imag;

        // constructors
        Root(){}
        Root(double _real,double _imag):real(_real),imag(_imag){}

        void display(); 

};

class Polynomial
{
    protected:
        std::vector<Term> terms;	// a dynamic array of 'Term'
           
    public:
        // constructors
        Polynomial();   // default constructor
        Polynomial(std::string equation);  

        // member functions
        void display(); // prints polynomial
        double evaluate(double x0); // evaluates polynomial at x = x0
        int degree();  // degree of polynomial 
        
        double integrate(double from,double to); // area under the curve
        double differentiate(double x0); // slope of the tangent line to the curve (*this) at point x = x0   

        vector<Term>& getTerms() {return terms;}


        // operations
        Polynomial differentiate();
        Polynomial integrate();
        Polynomial operator* (Polynomial& p2);
        Polynomial operator+ (Polynomial& p2);
        Polynomial operator- (Polynomial p2);
        friend ostream& operator<<(ostream& out,Polynomial& p); 

};
class Quadratic: public Polynomial
{
       
    public:
        vector<Root> roots;

        // constructors
        Quadratic():a(0),b(0),c(0){}
        Quadratic(std::string equation);   
        Quadratic(vector<Term>& terms);     

        // member functions               
        void displayRoots();
        double getDiscriminant() { return discriminant; }
         

        // data members
    private:
        double a = 0.0; 
        double b = 0.0; 
        double c = 0.0;   
        double discriminant;
        void calculateRoots();
        void calcDiscriminant();          
};

class Cubic : public Polynomial     // Cubic is a Polynomial
{
    
    public:
        vector<Root> roots;

        Cubic(){}
        Cubic(string equation);
        Cubic(vector<Term>& terms); 

        void displayRoots();

    private:
        double a = 0.0;
        double b = 0.0;
        double c = 0.0;
        double d = 0.0;
        void calculateRoots();        
};

