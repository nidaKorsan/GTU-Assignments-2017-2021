/*
	24/05/2018
	**** Booking Program for a hotel ****
	171044016
	Nida Korsan
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
typedef struct Customer{
	struct Customer * nextCustomer;
	char name[20];
	char surname[20];
	int age;
	char gender[10];
}Customer;
typedef struct Room{
	struct Room * nextRoom;
	int number;
	int capacity;
	int flor;
	Customer * customer;
}Room;

void init(Room * roomList);
void menu(Room * roomList);
	void add_room_to_end(Room * roomList,Room tmp);
	void add_room_after_room_number(Room * roomList,Room tmp,int afterRoom);
	void link_customers_to_room(Room * roomList,Customer tmp,int tmpRoom);
		void add_customer_to_end(Customer * customerList,Customer tmp);
	void remove_room(Room * roomList,int roomNum);
		Room * removeFirstRoom(Room * roomList,int roomNum);
		void freeCustomer(Customer * customer);
	void show_vacancy(Room * roomList);
	void get_by_floor(Room * roomList,int florNum);
	void print_list(Room * roomList);
void freeAll(Room * roomList);

int main()
{
	Room * roomList = (Room *)malloc(sizeof(Room));
	init(roomList);
	menu(roomList);
	freeAll(roomList);
	
	return 0;
}
void init(Room * roomList)/*Initiliazes the list while reading from file*/
{
	FILE * fr;
	FILE *fc;
	Room tmp;
	Customer tmp2;
	int i = 0,j,tmpRoom;
	fr = fopen("rooms.txt","r");
	fc = fopen("customers.txt","r");
	/*Reads rooms from fileinto a temporary variable then makes a linked list.*/
	fscanf(fr,"%d,%d,%d",&roomList->number,&roomList->capacity,&roomList->flor);
	roomList->customer = 0;
	roomList->nextRoom = 0;
	while(!feof(fr)){
		fscanf(fr,"%d,%d,%d",&tmp.number,&tmp.capacity,&tmp.flor);
		add_room_to_end(roomList,tmp);
	}
	/*Reads customers from file into a temporary variable*/	
	while(!feof(fc)){
		fscanf(fc,"%d,%s ",&tmpRoom,tmp2.name);
		j = -1;
		do{
			j++;
			tmp2.surname[j] = fgetc(fc);
		}while(tmp2.surname[j] != ',');
		tmp2.surname[j] = 0;
		fscanf(fc,"%d,%s",&tmp2.age,tmp2.gender);
		link_customers_to_room(roomList,tmp2,tmpRoom);
		/*printf("na: %s sur: %s age: %d gen: %s\n", tmp2.name,tmp2.surname,tmp2.age,tmp2.gender);*/
		i++;
	}
	fclose(fr);
	fclose(fc);
}
void menu(Room * roomList)/*To apply certain operations*/
{
	int choice,roomNum,florNum;
	Room tmp;
	Customer tmpC;
	printf("WELCOME TO THIS HOTEL!\n");
	do{
		printf("\nWhat would you like to do?\n\n");
		printf("1. Add room to the end\n");
		printf("2. Add room after room number\n");
		printf("3. Add customer to the room\n");
		printf("4. Remove room\n");
		printf("5. Show vacancy\n");
		printf("6. Show by floor number\n");
		printf("7. Show room list\n");
		printf("0. Exit\n");
		printf("\t\tChoice: ");
		scanf("%d",&choice);
		printf("\n");
		switch(choice){
			case 1:
				printf("Room number: ");
				scanf("%d",&tmp.number);
				printf("Room capacity: ");
				scanf("%d",&tmp.capacity);
				printf("Floor: ");
				scanf("%d",&tmp.flor);
				add_room_to_end(roomList,tmp);
				break;
			case 2:
				printf("Room number: ");
				scanf("%d",&tmp.number);
				printf("Room capacity: ");
				scanf("%d",&tmp.capacity);
				printf("Floor: ");
				scanf("%d",&tmp.flor);
				printf("After which room? : ");
				scanf("%d",&roomNum);
				add_room_after_room_number(roomList,tmp,roomNum);
				break;
			case 3:
				printf("Room number: ");
				scanf("%d",&roomNum);
				printf("Name: ");
				scanf("%s",tmpC.name);
				printf("Surname: ");
				scanf("%s",tmpC.surname);
				printf("Age: ");
				scanf("%d",&tmpC.age);
				printf("Gender(Male/Female): ");
				scanf("%s",tmpC.gender);
				link_customers_to_room(roomList,tmpC,roomNum);
				break;
			case 4:
				printf("Enter room number you'd like to remove: ");
				scanf("%d",&roomNum);
				if(roomList->number == roomNum){
					roomList = removeFirstRoom(roomList,roomNum);
				}
				else{
					remove_room(roomList,roomNum);
				}
				break;
			case 5:
				show_vacancy(roomList);
				break;
			case 6:
				printf("Enter the floor: ");
				scanf("%d",&florNum);
				get_by_floor(roomList,florNum);
				break;
			case 7:
				print_list(roomList);
			case 0:
				break;
			default:
				printf("Wrong choice! Choose again.\n");
		}

	}while(choice != 0);
	printf("GOODBYE!\n");
}
void add_room_to_end(Room * roomList,Room tmp)/*Recursively goes to end of the list and adds new room*/
{
	if(roomList->nextRoom == 0){
		roomList->nextRoom = (Room *)malloc(sizeof(Room));
		roomList->nextRoom->nextRoom = 0;
		roomList->nextRoom->number = tmp.number;
		roomList->nextRoom->capacity = tmp.capacity;
		roomList->nextRoom->flor = tmp.flor;
		roomList->nextRoom->customer = 0;
		return;
	}
	else
		add_room_to_end(roomList->nextRoom,tmp);
}
void add_room_after_room_number(Room * roomList,Room tmp,int afterRoom)/*Recursively goes to the room which has the number given 
and adds the new room after it. If there is not such a room, adds to the end of the list*/
{
	Room * tmp1;

	if(roomList->number == afterRoom){
		tmp1 = roomList->nextRoom;
		roomList->nextRoom = (Room *)malloc(sizeof(Room));
		roomList->nextRoom->nextRoom = tmp1;
		roomList->nextRoom->number = tmp.number;
		roomList->nextRoom->capacity = tmp.capacity;
		roomList->nextRoom->flor = tmp.flor;
		roomList->nextRoom->customer = 0;
		return;
	}
	if(roomList->nextRoom == 0){
		printf("\nThere is not a room has the number %d.Added to the end.\n",afterRoom);
		add_room_to_end(roomList,tmp);
	}
	else
		add_room_after_room_number(roomList->nextRoom,tmp,afterRoom);
}
void add_customer_to_end(Customer * customerList,Customer tmp)
{
	if(customerList->nextCustomer == 0){
		customerList->nextCustomer = (Customer *)malloc(sizeof(Customer));
		customerList->nextCustomer->nextCustomer = 0;
		strcpy(customerList->nextCustomer->name,tmp.name);
		strcpy(customerList->nextCustomer->surname,tmp.surname);
		customerList->nextCustomer->age = tmp.age;
		strcpy(customerList->nextCustomer->gender,tmp.gender);
		return;
	}
	else
		add_customer_to_end(customerList->nextCustomer,tmp);
}
void link_customers_to_room(Room * roomList,Customer tmp,int tmpRoom)
{
	if(roomList->number == tmpRoom){
		if(roomList->customer == 0){
			roomList->customer = (Customer *)malloc(sizeof(Customer));
			roomList->customer->nextCustomer = 0;
			strcpy(roomList->customer->name,tmp.name);
			strcpy(roomList->customer->surname,tmp.surname);
			roomList->customer->age = tmp.age;
			strcpy(roomList->customer->gender,tmp.gender); 
		}
		else
			add_customer_to_end(roomList->customer,tmp);
	}
	else
		link_customers_to_room(roomList->nextRoom,tmp,tmpRoom);
}
Room * removeFirstRoom(Room * roomList,int roomNum)/*A special function to remove first room*/
{
	Room * tmp;
	tmp = roomList->nextRoom;
	freeCustomer(roomList->customer);
	free(roomList);
	roomList = tmp;
	return roomList;	
}
void remove_room(Room * roomList,int roomNum)
{
	Room * tmp;
	while(roomList->nextRoom->number != roomNum)/*Find the room node which equals to room number given.*/
		roomList = roomList->nextRoom;
	if(roomList->nextRoom->nextRoom != 0){/*If it's not the last free*/
	tmp = roomList->nextRoom;
	roomList->nextRoom = tmp->nextRoom;
	freeCustomer(tmp->customer);
	free(tmp);
	}
	else{/*If it's last free*/
		freeCustomer( roomList->nextRoom->customer);
		free( roomList->nextRoom);
		roomList->nextRoom = 0;
	}
}
void freeCustomer(Customer * customer)
{
	if(customer == 0)
		return;
	if(customer->nextCustomer == 0){
		free(customer);
		return;
	}
	else{
		freeCustomer(customer->nextCustomer);
		free(customer);
	}
}
void show_vacancy(Room * roomList)
{
	if(roomList == 0)
		return;
	if(roomList->customer == 0)
		printf("Room %d is empty\n",roomList->number);
	show_vacancy(roomList->nextRoom);
}
void get_by_floor(Room * roomList,int florNum)
{
	if(roomList == 0)
		return;
	if(roomList->flor == florNum)
		printf("Room %d\n",roomList->number);
	get_by_floor(roomList->nextRoom,florNum);	
}
void print_list(Room * roomList)
{
	Customer * tmp;
	if(roomList == 0){
		return;
	}
	tmp  = roomList->customer;
	printf("Room %d(Floor %d – capacity %dx):\n",roomList->number,roomList->flor,roomList->capacity);
	if(tmp == 0){
		printf("->Empty\n");
		printf("\n");
	}
	else{
		while(tmp != 0){
			printf("-> %s %s(%d – %s)\n",tmp->name,tmp->surname,tmp->age,tmp->gender);
			tmp = tmp->nextCustomer;
		}
		printf("\n");
	}
	print_list(roomList->nextRoom);	
}
void freeAll(Room * roomList)/*Frees all taken addresses*/
{
	if(roomList->nextRoom == 0){
		freeCustomer(roomList->customer);
		free(roomList);
		return;
	}
	freeAll(roomList->nextRoom);
	freeCustomer(roomList->customer);
	free(roomList);
}