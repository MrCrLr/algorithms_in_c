/*--------------------------------------------------------------------------*/
// Recusive preorder traversal (Sedgewick)
/*--------------------------------------------------------------------------*/
traverse(struct node *t) 
{
    push(t);

    while (!stack_empty()) 
    {
        t = pop();
        visit(t);

        if (t->r  != z) 
            push(t->r);
        if (t->l  != z) 
            push(t->l);
    }
}

/*--------------------------------------------------------------------------*/
// Iterative preorder traversal (Sedgewick)
/*--------------------------------------------------------------------------*/
traverse(struct node *t) 
{
    push(t);

    while (!stack_empty()) 
    {
        t = pop();

        if (t != z) 
        {
            visit(t);
            push(t->r);
            push(t->l);
        }
    }
}
