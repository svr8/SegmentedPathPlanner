import math
import numpy as np
import matplotlib.pyplot as plt

from arena import arena
from cell import cell
from node import node
from graph0 import graph0

CLEAR_COLOR = 'white'
BLOCK_COLOR = 'black'
BOT_COLOR = 'green'
MAX = 1000000000

def showArena(a):
  xClear = []
  yClear = []
  xBlock = []
  yBlock = []
  for i in range(0, a.rows):
    for j in range(0, a.cols):
      if(a.cell[i][j] == 0):
        # plt.scatter([j], [i], color=CLEAR_COLOR)
        xClear.append(j)
        yClear.append(i)
      elif(a.cell[i][j] == 1):
        # plt.scatter([j], [i], color=BLOCK_COLOR)
        xBlock.append(j)
        yBlock.append(i)

  plt.scatter(xClear, yClear, color=CLEAR_COLOR)
  plt.scatter(xBlock, yBlock, color=BLOCK_COLOR)
  startCell = a.startCell
  plt.scatter([startCell.col], [startCell.row], color=BOT_COLOR)
  plt.pause(2)

# find euclidean distance betetween 2 cells
def calculateEuclideanDistance(cell1, cell2):
  return math.sqrt((cell1.row-cell2.row)**2 + (cell1.col-cell2.col)**2)

# find level 0 cell closest to given cell
def findClosestLeve0Node(level0List, targetCell):
  minDistance = MAX
  res = None

  for i in range(0, len(level0List)):
    d = calculateEuclideanDistance(targetCell, level0List[i])
    if d < minDistance:
      minDistance = d
      res = level0List[i]
  
  return res

# load arena
arena1 = arena('maps/sample1')
print(arena1)

# initialise level 0 cells
level0List = []
rowInterval = int(math.sqrt(arena1.rows))
colInterval = int(math.sqrt(arena1.cols))

for row in range(0, arena1.rows, rowInterval):
  for col in range(0, arena1.cols, colInterval):
    isBlock = arena1.cell[row][col] == 0
    level0List.append( node(row, col, isBlock) )

showArena(arena1)

alpha = math.sqrt(rowInterval**2 + colInterval**2)
maxd = int( (arena1.cols / colInterval) + 3 )
g0 = graph0(level0List, maxd, alpha)



# exploredCells = [ [0] * arena1.cols] * arena1.rows
