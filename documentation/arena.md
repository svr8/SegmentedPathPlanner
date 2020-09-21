# Arena

### enum arena_type
This is for identifying format of dataset. `arena` uses it to handle various parsing functions.

#### class arena
This class represents the environment robot is moving it and contains basic test case attributes to run tests.
Robot is supposed to read environment and update its own memory and
not change arena's values. It uses `string_tokenizer` to parse map dataset files.

**Properties** 
| Name  | Data Type | Description |
| ------------- | ------------- | ------------- |
| bucket | int | group index of tests. a group represent tests for the same map |
| graph  | cell_type**  | store grid cells as 2d array |
| start  | cell  | start point of robot for testing |
| destination | cell | goal of robot for testing |
| width | int | no. of columns in graph |
| height | int | no. of rows in graph |

**Constructors**
| Params | Description |
| ------------- | ------------- |
| None | - |
| filepath, map_type | filepath is map file to parse and it must be relative to root of this repository |
| scenepath, root, test_index, map_type | scenepath is a testcase file; root is game folder; test_index is bucket |

**Methods**
| Name | Return | Params | Description |
| ------------- | ------------- | ------------- | ------------- |
| parse_custom | void | filepath | filepath is the map file to parse and it must be relative to root of this repository | 
| parse_movingai | void | scenepath, root, test_index | parse scene files and map files to load complete dataset; root is game folder; test_index is bucket |
| get | cell_type | i: row, j: col | get graph cell value |
| set | void | i: row, j: col, type: value | sets graph cell value |
| clear | void | - | clears all memory allocated using `new`; clears other variables |