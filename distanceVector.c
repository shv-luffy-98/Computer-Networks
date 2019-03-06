#include <stdio.h>
#include <stdlib.h>
#define INFINITY 999

struct
{
    int cost, via;
}table[10][10];

int n;
void buildTable()
{
    int i, j;
    for(i = 0; i < n; ++i)
    {
        printf("Routing table for %c: \n",'A'+i);
        for(j = 0; j < n; ++j)
        {
            if(i == j)
                table[i][j].cost = 0;
            else
            {
                printf("->%c = ",'A'+j);
                scanf("%d",&table[i][j].cost);
            }
            if(table[i][j].cost != INFINITY)
                table[i][j].via = j;
            else
                table[i][j].via = INFINITY;
        }
    }
}

void constructTable()
{
    int i, j, k, newCost;
    for(i = 0; i < n; ++i)
        for(j = 0; j < n; ++j)
            for(k = 0; k < n && j != i; ++k)
            {
                newCost = table[i][j].cost + table[j][k].cost;
                if(table[i][k].cost > newCost)
                {
                    table[i][k].cost = newCost;
                    table[i][k].via = table[i][j].via;
                }
            }
}

void dispTable()
{
    int i, j;
    for(i = 0; i < n; ++i)
    {
        printf("\nRouting table of %c:\n",'A'+i);
        printf("Node\tCost\tVia\n");
        for(j = 0; j < n; ++j)
            printf("%c\t%d\t%c\n",'A'+j,table[i][j].cost,'A'+table[i][j].via);
    }
}

void findPath(int i,int j)
{
    printf("%c",'A'+i);
    if(i != j)
    {
        printf("-->");
        findPath(table[i][j].via, j);
    }
}

void main()
{
    int src,dest;
    printf("Enter the number of nodes : ");
    scanf("%d",&n);
    buildTable();
    constructTable();
    dispTable();
    
    //multiple
    printf("\nEnter the source node (0 to %d): ",n-1);
    scanf("%d",&src);
    printf("Enter the dest node(0 to %d): ",n-1);
    scanf("%d",&dest);
    printf("The shortest path is: ");
    findPath(src,dest);
    printf("\nCost of shortest path = %d",table[src][dest].cost);
}
