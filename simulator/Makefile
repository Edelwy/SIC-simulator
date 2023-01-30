# *************  Makefile: SIMULATOR  ****************
CC = g++
CFLAGS = -Wall -g -pedantic
LIBS = -lm
TARGET = simulator.elf

OBJECTS = \
	Machine.hpp.gch \
	Register.hpp.gch \
	Pomnilnik.hpp.gch \
	Device.hpp.gch \
	Opcode.hpp.gch \
	Execute.hpp.gch \
	Executer.hpp.gch \
	Command.hpp.gch \
	Runner.hpp.gch \
	CPU.hpp.gch \
	Loader.hpp.gch \
	Reader.hpp.gch \
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

Runner.hpp.gch : Runner.hpp
	${CC} -c  Runner.hpp ${CFLAGS} ${LIBS}

CPU.hpp.gch : CPU.hpp
	${CC} -c  CPU.hpp ${CFLAGS} ${LIBS}

Loader.hpp.gch : Loader.hpp
	${CC} -c  Loader.hpp ${CFLAGS} ${LIBS}

Reader.hpp.gch : Reader.hpp
	${CC} -c  Reader.hpp ${CFLAGS} ${LIBS}

main.o : main.cpp
	${CC} -c  main.cpp ${CFLAGS} ${LIBS}

