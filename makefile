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

	# build main
	g++ -c main/main.cpp -I./main -o ./builds/main.o

	# link all objects to main
	g++ -o app ./builds/string_tokenizer.o ./builds/cell.o ./builds/node_astar.o ./builds/node_pqdj.o ./builds/arena.o ./builds/robot_astar.o ./builds/robot_dj.o ./builds/robot_pqdj.o ./builds/main.o

run:
	./app

clean:
	rm -rf ./app ./builds/*