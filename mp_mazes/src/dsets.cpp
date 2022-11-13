/* Your code here! */
#include "dsets.h"


void DisjointSets::addelements(int num){
  for(int i = 1; i <= num; i++){
    elems.push_back(-1);
  }
}

int DisjointSets::find(int elem) {
    if (elems[elem] < 0) {
        return elem;
    }
    //path compression
    elems[elem] = find(elems[elem]);
    return elems[elem];
}

void DisjointSets::setunion(int a, int b) {
    int canonA = find(a);
    int canonB = find(b);
    if (canonA == canonB) {
        return;
    }
    //if B is less negative than A
    if (canonA < canonB) {
        elems[canonA] += elems[canonB];
        elems[canonB] = canonA;
    } else {
        elems[canonB] += elems[canonA];
        elems[canonA] = canonB;
    }
}

int DisjointSets::size(int elem) {
    return -1 * elems[find(elem)];
}