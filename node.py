import math

class node:

  def __init__(self, row, col, node_type):
    self.row = row
    self.col = col
    self.node_type = node_type
    self.isVisited = False

    self.adjacentNodeList = []
  
  def connect(self, node):
    self.adjacentNodeList.append(node)

  def calculateEuclideanDistance(self, node):
    return math.sqrt((self.row-node.row)**2 + (self.col-node.col)**2)
  
  def __eq__(self, otherNode):
    return self.row==otherNode.row and self.col==otherNode.col
  
  def __str__(self):
    res = "NODE:("
    res = res + "ROW: " + str(self.row) + " COL: " + str(self.col) + " TYPE: " + self.node_type +" )\n"
    return res
