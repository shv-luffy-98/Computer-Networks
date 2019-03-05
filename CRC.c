#include <stdio.h>
#include <stdlib.h>

struct {
    int bit; 
}r[16];

void crc(int data[], int n)
{
	int feedback, i, j, end = n + 16;

	for (i = 0; i < 16; ++i)
		r[i].bit = 0;

	for (i = 0; i < end; ++i)
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

	printf("Register content : ");
	for (i = 15; i >= 0; --i)
		printf("%d ", r[i].bit);

	for (i = n, j = 16; i < end; ++i)
		data[i] = r[--j].bit;
}

int sender(int data[])
{
	int i, n, end;
	printf("Enter number of bits : ");
	scanf("%d", &n);
	end = n + 16;

	printf("Enter data : ");
	for ( i = 0; i < n; ++i)
		scanf("%d", &data[i]);

	for ( i = n; i < end; ++i)
		data[i] = 0;
	crc(data, n);
    
	printf("\nThe message with CRC : ");
	for (i = 0; i < end; ++i)
		printf("%d ", data[i]);

    return n;
}

void transmit(int data[], int n)
{
	int ch, pos;
	printf("\n\nSending");
	printf("\nDo you want to corrupt the data?\n1. Yes\n2. No\nChoice : ");
	scanf("%d", &ch);
	if(ch != 1)
		return;
	printf("Enter the bit position between 0 to %d : ", 15);
	scanf("%d", &pos);
	if (data[20 - pos] == 0)
		data[20 - pos] = 1;
	else
		data[20 - pos] = 0;
}

void errorCheck()
{
	printf("\nError check:\n");
	for (int i = 15; i >= 0; --i)
		if (r[i].bit != 0)
		{
			printf("Data has been altered at %d", i);
			return;
		}
	printf("Data has not been altered");
}

void receive(int data[], int n)
{
	int i, end = n + 16;
	printf("\nMessage received : ");
	for (i = 0; i < end; ++i)
		printf("%d ", data[i]);
	printf("\n");
	crc(data, n);
	errorCheck();
}

int main()
{
	int data[100], n; 
	n = sender(data);
	transmit(data, n);
	receive(data, n);
	return 0;
}
