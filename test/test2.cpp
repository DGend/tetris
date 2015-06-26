#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
char* wall="■";
char* Block="□";
char* space=". ";

char* wall_Block="■";
char* play_Block="□";

bool field[21][12]={false,};

bool type1[4][4]={
	{0,0,0,0},
	{1,1,1,1},
	{0,0,0,1},
	{0,0,0,0}};
	
bool type2[4][4]={ 
	{0,0,0,0},
	{1,1,1,1},
	{1,0,0,0},
	{0,0,0,0}};
	
bool type3[4][4]={
	{0,0,0,0},
	{1,1,0,0},
	{0,1,1,0},
	{0,0,0,0}};
bool type4[4][4]={
	{0,0,0,0},
	{0,1,1,0},
	{0,1,1,0},
	{0,0,0,0}};

bool type5[4][4]={
	{0,0,0,0},
	{1,1,1,1},
	{0,0,0,0},
	{0,0,0,0}};

bool type6[4][4]={
	{0,0,0,0},
	{0,1,1,0},
	{1,1,0,0},
	{0,0,0,0}};

void arrCype(bool* type,bool* result)//배열복사
{
	int x = sizeof(type)*sizeof(type);
	for(int i=0; i<x; i++)
	{
		*(result+i)=*(type+i);
	}
}

void gotoxy(int x,int y)//x와 y
{
	COORD pos={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}

void initialize(bool arr[][4], bool x)//배열의 [0][]과[][0]의 삭제
{	
	bool tempBlockArr[4][4]={false,};
	arrCype(*arr,*tempBlockArr);
	int countX=0,countY=0;
	int i=0;
	int j=0;

	for(int k=1;k<4;k++)
	{
		for(int l=0;l<4;l++)
		{
			if(arr[k][l]==1&&x==true)
			{
				countX++;
				arr[i][countX]=tempBlockArr[k][l];
			}
			if(arr[l][k]==1&&x==false)
			{
				arr[i][countX]=tempBlockArr[k][l];
				countY++;
			}
		}

	}	
	gotoxy(0,0);
		for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			printf("%d",arr[i][j]);
		}
		printf("\n");
	}
	
}

void randomArr(bool *blockCpye)//랜덤으로 도형호출
{
	srand(time(NULL)); //seed를 삽입하여 Random값구현.
	switch(rand()%6+1){
		case 1:
			arrCype(*type1,blockCpye);
			break;
		case 2:
			arrCype(*type2,blockCpye);
			break;
		case 3:
			arrCype(*type3,blockCpye);
			break;
		case 4:
			arrCype(*type4,blockCpye);
			break;
		case 5:
			arrCype(*type5,blockCpye);
			break;
		case 6:
			arrCype(*type6,blockCpye);
	}
}

int rearrange(bool arr[][4],int pointX[5],int pointY[5])//블럭갯수출력
{
	int blockVolume=0,count=0;//블럭 갯수와 불필요한 행,열검사
	*pointX=0, *pointY=0;//true 좌표값
	
	for(int y=0; y<4;y++)
	{
		for(int x=0;x<4;x++)
		{
			if(arr[y][x]==1)
			{
				pointX[blockVolume]=x;
				pointY[blockVolume]=y;
				blockVolume++;
			}
		}
	}
	if(blockVolume<5)
	{
		for(int i=blockVolume;i<5;i++)
		{
			pointX[i]=0;
			pointY[i]=0;
		}
	}
	return blockVolume;
}

int pointMin(int point[],int blockVolume)
{
	int minimum=0;
	for(int i=0;i<blockVolume;i++)
	{
		if(minimum>point[i])
			minimum=point[i];
	}
	return minimum;
}

void blockShow(int x,int y,int blockVolume, int pointX[],int pointY[],bool mk)
{
	for(int i=0;i<blockVolume;i++)
	{
		gotoxy((x-pointMin(pointX,blockVolume)+pointX[i])*2,(y-pointMin(pointY,blockVolume)+pointY[i]));
		if(mk==true)
			printf("%s",play_Block);
		else
			printf("%s",space);
	}
}

int main()
{
	bool blockCpye[4][4]={false,};//임의의 배열을 저장할 배열.


	int ch=0;//키보드 입력 변수.
	int x=1,y=0;	

	randomArr(*blockCpye);//선택된 배열을 temp변수에 복사.


	initialize(blockCpye,true);

	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			printf("%d",blockCpye[i][j]);
		}
		printf("\n");
	}
	return 0;
}