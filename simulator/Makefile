# *************  Makefile: SIMULATOR  ****************
CC = g++
CFLAGS = -Wall -g -pedantic
LIBS = -lm
TARGET = test.elf

OBJECTS = \
	Machine.hpp.gch \
	Register.hpp.gch \
	Pomnilnik.hpp.gch \
	Device.hpp.gch \
	Opcode.hpp.gch \
	Execute.hpp.gch \
	Executer.hpp.gch \
	Command.hpp.gch \
	main.o

EXECUTABLES = \
	main.o

# ****************************************************
${TARGET} : ${OBJECTS}
	@echo "Compiling..."
	${CC} -o ${TARGET} ${EXECUTABLES} ${CFLAGS} ${LIBS} 

clean :
	rm -f ${TARGET} ${OBJECTS}

permissive :
	@echo "Compiling with 'permissive' enabled..."
	${CC} -o ${TARGET} ${EXECUTABLES} -fpermissive ${CFLAGS} ${LIBS} 

# ************ COMPILING ******************************
Machine.hpp.gch : Machine.hpp
	${CC} -c  Machine.hpp ${CFLAGS} ${LIBS} 

Register.hpp.gch : Register.hpp
	${CC} -c  Register.hpp ${CFLAGS} ${LIBS}

Pomnilnik.hpp.gch : Pomnilnik.hpp
	${CC} -c  Pomnilnik.hpp ${CFLAGS} ${LIBS}

Device.hpp.gch : Device.hpp
	${CC} -c  Device.hpp ${CFLAGS} ${LIBS}

Opcode.hpp.gch : Opcode.hpp
	${CC} -c  Opcode.hpp ${CFLAGS} ${LIBS}

Execute.hpp.gch : Execute.hpp
	${CC} -c  Execute.hpp ${CFLAGS} ${LIBS}

Executer.hpp.gch : Executer.hpp
	${CC} -c  Executer.hpp ${CFLAGS} ${LIBS}

Command.hpp.gch : Command.hpp
	${CC} -c  Command.hpp ${CFLAGS} ${LIBS}

main.o : main.cpp
	${CC} -c  main.cpp ${CFLAGS} ${LIBS}

