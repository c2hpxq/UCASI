
CC = gcc
LDFLAGS = -lpthread

fair: rwlock_test.c rwlock.c rwlock.h
	$(CC) -DFAIR=1 rwlock_test.c rwlock.c $(LDFLAGS) -o fair

unfair: rwlock_test.c rwlock.c rwlock.h
	$(CC) rwlock_test.c rwlock.c $(LDFLAGS) -o unfair

.PHONY: test, clean

test: fair unfair
	time ./fair
	time ./unfair

clean:
	rm fair unfair