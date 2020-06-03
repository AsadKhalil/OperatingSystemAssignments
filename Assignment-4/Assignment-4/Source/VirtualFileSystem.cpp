#include "VirtualFileSystem.h"

#include <fstream>
#include <iostream>

#include "FAT.h"
#include "Disk.h"
#include "DirectoryTree.h"
using namespace std;

VFS* VFS::s_Instance = nullptr;
string VFS::s_Name;
string VFS::s_Path;
uint VFS::s_BlockSize = 0;


//it will start the virtual file system of block siz eu have given and name of the disk and
//the import the path....then this will make json directory structre
void VFS::Start() {

	ifstream fin("Output.txt");

	if (fin) {
	
		fin >> s_BlockSize;
		fin >> s_Name;
		fin >> s_Path;
	}
	else {
		
		ofstream fout("Output.txt");

		cout << "Enter Size Of Block(Bytes Format)=  ";
		cin >> s_BlockSize;
		cout << "Enter Name of Disk = ";
		cin >> s_Name;
		cout << "Enter Import Path= ";
		cin >> s_Path;
		cin.ignore(1);
		fout << s_BlockSize << endl;
		fout << s_Name << endl;
		fout << s_Path << endl;

		fout.close();
	}

	fin.close();

	FAT::Start();
	DirectoryTree::Start();
	Disk::Start();

	s_Instance = new VFS();
}

//this function basically remove the directory entered by the
//user from your json structure and update the tree structure of json
void VFS::RemoveDirectory(const string& directory) {

	if (!DirectoryTree::GetInstance()->RemoveDirectory(directory))
	{
		cout << endl << directory << " ------Not Found !!!-------" << endl << endl;
	}
	else
	{


	}

}

//it it will power off and shutdown the system and delete the instance because you hav shutdwon you virtual system 
void VFS::PowerOff() {

	Disk::PowerOff();
	DirectoryTree::PowerOff();
	FAT::PowerOff();

	delete s_Instance;
}

//it will basically make directory in the root in which u are currently present in VFS
void VFS::MakeDirectory(const string& directory) {

	if (!DirectoryTree::GetInstance()->AddDirectory(directory))
	{
		cout << endl << directory << "------------ Already Exists!------------" << endl << endl;
	}
		else
	{


	}

}

//it will basically chamge the current directory to the required Directory
void VFS::ChangeDirectory(const string& directory) {

	if (!DirectoryTree::GetInstance()->ChangeDirectory(directory))	
	{
		cout << endl << directory << "-------------- Not Found! ---------------" << endl << endl;	
	}
		else
	{


	}

}

//it will basically import the file from the import and allocate the block which it needed
void VFS::ImportFile(const string& filename) {

	if (!Disk::GetInstance()->Import(filename))
	{
		cout << endl << "------File Cannot be import() = " << filename << endl << endl;
	}
		else
	{


	}


}
//it will current working directory
string VFS::GetCurrentDirectory() {

	return DirectoryTree::GetInstance()->GetCurrentDirectory();
}

//return status of the disk how many blocks are allocated or not
void VFS::DiskStatus() {

	Disk::GetInstance()->Status();
}

//it it print the List of all directories which we add in our json tree
void VFS::ListDirectory() {

	auto ans = DirectoryTree::GetInstance()->ListDirectories();

	cout << endl;
	int i=0;
	 while(i < ans.size())
	{
		cout << "     " << ans[i] << "   ";
		i++;
	}
	cout << endl<< endl<< endl;
}

























