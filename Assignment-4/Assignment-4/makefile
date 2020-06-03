all:
	g++ Source/Block.cpp -c -o Bin/Block.o
	g++ Source/DirectoryTree.cpp -c -o Bin/DirectoryTree.o
	g++ Source/Disk.cpp -c -o Bin/Disk.o
	g++ Source/FAT.cpp -c -o Bin/FAT.o
	g++ Source/VirtualFileSystem.cpp -c -o Bin/VirtualFileSystem.o
	g++ Source/Main.cpp -c -o Bin/Main.o
	g++ Bin/Main.o Bin/DirectoryTree.o Bin/Disk.o Bin/FAT.o Bin/VirtualFileSystem.o Bin/Block.o -o a.out

run:
	./a.out

clean:
	rm VCB/FAT.bin 
	rm VCB/DirectoryTree.json
	rm config.txt
	rm disk
