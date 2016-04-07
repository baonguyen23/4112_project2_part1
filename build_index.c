#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "p2random_v2.c"
#include <limits.h>


int CAP = 100;

int cmpfunc (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

int main(int argc, char** argv) {
  if(argc < 5 || strcmp("build", argv[1]) !=0 ){
    printf("Usage: build K P <fanouts> \n ");
    printf("argc %d \n", argc);
    printf("%d\n",strcmp("build", argv[1]));
    return 0;
  }
  //gather input
  int levels_n = argc - 4;
  int k = atoi(argv[2]);
  int p = atoi(argv[3]);
  int fanouts[levels_n];
  for(int f = 0; f<levels_n; f++){
    fanouts[f] = atoi(argv[4+f]);
  }

  //initialize an array to store how large each level should be
  int level_sizes[levels_n];
  for(int l = 0; l<levels_n; l++){
    level_sizes[l] = 0;
  }

  //find size for each level
  int i = 0;
  int should_do[levels_n];
  for(int l=0; l<levels_n; l++){
    should_do[l] = 1;
  }
  int current = levels_n - 1;

  while(i < k){
    while(should_do[current] == 0){
      current -= 1;
    }

    if(current < 0){
      printf("Error: Not enough keys! \n");
      return 0;
    }

    level_sizes[current]++;

    for(int reset=levels_n-1; reset > current; reset--){
      should_do[reset] = 1;
    }

    if(level_sizes[current] % (fanouts[current] - 1 ) == 0){
      should_do[current] = 0;
    }
    current = levels_n - 1;
    i++;
  }

  //find padding for each level and total index size
  int total_index_size=0;
  for(int i=0; i < levels_n; i++){
    printf("levels[%d] = %d\n", i, level_sizes[i]);
    level_sizes[i] += (level_sizes[i] % (fanouts[i]-1));
    total_index_size += level_sizes[i];
  }

  //create index
  int index[total_index_size];
  for(int i=0; i<total_index_size; i++){
    index[i] = INT_MAX;
  }

  int level_counts[levels_n];

  int level_starts[levels_n];
  level_starts[0] = 0;
  level_counts[0] = 0;
  for(int i=1; i<levels_n; i++){
    level_starts[i]= level_starts[i-1] + level_sizes[i-1];
    level_counts[i] = 0; //initialize
  }

  int level_locs[levels_n];
  memcpy(level_locs, level_starts, sizeof(int)*levels_n);

  i = 0;
  for(int l=0; l<levels_n; l++){
    should_do[l] = 1;
  }

  rand32_t *gen = rand32_init(time(NULL));
  size_t i, n = argc > 1 ? atoll(argv[1]) : 10;
  int32_t *keys = generate_sorted_unique(n, gen);
  free(gen);

  current = levels_n - 1;
  while(i < k){
    while(should_do[current] == 0){
      current -= 1;
    }

    level_counts[current]++;

    index[level_locs[current]] = keys[i];
    level_locs[current]++;

    for(int reset=levels_n-1; reset > current; reset--){
      should_do[reset] = 1;
    }

    if(level_counts[current] % (fanouts[current] - 1 ) == 0){
      should_do[current] = 0;
    }
    current = levels_n - 1;
    i++;
  }

  printf("\n[ ");
  int current_level = 1;
  for(int i=0; i<total_index_size; i++){

    if(index[i] == INT_MAX)
      printf("MI ");
    else printf("%d ", index[i]);

    if(i == level_starts[current_level]-1){
      printf("] \n[ ");
      current_level++;
    }
  }
  printf(" ] \n");

  free(keys);
  return 0;
}
