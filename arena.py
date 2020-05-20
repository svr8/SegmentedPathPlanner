from cell import cell
from node_type import node_type
class arena:
  
  def __init__(self, filename):

    file = open(filename, 'r')
    lineList = file.read().split('\n')

    # initialise map
    line = lineList.pop(0).split(' ')
    self.rows = int(line[0])
    self.cols = int(line[1])
    
    self.cell = []
    for i in range(0, self.rows):
      self.cell.append([])

      line = lineList.pop(0)
      for j in range(0, self.cols):
        cellData = node_type.FREE if line[j]=='0' else node_type.BLOCK
        self.cell[i].append(cellData)
      
    # initialise start point
    line = lineList.pop(0).split(' ')
    self.startCell = cell(int(line[0]), int(line[1]))

    # initialise destination point
    line = lineList.pop(0).split(' ')
    self.destinationCell = cell(int(line[0]), int(line[1]))

  def __str__(self):
    res = ""
    
    # res = res + "ARENA: \n"
    # for i in range(0, self.rows):
    #   for j in range(0, self.cols):
    #     r = ""
    #     if self.cell[i][j] == node_type.FREE:
    #       r = "0"
    #     elif self.cell[i][j] == node_type.BLOCK:
    #       r = "1"
    #     else:
    #       r = "2" # never occurs
        
    #     res = res + r
    #   res = res + "\n"
    
    res = res + ("ROWS = " + str(self.rows) + "\n")
    res = res + ("COLS = " + str(self.cols) + "\n")
    res = res + ("START CELL = " + str(self.startCell.row) + ", " + str(self.startCell.col) + "\n")
    res = res + ("DESTINATION CELL = " + str(self.destinationCell.row) + ", " + str(self.destinationCell.col) + "\n")

    return res

