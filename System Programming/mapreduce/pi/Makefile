EXECS=mapper_pi reducer_pi

all: $(EXECS)

CC=g++ -O3 -Wall

mapper_pi: mapper_pi.c ../core/mapper.c
	$(CC) $^ -o $@

reducer_pi: reducer_pi.c ../core/reducer.c ../core/libds.c
	$(CC) $^ -o $@

clean:
	rm -f $(EXECS) *.o *~
