/*
文件打包和解包
pak  打包文件 --->游戏资源  软件文档 资源

打包和解包
1.txt  2.txt 
表头信息     表大小  +表的个数(文件的个数)					目录 
表1 文件偏移量    文件大小   文件名大小	文件名			小目录
表2 文件偏移量    文件大小   文件名大小	文件名
文件1																									正文
文件2

*/
#include<iostream>
#include<fstream>
using namespace std;
char fileName[][10] = { "1.txt", "2.txt" };
struct fileList
{
	streamoff fileOff;//int   //streamoff  类型  偏移量   int
	streamoff fileSize;
	streamoff fileNameSize;
	char *filename;
}file[2];
int main()
{
	int listNum = 2, listSize = 0;//表头
	fstream srcFile[3];
	for (int i = 0; i < 2; ++i)
	{
		file[i].filename = fileName[i];//文件名
		file[i].fileNameSize = strlen(fileName[i])+1;//求文件名长度
		srcFile[i].open(fileName[i], ios::in | ios::binary);//打开文件
		srcFile[i].seekp(0, ios::end);//先指向文件末尾  //
		file[i].fileSize=srcFile[i].tellp();//得到文件大小
		
		listSize += 4 + 4 + 4 + file[i].fileNameSize;//得到文件名大小+文件偏移量+文件长度+文件名    计算表的大小(占用多少个字节)

		//listSize += sizeof(file[i].fileOff) + sizeof(file[i].fileSize) + sizeof(file[i].fileNameSize) + strlen(file[i].filename);
	}
	///开始计算偏移量
	for (int i = 0; i < 2; ++i)
	{
		if (i == 0)
		{
			file[i].fileOff= 8 + listSize;//sizeof(listSize)+sizeof(listNum)
		//第一个文件的偏移量   表头+表的总大小
		}
		else
		{
			file[i].fileOff = file[i - 1].fileOff + file[i - 1].fileSize;
		}
	}


	//写入pak文件
	srcFile[2].open("new.pak", ios::out | ios::binary);//创建文件
	srcFile[2].write((char*)&listSize, sizeof(int));//写入表大小
	srcFile[2].write((char*)&listNum, sizeof(int));//写入表的个数
	for (int i = 0; i < 2; ++i)//循环写入表
	{
		srcFile[2].write((char*)&file[i].fileOff, sizeof(int));//文件偏移
		srcFile[2].write((char*)&file[i].fileSize, sizeof(int));//文件大小
		srcFile[2].write((char*)&file[i].fileNameSize, sizeof(int));//文件名长度
		srcFile[2].write(file[i].filename, file[i].fileNameSize);//文件名
	}
	//循环写入文件
	for (int i = 0; i < 2; ++i)
	{
		srcFile[i].seekp(0, ios::beg);//文件指针移回文件开头
		//二进制文件读取写入
		//read write  //文件大小
		for (streamoff j= 0; j< file[i].fileSize; ++j)
		{
			//一个字节一个字节写入  get 和put
			srcFile[2].put(srcFile[i].get());//写入文件
		}
		//文本文件和二进制文件的区别    文本文件内容中不存在EOF
		srcFile[i].close();
	}
	srcFile[2].close();
	cin.get();
	return 0;
}