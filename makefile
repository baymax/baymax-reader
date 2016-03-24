CC = gcc

CFLAGS =  -Iheader/
LDFLAGS = -pthread
HEADER_DIR = header/
SRC_DIR = src/
OBJ_DIR = obj/
BIN_DIR = executable/

LDFLAGS = -lwiringPi

HEADER_FILES = $(HEADER_DIR)*.h
SOURCE_FILES = $(SRC_DIR)*.cpp
OBJ_FILES = $(OBJ_DIR)*.o

EXECUTABLE = baymax-reader

ALL: $(EXECUTABLE) connection logger sender ui

$(OBJ_DIR)pipeline.o: $(SRC_DIR)pipeline.cpp $(HEADER_DIR)pipeline.h
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJ_DIR)cmdparser.o: $(SRC_DIR)cmdparser.cpp $(HEADER_DIR)cmdparser.h $(OBJ_DIR)pipeline.o
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJ_DIR)init.o: $(SRC_DIR)init.cpp $(HEADER_DIR)init.h $(HEADER_DIR)errormsg.h
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJ_DIR)serial.o: $(SRC_DIR)serial.cpp $(HEADER_DIR)serial.h $(OBJ_DIR)cmdparser.o
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJ_DIR)main.o: $(SRC_DIR)main.cpp $(HEADER_DIR)main.h $(OBJ_DIR)serial.o $(OBJ_DIR)init.o
	$(CC) -c -o $@ $< $(CFLAGS)

$(EXECUTABLE): $(OBJ_DIR)main.o
	$(CC) $(LDFLAGS) $(OBJ_FILES) -o $(BIN_DIR)$(EXECUTABLE)
	
clean:
	rm $(OBJ_FILES)

run:
	./$(BIN_DIR)$(EXECUTABLE)

debug: $(EXECUTABLE) run

install: $(EXECUTABLE)
	cp $(BIN_DIR)$(EXECUTABLE) /bin/
	chmod +x /bin/$(EXECUTABLE)
	
cleanbin:
	rm $(BIN_DIR)* 