all: CarreraSim.cpp
	g++ CarreraSim.cpp -o output -std=c++11

# No se hizo ningún ifdef para el debug, ya que no se necesitó