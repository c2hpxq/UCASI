CC = clang
CFLAGS = -ggdb
LDFLAGS = -lpthread -lrt

TARGETS = \
  child_adder.out\
  create_counter.out\
  shm_cleaner.out\

SHMNAME = aaa

ifdef NOLOCK
CFLAGS += -DNOLOCK
endif

%.out: %.c
	@echo $(NOLOCK)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

test: $(TARGETS) counter.h
	./shm_cleaner.out $(SHMNAME)
	./create_counter.out $(SHMNAME) &
	sleep 5
	./child_adder.out $(SHMNAME)

clean: shm_cleaner.out
	./shm_cleaner.out $(SHMNAME)
	rm -f $(TARGETS)