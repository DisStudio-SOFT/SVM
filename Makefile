CC=gcc
CCFLAGS=-Wall

SRC=$(shell find src/ -name *.c)
OUT=$(patsubst src/%.c, out/%.o, $(SRC))

$(OUT): out/%.o: src/%.c
	@mkdir -p $(dir $@)
	@echo " CC     $@"
	@$(CC) -c $(CCFLAGS) $(patsubst out/%.o, src/%.c, $@) -o $@

build: $(OUT)
	@$(CC) $(CCFLAGS) $(OUT) -o svm
	@echo "done"
clean:
	@rm -r out
	@mkdir out