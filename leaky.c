#include <stdio.h>

typedef struct 
{
    int arrival_time, packet_size;
}Packet;

int main()
{
    int n, out_rate, buffer_size, time_slot, rem, cur, i, j;
    Packet packets[20];
    printf("Enter out rate, buffer size and time slot : ");
    scanf("%d %d %d", &out_rate, &buffer_size, &time_slot);
    printf("Enter number of packets : ");
    scanf("%d", &n);

    for(i = 0; i < n; ++i)
    {
        printf("Enter arrival time and packet size of packet %d : ", i + 1);
        scanf("%d%d", &packets[i].arrival_time, &packets[i].packet_size);
    }
    
    rem = buffer_size;
    cur = 0;
    for(i = 0, j = 0; i < time_slot; ++i)
    {
        if(packets[j].arrival_time == i)
        {
            if(packets[j].packet_size <= rem)
            {
                rem -= packets[j].packet_size;
                cur += packets[j].packet_size;
                printf("At %d : packet %d inserted, remaining buffer size = %d\n", i, j + 1, rem);
            }
            else
                printf("At %d : packet %d discarded\n", i, j + 1);
            ++j;
        }
        if(i % 5 == 0)
        {
            if(cur > out_rate)
            {
                rem += out_rate;
                cur -= out_rate;
                printf("At %d : %d bytes sent\n", i, out_rate);
            }
            else if(cur > 0)
            {
                printf("At %d : %d bytes sent\n", i, cur);
                rem = buffer_size;
                cur = 0;
            }
        }
    }
    while(cur)
    {
        if(cur > out_rate)
        {
            rem += out_rate;
            cur -= out_rate;
            printf("At %d : %d bytes sent\n", i, out_rate);
        }
        else if(cur > 0)
        {
            printf("At %d : %d bytes sent\n", i, cur);
            rem = buffer_size;
            cur = 0;
        }
        ++i;
    }
    return 0;
}