#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ARR_SIZE 1000000
#define SEC_MS 1000
typedef struct linkList{
	int num;
	struct linkList * next;
}linkList;
void readArr(char * fileName,int *arr);
void readList(char * fileName,linkList * list);
void freeEm(linkList * list);
void isPrmArr(int * arr,int num);
void isPrmList(linkList * list,int num);
void writeArr(int * arr);

int main()
{
	FILE *fin1,*fin2;
	double total,start,end,st1,en1,tot1,st2,en2,tot2;
	linkList * list = (linkList *)malloc(sizeof(linkList));
	int * arr = (int *)calloc(ARR_SIZE,sizeof(int));

	fin1 = fopen("output_prime_dynamic_array.txt","w");
	fin2 = fopen("output_prime_LiknedList.txt","w");
	/*2.a*/
	readList("data.txt",list);
		/*3.1*/
	start = (double)clock();
	isPrmList(list,500000);
	end = (double)clock();
	total = (end - start)/(double)CLOCKS_PER_SEC * SEC_MS;
	fprintf(fin2, "%.3f\n",total);
		/*3.2*/
	start = (double)clock();
	isPrmList(list,750000);
	end = (double)clock();
	total = (end - start)/(double)CLOCKS_PER_SEC * SEC_MS;
	fprintf(fin2, "%.3f\n",total);
		/*3.3*/
	start = (double)clock();
	isPrmList(list,1000000);
	end = (double)clock();
	total = (end - start)/(double)CLOCKS_PER_SEC * SEC_MS;
		/*4.1*/
	st1 = (double)clock();
	fprintf(fin2, "%.3f\n",total);
	en1 = (double)clock();
	tot1 = (en1 - st1) / (double)CLOCKS_PER_SEC * SEC_MS;
	/*2.b*/
	readArr("data.txt",arr);
		/*3.1*/	
	start = (double)clock();
	isPrmArr(arr,500000);
	end = (double)clock();
	total = (end - start) / (double)CLOCKS_PER_SEC * SEC_MS;
	fprintf(fin1, "%.3f\n",total);
		/*3.2*/
	start = (double)clock();
	isPrmArr(arr,750000);
	end = (double)clock();
	total = (end - start) / (double)CLOCKS_PER_SEC * SEC_MS;
	fprintf(fin1, "%.3f\n",total);
		/*3.3*/
	start = (double)clock();
	isPrmArr(arr,1000000);
	end = (double)clock();
	total = (end - start) / (double)CLOCKS_PER_SEC * SEC_MS;
		/*4.2*/
	st2 = (double)clock();
	fprintf(fin1, "%.3f\n",total);
	en2 = (double)clock();
	tot2 = (en2 - st2) / (double)CLOCKS_PER_SEC * SEC_MS;

	printf("Written time for linked list 1 - 1000000: %.3f ms\n",tot1);
	printf("Written time for dynamic array 1 - 1000000: %.3f ms\n",tot2);
	
	fclose(fin1);
	fclose(fin2);
	free(arr);
	freeEm(list);
	return 0;
}
void readArr(char * fileName,int *arr)/*Read the file and record the numbers into an array*/
{
	FILE *fr;
	int i;
	fr = fopen(fileName,"r");
	for(i = 0;i < 1000000 ;i++){
		fscanf(fr,"%d,00",&arr[i]);
	}
	fclose(fr);
}
void readList(char * fileName,linkList * list)/*Read the file and record the numbers into linked list*/
{
	FILE *fr;
	int i;
	fr = fopen(fileName,"r");
	fscanf(fr,"%d,00",&list->num);
	for(i = 1;i < 1000000 ;i++){
		list->next = (linkList *)malloc(sizeof(linkList));
		list->next->next = 0;
		fscanf(fr,"%d,00",&list->next->num);
		list = list->next;
	}
	fclose(fr);
}
void freeEm(linkList * list)/*This function frees the adresses for linked list*/
{
	int i;
	linkList * tmp;
	for(i = 0;i < 1000000;i++){
		tmp = list->next;
		free(list);
		list = tmp;
	}
}
void isPrmArr(int * arr,int num)/*Finds the prime numbers in an array*/
{
	int i,j,flag = 0,count = 0;
	printf("Prime numbers in array:\n");
	for(i = 0; i < num; i++,flag =0){
		for(j = 2; j <= arr[i] / 2 && flag != 1; j++){
			if(arr[i] % j == 0)
				flag = 1;				
		}
		if(arr[i] == 1)
			flag = 1;
		if(flag == 0){
			printf("%d\n",arr[i]);
			count++;
		}
	}
}
void isPrmList(linkList * list,int num)/*Finds the prime numbers in a linked list*/
{
	int i,j,flag = 0,count = 0;
	printf("Prime number in linked list\n");
	for(i = 0; i < num && list != 0; i++,flag =0){
		for(j = 2; j <= list->num / 2 && flag != 1; j++){
			if(list->num % j == 0)
				flag = 1;				
		}
		if(list->num == 1)
			flag = 1;
		if(flag == 0){
			printf("%d\n",list->num);
			count++;
		}
		list = list->next;

	}
}