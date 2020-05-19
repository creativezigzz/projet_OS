FLAGS = -Wall -W -pthread -lpthread -g -std=gnu99
ok:ok.c palin
	gcc $(FLAGS) ok.c -o ok
palin:palin.c
	gcc $(FLAGS) palin.c -o palin
