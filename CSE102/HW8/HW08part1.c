#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum{
	T,S,M,B,P,normal,finish,start
}block_type;
typedef struct 
{
	char text[10];
	int data;
	block_type type;
	int pos_x;
	int pos_y;
	int jump_x;
	int jump_y;
}block;

void init_board(block board[][10]);
void print_board(block board[][10]);
int roll_die();
int play(block board[][10],int pos_x,int pos_y);/*Plays the game for 1 player recursively*/
void game(block board[][10]);/*Plays the game for two players and prints the result*/


int main()
{
	block board[10][10];
	srand(time(NULL));
	init_board(board);
	print_board(board);
	game(board);	
	return 0;
}
void init_board(block board[][10])
{
	int col,row,data;
	/*Data initalization*/
	for(row = 0; row < 10; row++){
		if(row % 2 == 0)
			data = 91;
		else 
			data = 90;
		for(col = 0; col < 10; col++){
			board[row][col].type = normal;
			board[row][col].pos_x = row;
			board[row][col].pos_y = col;
			board[row][col].jump_x = 0;
			board[row][col].jump_y = 0;
			if(row % 2 == 0){
				board[row][col].data = data - (10 * row);
				sprintf(board[row][col].text,"%d",data - (10 * row));
				data++;
			}
			else{
				board[row][col].data = data - (10 * (row - 1));
				sprintf(board[row][col].text,"%d",data - (10 * (row - 1)));
				data--;
			}
		}		
	}
	board[0][2].type = T;sprintf(board[0][2].text,"T");board[0][2].jump_x = 2;board[0][2].jump_y = 1;
	board[0][7].type = S;sprintf(board[0][7].text,"S{72}");board[0][7].jump_x = 1;board[0][7].jump_y = 2;
	board[0][8].type = S;sprintf(board[0][8].text,"S{56}");board[0][8].jump_x = 5;board[0][8].jump_y = 4;
	board[0][9].type = finish;sprintf(board[0][9].text,"(Finish)");
	board[1][1].type = M;sprintf(board[1][1].text,"M{94}");board[1][1].jump_x = 3;board[1][1].jump_y = 0;
	board[1][5].type = P;sprintf(board[1][5].text,"P");
	board[1][8].type = B;sprintf(board[1][8].text,"B");board[1][8].jump_x = 3;board[1][8].jump_y = 1;
	board[2][2].type = S;sprintf(board[2][2].text,"S{68}");board[2][2].jump_x = 2;board[2][2].jump_y = 3;
	board[2][5].type = M;sprintf(board[2][5].text,"M{83}");board[2][5].jump_x = 7;board[2][5].jump_y = 1;
	board[2][8].type = T;sprintf(board[2][8].text,"T");board[2][8].jump_x = 3;board[2][8].jump_y = 2;
	board[3][1].type = M;sprintf(board[3][1].text,"M{77}");board[3][1].jump_x = 6;board[3][1].jump_y = 2;
	board[3][4].type = B;sprintf(board[3][4].text,"B");board[3][4].jump_x = 0;board[3][4].jump_y = 2;
	board[3][7].type = S;sprintf(board[3][7].text,"S{52}");board[3][7].jump_x = 1;board[3][7].jump_y = 4;	/*Initiliazes the special types*/
	board[4][3].type = T;sprintf(board[4][3].text,"T");board[4][3].jump_x = 1;board[4][3].jump_y = 5;
	board[4][6].type = M;sprintf(board[4][6].text,"M{77}");board[4][6].jump_x = 6;board[4][6].jump_y = 2;
	board[4][9].type = S;sprintf(board[4][9].text,"S{44}");board[4][9].jump_x = 6;board[4][9].jump_y = 5;
	board[5][0].type = B;sprintf(board[5][0].text,"B");board[5][0].jump_x = 4;board[5][0].jump_y = 4;
	board[5][2].type = P;sprintf(board[5][2].text,"P");
	board[5][5].type = S;sprintf(board[5][5].text,"S{22}");board[5][5].jump_x = 8;board[5][5].jump_y = 7;
	board[6][1].type = M;sprintf(board[6][1].text,"M{52}");board[6][1].jump_x = 1;board[6][1].jump_y = 4;
	board[6][5].type = B;sprintf(board[6][5].text,"B");board[6][5].jump_x = 9;board[6][5].jump_y = 5;
	board[6][9].type = T;sprintf(board[6][9].text,"T");board[6][9].jump_x = 4;board[6][9].jump_y = 6;
	board[7][1].type = B;sprintf(board[7][1].text,"B");board[7][1].jump_x = 3;board[7][1].jump_y = 5;
	board[7][5].type = S;sprintf(board[7][5].text,"S{12}");board[7][5].jump_x = 1;board[7][5].jump_y = 8;
	board[8][2].type = P;sprintf(board[8][2].text,"P");
	board[8][6].type = M;sprintf(board[8][6].text,"M{28}");board[8][6].jump_x = 2;board[8][6].jump_y = 7;
	board[9][3].type = M;sprintf(board[9][3].text,"M{11}");board[9][3].jump_x = 0;board[9][3].jump_y = 8;
	board[9][4].type = S;sprintf(board[9][4].text,"S{1}");board[9][4].jump_x = 9;board[9][4].jump_y = 9;
	board[9][9].type = start;sprintf(board[9][9].text,"(Start)");
}
void print_board(block board[][10])
{
	int col,row;
	for(row = 0; row < 10; row++){
		for(col = 0; col < 10; col++){
			printf("%-6s ",board[row][col].text);
		}
		printf("\n\n");
	}
}
int roll_die()
{
	int die;
	die = rand() % 6 + 1;
	return die;
}
int play(block board[][10],int pos_x,int pos_y)
{
	int currentData = board[pos_y][pos_x].data;
	int col,row,tmpx,trash;
	if((currentData += roll_die()) > 100)
		return play(board,pos_x,pos_y);
	if(currentData == 100){
		printf("(x,y) = 9,0\n");
		return 1;
	}
	for(row = 0; row < 10; row++){
		for(col = 0; col < 10; col++){
			if(board[row][col].data == currentData){
				if(board[row][col].type == P)
					return play(board,pos_x,pos_y);
				pos_x = col;
				pos_y = row;
			}
		}
	}
	if(board[pos_y][pos_x].type != normal){
		tmpx = pos_x;
		pos_x = board[pos_y][pos_x].jump_x;
		pos_y = board[pos_y][tmpx].jump_y;
	}

	trash = play(board,pos_x,pos_y) + 1; 
	printf("(x,y) = %d,%d\n",pos_x,pos_y);
	return trash; 

}
void game(block board[][10])
{
	int plyr1,plyr2;
	printf("Player 1 moves:\n");
	plyr1 = play(board,9,9);
	printf("(x,y) = 9,9\n");
	printf("Player 2 moves:\n");
	plyr2 = play(board,9,9);
	printf("(x,y) = 9,9\n");
	printf("Result is: ");
	if(plyr1 == plyr2)
		printf("Draw!!\n");
	else if(plyr1 > plyr2)
		printf("Player 2 Wins!!\n");
	else
		printf("Player 1 Wins!!\n");
}