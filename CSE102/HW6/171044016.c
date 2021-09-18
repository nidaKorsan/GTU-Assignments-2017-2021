#include <stdio.h>
#define CHR_LNG 1024
void menu();
void encrypt_open_msg();
void decrypt_secret_msg();
void keyValue(int *key);
int find_size_of_line(char line[]);
void reverse_line(char line[],int line_length);
void write(char line[][CHR_LNG],char fileName[]);
void read(char line[][CHR_LNG],char fileName[]);
int main()
{
	menu();
	return 0;
}
void menu()
{
	int choice;
	do{
		printf("1. Encrypt\n2. Decrypt\n0. Exit\nChoice: ");
		scanf("%d",&choice);
		switch(choice){
			case 1:
				encrypt_open_msg();
				break;
			case 2:
				decrypt_secret_msg();
				break;
		}
	}while(choice != 0);
}
void encrypt_open_msg()
{	
	char myStr[CHR_LNG][CHR_LNG];
	int key,j,i = 0;
	read(myStr,"open_msg.txt");
	keyValue(&key);
	for(i = 0; myStr[i][0] != 0; i++){
		for(j = 0; myStr[i][j] != 0;j++){
			if(myStr[i][j] == ' ')
				myStr[i][j] = '_';
			else if(myStr[i][j] == '.')
				myStr[i][j] = '*';
			else if(myStr[i][j] != '\n'){
				myStr[i][j] -= key;
				if(myStr[i][j] < 97){
					myStr[i][j] += 26;
				}
			}
		}
		printf("%s",myStr[i]);
	}
	printf("\n");
	write(myStr,"secret_msg.txt");
}
void decrypt_secret_msg()
{
	char myStr[CHR_LNG][CHR_LNG];
	int key,j,i = 0;
	read(myStr,"secret_msg.txt");
	keyValue(&key);
	for(i = 0; myStr[i][0] != 0; i++){
		for(j = 0; myStr[i][j] != 0;j++){
			if(myStr[i][j] == '_')
				myStr[i][j] = ' ';
			else if(myStr[i][j] == '*')
				myStr[i][j] = '.';
			else if(myStr[i][j] != '\n'){
				myStr[i][j] += key;
				if(myStr[i][j] > 122){
					myStr[i][j] -= 26;
				}
			}
		}
		printf("%s",myStr[i]);
	}
	printf("\n");
	write(myStr,"open_msg.txt");
}
void reverse_line(char line[],int line_length)
{
	char tmp;
	int i;
	for(i = 0; i < line_length / 2 ;i++){
		tmp = line[i];
		line[i] = line[line_length - i];
		line[line_length - i] = tmp;
	}
}
int find_size_of_line(char line[])
{
	int i;
	for(i = 0; line[i] != '\n' && line[i] != 0 ; i++);
		
	return i - 1;
}
/*This function takes key value from the user*/
void keyValue(int *key)
{
	do{
		printf("Key: ");
		scanf("%d",key);
	}while(*key < 1 || *key > 26);
}
/*Writing into the file,expects the text and file name*/
void write(char line[][CHR_LNG],char fileName[])
{
	int i=0;
	FILE *fin;
	fin = fopen(fileName,"w");
	if(fin == 0)
		printf("Can't open the file\n");
	do{
		fprintf(fin, "%s",line[i]);
	}while(line[i++][0] != 0);
	fclose(fin);
}
void read(char line[][CHR_LNG],char fileName[])
{
	FILE *fp;
	int i = 0;
	fp = fopen(fileName,"r");
	if(fp == 0){
		printf("Can't open the file\n");
	}
	do{
		fgets(line[i],CHR_LNG,(FILE*)fp);
		reverse_line(line[i],find_size_of_line(line[i]));
	}while(line[i++][0] != 0);
	printf("\n");
	fclose(fp);
}