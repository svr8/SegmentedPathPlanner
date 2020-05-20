from cell import cell
from node_type import node_type
import math

class robot:

  def __init__(self, arena):
    self.pos = arena.startCell
    self.arena = arena
    self.memory = []

    self.cols = len(self.arena.cell[0])
    self.rows = len(self.arena.cell)
    for i in range(0, self.rows):
      self.memory.append([])
      for _ in range(0, self.cols):
        self.memory[i].append(node_type.NOT_VISIBLE)

  def calculateEuclideanDistance(self, r1, c1, r2, c2):
    d = math.sqrt( ((r1-r2)*(r1-r2)) + ((c1-c2)*(c1-c2)) )
    return d
  
  def dijkstraPathLanner(self, start, destination):

    def updateEdge(dist, r1, c1, r2, c2):
      d1 = dist[r2][c2]
      d2 = dist[r1][c1] + self.calculateEuclideanDistance(r1, c1, r2, c2)
      dist[r2][c2] = min(d1,d2)
      print("DIST: " + str(r1) +"," + str(c1) +" --> " + str(r2) +"," + str(c2) + ": " + str(dist[r2][c2]) + ' ('+str(d1)+','+str(d2)+')')


    def updateNodeNeighbours(dist, rows, cols):
      r = self.pos.row
      c = self.pos.col 

      # top left
      if r+1<rows and c-1>=0:
        updateEdge(dist, r, c, r+1, c-1)
      # top
      if r+1<rows:
        updateEdge(dist, r, c, r+1, c)
      # top right
      if r+1<rows and c+1<cols:
        updateEdge(dist, r, c, r+1, c+1)
      # left
      if c-1>=0:
        updateEdge(dist, r, c, r, c-1)
      # right
      if c+1<cols:
        updateEdge(dist, r, c, r, c+1)
      # bottom left
      if r-1>=0 and c-1>=0:
        updateEdge(dist, r, c, r-1, c-1)
      # bottom
      if r-1>=0:
        updateEdge(dist, r, c, r-1, c)
      # bottom right
      if r-1>=0 and c+1<cols:
        updateEdge(dist, r, c, r-1, c+1)

    cols = self.cols
    rows = self.rows

    MAX = 1000000
    
    dist = [[MAX]*cols]*rows
    dist[start.row][start.col] = 0
    self.dist = dist
    self.memory[start.row][start.col] = node_type.FREE
    self.pos = start
    # print('>>>>' + str(start))

    limit = rows*cols
    path = []

    for _ in range(0, 3):
      # print('ITERATION: ' + str(_))
      cur = None
      minD = MAX*2

      # get minimum node
      for i in range(0, rows):
        for j in range(0, cols):
          # print("DIST: " + str(i) + ", " + str(j) + ": " + str(dist[i][j]))
          # if self.memory[i][j] == node_type.FREE:
            # print('FREE: ' + str(i) + ', ' + str(j))
          if self.memory[i][j] == node_type.FREE and minD > dist[i][j]:
            if cur != None:
              d1 = dist[i][j] + self.calculateEuclideanDistance(destination.row, destination.col, i,j)
              d2 = dist[cur.row][cur.col] + self.calculateEuclideanDistance(destination.row, destination.col, cur.row, cur.col)
              if d1 < d2:
                minD = dist[i][j]
                cur = cell(i,j)
            else:
              minD = dist[i][j]
              cur = cell(i, j)
      
      # update path
      path.append(cur)
      print(str(cur))

      # destination check
      if cur.isEqual(destination):
        print('GOAL')
        break
      
      # update graph edge weights
      updateNodeNeighbours(dist, rows, cols)

      # update robots memory
      self.pos = cur
      self.updateMemory()
    
    print('SEARCH COMPLETE')
    return path

  
  def updateMemory(self):
    print('UPDATE MEMORY')
    cols = self.cols
    rows = self.rows

    # top left
    if self.pos.row+1<rows and self.pos.col-1>=0:
      self.scanCell(self.pos.row+1, self.pos.col-1)
    # top
    if self.pos.row+1<rows:
      self.scanCell(self.pos.row+1, self.pos.col)
    # top right
    if self.pos.row+1<rows and self.pos.col+1<cols:
      self.scanCell(self.pos.row+1, self.pos.col+1)
    # left
    if self.pos.col-1>=0:
      self.scanCell(self.pos.row, self.pos.col-1)
    # center
    self.scanCell(self.pos.row, self.pos.col)
    # right
    if self.pos.col+1<cols:
      self.scanCell(self.pos.row, self.pos.col+1)
    # bottom left
    if self.pos.row-1>=0 and self.pos.col-1>=0:
      self.scanCell(self.pos.row-1, self.pos.col-1)
    # bottom
    if self.pos.row-1>=0:
      self.scanCell(self.pos.row-1, self.pos.col)
    # bottom right
    if self.pos.row-1>=0 and self.pos.col+1<cols:
      self.scanCell(self.pos.row-1, self.pos.col+1)
  
  def scanCell(self, row, col):
    self.memory[row][col] = self.arena.cell[row][col]
    r = ""
    if self.memory[row][col] == node_type.FREE:
      r = "FREE"
    elif self.memory[row][col] == node_type.BLOCK:
      r = "BLOCK"
    elif self.memory[row][col] == node_type.NOT_VISIBLE:
      r = "NOT_VISIBLE"
    else:
      r = "-------"
    print( "scanCell: " + str(row) + ", " + str(col) + " --> " + r + ' ' + str(self.dist[row][col]))