/*--------------------------------------------------------------------------*/
// Exercise: Mechanically remove recursion
// Recursive Postorder Traversal 
/*--------------------------------------------------------------------------*/
traverse(node *t) {
    if (t != z) 
    {
        traverse(t->l);
        traverse(t->r);
        visit(t)
    }
}
/*--------------------------------------------------------------------------*/
// Step 1: First sketch... incorrect.
/*--------------------------------------------------------------------------*/
traverse(node *t) { 
    l:  if (!t) goto s;
        push(t);
        t = t->l;

    r:  if (!t->r) goto s;
        t = t->r;
        push(t);
        if !(t->l) goto s;
        t = t->l;
        goto l;

    s:  if (stack_empty) goto x;
        t = pop(t);
        visit(t);
        goto r;

    x: ;
}

/*--------------------------------------------------------------------------*/
// Step 1: Visited plays role of “returning from left, now go right.
// 4 Control Points:
// l:  going down left
// r:  going right
// s:  stack handling (decisions)
// x:  exit
/*--------------------------------------------------------------------------*/
// stack entries: (node*, visited)
traverse(node *t) { 
l:  
    while (t != z) {
        push_state(t, 0);
        t = t->l;
    }

s:
    if (stack_empty()) goto x;
    
    pair top = peek();
    if (top.visited == 0) {
        set_top_state(1);       // mark: left done, right next
        t = top.node->r;
        goto r;
    }
    // top.visited == 1 --> both subtrees done
    pop();
    visit(top.node);
    goto s;

r:
    goto l;

x: ;
}

/*--------------------------------------------------------------------------*/
// Step 2: Remove obviously redundant "goto r" control point
/*--------------------------------------------------------------------------*/
traverse(node *t) { 
l:  
    while (t != z) {
        push_state(t, 0);
        t = t->l;
    }
s:
    if (stack_empty()) goto x;
    
    pair top = peek();
    if (top.visited == 0) {
        set_top_state(1);       // mark: left done, right next
        t = top.node->r;
        goto l;
    }
    // top.visited == 1 --> both subtrees done
    pop();
    visit(top.node);
    goto s;

x: ;
}

/*--------------------------------------------------------------------------*/
// Step 3: Iterative Postorder
// a) Outer loop replaces bounce between s: and x:.
// b) Inner loop replaces l: (left descent).
// c) If/else replaces the branching at s: and the jump to r:.
// d) t = z after visiting keeps control from re-descending into same node.
/*--------------------------------------------------------------------------*/
traverse(node *t) {
   
    while (t != z || stack_empty()) {
        while (t != z) {
            push_state(t, 0);
            t = t->l;
        }

        pair top = peek();

        if (top.visited == 0) {
            set_top_state(1);
            t = top.node->r;
        } else {
            pop();
            visit(top.node);
            t = z; // don't re-enter left loop on same node
        }
    }
}