CC = g++
INC = include
SRC = src
BUILD = build
INCLUDE = -I ./$(INC)

TARGET = steiner

OBJECTS = $(BUILD)/main.o $(BUILD)/aco.o $(BUILD)/ant.o $(BUILD)/common.o $(BUILD)/timer.o \
			$(BUILD)/dijkstra.o $(BUILD)/genetic.o $(BUILD)/mst.o $(BUILD)/solution.o

$(TARGET): $(OBJECTS)
	@$(CC) -o $@ $^ $(INCLUDE)

$(BUILD)/%.o: $(SRC)/%.cpp
	@mkdir -p $(BUILD)
	@$(CC) -o $@ -c $^ $(INCLUDE)

clean:
	@echo "Cleaning..."
	@rm -rf $(BUILD) $(TARGET)
