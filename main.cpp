/*Title: Mathematical Operations on Polynomials and Application of Calculus*/

#include <iostream>
#include "Polynomial.h"


using namespace std;

int main()
{
   Term terms[3] = {Term(3,2),Term(4,1),Term(1,0)};

   Polynomial p1 = Polynomial(terms,3);
   Polynomial p2 = p1.take_derivative();

   p1.test();
   p2.test();
     
   return 0;
}
