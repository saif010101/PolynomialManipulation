#include <iostream>
#include <cmath>

using namespace std;

double power(double base,int exp);
bool PowerIsOne(string equation,int index);
bool CoeffiecientIsOne(string temp);
void assign_if_coefficient_is_one(string temp,Term& tmp);
bool VariableIsEncountered(string equation,int index);
bool PowerIsEncountered(string equation,int index);
bool SignIsEncountered(string equation,int index);
bool NoVariableFound(string equation,int index);
void remove_spaces_from_string(string& str); // this function serves an important purpose
double newtonMethod(Cubic& p,double ini_guess);
void arrange (double& r1,double& r2);
int countWords(string command);



double power(double base,int exp)
{
    // power function algorithm
    // basically keep multiplying base with itself 'exp' times
    
    double result = 1;

    for (int i = 0; i < exp; i ++)
        result *= base;    // result = result * base;
    

    return result;
}

bool VariableIsEncountered(string equation,int index)
{
    // means that if in a string any variable x,y or z is encountered it should indicate it
    if (equation[index] >= 'x' && equation[index] <= 'z')
    {
        return true;
    }

    return false;
}

bool PowerIsEncountered(string equation, int index)
{
    // since x,y or z raised to something is denoted by ^, so if it is encountered indicate it
    if (equation[index] == '^')
    {
        return true;
    }

    return false;
}

bool SignIsEncountered(string equation, int index)
{
    // indicate whenver a plus or minus sign is encountered
    if (equation[index] == '+' || equation[index] == '-')
    {
        return true;
    }

    return false;
}

void remove_spaces_from_string(string& str)
{
    // create an empty string
    string temp = "";

    // iterate through the string
    for (int i = 0; i < str.length(); i ++)
    {
        // whenever something other than space is found append it to the string
        if (str[i] != ' ')
        {
            temp += str[i];
        }
    }


    str = temp; // assign temp to our str

}


void arrange(double &r1, double &r2)
{
    // purpose of this function is to arrange r1 and r2 such that
    // r1 = min(r1,r2) , r2 = max(r1,r2)
    // only swap if root 1 is greater than root 2
    
    if (r1 > r2)
    {
        double temp = r1;
        r1 = r2;
        r2 = temp;
    }
      
}



double newtonMethod(Cubic& p, double ini_guess)
{
    // initial guess for the newton method
    double x0 = ini_guess;

    while (true)
    {
        /* Formula : Xn+1 = Xn - f(Xn) / f'(Xn) */
        x0 = x0 - (p.evaluate(x0) / p.differentiate().evaluate(x0));

        double value = p.evaluate(x0);

        if (fabs(value) < pow(10,-8))   // error = 0.00000001
        {
            // basically anything if anything is as small as less than 10^-6 then 
            // consider it as zero
            if (fabs(x0) < pow(10,-6))  // difference = 0.000001
            {
                return 0.0;
            }

            return x0;
        }
            
    }
}

bool PowerIsOne(string equation,int index)
{
    // check if next character to variable is power operator or not
    // because if power is one we don't specify it
    // this function is used to recognise such situations
    if (equation[index + 1] != '^')
    {
        return true;
    }

    return false;
}

bool CoeffiecientIsOne(string temp)
{
    // if coefficient is one then temp must be one of these
    if (temp == "" || temp == "+" || temp == "-")
        return true;


    return false;
}

void assign_if_coefficient_is_one(string temp,Term& tmp)
{
    if (temp == "")
      tmp.coefficient(1);
    else if (temp == "-")
      tmp.coefficient(-1);
    else if (temp == "+")
      tmp.coefficient(1);
}

bool NoVariableFound(string equation, int index)
{
    bool result = false;

    while (equation[index] != '\0')
    {
        if (equation[index] == 'x')
        {
            return false;
        }
        index++;
    }

    return true;
}
