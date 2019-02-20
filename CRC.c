#include <stdio.h>
#include <stdlib.h>

struct reg
{
	int bit;
}r[16];

int n, end;

void crc(int data[])
{
	int feedback, i, j;

	for (i = 0; i < 16; ++i)
		r[i].bit = 0;

	for (i = 0; i< end; ++i)
	{
		feedback = r[15].bit;
		for (j = 15; j >= 0; --j)
			r[j].bit = r[j - 1].bit;

		r[0].bit = data[i];
		if (feedback == 1)
		{
			r[12].bit ^= feedback;
			r[5].bit ^= feedback;
			r[0].bit ^= feedback;
		}
	}

	printf("Register content :\n");
	for (int i = 15; i >= 0; --i)
		printf("%d ", r[i].bit);

	for (i = n, j = 16; i< end; ++i)
		data[i] = r[--j].bit;

	printf("\nThe message with CRC:\n");
	for (i = 0; i < end; ++i)
		printf("%d ", data[i]);
}
void sender(int data[])
{
	int i;
	printf("Sender : \n");
	printf("Enter the number of bits of data: ");
	scanf_s("%d", &n);
	end = n + 16;

	printf("Enter the data :");
	for (int i = 0; i<n; i++)
		scanf_s("%d", &data[i]);

	for (i = n; i < end; ++i)
		data[i] = 0;
	crc(data);
}
void transmit(int data[])
{
	int ch, pos;
	printf("\n\nData being transmitted.");
	printf("\nDo you want to corrupt the data? Yes = 1 / No = 0 :");
	scanf_s("%d", &ch);
	do
	{
		printf("Enter the bit position between 0 to %d : ", n + 15);
		scanf_s("%d", &pos);
		if (data[pos] == 0)
			data[pos] = 1;
		else
			data[pos] = 0;
		printf("Do you want to corrupt another data bit? Yes = 1 / No = 0 :");
		scanf_s("%d", &ch);
	} while (ch);
}
int errorCheck()
{
	printf("\nError check:\n");
	for (int i = 15; i >= 0; --i)
		if (r[i].bit != 0)
		{
			printf("Data has been altered.");
			printf("Position : %d", i);
			return 1;
		}
	return 0;
}
void receive(int data[])
{
	printf("\nReceiver side : \n");
	printf("Message received:\n");
	for (int i = 0; i<n + 16; i++)
		printf("%d ", data[i]);
	printf("\n");
	crc(data);
	if(!errorCheck())
		printf("Received data is unaltered.");
}
int main()
{
	int data[100], i; 
	sender(data);
	transmit(data);
	receive(data);
	return 0;
}
