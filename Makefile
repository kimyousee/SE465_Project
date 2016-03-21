CXX = clang++
CXXFLAGS = -emit-llvm
LINK = llvm-link
CPPFILES = infer_invariants.cpp CallGraph.cpp
OBJECTS = infer_invariants.o CallGraph.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = ${OBJECTS:.o=}
TARGET = pipair

all: ${OBJECTS} ${TARGET}

%: %.o
	${CXX} -o $@ -shared $< ${CXXFLAGS}

${TARGET} : ${OBJECTS}
	${LINK} -v ${OBJECTS} -o $@

clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS}
