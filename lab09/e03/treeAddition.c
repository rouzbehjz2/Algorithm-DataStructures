#include "treePrivate.h"

static int visit (node_t *, int);

/*
 *  recursively compute the number of nodes in the tree
 */
int count_r(node_t *root)
{
  int count=1;

  if (root == NULL) {
    return 0;
  }

  count += count_r(root->left);
  count += count_r(root->right);
  return count;
}

/*
 *  recursively compute the height of the tree
 */
int height_r(node_t *root)
{
  int hl, hr;

  if (root == NULL) {
    return -1;
  }

  hl = height_r(root->left);
  hr = height_r(root->right);
  return (hl>hr ? hl : hr) + 1;
}

void
countNode (
  node_t *root,
  int *vet
) {
  if (root==NULL) {
    return;
  }
  if (root->left==NULL && root->right==NULL) {
    vet[0]++;
  }
  if ((root->left!=NULL && root->right==NULL) ||
    (root->left==NULL && root->right!=NULL)) {
    vet[1]++;
  }
  if (root->left!=NULL && root->right!=NULL) {
    vet[2]++;
  }
  countNode (root->left, vet);
  countNode (root->right, vet);

  return;
}

int
countNodeBis (
  node_t *root,
  int *vet
) {
  int l, r;
  if (root==NULL) {
    return (0);
  }
  l = countNodeBis (root->left, vet);
  r = countNodeBis (root->right, vet);
  vet[l+r]++;

  return (1);
}

void
countLevel (
  node_t *root,
  int *vet,
  int h
) {
  if(root!=NULL) {
    vet[h-1]++;
    countLevel (root->left, vet, h-1);
    countLevel (root->right, vet, h-1);
  }

  return;
} 

void
countPath (
  node_t *root,
  int *np,
  int *length  
) {
  if (root==NULL) {
    return;
  }
  *length = *length + 1;
  if (root->left==NULL && root->right==NULL) {
    *np = *np + 1;
    return;
  }
  countPath (root->left, np, length);
  countPath (root->right, np, length);
  
  return;
}

/*
 *  It does NOT use the BST property.
 *  A node is found, and the function returns a value differnet from 0, when:
 *  - both keys are on the left child
 *  - both keys are on the right child
 *  - one key is on the left child and the other on the right child
 *  - one key is on the node and the other on the left child
 *  - one key is on the node and the other on the right child
 *  In all other cases the function returns 0.
 */

int visitVer1 (
  node_t *root,
  int key1,
  int key2
)
{
  int t_right, t_left, t_here;
  
  t_here = 0;
  t_right = t_left = 0;

  if (root != NULL) {
    if (compare (root->val, key1)==0 || compare(root->val, key2)==0) {
      t_here = 1;
    }
    t_left = visitVer1 (root->left, key1, key2);
    t_right = visitVer1 (root->right, key1, key2);
    if (t_left && t_right) {
      // Splitting node; one child on the left and one on the right
      // As for the BST version distance = left + right height
      printf("Distance between %d and %d: ", key1, key2);
      printf("%d edges\n", t_left+t_right);
    } else if (t_left || t_right) {
      if (t_here) {
        // One child on the left or on the right the other on this node
        // I return t_left if it is on the left and t_rith if it is on the right,
        // i.e., I always return t_left+t_right
        printf("Distance between %d and %d: ", key1, key2);
        printf("%d edges\n", t_left+t_right);
      } else {
        // On eis on the left or on the right and the other I do not know
        // I return t_left+1 or t_right+1, i.e., t_left+t_tight+1 being one = 0
        return t_left + t_right + 1;
      }
    }
  }
  
  return t_here;
}

/*
 *  Firsly it performs a common visit, then two separate visits
 */

int visitVer2 (
  node_t *root,
  int key1,
  int key2
)
{
  int d, d_left, d_right;
  
  if (root == NULL) {
    return (0);
  }

  if (compare (key1, root->val)<0 && compare(key2, root->val)<0) {
    d = visitVer2 (root->left, key1, key2);
  } else {
    if (compare (key1, root->val)>0 && compare(key2, root->val)>0) {
      d = visitVer2 (root->right, key1, key2);
    } else {
      d_left = visit (root, key1);
      d_right = visit (root, key2);
      d = d_left + d_right;
    }
  }

  return (d);
}

static int visit (
  node_t *root,
  int key
)
{
  int d;

  if (root == NULL) {
    return (-1);
  }

  if (compare (key, root->val) < 0) {
    d = visit (root->left, key);
    if (d>-1) {
      return (d+1);
    }
  }

  if (compare (key, root->val) > 0) {
    d = visit (root->right, key);
    if (d>-1) {
      return (d+1);
    }
  }

  // if (compare (root->val, key) == 0)
  return (0);
}
