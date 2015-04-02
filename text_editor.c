#include <stdio.h>

char NAME_FILE[30];

unsigned short int menu(void);
void get_name_file(char NAME_FILE[]);
FILE *open_file();
void read_file(FILE *file);
void file_table(FILE *file);
void write_file(FILE *file);

void main(void){
	unsigned short int quit =0;
	do{
		switch (menu()){
			case 1:
				get_name_file(NAME_FILE);
				file_table(open_file());
				break;
			case 2:
			default:
				quit =1; //Exit and close program
		};
	} while(!quit);
};

//Show menu
//Return the choice
unsigned short int menu(void){
	unsigned short int choice;

	system("clear");
	printf("\n");
	printf("TEXT EDITOR\n");
	printf("============================\n");
	printf("1: Open file\n");
	printf("2: Exit\n");
	printf("============================\n");
	printf("Make a choice: ");
	scanf("%hu", &choice);
	return choice;
};

//Receive address to string
//Get file name 
void get_name_file(char NAME_FILE[]){
	printf("\nEnter the name for file:");
	scanf(" %[A-Z a-z.0-9]", NAME_FILE);
	printf("\n%s\n", NAME_FILE);
};

//Open or Create a file named 'fileName.
//Return memory address of the file, or NULL case of error
FILE *open_file(){
	FILE *file;

	if((file = fopen(NAME_FILE, "a")) == NULL){
		perror("error: ");
		return NULL;
	};
	return file;
};

//Read and print file
void read_file(FILE *file){
	char ch;
	rewind(file);
	if((file = fopen(NAME_FILE, "r+")) == NULL){
		perror("error: ");
	};
	ch = getc(file);
	while(ch != EOF){
		putchar(ch);
		ch = getc(file);
	};
};

//Write text to new file or file existence
void write_file(FILE *file){
	long int pos_temp; /*Temporary index position of the file*/
	char ch;

	do{
		ch = getchar();
		putc(ch, file);
	}while(ch != 7);
	pos_temp = ftell(file); /*Receive current position*/
	fseek(file, pos_temp-1, SEEK_SET); /*Move index to two previous bytes*/
	putc(EOF, file); /*Remove o character 'CTRL+G' (7 in decimal)*/
	// putc(' ', file); /*Remove o character 'CTRL+G' (7 in decimal)*/
	// putc(' ', file); /*Remove o character '\n'*/
};

//Print table and call read_file and  write_file
void file_table(FILE *file){
	system("clear");
	printf("File: %-10s\t\t[take CRTL+G for exit and save]\n", NAME_FILE);
	printf("==============================================================="); //beginning of the file
	if(!ftell(file))
		printf("\n");
	read_file(file);
	write_file(file);
	fclose(file);
};
	
