#pragma once

static inline void rtrim(std::string &s);
bool tree_equals_output(stringstream & s, string filename);
void compareBinaryFiles( string yourFile, string ourFile );

template <int Dim>
void writeKdTreeToFile(const KDTree<Dim>& tree, string fname)
{
  ofstream outputFile(fname, ofstream::out);
  tree.printTree(outputFile, colored_out::DISABLE, -1);
  outputFile.close();
}

//
// Simple Constructor
//
template <int K>
void _test_linear_constructor(int size) {
  vector<Point<K>> points;
  points.reserve(size);
  for (int i = 0; i < size; i++) {
      Point<K> p;
      for (int j = 0; j < K; j++)
          p[j] = i;
      points.push_back(p);
  }

  KDTree<K> tree(points);
  std::string fname = "test_result_kdtree_"+to_string(K)+"_"+to_string(size)+".kd";
  writeKdTreeToFile(tree,fname);
  compareBinaryFiles(fname, "../tests/expected_kdtree_"+to_string(K)+"_"+to_string(size)+".kd" );
  REQUIRE(true);
}

//
// Simple Nearest Neighbor
//
template <int K>
void _test_linear_nearestNeighbor(int size) {
  vector<Point<K>> points;
  points.reserve(size);
  for (int i = 0; i < size; i++) {
      Point<K> p;
      for (int j = 0; j < K; j++)
          p[j] = i;
      points.push_back(p);
  }

  KDTree<K> tree(points);
  for (int i = 0; i < size; i++) {
    REQUIRE ( tree.findNearestNeighbor(points[i]) == points[i] );
  }
}