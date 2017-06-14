#CC = g++
CC = icpc
CFLAGS = -Wall -std=c++0x
#CFLAGS += -g
LDFLAGS = -I/opt/local/include
LIBS = -L/opt/local/lib -lpng

# list of sources:
SOURCE = imageconv.cpp pngio.cpp util.cpp conv.cpp image.cpp pixel.cpp
OBJECTS = $(SOURCE:.cpp=.o)

# execuatble
EXECUTABLE = imageconv

all: $(SOURCE) $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS) $(LIBS)

.cpp.o:
	$(CC) $(CFLAGS) -c $< $(LDFLAGS)

clean:
	rm $(OBJECTS) $(EXECUTABLE)
