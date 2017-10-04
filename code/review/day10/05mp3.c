#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

typedef struct _node{
	char name[256];
	struct _node *prev;
	struct _node *next;

}node_t;

node_t *head = NULL;
int first = 1;
node_t *cur = NULL;

void insert_list(char* name)
{
	node_t *p = (node_t*)malloc(sizeof(node_t));
	memset(p, 0, sizeof(node_t));
	strcpy(p->name, name);

	if(head == NULL){
		p->next = p->prev = p;
		head = p;
		cur = p;
		return;
	}

	p->prev = head->prev;
	p->next = head;
	head->prev->next = p;
	head->prev = p;
}

void show_list(void)
{
	node_t *p = head;

	if(p == NULL)printf("how do i??\n"),exit(0);
	int i = 1;
	do{
		printf("%d --> %s\n", i++, p->name);
		p = p->next;
	}while(p != head);
}

void add_music(void)
{
	DIR *pdir = opendir("/home/liang/code/review/music");
	struct dirent *p = NULL;

	char pathname[256] = {};
	while((p = readdir(pdir)) != NULL){
		if(p->d_name[0] == '.')
			continue;
		memset(pathname, 0, sizeof(pathname));
		sprintf(pathname, "/home/liang/code/review/music/%s", p->d_name);
		insert_list(pathname);
	}
	closedir(pdir);
}

int menu(void)
{
	printf("+--------------------------------+\n");
	printf("|          mp3   player          |\n");			
	printf("|   1,playmusic       2,prev     |\n");			
	printf("|   3,continue        4,next     |\n");			
	printf("+--------------------------------+\n");
	printf("chose >");
	int input;
	scanf("%d", &input);
	
	return input;
}

void playpause()
{
	if(first == 1){
		char buf[1024] = {};
		sprintf(buf, "madplay -o wav:- %s 2>/dev/null | aplay 2>/dev/null", cur->name);
		system(buf);
		first = 0;
		printf("cur: %s\n", cur->name);
	}
	else if(first == 0){
		system("killall -19 madplay");
	}
}

void continueplay()
{
	system("killall -18 madplay");
}

void prev()
{
	system("killall -9 madplay");
	cur = cur->prev;
	first = 1;
	playpause();
}

void next()
{
	system("killall -9 madplay");
	cur = cur->next;
	first = 1;
	playpause();
}

void test()
{
	add_music();
	while(1){
		show_list();
		int num = menu();
		switch(num){
			case 1:
				playpause();
				break;
			case 2:
				prev();
				break;
			case 3:
				continueplay();
				break;
			case 4:
				next();
				break;
		}
	}
}
int main(void)
{
	test();
	return 0;
}
