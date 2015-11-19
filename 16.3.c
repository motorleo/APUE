#include "apue.h"
#include <netdb.h>
#include <errno.h>
#include <syslog.h>
#include <sys/socket.h>
#include <sys/select.h>

#include <fcntl.h>

int
set_cloexec(int fd)
{
	int		val;

	if ((val = fcntl(fd, F_GETFD, 0)) < 0)
		return(-1);

	val |= FD_CLOEXEC;		/* enable close-on-exec */

	return(fcntl(fd, F_SETFD, val));
}
#define BUFLEN	128
#define QLEN 10

#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX 256
#endif

extern int initserver(int, const struct sockaddr *, socklen_t, int);

	void
serve(fd_set *sockfdset,int maxfd,int index,int fdarray[])
{
	int		clfd;
	FILE	*fp;
	char	buf[BUFLEN];
	int		nready,listenfd;

	for (;;){
		fd_set rset=*sockfdset;
		if ((nready=select(maxfd+1,&rset,NULL,NULL,NULL))>0){
			fprintf(stderr,"nready : %d\n",nready);
			for (int i=0;i<index;++i){
				listenfd=fdarray[i];
				if (FD_ISSET(listenfd,&rset)){
					//set_cloexec(listenfd);
					if ((clfd = accept(listenfd,NULL,NULL)<0)){
						//syslog(LOG_ERR,"ruptime:accept error: %s",
						//		strerror(errno));
						fprintf(stderr,"%s\n",strerror(errno));
						exit(1);
					}
					fprintf(stderr,"accept success!\n");
					//set_cloexec(clfd);
					if ((fp = popen("/usr/bin/uptime","r"))==NULL) {
						sprintf(buf,"error: %s\n",strerror(errno));
						send(clfd,buf,strlen(buf),0);
					} else {
						fprintf(stderr,"popen success!\n");
						while (fgets(buf,BUFLEN,fp)!=NULL){
							send(clfd,buf,strlen(buf),0);
							fprintf(stderr,"send success : %s\n"
									,buf);
						}
						pclose(fp);
					}
					close(clfd);
				}
			}

		}
	}
	exit(0);
}

	int
main(int argc, char *argv[])
{
	struct addrinfo	*ailist, *aip;
	struct addrinfo	hint;
	int				sockfd, err, n;
	char			*host;

	int				maxfd=-1,index=0;
	int				fdarray[FD_SETSIZE];
	fd_set			sockfdset;

	if (argc != 1)
		err_quit("usage: ruptimed");
	if ((n = sysconf(_SC_HOST_NAME_MAX)) < 0)
		n = HOST_NAME_MAX;	/* best guess */
	if ((host = malloc(n)) == NULL)
		err_sys("malloc error");
	if (gethostname(host, n) < 0)
		err_sys("gethostname error");
	//daemonize("ruptimed");
	memset(&hint, 0, sizeof(hint));
	hint.ai_flags = AI_CANONNAME;
	hint.ai_socktype = SOCK_STREAM;
	hint.ai_canonname = NULL;
	hint.ai_addr = NULL;
	hint.ai_next = NULL;
	if ((err = getaddrinfo(host, "ruptime", &hint, &ailist)) != 0) {
		//syslog(LOG_ERR, "ruptimed: getaddrinfo error: %s",
		//		gai_strerror(err));
		fprintf(stderr,"%s\n",gai_strerror(err));
		exit(1);
	}

	FD_ZERO(&sockfdset);
	memset(&fdarray,0,sizeof(int));

	for (aip = ailist; aip != NULL; aip = aip->ai_next) {
		if ((sockfd = initserver(SOCK_STREAM, aip->ai_addr,
						aip->ai_addrlen, QLEN)) >= 0) {
			FD_SET(sockfd,&sockfdset);
			if (sockfd>maxfd)
				maxfd=sockfd;
			fdarray[index]=sockfd;
			++index;
			//serve(sockfd);
			//exit(0);
		}
	}
	if (maxfd>=0) serve(&sockfdset,maxfd,index,fdarray);
	exit(1);
}
