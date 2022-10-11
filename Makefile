CC = g++
CFLAGS = -O1 -g
SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system

SRC_DIR   = ./src
INC_DIR   = ./include
BUILD_DIR = ./build
EXEC_FILE = raytracing


all: debug

debug: $(BUILD_DIR)/main.o $(BUILD_DIR)/vector.o $(BUILD_DIR)/sphere.o $(BUILD_DIR)/window.o $(BUILD_DIR)/light.o \
       $(BUILD_DIR)/scene.o $(BUILD_DIR)/color.o $(BUILD_DIR)/ray.o $(BUILD_DIR)/camera.o $(BUILD_DIR)/quadratic.o
	$(CC) $(CFLAGS) $(SFML_FLAGS) $(BUILD_DIR)/main.o $(BUILD_DIR)/vector.o $(BUILD_DIR)/scene.o   \
		$(BUILD_DIR)/sphere.o  $(BUILD_DIR)/window.o $(BUILD_DIR)/light.o $(BUILD_DIR)/color.o \
        	$(BUILD_DIR)/quadratic.o $(BUILD_DIR)/ray.o $(BUILD_DIR)/camera.o -o $(EXEC_FILE)

$(BUILD_DIR)/main.o: main.cc
	$(CC) $(CFLAGS) -c main.cc -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/vector.o: $(SRC_DIR)/vector.cc $(INC_DIR)/vector.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/vector.cc -o $(BUILD_DIR)/vector.o

$(BUILD_DIR)/scene.o: $(SRC_DIR)/scene.cc $(INC_DIR)/scene.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/scene.cc -o $(BUILD_DIR)/scene.o

$(BUILD_DIR)/sphere.o: $(SRC_DIR)/sphere.cc $(INC_DIR)/sphere.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/sphere.cc -o $(BUILD_DIR)/sphere.o

$(BUILD_DIR)/window.o: $(SRC_DIR)/window.cc $(INC_DIR)/window.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/window.cc -o $(BUILD_DIR)/window.o

$(BUILD_DIR)/light.o: $(SRC_DIR)/light.cc $(INC_DIR)/light.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/light.cc -o $(BUILD_DIR)/light.o

$(BUILD_DIR)/color.o: $(SRC_DIR)/color.cc $(INC_DIR)/color.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/color.cc -o $(BUILD_DIR)/color.o

$(BUILD_DIR)/ray.o: $(SRC_DIR)/ray.cc $(INC_DIR)/ray.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/ray.cc -o $(BUILD_DIR)/ray.o

$(BUILD_DIR)/camera.o: $(SRC_DIR)/camera.cc $(INC_DIR)/camera.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/camera.cc -o $(BUILD_DIR)/camera.o

$(BUILD_DIR)/quadratic.o: ./utils/quadratic.cc ./utils/quadratic.h
	$(CC) $(CFLAGS) -c ./utils/quadratic.cc -o $(BUILD_DIR)/quadratic.o

clean:
	rm $(BUILD_DIR)/*.o $(EXEC_FILE)
