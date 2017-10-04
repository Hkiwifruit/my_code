#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
void fun1(){
	printf("i am tangsanzang!\n");
}
void fun2(){
	printf("i am sunwukong!\n");
}
void fun3(){
	printf("i am ershixiong!\n");
}
void fun4(){
	printf("i am shashidi!\n");
}
void fun5(){
	printf("i am bailongma!\n");
}
int main()
{
	atexit(fun1);
	atexit(fun2);
	atexit(fun3);
	atexit(fun4);
	atexit(fun5);
	exit(0);
	return 0;
}
