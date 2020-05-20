import math
from node_type import node_type

class graph0:

  '''
    Layer0 Graph

    @param nodeList: list of layer 0 nodes
    @param MAXD: count of neighbours next to a node that might be directly connected
    @param ALPHA: each edge can have ALPHA as maximum length
  '''
  def __init__(self, width, height):
    self.width = math.sqrt(width)
    self.height = math.sqrt(height)
  
  def getClosestNode(self, node):
    return None
  
  def getPath(self, startNode, endNode):
    # TODO
    def getNext(dist, nodeList):
      minD = 1000000
      nodeCount = len(dist)
      res = None

      for i in range(0, nodeCount):
        if nodeList[i].isVisited == False and minD > dist[i]:
          res = i
          minD = dist[i]
      
      return nodeList[res]

    startNode = self.getClosestNode(startNode)
    endNode = self.getClosestNode(endNode)
    res = []

    # dijkstra's algorithm        
    # initialise distance vector
    nodeCount = len(self.nodeList)
    dist = [1000000] * nodeCount

    # initialise starting node in vector
    curIndex = self.getNodeIndex(startNode)
    dist[curIndex] = 0

    for _ in range(0, nodeCount):

      # update path
      curNode = getNext(dist, self.nodeList)
      res.append(curNode)

      # destination check
      if curNode == endNode:
        break

      curNode.isVisited = True # state update
      res.append(curNode) # path update
      
      # update weights of unvisited nodes
      childCount = len(curNode.adjacentNodeList)
      curIndex = self.getNodeIndex(curNode)
      for i in range(0, childCount):
        if curNode.adjacentNodeList[i].isVisited == False:
          childIndex = self.getNodeIndex(curNode.adjacentNodeList[i])
          localD = curNode.calculateEuclideanDistance(self.nodeList[childIndex])
          if dist[curIndex]+localD < dist[childIndex]:
            dist[childIndex] = dist[curNode] + localD
      
    return res

  def __str__(self):
    res = ""

    res = res + "GRAPH0: \n"
    for i in range(0, len(self.nodeList)):
      curNode = self.nodeList[i]

      res = res + str(curNode.row)+","+str(curNode.col)+": "
      for j in range(0, len(curNode.adjacentNodeList)):
        res = res + str(curNode.adjacentNodeList[j].row)+","+str(curNode.adjacentNodeList[j].col)+"  "
      
      res = res + "\n"
    
    return res
    
