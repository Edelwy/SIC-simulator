# *************  Makefile: SIMULATOR  ****************
CC = g++
CFLAGS = -Wall -g -pedantic
LIBS = -lm
TARGET = test.elf

OBJECTS = \
	Machine.hpp \
	Register.hpp \
	main.cpp
# ****************************************************
${TARGET} : ${OBJECTS}
	@echo "Compiling ..."
	${CC} -o ${TARGET} ${OBJECTS} ${CFLAGS} ${LIBS} 

clean :
	rm -f ${TARGET}

permissive :
	${CC} -o ${TARGET} ${OBJECTS} -fpermissive ${CFLAGS} ${LIBS} 


