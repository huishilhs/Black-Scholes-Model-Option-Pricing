CXX = g++
CXXFLAGS = -std=c++17 -IOptionPricer

SRC = main.cpp src/BlackScholes.cpp src/NormalDistribution.cpp
TARGET = BSOptionPricer

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
