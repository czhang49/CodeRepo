CXX = clang++
CXXFLAGS = -Iinclude -std=c++1y -stdlib=libc++ -g -O0 -c -Wall -Wextra
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lpng

.PHONY: all clean tidy

ifdef SANITIZE
CXXFLAGS += -fsanitize=$(SANITIZE)
LDFLAGS += -fsanitize=$(SANITIZE)
endif

EXES = circ_array_test stack_queue_test ast_test lex_test parse_test

EPNG_HEADERS = include/epng.h include/rgba_pixel.h

CIRC_ARR_HEADERS = include/circ_array.h include/circ_array.tcc
STACK_HEADERS = include/stack.h include/stack.tcc
QUEUE_HEADERS = include/queue.h include/queue.tcc
OS_HEADERS = $(CIRC_ARR_HEADERS) $(STACK_HEADERS) $(QUEUE_HEADERS)

TOKEN_HEADERS = include/token.h include/number.h include/operation.h
UNOP_HEADERS = include/unary_op.h include/uplus.h include/uminus.h
BINOP_HEADERS = include/binary_op.h include/divide.h include/exponent.h \
				include/minus.h include/plus.h include/times.h
NODE_HEADERS = include/node.h include/terminal.h $(BINOP_HEADERS)

TOKEN_OBJS = token.o number.o operation.o
NODE_OBJS = terminal.o binary_op.o divide.o exponent.o minus.o plus.o times.o \
			unary_op.o uplus.o uminus.o

all: $(EXES)

circ_array_test.o : $(CIRC_ARR_HEADERS) src/circ_array_test.cpp
	$(CXX) $(CXXFLAGS) src/circ_array_test.cpp

circ_array_test : circ_array_test.o
	$(CXX) $(LDFLAGS) circ_array_test.o -o circ_array_test

stack_queue_test.o : $(CIRC_ARR_HEADERS) $(STACK_HEADERS) $(QUEUE_HEADERS) \
   	src/stack_queue_test.cpp
	$(CXX) $(CXXFLAGS) src/stack_queue_test.cpp

stack_queue_test : stack_queue_test.o
	$(CXX) $(LDFLAGS) stack_queue_test.o -o stack_queue_test

rgba_pixel.o : include/rgba_pixel.h src/rgba_pixel.cpp
	$(CXX) $(CXXFLAGS) src/rgba_pixel.cpp

epng.o : include/epng.h src/epng.cpp
	$(CXX) $(CXXFLAGS) src/epng.cpp

token.o : include/token.h src/token.cpp
	$(CXX) $(CXXFLAGS) src/token.cpp

number.o : include/token.h include/number.h src/number.cpp
	$(CXX) $(CXXFLAGS) src/number.cpp

operation.o : include/token.h include/operation.h src/operation.cpp
	$(CXX) $(CXXFLAGS) src/operation.cpp

lex.o : $(TOKEN_HEADERS) include/lex.h src/lex.cpp
	$(CXX) $(CXXFLAGS) src/lex.cpp

lex_test.o : include/lex.h $(TOKEN_HEADERS) src/lex_test.cpp
	$(CXX) $(CXXFLAGS) src/lex_test.cpp

lex_test : lex_test.o lex.o token.o number.o operation.o
	$(CXX) $(LDFLAGS) $^ -o $@

terminal.o : include/node.h include/terminal.h src/terminal.cpp
	$(CXX) $(CXXFLAGS) src/terminal.cpp

unary_op.o : include/node.h include/unary_op.h src/unary_op.cpp
	$(CXX) $(CXXFLAGS) src/unary_op.cpp

uplus.o : include/node.h include/unary_op.h include/uplus.h src/uplus.cpp
	$(CXX) $(CXXFLAGS) src/uplus.cpp

uminus.o : include/node.h include/unary_op.h include/uminus.h src/uminus.cpp
	$(CXX) $(CXXFLAGS) src/uminus.cpp

binary_op.o : include/node.h include/binary_op.h src/binary_op.cpp
	$(CXX) $(CXXFLAGS) src/binary_op.cpp

divide.o : include/node.h include/binary_op.h include/divide.h src/divide.cpp
	$(CXX) $(CXXFLAGS) src/divide.cpp

exponent.o : include/node.h include/binary_op.h include/exponent.h src/exponent.cpp
	$(CXX) $(CXXFLAGS) src/exponent.cpp

minus.o : include/node.h include/binary_op.h include/divide.h src/divide.cpp
	$(CXX) $(CXXFLAGS) src/minus.cpp

plus.o : include/node.h include/binary_op.h include/plus.h src/plus.cpp
	$(CXX) $(CXXFLAGS) src/plus.cpp

times.o : include/node.h include/binary_op.h include/times.h src/times.cpp
	$(CXX) $(CXXFLAGS) src/times.cpp

ast_test.o : $(NODE_HEADERS) src/ast_test.cpp
	$(CXX) $(CXXFLAGS) src/ast_test.cpp

ast_test : $(NODE_OBJS) ast_test.o
	$(CXX) $(LDFLAGS) $^ -o $@

parser.o : $(TOKEN_HEADERS) $(NODE_HEADERS) src/parser.cpp
	$(CXX) $(CXXFLAGS) src/parser.cpp

parse_test.o : $(TOKEN_HEADERS) $(NODE_HEADERS) include/lex.h include/parser.h src/parse_test.cpp
	$(CXX) $(CXXFLAGS) src/parse_test.cpp

parse_test : $(TOKEN_OBJS) $(NODE_OBJS) lex.o parser.o parse_test.o
	$(CXX) $(LDFLAGS) $^ -o $@

doc: $(wildcard include/*) $(wildcard src/*) mp_parse.doxygen
	doxygen mp_parse.doxygen

clean:
	rm -rf *.o $(EXES) doc
