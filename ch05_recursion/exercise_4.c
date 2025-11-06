/*

Give the coordinates produced when the recursive tree-drawing procedure given
in the text is applied to the binary tree in Figure 4.2.

Node    X   Y
A       1   3
S       2   2
A       3   3
M       4   1 
P       5   0
L       6   1
E       7   2
T       8   4
R       9   3
E       10  5
E       11  4


visit(t) { 
    t->x = ++x; 
    t->y = y; 
}

traverse(t) {
    y++;
    if (t != z) {
        traverse(t->l);
        visit(t);
        traverse(t->r);
    }
    y--;
}

*/

