/*
NAME: Richard Miller	CS4350-Unix Systems Programming
Serial Number: 36

Group Number:

Assignment Number: 3

Due Date: 3/27/2019
*/

#include <stdio.h>

void encrypt(char* message, int key)
{
  int capitals = 0;
  printf("\nNumber of Capital Letters: %i", capitals);
  int lowerCase = 0;
  printf("\nNumber of Small Letters: %i", lowerCase);
  int digitCount = 0;
  printf("\nNumber of Digits: %i", digitCount);
  int symbols = 0;
  printf("\nNumber of Symbols: %i", symbols);
  int numChar = 0;
  printf("\nNumber of Characters in the message: %i", numChar);
  char lowerCaseMessage[255] = "lowercase message";
  printf("\nConverting Letters: %s", lowerCaseMessage);
  char encrypted[255] = "encrypted";
  printf("\nThe decrypted text is:\n%s\n", encrypted);
  char combo[255] = "combo";
  printf("Concatenation of original and encrypted text: %s\n\n", combo);
}

void decrypt(char* message, int key)
{
  int capitals = 0;
  printf("\nNumber of Capital Letters: %i", capitals);
  int lowerCase = 0;
  printf("\nNumber of Small Letters: %i", lowerCase);
  int digitCount = 0;
  printf("\nNumber of Digits: %i", digitCount);
  int symbols = 0;
  printf("\nNumber of Symbols: %i", symbols);
  int numChar = 0;
  printf("\nNumber of Characters in the message: %i", numChar);
  char lowerCaseMessage[255] = "lowercase message";
  printf("\nConverting Letters: %s", lowerCaseMessage);
  char decrypted[255] = "encrypted";
  printf("\nThe encrypted text is:\n%s\n", decrypted);
  char combo[255] = "combo";
  printf("Concatenation of original and encrypted text: %s\n\n", combo);
}

int validate(char* choice, int key)
{
}

int main()
{
	/*
	int input, temp, status;

	printf("Please enter a number: ");
	status = scanf("%d", &input);
	while (status != 1) {
		while ((temp = getchar()) != EOF && temp != '\n');
		printf("Invalid input... please enter a number: ");
		status = scanf("%d", &input);
	}

	printf("Your number is %d\n", input);
  */

  int keepLooping = 1;
  printf("Welcome to cryptography\n\n");
  while(keepLooping == 1)
  {
	char choice[255];
	char message[255];
	char encrypt[] = "encrypt";
	char decrypt[] = "decrypt";
	char exit[] = "exit";
	int key;
	int status;
	int temp;
	int isEncrypt;
	int isDecrypt;
	int isExit;
	

    printf("What would you like to do to a message?(encrypt, decrypt, exit)\nEnter your choice: ");
	status = scanf("%s", &choice);
	while (status != 1)
	{
		while ((temp = getchar()) != EOF && temp != '\n');
		printf("What would you like to do to a message?(encrypt, decrypt, exit)\nEnter your choice: ");
		status = scanf("%s", &choice);
	}

    printf("Enter your message:\n");
	status = scanf("%s", &message);
	while (status != 1)
	{
		while ((temp = getchar()) != EOF && temp != '\n');
		printf("What would you like to do to a message?(encrypt, decrypt, exit)\nEnter your choice: ");
		status = scanf("%s", &message);
	}

    printf("Enter the key number(1-95)\n");
	status = scanf("%d", &key);
	while (status != 1)
	{
		while ((temp = getchar()) != EOF && temp != '\n');
		printf("What would you like to do to a message?(encrypt, decrypt, exit)\nEnter your choice: ");
		status = scanf("%d", &key);
	}
	
	for (int i = 0; i < 7; i++)
		if (choice[i] != encrypt[i])
			int isEncrypt = 0;
	for (int i = 0; i < 7; i++)
		if (choice[i] != decrypt[i])
			int isDecrypt = 0;
	for (int i = 0; i < 4; i++)
		if (choice[i] != exit[i])
			int isExit = 0;

    if(isEncrypt == 1)
      encrypt(message, key);
    else if(isDecrypt == 1)
      decrypt(message, key);
    else if(isExit == 1)
      keepLooping = 0;
  }
  printf("Richard Miller Security Systems\n3-27-2019");
  
}