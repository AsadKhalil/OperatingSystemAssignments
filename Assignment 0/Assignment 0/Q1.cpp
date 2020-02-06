#include<iostream>
#include<cstring>
#include<fstream>
using namespace std;
int main(int argc,char*arg[])
{

ifstream fin;
char fiter;
int count=0;
	std::string b=string(arg[1]);
	std::string a="q1_"+b+".txt";

	fin.open(a);
	if(fin.is_open())
	{
		while (fin>>fiter) {
			//fin >> fiter;
			if (fiter >= '0' && fiter <= '9')
				count++;
		}
	}
	else
	  cout<<"Error Opening file" ;
	
	cout<<"Number of digits in file: "<<count;
}
