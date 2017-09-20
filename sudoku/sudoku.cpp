#include <time.h>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;
int sudoku[10][10];   
int N, i, j,u,v;
int main()
{
    freopen("sudoku.txt", "w+", stdout);
	int fn = (1 + 4) % 9 + 1;
    int star(int i, int j);    
	cin >> N;
	srand((unsigned)time(NULL));//以当前系统时间生成随机数
	for (int m = 0; m<N; m++)
	{

		for (i = 1; i <=9; i++)
		{
			for (j = 1; j <=9; j++)
				sudoku[i][j] = 0;
		}                                  //初始化数独矩阵
		for (i = 1; i <= 9; i++)
		{
			sudoku[1][i] = i;              //按序生成第一行
		}
		sudoku[1][1] = fn;                 
		sudoku[1][fn] = 1;
		random_shuffle(&(sudoku[1][2]), &(sudoku[1][9]));  //第一行第一个数交换为6，使后八个数随机排列
		
		
		star(2, 1);           //调用star函数，从第二行第一个数开始生成数独矩阵
		
		for (i = 1; i <= 9; i++)
		{
			for (j = 1; j <= 9; j++)
				cout << sudoku[i][j] << " ";
				cout << endl;;
		}//输出生成的数独矩阵
		
		cout << endl;
	}

	return 0;
}
int star(int i, int j)
{
	int same;
	
	if (i > 9 || j > 9)
	{
		return 1;
	}
		
		
	for (int a = 1; a <= 9; a++)
	{
		same = 1;
		for (int b = 1; b<i; b++)
		if (a == sudoku[b][j])
		{
				same = 0;
				break;
		}//检测上下有无重复
		
		if (same)
		{
			for (int n = 1; n<j; n++)
				if (a == sudoku[i][n])
				{
					same = 0;
					break;
				}//检测左右有无重复
		}
		
		if (same)
		{
			int x = (i / 3) * 3 + 3;
			int y = (j / 3) * 3 + 3; //找到宫格的边界格子
			if (i % 3 == 0)
			{
				x = i;
			}
			if (j % 3 == 0)
			{
				y = j;
			}
			for (u = x - 2; u <= x; u++)  //检查宫格中有无重复
			{
				if (same == 0)
					break;
				for (v = y - 2; v <= y; v++)
					if (a == sudoku[u][v])
					{
						same = 0;
						break;
					}
			}
		}
		
		if (same)
		{
			sudoku[i][j] = a;
			if (j<9)
			{
				if (star(i, j + 1))   //跳到此行的下一列 
					return 1;
			}
			else
			{
				if (i < 9)
				{
					if (star(i + 1, 1))    //跳到此列下一行
						return 1;
				}
				else
					return 1;  //当行或列数超过9时结束

			}
			sudoku[i][j] = 0;   
		}
		
	}
	return 0; 
}