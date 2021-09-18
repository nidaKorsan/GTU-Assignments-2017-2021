#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct 
{
	int Width;
	int Height;
	char **Map;
	int Flower_X;
	int Flower_Y;
}Forest;
typedef struct 
{
	int Coord_X;
	int Coord_Y;
	int Water_Bottle_Size;
}Botanist;
void init_game(Forest * forest,Botanist * botanist);
void print_map (Forest forest);
void search(Forest * forest,Botanist * botanist);
int isEmpty(Forest * forest,Botanist * botanist);/*This function generates a random way to go and checks if the target is empty or flower. If the target is not empty it recursively calls itself untill a proper target exists*/
void freeEmAll(Forest * forest);

int main()
{
	Botanist botanist;
	Forest forest;
	srand(time(NULL));
	init_game(&forest,&botanist);
	print_map(forest);
	printf("\nSearching...\n\n");
	search(&forest,&botanist);
	freeEmAll(&forest);
	return 0;
}
void init_game(Forest * forest,Botanist * botanist)
{
	FILE *fr;
	int row=0,col=0,i;
	fr = fopen("init.txt","r");
	fscanf(fr,"%d",&botanist->Water_Bottle_Size);
	fscanf(fr,"%d,",&forest->Width);
	fscanf(fr,"%d ",&forest->Height);
	forest->Map = (char **)calloc(forest->Width,sizeof(char *));
	for(i = 0; i < forest->Height;i++){
		forest->Map[i] = (char *)calloc(forest->Height,sizeof(char));
	}
	while(row != forest->Width){
		fscanf(fr,"%c",&forest->Map[row][col]);
		getc(fr);
		if(forest->Map[row][col] == 'B'){
			botanist->Coord_X = col;
			botanist->Coord_Y = row;
		}
		if(forest->Map[row][col] == 'F'){
			forest->Flower_X = col;
			forest->Flower_Y = row;
		}
		col++;
		if(col == forest->Height){
			col = 0;
			row++;
			getc(fr);
		}
	}
	fclose(fr);
}
void print_map (Forest forest)
{
	int row=0,col=0;
	while(row != forest.Width){
		printf("%c ",forest.Map[row][col]);
		col++;
		if(col == forest.Height){
			col = 0;
			row++;
			printf("\n");
		}
	}

}
void search(Forest * forest,Botanist * botanist)
{
	if(botanist->Coord_X == forest->Flower_X && botanist->Coord_Y == forest->Flower_Y){
		print_map(*forest);
		printf("I have found it on (%d,%d)!\n",botanist->Coord_Y,botanist->Coord_X);
		return;
	}
	if(botanist->Water_Bottle_Size == 0){
		print_map(*forest);
		printf("Help! I am on (%d,%d)\n",botanist->Coord_Y,botanist->Coord_X);
		return;
	}
	switch(isEmpty(forest,botanist)){
		case 1:
			forest->Map[botanist->Coord_Y][botanist->Coord_X] = ' ';
			if(forest->Map[botanist->Coord_Y][botanist->Coord_X + 1] != 'F')
			forest->Map[botanist->Coord_Y][botanist->Coord_X + 1] = 'B';
			botanist->Water_Bottle_Size--;
			botanist->Coord_X++;
			search(forest,botanist);
			break; 
		case 2:
			forest->Map[botanist->Coord_Y][botanist->Coord_X] = ' ';
			if(forest->Map[botanist->Coord_Y][botanist->Coord_X - 1] != 'F')
			forest->Map[botanist->Coord_Y][botanist->Coord_X - 1] = 'B';
			botanist->Water_Bottle_Size--;
			botanist->Coord_X--;
			search(forest,botanist);
			break;
		case 3:
			forest->Map[botanist->Coord_Y][botanist->Coord_X] = ' ';
			if(forest->Map[botanist->Coord_Y + 1][botanist->Coord_X] != 'F')
			forest->Map[botanist->Coord_Y + 1][botanist->Coord_X] = 'B';
			botanist->Water_Bottle_Size--;
			botanist->Coord_Y++;
			search(forest,botanist);
			break;
		case 4:
			forest->Map[botanist->Coord_Y][botanist->Coord_X] = ' ';
			if(forest->Map[botanist->Coord_Y - 1][botanist->Coord_X] != 'F')
			forest->Map[botanist->Coord_Y - 1][botanist->Coord_X] = 'B';
			botanist->Water_Bottle_Size--;
			botanist->Coord_Y--;
			search(forest,botanist);
	}
}
int isEmpty(Forest * forest,Botanist * botanist)
{
	int dir;
	dir = rand() % 4 + 1;
	if(dir == 1 && forest->Map[botanist->Coord_Y][botanist->Coord_X + 1] != '#' && botanist->Coord_X + 1 < forest->Height){/*if right*/
		return 1;
	}
	else if(dir == 2 && forest->Map[botanist->Coord_Y][botanist->Coord_X - 1] != '#' && botanist->Coord_X - 1 > -1){/*if left*/
		return 2;
	}
	else if(dir == 3 && forest->Map[botanist->Coord_Y + 1][botanist->Coord_X] != '#' && botanist->Coord_Y + 1 < forest->Width){/*if down*/
		return 3;
	}
	else if(dir == 4 && forest->Map[botanist->Coord_Y - 1][botanist->Coord_X] != '#' && botanist->Coord_Y - 1 > -1){/*if up*/
		return 4;
	}
	return isEmpty(forest,botanist);
}
void freeEmAll(Forest * forest)
{
	int i;
	for(i = 0; i < forest->Height;i++){
		free(forest->Map[i]);
	}
	free(forest->Map);

}