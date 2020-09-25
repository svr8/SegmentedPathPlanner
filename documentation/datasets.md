# Dataset Readme

## Custom Dense Dataset
**Format**:
```
WIDTH HEIGHT
BINARY_MATRIX
START_ROW START_COLUMN
GOAL_ROW GOAL_COLUMN
```

* `WIDTH` refers to number of columns of grid
* `HEIGHT` refers to number of rows of grid
* `BINARY_MATRIX` is a list of lines. There are `HEIGHT` number of lines and each line contains `WIDTH` number of characters following the below rules:

| Character  | Deccription |
| ------------- | ------------- |
| 0 | robot can pass through this cell |
| 1 | robot can not pass through this cell |
* `START_ROW` refers to robot's initial position's row (0-based).
* `START_COLUMN` refers to robot's initial position's column (0-based).
* `GOAL_ROW` refers to robot's destination position's row (0-based).
* `GOAL_COLUMN` refers to robot's destination position's column  (0-based).

**How To Generate**:

* In the root directory of project, open `map_generator.py`.
* On line `34`, edit the `PREFIX` value to the target location where dataset needs to be placed.
* On line `35`, edit the `DATASET_COUNT` value to the number of maps to be generated
* Run this python script to generate dataset: `python3 map_generator.py`

## Bioware Dragon Age: Origins Dataset
**Format**:
```
type octicle
height y
width x
map
```

* The first line `type octile` is of no use in this project, skip it while processing.
* Second line contains `y` that refers to the number of rows of grid map.
* Third line contains `x` that refers to the number of columns of grid map.
* Following `y` lines contain strings representing the map following the below rules:

| Character  | Deccription |
| ------------- | ------------- |
| . | robot can pass through this cell |
| G | robot can pass through this cell |
| @ | robot can not pass through this cell |
| T | robot can not pass through this cell |
| 0 | robot can not pass through this cell |

**Test Files Format**:
All test files are placed in `datasets/grids/moving_ai/game_dragon_age_origins/benchmark-problems`.
The first line contains `version` that is of no use in this project(it is skipped while processing).
Each line contains data in the following order top to bottom:

* `bucket`: an integer that tells the group of testcase. A group of testcases contains tests related to same map file.
* `map`: map file name in `maps` folder.
* `map width`: number of columns in grid.
* `map height`: number of rows in grid.
* `start column`: robot's initial position's column (0-based).
* `start row`: refers to robot's initial position's row (0-based).
* `goal column`: refers to robot's destination position's column (0-based).
* `goal row`: refers to robot's destination position's row (0-based).
* `optimal length`: refers to path length where distance between 2 waypoints or cells on path is calculated using euclidean distance. This is not used in this project.