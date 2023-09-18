#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_L 256
#define MAX 100000
// Dinh nghia cau truc sinh vien don gian
typedef struct Node
{
    char name[MAX_L];
    char type[MAX_L];
    char author[MAX_L];
    int quantity;
    struct Node *leftChild;
    struct Node *rightChild;
} Node; // Ham cap phat dong thong tin 1 sinh vien moi
Node *makeNode(char *name, char *type, char *author, int quantity)
{
    Node *p = (Node *)malloc(sizeof(Node));
    strcpy(p->name, name);
    strcpy(p->type, type);
    strcpy(p->author, author);
    p->quantity = quantity;
    p->leftChild = NULL;
    p->rightChild = NULL;
    return p;
}
// Ham them thong tin sinh vien moi vao cay
// Cay ban dau co the rong
// Cach 1. Tra ve qua ten ham
Node *insert(Node *r, char *name, char *type, char *author, int quantity)
{
    if (r == NULL)
        return makeNode(name, type, author, quantity); // cay ban dau rong
    int c = strcmp(r->name, name);
    if (c == 0)
    {
        printf("Student %s exists, do not insert\n", name);
        return r;
    }
    else if (c < 0)
    {
        r->rightChild = insert(r->rightChild, name, type, author, quantity);
        return r;
    }
    else
    {
        r->leftChild = insert(r->leftChild, name, type, author, quantity);
        return r;
    }
}
Node *find(Node *r, char *name)
{
    if (r == NULL)
        return NULL;
    int c = strcmp(r->name, name);
    if (c == 0)
        return r;
    if (c < 0)
        return find(r->rightChild, name);
    return find(r->leftChild, name);
}
Node *findMin(Node *r)
{
    if (r == NULL)
        return NULL;
    Node *lmin = findMin(r->leftChild);
    if (lmin != NULL)
        return lmin;
    return r;
}
Node *removeNode(Node *r, char *name)
{
    if (r == NULL)
        return NULL;
    int c = strcmp(r->name, name);
    if (c > 0)
        r->leftChild = removeNode(r->leftChild, name);
    else if (c < 0)
        r->rightChild = removeNode(r->rightChild, name);
    else
    {
        if (r->leftChild != NULL && r->rightChild != NULL)
        {
            Node *tmp = findMin(r->rightChild);
            strcpy(r->name, tmp->name);
            strcpy(r->type, tmp->type);
            strcpy(r->author, tmp->author);
            r->quantity = tmp->quantity;
            r->rightChild = removeNode(r->rightChild, tmp->name);
        }
        else
        {
            Node *tmp = r;
            if (r->leftChild == NULL)
                r = r->rightChild;
            else
                r = r->leftChild;
            free(tmp);
        }
    }
    return r;
}
void borrow(Node *r, char *a)
{
    if (r == NULL)
        return;
    Node *p = find(r, a);
    if (p == NULL)
        return;
    if (p->quantity == 0)
        printf("sach da duoc muon het\n");
    p->quantity = p->quantity - 1;
    printf("muon sach thanh cong\n");
}
void back(Node *r, char *a)
{
    if (r == NULL)
        return;
    Node *p = find(r, a);
    if (p == NULL)
        return;
    p->quantity = p->quantity + 1;
    printf("tra sach thanh cong\n");
}
void out(Node *r)
{
    if (r == NULL)
    printf("ds trong\n");
    if (r->quantity == 0)
        printf("%s\n", r->name);
    out(r->leftChild);
    out(r->rightChild);
}
void typeprint(Node *r, char *a)
{
    if (r == NULL)
        printf("ds trong\n");
    int c = strcmp(r->type, a);
    if (c == 0)
        printf("%s\n", r->name);
    if (c < 0)
        typeprint(r->rightChild, a);
    typeprint(r->leftChild, a);
}
Node *load(char *filename)
{
    Node *root = NULL;
    FILE *f = fopen(filename, "r");
    if (f == NULL)
        printf("Load data -> file not found\n");
    root = NULL;
    while (!feof(f))
    {
        char name[256], type[256], author[256];
        int quantity;
         fgets(name, 100, f);
         fgets(type, 100, f);
         fgets(author, 100, f);
         fscanf(f,"%d",quantity);
        root = insert(root, name, type, author, quantity);
    }
    fclose(f);
    return root;
}
int main(){
    Node *r = NULL;
    char c[] =" book.txt";
    load(c);
    char a[MAX];
    scanf("%s",a);
    borrow(r, a);
    return 0;
}
