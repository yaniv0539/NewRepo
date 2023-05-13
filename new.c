#include <stdio.h>
#include <stdlib.h>

typedef struct tnode {
    int data;
    struct tnode* left;
    struct tnode* right;
} TNODE;

typedef struct tree {
    TNODE* root;
} TREE;

int isBalanced(TREE tr);
int isBalancedHelper(TNODE* root, int* sum);
TNODE* createNode(int data);
TNODE* insertNode(TNODE* root, int data);

void main()
{
    TNODE* node1 = (TNODE*)malloc(sizeof(TNODE));
    TNODE* node2 = (TNODE*)malloc(sizeof(TNODE));
    TNODE* node3 = (TNODE*)malloc(sizeof(TNODE));
    TNODE* node4 = (TNODE*)malloc(sizeof(TNODE));
    TNODE* node5 = (TNODE*)malloc(sizeof(TNODE));
    TNODE* node6 = (TNODE*)malloc(sizeof(TNODE));
    TNODE* node7 = (TNODE*)malloc(sizeof(TNODE));

    node1->data = 3;
    node1->left = node2;
    node1->right = node3;

    node2->data = 0;
    node2->left = node4;
    node2->right = NULL;

    node3->data = 0;
    node3->left = node5;
    node3->right = node6;

    node4->data = 1;
    node4->left = NULL;
    node4->right = NULL;

    node5->data = 0;
    node5->left = node7;
    node5->right = NULL;

    node6->data = 0;
    node6->left = NULL;
    node6->right = NULL;

    node7->data = 0;
    node7->left = NULL;
    node7->right = NULL;

    TREE* mytree = (TREE*)malloc(sizeof(TREE));
    mytree->root = node1;

    printf("number of balanced TNODES: %d\n", isBalanced(*mytree));

    printf("\n");

    free(node1);
    free(node2);
    free(node3);
    free(node4);
    free(node5);
    free(node6);
    free(node7);
    free(mytree);
}

int isBalanced(TREE tr)
{
    int sum = 0;
    return isBalancedHelper(tr.root, &sum);
}

int isBalancedHelper(TNODE* root, int* sum)
{
    int leftCnt, rightCnt, leftSum, rightSum;

    if (root == NULL)
        return 0;

    leftCnt = isBalancedHelper(root->left, sum);

    leftSum = *sum;
    *sum = 0;

    rightCnt = isBalancedHelper(root->right, sum);

    rightSum = *sum;

    if (abs(leftSum - rightSum) < root->data)
        return leftCnt + rightCnt + 1;
    return leftCnt + rightCnt;
}

TNODE* createNode(int data)
{
    TNODE* newNode = (TNODE*)malloc(sizeof(TNODE));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

TNODE* insertNode(TNODE* root, int data)
{
    if (root == NULL) {
        root = createNode(data);
    }
    else if (data < root->data) {
        root->left = insertNode(root->left, data);
    }
    else if (data > root->data) {
        root->right = insertNode(root->right, data);
    }
    return root;
}