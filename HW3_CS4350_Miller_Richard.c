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
	int key = 1;

    printf("What would you like to do to a message?(encrypt, decrypt, exit)\nEnter your choice: ");
	scanf("%s", choice);

    printf("Enter your message:\n");
	scanf("%s", message);

    printf("Enter the key number(1-95)\n");
	scanf("%d", key);

    if(choice == "encrypt")
      encrypt(message, key);
    else if(choice == "decrypt")
      decrypt(message, key);
    else if(choice == "exit")
      keepLooping = 0;
  }
  printf("Richard Miller Security Systems\n3-27-2019");
  
}