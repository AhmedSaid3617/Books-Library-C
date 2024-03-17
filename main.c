#include <stdio.h>
#define MAX_BOOKS 100
#define MAX_NAME_LENGTH 100

// Data for books.
char names[MAX_BOOKS][MAX_NAME_LENGTH];
char authors[MAX_BOOKS][MAX_NAME_LENGTH];
int bookIds[MAX_BOOKS];
float prices[MAX_BOOKS];


char password[MAX_NAME_LENGTH]; 
char triedPassword[MAX_NAME_LENGTH]; // Input password to compare every time.
char availability[MAX_BOOKS]; // Each element is either 0 (free space) or 1 (occupied).

void setPassword();
int checkPassword();
int findIndex();
int addBook();
int deleteBook();
int viewBooks();


int main()
{
	char choice;
	

	printf("----------------------------------------------------- Welcome to your library -----------------------------------------------------\n\n\n");
	
	setPassword();

	while (1)
	{
		printf("Choose (1) to add a book\n");
		printf("Choose (2) to deleta a book\n");
		printf("Choose (3) to veiw books in the system\n");
		printf("Choose (4) to close the program\n");
		printf("Your choice is: ");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			addBook();
			break;
		
		case 2:
			deleteBook();
			break;
		
		case 3:
			viewBooks();
			break;
		
		case 4:
		return 0;

		default:
			printf("Enter a Valid choice!\n\n");
		}
	}

	return 0;
}

// Stores set password in password.
void setPassword()
{
	printf("Create your password:\n");
	scanf("%s", password);
	printf("Your password is %s\n", password);
}

// Checks if input password is the same as the one in password.
int checkPassword(){
	printf("Enter password: \n");
	scanf("%s", triedPassword);
	for (int i=0; i<MAX_NAME_LENGTH; i++){
		if (triedPassword[i] != password[i]){
			printf("Wrong password.\n");
			return 0;
		}
	}
	return 1;
}

// Finds the closest free index in availability array, to keep memory efficient.
int findIndex(){
	for (int i = 0; i < MAX_BOOKS; i++)
	{
		if (availability[i] == 0){
			return i;
		}
	}
}

// Adds a book.
int addBook()
{
	// Check password first.
	if (!checkPassword()){
		return 0;
	}

	// Get index of free space.
	int bookIndex = findIndex();
	int bookId;
	char repeated;

	printf("Enter book name: ");
	getchar();
	gets(names[bookIndex]);
	printf("\n");

	printf("Enter author name: ");
	gets(authors[bookIndex]);
	printf("\n");

	// Keep looping until a unique id is entered.
	do
	{
		repeated = 0;
		printf("Enter book id: ");
		scanf("%d", &bookId);
		for(int i=0; i<MAX_BOOKS; i++){
			if (bookIds[i] == bookId)
			{
				printf("This id already exists.\n");
				repeated = 1;
				break;
			}
		}
	} while (repeated);
	

	bookIds[bookIndex] = bookId;
	printf("\n");

	printf("Enter book price: ");
	scanf("%f", &prices[bookIndex]);

	// Set as unavailable.
	availability[bookIndex] = 1;

	return 1;
}

int deleteBook(){

	// Check password first.
	if (!checkPassword()){
		return 0;
	}

	int bookId;
	printf("Enter book id: ");
	scanf("%d", &bookId);

	for(int i = 0; i<MAX_BOOKS; i++){
		if(bookIds[i] == bookId){
			availability[i] = 0; // Make this index available in all arrays.
			printf("The book \"%s\" was deleted.\n", names[i]);
			return 1;
		}
	}

	printf("Id %d does not exist, please enter a valid Id\n", bookId);
	return 0;
}

int viewBooks(){

	if (!checkPassword()){
		return 0;
	}

	printf("List of books\n");
	for (int i = 0; i < MAX_BOOKS; i++)
	{
		if (availability[i] == 1){
			printf("==================\n");
			printf("Name: %s\n", names[i]);
			printf("Author: %s\n", authors[i]);
			printf("Id: %d\n", bookIds[i]);
			printf("Price: %f\n", prices[i]);
		}
	}
	printf("===============\n");
}

