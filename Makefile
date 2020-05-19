FLAGS = -Wall -Werror -W -pthread -lpthread -g -std=gnu99
ok:ok.c
	gcc $(FLAGS) ok.c -o ok
