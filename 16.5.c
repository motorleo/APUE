#include "apue.h"
#include <netdb.h>
#include <errno.h>
#include <syslog.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <signal.h>

#define QLEN 10

#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX 256
#endif

/* Reliable version of signal(), using POSIX sigaction().  */
Sigfunc *
signal(int signo, Sigfunc *func)
{
	struct sigaction	act, oact;

	act.sa_handler = func;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	if (signo == SIGALRM) {
#ifdef	SA_INTERRUPT
		act.sa_flags |= SA_INTERRUPT;
#endif
	} else {
		act.sa_flags |= SA_RESTART;
	}
	if (sigaction(signo, &act, &oact) < 0)
		return(SIG_ERR);
	return(oact.sa_handler);
}
extern int initserver(int, const struct sockaddr *, socklen_t, int);

void sigchld(int signo){
	while (wait(NULL)>0){};
}

void
serve(int sockfd)
{
	int		clfd, status;
	pid_t	pid;

	set_cloexec(sockfd);
	for (;;) {
		if ((clfd = accept(sockfd, NULL, NULL)) < 0) {
		//	syslog(LOG_ERR, "ruptimed: accept error: %s",
		//	  strerror(errno));
		    fprintf(stderr,"accept error:%s\n",strerror(errno));
			exit(1);
		}
		if ((pid = fork()) < 0) {
			//syslog(LOG_ERR, "ruptimed: fork error: %s",
			 // strerror(errno));
		    fprintf(stderr,"fork error:%s\n",strerror(errno));
			exit(1);
		} else if (pid == 0) {	/* child */
			/*
			 * The parent called daemonize ({Prog daemoninit}), so
			 * STDIN_FILENO, STDOUT_FILENO, and STDERR_FILENO
			 * are already open to /dev/null.  Thus, the call to
			 * close doesn't need to be protected by checks that
			 * clfd isn't already equal to one of these values.
			 */
			if (dup2(clfd, STDOUT_FILENO) != STDOUT_FILENO ||
			  dup2(clfd, STDERR_FILENO) != STDERR_FILENO) {
			//	syslog(LOG_ERR, "ruptimed: unexpected error");
		        fprintf(stderr,"ruptimed error\n");
				exit(1);
			}
			close(clfd);
			execl("/usr/bin/uptime", "uptime", (char *)0);
	//		syslog(LOG_ERR, "ruptimed: unexpected return from exec: %s",
	//		  strerror(errno));
		    fprintf(stderr,"exec error:%s\n",strerror(errno));
		} else {		/* parent */
			close(clfd);
	//		waitpid(pid, &status, 0);
		}
	}
}

int
main(int argc, char *argv[])
{
	struct addrinfo	*ailist, *aip;
	struct addrinfo	hint;
	int				sockfd, err, n;
	char			*host;

	if (argc != 1)
		err_quit("usage: ruptimed");
	if ((n = sysconf(_SC_HOST_NAME_MAX)) < 0)
		n = HOST_NAME_MAX;	/* best guess */
	if ((host = malloc(n)) == NULL)
		err_sys("malloc error");
	if (gethostname(host, n) < 0)
		err_sys("gethostname error");
//	daemonize("ruptimed");
	memset(&hint, 0, sizeof(hint));
	hint.ai_flags = AI_CANONNAME;
	hint.ai_socktype = SOCK_STREAM;
	hint.ai_canonname = NULL;
	hint.ai_addr = NULL;
	hint.ai_next = NULL;
	if ((err = getaddrinfo(host, "ruptime", &hint, &ailist)) != 0) {
//		syslog(LOG_ERR, "ruptimed: getaddrinfo error: %s",
//		  gai_strerror(err));
		fprintf(stderr,"getaddrinfo error:%s\n",strerror(errno));
		exit(1);
	}

	signal(SIGCHLD,sigchld);

	for (aip = ailist; aip != NULL; aip = aip->ai_next) {
		if ((sockfd = initserver(SOCK_STREAM, aip->ai_addr,
		  aip->ai_addrlen, QLEN)) >= 0) {
			serve(sockfd);
			exit(0);
		}
	}
	exit(1);
}
