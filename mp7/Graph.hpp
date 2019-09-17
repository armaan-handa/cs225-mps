#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"

#include <string>
#include <iostream>
#include <utility>

/**
* @return The number of vertices in the Graph
*/
template <class V, class E>
unsigned int Graph<V,E>::size() const {
  // TODO: Part 2
  return vertexMap.size();
}


/**
* @return Returns the degree of a given vertex.
* @param v Given vertex to return degree.
*/
template <class V, class E>
unsigned int Graph<V,E>::degree(const V & v) const {
  // TODO: Part 2
  string key = v.key();
  return adjList[key].size();
}


/**
* Inserts a Vertex into the Graph by adding it to the Vertex map and adjacency list
* @param key The key of the Vertex to insert
* @return The inserted Vertex
*/
template <class V, class E>
V & Graph<V,E>::insertVertex(std::string key) {
  // TODO: Part 2
  V & v = *(new V(key));
  vertexMap.insert({key, v});
  std::list<edgeListIter> temp;
  adjList.insert(std::make_pair(key, temp));
  return v;
}


/**
* Removes a given Vertex
* @param v The Vertex to remove
*/
template <class V, class E>
void Graph<V,E>::removeVertex(const std::string & key) {
  // TODO: Part 2
  std::list<std::reference_wrapper<E>> edges = incidentEdges(key);
  typedef typename std::list<std::reference_wrapper<E>>::const_iterator iter;
  for (iter it = edges.begin(); it != edges.end(); it++){
    removeEdge((*it).get().source(), (*it).get().dest());
  }
  adjList.erase(key);
  vertexMap.erase(key);
}


/**
* Inserts an Edge into the adjacency list
* @param v1 The source Vertex
* @param v2 The destination Vertex
* @return The inserted Edge
*/
template <class V, class E>
E & Graph<V,E>::insertEdge(const V & v1, const V & v2) {
  // TODO: Part 2
  E & e = *(new E(v1, v2));
  edgeList.push_front(e);
  adjList[v1.key()].push_front(edgeList.begin());
  adjList[v2.key()].push_front(edgeList.begin());
  return e;
}


/**
* Removes an Edge from the Graph
* @param key1 The key of the ource Vertex
* @param key2 The key of the destination Vertex
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const std::string key1, const std::string key2) {
  // TODO: Part 2
  typedef typename std::list<E_byRef>::iterator iter;
  for (iter it = edgeList.begin(); it != edgeList.end(); it++){
    if((*it).get().source() == key1 && (*it).get().dest() == key2){
        typedef typename std::list<edgeListIter>::iterator iter2;
        iter2 it2 = adjList[key1].begin();

        while(*it2 != it){
          it2++;
        }
        adjList[key1].erase(it2);
        it2 = adjList[key2].begin();
        while(*it2 != it){
          it2++;
        }
        adjList[key2].erase(it2);
       removeEdge(it);
    }
  }
}


/**
* Removes an Edge from the adjacency list at the location of the given iterator
* @param it An iterator at the location of the Edge that
* you would like to remove
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const edgeListIter & it) {
  // TODO: Part 2
  edgeList.erase(it);
}


/**
* @param key The key of an arbitrary Vertex "v"
* @return The list edges (by reference) that are adjacent to "v"
*/
template <class V, class E>
const std::list<std::reference_wrapper<E>> Graph<V,E>::incidentEdges(const std::string key) const {
  // TODO: Part 2
  std::list<std::reference_wrapper<E>> edges;
  typedef typename std::list<edgeListIter>::const_iterator iter;
  for (iter it = adjList.at(key).begin(); it != adjList.at(key).end(); it++){
    edges.push_front(**it);
  }
  return edges;
}


/**
* Return whether the two vertices are adjacent to one another
* @param key1 The key of the source Vertex
* @param key2 The key of the destination Vertex
* @return True if v1 is adjacent to v2, False otherwise
*/
template <class V, class E>
bool Graph<V,E>::isAdjacent(const std::string key1, const std::string key2) const {
  // TODO: Part 2
  std::list<std::reference_wrapper<E>> edges = incidentEdges(key1);
  typedef typename std::list<std::reference_wrapper<E>>::const_iterator iter;
  for (iter it = edges.begin(); it != edges.end(); it++){
    if(((*it).get()).dest().key() == key2){
      return true;
    }
  }
  return false;
}
