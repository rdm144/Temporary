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

int validateChoice(char* choice)
{
  if(scanf("%s", choice) != 1 || (choice != "encrypt" && choice != "decrypt" && choice != "exit"))
  {
    printf("Invalid message");
    return 0;
  }
  else
    return 1;
}

int validateKey(int key)
{
  if(key < 1 || key > 95)
    return 0;
  else
    return 1;
}

int main()
{
  int keepLooping = 1;
  printf("Welcome to cryptography\n\n");
  while(keepLooping == 1)
  {
    int valid = 0;
    printf("What would you like to do to a message?(encrypt, decrypt, exit)\nEnter your choice: ");
    char choice[255]; valid = validateChoice(choice);
    printf("Enter your message:\n");
    char message[255]; scanf("%s", message);
    printf("Enter the key number(1-95)\n");
    int key; scanf("%d", &key);
    if(choice == "encrypt")
    {
      encrypt(message, key);
    }
    else if(choice == "decrypt")
    {
      decrypt(message, key);
    }
    else if(choice == "exit")
    {
      keepLooping = 0;
    }
    else
    {
      
    }
  }
  printf("Richard Miller Security Systems\n3-27-2019");
}
