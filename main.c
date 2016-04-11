#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "p2random_v2.c"
#include <limits.h>

typedef struct {
  int* level_sizes;
  int32_t  ** index;
  int didFail;
}RangeIndex;


// Builds the tree index.
// k = number of keys, levels_n = number of levels, fanouts = array of fanouts for each level
RangeIndex build_index(int k, int levels_n, int *fanouts){
  RangeIndex range_index;
  // Initialize an array to store how large each level should be
  int* level_sizes = malloc(levels_n * sizeof(int));
  for(int l = 0; l<levels_n; l++){
    level_sizes[l] = 0;
  }

  // Find size of each level
  int key = 0;
  int should_do[levels_n];
  for(int l=0; l<levels_n; l++){
    should_do[l] = 1;
  }
  int current = levels_n - 1;

  while(key < k){
    while(should_do[current] == 0){
      current -= 1;
    }
    // if there are still keys left over and tree is full, report error.
    if(current < 0){
      printf("Error: Too many build keys! \n");
      free(level_sizes);
      range_index.didFail = 1;
      return range_index;
    }

    level_sizes[current]++;

    for(int reset=levels_n-1; reset > current; reset--){
      should_do[reset] = 1;
    }

    if(level_sizes[current] % (fanouts[current] - 1 ) == 0){
      should_do[current] = 0;
    }
    current = levels_n - 1;
    key++;
  }

  // Find padding for each level
  for(int i=0; i < levels_n; i++){
    printf("levels[%d] = %d\n", i, level_sizes[i]);
    level_sizes[i] += (level_sizes[i] % (fanouts[i]-1));
  }

  // If root node is empty, there are too few keys and an error should be reported.
  if (level_sizes[0] == 0) {
    printf("Error: Too few build keys! \n");
    free(level_sizes);
    range_index.didFail = 1;
    return range_index;
  }

  // Create index
  int32_t  **index = malloc(sizeof(int32_t *)*levels_n);
  void *ptr;
  for(int i=0; i<levels_n; i++){
    if(posix_memalign(&ptr, 16, sizeof(int32_t ) * level_sizes[i]) != 0){
      printf("Failed to allocate memory\n");
      range_index.didFail = 1;
      return range_index;
    }
    index[i] = ptr;
  }

// Hold a count of how many keys we've added for each level
  int level_counts[levels_n];
  for(int i=0; i<levels_n; i++){
    level_counts[i] = 0; //initialize
  }

  key = 0;
  for(int l=0; l<levels_n; l++){
    should_do[l] = 1;
  }

  // Generate k random keys
  rand32_t *gen = rand32_init(time(NULL));
  int32_t *keys = generate_sorted_unique(k, gen);
  free(gen);

  current = levels_n - 1;
  int32_t  *level;
  // Initialze to MAX INT
  for(int i=0; i<levels_n; i++){
    level = index[i];
    for(int j=0; j<level_sizes[i]; j++){
      level[j] = INT_MAX;
    }
  }

  // Insert keys
  while(key < k){

    while(should_do[current] == 0){
      current -= 1;
    }

    level = index[current];
    level[level_counts[current]] = keys[key];
    level_counts[current]++;

    for(int reset=levels_n-1; reset > current; reset--){
      should_do[reset] = 1;
    }

    // If node full
    if(level_counts[current] % (fanouts[current] - 1 ) == 0){
      should_do[current] = 0;
    }

    current = levels_n - 1;
    key++;

  }

  // Clean up and return
  free(keys);
  range_index.index = index;
  range_index.level_sizes = level_sizes;
  return range_index;
}

// Finds next node to search through in next level
// stopKey = last key index, level = level to search through,
// startKey = first key to start searching at, probe = value to probe for
int findNextNode(int stopKey, int32_t * level,
  int startKey, int probe){
  for(int i = startKey; i<stopKey; i++){
    if(int32_cmp(&level[i], &probe) > 0){
      return i;
    }
  }
  return -1;
}

// Probes index using binary search for each node
// range_index = tree to probe, levels_n = number of levels,
// fanouts = array of fanouts for each level, probe = value to probe for
int probe(RangeIndex range_index, int levels_n,
  int* fanouts, int32_t  probe){
    int32_t * level;
    int nextNode = 0;
    int stopKey = range_index.level_sizes[0];
    // find the node to search through in the next level
    for(int level_idx = 0; level_idx<levels_n; level_idx++){
      level = range_index.index[level_idx];
      nextNode = findNextNode(stopKey,
                              level,
                              nextNode*fanouts[level_idx], probe);
      // If value to probe for is larger than all values in level, then must be in last node
      nextNode = (nextNode == -1) ? fanouts[level_idx]+1 : nextNode;
      if(level_idx +1 < levels_n){
            // get the last key of the next level
            stopKey = fanouts[level_idx]* (fanouts[level_idx+1]-1);
      }
    }
  return nextNode;
}

// Builds index and loads probe values. For each value, the index is probed
// and the range identifier is appended to an array. The array is then printed out.
// takes in command line arguments in the form: build K P 9 5 9
int main(int argc, char** argv) {
  if(argc < 4){
    printf("Usage: build K P <fanouts> \n ");
    return 0;
  }
  // Gathers input and builds index
  int levels_n = argc - 3;
  int k = atoi(argv[1]);
  int p = atoi(argv[2]);
  int* fanouts = malloc(levels_n * sizeof(int));
  for(int f = 0; f<levels_n; f++){
    fanouts[f] = atoi(argv[3+f]);
  }
  RangeIndex range_index = build_index(k, levels_n, fanouts);

  if(range_index.didFail == 1){
    free(fanouts);
    return 0;
  }

  int32_t  *level;
  for(int i=0; i<levels_n; i++){
    level = range_index.index[i];
    printf("\n[ ");
    for(int j=0; j<range_index.level_sizes[i]; j++){
      if(level[j] == INT_MAX)
      printf("MI ");
      else printf("%d ", level[j]);
    }
    printf(" ] \n");
  }

  // Generates P random values and probes index for each value
  rand32_t *gen = rand32_init(time(NULL));
  int32_t *probes = generate(p, gen);
  free(gen);

  for(int i = 0; i<p; i++){
    int range = probe(range_index, levels_n, fanouts, probes[i]);
    printf("probe %d: %d\n", probes[i], range);
  }

  //clean up
  for(int i=0; i<levels_n; i++){
    free(range_index.index[i]);
  }
  free(range_index.index);
  free(range_index.level_sizes);
  free(probes);
  return 0;
}
