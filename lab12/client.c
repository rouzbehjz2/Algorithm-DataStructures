#include <stdio.h>
#include "queuePublic.h"
#include "graph.h"
#include "graphAddition.h"

// Main function
int main(int argc, char *argv[])  {
  graph_t *g;
  vertex_t *src;
  int srcId;

  // Check command line parameters
  util_check_m (argc>=2, "missing parameter."); 

  // Load graph from file
  g = graph_load (argv[1]);

  // Source vertex
  fprintf (stdout, "Source vertex. ");
  scanf ("%d", &srcId);

  // Find source and destination vertices
  src = graph_find (g, srcId);

  // Find Hamiltonian cycle
  graph_hamiltonian_cycle (g->g, g->nv, src);

  // Find Euler cycle
  graph_euler_cycle (g->g, g->nv, src);

  // Free graph and return
  graph_dispose (g);
  
  return EXIT_SUCCESS;
}
