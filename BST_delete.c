#include <stdio.h>
#include <stdlib.h>

// Structure for BST node
struct node {
    int data;
    struct node* left;
    struct node* right;
};

// Function to create a new node
struct node* createnode(int data) {
    struct node *newnode = (struct node*)malloc(sizeof(struct node));
    newnode->data = data;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}

// Function to insert a new node into BST
struct node* insert(struct node *root, int data) {
    if (root == NULL) {
        return createnode(data);
    } else if (data < root->data) {
        root->left = insert(root->left, data);
    } else {
        root->right = insert(root->right, data);
    }
    return root;
}

// Function to find minimum node (for deleting)
struct node* findMin(struct node* root) {
    while (root->left != NULL)
        root = root->left;
    return root;
}

// Function to delete a node from BST
struct node* deleteNode(struct node* root, int key) {
    if (root == NULL)
        return root;

    if (key < root->data)
        root->left = deleteNode(root->left, key);

    else if (key > root->data)
        root->right = deleteNode(root->right, key);

    else {
        // Case 1: No child
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }
        // Case 2: One child
        else if (root->left == NULL) {
            struct node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct node* temp = root->left;
            free(root);
            return temp;
        }
        // Case 3: Two children
        else {
            struct node* temp = findMin(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }

    return root;
}

// Postorder traversal: Left -> Right -> Root
void postorder(struct node* root) {
    if (root == NULL)
        return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}

int main() {
    struct node* root = NULL;

    root = insert(root, 15);
    insert(root, 10);
    insert(root, 20);
    insert(root, 8);
    insert(root, 12);
    insert(root, 18);
    insert(root, 25);

    printf("Postorder Traversal before delete: ");
    postorder(root);

    root = deleteNode(root, 20); // Example delete
    root = deleteNode(root, 18); // Example delete
    root = deleteNode(root, 8); // Example delete

    printf("\nPostorder Traversal after delete: ");
    postorder(root);
    printf("\n");

    return 0;
}
