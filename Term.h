#include <iostream>
#include <vector>
#include <string>

class Term
{
    private:
        double coff;
        int exp;
    public:
        // constructors
    	Term(){}	// default constructor
    	Term(double _coff,int _exp) : coff(_coff),exp(_exp){}	// parametrized constructor
    	
    	// getters
    	double coefficient() { return coff; }  // get coeffecient
    	int exponent() { return exp; }  // get exponent

        // setters
        void coefficient(double coff) { this->coff = coff; }  // get coeffecient
    	void exponent(int exp) { this->exp = exp; }  // get exponent

        //functions
        Term differentiate();
        Term integrate();
        void display();

        // operators
        Term operator* (Term& p2_term);	 
        Term operator+ (Term& p2_term);	
};
