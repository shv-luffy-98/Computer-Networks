#include <stdio.h>
int gcd(int a, int b)
{
	return a == 0 ? b : gcd(b % a, a);
}

int getE(int totient)
{
	int choice;
	printf("The choices for e are :\n");
	for (int i = 2; i < totient; ++i)
		if (gcd(i, totient) == 1)
			printf("%d ", i);
	printf("\nEnter e : ");
	scanf("%d", &choice);
	return choice;
}

int powerMod(int m, int x, int n)
{
	int c = 1;
	while (x--) 
        c = (c * m) % n;
	return c;
}
int main()
{
  char message[100];
  int p, q, i, encrypted[100];
	printf("Enter p and q : ");
	scanf("%d %d", &p, &q);
	
  int n = p * q, totient = (p - 1) * (q - 1), e = getE(totient), d = 1;
  while(((e * d) % totient) != 1) 
    ++d;

  printf("\nPublic key = {%d, %d}\nPrivate key = {%d, %d}", e, n, d, n);
	printf("\n\nEnter message to encrypt : ");
	scanf("\n");
	scanf("%[^\n]s", message);
	
  printf("Encrypted message : \n");
	for (i = 0; message[i]; ++i){
		encrypted[i] = powerMod(message[i], e, n);
		printf("%d : %c\n", encrypted[i]);
	}
	
  printf("\ndecrypted message : \n");
	for (int j = i - 1; i--;)
    printf("%d = %c\n", encrypted[j - i], powerMod(encrypted[j - i], d, n));
  return 0;
}
