/*learnstock.c*/


/*Visual Studio*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#define OK 1
#define NG 0
#define SETSIZE 12  //教師學習
#define CNO		10
#define GENMAX  10000
#define SEED	32767

/* 副程式宣言 */
void readdate(int data[SETSIZE][CNO], int teacher[SETSIZE]);  //讀取學習資料
int rand012(); // 亂數函數 使用給出 0,1,2三個數
int calscore(int data[SETSIZE][CNO], int teacher[SETSIZE], int answer[CNO]);//分數計算

int calldata[SETSIZE][CNO] = { 1, 0, 0, 0, 0, 0, 1, 0, 0, 1,
0, 1, 0, 1, 0, 1, 1, 1, 0, 1,
0, 1, 0, 0, 0, 1, 1, 0, 1, 0,
1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
1, 0, 0, 1, 1, 0, 1, 1, 1, 1,
0, 0, 0, 0, 0, 0, 1, 1, 0, 0,
1, 1, 1, 1, 0, 0, 1, 1, 0, 1,
0, 1, 1, 1, 0, 1, 1, 1, 0, 1,
0, 0, 1, 1, 0, 1, 1, 1, 0, 0,
1, 1, 1, 0, 0, 0, 0, 1, 1, 0,
0, 0, 1, 1, 1, 0, 0, 0, 1, 0,
1, 0, 0, 0, 1, 0, 1, 0, 1, 1
};

int callteacher[SETSIZE] = { 1, 1, 0, 1, 0, 1, 0, 0, 0, 0 };
//random founction


/************************************/
/*main*/

int main()
{
	int i, j;
	int score = 0;
	int answer[CNO];
	int data[SETSIZE][CNO];
	int teacher[SETSIZE];
	int bestscore = 0;
	int bestanswer[CNO];

	srand(SEED); // 亂數的初始化

	//讀取資料
	readdate(data, teacher);

	//解候補的生成 跟 檢查
	for (i = 0; i < GENMAX; i++)
	{
		for (j = 0; j < CNO; j++){
			answer[j] = rand012();

		}


		//檢查分數
		score = calscore(data, teacher, answer);

		//**最優分數更新
		if (score > bestscore){
			for (j = 0; j < CNO; ++j)
				bestanswer[j] = answer[j];
			bestscore = score;
			for (j = 0; j < CNO; ++j)
				printf("%2d", bestanswer[j]);
			printf(":score = %d \n", bestscore);
		}
	}

	//最佳解答輸出
	cout << "最優解" << endl;
	for (j = 0; j < CNO; j++)
		printf("%2d", bestanswer[j]);

	printf(":score = %d \n", bestscore);



	system("PAUSE");
	return 0;
}

//***
//clascore

int calscore(int data[SETSIZE][CNO], int teacher[SETSIZE], int answer[CNO]){

	int score = 0; //分數
	int point; //跟分數同一列的樹
	int i, j;

	for (i = 0; i < SETSIZE; ++i)
	{
		//相似度測試 (一致度計算)

		point = 0;
		for (j = 0; j < CNO; ++j){
			if (answer[j] == 2){
				++point;
			}
			else if (answer[j] == data[i][j]){
				++point;
			}

			if ((point == CNO) && (teacher[i] == 1)){
				++score;
			}
			else if ((point != CNO) && (teacher[i] == 0)){
				++score;
			}

		}
	}

	return score;
}

/**readdata*/

void readdate(int data[SETSIZE][CNO], int teacher[SETSIZE]){
	int i, j;

	for (i = 0; i < SETSIZE; ++i){
		for (j = 0; j < CNO; ++j){
			//scanf("%d", &data[i][j]);
			data[i][j] = calldata[i][j];
		}
		//scanf("%d", &teacher[i]);
		teacher[i] = callteacher[i];
	}
}

//
int rand012(){
	int rnd;
	while ((rnd = rand()) == RAND_MAX);
	return(double)rnd / RAND_MAX * 3;
}