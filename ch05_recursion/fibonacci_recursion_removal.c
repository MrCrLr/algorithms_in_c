// Recursive fibonacci computation
int fibonacci(int N)
{
    if (N <= 1) return 1;
    return fibonacci(N - 1) + fibonacci(N - 2);
}


// Non-recursive
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