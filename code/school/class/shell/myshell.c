#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int g_val =0 ;
int main()
{
//	const char* msg= "hello fwrite\n";
//	const char* msg2 = "hello wirte\n";
//	printf("hello printf!\n");
//	fwrite(msg, strlen(msg),1, stdout);
//
//	write(1, msg2,strlen(msg2));
	pid_t id = fork();
 if(id == 0){
	g_val=100;
	printf("i am child process! pid: %d, ppid: %d, g_val: %d, &g_val: %p\n",getpid(),getppid(),g_val,&g_val);
	sleep(100);
	exit(1);
}

else{
	printf("i am father process! pid: %d, ppid: %d, g_val: %d, &v_val: %p\n",getpid(),getppid(),g_val,&g_val);
	int status=0;
	pid_t ret= waitpid(id,&status,0);

	if (ret>0){
	if(WIFEXITED(status)){
			printf("exitcode: %d\n",WEXITSTATUS(status));
		}else{
			printf("child is quit not normal!\n");
		}
		//printf("wait success! ret:%d, status: %d, signal: %d, exitcode: %d\n",ret,status,status&0xff,(status)>>8&0xff);
	}else{
		perror("waitpid");
	}
}
//
// close(1);
// int fd = open("./mylog",O_WRONLY|O_CREAT,644);
// if(fd==-1){
// 	perror("open");
// 	return 1;
// }
// 
// //int fd1 = open("./mylog1",O_WRONLY|O_CREAT,644);
// //int fd2 = open("./mylog2",O_WRONLY|O_CREAT,644);
// //printf("fd: %d\n",fd);
// //
// //printf("fd1: %d\n",fd1);
// //printf("fd2: %d\n",fd2);
// const char* msg="hello fd!\n";
// int i=0;
// while(i<10){
// 	fwrite(msg, strlen(msg), 1, stdout);
// 	fflush(stdout);
// 	//write(fd, msg, strlen(msg));
// 	i++;
// }
//
// close(fd);
//
//
//FILE *fp=fopen("./log","w");
//if (NULL==fp){
//
//	perror("fopen");
//	return 1;
//}
//
//const char* msg="hello world\n";
//int i=0;
//while(i<10){
//	fwrite(msg, strlen(msg),1, fp);
//	i++;
//}
//
//pid_t pid = fork();
//if(pid < 0){
//	perror("error fork!");
//	exit(1);
//}
//else if(pid == 0){
//	printf("i am child process! pid: %d, ppid: %d\n",getpid(),getppid());
//	sleep(5);
//	printf("i am child process! pid: %d, ppid: %d\n",getpid(),getppid())
//}
//else{
//	printf("i am father process! pid: %d, ppid: %d\n",getpid(),getppid());
//	sleep(1);
//}
//return 0;
}
