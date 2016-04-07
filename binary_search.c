#include <stdio.h>

int n=47

// generate

// bit-mask needed
int binary_search(search_value, tree) {
  currLevel = 0
  lastLevel = (sizeof(tree)/sizeof(tree[0]))-1
  int node[];
  int i=0
  int found= 0;
  int lastKey = (sizeof(node)/sizeof(node[0]))-1
  node[] = tree[currLevel][i];
  while (!found) {
    if (i <= lastKey) {
      if (node[i]>search_value) {
        if (currLevel+1 <= lastLevel) {
          currLevel = currLevel+1
          node = tree[currLevel][i];
          lastKey = (sizeof(node)/sizeof(node[0]))-1;
          i=0;
        }
        else {
          // not found
          printf("Not found! %d is not present in the list.\n", search_value);
          break
        }
      }
      else if (root[i] == search_value) {
        found = 1;
        break
      }
      else {
        i++;
      }
    }
    else {
        if (currLevel+1 <= lastLevel) {
          currLevel = currLevel + 1;
          node = tree[currLevel][lastKey+1]
          lastKey = (sizeof(node)/sizeof(node[0]))-1;
          i=0;
        }
        else {
          // not found
          break
        }
      }
    }
  }
}
