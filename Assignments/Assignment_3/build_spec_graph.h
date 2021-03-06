///////////////////////////////////////////////////////////////////////////////
// Authors:         Rohit Kumar Sharma, M. Giri Prasanna
// NetID:           rsharma54, mugundakrish
// CSLogin:         rsharma, mgiriprasanna
// Email:           rsharma@cs.wisc.edu, mugundakrish@wisc.edu
// Created on:      October 25, 2018
//
///////////////////////////////////////////////////////////////////////////////

#include <time.h>
// #include "text_parsing.h"

#ifndef STRUCT_LIST_COMMANDS
#define STRUCT_LIST_COMMANDS
typedef struct command
{
    char *rule;
    struct command *next;
} command;
#endif

#ifndef STRUCT_TOKENS
#define STRUCT_TOKENS
typedef struct make_tokens
{
    char *token;
    struct make_tokens *next;
} make_tokens;
#endif

/**
 * Definition of the Node structure
 */
#ifndef STRUCT_MAKE_NODE
#define STRUCT_MAKE_NODE
typedef struct MakeNode
{
    char *name; // Tha name of the target
    time_t timestamp;
    int modify_build;
    command *rules;        // The list of commands to be executed for the target
    int isLeafNode;        // A flag which is 1 for a leaf node, else 0
    make_tokens *children; // An array of pointers to dependency names
} MakeNode;
#endif

#ifndef STRUCT_GRAPH_ADJ_LIST_NODE
#define STRUCT_GRAPH_ADJ_LIST_NODE
typedef struct graph_adj_list_node
{
    MakeNode *target;
    struct graph_adj_list_node *next;
} graph_adj_list_node;
#endif

#ifndef STRUCT_DIRECTED_GRAPH
#define STRUCT_DIRECTED_GRAPH
typedef struct directed_graph
{
    int targets_and_dependencies;
    int *visited_node;
    int *topological_num;
    struct graph_adj_list_node **dependencies;
} directed_graph;
#endif

void add_dependency(directed_graph *dag, MakeNode *target, MakeNode *dependency);
graph_adj_list_node *new_adj_list_node(MakeNode *target_node);
directed_graph *create_graph(int no_of_target_dependencies);
void print_graph(directed_graph *dag);
int depth_first_topological_traversal(directed_graph *dag, int node_num, int n);
graph_adj_list_node **topo_list(directed_graph *dag);
int index_head_node(directed_graph *dag, char *root);
int is_dag_cyclic(directed_graph *dag, int head_node_num);
int dfs_for_cycle(directed_graph *dag, int node_num, int *node_visit_status, MakeNode *parent, int head_node_num);
void delete_graph(directed_graph *graph, int num_nodes);
void print_modify_builds(directed_graph *graph);
