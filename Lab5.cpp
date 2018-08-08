/*****************************************************************************************
Project Name: Lab 5
Name: Kristopher Lowell
Date Completed: 8/8/2018
Purpose: To accept a sentence from user, and reformat it into a more proper sentence. 
Also, to find the minimum amount of steps it would take to make the first and second word
the same.
*****************************************************************************************/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int min(int x, int y, int z);					// Returns the minimum value of three integers
int edit_distance(string str1, string str2);	// Returns the minimum amount of steps to make one string into another

int main(int argc, char *argv[])
{
	vector <string> sentence;			// Using vector of strings for dynamic memory
	string word;

	cout << "Enter a sentence:" << endl;	// Prompting user for a sentence
	
	while (cin.peek() != '\n')			// Read the line
	{
		cin >> word;				// Taking advantage that cin stops at whitespace.
		sentence.push_back(word);
	}

	cout << endl <<  "The difference between the first and second word is: " << edit_distance(sentence[0], sentence[1]) << endl;

	for (unsigned i = 0; i < sentence.size(); i++)			// Turning every character in sentence to lower case.
		for (unsigned j = 0; j < sentence[i].size(); j++)
			sentence[i][j] = tolower(sentence[i][j]);

	sentence[0][0] = toupper(sentence[0][0]);			// Capitalizing the first letter of the first word

	cout << endl;

	for (unsigned i = 0; i < sentence.size(); i++)		// Since only non-whitespace characters are stored in strings, we can turn it into
		cout << sentence[i] << " ";						// a proper sentence by just printing the individual strings with a space after each one.

	sentence.clear();			// Clearing out the vector for good measure
	
	cout << endl;

	return 0;
}

int min(int x, int y, int z)
{
	if (x <= y && x <= z)			// In case x is the lowest
		return x;
	else if (y <= x && y <= z)		// In case y is the lowest
		return y;
	else							// In case z is the lowest
		return z;
}

int edit_distance(string str1, string str2)
{
	int **arr = new (nothrow) int*[str1.size() + 1];	// Creating a multidimensional array to store results
	
	for (unsigned i = 0; i < str1.size() + 1; i++)
		arr[i] = new (nothrow) int[str2.size() + 1];

	int result;			// Final result variable since array will have to be deleted

	for (unsigned i = 0; i <= str1.size(); i++)		// Filling array in bottom-up manner
	{
		for (unsigned j = 0; j <= str2.size(); j++)
		{
			if (i == 0)				// In case of the first string being empty, the only option is to fill it with the second string
				arr[i][j] = j;
			else if (j == 0)		// In case of the second string being empty, the only option is to fill it with the first string
				arr[i][j] = i;
			else if (str1[i - 1] == str2[j - 1])	// If the last characters are the same, then ignore it and check the rest of the strings
				arr[i][j] = arr[i - 1][j - 1];
			else									// If the last character is different, then consider all the posssibilities and find the minimum of said possibilities.
				arr[i][j] = 1 + min(arr[i][j - 1], arr[i - 1][j], arr[i - 1][j - 1]);	// min(insert, remove, replace)
		}
	}

	result = arr[str1.size()][str2.size()];	// Final result will be stored in the last cell of the table

	for (unsigned i = 0; i < str1.size() + 1; i++)	// Clearing the array
		delete [] arr[i];

	delete[] arr;

	return result;
}