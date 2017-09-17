// sudoku.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include <fstream>
using namespace std;

char sudo[10][10];
int hang[10][10];//行数组
int lie[10][10];//列数组
int gong[10][10];//宫数组
int max1 = 1;//已生成数组个数
int min1 = 1;//要求生成的数组个数
FILE *fp;
errno_t err;

bool check(int h, int l){
	char c = sudo[h][l];
	int k = (int)c - 48;
	int g = h / 3 * 3 + l / 3;
	if (hang[h][k] == 1) {//判断该是否有重复
		return false;
	}
	if (lie[l][k] == 1) {//判断该列是否有重复
		return false;
	}
	if (gong[g][k] == 1) {//判断所在的宫是否有重复
		return false;
	}
	return true;
}

void outsudo() {//输出数独
	for (int i = 0;i<9;i++) {
		for (int j = 0;j<9;j++) {
			fputc(sudo[i][j], fp);
			fputc(' ', fp);
		}
		fputc('\n', fp);
	}
	fputc('\n', fp);
	max1 += 1;
}

void setsudo(int h, int l){//生成数独
	char c;
	int s = 0;
	int g = h / 3 * 3 + l / 3;
	for (c = '1';c <= '9';c=c+1) {
		if (max1>min1) {//数独个数足够后返回
			return;
		}
		sudo[h][l] = c;
		s = (int)c - 48;
		if (check(h, l)) {//判断该数是否符合条件
			hang[h][s] = 1;
			lie[l][s] = 1;
			gong[g][s] = 1;
			if (h == 8 && l == 8) {//数独填满后输出
				outsudo();
			}
			if (l < 8) {
				setsudo(h, l + 1);
			}
			else {
				if(h < 8){
				setsudo(h + 1, 0);
				}
			}
			hang[h][s] = 0;
			lie[l][s] = 0;
			gong[g][s] = 0;
		}
	}
	sudo[h][l] = '0';
}

int main(int argc, char* argv[])
{
	min1 = 0;
	if (argv[1][0] == '-'&&argv[1][1] == 'c' &&argc==3) {//判断命令格式是否正确
		for (int k = 0;argv[2][k] != '\0';k++) {
			if (argv[2][k] <= '9'&&argv[2][k] >= '0') {//得到要求的数独个数
				min1 = min1 * 10 + argv[2][k]-48;
			}
			else {
				cout << "format error!" << endl;
				return 0;
			}
		}
	}
	else {
		cout << "format error!" << endl;
		return 0;
	}
	err=fopen_s(&fp,"sudoku.txt", "w");
	int i, j;
	for (i = 0;i<10;i++) {//初始化
		for (j = 0;j<10;j++) {
			sudo[i][j] = '0';
			hang[i][j] = 0;
			lie[i][j] = 0;
			gong[i][j] = 0;
		}
	}
	setsudo(0, 0);//开始生成数独
	return 0;
}

