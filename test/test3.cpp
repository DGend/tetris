#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

char* WALL="��";
char* BLOCK="��";
char* SPACE=". ";

bool check(int inputX,int inputY,bool field[][12],int blockVolume, int pointX[],int pointY[]);
void blockShow(int blockVolume, int pointX[],int pointY[],char* block);
int rearrange(bool arr[][4],int pointX[5],int pointY[5]);

bool Type1[4][4]={
	{0,1,1,1},
	{0,0,0,1},
	{0,0,0,0},
	{0,0,0,0}};	
bool Type2[4][4]={ 
	{1,1,1,0},
	{1,0,0,0},
	{0,0,0,0},
	{0,0,0,0}};	
bool Type3[4][4]={
	{1,1,0,0},
	{0,1,1,0},
	{0,0,0,0},
	{0,0,0,0}};
bool Type4[4][4]={
	{1,1,0,0},
	{1,1,0,0},
	{0,0,0,0},
	{0,0,0,0}};
bool Type5[4][4]={
	{1,1,1,1},
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0}};
bool Type6[4][4]={
	{0,1,1,0},
	{1,1,0,0},
	{0,0,0,0},
	{0,0,0,0}};
void oneArray(int input[5],int output[5])//1���� �迭 ����
{
	for(int i=0;i<5;i++)
		output[i]=input[i];
}
void arr_cype(bool* input,bool* output)//2���� �迭����
{
	for(int a=0;a<16;a++)
	{
		*(output+a)=*(input+a);
	}
}
void arryAdd(int point[5],int value,int blockValue)//1���� �迭�� �� �迭��ҿ� ������ ����
{
	for(int i=0;i<blockValue;i++)
		point[i]+=value;
}
void rotation(int x,int y,int outPointX[5],int outPointY[5],int* outValue,bool arr[][4],bool field[][12])//����ȸ�� �� Ȯ��
{
	bool temp_arr[4][4]={false,};
	int cypeX[5]={false,},cypeY[5]={false,};
	arr_cype(*arr,*temp_arr);

	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			arr[j][3-i]=temp_arr[i][j];
		}
	}
	int value=rearrange(arr,cypeX,cypeY);
	arryAdd(cypeX,x,value);
	arryAdd(cypeY,y,value);
	if(check(0,0,field,value,cypeX,cypeY)==true)
	{
		blockShow(*outValue,outPointX,outPointY,SPACE);
		blockShow(value,cypeX,cypeY,BLOCK);
		oneArray(cypeX,outPointX);
		oneArray(cypeY,outPointY);		
		outValue=&value;
		
	}
}
void Random_Arr(bool* temp_type)//�������� ���� ����
{
	srand(time(NULL)); //seed�� �����Ͽ� Random������.
	switch(rand()%6+1){
		case 1:
			arr_cype(*Type1,temp_type);
			break;
		case 2:
			arr_cype(*Type2,temp_type);
			break;
		case 3:
			arr_cype(*Type3,temp_type);
			break;
		case 4:
			arr_cype(*Type4,temp_type);
			break;
		case 5:
			arr_cype(*Type5,temp_type);
			break;
		case 6:
			arr_cype(*Type6,temp_type);
	}
}

void gotoxy(int x,int y)//x�� y
{
	COORD pos={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}

void Base_show(bool field[][12])//�ʱ� �ʵ�迭�� �Է� �� ���
{
	for(int a=0; a<21; a++)
	{
		for(int b=0; b<12; b++)
		{
			if(b==0 || b==11 || a==20)
				field[a][b]=true;

			if(field[a][b]==true)
				printf("%s",WALL);
			else
				printf("%s",SPACE);
		}
		printf("\n");
	}	
}
//#####�˻�ܰ�#####
int rearrange(bool arr[][4],int pointX[5],int pointY[5])//���������
{
	int blockValue=0,count=0;//�� ������ ���ʿ��� ��,���˻�
	int tempX=4,tempY=0;
	for(int y=0; y<4;y++)
	{
		for(int x=0;x<4;x++)
		{
			if(arr[y][x]==1)
			{
				pointX[blockValue]=x+1;
				pointY[blockValue]=y;
				blockValue++;
				if(tempX>x)
					tempX=x;
				if(tempY>y)
					tempY=y;
			}
		}
	}
	for(int i=0;i<blockValue;i++)
	{
		pointX[i]-=tempX;
		pointY[i]-=tempY;
	}
	return blockValue;
}
//�Էµ� �迭�� �ּҰ��� ã�� ��ȯ
int pointMin(int point[],int blockVolume)
{
	int minimum=point[0];
	for(int i=0;i<blockVolume;i++)
	{
		if(minimum>point[i])
			minimum=point[i];
	}
	return minimum;
}
//���� ��ġ�� ��Ҹ� Ȯ���ϴ� �Լ�
bool check(int inputX,int inputY,bool field[][12],int blockValue, int pointX[],int pointY[])
{	
	int tempX[5]={false,},tempY[5]={false,};
	for(int i=0;i<5;i++)
	{
		tempX[i]=pointX[i]+inputX;
		tempY[i]=pointY[i]+inputY;
	}
	for(int i=0;i<blockValue;i++)
	{
		gotoxy((tempX[i])*2,tempY[i]);
		if(field[tempY[i]][tempX[i]]==1)
			return false;
	}	
	return true;
}
//#####�����#####
void blockShow(int blockVolume, int pointX[],int pointY[],char* block)
{
	for(int i=0;i<blockVolume;i++)
	{
		gotoxy((pointX[i])*2,(pointY[i]));
		printf("%s",block);
	}
}
void lineCheck(bool field[][12],int pointX[],int pointY[],int blockValue,int higth)//�� �������� ����
{
	int count=0,nextY=pointY[0],limit=higth-1;
	int indexY=0,samcheck=0;

	for(int y=0;y<blockValue;y++)
	{
		if(nextY<=pointY[y])
		{
			for(int i=1;i<11;i++)
			{
				if(field[pointY[y]][i]==true)
					count++;
			}
			if(count>9)
			{
				for(int j=pointY[y];j>limit;j--)
				{
					for(int i=1;i<11;i++)
					{
						field[j][i]=field[j-1][i];
						gotoxy(i*2,j);
						if(field[j][i]==true)
							printf("%s",BLOCK);
						else
							printf("%s",SPACE);
					}
				}
				nextY--;
			}			
			nextY=pointY[y];
		}
		count=0;
	}
}

int main(void)
{
	bool field[21][12]={false,};
	bool blockCype[4][4]={false,};//������ �� ���� ������ �迭.
	int x=1,y=0;
	int pointX[5]={0,},pointY[5]={0,};
	int blockValue=0;
	int ch=0;//Ű���� �Է� ����.
	int higth=20;

	Base_show(field);
while(higth>0)
{
	x=1,y=0;//X,Y��ǥ�� �ʱ�ȭ
	Random_Arr(*blockCype);//���õ� �迭�� temp������ ����.
	blockValue=rearrange(blockCype,pointX,pointY);
	check(x,y,field,blockValue,pointX,pointY);
	blockShow(blockValue,pointX,pointY,BLOCK);
	for(int height=0;height<20; height++)
	{
		for(int time=0; time<18000; time++)
		{
			if(kbhit())//Ű���� �Է� ����
			{
				ch=getch();
				if(ch==224)
					ch=getch();
				if(ch==UP)
				{
					rotation(x,y,pointX,pointY,&blockValue,blockCype,field);
				}
				else if(ch==DOWN)
				{
					if(check(0,1,field,blockValue,pointX,pointY)==true)
					{
						blockShow(blockValue,pointX,pointY,SPACE);
						arryAdd(pointY,1,blockValue);
						blockShow(blockValue,pointX,pointY,BLOCK);
						y++;
					}
					else
					{
						for(int i=0;i<blockValue;i++)
						{
							field[pointY[i]][pointX[i]]=true;
						}
						if(higth>pointMin(pointY,blockValue))
							higth=pointMin(pointY,blockValue);
						break;
					}
				}
				else if(ch==LEFT)
				{
					if(check(-1,0,field,blockValue,pointX,pointY)==true)
					{
						blockShow(blockValue,pointX,pointY,SPACE);
						arryAdd(pointX,-1,blockValue);
						blockShow(blockValue,pointX,pointY,BLOCK);
						x--;				
					}
				}
				else if(ch==RIGHT)
				{
					if(check(1,0,field,blockValue,pointX,pointY)==true)
					{
						blockShow(blockValue,pointX,pointY,SPACE);
						arryAdd(pointX,1,blockValue);
						blockShow(blockValue,pointX,pointY,BLOCK);
						x++;
					}
				}
				else if(ch==32)
				{
					int tempX[5]={false,},tempY[5]={false,},tempValue=blockValue;
					oneArray(pointX,tempX);
					oneArray(pointY,tempY);
					for(int i=0;i<20;i++)
					{
						if(check(0,1,field,blockValue,pointX,pointY)==true)
						{
							arryAdd(pointY,1,blockValue);
							y++;
						}
						else
						{
							blockShow(tempValue,tempX,tempY,SPACE);
							blockShow(blockValue,pointX,pointY,BLOCK);
							if(higth>pointMin(pointY,blockValue))
								higth=pointMin(pointY,blockValue);
							break;
						}
					}
					break;
				}
			}	
		}
		if(check(0,1,field,blockValue,pointX,pointY)==true)
		{
			blockShow(blockValue,pointX,pointY,SPACE);
			arryAdd(pointY,1,blockValue);
			blockShow(blockValue,pointX,pointY,BLOCK);
			y++;
		}
		else
		{
			for(int i=0;i<blockValue;i++)
			{
				field[pointY[i]][pointX[i]]=true;
			}
			if(higth>pointMin(pointY,blockValue))
				higth=pointMin(pointY,blockValue);
			break;
		}
	}
	//check!!!!!
	gotoxy(30,5);
	printf("higth = %2d",higth);
	///////////////////////////
	lineCheck(field,pointX,pointY,blockValue,higth);//������ ���� �� �� �ű�	
}
return 0;
}