#include <queue>
#include <algorithm>
#include <string>
#include <list>
#include <vector>

using namespace std;
/**
 * Returns an std::list of vertex keys that creates some shortest path between `start` and `end`.
 *
 * This list MUST include the key of the `start` vertex as the first vertex in the list, the key of
 * the `end` vertex as the last element in the list, and an ordered list of all vertices that must
 * be traveled along the shortest path.
 *
 * For example, the path a -> c -> e returns a list with three elements: "a", "c", "e".
 *
 * @param start The key for the starting vertex.
 * @param end   The key for the ending vertex.
 */
template <class V, class E>
std::list<std::string> Graph<V,E>::shortestPath(const std::string start, const std::string end) {


    std::unordered_map<string, bool> visited;
    std::unordered_map<string, string> predesscor;
    queue<string> queue;

    queue.push(start);
    visited[start] = true;
    bool done = false;
    string temp;

    while (!queue.empty() && done == false) {
        string u = queue.front();
//        cout<< " " << u <<endl;

        std::list<std::reference_wrapper<E>> edges = incidentEdges(u);
        typedef typename std::list<std::reference_wrapper<E>>::const_iterator iter;

        for (iter i = edges.begin(); i != edges.end(); i++) {
//            cout<< "here " << ((*i).get()).dest().key() <<endl;
//            cout<< "here " << ((*i).get()).source().key() <<endl;
            if((*i).get().dest().key() == u){
                temp = (*i).get().source().key();
            } else {
                temp = (*i).get().dest().key();
            }
//            cout<< "here " << temp <<endl;

            if (visited[temp] == false){

                visited[temp] = true;

                predesscor[temp] = u;
//                cout<< "here " << temp <<endl;
//                cout<< " " << u <<endl;

                queue.push(temp);

                if (!temp.compare(end)){
//                    cout<< "true, I should break" <<endl;
                    done = true;
                    break;
                }
            }
        }
        queue.pop();
    }
//    cout<< "-------------------- "<<endl;

    std::list<std::string> path;

    string crawl = end;
    path.push_front(crawl);
    while (predesscor[crawl] != start) {
       //cout<< "here 1" <<endl;
        path.push_front(predesscor[crawl]);
        crawl = predesscor[crawl];
    }
    path.push_front(start);


  return path;
}
