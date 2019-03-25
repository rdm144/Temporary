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
  if(choice == "\0")
	if(scanf("%s", choice) != 1)
	{
	  printf("Invalid message");
	  return 0;
	}
  if(choice != "encrypt" && choice != "decrypt" && choice != "exit")
  {
    printf("Invalid message");
    return 0;
  }
  if (key == -1)
    if (scanf("%s", choice) != 1)
    {
      printf("Invalid key");
	  return 0;
	}
  if (key < 1 || key > 95)
  {
	printf("Invalid Key");
	return 0;
  }
  return 1;
}

int main()
{
	char thing[255];
	printf("enter a thing ");
	scanf("%s", thing);
  /*
  int keepLooping = 1;
  printf("Welcome to cryptography\n\n");
  while(keepLooping == 1)
  {
	char choice[255] = "\0";
	char message[255];
	int key = 1;

    printf("What would you like to do to a message?(encrypt, decrypt, exit)\nEnter your choice: ");
	if (validate(choice, key) != 1)
	  continue;

    printf("Enter your message:\n");
	scanf("%s", message);

	key = -1;
    printf("Enter the key number(1-95)\n");
	if (validate(choice, key) != 1)
		continue;

    if(choice == "encrypt")
      encrypt(message, key);
    else if(choice == "decrypt")
      decrypt(message, key);
    else if(choice == "exit")
      keepLooping = 0;
  }
  printf("Richard Miller Security Systems\n3-27-2019");
  */
}
