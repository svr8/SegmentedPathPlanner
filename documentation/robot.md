# Robot

# robot_astar

### class robot_astar
robot_astar solves path planning problem using A* and Segmented A*(Proposed) algorithms.

**Properties** 
| Name  | Data Type | Description |
| ------------- | ------------- | ------------- |
| env | arena | represents the physical world robot is moving in. robot will not change arena's values. |
| cur_node | node_astar | current position in `env` |
| open_list | priority_queue<node_astar, vector<node_astar>, node_compare_on_f> | please refer to A* algorithm for its usage |
closed_list | priority_queue<node_astar, vector<node_astar>, node_compare_on_f> | please refer to A* algorithm for its usage |
| open_list_state | double** | it is a matrix associated with respective grid cell. it is `-1` if its absent in `open_list`, otherwise stores respective `f` value of node |
| closed_list_state | double** | it is a matrix associated with respective grid cell. it is `-1` if its absent in `closed_list`, otherwise stores respective `f` value of node |
| found | bool | - |
| path | vector<cell> | stores path travelled by robot |
| parent | cell** | it is a matrix where each cell contains value of its parent node. Here parent refers to the node where robot comes from parent node to child node. It is used in calculating robot's final path |

**Constructors**
| Params | Description |
| ------------- | ------------- |
| a | a is arena type variable to interface robot with simulation environment |

**Methods**
| Name | Return | Params | Description |
| ------------- | ------------- | ------------- | ------------- |
| generate_path | void | target | uses `parent` to generate series of cells robot travelled |
| set_pos | void | pos | set current position in `env` map |
| move | vector<cell> | destination | use dijkstra's algo to move to destination |
| move_segmented | vector<cell> | destination, alpha | use proposed approach to move to destination |
| get_next_segment | cell | destination, alpha | please refer to proposed algorithm on how to calculate segment using alpha |
| scan_arena | void | destination | after robot moves to an adjacent cell, its 8 neighbors are scanned |
| scan_cell | void | c, destination | scan and update given c cell |

# robot_dj
robot_dj solves path planning problem using Dijkstra and Segmented Dijkstra(Proposed) algorithms.

**Properties** 
| Name  | Data Type | Description |
| ------------- | ------------- | ------------- |
| env | arena | represents the physical world robot is moving in. robot will not change arena's values. |
| cur_pos | cell | current position in `env` |
| scanned_env | cell_type** | it is a 2d matrix representing robot's memory of the simulation environment |
| dist | double** | it is a 2d matrix where each cell contains shortest distance calculated(so far) from robot's start to respective cell |
| path | vector<cell> | stores path travelled by robot |
| parent | cell** | it is a matrix where each cell contains value of its parent node. Here parent refers to the node where robot comes from parent node to child node. It is used in calculating robot's final path |

**Constructors**
| Params | Description |
| ------------- | ------------- |
| a | a is arena type variable to interface robot with simulation environment |

**Methods**
| Name | Return | Params | Description |
| ------------- | ------------- | ------------- | ------------- |
| is_destination_reached | bool | destination | returns true if robot's current position is same as destination  |
| is_deadend | bool | destination | returns true if robot's memory has destination as a `BLOCK` cell |
| generate_path | void | target | uses `parent` to generate series of cells robot travelled |
| set_pos | void | pos | set current position in `env` map |
| move | vector<cell> | destination | use dijkstra's algo to move to destination |
| move_segmented | vector<cell> | destination, alpha | use proposed approach to move to destination |
| get_next_segment | cell | destination, alpha | please refer to proposed algorithm on how to calculate segment using alpha |
| scan_arena | void | destination | after robot moves to an adjacent cell, its 8 neighbors are scanned |
| scan_cell | void | c, destination | scan and update given c cell |

# robot_pqdj
robot_pqdj solves path planning problem using PriorityQueue based Dijkstra and 
PriorityQueue based Segmented Dijkstra(Proposed) algorithms.

**Properties** 
| Name  | Data Type | Description |
| ------------- | ------------- | ------------- |
| env | arena | represents the physical world robot is moving in. robot will not change arena's values |
| cur_node | node_pqdj | current position in `env` |
| scanned_env | priority_queue<node_pqdj, vector<node_pqdj>, node_compare> | it is a priority queue based on sorted on `f` |
| cell_state | cell_type** | robot's memory of the simulation environment |
| dist | double** | it is a 2d matrix where each cell contains shortest distance calculated(so far) from robot's start to respective cell |
| path | vector<cell> | stores path travelled by robot |
| parent | cell** | it is a matrix where each cell contains value of its parent node. Here parent refers to the node where robot comes from parent node to child node. It is used in calculating robot's final path |

**Constructors**
| Params | Description |
| ------------- | ------------- |
| a | a is arena type variable to interface robot with simulation environment |

**Methods**
| Name | Return | Params | Description |
| ------------- | ------------- | ------------- | ------------- |
| is_destination_reached | bool | destination | returns true if robot's current position is same as destination  |
| is_deadend | bool | destination | returns true if robot's memory has destination as a `BLOCK` cell |
| generate_path | void | target | uses `parent` to generate series of cells robot travelled |
| set_pos | void | pos | set current position in `env` map |
| move | vector<cell> | destination | use dijkstra's algo to move to destination |
| move_segmented | vector<cell> | destination, alpha | use proposed approach to move to destination |
| get_next_segment | cell | destination, alpha | please refer to proposed algorithm on how to calculate segment using alpha |
| scan_arena | void | destination | after robot moves to an adjacent cell, its 8 neighbors are scanned |
| scan_cell | void | c, destination | scan and update given c cell |