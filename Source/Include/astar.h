#ifndef astar_h
#define astar_h

#include <algorithm>
#include <functional>
#include <map>
#include <set>
#include <queue>
#include <vector>

#include "bdg_math.h"

namespace bdg_astar {
  
class SearchNode {
 public:
  Vec2i currentPos;
  //int cur_result_index;
  int prevResultIndex;

  float elapsedCost;
  float heuristicCost;

  float getTotalCost() { return elapsedCost + heuristicCost; }

  static bool cmp(SearchNode left, SearchNode right) { return left.getTotalCost() < right.getTotalCost(); };

  bool operator < (const SearchNode& other) const {return SearchNode::cmp(*this, other);}
};

using SearchPQueue = std::priority_queue<SearchNode, std::vector<SearchNode>>;

using Link = std::pair<Vec2i, float>;


class AStar {
 public:
  AStar();
  
  void requestPath(Vec2i startPosn,
		   std::set<Vec2i> destinations,
		   std::function<std::vector<Link>(Vec2i)> expand);

  bool tick();

  std::vector<Vec2i> getSolution();

 protected:
  float calcSingleHeuristic(Vec2i startPos, Vec2i destPos);
  float calcShortestHeuristic(Vec2i startPos);
  int findResult(Vec2i pos);

 private:
  std::set<Vec2i> m_destinations;

  std::vector<SearchNode> m_bestResults;
  std::function<std::vector<Link>(Vec2i)>  m_expandFunc;

  SearchPQueue m_searchQueue;

  float m_solutionLength;
  int m_endingIndex;
};

} // namespace bdg_astar
#endif // astar_h
