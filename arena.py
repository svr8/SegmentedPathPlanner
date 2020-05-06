from cell import cell

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
        cellData = 0 if line[j]=='0' else 1
        self.cell[i].append(cellData)
      
    # initialise start point
    line = lineList.pop(0).split(' ')
    self.startCell = cell(int(line[0]), int(line[1]))

    # initalise destinations
    line = lineList.pop(0)
    destinationCount = int(line[0])
    self.destination = []
    for i in range(0, destinationCount):
      line = lineList.pop(0).split(' ')
      c = cell(int(line[0]), int(line[1]))
      self.destination.append( c )
    
  def __str__(self):
    res = ""
    
    res = res + "ARENA: \n"
    for i in range(0, self.rows):
      for j in range(0, self.cols):
        res = res + str(self.cell[i][j])
      res = res + "\n"
    
    res = res + ("ROWS = " + str(self.rows) + "\n")
    res = res + ("COLS = " + str(self.cols) + "\n")
    res = res + ("START CELL = " + str(self.startCell.row) + ", " + str(self.startCell.col) + "\n")
    res = res + ("DESTINATION LIST: " + "\n")
    for i in range(0, len(self.destination)):
      res = res + ("#" + str((i+1)) + ": " + str(self.destination[i].row) + ", " + str(self.destination[i].col) + "\n")
    
    return res

