/*
�ļ�����ͽ��
pak  ����ļ� --->��Ϸ��Դ  ����ĵ� ��Դ

����ͽ��
1.txt  2.txt 
��ͷ��Ϣ     ���С  +��ĸ���(�ļ��ĸ���)					Ŀ¼ 
��1 �ļ�ƫ����    �ļ���С   �ļ�����С	�ļ���			СĿ¼
��2 �ļ�ƫ����    �ļ���С   �ļ�����С	�ļ���
�ļ�1																									����
�ļ�2

*/
#include<iostream>
#include<fstream>
using namespace std;
char fileName[][10] = { "1.txt", "2.txt" };
struct fileList
{
	streamoff fileOff;//int   //streamoff  ����  ƫ����   int
	streamoff fileSize;
	streamoff fileNameSize;
	char *filename;
}file[2];
int main()
{
	int listNum = 2, listSize = 0;//��ͷ
	fstream srcFile[3];
	for (int i = 0; i < 2; ++i)
	{
		file[i].filename = fileName[i];//�ļ���
		file[i].fileNameSize = strlen(fileName[i])+1;//���ļ�������
		srcFile[i].open(fileName[i], ios::in | ios::binary);//���ļ�
		srcFile[i].seekp(0, ios::end);//��ָ���ļ�ĩβ  //
		file[i].fileSize=srcFile[i].tellp();//�õ��ļ���С
		
		listSize += 4 + 4 + 4 + file[i].fileNameSize;//�õ��ļ�����С+�ļ�ƫ����+�ļ�����+�ļ���    �����Ĵ�С(ռ�ö��ٸ��ֽ�)

		//listSize += sizeof(file[i].fileOff) + sizeof(file[i].fileSize) + sizeof(file[i].fileNameSize) + strlen(file[i].filename);
	}
	///��ʼ����ƫ����
	for (int i = 0; i < 2; ++i)
	{
		if (i == 0)
		{
			file[i].fileOff= 8 + listSize;//sizeof(listSize)+sizeof(listNum)
		//��һ���ļ���ƫ����   ��ͷ+����ܴ�С
		}
		else
		{
			file[i].fileOff = file[i - 1].fileOff + file[i - 1].fileSize;
		}
	}


	//д��pak�ļ�
	srcFile[2].open("new.pak", ios::out | ios::binary);//�����ļ�
	srcFile[2].write((char*)&listSize, sizeof(int));//д����С
	srcFile[2].write((char*)&listNum, sizeof(int));//д���ĸ���
	for (int i = 0; i < 2; ++i)//ѭ��д���
	{
		srcFile[2].write((char*)&file[i].fileOff, sizeof(int));//�ļ�ƫ��
		srcFile[2].write((char*)&file[i].fileSize, sizeof(int));//�ļ���С
		srcFile[2].write((char*)&file[i].fileNameSize, sizeof(int));//�ļ�������
		srcFile[2].write(file[i].filename, file[i].fileNameSize);//�ļ���
	}
	//ѭ��д���ļ�
	for (int i = 0; i < 2; ++i)
	{
		srcFile[i].seekp(0, ios::beg);//�ļ�ָ���ƻ��ļ���ͷ
		//�������ļ���ȡд��
		//read write  //�ļ���С
		for (streamoff j= 0; j< file[i].fileSize; ++j)
		{
			//һ���ֽ�һ���ֽ�д��  get ��put
			srcFile[2].put(srcFile[i].get());//д���ļ�
		}
		//�ı��ļ��Ͷ������ļ�������    �ı��ļ������в�����EOF
		srcFile[i].close();
	}
	srcFile[2].close();
	cin.get();
	return 0;
}