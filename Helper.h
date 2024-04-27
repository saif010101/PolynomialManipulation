#include <iostream>

using namespace std;

double power(double base,int exp);
bool PowerIsOne(string equation,int index);
bool CoeffiecientIsOne(string temp);
void assign_if_coefficient_is_one(string temp,vector<double>&);
bool VariableIsEncountered(string equation,int index);
bool PowerIsEncountered(string equation,int index);
bool SignIsEncountered(string equation,int index);
void remove_spaces_from_string(string& str); // this function serves an important purpose


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
    if (equation[index] == '+' || equation[index] == '-' || equation[index] == '\0')
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

void assign_if_coefficient_is_one(string temp, vector<double> &coff)
{
    if (temp == "")
        coff.push_back(1);
    else if (temp == "-")
        coff.push_back(-1);
    else if (temp == "+")
        coff.push_back(1);
}
