# Node

## node_astar

### class node_astar
This wraps up all attributes needed to handle A* algorithm's nodes.

**Properties** 
| Name  | Data Type | Description |
| ------------- | ------------- | ------------- |
| pos | cell | represents current position in `arena`. |
| f, g, h | double | Please refer to A* algorithms for these terms. |

**Constructors**
| Params | Description |
| ------------- | ------------- |
| - | Initialise current position to (-1, -1); f=g=h=0 |
| r, c | Intialise current position to (c, r); f=g=h=0 |

**Methods**
| Name | Return | Params | Description |
| ------------- | ------------- | ------------- | ------------- | 
| euclidean_distance | double | other | return s euclidean distance between `other` and `this` node |

### class node_compare_on_f
serves as comparator for node_astar using `f` attribute; sorts in non-increasing order.

# node_pqdj

### class node_pqdj 
This wraps up all attributes needed to handle Dijkstra's algorithm's nodes.

**Properties** 
| Name  | Data Type | Description |
| ------------- | ------------- | ------------- |
| pos | cell | represents current position in `arena` |
| dist | double | distance between source and `this` node |

**Constructors**
| Params | Description |
| ------------- | ------------- |
| - | Initialise current position to (-1, -1); dist=-1 |
| r, c , d| Intialise current position to (c, r); dist=d |


### class node_compare
serves as comparator for node_pqdj using `dist` attribute; sorts in non-increasing order.