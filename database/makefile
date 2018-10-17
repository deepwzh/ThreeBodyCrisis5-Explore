CC = g++
CFLAG = -std=c++11
INCLUDES = -Iinclude
LIBS = -Llib
db: game_achieve_accesser.o database_accesser.o json.o database.o
	$(CC) -o  database database.test.o game_achieve_accesser.o database_accesser.o json.o  \
	 $(LIBS) -ljsoncpp  `mysql_config --cflags --libs` \
	 $(CFLAG)
json.o: json.cpp json.h
	$(CC) -c -g json.cpp $(INCLUDES) \
	$(CFLAG)
database_accesser.o: database_accesser.cpp database_accesser.h
	$(CC) -c -g database_accesser.cpp $(INCLUDES) \
	$(CFLAG)
game_achieve_accesser.o: game_achieve_accesser.cpp game_achieve_accesser.h
	$(CC) -c -g game_achieve_accesser.cpp $(INCLUDES) \
	$(CFLAG)
database.o: database.test.cpp
	$(CC) -c -g test/database.test.cpp $(INCLUDES) \
	$(CFLAG)
clean:
	rm database.o game_achieve_accesser.o database_accesser.o json.o