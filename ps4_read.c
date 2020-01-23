#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include<stdlib.h>
#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<signal.h>
#include<pthread.h>

short int ld=0;

void handle()
{
close(ld);
}


void *ps4_read()
{
ld = open("/dev/input/event4", O_RDWR);
struct input_event ev;
while(1)
{
read(ld,&ev,sizeof(ev));
//printf("%d \n",ev.value);
if((ev.type==1 ) ||(ev.type==3 &&  (ev.code==16 || ev.code==17) ) ) 
 {
puts("detected");
printf("%d = ",ev.code);
printf("%d",ev.value);
}
}
}

int main(int argc,char**argv)
{
pthread_t p;
pthread_create(&p,NULL,(void *)ps4_read,NULL);
pthread_join(p,NULL);
signal(SIGQUIT,handle);
}
