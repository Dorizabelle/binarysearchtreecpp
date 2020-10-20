//Dorizabelle Northecide
//Software Development
//October 19, 2020

#include <iostream>
using namespace std;

struct node
{
    int data;
    struct node *left;
    struct node *right;
};

struct node *newNode(int data)
{
    struct node *node = new struct node;
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void insert(struct node **rootRef, int data)
{
    if (*rootRef == NULL)
    {
        *rootRef = newNode(data);
    }
    else
    {
        if (data > (*rootRef)->data)
        {
            insert(&(*rootRef)->right, data);
        }
        else
        {
            insert(&(*rootRef)->left, data);
        }
    }
}

void printInOrder(struct node *root)
{
    if (root == NULL)
        return;
    printInOrder(root->left);
    cout << root->data << " ";
    printInOrder(root->right);
}

int findMinValueLoop(struct node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    else
    {
        struct node *current = root;
        while (current->left != NULL)
        {
            current = current->left;
        }
        return (current->data);
    }
}

int findMinValueRec(struct node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    else
    {
        if (root->left == NULL)
        {
            return root->data;
        }
        return findMinValueRec(root->left);
    }
}

// TODO:
// Q1: Finding the size of BST
int size(struct node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    else
    {
        //cout << "data: " << root->data << endl;
        return (size(root->left) + 1 + size(root->right));
    }
}

// Q2: Finding the height of BST
int height(struct node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    else
    {
        return 1 + max(height(root->left), height(root->right));
    }
}

// Q3: Finding a given value in BST
bool findValue(struct node *root, int target)
{
    if (root == NULL)
    {
        cout << "not found" << endl;
        return false;
    }
    if (target == root->data)
    {
        cout << "found" << endl;
        return true;
    }
    if (target < root->data)
    {
        cout << "searcing left" << endl;
        return findValue(root->left, target);
    }
    else
    {
        cout << "searcing right" << endl;
        return findValue(root->right, target);
    }
}

// Q4: Finding the max value in BST
int findMaxValue(struct node *root)
{
    struct node *current = root;
    while (current->right != NULL)
        current = current->right;
    return (current->data);
}

// Q5: Delete a node in BST
struct node **getSuccessor(struct node **node)
{
    struct node **tmp = node;
    while ((*tmp)->right != NULL)
        tmp = &(*tmp)->right;
    return tmp;
}

void deleteNode(struct node **root, int target)
{
    if (*root != NULL)
    {
        if (*root == NULL)
        {
            std::cerr << "ERROR: Node does not exist\n";
        }

        if (target == (*root)->data)
        {
            if ((*root)->right == NULL)
            {
                *root = (*root)->left;
            }
            else if ((*root)->left == NULL)
            {
                *root = (*root)->right;
            }
            else
            {
                struct node **successor = getSuccessor(&(*root)->left);
                (*root)->data = (*successor)->data;
                deleteNode(successor, (*successor)->data);
            }
        }
        else if (target < (*root)->data)
        {
            deleteNode(&(*root)->left, target);
        }
        else
        {
            deleteNode(&(*root)->right, target);
        }
    }
}

// Q6: Print the values in pre-order
void printPreOrder(struct node *root)
{
    if (root == NULL)
        return;
    cout << root->data << " ";
    printPreOrder(root->left);
    printPreOrder(root->right);
}

// Q7: Print the values in post-order
void printPostOrder(struct node *root)
{
    if (root == NULL)
        return;
    printPostOrder(root->left);
    printPostOrder(root->right);
    cout << root->data << " ";
}

int main()
{
    struct node *root = NULL;

    insert(&root, 50);
    insert(&root, 70);
    insert(&root, 40);
    insert(&root, 20);
    insert(&root, 90);
    insert(&root, 45);

    // insert(&root, 4);
    // insert(&root, 2);
    // insert(&root, 5);
    // insert(&root, 1);
    // insert(&root, 6);
    // insert(&root, 3);
    // insert(&root, 7);

    cout << "In-order" << endl;
    printInOrder(root);

    cout << "\nPre-order" << endl;
    printPreOrder(root);

    cout << "\nPost-order" << endl;
    printPostOrder(root);

    cout << "\nSize: " << size(root);

    cout << "\nheight: " << height(root);

    cout << "\nfinding value: \n"
         << findValue(root, 45);
    //cout << "\ndeleting number: "
    //<< deleteNode(&root, 45);

    cout << "\nSmallest value: " << findMinValueRec(root);

    cout << "\nLargest value: "
         << findMaxValue(root);

    deleteNode(&root, 45);

    cout << "\nIn-order" << endl;
    printInOrder(root);

    deleteNode(&root, 90);

    cout << "\nIn-order" << endl;
    printInOrder(root);

    deleteNode(&root, 20);

    cout << "\nIn-order" << endl;
    printInOrder(root);
    return 0;
}