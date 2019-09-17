/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

//lets get this bread!

#include <utility>
#include <algorithm>
#include <cmath>

using namespace std;
// returns true if the first vector is smaller than the second vector at the given dimension
template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    if (curDim < 0){
        return false;
    }
    if (first[curDim] < second[curDim]){
        return true;
    } else if (first[curDim] > second[curDim]){
        return false;
    }

    return (first < second);
}
//returns if it should replace a based on the smallest euclidean distance away
template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    double curr_dist = getDistance(target, currentBest);
    double pot_dist = getDistance(target, potential);
    if (pot_dist == curr_dist){
        return (potential < currentBest);
    }
    return (pot_dist < curr_dist) ;
}

/**
 * Constructs a KDTree from a vector of Points, each having dimension Dim.
 */
template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    points = newPoints;
    root = NULL;
    if (!points.empty()){
        root = constructor(0, points.size() - 1, 0);
    }
}

// made this to help recurse adding points
// left = beginning index
// right = ending index
template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::constructor(int left, int right, int dim) {
  if (left > right){
      return NULL;
  }
    int middle = (left + right) / 2;
    int curr_dim = (dim + 1) % Dim;

    Point<Dim> point = quickSelect(left, right, middle, dim);
    KDTreeNode* temp = new KDTreeNode(point);

    //recursively build the tree
    temp->left = constructor(left, middle - 1, curr_dim);
    temp->right = constructor(middle + 1, right, curr_dim);
    return temp;
}

// made this to sort vector with the addition of partition
//left = beginning index
//right = ending index
//middle = median index
template <int Dim>
Point<Dim> KDTree<Dim>::quickSelect(int left, int right, int middle, int dim) {

    if (left == right){
        return points[left];
    }
    int new_middle = partition(left, right, middle, dim);
    if (new_middle == middle) {
      return points[middle];
    } else if (middle < new_middle){
        return quickSelect(left, new_middle - 1, middle, dim);
    }
    return quickSelect(new_middle + 1, right, middle, dim);
}

//necesary function to implement quick select properly
//left = beginning index
//right = ending index
//middle = median index
template <int Dim>
int KDTree<Dim>::partition(int left, int right, int middle, int dim) {

    Point<Dim> middle_point = points[middle];

    swap(points[middle], points[right]);

    int new_middle = left;

    //shoulda done quick sort, but were in too deep
    for (int i = left; i < right; i++) {
        if (!smallerDimVal(middle_point,points[i], dim)) {
            swap(points[new_middle], points[i]);
            new_middle++;
        }
    }
    swap(points[right], points[new_middle]);
    return new_middle;

}

/**
 * Copy constructor for KDTree.
 */
template <int Dim>
KDTree<Dim>::KDTree(const KDTree& other) {
    root = copy(other.root);
    return *this;
}
//made function to make it copying simpler
template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::copy(const KDTreeNode* subRoot)
{
    if (subRoot == NULL){
        return NULL;
    }

    KDTreeNode* newNode = new KDTreeNode(subRoot->elem);
    newNode->left = copy(subRoot->left);
    newNode->right = copy(subRoot->right);
    return newNode;
}

// Assignment operator
template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree& rhs) {

    if (this != &rhs) {
        clear(root);
        root = copy(rhs.root);
    }
    return *this;
}
//made to make easier to delete
template <int Dim>
KDTree<Dim>::~KDTree() {

    clear(root);
}
//recursively delete nodes
template <int Dim>
void KDTree<Dim>::clear(KDTreeNode* subRoot)
{
    if (subRoot == NULL){
        return;
    }
    clear(subRoot->left);
    clear(subRoot->right);
    delete subRoot;
}

/**
 * This function takes a reference to a template parameter
 * Point and returns the Point closest to it in the tree. We are defining closest here to be the
 * minimum Euclidean distance between elements.
 */
template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    return findNearestNeighbor(query, root, 0);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query, KDTreeNode* subRoot, int dim) const
{
    // return the point if left and right are null
    if (subRoot->left == NULL && subRoot->right == NULL){
        return subRoot->point;
    }
    // if the point is itself, we are done
    if(subRoot->point == query){
        return subRoot->point;
    }

    Point<Dim> nearestNeighbor;
    Point<Dim> best_rn = subRoot->point;
    int nextDim = (dim + 1) % Dim;

    //initialized to see if the query is smaller than the point at the given dimension, if so, we know to move left in the tree
    bool check_left = smallerDimVal(query, subRoot->point, dim);

    //recursive check to get to the point as close as possible
    if (check_left){
        if (subRoot->left != NULL){
            nearestNeighbor = findNearestNeighbor(query, subRoot->left, nextDim);
        }
    } else if (!check_left){
        if (subRoot->right != NULL){
            nearestNeighbor = findNearestNeighbor(query, subRoot->right, nextDim);
        }
    }
    //checking which is closer best_rn or the nearest neigbhor
    if (shouldReplace(query, best_rn, nearestNeighbor)){
        best_rn = nearestNeighbor;
    }

    //original distance of the subroot point
    double subroot_dist = getDistance(query, best_rn);

    //getting the distance to the closest point rn
    double nn_dist = getDistance(query, best_rn);

    // checking if the other roots will be closer
    /*if (subroot_dist <= nn_dist){
        if (check_left && subRoot->right){
            nearestNeighbor = findNearestNeighbor(query, subRoot->right, nextDim );
            if (shouldReplace(query, best_rn, nearestNeighbor)){
                best_rn = nearestNeighbor;
            }
        } else if (!check_left && subRoot->left){
            nearestNeighbor = findNearestNeighbor(query, subRoot->left, nextDim );
            if (shouldReplace(query, best_rn, nearestNeighbor)){
                best_rn = nearestNeighbor;
            }
        }
    }*/

    return best_rn;
}
//function used to get distance between two points.
template <int Dim>
double KDTree<Dim>::getDistance(const Point<Dim>&first, const Point<Dim>&second) const{
    double dist = 0;
    for (unsigned i =0; i < Dim; i++){
        dist += (first[i] - second[i])*(first[i] - second[i]);
    }
    return dist;
}
