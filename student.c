#include <stdio.h>/* for NULL */
#include <string.h>/* for  strtok() */
#include <ctype.h>/* for atoi() */
#include <errno.h>/* for perror() */
#include <assert.h>/* for assert() */

#include <netdb.h>/* for gethostbyname() and struct hostent */
#include <sys/types.h>/* for pid_t, socket.h */
#include <sys/param.h>/* for MAXHOSTNAMELEN */
#include <sys/socket.h>/* for AF_INET, etc. */
#include <netinet/in.h>/* for struct sockaddr_in */

#include <time.h>
#include <sys/time.h>/* for struct timeval */


/* this is in netinet/in.h; included here for reference only.
struct sockaddr_in {
shortsin_family;
u_shortsin_port;
structin_addr sin_addr;
charsin_zero[8];
};
*/

/***************************************************************************/
static char *RCSId="$Id: c-client.c,v 1.1 1997/01/19 20:34:49 calvert Exp $";
/***************************************************************************/

#define NMSIZE26
#define BUFSIZE256


#define IDNAME"W.H.Derek"
#define USERNUM 8888

#define SVR_ADDR"tao.ite.uconn.edu"/* server name */
#define SVR_PORT3300
/* Port # of lab 3 server */



/***************************************************************************/
/***************************************************************************/

void die(char *s)
{
perror(s);
exit(2);
}

char *getTime(void)
{
struct timeval myTime;
struct tm *myTimP;

gettimeofday(&myTime,(struct timezone *)NULL);
myTimP = localtime((time_t *)&myTime.tv_sec);
return asctime(myTimP);
}

/*
 * translate strings in "dotted quad-port" notation ("W.X.Y.Z-P") to
 * struct sockaddr_in
 * NOTE: ranges not checked on integers.  Result is correct only
 * if the quad is actually valid, i.e. 0 <= W,X,Y,Z < 256
 */

int StringToSockaddr(char *name, struct sockaddr_in *address)
{
int a,b,c,d,p;
char string[BUFSIZE];
register char *cp;

assert(name!=NULL);
assert(address!=NULL);

/* Copy the name string into a private buffer so we don't crash trying
 * to write into a constant string.
 */
if (strlen(name) > BUFSIZE-1)
return -1;
else
strcpy(string,name);

cp = string;

address->sin_family = AF_INET;

/* throw away leading blanks, since they make gethostbyname() choke.  */
while (cp[0]==' ' || cp[0]=='\t') cp++;

/* is the first character a digit?
 * If so, we assume "w.x.y.z-port"
 * If not, we assume "hostname-port" */
if (isdigit(cp[0])) {
if (sscanf(cp,"%d.%d.%d.%d-%d",&a,&b,&c,&d,&p) != 5)
return -2;

address->sin_addr.s_addr = htonl(a<<24 | b<<16 | c<<8 | d);
address->sin_port = htons(p);
} else { /* we dont have a digit first */
char *port;

/* find the '-' in string: format must be hostname-port*/
if ((port=strchr(cp,'-')) == NULL)
return -3;

/* split string in two... hostname\0port\0 and increment port past \0 */
*port++ = '\0';

/* look-up hostentry for the hostname */
{
struct hostent *destHostEntry;

/* find the hostEntry for string */
if ((destHostEntry=gethostbyname(cp))== NULL)
return -4;

/* copy the address from the hostEntry into our address */
bcopy(destHostEntry->h_addr_list[0],
&address->sin_addr.s_addr, destHostEntry->h_length);

} /* look-up the hostentry for hostname */

address->sin_port = htons(atoi(port));

} /* else (we have hostname-port) */

return 0;
}


/*
 * Convert a struct sockaddr_in into dotted.quad-port string notation.
 * String must point to a buffer of at least 22 characters.
 */
int SockaddrToString (char *string, struct sockaddr_in *ss)
{
int ip = ss->sin_addr.s_addr;
ip = ntohl(ip);
if (string==0x0)
return -1;
sprintf(string ,"%d.%d.%d.%d-%d", (int)(ip>>24)&0xff,
(int)(ip>>16)&0xff,
(int)(ip>>8)&0xff,
(int)ip&0xff, ntohs(ss->sin_port));
return 1;
}

int main(int argc, char **argv)
{

int mySocket;
struct sockaddr_in destAddr, myAddr;
int lineSize, myPort;
int sizeofmyAddr, sizeofdestAddr;
char inbuf[BUFSIZE], msgbuf[BUFSIZE], addrbuf[BUFSIZE], saddrbuf[BUFSIZE];

char hostName[MAXHOSTNAMELEN+1];

/***********************************************************
 * Create a socket to be the endpoint of the connection
 * to the server.  Set up the destination address information.
 ************************************************************/

if ((mySocket = socket(AF_INET,SOCK_STREAM,0)) < 0)
die("couldn't allocate socket");



/**************************************************************
 * Make the connection
 ****************************************************************/
sprintf(addrbuf, "%s-%d", SVR_ADDR, SVR_PORT);
StringToSockaddr (addrbuf, &destAddr);
if (connect(mySocket,(struct sockaddr *) &destAddr,sizeof(destAddr)) < 0)
die("failed to connect to server");

printf("connected to server at %s\n",getTime());

sizeofmyAddr = sizeof(myAddr);
if (getsockname(mySocket, (struct sockaddr *) &myAddr,&sizeofmyAddr)<0) {
printf("getsockname failed on mySocket!\n");
addrbuf[0] = (char) 0;
} else {
/* set up addrbuf */
SockaddrToString (addrbuf, &myAddr);
}

sizeofdestAddr = sizeof(destAddr);
if (getpeername(mySocket,(struct sockaddr *) &destAddr,&sizeofdestAddr)<0) {
printf("getpeername failed on mySocket!\n");
saddrbuf[0] = (char) 0;
} else {
SockaddrToString (saddrbuf, &destAddr);
}
sprintf(msgbuf,"EX0 %s %s %d %s\n", saddrbuf, addrbuf, USERNUM, IDNAME);

/*
 * your code goes here -- hint, use "send"
 */
/*----------------- insert code ---------------------------*/
/*
 * Get the reply, first the greeting, then the random number.
 */

/* get the greeting  -- hint -- use "recv"
 */
/*----------------- insert code ---------------------------*/
/* dont forget to get the random number */
/*----------------- insert code ---------------------------*/
/* parse out the servernum from the reply */
/*----------------- insert code ---------------------------*/
/* construct and send the client ack string*/
/*----------------- insert code ---------------------------*/
/* wait for reply */
/*----------------- insert code ---------------------------*/
/* now close the connection -- hint -- use close() */
/*----------------- insert code ---------------------------*/
return 0;
}

