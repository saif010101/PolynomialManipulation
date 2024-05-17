/* CS1004 - Object Oriented Programming : Semester Project
Title: Mathematical Operations on Polynomials with Application of Calculus
Project Members:
Wajid Ali (23P-0606)
Muhammad Saif (23P-0512)
Afrasiab Shahid (23P-0585)

// Room for imrpovement :

1. Sort the terms in descending order so the output is more organized
2. make the terminal for user friendly by accepting spaces and invalid inputs

*/

#include <iostream>
#include "Polynomial.h"

void menu();
void help();
void splitWords(vector<string> &, string);
int countWords(string command);
bool PolynomialExists(string polynomial_name, const vector<string> &names, int &index);
void createNewPolynomial(vector<string> &names, vector<Polynomial> &polys, const vector<string> &words);
void findAntiDerivative(Polynomial &poly);
void IntegrateWithLimits(Polynomial &poly, const vector<string> &words);
void findDerivateAtPoint(Polynomial &poly, double x0);
void findDerivative(Polynomial &poly);
void printPolynomials(vector<Polynomial> &polys, vector<string> &names);
void addPolynomials(Polynomial &p1, Polynomial &p2);
void subtractPolynomials(Polynomial &p1, Polynomial &p2);
void multiplyPolynomials(Polynomial &p1, Polynomial &p2);
void evaluatePolynomialAtPoint(Polynomial &p1, double x0);
void findPolynomialRoots(Polynomial &p);

using namespace std;

int main()
{

      vector<string> names;         // stores the names of the polynomials
      vector<Polynomial> polynomials;     // stores the actual polynomials
      vector<string> words;   // store user command

      string command;   // used for taking input from user

      int count;  // it counts the number of words in user command
      int index; // it is used to refer to elements in polynomials vector array
      int index_2; // it is used to refer to elements in polynomials vector array

      menu();

      
      do    // (keep looping until user enter "exit" command)
      {
            /* always show command : to make sure user is active */
            cout << "type command : ";
            getline(cin >> ws, command);


            /* use split words function to splits string into array of words*/
            splitWords(words, command);
            count = countWords(command);


            // case : new [polynomial_name]
            if (count == 2 && words[0] == "new" && !PolynomialExists(words[1], names, index))
                  createNewPolynomial(names, polynomials, words);



            // case : integrate [polynomial_name]
            else if (count == 2 && words[0] == "integrate" && PolynomialExists(words[1], names, index))
                  findAntiDerivative(polynomials[index]);



            // case : finds roots of [polynomial_name]
            else if (count == 3 && words[0] == "roots" && words[1] == "of" && PolynomialExists(words[2], names, index))
                  findPolynomialRoots(polynomials[index]);



            // case : integrate [polynomial_name] from [a] to [b]
            else if (count == 6 && words[0] == "integrate" && PolynomialExists(words[1], names, index) && words[2] == "from" && words[4] == "to")
                  IntegrateWithLimits(polynomials[index], words);



            // case : diff [polynomial_name] at [x0]
            else if (count == 4 && words[0] == "diff" && PolynomialExists(words[1], names, index) && words[2] == "at")
                  findDerivateAtPoint(polynomials[index], stod(words[3]));




            // case : diff [polynomial_name]
            else if (count == 2 && words[0] == "diff" && PolynomialExists(words[1], names, index))
                  findDerivative(polynomials[index]);



            // case: print
            else if (count == 1 && words[0] == "print")
                  printPolynomials(polynomials, names);



            // case : [polynomial1_name] + [polynomial2_name]
            else if (count == 3 && words[1] == "+" && PolynomialExists(words[0], names, index) && PolynomialExists(words[2], names, index_2))
                  addPolynomials(polynomials[index], polynomials[index_2]);



            // case : [polynomial1_name] - [polynomial2_name]
            else if (count == 3 && words[1] == "-" && PolynomialExists(words[0], names, index) && PolynomialExists(words[2], names, index_2))
                  subtractPolynomials(polynomials[index], polynomials[index_2]);



            // case : [polynomial1_name] * [polynomial2_name]
            else if (count == 3 && words[1] == "*" && PolynomialExists(words[0], names, index) && PolynomialExists(words[2], names, index_2))
                  multiplyPolynomials(polynomials[index], polynomials[index_2]);



            // case : evaluate [polynomial_name] at [x0]
            else if (count == 4 && words[0] == "evaluate" && PolynomialExists(words[1], names, index) && words[2] == "at")
                  evaluatePolynomialAtPoint(polynomials[index], stod(words[3]));
            


            else if (count == 1 && words[0] == "help")
                  help();


            else
                  cout << "invalid command\n";


            words.clear();    // clears the words array so user it is ready for next input

      } while (command != "exit");


      return 0;

}  // end of main


void splitWords(vector<string> &words, string command)
{
      int len = 0;
      int pos = 0;

      for (int i = 0; i <= command.length(); i++)
      {
            if (command[i] == ' ' || command[i] == '\0')
            {
                  string temp = command.substr(pos, len);
                  words.push_back(temp);

                  pos = i + 1;
                  len = -1;
            }

            len++;
      }
}

int countWords(string command)
{
      int count = 0;

      for (int i = 0; i < command.length(); i++)
      {
            if (command[i] == ' ')
                  count += 1;
      }

      return count + 1; // if there are n spaces in a string then there will be n + 1 words
                        // assuming there is a gap of single space character between each word
}

bool PolynomialExists(string polynomial_name, const vector<string> &names, int &index)
{
      // iterate through the names of the polynomials and see if we can find it
      for (int i = 0; i < names.size(); i++)
      {
            // if found return true
            if (names[i] == polynomial_name)
            {
                  index = i;
                  return true;
            }
      }

      // cout << "polynomial not found\n";
      index = -1;
      return false;
}

void createNewPolynomial(vector<string> &names, vector<Polynomial> &polys, const vector<string> &words)
{
      // execute if there are two words
      // and the first word is new
      // and no polynomial of this name exists before

      names.push_back(words[1]); // save name in names array
      string p;                  // create a var sting to get user input

      /* get user input */
      cout << "enter polynomial : ";
      getline(cin >> ws, p);

      /* add polynomial to array */
      polys.push_back(Polynomial(p));

      /* show success prompt */
      cout << "polynomial added sucessfully.\n"; // success prompt
}

void findAntiDerivative(Polynomial &poly)
{
      // create an object of polynomial and store the anti derivative
      Polynomial anti_derivative = poly.integrate();

      /* print anti-derivative */
      cout << "= " << anti_derivative << "\n";
}

void IntegrateWithLimits(Polynomial &poly, const vector<string> &words)
{
      // extracting limits of integration from string
      double a = stod(words[3]);
      double b = stod(words[5]);

      /* display the value */
      cout << "= " << poly.integrate(a, b) << "\n";
}

void findDerivateAtPoint(Polynomial &poly, double x0)
{
      /* display the result to user */
      cout << "= " << poly.differentiate(x0) << "\n";
}

void findDerivative(Polynomial &poly)
{
      /* calculate derivative */
      Polynomial p = poly.differentiate();

      /* display derivative */
      cout << "= " << p << endl;
}

void printPolynomials(vector<Polynomial> &polys, vector<string> &names)
{
      cout << "\n";
      for (int i = 0; i < polys.size(); i++)
            cout << names[i] << " : " << polys[i];
      cout << "\n";
}

void addPolynomials(Polynomial &p1, Polynomial &p2)
{
      /* add two polynomials */
      Polynomial p3 = p1 + p2;

      /* display the result */
      cout << "= " << p3 << endl;
}

void subtractPolynomials(Polynomial &p1, Polynomial &p2)
{
      /* subtract two polynomials */
      Polynomial p3 = p1 - p2;

      /* display the result */
      cout << "= " << p3 << endl;
}

void multiplyPolynomials(Polynomial &p1, Polynomial &p2)
{
      /* multiply two polynomials */
      Polynomial p3 = p1 * p2;

      /* display the result */
      cout << "= " << p3 << endl;
}

void evaluatePolynomialAtPoint(Polynomial &p1, double x0)
{
      /* display the result */
      cout << "= " << p1.evaluate(x0) << endl;
}

void findPolynomialRoots(Polynomial &p)
{
      int degree = p.degree();

      if (degree == 3)
      {
            Cubic c(p.getTerms());
            c.displayRoots();
      }
      else if (degree == 2)
      {
            Quadratic q(p.getTerms());
            q.displayRoots();
      }
      else
      {
            cout << "only cubic and quadratic equations allowed\n";
      }
}

void menu()
{
      cout << "************************************************************************\n"
           << "******* Operations on Polynomials with Applications of Calculus ********\n"
           << "************************************************************************\n"
              "                        Wajid Ali (23P-0606)\n"
              "                        Muhammad Saif (23P-0512)\n"
              "                        Afrasiab Shahid (23P-0585)\n\n"

           << "\ntype \"help\" for the commands list\n\n\n";

} 

void help()
{
      
      system("cls");    // for windows
      // system("clear"); // for linux

      menu();           
      cout << "Commands List :\n\n"

      "new [polynomial_name]		-- prompt user to add a new polynomial\n"
      "integrate [polynomial_name]		-- calculates anti-derivative of polynomial\n"
      "integrate [polynomial_name] from [a] to [b]    -- calculates area from a to b\n"
      "diff [polynomial_name]		-- calculates derivate \n"
      "diff [polynomial_name] at [x0]	-- calculates the value of derivative at x\n"
      "roots of [polynomial_name]	-- calculate roots of polynomial (cubic and lower only)\n"
      "evaluate [polynomial_name] at [x0]  -- evaluate polynomial at x0\n"
      "[polynomial1_name] + [polynomial2_name]	-- adds two polynomials\n"
      "[polynomial1_name] - [polynomial2_name]	-- subtracts two polynomials\n"
      "[polynomial1_name] * [polynomial2_name] -- multiplies two polynomials\n"
      "print	-- prints all polynomials saved by the user\n"
      "exit    -- exits out the program\n\n\n";
}
