#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct
{
    int seqno;
    char msg[21];
}Frame;

void printFrames(Frame frames[], int n)
{
    for (int i = 0; i < n; ++i)
        printf("Frame %d : %s\n", frames[i].seqno, frames[i].msg);
}
void shuffleFrames(Frame frames[], int n)
{
    int r;
    Frame temp;
    for(int i = 0; i < n; ++i)
    {
        r = rand() % n;
        temp = frames[i];
        frames[i] = frames[r];
        frames[r] = temp;
    }
}
void frameSort(Frame frames[], int n)
{
    int i, j;
    for ( i = 0; i < n; ++i)
        for ( j = 0; j < n - i - 1; ++j)
            if (frames[j].seqno > frames[j + 1].seqno)
            {
                Frame temp = frames[j];
                frames[j] = frames[j + 1];
                frames[j + 1] = temp;
            }
}
int main()
{
    char msg[100];
    int framesize, ch, nof;
    Frame frames[10];
    time_t t;
    srand(time(&t));
    
    printf("1. Fixed frame size\n2. Fixed frame count\n3. Exit\nChoice : ");
    scanf("%d", &ch);
    if(ch != 2 && ch != 1)
        return 0;
    if (ch == 1)
    {
        printf("\n1. Random sequence number\n2. Explicit sequence number\n3. Exit\nChoice : ");
        scanf("%d", &ch);
        if (ch != 1 && ch !=2)
            return 0;
        
        printf("Enter message : ");
        scanf("\n%[^\n]s", msg);
        printf("Enter frame size (<20): ");
        scanf("%d", &framesize);

        nof = strlen(msg) / framesize;
        if(strlen(msg) % framesize)
            ++nof;

        for(int i = 0, shift = 0; i < nof; ++i, shift += framesize)
        {
            frames[i].seqno = i + 1;
            for(int j = 0; j < framesize; ++j)
                frames[i].msg[j] = msg[j + shift];
        }
        if(ch == 1)
            shuffleFrames(frames, nof);
        else
        {
            int tempSeqno;
            Frame tempframes[20];
            printf("Enter valid sequence numbers : ");
            for(int i = 0; i < nof; ++i)
            {
                scanf("%d", &tempSeqno);
                tempframes[i] = frames[tempSeqno - 1];
            }
            for(int i = 0; i < nof; ++i)
                frames[i] = tempframes[i];
        }
    }
    else if(ch == 2)
    {
        printf("\n1. Enter message for given sequence number\n2. Enter message and sequence number\n3. Exit\nChoice : ");
        scanf("%d", &ch);
        if(ch != 1 && ch != 2)
            return 0;
        printf("Enter number of frames : ");
        scanf("%d", &nof);
        if(ch == 1)
        {
            for(int i = 0; i < nof; ++i)
                frames[i].seqno = i + 1;
            shuffleFrames(frames, nof);

            for(int i = 0; i < nof; ++i)
            {
                printf("Enter message for frame %d : ", frames[i].seqno);
                scanf("\n%[^\n]s", frames[i].msg);
            }
        }
        else
        {
            for(int i = 0; i < nof; ++i)
            {
                printf("Enter sequence number and message : ");
                scanf("%d ", &frames[i].seqno);
                scanf("%[^\n]s", frames[i].msg);
            }
        }
    }
    printf("\nReceived frames : \n");
    printFrames(frames, nof);
    frameSort(frames, nof);
    
    printf("\nReceived frames after sorting : \n");
    printFrames(frames, nof);
    return 0;
}
