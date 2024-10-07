#ifndef _GRAPHADDITION
#define _GRAPHADDITION

#include "graph.h"

// Type definitions
typedef struct {
  int t;
  int f;
  int b;
  int c;
} edge_type_counters_t;

// Eternal functions prototypes
extern int graph_bfs_count (graph_t *, vertex_t *);
extern int graph_bfs_distance (graph_t *, vertex_t *);
extern edge_type_counters_t *graph_dfs_type (graph_t *, vertex_t *);
extern int graph_dfs_depth (graph_t *, vertex_t *);
extern void graph_print (graph_t *);
extern void graph_dfs_r_dag_max_path (graph_t *, vertex_t *, int);
extern void graph_dfs_r_max_path (graph_t *, vertex_t *, int);

#endif
