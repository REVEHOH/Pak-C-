/*
��pak�ļ� 
---> ��Ĵ�С   �����  
-->�õ��������-->�ļ������� 

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
		os << "�ļ�ƫ����" << other.fileOff << "�ļ���С" << other.fileSize << "�ļ�����С" << other.fileNameSize << "�ļ���" << other.fileName << endl;
		return os;
	}
}fInfo[2];
int main()
{
	fstream srcfile;
	srcfile.open("new.pak", ios::in | ios::binary);//��pak�ļ�
	if (srcfile.is_open())
	{
		cout << "�򿪳ɹ�" << endl;
	}
	int  listSize,listNum;
	srcfile.read((char*)&listSize, 4);//��ȡ��Ĵ�С
	srcfile.read((char*)&listNum, 4);//��ȡ�����
	
	//�ṹ�� ����  -->vector   ��̬����   
	for (int i = 0; i < listNum; ++i)//��ȡ�������
	{
		srcfile.read((char*)&fInfo[i].fileOff, 4);//��ȡ�ļ�ƫ����
		srcfile.read((char*)&fInfo[i].fileSize, 4);
		srcfile.read((char*)&fInfo[i].fileNameSize, 4);
		srcfile.read(fInfo[i].fileName, fInfo[i].fileNameSize);
		//fInfo[i].fileName[fInfo[i].fileNameSize] = '\0';
		//cout << fInfo[i];
	}
	//д���ļ�
	fstream file[2];
	for (int i = 0; i < 2; ++i)
	{
		file[i].open(fInfo[i].fileName, ios::out | ios::binary);//���ļ�
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