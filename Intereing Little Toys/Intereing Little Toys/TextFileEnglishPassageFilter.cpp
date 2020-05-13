#include<windows.h>
#include<Commdlg.h>
#include<cstdio>
#include<iostream>
#include<fstream>
#include<cstring>
#include<shlobj.h>
using namespace std;

#define TEMPFILENAME "//12345678974456454.txt"
char desktoppath[255];

// ����ֵ: �ɹ� 1, ʧ�� 0 Returns�� Success 1 Failed 0
// ͨ�� path ���ػ�ȡ��·�� Return the gained path through the "path" array
int OpenFileDialog(char *path)
{
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn); // �ṹ��С Structure size
	ofn.lpstrFile = path; // ·�� path
	ofn.nMaxFile = MAX_PATH; // ·����С Path size
	ofn.lpstrFilter = "Text Files(*TXT)\0*.txt\0\0"; // �ļ����� File format Filter
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;//�Ի�����Ϊ���ļ���·��������� Dialog box behavior:File and path must exist
	return GetOpenFileName(&ofn);
}

int SaveFileDialog(char *path)
{
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn); // �ṹ��С Structure size
	ofn.lpstrFile = path; // ·�� path
	ofn.lpstrDefExt = TEXT("txt");//Ĭ�ϸ�ʽ default format
	ofn.nMaxFile = MAX_PATH; // ·����С Path
	ofn.lpstrFilter = "Text Files(*TXT)\0*.txt\0\0"; // �ļ����� File format Filter
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;//�Ի�����Ϊ���ļ���·��������� Dialog box behavior:File and path must exist
	return GetSaveFileName(&ofn);
}

//��������·�� return Desktop's path
char* GetDesktopPath() {
	SHGetSpecialFolderPath(0, desktoppath, CSIDL_DESKTOPDIRECTORY, 0);
	return desktoppath;
}

int main(void)
{
	char openFile[MAX_PATH] = { 0 };
	char saveFile[MAX_PATH] = { 0 };
	if (OpenFileDialog(openFile)&&SaveFileDialog(saveFile))
	{
		if(!strcmp(openFile,saveFile)){//samefile
			char* tempFileLocation = strcat(GetDesktopPath(), TEMPFILENAME);
			if (CopyFile(openFile,tempFileLocation, FALSE)) {
				ifstream fin(tempFileLocation);
				ofstream fout(saveFile);
				char ch;
				while (fin >> noskipws >> ch) {
					if (ch >= 1 && ch <= 127)
						fout << ch;
				}
				fin.close();
				fout.close();
				DeleteFile(tempFileLocation);
			}
			else {
				printf("Unknow Error\n");
				getchar();
			}
		}
		else {
			ifstream fin(openFile);
			ofstream fout(saveFile);
			char ch;
			while (fin >> noskipws >> ch) {
				if (ch >= 1 && ch <= 127)
					fout << ch;
			}
			fin.close();
			fout.close();
		}
	}
	else {
		puts("UnknowError!\n");
		getchar();
	}
	return 0;
}