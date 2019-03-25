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
	unsigned char temp[] = "A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z,0,1,2,3,4,5,6,7,8,9,!,34,#,$,%,&,',(,),*,+,44,-,.,/,:,;,<,=,>,?,@,[,92,],^,_,`,{,|,},~";
	int length = 0;
	for (int i = 0; i < 255; i++)
	{
		if (message[i] == 0)
			break;
		else
			length++;
	}

	unsigned char ray[length][2];
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < 94; j++)
		{
			if (message[i] == temp[j])
			{
				ray[i][0] = message[i];
				int offset = j + key;
				if (offset > 93)
					offset = offset - 93;
				ray[i][1] = temp[offset];
				break;
			}
		}
	}

	int capitals = 0;
	for (int i = 0; i < length; i++)
		if (message[i] > 64 && message[i] < 91)
			capitals++;
	printf("\nNumber of Capital Letters: %i", capitals);

	int lowerCase = 0;
	for (int i = 0; i < length; i++)
		if (message[i] > 96 && message[i] < 123)
			lowerCase++;
	printf("\nNumber of Small Letters: %i", lowerCase);

	int digitCount = 0;
	for (int i = 0; i < length; i++)
		if (message[i] > 47 && message[i] < 58)
			digitCount++;
	printf("\nNumber of Digits: %i", digitCount);

	int symbols = 0;
	for (int i = 0; i < length; i++)
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

	int numChar = length;
	printf("\nNumber of Characters in the message: %i", numChar);

	char lowerCaseMessage[length];
	for (int i = 0; i < length; i++)
	{
		if (message[i] > 64 && message[i] < 91)
			lowerCaseMessage[i] = message[i] + 32;
		else
			lowerCaseMessage[i] = message[i];
	}
	printf("\nConverting Letters: %s", lowerCaseMessage);

	char encrypted[length];
	for (int i = 0; i < length; i++)
	{
		encrypted[i] = ray[i][1];
	}
	printf("\nThe decrypted text is:\n%s\n", encrypted);

	char combo[length*2];
	for (int i = 0; i < length*2; i++)
	{
		if (i < length)
			combo[i] = message[i];
		else
			combo[i] = encrypted[i];
	}
	printf("\nConcatenation of original and encrypted text: %s\n\n\n", combo);
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
	printf("\n\nYour encrypted text is:\n%s\n", decrypted);
	char combo[255] = "combo";
	printf("\nConcatenation of original and encrypted text: %s\n\n\n", combo);
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
			printf("Invalid message\n\n");
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
			printf("Invalid Key number\n\n");
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
	int key;
	int which;
	int keepLooping = 1;
	printf("Welcome to cryptography\n\n");
	while (keepLooping == 1)
	{
		unsigned char choice[255] = { 0 };
		unsigned char message[255] = { 0 };
		which = 0;
		printf("What would you like to do to a message?(encrypt, decrypt, exit)\nEnter your choice:  ");
		which = validate(choice, &key, 1);
		if (which == 0)
		{
			printf("Invalid message\n");
			continue;
		}
		else if (which == 3)
			break;

		printf("\nEnter your message:\n");
		scanf("%s", &message);
		printf("Enter the key number(1-95)\n");
		if (validate(choice, &key, 2) != 1)
		{
			printf("Invalid key\n");
			continue;
		}
		if (which == 1)
			encrypt(message, key);
		else if (which == 2)
			decrypt(message, key);
		else if (which == 3)
			keepLooping = 0;
	}
	printf("Richard Miller Security Systems\n3-27-2019\n");

}