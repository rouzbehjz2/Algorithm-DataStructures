#include <stdio.h>
#include "queuePublic.h"
#include "graph.h"
#include "graphAddition.h"

// Main function
int main (int argc, char *argv[]) {
  graph_t *g;
  vertex_t *v, *src;
  int i, n, count, distance, depth, max_path;
  edge_type_counters_t *counters;

  // Check command line parameters
  util_check_m (argc>=2, "missing parameter."); 

  // Load graph from file
  g = graph_load (argv[1]);

  count = distance = depth = max_path = 0;
  
  // Read initial vertex from user
  fprintf (stdout, "Initial vertex? ");
  scanf ("%d", &i);

  // Find initial vertex
  src = graph_find (g, i);

  // Count vertices performing BFS
  graph_attribute_init (g);
  count = graph_bfs_count (g, src);
  if (count != -1) {
    fprintf (stdout, "Number of vertices reached with BFS: %d\n",
      count);
  }

  // Maximum distance from initial vertex to any vertex reachable (with BFS)
  graph_attribute_init (g);
  distance = graph_bfs_distance (g, src);
  if (distance != -1) {
    fprintf (stdout, "Maximum distance using BFS: %d\n", distance);
  }

  // Compute number of tree, forward, backward and cross edges
  graph_attribute_init (g);
  counters = graph_dfs_type (g, src);
  if(counters != NULL) {
    fprintf (stdout, "Tree edges: %d\n", counters->t);
    fprintf (stdout, "Forward edges: %d\n", counters->f);
    fprintf (stdout, "Backward edges: %d\n", counters->b);
    fprintf (stdout, "Cross edges: %d\n", counters->c);
    free(counters);
  }

  // Compute depth of the depth-first visit tree
  graph_attribute_init (g);
  depth = graph_dfs_depth (g, src);
  if (depth != -1) {
    fprintf (stdout, "Depth of the visit tree starting from %d: %d\n", i, depth);
  }

  // Compute max path
  fprintf (stdout, "Max Path for: Dag (0), graph (1), or both (2)? ");
  scanf ("%d", &n);
  if (n==0 || n==2) {
    graph_attribute_init (g);
    graph_dfs_r_dag_max_path (g, src, 0);
    fprintf (stdout, "Max Path for DAG starting from %d:\n", i);
    v = g->g;
    while (v!=NULL) {
      fprintf (stdout, "Vertex=%d MaxPath=%d\n", v->id, v->disc_time);
      v = v->next;
    }
  }
  if (n==1 || n==2) {
    graph_attribute_init (g);
    graph_dfs_r_max_path (g, src, 0);
    fprintf (stdout, "Max Path for GRAPH starting from %d:\n", i);
    v = g->g;
    while (v!=NULL) {
      fprintf (stdout, "Vertex=%d MaxPath=%d\n", v->id, v->disc_time);
      v = v->next;
    }
  }

  // Free graph and return
  graph_dispose (g);
  
  return EXIT_SUCCESS;
}
