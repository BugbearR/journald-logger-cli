#CC = cc
#LINK.c = cc
CFLAGS = -g -Wall -Wextra
LDLIBS = -lsystemd

.PHONY: all
all: journald-logger-cli

.PHONY: clean
clean:
	$(RM) journald-logger-cli.o

journald-logger-cli : journald-logger-cli.o

journald-logger-cli.o: journald-logger-cli.c
