CC = g++
FILES = *.cpp
LINUX_LINKER_FLAGS = -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -lm -ldl -lXinerama -lXcursor -lSOIL
MAC_LINKER_FLAGS = -framework OpenGl -lglfw3 -lSOIL -framework CoreFoundation
OBJS = *.o
BIN = Main
DELETER = rm -f
OS := $(shell uname)

run:
ifeq ($(OS),Darwin)
	$(MAKE) mac
else
	$(MAKE) linux
endif

mac:
	$(CC) -c $(FILES)
	$(CC) $(OBJS) -o $(BIN) $(MAC_LINKER_FLAGS)
	./$(BIN)
linux:
	$(CC) -c $(FILES) 
	$(CC) $(OBJS) -o $(BIN) $(LINUX_LINKER_FLAGS)
	./$(BIN)
clean:
	$(DELETER) $(OBJS) $(BIN)