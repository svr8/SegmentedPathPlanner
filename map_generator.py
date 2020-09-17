import random

def generate_map(rows, cols, mapFile):
  start_row = random.randint(0, rows-1)
  start_col = random.randint(0, cols-1)
  goal_row = random.randint(0, rows-1)
  goal_col = random.randint(0, cols-1)

  matrix = []
  for i in range(0, rows):
    matrix.append([])
    for j in range(0, cols):
      matrix[i].append(random.randint(0,5))
      if matrix[i][j] != 1:
        matrix[i][j] = 0
  
  matrix[start_row][start_col] = 0
  matrix[goal_row][goal_col] = 0

  file = open(mapFile, 'w')

  file.write( str(rows) + " " + str(cols) + "\n" )
  
  for i in range(0, rows):
    line = ""
    for j in range(0, cols):
      line = line + str(matrix[i][j])
    file.write(line + "\n")

  file.write( str(start_row) + " " + str(start_col) + "\n" )
  file.write( str(goal_row) + " " + str(goal_col) + "\n")


prefix = "maps_250x250/sample"
for i in range(0, 1000):
  f = prefix + str(i)
  generate_map(250, 250, f)
  print(f+" done")




