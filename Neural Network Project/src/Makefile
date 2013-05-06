CC = g++
RM = rm
CP = cp

EXE = nnproject.exe
SRCS = main.cpp
ART2NETWORKOBJS = art2network/ART2Network.o art2network/Maxnet.o art2network/nnfunctions.o
FREQUENCYOBJS = frequency/FrequencyRecord.o frequency/FrequencyTable.o
OBJS = $(SRCS:.cpp=.o) $(ART2NETWORKOBJS) $(FREQUENCYOBJS)
BIN = ../bin

.SUFFIXES: .cpp .o
.PHONY: all clean

all: $(EXE)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(EXE): $(OBJS) 
	$(CC) $(CFLAGS) -o $(EXE) $(OBJS)
	$(CP) $(EXE) $(BIN)/$(EXE)

$(ART2NETWORKOBJS): art2network/indextypes.h art2network/Vector.h art2network/Matrix.h

art2network/Maxnet.o art2network/ART2Network.o: art2network/nntypes.h art2network/nnfunctions.h

$(FREQUENCYOBJS): frequency/FrequencyRecord.h

frequency/FrequencyTable.o: frequency/FrequencyTable.h

clean:
	-$(RM) -f $(EXE) $(OBJS)
 