/*
打开pak文件 
---> 表的大小   表个数  
-->得到表的内容-->文件的内容 

*/
#include<iostream>
#include<fstream>
using namespace std;
struct fileInfo
{
	int fileOff;
	int fileSize;
	int fileNameSize;
	char fileName[20];
	friend ostream&operator<<(ostream&os, fileInfo&other)
	{
		os << "文件偏移量" << other.fileOff << "文件大小" << other.fileSize << "文件名大小" << other.fileNameSize << "文件名" << other.fileName << endl;
		return os;
	}
}fInfo[2];
int main()
{
	fstream srcfile;
	srcfile.open("new.pak", ios::in | ios::binary);//打开pak文件
	if (srcfile.is_open())
	{
		cout << "打开成功" << endl;
	}
	int  listSize,listNum;
	srcfile.read((char*)&listSize, 4);//读取表的大小
	srcfile.read((char*)&listNum, 4);//读取表个数
	
	//结构体 数组  -->vector   动态数组   
	for (int i = 0; i < listNum; ++i)//读取表的内容
	{
		srcfile.read((char*)&fInfo[i].fileOff, 4);//读取文件偏移量
		srcfile.read((char*)&fInfo[i].fileSize, 4);
		srcfile.read((char*)&fInfo[i].fileNameSize, 4);
		srcfile.read(fInfo[i].fileName, fInfo[i].fileNameSize);
		//fInfo[i].fileName[fInfo[i].fileNameSize] = '\0';
		//cout << fInfo[i];
	}
	//写入文件
	fstream file[2];
	for (int i = 0; i < 2; ++i)
	{
		file[i].open(fInfo[i].fileName, ios::out | ios::binary);//打开文件
		for (streamoff j = 0; j < fInfo[i].fileSize; ++j)
		{
			file[i].put(srcfile.get());
		}
		file[i].close();
	}
	srcfile.close();
	cin.get();
	return 0;
}