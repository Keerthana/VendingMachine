################################
OPT:=

CXX = u++										# compiler
CXXFLAGS = -g -multi -Wall -Wno-unused-label -MMD ${OPT} # compiler flags
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

OBJECTS =  bank.o vendingmachine.o watcard.o watcardoffice.o parent.o student.o config.o nameserver.o printer.o  bottlingplant.o truck.o student.o soda.o # 
DEPENDS = ${OBJECTS:.o=.d}						# substitute ".o" with ".d"
EXEC = soda

#############################################################
.PHONY : all clean

all : ${EXEC}									# build all executables

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} $^ -o $@

#############################################################
${OBJECTS} : ${MAKEFILE_NAME}					# OPTIONAL : changes to this file => recompile

-include ${DEPENDS}								# include *.d files containing program dependences

clean :											# remove files that can be regenerated
	rm -f *.d *.o ${EXEC} ImplType
