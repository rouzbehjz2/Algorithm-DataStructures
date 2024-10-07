#ifndef _TREE_PUBLIC_INCLUDED
#define _TREE_PUBLIC_INCLUDED

#include "data.h"

#define PREORDER  -1
#define INORDER    0
#define POSTORDER  1

typedef struct node node_t;

data_t getData (node_t *);
node_t *createEmptyTree ();
node_t *readTree(FILE *);
node_t *searchI (node_t *, data_t);
node_t *searchR (node_t *, data_t);
node_t *treeMinI (node_t *);
node_t *treeMinR (node_t *);
node_t *treeMaxI (node_t *);
node_t *treeMaxR (node_t *);
node_t *insert(node_t *, data_t);
node_t *delete(node_t *, data_t);
void writeTree(FILE *, node_t *, int);
void freeTree(node_t *);

int count_r(node_t *root);
int height_r(node_t *root);

void countNode (node_t *, int *);
int countNodeBis (node_t *, int *);
void countLevel (node_t *, int *, int);
void countPath (node_t *, int *, int *);

int visitVer1 (node_t *, int, int);
int visitVer2 (node_t *, int, int);

#endif

