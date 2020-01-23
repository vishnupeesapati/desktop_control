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


int ld;
void press(int n)
{

        struct input_event ev;

      ev.type = 1;
                              ev.code = n;
                              ev.value = 1;     // 0 = released, 1 = pressed
                              ////key press
                               write(ld, &ev, sizeof(struct input_event));

			   //   ev.type = EV_SYN;
			     //  ev.code = SYN_REPORT;
                             ////key press report
			     //  write(ld,&ev,sizeof(struct input_event));
			       //type EV_SYN
			       //code EV_REPORT
                         
			      ev.code = n;
                              ev.value=0;
                              write(ld,&ev,sizeof(struct input_event));
                          //////key release
			      ev.code = SYN_REPORT;
			      ev.type = EV_SYN;

			      write(ld,&ev,sizeof(struct input_event));
			  /////////key press report

                
}

int main(int argc,char**argv)
{
ld = open("/dev/input/event4", O_RDWR);

press(atoi(argv[1]));


close(ld);
}
