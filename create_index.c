#include <stdio.h>
// example of 3 level 3-2-3 tree
int h = 3;
int f[h] = {3,2,3};
int K = 9;
int i, j;

// no 0 level trees. throw error if no parameters.
// calculate max number of keys that could fit in tree
int calculate_max() {
  int totalMax;
  if (h==1)
    totalMax = f[0]-1;
  else {
    int lowestLevel = h;
    totalMax = 0;
    // calculate max for each level and sum to get max number of total keys
    while (lowestLevel > 0) {
      // max number of keys for one level
      int levelMax = 1;
      for (i=0; i<lowestLevel; i++) {
        if (i == lowestLevel-1)
          levelMax *= f[i] - 1;
        else
          levelMax *= f[i];
      }
      totalMax += levelMax;
      lowestLevel -= 1;
    }
  }
  return totalMax;

}

// after validating array of keys is appropriate size
// checks if too few keys by filling tree and checking if root is empty
// can't allocate max array for each level, so working in fanout-1 arrays at a time
void distribute_keys(sorted_keys) {
  keyIndex = 0;
  for (i=0; i<h; i++) {
    numOfKeys = f[i]-1;
    int node[numOfKeys];
    // keep inserting until node is filled
    int insertNum = 0;


    do this for fanout number of times
    while j < k
      while insert < numOfKeys {
      insert element into node
      insert++
      j++
    }
    if j < k
      insert element into parent node
    for (j=0; j<K; j++) {
      while (insertNum < numOfKeys) {
        node[insertNum] = sorted_keys[j];
        insertNum++;

      }
    }




  }

}
