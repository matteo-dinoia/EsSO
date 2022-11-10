#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>

#define PANIC(string) exit((dprintf(1, "FATAL: %s\n", (string)), 1))
#define READ 0
#define WRITE 1


int main(int argc, char **argv){
	/*ARGUMENT CHECK AND OBTAIN VALUES*/
	if(argc<3)
		PANIC("not enougth parameters\n");
	int num_child=atoi(argv[1]);
	int initial_value=atoi(argv[2]);
	if(num_child<=0 || initial_value<=0 )
		PANIC("negative or null parameter/s\n");

	/*CREATE CHILD*/
	int pid, initialFd[2], oldFd[2], fd[2];
	int p_write=-1, p_read=-1;
	for(int i=0; i<num_child; i++){
		if(i==0){ //FIST
			if(pipe(initialFd)==-1) PANIC("failed pipe\n");
			p_write=initialFd[WRITE];
			p_read=initialFd[READ];
			memcpy(oldFd, initialFd, 2*sizeof(int));
			if(pipe(fd)==-1) PANIC("failed pipe\n");
		}
		else if(i==num_child-1){ //LAST
			memcpy(oldFd, fd, 2*sizeof(int));
			memcpy(fd, initialFd, 2*sizeof(int));
		}
		else{ //MIDDLE
			memcpy(oldFd, fd, 2*sizeof(int));
			if(pipe(fd)==-1) PANIC("failed pipe\n");
		}

		if((pid=fork())==0){/*CHILD*/
			close(oldFd[WRITE]);//close write old
			close(fd[READ]);//clode read old
			p_write = fd[WRITE];
			p_read= oldFd[READ];
			break;
		}
		else if(pid==-1)
			PANIC("during forking child\n");
		else{
			if(i!=0){
				close(oldFd[READ]);
				close(oldFd[WRITE]);
			}
		}
	}

	if(pid==0){ //SON
		int buf;
		while(1){
			read(p_read, &buf, sizeof(int));
			dprintf(1, "READ %d (child pid=%d)\n", buf, getpid());
			if(buf==0){
				write(p_write, &buf, sizeof(int));
				dprintf(1, "WROTE 0 AND FINISHED (child pid=%d)\n", getpid());

				close(p_read);
				close(p_write);
				exit(0);
			}
			buf--;
			write(p_write, &buf, sizeof(int));
			dprintf(1, "WRITE %d (child pid=%d)\n", buf, getpid());
		}
	}
	else{ //FATHER
		//WRITE
		write(p_write, &initial_value, sizeof(int));
		dprintf(1, "WROTE %d (father)\n", initial_value);

		//CLOSE
		close(p_read);
		close(p_write);


		while((pid=wait(NULL))!=-1|| errno==EINTR){
			if(errno!=EINTR){
				dprintf(1, "\tDEAD (child pid=%d)\n", pid);
			}
		}
	}

	return 0;
}