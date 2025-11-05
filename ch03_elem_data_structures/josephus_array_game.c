#include <stdio.h>

void start_menu(void);
void get_user_input(int *interval, int *members);
void print_sacrifice(int members, int remaining, int index);
void next_sacrifice(void);
void run_ceremony(int interval, int members);
void oink_oink(void);

int main(void) 
{
    start_menu();

    int interval = 0; 
    int members = 0;

    get_user_input(&interval, &members);
    run_ceremony(interval, members);
    oink_oink();

    return 0;
}

void start_menu(void) 
{
    printf("|****** PLAY PIG DEATH CULT *******|\n");
    printf("| Enter two positive digits with a |\n");
    printf("| space in between & press enter.  |\n");
    printf("\n");
}

void get_user_input(int *interval, int *members) {
    scanf("%d %d", interval, members);
    printf("\nCountdown: %d\n", *interval);
    printf("Cult membership: %d\n\n", *members);
}

void run_ceremony(int interval, int members) 
{
    int dead[members] = {};
    int remaining = members;

    int index = 0;
    while (remaining > 0) {
        
        int count = 0;
        while (count < interval) {
            if (!dead[index]) {
                count++;
            }
            if (count == interval) {
                break;
            }
            index = (index + 1) % members;
        }
        dead[index]++;
        remaining--;

        print_sacrifice(members, remaining, index);
        if (remaining == 1) next_sacrifice();

        index = (index + 1) % members;
    }
}

void print_sacrifice(int members, int remaining, int index)
{
    printf("Death #%2d: member %2d\n", members - remaining, index + 1);
}

void next_sacrifice(void) {
    printf("Press ENTER to sacrifice last member...\n");
    
    int ch;
    
    while ((ch = getchar()) != '\n' && ch != EOF) {}
    do {
        ch = getchar();
    } while (ch != ' ' && ch != '\n');
}

void oink_oink(void) 
{
    printf("\n");
    printf("    (\\____/)\n");
    printf("    / @__@ \\\n");
    printf("   (  (oo)  )      OINK! OINK!\n"); 
    printf("    `-.~~.-'\n");
    printf("____// :: \\\\___________________________\n");
    printf("   (!)=[]=(!)\n");    
    printf("== _\\__/\\__/_== == == == == == == == ==\n");   
    printf("__[___∞)(∞___]_________________________\n");
    printf("^” ^”^^”^ ^””^ ^^””^^ ^”^”^^” ””^^”^ ^^\n");
    printf("\n");
}