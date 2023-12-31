CC=gcc
CFLAGS=-std=c17 -Wall
DEFINE=
TARGET=main
TEST=test
OBJ_DIR =./obj
SRC_DIR =./src
BIN_DIR =./bin
INCLUDE_DIR =./include

${TARGET}: ${OBJ_DIR}/argParser.o ${OBJ_DIR}/accessRecord.o ${OBJ_DIR}/mainPage.o  ${OBJ_DIR}/accessQueue.o ${OBJ_DIR}/pageTable.o  ${OBJ_DIR}/index.o ${OBJ_DIR}/main.o
	${CC} ${DEFINE} ${CFLAGS} -o ${BIN_DIR}/${TARGET} ${OBJ_DIR}/argParser.o ${OBJ_DIR}/accessRecord.o ${OBJ_DIR}/mainPage.o  ${OBJ_DIR}/accessQueue.o ${OBJ_DIR}/pageTable.o ${OBJ_DIR}/index.o ${OBJ_DIR}/main.o

${TEST}: ${OBJ_DIR}/argParser.o ${OBJ_DIR}/accessRecord.o ${OBJ_DIR}/mainPage.o  ${OBJ_DIR}/accessQueue.o ${OBJ_DIR}/pageTable.o  ${OBJ_DIR}/index.o ${OBJ_DIR}/test.o
	${CC} ${DEFINE} ${CFLAGS} -o ${BIN_DIR}/${TEST} ${OBJ_DIR}/argParser.o ${OBJ_DIR}/accessRecord.o ${OBJ_DIR}/mainPage.o  ${OBJ_DIR}/accessQueue.o ${OBJ_DIR}/pageTable.o ${OBJ_DIR}/index.o ${OBJ_DIR}/test.o

${OBJ_DIR}/argParser.o: ${INCLUDE_DIR}/argParser.h
	${CC} ${DEFINE} ${CFLAGS} -I ${INCLUDE_DIR}/ -c ${SRC_DIR}/argParser.c -o ${OBJ_DIR}/argParser.o

${OBJ_DIR}/accessRecord.o: ${INCLUDE_DIR}/accessRecord.h
	${CC} ${DEFINE} ${CFLAGS} -I ${INCLUDE_DIR}/ -c ${SRC_DIR}/accessRecord.c -o ${OBJ_DIR}/accessRecord.o

${OBJ_DIR}/mainPage.o: ${INCLUDE_DIR}/mainPage.h
	${CC} ${DEFINE} ${CFLAGS} -I ${INCLUDE_DIR}/ -c ${SRC_DIR}/mainPage.c -o ${OBJ_DIR}/mainPage.o

${OBJ_DIR}/accessQueue.o: ${INCLUDE_DIR}/accessQueue.h
	${CC} ${DEFINE} ${CFLAGS} -I ${INCLUDE_DIR}/ -c ${SRC_DIR}/accessQueue.c -o ${OBJ_DIR}/accessQueue.o

${OBJ_DIR}/pageTable.o: ${INCLUDE_DIR}/pageTable.h
	${CC} ${DEFINE} ${CFLAGS} -I ${INCLUDE_DIR}/ -c ${SRC_DIR}/pageTable.c -o ${OBJ_DIR}/pageTable.o

${OBJ_DIR}/index.o: ${INCLUDE_DIR}/index.h
	${CC} ${DEFINE} ${CFLAGS} -I ${INCLUDE_DIR}/ -c ${SRC_DIR}/index.c -o ${OBJ_DIR}/index.o

${OBJ_DIR}/main.o: ${INCLUDE_DIR}/index.h
	${CC} ${DEFINE} ${CFLAGS} -I ${INCLUDE_DIR}/ -c ${SRC_DIR}/main.c -o ${OBJ_DIR}/main.o

${OBJ_DIR}/test.o: ${INCLUDE_DIR}/index.h
	${CC} ${DEFINE} ${CFLAGS} -I ${INCLUDE_DIR}/ -c ${SRC_DIR}/test.c -o ${OBJ_DIR}/test.o

clean:
	rm -f ${BIN_DIR}/* ${OBJ_DIR}/*