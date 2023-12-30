# Compiler Version
CC = g++

# Compiler Flags
CFLAGS = -Wall -g -std=c++11

# Target
TARGET = $(if $(filter 1,$(task)),dict,src)

# Object Files
OBJ = main_$(TARGET).o Node.o dict.o search.o

# Header Files
HEADER = Node.h dict.h

# cpp Files
CPP = Node.cpp main_$(TARGET).cpp dict.cpp search.cpp

# Compile
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)
	rm -f $(OBJ)

# Object Files
Node.o: Node.cpp
	$(CC) $(CFLAGS) -c Node.cpp

dict.o: dict.cpp
	$(CC) $(CFLAGS) -c dict.cpp
search.o: search.cpp
	$(CC) $(CFLAGS) -c search.cpp

main_$(TARGET).o: main_$(TARGET).cpp
	$(CC) $(CFLAGS) -c main_$(TARGET).cpp

# Clean
clean:
	rm -f $(OBJ) $(TARGET) *~

# Run
run:
	./$(TARGET)

# Debug
debug:
	gdb ./$(TARGET)
