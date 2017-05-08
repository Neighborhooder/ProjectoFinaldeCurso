#include <stdio.h>

struct Edge{
  int src, dest, weight;
};

struct Graph{
  int V, E;
  struct Edge *edge;
};

struct subset{
  int parent;
  int rank;
};

int find(struct subset subsets[], int i){
  if (subsets[i].parent != i){
    subsets[i].parent = find(subsets, subsets[i].parent);
  }
  return subsets[i].parent;
}


void Union(struct subset subsets[], int x,int y){

  int xroot = find(subsets, x);
  int yroot = find(subsets, y);

  if (subsets[xroot].rank < subsets[yroot].rank){
    subsets[xroot].parent = yroot;
  }
  else if (subsets[xroot].rank > subsets[yroot].rank){
    subsets[yroot].parent = xroot;
  }
  else{
    subsets[yroot].parent = xroot;
    subsets[xroot].rank++;
  }
}

void Boruvka(struct Graph* graph){
  int V =  graph -> V, E = graph -> E;
  int i, set1, set2;
  struct Edge *edge = graph -> edge;

  struct subset *subsets;

  int *cheapest;

  for (i =0; i < V; ++i) {
    subsets[V].parent = V;
    subsets[V].rank = 0;
    cheapest[V] = -1;
  }

  int numTrees = V;
  int ASTweight = 0;

  while(numTrees > 1){

    for(i = 0; i < E; i++){
      set1 = find(subsets, edge[i].src);
      set2 = find(subsets, edge[i].dest);

      if (set1 == set2){
        continue;
      }else{
        if (cheapest[set1] == -1 || edge[cheapest[set1]].weight > edge[i].weight){
          cheapest[set1] = i;
        }
        if (cheapest[set1] == -1 || edge[cheapest[set2]].weight > edge[i].weight){
          cheapest[set2] = i;
        }
      }

    }
    for(i = 0; i < V; i++){
      if (cheapest[i] != -1) {
        set1 = find(subsets, edge[cheapest[i]].src);
        set2 = find(subsets, edge[cheapest[i]].dest);

        if (set1 == set2){
          continue;
        }

        ASTweight += edge[cheapest[i]].weight;
        printf("Edge %d-%d included in AST with weight %d\n",edge[cheapest[i]].src, edge[cheapest[i]].dest, edge[cheapest[i]].weight );

        Union(subsets, set1, set2);
        numTrees--;
      }
    }
 }
 printf("Weight of AST is %d\n", ASTweight);
}

struct Graph *createGraph(int V,int E){
  struct Graph *graph;
  graph -> V  = V;
  graph -> E  = E;
  return graph;
}
int main(){
  //A B C D E
  //0 1 2 3 4



int V = 5;
int E = 8;
struct Graph *graph = createGraph(V, E);

//add edge A->B
graph -> edge[0].src = 0;
graph -> edge[0].dest = 1;
graph -> edge[0].weight = 6;

//add edge A->E

graph -> edge[1].src = 0;
graph -> edge[1].dest = 4;
graph -> edge[1].weight = 7;

//add edge B->C

graph -> edge[2].src = 1;
graph -> edge[2].dest = 2;
graph -> edge[2].weight = 5;

//add edge B->D

graph -> edge[3].src = 1;
graph -> edge[3].dest = 3;
graph -> edge[3].weight = 4;

//add edge B->E

graph -> edge[4].src = 1;
graph -> edge[4].dest = 4;
graph -> edge[4].weight = 8;

//add edge C->D

graph -> edge[5].src = 2;
graph -> edge[5].dest = 3;
graph -> edge[5].weight = 7;

//add edge C->E

graph -> edge[6].src = 2;
graph -> edge[6].dest = 4;
graph -> edge[6].weight = 3;

//add edge D->E

graph -> edge[3].src = 3;
graph -> edge[3].dest = 4;
graph -> edge[3].weight = 9;

Boruvka(graph);
return 0;


}
