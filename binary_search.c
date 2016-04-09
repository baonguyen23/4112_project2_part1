#include <stdio.h>

int f[] = {3,2,3};

// generate

int binary_search(search_key, tree) {
  currLevel = 0;
  lastLevel = (sizeof(tree)/sizeof(tree[0]))-1;
  int i=0;
  // root node
  int startOfNode = 0;
  int endOfNode = sizeof(tree[currLevel])/sizeof(tree[currLevel][0]);
  //int lastKey = (sizeof(node)/sizeof(node[0]))-1;
  while (i <= endOfNode) {
    if (i != endOfNode) {
      if (search_key>tree[currLevel][i]) {
        i++;
      }
      else if (tree[currLevel][i] == search_key) {
        printf("Found! %d is present in the list.\n", search_value);
        break;
      }
      else if (tree[currLevel][i] == INT_MAX) {
        // calculate ith group in level
        int k;
        int fanoutCount=0;
        if (currLevel+1 <= lastLevel) {
          currLevel = currLevel+1;
          while (currLevel <= lastLevel) {
            keysPerNode = f[currLevel]-1;
            fanout = f[currLevel-1];
            int j;
            int currNode=1;
            int node_found =0;
            for (j=0; j<(sizeof(tree[currLevel])/sizeof(tree[currLevel][0]); j+=keysPerNode) {
              if (currNode%fanout == 0) {
                fanoutCount++;
              }
              if (fanoutCount == i) {
                node_found = 1;
                startOfNode = j+keysPerNode;
                endOfNode = startOfNode+keysPerNode;
                i = startOfNode;
                break;
              }
              else {
                currNode++;
              }
            }
            if (!node_found) {
              currLevel++;
            }
          }
          if (!node_found) {
            printf("Not found! %d is not present in the list.\n", search_value);
            break;
          }
        }
        else {
          printf("Not found! %d is not present in the list.\n", search_value);
          break;
        }
      }
      else {
        // calculate ith group in each level
        int k;
        if (currLevel+1 <= lastLevel) {
          currLevel = currLevel+1;
          keysPerNode = f[currLevel]-1;
          int j;
          int currNode=0;
          int node_found =0;

          for (j=0; j<(sizeof(tree[currLevel])/sizeof(tree[currLevel][0]); j+=keysPerNode) {
            if (currNode == i) {
              node_found = 1;
              startOfNode = j;
              endOfNode = j+keysPerNode;
              i = startOfNode;
              break;
            }
            else {
              currNode++;
            }
          }
        }
        else {
          // not found
        }
      }
    }
    else {
      // calculate ith group in each level
      int k;
      if (currLevel+1 <= lastLevel) {
        currLevel = currLevel+1;
        while (currLevel <= lastLevel) {
          keysPerNode = f[currLevel]-1;
          int j;
          int currNode=0;
          int node_found =0;
          // for all i in all levels
          // what if no i node when it gets to end
          for (j=0; j<(sizeof(tree[currLevel])/sizeof(tree[currLevel][0]); j+=keysPerNode) {
            if (currNode == i) {
              node_found = 1;
              startOfNode = j;
              endOfNode = j+keysPerNode;
              i = startOfNode;
              break;
            }
            else {
              currNode++;
            }
          }
          if (!node_found) {
            currLevel++;
          }
        }
        if (!node_found) {
          printf("Not found! %d is not present in the list.\n", search_value);
          break;
        }
      }
      else {
        printf("Not found! %d is not present in the list.\n", search_value);
        break;
      }
    }
  }
}
