/*
NAME: Richard Miller	CS4350-Unix Systems Programming
Serial Number: 36

Group Number:

Assignment Number: 3

Due Date: 3/27/2019
*/

#include <stdio.h>

void encrypt(char* message, int *key)
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

void decrypt(char* message, int *key)
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

int validate(char* c, int *k, int which)
{
	char en[] = "encrypt";
	char de[] = "decrypt";
	char ex[] = "exit";
	int isEncrypt = 1;
	int isDecrypt = 1;
	int isExit = 1;
	int status;
	char temp;
	switch (which)
	{
	case 1:
		status = scanf("%s", &c);
		while ((temp = getchar()) != EOF && temp != '\n');
		if (status != 1)
		{
			printf("Invalid message\n");
			return 0;
		}
		for (int i = 0; i < 7; i++)
			if (c[i] != en[i])
				isEncrypt = 0;
		for (int i = 0; i < 7; i++)
			if (c[i] != de[i])
				isDecrypt = 0;
		for (int i = 0; i < 4; i++)
			if (c[i] != ex[i])
				isExit = 0;

		if (isEncrypt == 1)
			return 1;
		else if (isDecrypt == 1)
			return 2;
		else if (isExit == 1)
			return 3;
		else
			return 0;
			break;
	case 2:
		status = scanf("%d", k);
		while ((temp = getchar()) != EOF && temp != '\n');
		if (status != 1)
		{
			printf("Invalid message\n");
			return 0;
		}
		if (*k < 1 || *k > 95)
			return 0;
		else
			return 1;
		break;
	}
}

int main()
{
	int keepLooping = 1;
	printf("Welcome to cryptography\n\n");
	while (keepLooping == 1)
	{
		char choice[255];
		char message[255];
		int *key;
		int which = 0;
		printf("What would you like to do to a message?(encrypt, decrypt, exit)\nEnter your choice: ");
		which = validate(choice, key, 1);
		if (which == 0)
			continue;
		printf("Enter your message:\n");
		scanf("%s", &c);
		printf("Enter the key number(1-95)\n");
		if (validate(choice, key, 2) != 1)
			continue;

		if (which == 1)
			encrypt(message, key);
		else if (which == 2)
			decrypt(message, key);
		else if (which == 3)
			keepLooping = 0;
	}
	printf("Richard Miller Security Systems\n3-27-2019");

}