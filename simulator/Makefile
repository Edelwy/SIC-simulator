# *************  Makefile: SIMULATOR  ****************
CC = g++
CFLAGS = -Wall -g -pedantic
LIBS = -lm
TARGET = test.elf

OBJECTS = \
	Machine.hpp \
	Register.hpp \
	Pomnilnik.hpp \
	Device.hpp \
	Opcode.hpp \
	main.cpp
	
# ****************************************************
${TARGET} : ${OBJECTS}
	@echo "Compiling..."
	${CC} -o ${TARGET} ${OBJECTS} ${CFLAGS} ${LIBS} 

clean :
	rm -f ${TARGET}

permissive :
	@echo "Compiling with 'permissive' enabled..."
	${CC} -o ${TARGET} ${OBJECTS} -fpermissive ${CFLAGS} ${LIBS} 


