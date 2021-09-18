#include <stdio.h>
#define BRD_SIZE 8
typedef enum {
	white_man,
	black_man,
	white_king,
	black_king,
	empty} piece;
typedef enum{
	white = 10,
	black = 20} player;
int absolute(int a);
void init_board(piece board[][BRD_SIZE]);
void display_board(piece board[][BRD_SIZE]);
int move(piece board[][BRD_SIZE],int from_x,int from_y,int to_x,int to_y,player p);
int wrong_player(piece board[][BRD_SIZE],int from_x,int from_y,player p);
int move_not_allowed(piece board[][BRD_SIZE],int from_x,int from_y,int to_x,int to_y);
int isEmpty(piece board[][BRD_SIZE],int to_x,int to_y);
int isBack(piece board[][BRD_SIZE],int from_x,int from_y,int to_x,int to_y);
int isCross(int from_x,int from_y,int to_x,int to_y);
int isMan(piece board[][BRD_SIZE],int from_x,int from_y);
int howMuchTile(int from_x,int from_y,int to_x,int to_y);
void goStraight(piece board[][BRD_SIZE],int from_x,int from_y,int to_x,int to_y);
int captureMan(piece board[][BRD_SIZE],int from_x,int from_y,int to_x,int to_y);
int toWhere(int from_x,int from_y,int to_x,int to_y);
int checkMan(piece board[][BRD_SIZE],int from_x,int from_y);
int canKingGo(piece board[][BRD_SIZE],int from_x,int from_y,int to_x,int to_y);
void becomingKing(piece board[][BRD_SIZE],player p);
void captureKing(piece board[][BRD_SIZE],int from_x,int from_y,int to_x,int to_y);
int checkKing(piece board[][BRD_SIZE],int from_x,int from_y,int to_x,int to_y);
int controlWhereMan(piece board[][BRD_SIZE],int *from_x,int *from_y,int *to_x,int *to_y);





int main()
{
	piece ar[BRD_SIZE][BRD_SIZE];
	int from_x,from_y,to_x,to_y,player;
	init_board(ar);
	display_board(ar);
	do{
		printf("Enter from_x from_y : ");
		scanf("%d %d",&from_x,&from_y);
		printf("Enter to_x to_y : ");
		scanf("%d %d",&to_x,&to_y);
		printf("Enter player : ");
		scanf("%d",&player);
		printf("move : %d\n",move(ar,from_x,from_y,to_x,to_y,player));
		display_board(ar);
	}while(from_x != -1);

	return 0;

}
int absolute(int a)
{
	if(a < 0){
		a *= -1;
		return a;
	}
	else 
		return a;
}
void init_board(piece board[][BRD_SIZE])
{
	int i,j;
	for(i = 0;i < BRD_SIZE; i++){
		for(j = 0 ; j < BRD_SIZE; j++){
			board[i][j] = empty;
		}
	}
	for(i = 1; i < 3 ; i++){
		for(j = 0; j < BRD_SIZE; j++){
			board[i][j] = black_man;
		}
	}
	for(i = 5; i < 7 ; i++){
		for(j = 0; j < BRD_SIZE; j++){
			board[i][j] = white_man;
		}
	}
}
void display_board(piece board[][BRD_SIZE])
{
	int i,j;
	for(i = 0;i < BRD_SIZE;i++){
		for(j = 0;j < BRD_SIZE;j++){
			switch(board[i][j]){
				case white_man:
					printf("w");
					break;
				case black_man:
					printf("b");
					break;
				case white_king:
					printf("W");
					break;
				case black_king:
					printf("B");
					break;
				case empty:
					printf("-");
			}
		}
		printf("\n");
	}
}
int move(piece board[][BRD_SIZE],int from_x,int from_y,int to_x,int to_y,player p)
{
	int countCapture = 0;
		if(wrong_player(board,from_x,from_y,p)){
			return -1;
		}
		else if(move_not_allowed(board,from_x,from_y,to_x,to_y) || canKingGo(board,from_x,from_y,to_x,to_y) == -2 ){
			return -2;
		}
		else if(isMan(board,from_x,from_y) && howMuchTile(from_x,from_y,to_x,to_y) == 1){
			goStraight(board,from_x,from_y,to_x,to_y);		
		}
		else if(isMan(board,from_x,from_y) && howMuchTile(from_x,from_y,to_x,to_y) == 2){
			do{
				captureMan(board,from_x,from_y,to_x,to_y);
				countCapture++;
				if(!controlWhereMan(board,&from_x,&from_y,&to_x,&to_y))
					break;

			}while(checkMan(board,from_x,from_y));
		}
		else if(!isMan(board,from_x,from_y) && canKingGo(board,from_x,from_y,to_x,to_y)){
			goStraight(board,from_x,from_y,to_x,to_y);
		}
		else if(!isMan(board,from_x,from_y) && checkKing(board,from_x,from_y,to_x,to_y)){
			captureKing(board,from_x,from_y,to_x,to_y);
			countCapture++;
		}
		
		becomingKing(board,p);
	return countCapture;
}
int canKingGo(piece board[][BRD_SIZE],int from_x,int from_y,int to_x,int to_y)
{
	int i;
	if(white_king == board[from_y][from_x]){
		if(from_y - to_y == 0){
			if(to_x > from_x)
				for( i = from_x + 1; i < to_x ;i++ ){
					if(white_man == board[from_y][i] || white_king == board[from_y][i])
						return -2;
					if(!isEmpty(board,i,from_y))
						return 0;
				}
			else
				for( i = from_x -1; i > to_x ;i-- ){
					if(white_man == board[from_y][i] || white_king == board[from_y][i])
						return -2;
					if(!isEmpty(board,i,from_y))
						return 0;
				}
		}
		else if(from_x - to_x == 0){
			if(to_y > from_y)
				for( i = from_y + 1; i < to_y ;i++ ){
					if(white_man == board[i][from_x] || white_king == board[i][from_x])
						return -2;
					if(!isEmpty(board,from_x,i))
						return 0;
				}
			else
				for( i = from_y - 1; i > to_y ;i-- ){
					if(white_man == board[i][from_x] || white_king == board[i][from_x])
						return -2;

					if(!isEmpty(board,from_x,i))
						return 0;
				}
		}
	}
	if(black_king == board[from_y][from_x]){
		if(from_y - to_y == 0){
			if(to_x > from_x)
				for( i = from_x + 1; i < to_x ;i++ ){
					if(black_man == board[from_y][i] || black_king == board[from_y][i])
						return -2;
					if(!isEmpty(board,i,from_y))
						return 0;
				}
			else
				for( i = from_x -1; i > to_x ;i-- ){
					if(black_man == board[from_y][i] || black_king == board[from_y][i])
						return -2;
					if(!isEmpty(board,i,from_y))
						return 0;
				}
		}
		else if(from_x - to_x == 0){
			if(to_y > from_y)
				for( i = from_y + 1; i < to_y ;i++ ){
					if(black_man == board[i][from_x] || black_king == board[i][from_x])
						return -2;
					if(!isEmpty(board,from_x,i))
						return 0;
				}
			else
				for( i = from_y - 1; i > to_y ;i-- ){
					if(black_man == board[i][from_x] || black_king == board[i][from_x])
						return -2;
					if(!isEmpty(board,from_x,i))
						return 0;
				}
		}
	}

	return 1;
}
void captureKing(piece board[][BRD_SIZE],int from_x,int from_y,int to_x,int to_y)
{
	int i;
	if(from_y - to_y == 0){
			if(to_x > from_x)
				for( i = from_x + 1; i < to_x ;i++ ){
					board[from_y][i] = empty;
				}
			else
				for( i = from_x -1; i > to_x ;i-- ){
					board[from_y][i] = empty;
				}
		}
		else if(from_x - to_x == 0){
			if(to_y > from_y)
				for( i = from_y + 1; i < to_y ;i++ ){
					board[i][from_x] = empty;
				}
			else
				for( i = from_y - 1; i > to_y ;i-- ){
					board[i][from_x] = empty;
				}
		}
		board[to_y][to_x] = board[from_y][from_x];
		board[from_y][from_x] = empty;
}
int checkKing(piece board[][BRD_SIZE],int from_x,int from_y,int to_x,int to_y)
{
	int count = 0,i;
	if(white_king == board[from_y][from_x]){
		if(from_y - to_y == 0){
			if(to_x > from_x)
				for( i = from_x + 1; i < to_x ;i++ ){
					if(black_man == board[from_y][i] || black_king == board[from_y][i])
						count++;
				}
			else
				for( i = from_x -1; i > to_x ;i-- ){
					if(black_man == board[from_y][i] || black_king == board[from_y][i])
						count++;
				}
		}
		else if(from_x - to_x == 0){
			if(to_y > from_y)
				for( i = from_y + 1; i < to_y ;i++ ){
					if(black_man == board[i][from_x] || black_king == board[i][from_x])
						count++;
				}
			else
				for( i = from_y - 1; i > to_y ;i-- ){
					if(black_man == board[i][from_x] || black_king == board[i][from_x])
						count++;
				}
		}
	}
	if(black_king == board[from_y][from_x]){
		if(from_y - to_y == 0){
			if(to_x > from_x)
				for( i = from_x + 1; i < to_x ;i++ ){
					if(white_man == board[from_y][i] || white_king == board[from_y][i])
						count++;
				}
			else
				for( i = from_x -1; i > to_x ;i-- ){
					if(white_man == board[from_y][i] || white_king == board[from_y][i])
						count++;
				}
		}
		else if(from_x - to_x == 0){
			if(to_y > from_y)
				for( i = from_y + 1; i < to_y ;i++ ){
					if(white_man == board[i][from_x] || white_king == board[i][from_x])
						count++;
				}
			else
				for( i = from_y - 1; i > to_y ;i-- ){
					if(white_man == board[i][from_x] || white_king == board[i][from_x])
						count++;
				}
		}
	}
	if(count == 1)
		return 1;
	else 
		return 0;
}
int wrong_player(piece board[][BRD_SIZE],int from_x,int from_y,player p)
{
	if(p == 20 && (white_man == board[from_y][from_x] || white_king == board[from_y][from_x]))
		return 1;
	else if(p == 10 && (black_man == board[from_y][from_x] || black_king == board[from_y][from_x]))
		return 1;
	else 
		return 0;
}
int move_not_allowed(piece board[][BRD_SIZE],int from_x,int from_y,int to_x,int to_y)
{
	if(!isEmpty(board,to_x,to_y)){
		return 1;
	}
	else if(isBack(board,from_x,from_y,to_x,to_y)){
		return 1;
	}
	else if(isCross(from_x,from_y,to_x,to_y)){
		return 1;
	}
	else 
		return 0;
}
int isEmpty(piece board[][BRD_SIZE],int to_x,int to_y)
{
	if(board[to_y][to_x] == empty)
		return 1;
	else
		return 0;
}
int isBack(piece board[][BRD_SIZE],int from_x,int from_y,int to_x,int to_y)
{
	if(white_man == board[from_y][from_x] && to_y > from_y)/*white man back*/
		return 1;
	else if(black_man == board[from_y][from_x] && to_y < from_y)/*black man back*/
		return 1;
	else
		return 0;
}
int isCross(int from_x,int from_y,int to_x,int to_y)
{
	if(0 == absolute(from_y - to_y) - absolute(from_x - to_x))
		return 1;
	else 
		return 0;
}
int isMan(piece board[][BRD_SIZE],int from_x,int from_y)
{
	if(white_man == board[from_y][from_x] || black_man == board[from_y][from_x])
		return 1;
	else 
		return 0;
}
int howMuchTile(int from_x,int from_y,int to_x,int to_y)
{
	return absolute(from_y - to_y) + absolute(from_x - to_x);
}
void goStraight(piece board[][BRD_SIZE],int from_x,int from_y,int to_x,int to_y)
{
	board[to_y][to_x] = board[from_y][from_x];
	board[from_y][from_x] = empty;	
}
int captureMan(piece board[][BRD_SIZE],int from_x,int from_y,int to_x,int to_y)
{
		if(checkMan(board,from_x,from_y) == 1 && toWhere(from_x,from_y,to_x,to_y) == 1){	
			board[from_y - 1][from_x] = empty;
			board[from_y][from_x] = empty;
			board[to_y][to_x] = white_man;
		}
		else if(checkMan(board,from_x,from_y) == 2 && toWhere(from_x,from_y,to_x,to_y) == 3){
			board[from_y][from_x - 1] = empty;
			board[from_y][from_x] = empty;
			board[to_y][to_x] = white_man;
		}
		else if(checkMan(board,from_x,from_y) == 3 && toWhere(from_x,from_y,to_x,to_y) == 4){
			board[from_y][from_x + 1] = empty;
			board[from_y][from_x] = empty;
			board[to_y][to_x] = white_man;
		}
		else if(checkMan(board,from_x,from_y) == 4 && toWhere(from_x,from_y,to_x,to_y) == 2){
			board[from_y + 1][from_x] = empty;
			board[from_y][from_x] = empty;
			board[to_y][to_x] = black_man;
		}
		else if(checkMan(board,from_x,from_y) == 5 && toWhere(from_x,from_y,to_x,to_y) == 3){
			board[from_y][from_x - 1] = empty;
			board[from_y][from_x] = empty;
			board[to_y][to_x] = black_man;
		}
		else if(checkMan(board,from_x,from_y) == 6 && toWhere(from_x,from_y,to_x,to_y) == 4){
			board[from_y][from_x + 1] = empty;
			board[from_y][from_x] = empty;
			board[to_y][to_x] = black_man;
		}
		else 
			return -2;
		return 0;
}
int toWhere(int from_x,int from_y,int to_x,int to_y)
{
	if(to_y < from_y && to_x == from_x)/*up*/
		return 1;
	else if(to_y > from_y && to_x == from_x)/*down*/
		return 2;
	else if(to_y == from_y && to_x < from_x)/*left*/
		return 3;
	else if(to_y == from_y && to_x > from_x)/*right*/
		return 4;
	else 
		return 0;
}
int checkMan(piece board[][BRD_SIZE],int from_x,int from_y)
{
	if(white_man == board[from_y][from_x]){
		if(from_y > 1 && (board[from_y - 1][from_x] == black_man || board[from_y - 1][from_x] == black_king)){
			return 1;
		}
		else if(from_x > 1 && (board[from_y][from_x - 1] == black_man || board[from_y][from_x - 1] == black_king)){
			return 2;
		}
		else if(from_x < 6 && (board[from_y][from_x + 1] == black_man || board[from_y][from_x + 1] == black_king)){
			return 3;
		}
		else
			return 0;
	}
	else if(black_man == board[from_y][from_x]){
		if(from_y < 6 && (board[from_y + 1][from_x] == white_man || board[from_y + 1][from_x] == white_king)){
			return 4;
		}
		else if(from_x > 1 && (board[from_y][from_x - 1] == white_man || board[from_y][from_x - 1] == white_king)){
			return 5;
		}
		else if(from_x < 6 && (board[from_y][from_x + 1] == white_man || board[from_y][from_x + 1] == white_king)){
			return 6;
		}
		else
			return 0;
	}
	else 
		return 0;

}
void becomingKing(piece board[][BRD_SIZE],player p)
{
	int i,j;
	if(p == white)
		i = 0;
	else
		i = 7;
	if(i == 0)/*white man becomes king*/
		for(j = 0;j < BRD_SIZE ; j++)
			if(board[i][j] == white_man)
				board[i][j] = white_king;
	else
		for(j = 0;j < BRD_SIZE ; j++)
			if(board[i][j] == black_man)
				board[i][j] = black_king;		
}
int controlWhereMan(piece board[][BRD_SIZE],int *from_x,int *from_y,int *to_x,int *to_y)
{
	*from_y = *to_y;
	*from_x = *to_x;
	if(white_man == board[*to_y][*to_x]){
		if(*to_y > 1 && (board[*to_y - 1][*to_x] == black_man || board[*to_y - 1][*to_x] == black_king)){
			*to_y = *to_y - 2;
			if(isEmpty(board,*to_x,*to_y))
				return 1;
			else 
				return 0;
		/*up for white*/
		}	
		else if(*to_x > 1 && (board[*to_y][*to_x - 1] == black_man || board[*to_y][*to_x - 1] == black_king)){
			*to_x = *to_x - 2;
			if(isEmpty(board,*to_x,*to_y))
				return 1;
			else 
				return 0;
		/*left for white*/	
		}
		else if(*to_x < 6 && (board[*to_y][*to_x + 1] == black_man || board[*to_y][*to_x + 1] == black_king)){
			*to_x = *to_x + 2;
			if(isEmpty(board,*to_x,*to_y))
				return 1;
			else 
				return 0;
		}
		else 
			return 0;
	}
	else if(black_man == board[*to_y][*to_y]){
		if(*to_y < 6 && (board[*to_y + 1][*to_x] == white_man || board[*to_y + 1][*to_x] == white_king)){
			*to_y = *to_y + 2;
			if(isEmpty(board,*to_x,*to_y))
				return 1;
			else 
				return 0;
			/*down for black*/
		}
		else if(*to_x > 1 && (board[*to_y][*to_x - 1] == white_man || board[*to_y][*to_x - 1] == white_king)){
			*to_x = *to_x - 2;
			if(isEmpty(board,*to_x,*to_y))
				return 1;
			else 
				return 0;
			/*left for black*/
		}
		else if(*to_x < 6 && (board[*to_y][*to_x + 1] == white_man || board[*to_y][*to_x + 1] == white_king)){
			*to_x = *to_x + 2;
			if(isEmpty(board,*to_x,*to_y))
				return 1;
			else 
				return 0; 
			/*right for black*/
		}
		else 
			return 0;
	}
	else 
		return 0;
}