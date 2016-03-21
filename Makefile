CXX = clang
CXXFLAGS = -emit-llvm
OBJECTS = infer_invariants.o CallGraph.o
CPPFILES = infer_invariants.cpp
DEPENDS = ${OBJECTS:.o=.d}
EXEC = pipair

${EXEC} : ${OBJECTS}
        ${CXX} ${CXXFLAGS} -c {CPPFILES} -o ${EXEC}

clean :
        rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS}