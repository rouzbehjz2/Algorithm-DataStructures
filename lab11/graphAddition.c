#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "graphAddition.h"
#include "queuePublic.h"

// Static functions prototypes
static void graph_dfs_type_r (graph_t *, vertex_t *, int, edge_type_counters_t *);
static int graph_dfs_depth_r (graph_t *, vertex_t *, int);

/*
  This function counts the number of vertices reached while performing
  a breadth-first visit of the graph (temporary fields for 
  the graph's vertices are assumed to be clear).
*/
int graph_bfs_count (graph_t *g, vertex_t *n) {
  int counter = 0;
  queue_t *qp;
  vertex_t *d;
  edge_t *e;

  // Check parameters
  if (g == NULL || n == NULL) {
    fprintf (stdout, "Invalid graph or vertex.\n");
    return -1;
  }

  // Initialize queue
  qp = queue_init (g->nv);

  // Add initial vertex to the current open set
  n->color = GREY;
  n->pred = NULL;
  queue_put (qp, (void *)n);

  // Pick new vertex from the current open set (in LIFO order)
  while (!queue_empty_m (qp)) {
    queue_get (qp, (void **)&n);
    e = n->head;

    // Expand the current open set with the adjacent vertices
    while (e != NULL) {
      d = e->dst;
      if (d->color == WHITE) {
	 d->color = GREY;
	 d->pred = n;
	 queue_put (qp, (void *)d);
      }
      e = e->next;
    }

    // Close current vertex
    n->color = BLACK;

    // Update counter
    counter++;
  }

  // Dispose queue
  queue_dispose (qp, NULL);

  // Return number of vertices
  return counter;
}

/*
 * Maximum distance between the initial vertex and any other vertex
 * reached while performing a breadth-first visit of the graph
 * (equal to the height of the visit tree).
 */
int graph_bfs_distance (graph_t *g, vertex_t *n) {
  int maxDist = 0;
  queue_t *qp;
  vertex_t *d;
  edge_t *e;

  // Check parameters
  if (g == NULL || n == NULL) {
    printf ("Invalid graph or vertex.\n");
    return -1;
  }

  // Initialize queue
  qp = queue_init (g->nv);

  // Add initial vertex to the current open set
  n->color = GREY;
  n->dist = 0;
  n->pred = NULL;
  queue_put (qp, (void *)n);

  // Pick new vertex from the current open set (in LIFO order)
  while (!queue_empty_m (qp)) {
    queue_get (qp, (void **)&n);
    e = n->head;

    // Expand the current open set with the adjacent vertices
    while (e != NULL) {
      d = e->dst;
      if (d->color == WHITE) {
        d->color = GREY;
        d->dist = n->dist + 1;
        d->pred = n;
        queue_put (qp, (void *)d);

        // Update current max distance
        if (d->dist > maxDist) {
          maxDist = d->dist;        
        } 
      }
      e = e->next;
    }

    // Close current vertex
    n->color = BLACK;
  }

  // Dispose queue
  queue_dispose (qp, NULL);

  // Return max distance
  return maxDist;
}

/*
 * Compute the number of tree, forward, backward and cross edges
 * encountered while performing a depth-first visit of the graph
 * from the initial vertex n
 */
edge_type_counters_t *graph_dfs_type (graph_t *g, vertex_t *n) {
  // Check parameters
  if (g == NULL || n == NULL) {
    fprintf (stdout, "Invalid graph or vertex.\n");
    return NULL;
  }

  // Allocate and initialize edge type counters
  edge_type_counters_t *counters = (edge_type_counters_t*) util_calloc
    (1, sizeof(edge_type_counters_t));

  // Compute edge type counters through a recursive depth-first visit
  graph_dfs_type_r (g, n, 0, counters);

  // Return edge type counters
  return counters;
}

void graph_dfs_type_r (
  graph_t *g, vertex_t *n, int currTime, edge_type_counters_t* counters
) {
  edge_t *e;
  vertex_t *tmp;

  // Set current vertex as open
  n->color = GREY;
  n->disc_time = ++currTime;

  // Scan each vertex adjacent to the current one
  e = n->head;
  while (e != NULL) {
    tmp = e->dst;

    // Update edge type counters
    switch (tmp->color) {
      case WHITE: 
        (counters->t)++; 
        break;
      case GREY: 
        (counters->b)++; 
        break;
      case BLACK: 
        if (n->disc_time < tmp->disc_time) {
          (counters->f)++; 
        } else {
          (counters->c)++; 
        }
    }

    // Recurr on adjacent veritices not currently open or closed
    if (tmp->color == WHITE) {
      tmp->pred = n;
      graph_dfs_type_r (g, tmp, currTime, counters);
    }
    e = e->next;
  }

  // Close current vertex
  n->color = BLACK;
  n->endp_time = ++currTime;

  return;
}

/*
 * Compute the depth of the depth-first visit tree starting
 * from the initial vertex n
 */
int graph_dfs_depth (graph_t *g, vertex_t *n) {
  // Check parameters
  if (g == NULL || n == NULL) {
    printf ("Invalid graph or vertex.\n");
    return -1;
  }

  // Compute depth through a recursive depth-first visit
  int depth = graph_dfs_depth_r (g, n, 0);

  // Return depth
  return depth;
}

int graph_dfs_depth_r (graph_t *g, vertex_t *n, int level) {
  edge_t *e;
  vertex_t *tmp;
  int maxLevel = level;
  int newLevel;

  // Set current vertex as open
  n->color = GREY;

  // Scan each vertex adjacent to the current one
  e = n->head;
  while (e != NULL) {
    tmp = e->dst;

    // Recurr on adjacent veritices not currently open or closed
    if (tmp->color == WHITE) {
      tmp->pred = n;
      newLevel = graph_dfs_depth_r (g, tmp, level+1);
      if(newLevel > maxLevel) {
        maxLevel = newLevel;      
      }
    }
    e = e->next;
  }

  // Close current vertex
  n->color = BLACK;

  // Return max level reached on the current subgraph
  return maxLevel;
}

/*
 * This is an helper function to print the graph
 */
void graph_print (graph_t *g) {
  edge_t *e;
  vertex_t *src, *dst;

  for (src=g->g; src!=NULL; src=src->next) {
    e = src->head;
    while (e != NULL) {
      dst = e->dst;
      fprintf (stdout, "X %d %d\n", src->id, dst->id);
      e = e->next;
    }
  }

  return;
}

#if 0
/*
 *  Compute maximum distance from origin
 */
void graph_dfs_max_path (graph_t *g, vertex_t *n) {
  int currTime=0;
  vertex_t *tmp, *tmp2;
  
  fprintf (stdout, "List of edges:\n");
  currTime = graph_dfs_r_max_path (g, n, currTime);
  for (tmp=g->g; tmp!=NULL; tmp=tmp->next) {
    if (tmp->color == WHITE) {
      currTime = graph_dfs_r_max_path (g, tmp, currTime);
    }
  }
  
  fprintf (stdout, "List of vertices:\n");
  for (tmp=g->g; tmp!=NULL; tmp=tmp->next) {
    tmp2 = tmp->pred;
    printf("%2d: %2d/%2d (%d)\n",
      tmp->id, tmp->disc_time, tmp->endp_time,
      (tmp2!=NULL) ? tmp->pred->id : -1); 
  }

  return;
}
#endif

/*
 *  perform recursive DFS from vertex i: 
 *  labels nodes with td/tq, edges as T/F/B/C
 */
void graph_dfs_r_dag_max_path (graph_t *g, vertex_t *n, int currTime) {
  edge_t *e;
  vertex_t *tmp;

  if (currTime <= n->disc_time)
    return;
  
  n->disc_time = currTime;
  e = n->head;
  while (e != NULL) {
    currTime = n->disc_time + e->weight;
    tmp = e->dst;
    graph_dfs_r_dag_max_path (g, tmp, currTime);
    e = e->next;
  }

  return;
}

/*
 *  perform recursive DFS from vertex i: 
 *  labels nodes with td/tq, edges as T/F/B/C
 */
void graph_dfs_r_max_path (graph_t *g, vertex_t *n, int currTime) {
  edge_t *e;
  vertex_t *tmp;

  n->color = GREY;
  if (currTime <= n->disc_time)
    return;
  
  n->disc_time = currTime;
  e = n->head;
  while (e != NULL) {
    currTime = n->disc_time + e->weight;
    tmp = e->dst;
    if (tmp->color == WHITE) {
      graph_dfs_r_max_path (g, tmp, currTime);
    }
    e = e->next;
  }
  n->color = WHITE;

  return;
}

