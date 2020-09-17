import numpy as np
import matplotlib.pyplot as plt

CLEAR_COLOR = 0
BLOCK_COLOR = 1
BOT_COLOR = 0.759999
GOAL_COLOR = 0.4

class arena:
  
  def __init__(self, filename):

    file = open(filename, 'r')
    lineList = file.read().split('\n')

    # initialise map
    line = lineList.pop(0).split(' ')
    self.cols = int(line[0])
    self.rows = int(line[1])
    
    self.cell = []
    for i in range(0, self.rows):
      self.cell.append([])

      line = lineList.pop(0)
      for j in range(0, self.cols):
        cellData = 0 if line[j]=='0' else 1
        self.cell[i].append(cellData)
      
    # initialise start point
    line = lineList.pop(0).split(' ')
    self.startCell = [int(line[0]), int(line[1])]

    # initialise destination point
    line = lineList.pop(0).split(' ')
    self.destinationCell = [int(line[0]), int(line[1])]

  def __str__(self):
    res = ""
    
    # res = res + "ARENA: \n"
    # for i in range(0, self.rows):
    #   for j in range(0, self.cols):
    #     r = ""
    #     if self.cell[i][j] == 0:
    #       r = "0"
    #     elif self.cell[i][j] == 1:
    #       r = "1"
    #     else:
    #       r = "2" # never occurs
        
    #     res = res + r
    #   res = res + "\n"
    
    res = res + ("ROWS = " + str(self.rows) + "\n")
    res = res + ("COLS = " + str(self.cols) + "\n")
    res = res + ("START CELL = " + str(self.startCell[0]) + ", " + str(self.startCell[1]) + "\n")
    res = res + ("DESTINATION CELL = " + str(self.destinationCell[0]) + ", " + str(self.destinationCell[1]) + "\n")

    return res

def show_arena(a):
  endCell = a.destinationCell

  image = np.zeros(a.rows*a.cols)
  image = image.reshape((a.rows, a.cols))
  for i in range(a.rows):
    for j in range(a.cols):
      image[i][j] = a.cell[i][j]
  image[endCell[1]][endCell[0]] = GOAL_COLOR
  plt.matshow(image, fignum=False)
  plt.pause(1)

  return image

def simulate_bot(img, cur_pos, simFilePath):
  file = open(simFilePath, 'r')
  lineList = file.read().split('\n')

  # no of movements
  line = lineList.pop(0).split(' ')
  count = int(line[0])

  # simulation
  for _ in range(count):
    line = lineList.pop(0).split(' ')
    col = int(line[0])
    row = int(line[1])

    x0 = cur_pos[0]
    y0 = cur_pos[1]
    x1 = col
    y1 = row

    # img[y0][x0] = CLEAR_COLOR
    img[y1][x1] = BOT_COLOR
    plt.matshow(img, fignum=False)
    plt.pause(0.1)

    cur_pos = [col, row]

def main():
  env = arena('maps_250x250/sample0')
  arena_img = show_arena(env)
  print(env)
  cur_pos = [env.startCell[0], env.startCell[1]]
  simulate_bot(arena_img, cur_pos, 'out')

  plt.pause(1)

if __name__ == '__main__':
  main()