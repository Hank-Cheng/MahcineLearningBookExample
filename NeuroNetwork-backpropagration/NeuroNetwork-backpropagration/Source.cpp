/*Backpropagation*/
//**
//Backpropagation方法的類神經網路機械學習
//誤差的電話 學習的結果的係數等輸出

//本次神經網路 為3個輸入 3個中間層(1層) 1個輸出
//backprogation在輸出層只有一層時候的計算方法
// 當滿足終止條件(例如小於規定誤差)方可停止程式
//1.讀取data的例子的輸入與輸出(x,o)
//  1.1使用x計算中間層的輸出hi
//  1.2使用中間層輸出hi計算O輸出層的輸出
//2.輸出層的神經元計算  wi ← wi + alpha*E*f'(u)*hi 
//3.中間層的神經元計算  Δ(delta)j = hi[j] * (1 - hi[j]) * wo[j] * (x[INPUTNO] - o)*o*(1 - o);
//4.中間層第j個的神經元第i個的輸入的計算  wh[j][i] += ALPHA * x[i]  * dj;


/*Visual Studio*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <windows.h>
#include <math.h>
using namespace std;


#define INPUTNO 3
#define HIDDENNO 3
#define ALPHA 10/*學習率*/
#define SEED	65535 /*亂數表*/
#define MAXINPUTNO 100 /*學習最大次數*/
#define BIGNUM 100 /*誤差的初始值*/
#define LIMIT 0.001 /*誤差的上限值*/
#define sleeptime 0

double f(double u);
double drnd(void);
void   initwo(double wo[HIDDENNO + 1]);//出力層的初期化
void   initwh(double wh[HIDDENNO][INPUTNO + 1]);//中間層的初期化
void   print(double wh[HIDDENNO][INPUTNO + 1], double wo[HIDDENNO + 1]);//結果的出力
double forward(double wh[HIDDENNO][INPUTNO + 1], double wo[HIDDENNO + 1], double hi[], double e[INPUTNO + 1]);
void   olearn(double wo[HIDDENNO + 1], double hi[], double e[INPUTNO + 1], double o);
int    getdata(double e[][INPUTNO + 1]); /*学習資料的讀取*/
void   hlearn(double wh[HIDDENNO][INPUTNO + 1], double wo[HIDDENNO + 1], double hi[], double e[INPUTNO + 1], double o);

/*main*/
int main(){
	double wh[HIDDENNO][INPUTNO + 1];/*中間層的重量*/
	double wo[HIDDENNO + 1];    /*輸出層的重量*/
	double e[MAXINPUTNO][INPUTNO + 1]; /*學習資料組*/
	double hi[HIDDENNO + 1]; /*中間層的輸出*/
	double o; /*輸出*/
	double err = BIGNUM; /*誤差的評價*/
	int i, j; /*for迴圈用*/
	int count = 0; /*學習次數迴圈用*/
	int n_of_e;  /*學習資料的個數*/

	/*乱数の初期化*/
	srand(SEED);

	/*重みの初期化*/
	initwh(wh); /*中間層的重量初始化*/
	initwo(wo);/*輸出層的重量初始化*/
	print(wh, wo); /*結果輸出*/

	/*学習データの読み込み*/
	n_of_e = getdata(e);

	printf("学習データの個数/學習資料庫數量%d \n", n_of_e);

	/*学習本體*/
	while (err > LIMIT){
		err = 0.0;
		for (j = 0; j < n_of_e; ++j){
			/*順方向的計算*/
			o = forward(wh, wo, hi, e[j]); //e[j] is a pointer
			/*出力層の重みの調整*/
			olearn(wo, hi, e[j], o);
			/*中間層の重みの調整*/
			hlearn(wh, wo, hi, e[j], o);
			/*誤差の積算*/
			err += (o - e[j][INPUTNO])*(o - e[j][INPUTNO]);
		}

		++count;

		/*誤差の出力*/
		fprintf(stderr, "運算第%d次\t誤差 %lf\n", count, err);
		Sleep(sleeptime);//運算速度調整至可以觀察的程度
	}/*学習終了*/

	/*結合荷重的輸出*/
	print(wh, wo);

	/*学習データに対する出力*/
	for (i = 0; i < n_of_e; ++i){
		printf("%d ", i);
		for (j = 0; j < INPUTNO + 1; ++j)
			printf("%lf ", e[i][j]);
		o = forward(wh, wo, hi, e[i]); //輸出答案
		printf("%lf\n", o);

	}

	system("PAUSE");
	return 0;
}

void hlearn(double wh[HIDDENNO][INPUTNO + 1], double wo[HIDDENNO + 1], double hi[], double e[INPUTNO + 1], double o){

	int i, j;
	double dj;

	for (j = 0; j < HIDDENNO; ++j){
		dj = hi[j] * (1 - hi[j])*wo[j] * (e[INPUTNO] - o)*o*(1 - o); /*(中間層第J個的神經元的計算)*/

		for (i = 0; i < INPUTNO; ++i)
			wh[j][i] += ALPHA*e[i] * dj; /*(中間層第J個第i個的神經元的輸入 計算)*/
		wh[j][i] += ALPHA*(-1.0)*dj;    /*極值處理*/

	}
}
int    getdata(double e[][INPUTNO + 1]){
	//int n_of_e = 0;/*データセットの個数*/
	int j = 0;
	//printf("EOF== %d", EOF);
	//while (scanf("%lf", &e[n_of_e][j]) != EOF){
	//	printf("e[%d][%d]== %lf ", n_of_e,j,e[n_of_e][j]);
	//	++j;
	//	if (j > INPUTNO){
	//		j = 0;
	//		++n_of_e;
	//	}
	//	
	//}

	int n_of_e = 8;/*データセットの個数*/

	e[0][0] = 1;
	e[0][1] = 1;
	e[0][2] = 1;
	e[0][3] = 1;//第0組教師學習的答案

	e[1][0] = 1;
	e[1][1] = 1;
	e[1][2] = 0;
	e[1][3] = 1;

	e[2][0] = 1;
	e[2][1] = 0;
	e[2][2] = 1;
	e[2][3] = 1;

	e[3][0] = 1;
	e[3][1] = 0;
	e[3][2] = 0;
	e[3][3] = 0;

	e[4][0] = 0;
	e[4][1] = 1;
	e[4][2] = 1;
	e[4][3] = 1;

	e[5][0] = 0;
	e[5][1] = 1;
	e[5][2] = 1;
	e[5][3] = 1;

	e[6][0] = 0;
	e[6][1] = 0;
	e[6][2] = 1;
	e[6][3] = 0;

	e[7][0] = 0;
	e[7][1] = 0;
	e[7][2] = 0;
	e[7][3] = 0;


	return n_of_e;
}
void   olearn(double wo[HIDDENNO + 1], double hi[], double e[INPUTNO + 1], double o){

	int i;
	double d;
	d = (e[INPUTNO] - o) * o *(1 - o);/*誤差の計算*/  /*o 是剛剛forward 計算出來的結果*/
	for (i = 0; i < HIDDENNO; ++i){
		wo[i] += ALPHA*hi[i] * d;/*重みの学習*/          /*wi更新 wi wi ← wi + alpha*E*f'(u)*hi  */
	}
	wo[i] += ALPHA*(-1.0)*d;/*しきいちの学習*/           /*本次是siguma函數 f'(u)~ f(u) * ( 1-f(u) )   */
}
double forward(double wh[HIDDENNO][INPUTNO + 1], double wo[HIDDENNO + 1], double hi[], double e[INPUTNO + 1]){ /*陣列[0] 是陣列的位置 +1 之後才是資料 */
	int i, j;
	double u;
	double o;

	/*中間層輸出的計算*/
	for (i = 0; i < HIDDENNO; ++i){
		u = 0;
		for (j = 0; j < INPUTNO; ++j)
			u += e[j] * wh[i][j]; /*e[j]是指標,(第一個輸入) wh也是指標(第一個重量) 這裡是指標互乘*/ /*每個*/
		u -= wh[i][j];      //極值處理
		hi[i] = f(u);       //hi 中間層輸出
	}

	/*出力の計算*/
	o = 0;
	for (i = 0; i < HIDDENNO; ++i)
		o += hi[i] * wo[i];
	o -= wo[i]; //閾値の処理。

	return f(o);
}
void   print(double wh[HIDDENNO][INPUTNO + 1], double wo[HIDDENNO + 1]){
	int i, j;

	cout  << endl;
	cout << "中間層的重量wh" << endl;
	for (i = 0; i < HIDDENNO; ++i)
		for (j = 0; j < INPUTNO + 1; ++j)
			printf("%lf\n", wh[i][j]);
	printf("\n");

	cout << "輸出層的重量wo" << endl;
	for (i = 0; i < HIDDENNO + 1; i++)
		printf("%lf\n", wo[i]);
	printf("\n");
}
void   initwh(double wh[HIDDENNO][INPUTNO + 1]){
	for (int i = 0; i < HIDDENNO; ++i)
		for (int j = 0; j < INPUTNO + 1; ++j)
			wh[i][j] = drnd();
}
void   initwo(double wo[HIDDENNO + 1]){
	for (int i = 0; i < HIDDENNO + 1; ++i)
		wo[i] = drnd();
}
double drnd(void){
	double rndno;/*亂數生成*/
	while ((rndno = (double)rand() / RAND_MAX) == 1.0);
	rndno = rndno * 2 - 1; /*從-1到1之間亂數生成*/
	return rndno;
}
double f(double u){
	return 1.0 / (1.0 + exp(-u));
}

/*backpropagation教師學習方法是先將教師的輸入計算之後算出來的輸出跟 當組的真實輸出比較之後算出誤差，再加上學習率由後往前修改比重*/