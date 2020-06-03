#pragma once

#include "json.hpp"

#include <stack>
#include <iostream>

#include "Common.h"
using namespace std;
class DirectoryTree {

private:
	static DirectoryTree* s_Instance;

private:
	static nlohmann::json s_Object;
	stack<string> m_PathStack;
	stack<nlohmann::json*> m_JsonStack;
	nlohmann::json* m_Current;

protected:
	DirectoryTree();
	~DirectoryTree() = default;

public:
	static void Start();
	static void PowerOff();

	static DirectoryTree* GetInstance() { return s_Instance; }

	uint AddFile(const string& file);
	bool AddDirectory(const string& directory);

	bool ChangeDirectory(const string& directory);

	vector<string> ListDirectories();

	void RemoveFile(const string& file);
	bool RemoveDirectory(const string& directory);

	string GetCurrentDirectory();

private:
	static void Flush();
	void RemoveFile(uint index) const;
};

