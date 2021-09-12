// kruskal.cpp

#include <algorithm>
#include <set>

#include "coord.h"
#include "kruskal.h"

// TODO test to ensure sort working in order

struct InternalEdge
{
  int distance;
  int index0, index1;
};

bool sortInternalEdge(InternalEdge a, InternalEdge b)
{
  return a.distance > b.distance;
}

std::vector<KruskPair> computeKruskal(std::vector<Coord> points)
{
  std::vector<KruskPair> outEdges;
  std::vector<InternalEdge> internalEdges;

  std::vector<std::set<int>> forest;

  for (int i = 0; i < points.size(); ++i) {
    std::set<int> pointSet;
    pointSet.insert(i);
    forest.push_back(pointSet);
  }

  for (int i = 0; i < points.size(); ++i) {
    Coord& pointI = points[i];
    for (int j = i + 1; j < points.size(); ++j) {
      Coord& pointJ = points[j];
      int dist = pointI.manhattanDist(pointJ);
      InternalEdge newInternalEdge;
      newInternalEdge.distance = dist;
      newInternalEdge.index0 = i;
      newInternalEdge.index1 = j;
      internalEdges.push_back(newInternalEdge);
    }
  }

  // sort by distance DECREASING
  std::sort(internalEdges.begin(), internalEdges.end(), sortInternalEdge);

  while (!internalEdges.empty()) {
    InternalEdge e = internalEdges.back();
    internalEdges.pop_back();

    int i = e.index0;
    int j = e.index1;

    int iIdx = -1;
    int jIdx = -1;
      
    for (int n = 0; n < forest.size(); ++n) {
      auto tree = forest[n];

      auto foundI = tree.find(i);
      auto foundJ = tree.find(j);

      if (foundI != tree.end()) {
	iIdx = n;
      }
      if (foundJ != tree.end()) {
	jIdx = n;
      }
    }

    if (iIdx != jIdx) {
      std::set<int> mergedTree;
      std::set<int> iTree = forest[iIdx];
      std::set<int> jTree = forest[jIdx];
	
      std::merge(iTree.begin(), iTree.end(),
		 jTree.begin(), jTree.end(),
		 std::inserter(mergedTree, mergedTree.begin()));
      forest[iIdx] = mergedTree;
      forest.erase(forest.begin() + jIdx);

      outEdges.push_back(KruskPair(i, j));
    }
  }
  
  return outEdges;
}
