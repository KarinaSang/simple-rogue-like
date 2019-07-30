CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -MMD -Werror
EXEC = cc3k+
OBJECTS = main.o textdisplay.o game.o cell.o enemy.o player.o treasure.o potion.o dragon.o merchant.o playerdecorator.o enemydecorator.o basicenemy.o vampiredecorator.o trolldecorator.o goblindecorator.o basicplayer.o elfdecorator.o orcdecorator.o dwarfdecorator.o

DEPENDS = ${OBJECTS:.o=.d}

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
