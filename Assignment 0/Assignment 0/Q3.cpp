#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;


void reverse(char str[])

{	// Initialize left and right pointers 
	fstream fout;
	fout.open("output.txt");
	int r = strlen(str) - 1;
	int l = 0;

	// Traverse string from both ends until 
	// 'l' and 'r' 
	while (l < r)
	{

		if (str[l] == 'a' || str[l] == 'e' || str[l] == 'i' || str[l] == 'o' || str[l] == 'u' ||
			str[l] == 'A' || str[l] == 'E' || str[l] == 'I' || str[l] == 'O' || str[l] == 'U')
			l++;
		else if (str[r] == 'a' || str[r] == 'e' || str[r] == 'i' || str[r] == 'o' || str[r] == 'u' ||
			str[r] == 'A' || str[r] == 'E' || str[r] == 'I' || str[r] == 'O' || str[r] == 'U')
			r--;

		else // Both str[l] and str[r] are not vowel
		{
			swap(str[l], str[r]);
			l++;
			r--;
		}
	}
	fout<<str;
}

// Driver code 
int main(int argc,char*arg[])
{
	ifstream fin;
	char red;
	char buffer[100];
	int i = 0;
	std::string b=string(arg[1]);
	std::string a="q3_"+b+".txt";

	fin.open(a);
		if (fin.is_open())
		{
			while (!fin.eof())
			{
			fin >> red;
			buffer[i++] = red;

			}
			buffer[i] = '\0';
			reverse(buffer);
			cout << buffer;
		}
		else
		{
			cout << "Error Opening file";
		}
	return 0;
}