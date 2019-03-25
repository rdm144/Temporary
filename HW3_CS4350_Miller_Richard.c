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

int validate(int which)
{
	char en[] = "encrypt";
	char de[] = "decrypt";
	char ex[] = "exit";

	char temp;
	switch (which)
	{
	case 1:
		int status = scanf("%s", &choice);
		while ((temp = getchar()) != EOF && temp != '\n');

		if (status != 1)
		{
			printf("Invalid message\n");
			return 0;
		}

		for (int i = 0; i < 7; i++)
			if (choice[i] != en[i])
				isEncrypt = 0;
		for (int i = 0; i < 7; i++)
			if (choice[i] != de[i])
				isDecrypt = 0;
		for (int i = 0; i < 4; i++)
			if (choice[i] != ex[i])
				isExit = 0;
		if (isEncrypt == 0 && isDecrypt == 0 && isExit == 0)
			return 0;
		else
			return 1
			break;
	case 2:
		int status = scanf("%d", &key);
		while ((temp = getchar()) != EOF && temp != '\n');
		if (status != 1)
		{
			printf("Invalid message\n");
			return 0;
		}
		if (key < 1 || key > 95)
			return 0;
		else
			return 1;
		break;
	}
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
	while (keepLooping == 1)
	{
		char choice[255];
		char message[255];

		int key;
		int status;
		int temp;
		int isEncrypt;
		int isDecrypt;
		int isExit;
		isEncrypt = 1;
		isDecrypt = 1;
		isExit = 1;

		printf("What would you like to do to a message?(encrypt, decrypt, exit)\nEnter your choice: ");
		if (validate(1) != 1)
			continue;

		printf("Enter your message:\n");

		printf("Enter the key number(1-95)\n");
		if (validate(2) != 1)
			continue;

		if (isEncrypt == 1)
			encrypt(message, key);
		else if (isDecrypt == 1)
			decrypt(message, key);
		else if (isExit == 1)
			keepLooping = 0;
	}
	printf("Richard Miller Security Systems\n3-27-2019");

}