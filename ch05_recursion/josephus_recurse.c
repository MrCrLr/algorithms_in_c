// Chapter 5, exercise 9:
#include <stdio.h>
#include <stdlib.h>

void start_menu(void);
void get_user_input(int *interval, int *members);
void run_recursive_ceremony(int *alive, int members, int interval, int remaining, int start);

int main(void) 
{
    start_menu();

    int interval, members;

    get_user_input(&interval, &members);
    
    // Mark everyone alive at teh beginning
    int *alive = calloc(members, sizeof *alive);
    for (int i = 0; i < members; i++)
        alive[i] = 1;

    run_recursive_ceremony(alive, members, interval, members, 0);
    
    free(alive);

    return 0;
}

void start_menu(void) 
{
    printf("|********* RECURSIVE CULT *********|\n");
    printf("| Enter two positive digits with a |\n");
    printf("| space in between & press enter.  |\n");
    printf("\n");
}

void get_user_input(int *interval, int *members) {
    scanf("%d %d", interval, members);
    printf("\nCountdown: %d\n", *interval);
    printf("Cult membership: %d\n\n", *members);
}

void run_recursive_ceremony(int *alive, int members, int interval, int remaining, int start)
{
    if (remaining == 0) 
        return;

    int count = 0;
    int i = start;

    while (1) {
        if (alive[i]) {
            count++;
            if (count == interval)
                break;
        }
        i = (i + 1) % members;
    }

    alive[i] = 0;
    printf("Death #%2d, Member #%2d\n", members - remaining + 1, i + 1);

    run_recursive_ceremony(alive, members, interval, remaining - 1, (i + 1) % members);
}