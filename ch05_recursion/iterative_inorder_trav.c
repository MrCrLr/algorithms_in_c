/*--------------------------------------------------------------------------*/
// Exercise: Mechanically remove recursion
// Recursive Inorder Traversal 
/*--------------------------------------------------------------------------*/
traverse(node *t) {
    if (t != z) {
        traverse(t->l);
        visit(t);
        traverse(t->r);
    }
}
/*--------------------------------------------------------------------------*/
// Step 1: The second recursive call can be easily removed 
// because there is no code following it. 
// a.k.a. "end-recursion removal"
/*--------------------------------------------------------------------------*/
traverse(node *t) {
    l:  if (t == z) goto x;
        traverse(t->l);
        visit(t);
        t = t->r; 
        goto l;
    x: ;
}
/*--------------------------------------------------------------------------*/
// Step 2: We start by adding all left children to stack
// and then after popping and visiting each node on the stack adding
// the right child and then adding all left children of it.
/*--------------------------------------------------------------------------*/
traverse(node *t) {
    l:  if (t == z) goto s;
        push(t); 
        t = t->l;
        goto l;
        
    r:  t = t->r;
        goto l;
        
    s:  if (stack_empty()) goto x;
        t = pop(); 
        visit(t);
        goto r;

    x: ;
}
/*--------------------------------------------------------------------------*/
// Step 3: Now we must "mechanically" remove the goto-mess.
// Easily remove the goto 'r' and 's' as they are surrounded by gotos.
/*--------------------------------------------------------------------------*/
traverse(node *t) {
    l:  while (t != z) {
            push(t); 
            t = t->l;
        }
        if (stack_empty()) goto x;
        t = pop(); 
        visit(t);
        t = t->r;
        goto l;

    x: ;
}
/*--------------------------------------------------------------------------*/
// Step 4: Finally, we are able to remove the last set of gotos by
// adding another while loop to come to our nonrecursive tree traversal method.
/*--------------------------------------------------------------------------*/
traverse(node *t) {

    while (t != z || !stack_empty()) {
        
        while (t != z) {
            push(t); 
            t = t->l;
        }

        t = pop();
        visit(t);
        t  = t->r;
    }
}
