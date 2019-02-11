TARGET=fuse
C_SRCFILES=device.cpp filesystem.cpp fuse.cpp main.cpp
OBJ_FILES=${C_SRCFILES:.cpp=.o}
.PHONY: clean run
.SUFFIXES:

$(TARGET): $(OBJ_FILES)
	g++ -std=c=++11 -g -o $@ $(OBJ_FILES)

%.o: %.cpp
	g++ -std=c++11 -g -c -o $@ $<

run: $(TARGET)
	./$(TARGET) input1.txt

clean:
	rm -f *.o
	rm -f $(TARGET)

delete:
	rm -f *.disk