/*
 Name: David Giacobbi
 Class: CPSC 122, Section 01
 Date Submitted: February 17, 2022
 Assignment: Project 5                                                                    
 Description: This project takes encrypts and decrypts 
              a file using the transposition cipher.
*/

// Preprocessor directives for file work
#include <iostream>
#include <fstream>
using namespace std;

// Function prototypes
void keyGen (string);
void fileControl (string, string, string, int);
char transform(char, int[][2]);
void fileOpen(fstream&, string, char);
bool sink(int[][2], int);
int mysterySort(int[][2], int);

int main(int argc, char* argv[])
{
    // Variable declaration for comman line input
    int userMode;

    // Takes user string and turns into int
    userMode = atoi(argv[1]);

    // If-statement regulates opening files depending on command line input
    if (userMode == 0)
    {
        // Generates transposition array in keyFile
        keyGen(argv[2]);   
    }
    else
    {
        // Function determines whether to encrypt or decrypt file
        fileControl(argv[2], argv[3], argv[4], userMode);
    }
}

/*
Description: Opens key file for writing.  Generates and stores encrypt
             and decrypt keys in the key file.    
Input: name of the file in which to store generated keys
Output: file holds generated encryption and decryption keys 
*/
void keyGen(string name)
{
    // Declare variables to write random key to keyFile
    fstream keyFile;
    int key[26];
    bool validate[26] = {false};
    int k, pos = 0;
    
    fileOpen(keyFile, name, 'w');

    // Generate new random numbers every time it is called
    srand((unsigned)time(NULL));

    // For loop gives random number 0-25 for each key array
    // element; does not repeat using bool array to check
    while(pos < 26)
    {
        while(true)
        {
            k = rand() % 26;

            // Checks to see if random number has been used
            // in the key array
            if(validate[k] == false)
            {
                key[pos] = k;
                validate[k] = true;
                keyFile << key[pos] << endl;

                pos++;
            }
            break;
        }
    }
}
	
/*
Description: Processes files, invokes function to encrypt/decrypt characters
Input: Command line arguments of each file name in string, mode from command line
Output: writes a character to the output file
*/
void fileControl(string fileKey, string fileIn, string fileOut, int mode)
{
    // Variable declaration
    fstream keyFile, inFile, outFile;
    char ch;
    int encryptKey[26][2], decryptKey[26][2];

    // Opens files for encryption or decryption
    fileOpen(keyFile, fileKey, 'r');
    fileOpen(inFile, fileIn, 'r');
    fileOpen(outFile, fileOut, 'w');

    // Constructs encryption 2-D array for transform function
    for (int i = 0; i < 26; i++)
    {
        int key;
        encryptKey[i][0] = i;

        keyFile >> key;
        encryptKey[i][1] = key;        
    }

    keyFile.close();

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
                ch = transform(ch, encryptKey);
            }
            outFile.put(ch);
        }
        
        inFile.close();
        outFile.close();
    }
    // Decryption sequence
    else if (mode == 2)
    {
        // Perform sort function to encryptKey
        mysterySort(encryptKey, 26);

        // Constructs decryption 2-D array from sorted encryption 2-D array
        for (int i = 0; i < 26; i++)
        {
            decryptKey[i][0] = i;
            decryptKey[i][1] = encryptKey[i][0];
        }

        // For loop decrypts by character until end of file
        while (inFile.peek() != EOF)
        {
            ch = inFile.get();
            if (isalpha(ch))
                ch = transform(ch, decryptKey);
            outFile.put(ch);
        }

        inFile.close();
        outFile.close();
    }
    // Error checking for mode inputs not 0-2
    else
    {
        cout << "Please enter a valid mode of operation choice." << endl;
        exit(EXIT_FAILURE);
    }
}

/*
Description: Encrypts/Decrypts an upper case alphabetic character using the 
             transposition cipher. Operation depends on whether it is sent 
             the encrypt or decrypt key
Input: upper case alphabetic character, encryption or decryption array
Returns: encrypted or decrypted  version of ch
*/
char transform(char ch, int encDec[][2])
{
    int pos = ch - 65;
    pos = encDec[pos][1];
    ch = pos + 65;

    return ch;
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

/*
Description: Algorithm to sort the key array. Invoked within keyGen
Input: 26 position 2-D array, K, of integers with columns 0 and 1
Output: An array k, where col 0 is the sorted version of col 1. 
        The original column 1 is taken along for the ride.
*/
bool sink(int table[][2], int bottom)
{
    bool shift = false;
    int temp, cur = 0;

    while (cur < bottom - 1)
    {
        if (table[cur][1] > table[cur + 1][1])
        {
            shift = true;

            temp = table[cur][0];
            table[cur][0] = table[cur + 1][0];
            table[cur + 1][0] = temp;

            temp = table[cur][1];
            table[cur][1] = table[cur + 1][1];
            table[cur + 1][1] = temp;
        }
        cur++;
    }
    return shift;
}

int mysterySort(int table[][2], int len)
{
    int bottom = len;
    bool shift = true;

    while (shift)
    {
        shift = sink(table, bottom);
        bottom--;
    }

    return table[len][1];
}