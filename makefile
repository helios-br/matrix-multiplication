# CONSTANTS

COMPILATION_OPTS = -Wall -g
APPLICATION_NAME = matrix-app
SOURCES_DIR = ./src/cpp
SOURCES = $(wildcard $(SOURCES_DIR)/*.cpp $(SOURCES_DIR)/external/*.cpp $(SOURCES_DIR)/util/*.cpp)
OUTPUT_DIR = ./output
RUN = run.sh

# OPTIONS
# g++ -Wall -fopenmp -g $(SOURCES) -o $(OUTPUT_DIR)/$(APPLICATION_NAME)

all: build

clean:
	@clear
	@echo "Cleaning..."
	@rm -rf output
	@rm -rf $(RUN)
	@echo "# All clean!"
	
compile: clean
	@echo "Compiling application..."
	@mkdir output	
	g++ -Wall -fopenmp -lstdc++ -g $(SOURCES) -o $(OUTPUT_DIR)/$(APPLICATION_NAME)
	@echo "# Done!"

build: compile
	@echo
	@echo "Building application..."
	# CREATING RUN.SH 
	@touch $(RUN)
	@echo "clear" >> $(RUN)
	@echo "echo -e 'Running application...'" >> $(RUN)
	@echo "echo" >> $(RUN)
	@echo "rm log.txt" >> $(RUN)
	@echo "cd output" >> $(RUN)
	@echo "./$(APPLICATION_NAME) $$""1" "&> ../log.txt" >> $(RUN)
	@echo "echo" >> $(RUN)
	@echo "echo -e '# Done!'" >> $(RUN)
	@echo "echo" >> $(RUN)
	# COPYING INSTANCES TO OUTPUT DIRECTORY
	@cp -r ./instances/. output
	@echo "Process completed!"
	@echo "Execute: ./run.sh instance_name"
