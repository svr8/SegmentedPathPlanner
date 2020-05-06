class graph0:

  def __init__(self, nodeList, MAXD, ALPHA):
    self.nodeList = nodeList
    
    # create connections
    for i in range(0, len(self.nodeList)):
      curNode = self.nodeList[i]
    
      limit = min(len(self.nodeList), i+MAXD)
      for j in range(i+1, limit):

        d = curNode.calculateEuclideanDistance(nodeList[j])
        if d <= ALPHA:
          curNode.connect(nodeList[j])
          nodeList[j].connect(curNode)


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
    
