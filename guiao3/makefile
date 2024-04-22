CFLAGS=-Wall -Wextra -pedantic -O2
OBJS=$(patsubst %.c, %.o, $(wildcard *.c))

all: ccard

ccard: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

complexidade:
	@echo Only printing when Modified McCabe Cyclomatic Complexity is above 5
	@pmccabe *.c | sort -nr | awk '{if($$1>5)print}'

check:
	cppcheck --enable=all --suppress=missingIncludeSystem .

codigo.zip: $(wildcard *.h) $(wildcard *.c)
	zip -9r $@ $^

clean:
	rm -f $(OBJS) codigo.zip