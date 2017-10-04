#include <stdio.h> 
#include <stdlib.h> 
int g_val = 100; 
void test() {
	     int a = 10;     
		 int b = 10;     
		 printf("test stack1 address : 0x%x\n", &a);     
		 printf("test stack2 address : 0x%x\n", &b); 
}

void (*fp)(); 
int main() {
	     int a = 10;     
		 int *heap = malloc(sizeof(int));    
		 fp = test;     
		 printf("code address  : 0x%x\n", fp);     
		 printf("data address  : 0x%x\n", &g_val);     
		 printf("heap  address  : 0x%x\n", heap);     
		 printf("main stack0 address : 0x%x\n", &a);     
		 fp();    
		 return 0; 
}
