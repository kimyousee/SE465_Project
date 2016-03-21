#CXX = clang++
#CXXFLAGS = -emit-llvm -pedantic -Wall -v -stdlib=libstdc++
#LINK = llvm-link
CXX = g++
CPPFILES = infer_invariants.cpp CallGraph.cpp
OBJECTS = infer_invariants.o CallGraph.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = ${OBJECTS:.o=}
TARGET = pipairTarget

all: ${OBJECTS} ${TARGET}

${TARGET} : ${OBJECTS}
	${CXX} ${CPPFILES} -o ${TARGET}

#%: %.o
#	${CXX} -o $@ -shared $< ${CXXFLAGS}


# ${TARGET} : ${OBJECTS}
#	${LINK} -v ${OBJECTS} -o $@ -f

clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS}
