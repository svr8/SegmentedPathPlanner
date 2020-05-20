import math
import numpy as np
import matplotlib.pyplot as plt

from arena import arena
from node_type import node_type
from robot import robot

# from cell import cell
# from node import node
# from graph0 import graph0

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
      if(a.cell[i][j] == node_type.FREE):
        xClear.append(j)
        yClear.append(i)
      elif(a.cell[i][j] == node_type.BLOCK):
        xBlock.append(j)
        yBlock.append(i)

  plt.scatter(xClear, yClear, color=CLEAR_COLOR)
  plt.scatter(xBlock, yBlock, color=BLOCK_COLOR)
  startCell = a.startCell
  plt.scatter([startCell.col], [startCell.row], color=BOT_COLOR)
  plt.pause(2)

def showMovement(row, col):
  plt.scatter([col], [row], color=BOT_COLOR)
  plt.pause(0.25)


def main():
  # load arena
  arena1 = arena('maps/sample1')
  showArena(arena1)
  print(arena1)

  # initialise robots
  r = robot(arena1)

  # djikstra path
  p = r.dijkstraPathLanner(arena1.startCell, arena1.destinationCell)

  # show result path
  l = len(p)
  for i in range(0, l):
    curCell = p[i]
    # print(curCell)
    showMovement(curCell.row, curCell.col)
  
  plt.pause(2)
  # print(arena1)

if __name__ == '__main__':
  main()