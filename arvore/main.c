#include<stdlib.h>
#include<stdio.h>

struct bin_tree {
int data;
int state;
struct bin_tree * right, * left;
};
typedef struct bin_tree node;

void insert(node ** tree, int val, int track)
{
    node *temp = NULL;
    if(!(*tree))
    {
        temp = (node *)malloc(sizeof(node));
        temp->left = temp->right = NULL;
        temp->data = val;
        temp->state = track;
        *tree = temp;
        return;
    }

    if(val < (*tree)->data)
    {
        insert(&(*tree)->left, val,0);
    }
    else if(val > (*tree)->data)
    {
        insert(&(*tree)->right, val, 0);
    }

}

void isLeaf(node * tree) {
    node * tmp = tree;
    while(tmp->left) {
        tmp->left = tmp->left->left;
    }
    printf("filho: %d\n", tree->data);

}

/*int print_preorder(node * tree, int val, int alt)
{
    //int altura = alt;
    int valueRight = 0;
    int valueLeft = 0;
    int i = 0;
    //node * tmp = (node *)malloc(sizeof(node));
    node * tmp = tree->left;
    node * tmp2 = tree->right;
    while(alt > 1) {

        tmp = tmp->right;
        tmp2 = tmp2->left;


        //i++;
        alt--;
        printf("%d\n", tmp->data);
        printf("%d\n", tmp2->data);
    }
    return 0;
    if (tree)
    {
        //printf("%d\n",tree->data);
        valueRight = print_preorder(tree->left, val, alt);
        valueLeft = print_left(tree->right);
    }
    return abs(val - valueRight) > (val - valueLeft)? (val - valueLeft) : (val - valueRight);
}*/

/*int print_left(node * tree) {
    if(tree) {
        //printf("%d\n", tree->data);
        print_left(tree->left);
    }
}*/

/*void print_preorder(node * tree, int val)
{
    if (tree)
    {
        printf("%d\n",tree->data);
        print_preorder(tree->left);
        print_preorder(tree->right);
    }

}*/

void print_inorder(node * tree)
{
    if (tree)
    {
        print_inorder(tree->left);
        printf("%d\n",tree->data);
        print_inorder(tree->right);
    }
}

void print_postorder(node * tree)
{
    if (tree)
    {
        print_postorder(tree->left);
        print_postorder(tree->right);
        printf("%d\n",tree->data);
    }
}

void deltree(node * tree)
{
    if (tree)
    {
        deltree(tree->left);
        deltree(tree->right);
        free(tree);
    }
}

/*node* search(node ** tree, int val)
{
    int menor = 0;
    if(!(*tree))
    {
        return NULL;
    }

    if(val < (*tree)->data)
    {
        search(&((*tree)->left), val);
    }
    else if(val > (*tree)->data)
    {
        search(&((*tree)->right), val);
    }
    else if(val == (*tree)->data)
    {
        return (*tree);
    }
}*/


node* search(node ** tree, int val)
{
    //int menor = 0;
    if(!(*tree))
    {
        return NULL;
    }

    if(val == (*tree)->data)
    {
        return (*tree);
    }


    if(val < (*tree)->data)
    {
        //f((*tree)->left)
        if(val == (((*tree)->left)->data))
            return (*tree);
        search(&((*tree)->left), val);
    }
    else if(val > (*tree)->data)
    {
        if(val == (((*tree)->right)->data))
            return (*tree);
        search(&((*tree)->right), val);
    }
}



/*int search(node ** tree, int val, int minimo)
{   int menor = minimo;
    int aux;

    if(*tree->left) {
        return *tree->data;
    }


    if(val < (*tree)->data)
    {

        aux = (*tree)->data - val;
        if(aux < menor)
            menor = aux;
        search(&((*tree)->left), val, menor);
    }
    else if(val > (*tree)->data)
    {
        aux = val - (*tree)->data;
        if(aux < menor)
            menor = aux;
        search(&((*tree)->right), val, menor);
    }
    else if(val == (*tree)->data)
    {
        aux = val - (*tree)->data;
        if(aux < menor)
            menor = aux;
        search(&((*tree)->right), val, menor);
    }
}*/



void main()
{
    node *root;
    node *tmp;
    //int i;
    int vetor[] = {50, 95, 180, 34, 119, 11, 123, 62, 64, 199};
    root = NULL;
    /* Inserting nodes into tree */
    int i;
    for(i = 0; i < 10; i++) {
        insert(&root, vetor[i], 0);
    }
    /*int altura = (7/2) - (1);
    insert(&root, 9,0);
    insert(&root, 4,0);
    insert(&root, 15,0);
    insert(&root, 6,0);
    insert(&root, 12,0);
    insert(&root, 17,0);
    insert(&root, 2,0);*/

    /* Printing nodes of tree */
    printf("Pre Order Display\n");
   // printf("%d\n", print_preorder(root , root->data, altura));

    printf("In Order Display\n");
    print_inorder(root);

    printf("Post Order Display\n");
    print_postorder(root);

    //isLeaf(root);
    /* Search node into tree */
    tmp = search(&root, 62);
    //printf("%d\n", tmp);
    if (tmp)
    {
        printf("Searched node=%d\n", tmp->data);
    }
    else
    {
        printf("Data Not found in tree.\n");
    }

    /* Deleting all nodes of tree */
    deltree(root);
}
