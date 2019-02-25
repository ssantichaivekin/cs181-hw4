self-walk : self-walk-skeleton.c
	gcc -O0 -g -fno-omit-frame-pointer -o self-walk self-walk-skeleton.c
self-walk-part1 : self-walk-skeleton-part1.c
	gcc -O0 -g -fno-omit-frame-pointer -o self-walk-part1 self-walk-skeleton-part1.c

