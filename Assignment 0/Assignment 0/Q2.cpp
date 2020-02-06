#include<iostream>
#include<fstream>
#include<cstring>
#include<vector>
using namespace std;
// Driver code 
class Info
{
public:	
	char rollno[20];
	char name[20];
	char email[20];

	Info()
	{
		rollno[0] ='\0' ;
		name[0] = '\0';
		email[0] = '\0';
	}
	void print()
	{
		cout << rollno<<"\t" << name<<"\t" << email<<endl;
	}
	Info &operator=(const Info &rhs)
	{
	if (this !=&rhs)
	{
		for (int i = 0; i < 20; i++)
		{
			rollno[i] = rhs.rollno[i];
		}
		for (int i = 0; i < 20; i++)
		{
			name[i] = rhs.name[i];
		}	
		for (int i = 0; i < 20; i++)
		{
			email[i] = rhs.email[i];
		}
	
	}
	return *this;
	}
};
int main()
{
	ifstream fin;
	ofstream fout;
	fout.open("output.txt");
	int i = 0;
	Info *details=new Info[100];
	int opt = 0;
	cout << "Press 1 to enter details:\n";
	cout << "Press 2 to delete details:\n";
	cout << "Press 3 to read details:\n";
cout<<"Press -1 to exit\n";
	cin >> opt;
		while (opt != -1)
		{

			if (opt == 1)
			{
				Info oneUnit;
				cout << "Enter Roll no:  ";
				cin.ignore();
				cin.getline(oneUnit.rollno, 20);
				cout << "Enter Name :  ";
				cin.getline(oneUnit.name, 20);
				cout << "Enter Email:  ";
				cin.getline(oneUnit.email, 20);

				details[i++] = oneUnit;
				//fout.open("output.txt", std::ofstream::out | std::ofstream::trunc);
				//fout.clear();
					fout << details[i].rollno << "\t" << details[i].name << "\t" << details[i].email;
					fout << endl;
					cout << details[i].rollno << "\t" << details[i].name << "\t" << details[i].email << endl;

				
			}
			if (opt == 2)
			{
				int m = 0, n = 0;
				bool flag = false;
				cout << "Enter Roll no:  ";
				char temp[20];
				cin.ignore();
				cin.getline(temp, 20);
				for (int k = 0; k < i; k++)
				{
					for (int l = 0; l < strlen(temp); l++)
					{
						if (details[k].rollno[m] == temp[n])
						{
							flag = true;
							m++; n++;
						}
						else
							flag = false;

					}
					if (flag)
					{

						details[k]=details[k+1];
						i--;
					}
					m = 0; n = 0;
					fout.open("output.txt", std::ofstream::out | std::ofstream::trunc);
//					fout.clear();

					for (int p = 0; p < i; p++)
					{
						fout << details[p].rollno << "\t" << details[p].name << "\t" << details[p].email;
						fout << endl;

					}
				}
				for (int j = 0; j < i; j++)
				{
					details[j].print();
					fout.open("output.txt", std::ofstream::out | std::ofstream::trunc);
					//fout.clear();

					for (int p = 0; p < i; p++)
					{
						fout << details[p].rollno << "\t" << details[p].name << "\t" << details[p].email;
						fout << endl;

					}
				}

			}
			
			if (opt == 3)
			{
				cout << "Enter Roll no:  ";
				char temp[20];
				int m = 0, n = 0;
				bool flag = false;
				cin.ignore();
				cin.getline(temp, 20);
				for (int k = 0; k < i; k++)
				{
					for (int l = 0; l < strlen(temp); l++)
					{
						if (details[k].rollno[m] == temp[n])
						{
							flag = true;
							m++; n++;
						}
						else
							flag = false;
					}
					if (flag)
					{
						details[k].print();
						break;
					}
					m = 0; n = 0;
				}

			}

			cout << "Press 1 to enter details:\n";
			cout << "Press 2 to delete details:\n";
			cout << "Press 3 to read details:\n";
			cout<<"Press -1 to exit\n";
			cin >> opt;
		}
}