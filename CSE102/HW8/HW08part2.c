#include <stdio.h>

char * find_operations(int arr[],int expected_val,char operations[],size_t arr_len,int cursor,int current);

int main()
{
	int arr[] = {25,12,6,10,32,8};
	char op[]=" ";
	printf("Operation sequence should be :\n%s\n",find_operations(arr,44,op,6,0,0));

	return 0;
}
char * find_operations(int arr[],int expected_val,char operations[],size_t arr_len,int cursor,int current)
{ 
	int i;
	if(cursor == 0){
		current = arr[0];					/*Assigns operations[arrlen - 1] for later usage control*/
		operations[arr_len - 1] = '1';
	}
	if(current == expected_val && cursor == arr_len - 1){
		operations[arr_len - 1] = 0;						/*If expected value is found return*/
		return operations;
	}
	else if(cursor < (arr_len - 1)){/*Recursive part of the function*/
		if(operations[arr_len - 1] != 0){
			operations[cursor] = '+';
			find_operations(arr,expected_val,operations,arr_len,cursor+1,current+arr[cursor+1]);	
		}
		if(operations[arr_len - 1] != 0){
			operations[cursor] = '-';
			find_operations(arr,expected_val,operations,arr_len,cursor+1,current-arr[cursor+1]);
		}
		if(operations[arr_len - 1] != 0){
			operations[cursor] = '*';
			find_operations(arr,expected_val,operations,arr_len,cursor+1,current*arr[cursor+1]);
		}
	}
	if(cursor == 0 && operations[arr_len - 1] == '1'){
		for(i = 0; i < arr_len-1;i++)
			operations[i] = ' ';			/*If expected value is not possible return n - 1 spaces*/
		operations[arr_len-1] = 0;
		return operations;
	}
	else
		return operations;
}