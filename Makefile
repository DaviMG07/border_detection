all: bin/image bin/image_hps

bin/image:
	@mkdir -p bin
	gcc lib/*.c src/*.c tests/image.c -o bin/image -lm --std=c99 -DCOPROCESSOR

bin/image_hps:
	@mkdir -p bin
	gcc lib/*.c src/*.c tests/image.c -o bin/image_hps -lm --std=c99

run: bin/image
	./bin/image

run_hps: bin/image_hps
	./bin/image_hps

clean:
	rm -f bin/image bin/image_hps

.PHONY: all run run_hps clean

