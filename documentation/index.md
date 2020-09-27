# Documentation

## System Requirements
* GCC version >= 9.3.0 to run path planning algorithms
* make
* python3 to run map generator and visualiser (with numpy, matplotlib packages)


## How to Run
Execute the following commands in root directory of this project.

* `make clean build run_custom` to run tests on custom dense map datasets.
* `make clean build run_movingai` to run tests on Dragon Age: Origins game datasets.

## Folder Structure

| Folder Name  | Description | Docs |
| ------------- | ------------- | -------------  |
| **arena**  | Arena is a simple map parser. | [arena.md](arena.md) |
| **cell**  | Cell represents grid cell of the map.  | [cell.md](cell.md) |
| **datasets** | Any dataset included in testing the algorithm is placed here. Every dataset has a readme that will describe file formats. | [datasets.md](datasets.md) |
| **main** | This is a trigger for all robot algorithms and test suits in the project. 2 mains have been defined for 2 datasets: custom and moving ai | - |
| **node** | Interpretation of grid cell by robot is in the form of node. | [node.md](node.md) |
| **robot** | Different bots are defined for each type of algorithm. | [robot.md](robot.md) |
| **string_tokenizer** | Simple space separated string reader. | [string_tokenizer.md](string_tokenizer.md) |
| **tests** | All test results are placed here. | - |