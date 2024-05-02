/*Title: Mathematical Operations on Polynomials with Application of Calculus*/

#include <iostream>
#include "Polynomial.h"


using namespace std;

int main()
{

   Term terms1[3] = {Term(9,2),Term(3,1),Term(8,2)};
   Term terms2[2] = {Term(5,3),Term(5,4)};

   Polynomial p1(terms1,3);
   Polynomial p2(terms2,2);

   cout << "Test\n";
   Polynomial p3 = p1 + p2;
   p3.display();
   return 0;
}
