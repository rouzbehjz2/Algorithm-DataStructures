#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "graphAddition.h"
#include "queuePublic.h"

// Static functions prototypes
static int graph_hamiltonian_cycle_r (vertex_t *, vertex_t *, int, queue_t **);
static int graph_euler_cycle_r (vertex_t *, vertex_t *, int, queue_t **);
static int graph_count_edges (vertex_t *);
static int graph_clean (vertex_t *);
static void graph_print_path (queue_t *);

/*
 * Hamiltonian cycle (if it exists).
 */
void graph_hamiltonian_cycle (
  vertex_t *g, int nv, vertex_t *src
) {
  queue_t *hamiltonianCycle = NULL;

  // Check parameters
  if (g==NULL || src == NULL) {
    printf ("Invalid graph or vertices.\n");
    return;
  }

  // Clean graph
  graph_clean(g);

  // Compute and print Hamiltonian cycle (if it exists)
  graph_hamiltonian_cycle_r(src, src, nv, &hamiltonianCycle);

  if(hamiltonianCycle != NULL) {
    printf("Hamiltonian cycle:\n\t");
    graph_print_path(hamiltonianCycle);
    queue_dispose(hamiltonianCycle, NULL);
    printf("\n");
  } else {
    printf("There is no Hamiltonian cycle in the graph\n");
  }
}

static int graph_hamiltonian_cycle_r (
  vertex_t *src, vertex_t *dst, int n, queue_t **hamiltonianCycle
) {
  edge_t *e;
  vertex_t *tmp;

  // Skip already visited nodes
  if (src->color == BLACK)
    return 0;

  // Mark current node as visited and update left to visit nodes count
  src->color = BLACK;
  n--;

  // If no nodes are left to vist we have found a Hamiltonian cycle
  if (n == 0) {
    e = src->head;
    while (e != NULL) {
      tmp = e->dst;
      if(tmp == dst) {
        *hamiltonianCycle = queue_init(0);
        queue_put(*hamiltonianCycle, (void *)src);
        return 1;
      }
      e = e->next;
    }
    return 0;
  }

  // Process neighbours
  e = src->head;
  while (e != NULL) {
    tmp = e->dst;

    // Recurr on neighbor, winding up recursion if a Hamiltonian cycle was found
    if(graph_hamiltonian_cycle_r(tmp, dst, n, hamiltonianCycle)) {
      queue_put(*hamiltonianCycle, (void *)src);
      return 1;
    }
    e = e->next;
  }

  // Backtrack
  src->color = WHITE;
  
  return 0;
}

/*
 * Euler cycle (if it exists).
 */
void graph_euler_cycle (vertex_t *g, int nv, vertex_t *src) {
  queue_t *eulerCycle = NULL;
  int ne = 0;

  // Check parameters
  if (g==NULL || src==NULL) {
    printf ("Invalid graph or vertices.\n");
    return;
  }

  // Clean graph
  graph_clean (g);

  // Count number of edges
  ne = graph_count_edges (g);

  // Compute and print Euler cycle (if it exists)
  graph_euler_cycle_r (src, src, ne, &eulerCycle);

  if (eulerCycle != NULL) {
    printf("Euler cycle:\n\t");
    graph_print_path (eulerCycle);
    queue_dispose (eulerCycle, NULL);
    printf("\n");
  } else {
    printf("There is no Euler cycle in the graph\n");
  }

  return;
}

int graph_euler_cycle_r (
  vertex_t *src, vertex_t *dst, int n, queue_t **eulerCycle
) {
  edge_t *e;

  /* If no edges are left to visit and we are on destination
     then we have found an Euler cycle
  */
  if (n == 0 && src == dst) {
    *eulerCycle = queue_init(0);
    queue_put(*eulerCycle, (void *)src);
    return 1;
  }

  // Process neighbours
  e = src->head;
  while (e != NULL) {

    // Skip already visited edges
    if (e->color != WHITE) {
      e = e->next;
      continue;
    }

    // Mark current edge as visited
    e->color = BLACK;

    // Recurr on neighbor, winding up recursion if an Euler cycle was found
    if (graph_euler_cycle_r(e->dst, dst, n-1, eulerCycle)) {
      queue_put(*eulerCycle, (void *)src);
      return 1;
    }
  
    // Unmark current edge
    e->color = WHITE;
    e = e->next;
  }

  return 0;
}

/*
 * Helper function to clean vertex and edge attributes
 */
 
int graph_clean(vertex_t *g) {
  edge_t *e;
  vertex_t *tmp;

  for (tmp=g; tmp!=NULL; tmp=tmp->next) {
    tmp->color = WHITE;
    tmp->dist = INT_MAX;
    tmp->pred = NULL;
    tmp->scc = tmp->disc_time = tmp->endp_time = -1;
    
    e = tmp->head;
    while (e != NULL)  {
      e->color = WHITE;
      e = e->next;
    }
  }

  return (1);
}

/*
 * Helper function to print the graph
 */

void graph_print(vertex_t *g) {
  edge_t *e;
  vertex_t *src, *dst;
  for (src=g; src!=NULL; src=src->next) {
    e = src->head;
    while (e != NULL) {
      dst = e->dst;
      printf("X %d %d\n", src->id, dst->id);
      e = e->next;
    }
  }
}

/*
 * Helper function to print paths
 */
void graph_print_path(queue_t *path) {
  vertex_t *n;

  if(queue_empty_m(path))
    return;

  queue_get(path, (void **)&n);
  graph_print_path(path);
  printf("%d ", n->id);
}

/*
 * Helper function to count edges
 */
int graph_count_edges(vertex_t *g) {
  edge_t *e;
  vertex_t *tmp;
  int cont = 0;
  
  for (tmp=g; tmp!=NULL; tmp=tmp->next) {
    e = tmp->head;
    while (e != NULL)  {
      cont++;
      e = e->next;
    }
  }
  
  return cont;
}


