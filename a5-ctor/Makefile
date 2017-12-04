CXX = g++-5
CXXFLAGS = -std=c++14 -g -Wall -MMD
EXEC = ctor
OBJECTS =  path.o address.o board.o builder.o graphicDisplay.o main.o subject.o tile.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean
clean: 
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
