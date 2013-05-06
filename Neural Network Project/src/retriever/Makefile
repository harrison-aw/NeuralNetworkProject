CC = g++
RM = rm
CP = cp

CFLAGS = -I/usr/include/libxml2
LIBS = -ltidy -llibxml2 -lcurl

EXE = retrieve.exe
SRCS = main.cpp GitHubLink.cpp
OBJS = $(SRCS:.cpp=.o)
BIN = ../../bin

.SUFFIXES: .cpp .o
.PHONY: all clean

all: retrieve.exe

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

$(EXE): $(OBJS) 
	$(CC) $(CFLAGS) -o $(EXE) $(OBJS) $(LIBS)
	$(CP) $(EXE) $(BIN)/$(EXE)

$(OBJS): GitHubLink.h

clean:
	-$(RM) -f $(EXE) $(OBJS)
 