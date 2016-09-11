//Reinforce_Learning_QLearning
/*2016/09/11*/
/**/
//使用強化學習中的Q學習法來處理 迷宮問題
//本次Q學習的迷宮圖
//s為狀態
//										 START
//										  s0
//								    	/     \
//						   		      /          \
//								   /               \
//								s1                   s2
//							   /   \               /    \
//							  s3    s4           s5     s6
//							 / \    / \         /  \   /  \
//							s7 s8  s9 s10     s11 s12 s13 s14
/**/
//Q-Learning 學習過程
//1.全部的Q值使用亂數初始化
//2.反覆執行以下事情來學習
// 2.1動作狀態初始化
// 2.2從可能選擇的選項中，依照Q值大小來決定行動的選項
// 2.3行動後、使用Qt = Qt + ALPHA*(r(報酬)+　garma max*Qｔ+1  - Qt);
// 2.4到達一定條件之後(例如 目標狀態已經走到底的狀態，或者是一定的時間經過之後) 回到2.1
// 2.5回到2.2
/**/
/**/
//Q的更新程式處理
//2.3.1如果可以得到報酬的話，將報酬乘於一定比例並加在Q值上面
//將(下一個)可以選擇的狀態之中最大的Q值乘於一定比例之後加在Q上面

/**/
//程式架構
//								  main
//								   ｜
//			　一一一一一一一一一一一一一一一一一一一一一一一一一一一一一一
//			  |           　    |                   |                  |
//		printqvalue函數　　　selecta函數　　　　　Updata函數　　　　　rand100()函數
//　　　　Ｑ值的輸出		　	　行動選擇			Ｑ值的更新		   rand01()函數
//																   rand1()函數
//																	亂數函數


/*learning*/


/*Visual Studio*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include<windows.h>
using namespace std;


#define GENMAX  1000 /*學習次數*/
#define NODENO 15 /*Q的節點數*/
#define ALPHA 0.1 /*學習率*/
#define GAMMA   0.9 /*打折續*/
#define EPSILON 0.3 /*隨機選擇走路的機率*/
#define SEED	32767 /*亂數表*/
#define sleeptime 50 



int rand100();
int rand01();
double rand1();
void printqvalue(int qvalue[NODENO]);
int selecta(int olds, int qvalue[NODENO]);
int updateq(int s, int qvalue[NODENO]);



/*main function*/
int main(){
	int i;
	int s;/*state*/
	int t;/*time*/
	int qvalue[NODENO];

	srand(SEED);/*亂數初始化*/

	/*Q値の初期化*/
	for (i = 0; i < NODENO; ++i)
		qvalue[i] = rand100();
	printqvalue(qvalue);

	/*学習本体*/
	for (i = 0; i < GENMAX; ++i){
		s = 0;
		for (t = 0; t < 3; ++t){
			/*行動の選択*/
			s = selecta(s, qvalue);

			/*Q値の更新*/
			qvalue[s] = updateq(s, qvalue);
		}
		/*Q値の出力*/
		printqvalue(qvalue);
		Sleep(sleeptime);
	}


	system("PAUSE");
	return 0;
}


int updateq(int s, int qvalue[NODENO]){

	int qv;/*更新されたq*/
	int qmax;/*Qの最大値*/

	/*迷宮最下層的時候*/
	if (s > 6){
		if (s == 14){ /*給予報酬*//*報酬1000*/
			qv = qvalue[s] + ALPHA*(1000 - qvalue[s]);
		}
		/*如果要增加某節點的報酬就是像下面的程式*/
		/*else if (s=11){
		qv=value[s]+ALPHA*(500-qvalue[s]);
		}*/
		else/*無報酬*/
			qv = qvalue[s];
	}
	/*最下層以外的時候會繼續往下找*/
	else{
		if ((qvalue[2 * s + 1]) > (qvalue[2 * s + 2]))
			qmax = qvalue[2 * s + 1];
		else qmax = qvalue[2 * s + 2];
		qv = qvalue[s] + ALPHA*(GAMMA*qmax - qvalue[s]);
	}
	return qv;
}

int selecta(int olds, int qvalue[NODENO]){
	int s;
	/*e-greddy亂數法選擇行動*/
	if (rand1() < EPSILON){
		/*ランダム行動*/
		if (rand01() == 0)	s = 2 * olds + 1;
		else s = 2 * olds + 2;
	}
	else{
		/*Q値最大値を選択*/
		if ((qvalue[2 * olds + 1]) > (qvalue[2 * olds + 2])){
			s = 2 * olds + 1;
		}
		else s = 2 * olds + 2;
	}

	return s;
}

void printqvalue(int qvalue[NODENO]){
	for (int i = 1; i < NODENO; ++i){
		printf("%d  ", qvalue[i]);
	}
	printf("\n");
}
int rand100(){
	int rnd = rand();

	while ((rnd == RAND_MAX));
	return(int)((double)rnd / RAND_MAX * 101);
}
int rand01(){
	int rnd;
	rnd = rand();
	while (rnd == RAND_MAX);

	return (int)((double)rnd / RAND_MAX * 2);
}
double rand1(){
	return(double)rand() / RAND_MAX;
}

/**/
//將執行的結果圖形化之後會看到
//Q2.Q6.Q14 從起點開始到Q14所有會經過的路經的Q值會因次數增加而越來越高
