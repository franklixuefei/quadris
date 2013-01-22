CXX = g++
CXXFLAGS = -Wall -MMD -L/usr/X11R6/lib -lX11
EXEC = quadris
OBJECTS = main.o tree.o command.o block.o blockAnimation.o cell.o grid.o iblock.o jblock.o lblock.o nextBlock.o oblock.o quadris.o sblock.o tblock.o zblock.o window.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}

