#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

int arr[10][10];	//數獨地圖
bool flag = false;	//是否找到答案了
bool check(int, int);
void dfs(int);

int main(){
	bool used[100];
	srand(time(NULL));	//設亂數種子
	while(!flag){
		int i, j, k;
		//做數獨中左上、中間、右下大格的隨機填數
		for(k=0; k<9; k+=3){
			memset(used, 0, sizeof(used));	//將檢查數字有無使用過的布林陣列設為0
			for(i=k; i<k+3; i++){	
				for(j=k; j<k+3; j++){
					int x = rand() % 9;	//設x為0-8的亂數
					while(used[x])	//若亂數x被使用過
						x = rand() % 9;	//找新的亂數x
					used[x] = true;	//將未使用過的數設為已使用
					arr[i][j] = x + 1;	//將值存進數獨陣列中
				}
			}
		}
		dfs(0);	//填空格子
	}
	memset(used, 0, sizeof(used));	//將檢查格子是否為空的布林陣列設為0
	int n;
	scanf("%d", &n);	//使用者輸入數獨有n個空格
	while(n--){
		int x = rand() % 81;	//設x為0-80的亂數
		while(used[x])	//若格子x為空格
			x = rand() % 81;	//找新的亂數x
		used[x] = true;	//將非空格設為空格
		int i = x / 9;	//設i為第幾列
		int j = x % 9;	//設j為第幾行
		arr[i][j] = 0;	//將格子挖空
	}
	//輸出地圖
	int i, j;
	for(i=0; i<9; i++){
		if(i % 3 == 0)
			printf("- - - - - - - - -\n");
		for(j=0; j<9; j++){
			printf("%d", arr[i][j]);
			if(j % 3 == 2)
				printf("|");
			else
				printf(" ");
		}
		puts("");
	}
	printf("- - - - - - - - -\n");
	return 0;
}
void dfs(int idx){
	
	if(idx == 81){	//若格子填滿
		flag = true;	//找到答案了
		return;
	}
	int i = idx / 9;	//設i為第幾列
	int j = idx % 9;	//設j為第幾行
	if(arr[i][j]){	//若數獨陣列在該格已經有數字了
		dfs(idx + 1);	//找下一格
		return;
	}
	bool used[10] = {0};	//設一布林陣列檢查數字有無使用過，且初始值設為0
	int t;
	for(t=0; t<9; t++){	//一個格子最多九種可能（填數字1-9）
		int x = rand() % 9;	//設x為0-8的亂數
		while(used[x])	//若亂數x被使用過
			x = rand() % 9;	//找新的亂數x
		used[x] = true;	//將未使用過的數設已使用
		arr[i][j] = x + 1;	//將值存進數獨陣列中
		if(check(i, j))	//若該位置填入的數滿足直行、橫列和九宮格都不重複
			dfs(idx + 1);	//填下一格
		if(flag)	//有答案了就直接回上一層
			return;
		arr[i][j] = 0;	//重新填數
	}
}
bool check(int i, int j){
	int r, c;
	for(r=0; r<9; r++){	//直行、橫列都有9格
		if(i != r && arr[r][j] == arr[i][j])	//若同一行不同列有相同的數
			return false;	//該位置填入的數不合理
		if(j != r && arr[i][r] == arr[i][j])	//若同一列不同行有相同的數
			return false;	//該位置填入的數不合理
	}
	//設該位置所在之九宮格的左上角在第a列第b行
	int a = i / 3 * 3;
	int b = j / 3 * 3;
	bool used[10] = {0};	//設一布林陣列檢查數字有無使用過，且初始值設為0
	for(r=a; r<a+3; r++){
		for(c=b; c<b+3; c++){
			if(arr[r][c] && used[arr[r][c]])	//若該數在九宮格內重複使用
				return false;	//該位置填入的數不合理
			used[arr[r][c]] = true;	//將檢查到的數字設為已使用
		}
	}
	return true;	//直行、橫列和九宮格都不重複時，回傳true
}
