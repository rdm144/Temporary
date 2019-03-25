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
    char temp[94];
	int tIndex = 0;
	for (int i = 65; i < 91; i++)
	{
		temp[tIndex] = i;
		tIndex++;
	}
	for (int i = 97; i < 123; i++)
	{
		temp[tIndex] = i;
		tIndex++;
	}
	for (int i = 48; i < 58; i++)
	{
		temp[tIndex] = i;
		tIndex++;
	}
	for (int i = 33; i < 48; i++)
	{
		temp[tIndex] = i;
		tIndex++;
	}
	for (int i = 58; i < 65; i++)
	{
		temp[tIndex] = i;
		tIndex++;
	}
	for (int i = 91; i < 97; i++)
	{
		temp[tIndex] = i;
		tIndex++;
	}
	for (int i = 123; i < 127; i++)
	{
		temp[tIndex] = i;
		tIndex++;
	}
	
	char ray[255][2];
	for (int i = 0; i < 255; i++)
		if (message[i] != 0)
			ray[i][0] = message[i];
		else
			break;
	for (int i = 0; i < 255; i++)
	{
		for (int j = 0; j < 94; j++)
		{
			if(message[i] == temp[j] && message[i] != 0)
			{
				int offset = j + key;
				if (offset > 93)
					offset -= 93;
				ray[i][1] = temp[offset];
			}
		}
	}

	int capitals = 0;
	for (int i = 0; i < 255; i++)
		if (message[i] > 64 && message[i] < 91)
			capitals++;
	printf("\nNumber of Capital Letters: %i", capitals);

	int lowerCase = 0;
	for (int i = 0; i < 255; i++)
		if (message[i] > 96 && message[i] < 123)
			lowerCase++;
	printf("\nNumber of Small Letters: %i", lowerCase);

	int digitCount = 0;
	for (int i = 0; i < 255; i++)
		if (message[i] > 47 && message[i] < 58)
			digitCount++;
	printf("\nNumber of Digits: %i", digitCount);

	int symbols = 0;
	for (int i = 0; i < 255; i++)
	{
		for (int j = 33; j < 48; j++)
			if (message[i] == j)
				symbols++;
		for (int j = 58; j < 65; j++)
			if (message[i] == j)
				symbols++;
		for (int j = 91; j < 97; j++)
			if (message[i] == j)
				symbols++;
		for (int j = 123; j < 127; j++)
			if (message[i] == j)
				symbols++;
	}
	printf("\nNumber of Symbols: %i", symbols);

	int numChar = 0;
	for (int i = 0; i < 255; i++)
	{
		if (message[i] == 0)
			break;
		else
			numChar++;
	}
	printf("\nNumber of Characters in the message: %i", numChar);

	printf("\nConverting Letters: ");
        for(int i = 0; i < numChar; i++)
        {
            if(ray[i][0] > 64 && ray[i][0] < 91)
                printf("%c", ray[i][0] + ('a'-'A'));
            else
                printf("%c", ray[i][0]);
        }

        printf("\nThe decrypted text is:\n");
        for (int i = 0; i < numChar; i++)
		printf("%c", ray[i][1]);
	printf("\n\nConcatenation of original and encrypted text: ");
        for(int i = 0; i < numChar; i++)
            printf("%c", ray[i][0]);
        for (int i = 0; i < numChar; i++)
	    printf("%c", ray[i][1]);
        printf("\n\n\n");
}

void decrypt(char* message, int key)
{
	char temp[94];
	int tIndex = 0;
	for (int i = 65; i < 91; i++)
	{
		temp[tIndex] = i;
		tIndex++;
	}
	for (int i = 97; i < 123; i++)
	{
		temp[tIndex] = i;
		tIndex++;
	}
	for (int i = 48; i < 58; i++)
	{
		temp[tIndex] = i;
		tIndex++;
	}
	for (int i = 33; i < 48; i++)
	{
		temp[tIndex] = i;
		tIndex++;
	}
	for (int i = 58; i < 65; i++)
	{
		temp[tIndex] = i;
		tIndex++;
	}
	for (int i = 91; i < 97; i++)
	{
		temp[tIndex] = i;
		tIndex++;
	}
	for (int i = 123; i < 127; i++)
	{
		temp[tIndex] = i;
		tIndex++;
	}
	
	char ray[255][2];
	for (int i = 0; i < 255; i++)
		if (message[i] != 0)
			ray[i][0] = message[i];
		else
			break;
	for (int i = 0; i < 255; i++)
	{
		for (int j = 0; j < 94; j++)
		{
			if(message[i] == temp[j] && message[i] != 0)
			{
				int offset = j - key;
				if (offset < 0)
					offset += 93;
				ray[i][1] = temp[offset];
			}
		}
	}

	int capitals = 0;
	for (int i = 0; i < 255; i++)
		if (message[i] > 64 && message[i] < 91)
			capitals++;
	printf("\nNumber of Capital Letters: %i", capitals);

	int lowerCase = 0;
	for (int i = 0; i < 255; i++)
		if (message[i] > 96 && message[i] < 123)
			lowerCase++;
	printf("\nNumber of Small Letters: %i", lowerCase);

	int digitCount = 0;
	for (int i = 0; i < 255; i++)
		if (message[i] > 47 && message[i] < 58)
			digitCount++;
	printf("\nNumber of Digits: %i", digitCount);

	int symbols = 0;
	for (int i = 0; i < 255; i++)
	{
		for (int j = 33; j < 48; j++)
			if (message[i] == j)
				symbols++;
		for (int j = 58; j < 65; j++)
			if (message[i] == j)
				symbols++;
		for (int j = 91; j < 97; j++)
			if (message[i] == j)
				symbols++;
		for (int j = 123; j < 127; j++)
			if (message[i] == j)
				symbols++;
	}
	printf("\nNumber of Symbols: %i", symbols);

	int numChar = 0;
	for (int i = 0; i < 255; i++)
	{
		if (message[i] == 0)
			break;
		else
			numChar++;
	}
	printf("\nNumber of Characters in the message: %i", numChar);

	printf("\nConverting Letters: ");
        for(int i = 0; i < numChar; i++)
        {
            if(ray[i][0] > 64 && ray[i][0] < 91)
                printf("%c", ray[i][0] + ('a'-'A'));
            else
                printf("%c", ray[i][0]);
        }

        printf("\n\nThe decrypted text is:\n");
        for (int i = 0; i < numChar; i++)
		printf("%c", ray[i][1]);
	printf("\n\nConcatenation of original and decrypted text: ");
        for(int i = 0; i < numChar; i++)
            printf("%c", ray[i][0]);
        for (int i = 0; i < numChar; i++)
	    printf("%c", ray[i][1]);
        printf("\n\n\n");
}

int validate(char* choice, int *k, int which)
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
		status = scanf("%s", choice);
		while ((temp = getchar()) != EOF && temp != '\n');
		if (status != 1)
		{
			printf("\nInvalid message\n\n");
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
			printf("\nInvalid Key Number\n\n");
			return 0;
		}
		if (*k < 1 || *k > 95)
			return 0;
		else
			return 1;
		break;
	}
}

void clearMessageAndChoice(char* choice, char* message)
{
	for (int i = 0; i < 255; i++)
	{
		choice[i] = 0;
		message[i] = 0;
	}
}

int main()
{
	int key;
	int which;
	char choice[255];
	char message[255];
	int keepLooping = 1;
	printf("Welcome to cryptography\n\n");
	while (keepLooping == 1)
	{
		clearMessageAndChoice(choice, message);
		key = 0;
		which = 0;
		printf("What would you like to do to a message?(encrypt, decrypt, exit)\nEnter your choice:  ");
		which = validate(choice, &key, 1);
		if (which == 0)
		{
			printf("\nInvalid message\n\n");
			continue;
		}
                else if(which == 1)
                {
                        printf("\nEnter your message:\n");
			int temp = scanf("%s", message);
			printf("Enter the key number(1-95)\n");
			if (validate(choice, &key, 2) != 1)
			{
				printf("\nInvalid Key Number\n\n");
				continue;
			}
                }
                else if(which == 2)
                {
			printf("Enter the key number(1-95)\n");
			if (validate(choice, &key, 2) != 1)
			{
				printf("\nInvalid Key Number\n\n");
				continue;
			}
                        printf("Enter your message:\n");
			int temp = scanf("%s", message);
                }
		else if (which == 3)
			break;

		if (which == 1)
			encrypt(message, key);
		else if (which == 2)
			decrypt(message, key);
		else if (which == 3)
			keepLooping = 0;
	}
	printf("\nRichard Miller Security Systems\n3-27-2019\n");
}
