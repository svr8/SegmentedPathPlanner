build:
	# build string_tokenizer
	g++ -c string_tokenizer/string_tokenizer.cpp -I ./string_tokenizer -o ./builds/string_tokenizer.o

	# build cell
	g++ -c cell/cell.cpp -I ./cell -o ./builds/cell.o

	# build a_star node
	g++ -c node/node_astar.cpp -I ./node -o ./builds/node_astar.o

	# build priority queue based dijkstra node
	g++ -c node/node_pqdj.cpp -I ./node -o ./builds/node_pqdj.o

	# build arena
	g++ -c arena/arena.cpp -I ./arena -o ./builds/arena.o

	# build a_star robot
	g++ -c robot/robot_astar.cpp -I ./robot -o ./builds/robot_astar.o

	# build dijkstra robot
	g++ -c robot/robot_dj.cpp -I ./robot -o ./builds/robot_dj.o

	# build priority queue based dijkstra robot
	g++ -c robot/robot_pqdj.cpp -I ./robot -o ./builds/robot_pqdj.o

run_custom:
	# build main for custom maps
	g++ -c main/main_custom.cpp -I./main -o ./builds/main_custom.o

	# link all objects to main
	g++ -o app ./builds/string_tokenizer.o ./builds/cell.o ./builds/node_astar.o ./builds/node_pqdj.o ./builds/arena.o ./builds/robot_astar.o ./builds/robot_dj.o ./builds/main_custom.o
	
	# execute
	./app

run_movingai:
	# build main for moving ai maps
	g++ -c main/main_moving_ai.cpp -I./main -o ./builds/main_moving_ai.o

	# link all objects to main
	g++ -o app ./builds/string_tokenizer.o ./builds/cell.o ./builds/node_astar.o ./builds/node_pqdj.o ./builds/arena.o ./builds/robot_astar.o ./builds/robot_dj.o ./builds/robot_pqdj.o ./builds/main_moving_ai.o
	
	# execute
	./app

run_custom_a_alpha5:
	# build main for custom maps
	g++ -c main/main_custom_a_alpha5.cpp -I./main -o ./builds/main_custom_a_alpha5.o

	# link all objects to main
	g++ -o custom_a_alpha5 ./builds/string_tokenizer.o ./builds/cell.o ./builds/node_astar.o ./builds/node_pqdj.o ./builds/arena.o ./builds/robot_astar.o ./builds/robot_dj.o ./builds/robot_pqdj.o ./builds/main_custom_a_alpha5.o
	
	# execute
	./custom_a_alpha5

run_custom_a_alpha10:
	# build main for custom maps
	g++ -c main/main_custom_a_alpha10.cpp -I./main -o ./builds/main_custom_a_alpha10.o

	# link all objects to main
	g++ -o custom_a_alpha10 ./builds/string_tokenizer.o ./builds/cell.o ./builds/node_astar.o ./builds/node_pqdj.o ./builds/arena.o ./builds/robot_astar.o ./builds/robot_dj.o ./builds/robot_pqdj.o ./builds/main_custom_a_alpha10.o
	
	# execute
	./custom_a_alpha10

run_custom_as_alpha5:
	# build main for custom maps
	g++ -c main/main_custom_as_alpha5.cpp -I./main -o ./builds/main_custom_as_alpha5.o

	# link all objects to main
	g++ -o custom_as_alpha5 ./builds/string_tokenizer.o ./builds/cell.o ./builds/node_astar.o ./builds/node_pqdj.o ./builds/arena.o ./builds/robot_astar.o ./builds/robot_dj.o ./builds/robot_pqdj.o ./builds/main_custom_as_alpha5.o
	
	# execute
	./custom_as_alpha5

run_custom_as_alpha10:
	# build main for custom maps
	g++ -c main/main_custom_as_alpha10.cpp -I./main -o ./builds/main_custom_as_alpha10.o

	# link all objects to main
	g++ -o custom_as_alpha10 ./builds/string_tokenizer.o ./builds/cell.o ./builds/node_astar.o ./builds/node_pqdj.o ./builds/arena.o ./builds/robot_astar.o ./builds/robot_dj.o ./builds/robot_pqdj.o ./builds/main_custom_as_alpha10.o
	
	# execute
	./custom_as_alpha10
run_custom_pqd_alpha5:
	# build main for custom maps
	g++ -c main/main_custom_pqd_alpha5.cpp -I./main -o ./builds/main_custom_pqd_alpha5.o

	# link all objects to main
	g++ -o custom_pqd_alpha5 ./builds/string_tokenizer.o ./builds/cell.o ./builds/node_astar.o ./builds/node_pqdj.o ./builds/arena.o ./builds/robot_astar.o ./builds/robot_dj.o ./builds/robot_pqdj.o ./builds/main_custom_pqd_alpha5.o
	
	# execute
	./custom_pqd_alpha5

run_custom_pqd_alpha10:
	# build main for custom maps
	g++ -c main/main_custom_pqd_alpha10.cpp -I./main -o ./builds/main_custom_pqd_alpha10.o

	# link all objects to main
	g++ -o custom_pqd_alpha10 ./builds/string_tokenizer.o ./builds/cell.o ./builds/node_astar.o ./builds/node_pqdj.o ./builds/arena.o ./builds/robot_astar.o ./builds/robot_dj.o ./builds/robot_pqdj.o ./builds/main_custom_pqd_alpha10.o
	
	# execute
	./custom_pqd_alpha10

run_custom_pqds_alpha5:
	# build main for custom maps
	g++ -c main/main_custom_pqds_alpha5.cpp -I./main -o ./builds/main_custom_pqds_alpha5.o

	# link all objects to main
	g++ -o custom_pqds_alpha5 ./builds/string_tokenizer.o ./builds/cell.o ./builds/node_astar.o ./builds/node_pqdj.o ./builds/arena.o ./builds/robot_astar.o ./builds/robot_dj.o ./builds/robot_pqdj.o ./builds/main_custom_pqds_alpha5.o
	
	# execute
	./custom_pqds_alpha5

run_custom_pqds_alpha10:
	# build main for custom maps
	g++ -c main/main_custom_pqds_alpha10.cpp -I./main -o ./builds/main_custom_pqds_alpha10.o

	# link all objects to main
	g++ -o custom_pqds_alpha10 ./builds/string_tokenizer.o ./builds/cell.o ./builds/node_astar.o ./builds/node_pqdj.o ./builds/arena.o ./builds/robot_astar.o ./builds/robot_dj.o ./builds/robot_pqdj.o ./builds/main_custom_pqds_alpha10.o
	
	# execute
	./custom_pqds_alpha10

run_dao_a_alpha5:
	# build main for custom maps
	g++ -c main/main_dao_a_alpha5.cpp -I./main -o ./builds/main_dao_a_alpha5.o

	# link all objects to main
	g++ -o dao_a_alpha5 ./builds/string_tokenizer.o ./builds/cell.o ./builds/node_astar.o ./builds/node_pqdj.o ./builds/arena.o ./builds/robot_astar.o ./builds/robot_dj.o ./builds/robot_pqdj.o ./builds/main_dao_a_alpha5.o
	
	# execute
	./dao_a_alpha5

run_dao_a_alpha10:
	# build main for custom maps
	g++ -c main/main_dao_a_alpha10.cpp -I./main -o ./builds/main_dao_a_alpha10.o

	# link all objects to main
	g++ -o dao_a_alpha10 ./builds/string_tokenizer.o ./builds/cell.o ./builds/node_astar.o ./builds/node_pqdj.o ./builds/arena.o ./builds/robot_astar.o ./builds/robot_dj.o ./builds/robot_pqdj.o ./builds/main_dao_a_alpha10.o
	
	# execute
	./dao_a_alpha10

run_dao_as_alpha5:
	# build main for custom maps
	g++ -c main/main_dao_as_alpha5.cpp -I./main -o ./builds/main_dao_as_alpha5.o

	# link all objects to main
	g++ -o dao_as_alpha5 ./builds/string_tokenizer.o ./builds/cell.o ./builds/node_astar.o ./builds/node_pqdj.o ./builds/arena.o ./builds/robot_astar.o ./builds/robot_dj.o ./builds/robot_pqdj.o ./builds/main_dao_as_alpha5.o
	
	# execute
	./dao_as_alpha5

run_dao_as_alpha10:
	# build main for custom maps
	g++ -c main/main_dao_as_alpha10.cpp -I./main -o ./builds/main_dao_as_alpha10.o

	# link all objects to main
	g++ -o dao_as_alpha10 ./builds/string_tokenizer.o ./builds/cell.o ./builds/node_astar.o ./builds/node_pqdj.o ./builds/arena.o ./builds/robot_astar.o ./builds/robot_dj.o ./builds/robot_pqdj.o ./builds/main_dao_as_alpha10.o
	
	# execute
	./dao_as_alpha10
run_dao_pqd_alpha5:
	# build main for custom maps
	g++ -c main/main_dao_pqd_alpha5.cpp -I./main -o ./builds/main_dao_pqd_alpha5.o

	# link all objects to main
	g++ -o dao_pqd_alpha5 ./builds/string_tokenizer.o ./builds/cell.o ./builds/node_astar.o ./builds/node_pqdj.o ./builds/arena.o ./builds/robot_astar.o ./builds/robot_dj.o ./builds/robot_pqdj.o ./builds/main_dao_pqd_alpha5.o
	
	# execute
	./dao_pqd_alpha5

run_dao_pqd_alpha10:
	# build main for custom maps
	g++ -c main/main_dao_pqd_alpha10.cpp -I./main -o ./builds/main_dao_pqd_alpha10.o

	# link all objects to main
	g++ -o dao_pqd_alpha10 ./builds/string_tokenizer.o ./builds/cell.o ./builds/node_astar.o ./builds/node_pqdj.o ./builds/arena.o ./builds/robot_astar.o ./builds/robot_dj.o ./builds/robot_pqdj.o ./builds/main_dao_pqd_alpha10.o
	
	# execute
	./dao_pqd_alpha10

run_dao_pqds_alpha5:
	# build main for custom maps
	g++ -c main/main_dao_pqds_alpha5.cpp -I./main -o ./builds/main_dao_pqds_alpha5.o

	# link all objects to main
	g++ -o dao_pqds_alpha5 ./builds/string_tokenizer.o ./builds/cell.o ./builds/node_astar.o ./builds/node_pqdj.o ./builds/arena.o ./builds/robot_astar.o ./builds/robot_dj.o ./builds/robot_pqdj.o ./builds/main_dao_pqds_alpha5.o
	
	# execute
	./dao_pqds_alpha5

run_dao_pqds_alpha10:
	# build main for custom maps
	g++ -c main/main_dao_pqds_alpha10.cpp -I./main -o ./builds/main_dao_pqds_alpha10.o

	# link all objects to main
	g++ -o dao_pqds_alpha10 ./builds/string_tokenizer.o ./builds/cell.o ./builds/node_astar.o ./builds/node_pqdj.o ./builds/arena.o ./builds/robot_astar.o ./builds/robot_dj.o ./builds/robot_pqdj.o ./builds/main_dao_pqds_alpha10.o
	
	# execute
	./dao_pqds_alpha10


clean:
	rm -rf ./app ./builds/*