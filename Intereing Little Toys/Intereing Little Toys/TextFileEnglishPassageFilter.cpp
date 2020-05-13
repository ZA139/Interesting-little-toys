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

// 返回值: 成功 1, 失败 0 Returns： Success 1 Failed 0
// 通过 path 返回获取的路径 Return the gained path through the "path" array
int OpenFileDialog(char *path)
{
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn); // 结构大小 Structure size
	ofn.lpstrFile = path; // 路径 path
	ofn.nMaxFile = MAX_PATH; // 路径大小 Path size
	ofn.lpstrFilter = "Text Files(*TXT)\0*.txt\0\0"; // 文件类型 File format Filter
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;//对话框行为：文件和路径必须存在 Dialog box behavior:File and path must exist
	return GetOpenFileName(&ofn);
}

int SaveFileDialog(char *path)
{
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn); // 结构大小 Structure size
	ofn.lpstrFile = path; // 路径 path
	ofn.lpstrDefExt = TEXT("txt");//默认格式 default format
	ofn.nMaxFile = MAX_PATH; // 路径大小 Path
	ofn.lpstrFilter = "Text Files(*TXT)\0*.txt\0\0"; // 文件类型 File format Filter
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;//对话框行为：文件和路径必须存在 Dialog box behavior:File and path must exist
	return GetSaveFileName(&ofn);
}

//返回桌面路径 return Desktop's path
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