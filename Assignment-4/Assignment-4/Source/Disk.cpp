#include "Disk.h"

#include "VirtualFileSystem.h"
#include "FAT.h"
#include "DirectoryTree.h"
using namespace std;

Disk* Disk::s_Instance = nullptr;
FILE* Disk::s_FileStream = nullptr;
uint Disk::s_FreeBlocks = 0;
uint Disk::s_AllocatedBlocks = 0;;

void Disk::Start() {

	s_FileStream = fopen(VFS::GetFileName().c_str(), "r");

	if (!s_FileStream) {

		s_FileStream = fopen(VFS::GetFileName().c_str(), "wb+");

		uint blockSize = VFS::GetBlockSize();
		char* buffer = new char[blockSize];

		memset(buffer, 0, blockSize * sizeof(char));

		s_FreeBlocks = FAT::GetEntries();

		fwrite((const void*)(&s_FreeBlocks), sizeof(uint), 1, s_FileStream);
		fwrite((const void*)(&s_AllocatedBlocks), sizeof(uint), 1, s_FileStream);

		for (uint i = 0; i < FAT::GetEntries(); i++)
			fwrite((const void*)buffer, blockSize * sizeof(char), 1, s_FileStream);

		delete[] buffer;

		fclose(s_FileStream);
	}

	else
	{



	}

	fclose(s_FileStream);
	s_FileStream = fopen(VFS::GetFileName().c_str(), "rb+");

	fread((void*)(&s_FreeBlocks), sizeof(uint), 1, s_FileStream);
	fread((void*)(&s_AllocatedBlocks), sizeof(uint), 1, s_FileStream);

	s_Instance = new Disk();
}

void Disk::PowerOff() {

	fseek(s_FileStream, 0, SEEK_SET);
	fwrite((const void*)(&s_FreeBlocks), sizeof(uint), 1, s_FileStream);
	fwrite((const void*)(&s_AllocatedBlocks), sizeof(uint), 1, s_FileStream);
	
	fclose(s_FileStream);
	delete s_Instance;
}

bool Disk::Import(const string& filename) {
	
	FILE* file;

	string path = VFS::GetPath();

	path += filename;

	file = fopen(path.c_str(), "r");

	if (!file) {

		cout << "Cant Find File: " << path << endl;
		fclose(file);
		return false;
	}
	
	else
	{



	}

	fseek(file, 0, SEEK_END);

	int length = ftell(file);

	fseek(file, 0, SEEK_SET);

	uint blockSize = VFS::GetBlockSize();

	if (length > blockSize * s_FreeBlocks) {

		cout << "File Is Bigger Than Disk!" << endl;
		return false;
	}
	else
	{



	}
				
	uint blocks = length / blockSize;

	if ((length % blockSize) != 0)
		blocks += 1;
	
	else
	{



	}

	vector<uint> blockIDs;

	uint startingIndex = DirectoryTree::GetInstance()->AddFile(filename);

	if (startingIndex == (uint)-1)
		return false;

	else
	{



	}

	blockIDs.push_back(startingIndex);
	int i=0;
	while (i < blocks) 
	{

		uint index = FAT::GetInstance()->Allocate();
		FAT::GetInstance()->SetBlock(blockIDs[i - 1], Block(Block::Status::Allocated, index));
		blockIDs.push_back(index);
		i++;
	}

	char* buffer = new char[blockSize];

	for (auto i : blockIDs) {

		fread(buffer, blockSize * sizeof(char), 1, file);

		fseek(s_FileStream, (i * blockSize * sizeof(char)) + 2 * sizeof(uint), SEEK_SET);
		fwrite((void*)buffer, blockSize * sizeof(char), 1, s_FileStream);
		fseek(s_FileStream, 0, SEEK_SET);
	}

	delete[] buffer;

	s_AllocatedBlocks = blockIDs.size();
	s_FreeBlocks -= s_AllocatedBlocks;
	return true;
}

void Disk::CalculateStatus(uint count) {

	s_AllocatedBlocks -= count;
	s_FreeBlocks += count;
}

void Disk::Status() {

	cout << endl << "Block Size(KB): " << (float) VFS::GetBlockSize() / 1024 << endl;
	cout << "Free Blocks: " << s_FreeBlocks << endl;
	cout << "Allocated Blocks: " << s_AllocatedBlocks << endl;
	cout << "Total Space(KB): " << (float) (FAT::GetEntries() * VFS::GetBlockSize()) / 1024 << endl;
	cout << "Free Space(KB): " << (float) (s_FreeBlocks * VFS::GetBlockSize() / 1024) << endl;
	cout << "Allocated Space(KB): " << (float) (s_AllocatedBlocks * VFS::GetBlockSize()) / 1024 << endl;
	cout << endl << endl;
}
