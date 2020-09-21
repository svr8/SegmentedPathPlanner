# Arena

### enum arena_type
This is for identifying format of dataset. `arena` uses it to handle various parsing functions.

#### class arena
This class represents the environment robot is moving it.
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

**Methods**
| Name | Return | Params | Description |
| ------------- | ------------- | ------------- | ------------- |
| parse_custom | void | filepath | filepath is the map file to parse and it must be relative to root of this repository | 
| parse_movingai | void | scenepath | test |
