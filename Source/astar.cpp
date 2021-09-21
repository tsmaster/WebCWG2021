#include "astar.h"

using namespace bdg_astar;

AStar::AStar()
{
  m_solutionLength = -1.0f;
  m_endingIndex = -1;
}

void AStar::requestPath(Vec2i startPosn,
			std::set<Vec2i> destinations,
			std::function<std::vector<Link>(Vec2i)> expand,
			int maxLen)
{
  m_bestResults.clear();
  m_destinations = destinations;
  m_expandFunc = expand;
  m_maxLen = maxLen;

  float h = calcShortestHeuristic(startPosn);
  SearchNode startNode;
  startNode.currentPos = startPosn;
  startNode.prevResultIndex = -1;
  startNode.elapsedCost = 0;
  startNode.heuristicCost = h;
  m_searchQueue.push(startNode);
  m_bestResults.push_back(startNode);
}

int AStar::findResult(Vec2i pos) {
  for (int i = 0; i < m_bestResults.size(); ++i) {
    if (m_bestResults[i].currentPos == pos) {
      return i;
    }
  }
  return -1;
}

int AStar::countLengthForNode(SearchNode& n)
{
  if (n.prevResultIndex == -1) {
    return 1;
  }

  return countLengthForNode(m_bestResults[n.prevResultIndex]) + 1;
}

bool AStar::tick()
{
  if (m_searchQueue.size() == 0) {
    return (m_endingIndex >= 0);
  }
  
  SearchNode n = m_searchQueue.top();
  m_searchQueue.pop();

  int pathLen = countLengthForNode(n);
  if (pathLen > m_maxLen) {
    return false;
  }

  Vec2i currentPos = n.currentPos;
  int currentResultIndex = findResult(currentPos);

  for (Link neighborLink : m_expandFunc(currentPos)) {
    Vec2i newPos = neighborLink.first;
    float linkDist = neighborLink.second;

    float newElapsedDistance = n.elapsedCost + linkDist;
    float newHeuristicDistance = calcShortestHeuristic(newPos);
    if ((m_endingIndex >= 0) &&
	(newElapsedDistance + newHeuristicDistance > m_solutionLength)) {
      // can't do better than current solution, bail
      continue;
    }

    int newResultIndex = findResult(newPos);

    bool foundEnd = (m_destinations.find(newPos) != m_destinations.end());

    if (newResultIndex != -1) {
      // revisiting an existing node - is this chain better?
      if (newElapsedDistance >= m_bestResults[newResultIndex].elapsedCost) {
	continue;
      } else {
	// this is a better path to that node
	m_bestResults[newResultIndex].elapsedCost = newElapsedDistance;
	m_bestResults[newResultIndex].prevResultIndex = currentResultIndex;
	m_searchQueue.push(m_bestResults[newResultIndex]);

	if (foundEnd) {
	  if ((m_endingIndex < 0) || (newElapsedDistance < m_solutionLength)) {
	    m_solutionLength = newElapsedDistance;
	    m_endingIndex = newResultIndex;
	  }
	}
      }
    } else {
      // new node
      SearchNode newNode;

      newNode.currentPos = newPos;
      newNode.prevResultIndex = currentResultIndex;
      newNode.elapsedCost = newElapsedDistance;
      newNode.heuristicCost = newHeuristicDistance;

      m_bestResults.push_back(newNode);
      m_searchQueue.push(newNode);

      if (foundEnd) {
	if ((m_endingIndex < 0) || (newElapsedDistance < m_solutionLength)) {
	  m_solutionLength = newElapsedDistance;
	  m_endingIndex = m_bestResults.size() - 1;
	}
      }
    }
  }
  
  return false;
}

float AStar::calcSingleHeuristic(Vec2i startPos, Vec2i destPos)
{
  return startPos.distEuclid(destPos);
}

float AStar::calcShortestHeuristic(Vec2i startPos)
{
  float shortest = -1.0f;

  for (Vec2i destPos: m_destinations) {
    float h = calcSingleHeuristic(startPos, destPos);
    if ((shortest < 0.0f) || (h < shortest)) {
      shortest = h;
    }
  }

  return shortest;
}

std::vector<Vec2i> AStar::getSolution()
{
  std::vector<Vec2i> workList;

  int workIndex = m_endingIndex;
  while (workIndex >= 0) {
    workList.push_back(m_bestResults[workIndex].currentPos);
    workIndex = m_bestResults[workIndex].prevResultIndex;
  }

  std::reverse(workList.begin(), workList.end());
  return workList;
}
