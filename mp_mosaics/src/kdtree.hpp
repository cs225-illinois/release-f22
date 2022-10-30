/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    return (first[curDim] == second[curDim]) ? first < second : first[curDim] < second[curDim];
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    int current_distance = 0;
    int potential_distance = 0;
    for (size_t i=0; i < Dim; i++) {
      current_distance += (target[i] - currentBest[i])*(target[i] - currentBest[i]);
      potential_distance += (target[i] - potential[i])*(target[i] - potential[i]);
    }
    return (current_distance == potential_distance) ? potential < currentBest : potential_distance < current_distance;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    if(newPoints.empty()){
       root = NULL;
       size = 0;
    } else {
      vector<Point<Dim>> copied_pts = newPoints;
      constructor_helper(root, copied_pts, 0);
    }   
}

template <int Dim>
void KDTree<Dim>::constructor_helper(KDTreeNode*& subroot, vector<Point<Dim>>& points, int dimension) {
  if (points.size() == 0) {
    return;
  }
  if (points.size() == 1) {
      subroot = new KDTreeNode(points.at(0));
      return;
  }
  sortByK(points, dimension);
  size_t median = (points.size()-1)/2;
  vector<Point<Dim>> less;
  vector<Point<Dim>> more;
  if (median == 0) {
     vector<Point<Dim>> temp;
    subroot = new KDTreeNode(points.at(0));
    temp.push_back(points.at(1));
    if (smallerDimVal(temp[0], subroot->point, dimension)) {
      constructor_helper(subroot->left, temp, (dimension+1)%Dim);
    } else {
      constructor_helper(subroot->right, temp, (dimension+1)%Dim);
    }
  } else {
    for (size_t i = 0; i < median; ++i) {
    less.push_back(points.at(i));
  }
  for (size_t i = median+1; i < points.size(); ++i) {
    more.push_back(points.at(i));
  }
  
  subroot = new KDTreeNode(points.at(median));
  constructor_helper(subroot->left, less, (dimension+1)%Dim);
  constructor_helper(subroot->right, more, (dimension+1)%Dim);
  }
  
}

template <int Dim>
void KDTree<Dim>::sortByK(vector<Point<Dim>>& input, int k) {
  vector<Point<Dim>> temp;
  if (input.size() <= 1) {
    return;
  }
  size_t midpt = (input.size()) / 2;
  vector<Point<Dim>> left;
  vector<Point<Dim>> right;
  if (midpt == 0) {
    return;
  }
  for (size_t i = 0; i < midpt; ++i) {
    left.push_back(input.at(i));
  }
  for (size_t i = midpt; i < input.size(); ++i) {
    right.push_back(input.at(i));
  }
  sortByK(left, k);
  sortByK(right, k);
  temp = mergeSortByK(left, right, k);
  input = temp;

}
template <int Dim>
vector<Point<Dim>> KDTree<Dim>::mergeSortByK(vector<Point<Dim>>& list1, vector<Point<Dim>>& list2, int k) {
  size_t list1_index = 0;
  size_t list2_index = 0;
  vector<Point<Dim>> merged(list1.size() + list2.size());
  for (size_t i = 0; i < merged.size(); i++) {
    //one list empty, fill the rest with the other
    if (list1.empty() || list1_index >= list1.size()) {
      merged[i] = list2[list2_index];
      list2_index++;
    } else if (list2.empty() || list2_index >= list2.size()) {
      merged[i] = list1[list1_index];
      list1_index++;
    } else {
      //tie breaker condition
      if (list1[list1_index][k] == list2[list2_index][k]) {
        if (list1[list1_index] < list2[list2_index]) {
          merged[i] = list1[list1_index];
          list1_index++;
        } else {
          merged[i] = list2[list2_index];
          list2_index++;
        }
      } else if (list1[list1_index][k] < list2[list2_index][k]) {
        merged[i] = list1[list1_index];
        list1_index++;
      } else {
        merged[i] = list2[list2_index];
        list2_index++;
      }
    }
  }
  return merged;
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  copy_helper(root, other->root);
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  delete_helper(root);
  copy_helper(root, rhs->root);
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  delete_helper(root);
}

template <int Dim>
void KDTree<Dim>::delete_helper(KDTreeNode*& subroot) {
  if (subroot == NULL) {
    return;
  }
  delete_helper(subroot->left);
  delete_helper(subroot->right);
  delete subroot;
}

template<int Dim>
void KDTree<Dim>::copy_helper(KDTreeNode*& subroot, KDTreeNode*& other_subroot) {
  if (other_subroot == NULL) {
    return;
  }
  subroot = new KDTreeNode(other_subroot->point);
  copy_helper(subroot->left, other_subroot->left);
  copy_helper(subroot->right, other_subroot->right);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    Point<Dim> copied_query = query;
    Point<Dim> nearest_neighbor = root->point;
    find_nearest_neighbor_helper(root, nearest_neighbor, copied_query, 0);


    return nearest_neighbor;
}
template<int Dim>
void KDTree<Dim>::find_nearest_neighbor_helper(KDTreeNode* current, Point<Dim>& current_best, Point<Dim>& query, int k) const {
  if (current == NULL) {
    return;
  }
  KDTreeNode* first;
  KDTreeNode* second;
  if (smallerDimVal(current->point, query, k)) {
    first = current->right;
    second = current->left;
  } else {
    first = current->left;
    second = current->right;
  }
  //first becomes current, then recursively moves down the tree until hyperrectangle is found at leaf node
  find_nearest_neighbor_helper(first, current_best, query, (k+1)%Dim);

  current_best = (shouldReplace(query, current_best, current->point))? current->point: current_best;
  double best_radius = 0.0;
  for (size_t i = 0; i< Dim; i++) {
    best_radius += (current_best[i] - query[i])*(current_best[i] - query[i]);
  }
  double current_dist = (current->point[k] - query[k])*(current->point[k] - query[k]);
  if (best_radius >= current_dist) {
    //try again with second node
    find_nearest_neighbor_helper(second, current_best, query, (k+1)%Dim);
  }

}
