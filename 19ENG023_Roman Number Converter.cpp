/*--------------------------------------
  Name              -   Gunaratne U.B.R.A.
  Index Number      -   19/ENG/023
  Quest Number      -   2
  Program           -   Roman Number Converter
--------------------------------------*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

/*--------------------------------------
  Function          -   To convert single
                        roman numbers 
                        to numericals
  Input             -   singleRomanNumber
  returns           -   relevant numerical value
--------------------------------------*/
int getPriorityValue(char romanNumber)
{
    switch (romanNumber)
    {
    case 'I':
    case 'i':
        return 1;
        break;
    case 'V':
    case 'v':
        return 5;
        break;
    case 'X':
    case 'x':
        return 10;
        break;
    case 'L':
    case 'l':
        return 50;
        break;
    case 'C':
    case 'c':
        return 100;
        break;
    default:
        return -1;
    }
}

/*--------------------------------------
  Function          -   To check whether the input
                        roman number has invalid 
                        characters
  Input             -   fullRomanNumber
  returns           -   true: if it is valid
                        false: if it is not valid
--------------------------------------*/
bool isValidCharacters(string romanNumber)
{
    for (int i = 0; i < romanNumber.length(); i++)
    {
        if (getPriorityValue(romanNumber[i]) == -1)
        {
            return false;
        }
    }
    return true;
}

/*--------------------------------------
  Function          -   checks for invalid repititions
                        in the roman number
  Input             -   fullRomanNumber
  returns           -   true: if it is valid
                        false: if it is not valid
--------------------------------------*/
bool isValidCharacterRepitition(string romanNumber)
{
    vector<char> occurences;
    occurences.push_back(tolower(romanNumber[0]));
    for (int i = 1; i < romanNumber.length(); i++)
    {
        if (occurences[0] == tolower(romanNumber[i]))
        {
            occurences.push_back(tolower(romanNumber[i]));
            int occurenceCount = occurences.size();
            char currentChar = occurences[0];
            if (currentChar == 'i')
            {
                if (occurenceCount > 3)
                {
                    return false;
                }
            }
            if (currentChar == 'v')
            {
                if (occurenceCount > 1)
                {
                    return false;
                }
            }
            if (currentChar == 'x')
            {
                if (occurenceCount > 3)
                {
                    return false;
                }
            }
            if (currentChar == 'l')
            {
                if (occurenceCount > 1)
                {
                    return false;
                }
            }
            if (currentChar == 'c')
            {
                if (occurenceCount > 1)
                {
                    return false;
                }
            }
        }
        else
        {
            occurences.clear();
            occurences.push_back(tolower(romanNumber[i]));
        }
    }

    return true;
}

/*--------------------------------------
  Function          -   read the file line by line
                        converts the roman numbers to 
                        numericals
  Input             -   
  returns           -   
--------------------------------------*/
void readFileAndEvaluate()
{
    fstream numbersFile;
    numbersFile.open("numbers.txt", ios::in);
    if (numbersFile.is_open())
    {
        string romanNumber;
        while (getline(numbersFile, romanNumber))
        {
            cout << romanNumber << " = ";
            if (!isValidCharacters(romanNumber))
            {
                cout << "ERROR. INVALID CHARACTER OCCURENCE FOUND" << endl;
                continue;
            }
            if (!isValidCharacterRepitition(romanNumber))
            {
                cout << "ERROR. INVALID CHARACTER REPITITION FOUND" << endl;
                continue;
            }
            int totalSoFar = 0;
            int romanNumberLength = romanNumber.length();
            for (int i = 0; i < romanNumberLength; i++)
            {
                char currentRomanNumber = romanNumber[i];
                int currentPriority = getPriorityValue(currentRomanNumber);
                if (i + 1 < romanNumberLength)
                {
                    char nextRomanNumber = romanNumber[i + 1];
                    int nextPriority = getPriorityValue(nextRomanNumber);
                    if (currentPriority >= nextPriority)
                    {
                        totalSoFar += currentPriority;
                    }
                    else
                    {
                        totalSoFar = totalSoFar - currentPriority + nextPriority;
                        i++;
                    }
                }
                else
                {
                    totalSoFar += currentPriority;
                }
            }
            cout << totalSoFar << endl;
        }
    }
}

/*--------------------------------------
  Function          -   main
--------------------------------------*/
int main()
{
    readFileAndEvaluate();
}