/* Your code here! */
#include "dsets.h"
void DisjointSets::addelements(int num){
  for (int i = 0; i < num; i++){
    set.push_back(-1);
  }
}
int DisjointSets::find(int elem){
  if(set[elem] < 0){
    return elem;
  }
  else {
    return find(set[elem]);
  }
}
void DisjointSets::setunion(int a, int b){
  int aroot = find(a);
  int broot = find(b);
  if (aroot == broot){
    return;
  }
  int newSize = set[aroot] + set[broot];
  if(set[aroot] > set[broot]){
    set[aroot] = broot;
    set[broot] = newSize;
  }
  else {
    set[broot] = aroot;
    set[aroot] = newSize;
  }

}
int DisjointSets::size(int elem){
  return -set[find(elem)];
}
