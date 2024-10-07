#include "treePublic.h"

#define OK 1
#define KO 0

static void stats (node_t *);

int
main (
  void
   )
{
  node_t *root, *tmp;
  data_t d, d1, d2;
  int retValue, i, end = 0;
  char row[MAXC];
  FILE *fp = NULL;

  root = NULL;
  root = createEmptyTree();

  while (!end) {

    fprintf (stdout, "User selection\n");
    fprintf (stdout, "\t1) Insert one single node\n\t2) Cancel one single node\n\t3) Search a node\n");
    fprintf (stdout, "\t4) Print BST on stdout\n\t5) Write BST on file\n\t6) Read BST from file\n");
    fprintf (stdout, "\t7) Compute min and max\n\t8) Compute Stats\n\t9) Compute distance between tno nodes\n");
    fprintf (stdout, "\t10) End\n\t> ");
    scanf ("%s", row);

    switch (atoi(row)) {

      case 1:
        fprintf (stdout, "data: ");
	retValue = readData (stdin, &d);
        if (retValue==0) {
          fprintf (stderr, "Input error.\n");
          exit (0);
        }
	root = insert (root, d);
	break;

      case 2:
        fprintf (stdout, "data: ");
	retValue = readData (stdin, &d);
        if (retValue==0) {
          fprintf (stderr, "Input error.\n");
          exit (0);
        }
	root = delete (root, d);
	break;

      case 3:
        fprintf (stdout, "data: ");
	retValue = readData (stdin, &d);
        if (retValue==0) {
          fprintf (stderr, "Input error.\n");
          exit (0);
        }

	tmp = searchI (root, d);
	if (tmp != NULL) {
	  fprintf (stdout, "Iterative Search: Found -> ");
          writeData (stdout, getData(tmp));
	} else {
	  fprintf (stdout, "Iterative Search: Not Found\n");
        }
	tmp = searchR (root, d);
	if (tmp  != NULL) {
	  fprintf (stdout, "Recursive Search: Found -> ");
          writeData (stdout, getData(tmp));
	} else {
	  fprintf (stdout, "Recursive Search: Not Found\n");
        }
	break;

      case 4:
	writeTree (stdout, root, INORDER);
	break;

      case 5:
	fprintf (stdout, "File Name: ");
	scanf ("%s", row);

        if (strcmp (row, "stdout") == 0) {
          fp = stdout;
        } else {
   	  fp = fopen (row, "w");
        }

        if (fp == NULL) {
         fprintf (stderr, "Error Opening File %s\n", row);
         break;
	}

	writeTree (fp, root, PREORDER);

        if (strcmp (row, "stdout") != 0) {
	  fclose(fp);
	}
	break;

      case 6:
	fprintf (stdout, "File Name: ");
	scanf ("%s", row);

	fp = fopen (row, "r");
	if (fp == NULL) {
	  fprintf (stderr, "Error Opening File %s\n", row);
	} else {
	  freeTree (root);
	  root = readTree (fp);
	}
	break;

      case 7:
        fprintf (stdout, "Tree minimum iterative: "); 
        tmp = treeMinI (root);
        writeData (stdout, getData(tmp));
        fprintf (stdout, "Tree minimum recursive: "); 
        tmp = treeMinR (root);
        writeData (stdout, getData(tmp));
        fprintf (stdout, "Tree maximum iterative: ");
        tmp = treeMaxI (root);
        writeData (stdout, getData(tmp));
        fprintf (stdout, "Tree maximum recursive: "); 
        tmp = treeMaxR (root);
        writeData (stdout, getData(tmp));
	break;

      case 8:
        stats (root);
	break;

      case 9:
        fprintf (stdout, "key 1: ");
	retValue = readData (stdin, &d1);
        fprintf (stdout, "key 2: ");
	retValue = readData (stdin, &d2);
        i = visitVer1 (root, d1, d2);
        i = visitVer2 (root, d1, d2);
        printf("Distance between %d and %d: %d edges\n",
          d1, d2, i);
        break;

      case 10:
	end = 1;
	break;

      default:
	fprintf (stderr, "Unknown Option.\n");
	break;
    }
  }

  freeTree(root);

  return (OK);
}

void stats (node_t *root) {
  int height=-1, count=0;
  int i, *v1, *v2;
  int np, length;

  count = count_r(root);
  printf("Number of nodes: %d\n", count);

  height = height_r(root);
  printf("Tree height: %d\n", height);

  v1 = (int *) malloc (3 * sizeof (int));
  v2 = (int *) malloc (height * sizeof (int));
  if (v1==NULL || v2==NULL) {
    fprintf (stdout, "Alloction Error.\n");
    exit (1);
  }

  for (i=0; i<3; i++) {
    v1[i] = 0;
  }
  countNode (root, v1);
  fprintf (stdout, "#Node with 0-1-2 children (implementation 1): ");
  for (i=0; i<3; i++) {
    fprintf (stdout, "%d ", v1[i]);
  }
  fprintf (stdout, "\n");

  for (i=0; i<3; i++) {
    v1[i] = 0;
  }
  countNodeBis (root, v1);
  fprintf (stdout, "#Node with 0-1-2 children (implementation 2): ");
  for (i=0; i<3; i++) {
    fprintf (stdout, "%d ", v1[i]);
  }
  fprintf (stdout, "\n");

  for (i=0; i<height; i++) {
    v2[i] = 0;
  } 
  countLevel (root, v2, height);
  fprintf (stdout, "#Node for level: ");
  for (i=height-1; i>=0; i--) {
    fprintf (stdout, "l%d=%d ", i, v2[i]);
    if (i>0) {
      fprintf (stdout, " ");
    } else {
      fprintf (stdout, "\n");
    }
  }

  np = length = 0;
  countPath (root, &np, &length);
  fprintf (stdout, "#Path: %d\n", np);
  fprintf (stdout, "#Total Length: %d\n", length);

  return;
}

