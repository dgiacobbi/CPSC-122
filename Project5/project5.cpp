/*
 Name: David Giacobbi
 Class: CPSC 122, Section 01
 Date Submitted: February 10, 2022
 Assignment: Project 5                                                                    
 Description: This project takes encrypts and decrypts 
              a file using the Affine cipher.
*/

// Preprocesor directives
#include <iostream>
#include <fstream>
using namespace std;

// Function prototypes for encryption/decryption
void keyGen(string);
char encrypt(char, int, int);
char decrypt(char, int, int, int);
void runMode(fstream& , fstream&, fstream&, int, int, int);
void fileOpen(fstream&, string, char);

// Global variables used to decryt, find mod inverses
const int CONSTANT_P = 25;
int MI[] = {0, 1, 0, 9, 0, 21, 0, 15, 0, 3, 0, 19, 0,
            0, 0, 7, 0, 23, 0, 11, 0, 5, 0, 17, 0, 25};

int main(int argc, char* argv[])
{
    // Variable declaration for files and command line input
    fstream keyFile, inFile, outFile;
    int userMode, alpha, beta;

    // Takes user string and turns into int
    userMode = atoi(argv[1]);

    // If-statement regulates opening files depending on command line input
    if (userMode == 0)
    {
        // Opens keyFile and generates alpha and beta key
        fileOpen(keyFile, argv[2], 'w');
        keyGen(argv[2]);   
    }
    else
    {
        // Opens files for encryption or decryption
        fileOpen(keyFile, argv[2], 'r');
        fileOpen(inFile, argv[3], 'r');
        fileOpen(outFile, argv[4], 'w');

        // Stores values from key file in alpha and beta
        keyFile >> alpha;
        keyFile >> beta;

        // Function determines whether to encrypt or decrypt file
        runMode(keyFile, inFile, outFile, userMode, alpha, beta);
    }

    keyFile.close();
    inFile.close();
    outFile.close();

}

/*
Description: Randomly generates and stores alpha and beta values.
The alpha value is randomly drawn from the the set: 
{1,3,5,7,9,11,15,17,19,21,23,25}
The beta value is randomly drawn from the range: [1..25]  
Input: name of file that stores the keys
Output: alpha and beta values on subsequent lines of keyFile
*/
void keyGen(string name)
{
    // Variable declaration to randomly grab alpha and beta values for keyFile
    int alpha[] = {1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23, 25};
    int alphaIndex, beta;
    fstream keyFile;

    fileOpen(keyFile, name, 'w');

    // Assigns beta random int from 1-25, assigns alpha random index 0-11
    srand((unsigned)time(0));
    alphaIndex = (rand() % 11);
    beta = (rand() % 25) + 1;

    // Writes to keyFile the alpha value corresponding to random index and 
    // random beta integer generated 1-25
    keyFile << alpha[alphaIndex] << endl;
    keyFile << beta << endl;
}

/*
Description: Encrypts an upper case alphabetic character 
             using the affine cipher
Input: upper case alphabetic character, valid alpha and beta values
Returns: encrypted version of ch
*/
char encrypt(char ch, int alpha, int beta)
{
    // Turns character into positional value and performs Affine encrypt
    int pos = ch - 65;
    pos = ((alpha * pos) + beta) % 26;
    ch = pos + 65;

    return ch;
}

/*
Description: Decrypts an upper case alphabetic character 
             using the affine cipher
Input: upper case alphabetic character, valid alpha and beta values. 
       Dictionary of multiplicative inverse values mod 26
Returns: decrypted version of input character
*/
char decrypt(char ch, int alpha, int beta)
{
    // Turns character into positional value and performs Affine decrypt
    int pos = ch - 'A';
    pos = ((MI[alpha] * pos) - (MI[alpha] * beta) + (CONSTANT_P * 26)) % 26;
    ch = pos + 'A';

    return ch;
}

/*
Description: invokes fileOpen on all files.  Closes all files.  Reads 
             key file. Reads the input file and either invokes encrypt
             or decrypt. If the action is encrypt, alphabetic characters
             are transformed to upper case.   Writes the result of encrypt
             or decrypt to the output file. 
Input: names of key file, input file and output file. mode value of 1 or 2
Output: writes to the output file
*/
void runMode(fstream& keyFile, fstream& inFile, fstream& outFile, int mode, int alpha, int beta)
{
    // Variable declaration
    char ch;

    // Encryption sequence
    if (mode == 1)
    {
        // While loop encrypts characters one by one using function 
        // only if they are alphabetical 
        while (inFile.peek() != EOF)
        {
            ch = inFile.get();
            if (isalpha(ch))
            {
                // Changes character to uppercase ASCII values before encrypt
                ch = toupper(ch);
                ch = encrypt(ch, alpha, beta);
            }
            outFile.put(ch);
        }
    }
    // Decryption sequence (same as encryption but with decrypt function)
    else if (mode == 2)
    {
        keyFile >> alpha;
        keyFile >> beta;

        while (inFile.peek() != EOF)
        {
            ch = inFile.get();
            if (isalpha(ch))
                ch = decrypt(ch, alpha, beta);
            outFile.put(ch);
        }
    }
    // Error checking for mode inputs not 0-2
    else
    {
        cout << "Please enter a valid mode of operation choice." << endl;
        exit(EXIT_FAILURE);
    }
}

/*
Description: function opens a file
Input: file stream object reference, name of the file, mode of open
Output: input file name is opened. 
*/
void fileOpen(fstream& file, string name, char mode)
{
    string fileType;

    if (mode == 'r')
        fileType = "input";
    if (mode == 'w')
        fileType = "output";

    if (mode == 'r')
        file.open(name, ios::in);  //available thorugh fstream
    if (mode == 'w')
        file.open(name, ios::out);  //available through fstream;

    if (file.fail()) //error condition 
    {
        cout << "Error opening " << fileType << " file" << endl; 
        exit(EXIT_FAILURE);
    }
}