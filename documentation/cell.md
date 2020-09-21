# Cell

### enum cell_type
This represents various type of grid cells:
UNVISITED: robot has not seen this cell yet
VISITED: robot has seen, but the value is unknown
FREE: robot can traverse through this cell
BLOCK: robot cannot traverse through this cell

### class cell
This is a basic wrapper for grid cell tools.

**Properties** 
| Name  | Data Type | Description |
| ------------- | ------------- | ------------- |
| row | int | y-coordinate in graph |
| col | int | x-coordinate in graph |

**Constructors**
| Params | Description |
| ------------- | ------------- |
| - | Initialise to (-1, -1) |
| r, c | Intialise to (r: row index, c: col index) |

**Methods**
| Name | Return | Params | Description |
| ------------- | ------------- | ------------- | ------------- |
| euclidean_distance | double | other | return euclidean distance between `other` and `this` cell |
| is_equal | bool | other | checks if `other` and `this` cell represent the same position |
