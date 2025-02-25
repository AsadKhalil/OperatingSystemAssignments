#pragma once

#include "DirectoryTree.h"
#include "Common.h"
using namespace std;
class VFS
{

private:
	static VFS* s_Instance;

private:
	static string s_Name;
	static string s_Path;
	static uint s_BlockSize;

protected:
	VFS() = default;
	~VFS() = default;

public:

	//start your virtual file system
	static void Start();
	//power off and shut down your virtual file system
	static void PowerOff();
	//it will show you the list of all directoreis and files of virtual file system
	void ListDirectory();
	//it will remove the driectory from File system which will you pass by String If it is Present
	void RemoveDirectory(const string& directory);
	//it will make a directory in the root system
	void MakeDirectory(const string& directory);
	//it will change the root directory of your virtual file system which will you pass him as String If it is Present
	void ChangeDirectory(const string& directory);
	//it will return us cureent Directory
	string GetCurrentDirectory();
	//import a file for our virtual hard drive
	void ImportFile(const string& filename);
	//it will return what is your disk status how many memey block is allocated
	void DiskStatus();
	//it will return the size of each blovk which we pass at the runtime
	static uint GetBlockSize() { return s_BlockSize; }
	//it will return the path of file
	static const string& GetPath() { return s_Path; }
	//it will return the name of the file
	static const string& GetFileName() { return s_Name; }
	//it is basically the single instance of VFS
	static VFS* GetInstance() { return s_Instance; }
};
