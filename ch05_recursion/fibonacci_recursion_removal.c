// Showing where recursion SHOULD NOT be used
// Recursive fibonacci computation 
int fibonacci(int N)
{
    if (N <= 1) return 1;
    return fibonacci(N - 1) + fibonacci(N - 2);
}

// Step 1: "Manually" removing recursion
int fibonacci(int N)
{
    int num[2] = { 1, 1 };
    int i = 2;

    if (N <= 1)
        return 1;

loop:
    if (i > N)
        goto done;

    int temp = num[0] + num[1];
    num[0] = num[1];
    num[1] = temp;
    i++;
    goto loop;

done:
    return num[1];
}

// Step 2: "Manually" removing recursion
int fibonacci(int N)
{
    int num[2] = { 1, 1 };
    int i = 2;

    if (N <= 1)
        return 1;

    while (i <= N) {
        int temp = num[0] + num[1];
        num[0] = num[1];
        num[1] = temp;
        i++;
    }
    return num[1];
}

// Iterative v1
int fibonacci(int N)
{   
    int num[2] = { 0, 1 };
    if (N == 1) return num[0];
    if (N == 2) return num[1];

    for (int i = 2; i < N; i++) {
        int temp = num[0] + num[1];
        num[0] = num[1];
        num[1] = temp;
    }
    return num[1];
}

// Iterative v2
int fibonacci(int N)
{   
    int num[N];

    for (int i = 0; i < N; i++) {
        if (i < 2) { 
            num[i] = i;
        } else {
            num[i] = num[i - 2] + num[i - 1];
        }
    }
    return num[N - 1];
}

// Sedgewick's non-recursive
#define max 25
int fibonacci(int N) 
{
    int i; 
    F[max];
    F[0] = 1; 
    F[1] = 1;
    
    for (i = 2; i<= max; i++)
        F[i] = F[i - 1] + F[i - 2];
    
    return F[N];
} 