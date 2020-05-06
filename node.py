import math

class node:

  def __init__(self, row, col, isBlock):
    self.row = row
    self.col = col
    self.isBlock = isBlock
    self.isVisited = False

    self.adjacentNodeList = []
  
  def connect(self, node):
    self.adjacentNodeList.append(node)

  def calculateEuclideanDistance(self, node):
    return math.sqrt((self.row-node.row)**2 + (self.col-node.col)**2)
