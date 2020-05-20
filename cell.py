class cell:
  def __init__(self, row, col):
    self.row = row
    self.col = col
  
  def isEqual(self, otherCell):
    return self.row==otherCell.row and self.col==otherCell.col
  
  def __str__(self):
    return "CELL: " + str(self.row) + ", " + str(self.col)