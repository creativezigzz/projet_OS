FLAGS = -Wall -W -pthread -lpthread -g -std=gnu99
projet:projet.c palin
	gcc $(FLAGS) projet.c -o projet
palin:palin.c
	gcc $(FLAGS) palin.c -o palin
