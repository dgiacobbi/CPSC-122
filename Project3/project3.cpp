/*
 Name: David Giacobbi
 Class: CPSC 122, Section 01
 Date Submitted: January 27, 2022
 Assignment: Project 2                                                                    
 Description: This program takes in two c-string digits and converts
              them to integers. It then multiplies them and writes the
              product to the file from the command line.
*/

//Preprocessor directives for file I/O
#include <iostream>
#include <fstream>
using namespace std;

//Function prototype for c-string converter and error check
int atoiMy(char*);
void error(int);

int main(int argc, char* argv[])
{
    //Error checking for two many command line arguments
    if (argc != 4)
        error(1);
    
    //Error checking for negative integers
    if (argv[1][0] == '-' || argv[2][0] == '-')
        error(2);
    
    //Declare and open file from command line
    ofstream fout;
    fout.open(argv[3]);
    
    //Writing product to file
    fout << atoiMy(argv[1]) * atoiMy(argv[2]) << endl;

    //Close file
    fout.close();
}

/*
Description: Turns a digit stored c-string into an int
Input: char str, a command line c-string that contains
       a digit
Return: the corresponding integer of the same value as
        the digit string inputed
*/
int atoiMy(char str[])
{
    //Running total for converted integer
    int intArg = 0;

    for (int i = 0; str[i] != '\0'; i++)
    {
        //Converts the ASCII value of character to its actual integer value
        int add = int(str[i]) - 48;

        //Converts c-string to integer by every tens place,
        //starting left and moving right placing following digit
        //to the right until string reaches null-terminator
        intArg = (intArg * 10) + add;
    }

    return intArg;
}
    
/*
Description: Error checking function that shuts down program
             if input is not acceptable for program
Input: int, key, to direct error function to correct message
Return: N/A
*/
void error(int key)
{
    if (key == 1)
    {
        cout << "Please make sure to enter only two positive integers and one output file!" << endl;
        exit(EXIT_FAILURE);
    }

    if (key == 2)
    {
        cout << "Only input positive integers for multiplication." << endl;
        exit(EXIT_FAILURE);
    }

}
