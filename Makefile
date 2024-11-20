CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11
LDFLAGS = 

TARGET_MAIN = main.exe
TARGET_TEST = test_c_list.exe

OBJS_MAIN = main.o c_list.o
OBJS_TEST = test_c_list.o c_list.o

all: $(TARGET_MAIN)

$(TARGET_MAIN): $(OBJS_MAIN)
	$(CC) $(LDFLAGS) -o $@ $^

$(TARGET_TEST): $(OBJS_TEST)
	$(CC) $(LDFLAGS) -o $@ $^

main.o: main.c c_list.h
	$(CC) $(CFLAGS) -c main.c

test_c_list.o: test_c_list.c c_list.h
	$(CC) $(CFLAGS) -c test_c_list.c

c_list.o: c_list.c c_list.h
	$(CC) $(CFLAGS) -c c_list.c

task_8_1.exe: task_8_1.o
	gcc -o task_8_1.exe task_8_1.o
 task_8_1.o: task_8_1.c
	gcc -Wall -Wextra -pedantic -std=c11 -c task_8_1.c

clean:
	del /f /q *.o *.exe
