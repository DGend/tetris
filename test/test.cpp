#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

bool field[21][12]={false,};
char* wall="■";
char* Block="□";
char* space=". ";

bool Type6[4][4]={
	{0,1,1,0},
	{1,1,0,0},
	{0,0,0,0},
	{0,0,0,0}};

void gotoxy(int x,int y)//x와 y
{
	COORD pos={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}

void arr_Cype(bool* type,bool* result)//배열복사
{
	int x = sizeof(type)*sizeof(type);
	for(int i=0; i<x; i++)
	{
		*(result+i)=*(type+i);
	}
}

void rotation(bool arr[][4])//도형회전
{
	bool temp_arr[4][4]={false,};
	arr_Cype(*arr,*temp_arr);
	for(int i=0;i<16;i++)
	{
		arr[i%4][3-i/4]=temp_arr[i/4][i%4];
	}
}
/*
void show_backup(int x, int y, bool arr[][4],bool mk)//블럭출력
{
	int count_x=0,count_y=0;
	int type_x=0, type_y=0;
	bool temp[4][4]={false,};
	arr_Cype(*temp_type,*temp);

	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			if(arr[i][j]==0)
				count_y++;
			if(arr[j][i]==0)
				count_x++;
		}
		if(count_y<4)
		{
			type_y++;
		}
		else
		{
			for(int j=0; j<4&&i<3; j++)
			{
				temp[i][j]=temp[i+1][j];
				temp[i+1][j]=false;
			}
		}
		count_y=0;
		if(count_x<4)
		{
			type_x++;
		}
		else
		{
			for(int j=0; j<4&&i<3; j++)
			{
				temp[j][i]=temp[j][i+1];
				temp[j][i+1]=false;
			}
		}
		count_x=0;
	}
	//문제!!!!
	for(int i=0; i<type_y;i++)
	{
		for(int j=0; j<type_x; j++)
		{
			temp[i][j]=temp_type;
		}
	}

	if(x+type_x>11)
		x=11-type_x;
	if(y+type_y>20)
		y=20-type_y;

	for(int i=0;i<type_y;i++)
	{
		for(int j=0;j<type_x;j++)
		{
			if(y>20)
			{
				field[y+type_y][x+type_x]=temp[type_y][type_x];
			}
			else
			{
				gotoxy((x+j)*2,y+i);
				if(temp[i][j]==1&&mk==true)
					printf("%s",Block);
				else
					printf("%s",space);
			}
		}
	}	
}
*/
void show(int x, int y, bool arr[][4],bool mk)//블럭출력
{
	int count_x=0,count_y=0;
	int type_x=0, type_y=0;
	bool temp[4][4]={false,};
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			if(arr[i][j]==0)
				count_y++;
			if(arr[j][i]==0)
				count_x++;
		}
		if(count_y<4)
		{
			temp[type_y][type_x]=true;
			type_y++;
		}
		count_y=0;
		if(count_x<4)
		{
			temp[type_y][type_x]=true;
			type_x++;
		}
		count_x=0;
	}

	if(x+type_x>10)
		x=10-type_x;
	if(y+type_y>20)
		y=20-type_y;

	for(int i=0;i<type_y;i++)
	{
		for(int j=0;j<type_x;j++)
		{
			if(y>20)
			{
				field[y+type_y][x+type_x]=temp[type_y][type_x];
			}
			else
			{
				gotoxy((x+j)*2,y+i);
				if(temp[i][j]==1&&mk==true)
					printf("%s",Block);
				else
					printf("%s",space);
			}
		}
	}	
}

void mk_show(bool type[][4])
{
	for(int i=0; i<16;i++)
	{
		if(i%4==0&&i!=0)
			printf("\n");
		printf("%d",type[i/4][i%4]);
	}
}


void reset(bool* type)
{
	int x = sizeof(type)*sizeof(type);
	for(int i=0; i<x; i++)
	{
		*(type)=0;
	}
}

int arr_reconstitution(bool type[][4],bool choice)//배열 움직임, 길이
{
	int count=0;
	int result=0;
	for(int i=0; i<16; i++)
	{
		if(type[i/4][i%4]==0)
			count++;
		
		
		if(count>3)
		{
			for(int j=0; j<4&&i<3; j++)
			{
				type[i][j]=type[i+1][j];
				type[i+1][j]=false;
			}
		}
		else
			result++;
	}
	return result;
}

int test()
{
	int a=1;
	int b=2;

	return a,b;
}
void change1(bool arr[][4],bool x)
{
	int a=0;
	int b=5;
	int* temp;
	if(x==true)
		temp=&a;
	else
		temp=&b;
	
	for(int i=0; i<4;i++)
	{
		*temp+=1;
	}
	printf("temp=%d",*temp);
}

void change(bool arr[][4],bool result[][4], bool x)
{
	int *temp_x,*temp_y;
	int i=1;
	int j=0;
	if(x==true)
	{
		temp_x=&j;
		temp_y=&i;
	}
	else
	{
		temp_x=&i;
		temp_y=&j;
	}
	for(; i<4;i++)
	{
		for(;j<4;j++)
		{
			result[*temp_y][*temp_x]=arr[*temp_y][*temp_x];
			printf("%d",arr[*temp_y][*temp_x]);
		}
		j=0;
		printf("\n");
	}
}

int main()
{
	bool test[4][4]={false,};
	bool arr[4][4]={
		{0,0,0,0},
		{1,1,1,1},
		{0,0,0,1},
		{0,0,0,0}};
	change(arr,test,false);
	printf("\n");
	change(arr,test, true);
	
	int count_x=0,count_y=0;
	int type_x=0, type_y=0;
	bool temp[4][4]={false,};
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			if(arr[i][j]==0)
				count_y++;
			if(arr[j][i]==0)
				count_x++;
		}
		if(count_y<4)
		{			
			type_y++;
		}
		count_y=0;
		if(count_x<4)
		{			
			type_x++;
		}
		count_x=0;
	}
	return 0;

	/*
	bool temp[4][4]={false,};
	arr_Cype(*Type6,*temp);
	mk_show(temp);
	
	reset(*temp);
	printf("\n");

	rotation(temp);
	mk_show(temp);
	printf("\n");
	*/

}