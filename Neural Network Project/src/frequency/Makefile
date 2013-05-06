CC = g++
RM = rm
CP = cp

CFLAGS =

EXE = frequency.exe
SRCS = main.cpp FrequencyRecord.cpp FrequencyTable.cpp
OBJS = $(SRCS:.cpp=.o)
BIN = ../../bin

.SUFFIXES: .cpp .o
.PHONY: all clean objects

all: $(EXE)

%.o: %.cpp FrequencyRecord.h
	$(CC) $(CFLAGS) -c $<

main.o FrequencyTable.o: FrequencyTable.h

$(EXE): $(OBJS) 
	$(CC) $(CFLAGS) -o $(EXE) $(OBJS)
	$(CP) $(EXE) $(BIN)/$(EXE)

clean:
	-$(RM) -f $(EXE) $(OBJS)
 