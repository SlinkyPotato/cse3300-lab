#include <stdlib.h> // fixes built-in error warnings
#include <unistd.h>
#include <stdio.h>  /* for NULL */
#include <string.h>  /* for  strtok() */
#include <ctype.h>  /* for atoi() */
#include <errno.h>  /* for perror() */
#include <assert.h>  /* for assert() */

#include <netdb.h>  /* for gethostbyname() and struct hostent */
#include <sys/types.h>  /* for pid_t, socket.h */
#include <sys/param.h>  /* for MAXHOSTNAMELEN */
#include <sys/socket.h>  /* for AF_INET, etc. */
#include <netinet/in.h>  /* for struct sockaddr_in */

#include <time.h>
#include <sys/time.h>  /* for struct timeval */


/* this is in netinet/in.h; included here for reference only.
struct sockaddr_in {
  short sin_family;
  u_short sin_port;
  struct  in_addr sin_addr;
  char  sin_zero[8];
};
*/

/***************************************************************************/
static char *RCSId = "$Id: c-client.c,v 1.1 1997/01/19 20:34:49 calvert Exp $";
/***************************************************************************/

#define NMSIZE    26
#define BUFSIZE    256


#define IDNAME  "B..Patino"
#define USERNUM 3462

#define SVR_ADDR  "tao.ite.uconn.edu"  /* server name */
#define SVR_PORT  3300
#define SVR_ALTPORT  3301
/* Port # of lab 3 server */
#define LCL_ADDR "localhost"

/***************************************************************************/
/***************************************************************************/

void die(char *s) {
  perror(s);
  exit(2);
}

char *getTime(void) {
  struct timeval myTime;
  struct tm *myTimP;

  gettimeofday(&myTime, (struct timezone *) NULL);
  myTimP = localtime((time_t *) &myTime.tv_sec);
  return asctime(myTimP);
}

/*
 * translate strings in "dotted quad-port" notation ("W.X.Y.Z-P") to
 * struct sockaddr_in
 * NOTE: ranges not checked on integers.  Result is correct only
 * if the quad is actually valid, i.e. 0 <= W,X,Y,Z < 256
 */

int StringToSockaddr(char *name, struct sockaddr_in *address) {
  int a, b, c, d, p;
  char string[BUFSIZE];
  register char *cp;

  assert(name != NULL);
  assert(address != NULL);

/* Copy the name string into a private buffer so we don't crash trying
 * to write into a constant string.
 */
  if (strlen(name) > BUFSIZE - 1)
    return -1;
  else
    strcpy(string, name);

  cp = string;

  address->sin_family = AF_INET;

  /* throw away leading blanks, since they make gethostbyname() choke.  */
  while (cp[0] == ' ' || cp[0] == '\t') cp++;

  /* is the first character a digit?
   * If so, we assume "w.x.y.z-port"
   * If not, we assume "hostname-port" */
  if (isdigit(cp[0])) {
    if (sscanf(cp, "%d.%d.%d.%d-%d", &a, &b, &c, &d, &p) != 5) return -2;

    address->sin_addr.s_addr = htonl(a << 24 | b << 16 | c << 8 | d);
    address->sin_port = htons(p);
  } else {    /* we dont have a digit first */
    char *port;

    /* find the '-' in string: format must be hostname-port*/
    if ((port = strchr(cp, '-')) == NULL)
      return -3;

    /* split string in two... hostname\0port\0 and increment port past \0 */
    *port++ = '\0';

    /* look-up hostentry for the hostname */
    {
      struct hostent *destHostEntry;

      /* find the hostEntry for string */
      if ((destHostEntry = gethostbyname(cp)) == NULL)
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
int SockaddrToString(char *string, struct sockaddr_in *ss) {
  int ip = ss->sin_addr.s_addr;
  ip = ntohl(ip);
  if (string == 0x0)
    return -1;
  sprintf(string, "%d.%d.%d.%d-%d", (int) (ip >> 24) & 0xff,
          (int) (ip >> 16) & 0xff,
          (int) (ip >> 8) & 0xff,
          (int) ip & 0xff, ntohs(ss->sin_port));
  return 1;
}

/*
 * Obtain the value after the specified token from string
 */
char* nextTokenFromString(char* words, char* token) {
  char* foundWord; // pointer to store the found word
  char* word = strtok(words, " "); // get the first word before the specified split
  int isNextToken = 0; // true if the specified token is found
  while (word != NULL) { // keep looping until all tokens after split have been processed
    if (isNextToken == 1) { // if the token was found before the current iteration
      foundWord = word; // the next token after the specified token is obtained
      isNextToken = 0; // set the counter to zero
      break; // break out earlier for faster processing
    }
    if (strcmp(token, word) == 0) isNextToken = 1; // set the flag to true if the current token matches specified token
    word = strtok(NULL, " "); // continue to the next token
  }
  return foundWord; // return either NULL or the found token
}

int main(int argc, char **argv) {

  int mySocket, psock, newsock;
  struct sockaddr_in destAddr, myAddr, freeAddr;
  int lineSize, myPort;
  int sizeofmyAddr, sizeofdestAddr, sizeoffreeAddr;
  char inbuf[BUFSIZE], msgbuf[BUFSIZE], addrbuf[BUFSIZE], saddrbuf[BUFSIZE], freeAddrbuf[BUFSIZE];
  char servernumBuf[BUFSIZE]; // initial server nubmer response
  char recServernum[BUFSIZE]; // after ack response servernum+1

  char hostName[MAXHOSTNAMELEN + 1]; // Not used...

  /***********************************************************
   * Create a socket to be the endpoint of the connection
   * to the server.  Set up the destination address information.
   ************************************************************/

  // i
  if ((mySocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) die("couldn't allocate socket"); // exercise 0 socket
  if ((psock = socket(AF_INET, SOCK_STREAM, 0)) < 0) die ("couldn't allocate socket"); // exercise 1 socket

  /**************************************************************
   * Make the connection
   ****************************************************************/
  
  // ii
  sprintf(addrbuf, "%s-%d", SVR_ADDR, SVR_PORT);
  StringToSockaddr(addrbuf, &destAddr);

  // iii
  if (connect(mySocket, (struct sockaddr *) &destAddr, sizeof(destAddr)) < 0) die("failed to connect to server");
  printf("connected to server at %s\n", getTime());

  // iv
  sizeofmyAddr = sizeof(myAddr);
  if (getsockname(mySocket, (struct sockaddr *) &myAddr, &sizeofmyAddr) < 0) {
    printf("error: getsockname failed on mySocket!\n");
    addrbuf[0] = (char) 0;
  } else {
    SockaddrToString(addrbuf, &myAddr);
  }

  sizeofdestAddr = sizeof(destAddr);
  if (getpeername(mySocket, (struct sockaddr *) &destAddr, &sizeofdestAddr) < 0) {
    printf("error: getpeername failed on mySocket!\n");
    saddrbuf[0] = (char) 0;
  } else {
    SockaddrToString(saddrbuf, &destAddr);
  }

  /*
   * Bind free port 
   */

  /* Set up free port */
  freeAddr.sin_family = AF_INET;
  freeAddr.sin_addr.s_addr = INADDR_ANY;
  freeAddr.sin_port = htons(0);

  // Bind the free port number
  if (bind(psock, (struct sockaddr*) &freeAddr, sizeof(freeAddr)) < 0) {
    close(psock);
    close(mySocket);
    printf("error: bind failed\n");
    exit(1);
  } 

  // Get binded sock address
  sizeoffreeAddr = sizeof(freeAddr);
  if (getsockname(psock, (struct sockaddr *) &freeAddr, &sizeoffreeAddr) < 0) {
    printf("getsockname failed on psock\n");
    freeAddrbuf[0] = (char) 0;
  } else {
    SockaddrToString(freeAddrbuf, &freeAddr);
    printf("Binded port: %s\n", freeAddrbuf);
  }

  // call listen
  if (listen(psock, 5) < 0) {
    close(psock);
    close(mySocket);
    die("error: failed to listen to psock");
  }

  // Generate request string (different addrbuf socket for exercise 1)
  sprintf(msgbuf, "ex1 %s %s %d %s\n", saddrbuf, freeAddrbuf, USERNUM, IDNAME);

/*
 * Get the reply, first the greeting, then the random number.
 */
  int sendResult = send(mySocket, msgbuf, sizeof(msgbuf), 0);
  if (sendResult < 0) {
    close(mySocket);
    close(psock);
    die("error: failed to send to socket");
  }

  /* get the greeting  -- hint -- use "recv" */

  int receiveResult = recv(mySocket, inbuf, sizeof(inbuf), 0);
  if (receiveResult < 0) {
    close(psock);
    close(mySocket);
    die("error: failed to receive from socket");
  }
  inbuf[receiveResult] = '\0'; // terminate string

  // Check if OK exists
  if (strstr(inbuf, "OK") == NULL) {
    close(psock);
    close(mySocket);
    printf("errror: Not OK\n%s\n", inbuf);
    exit(1);
  }

  /*// Check usernum+1
  char recUsernum[BUFSIZE];
  sprintf(recUsernum, "%d", (USERNUM + 1));
  if (strstr(inbuf, recUsernum) == NULL) {
    printf("error: Missing usernum+1\n%s\n", inbuf);
    die("");
  }
*/
  // display the server response on connection
  printf("\n---- Server response on connection ----\n%s\n", inbuf);

  /* dont forget to get the random number */

  // split string by white space
  char* obtained = nextTokenFromString(inbuf, IDNAME);

  // set servernum (random number)
  strcpy(servernumBuf, obtained);
  printf("Random Number: %s\n", servernumBuf);

  /* parse out the servernum from the reply */
  // Convert servernum to int
  int servernum = strtol(servernumBuf, (char **)NULL, 10);
  
  // call accept()
  newsock = accept(psock, (struct sockaddr *) &freeAddr, &sizeoffreeAddr);
  if (newsock < 0) {
    close(psock);
    close(mySocket);
    printf("error: accept failed\n");
    exit(1);
  }

  // call recv on newsock to get new random number from server or until it returns zero
  int psockRecv = recv(newsock, inbuf, sizeof(inbuf), 0);
  if (psockRecv < 0) {
    close(psock);
    close(mySocket);
    printf("error: receiving packets\n");
    exit(1);
  }
  inbuf[psockRecv] = '\0'; // terminal string

  // Verify random number has been received

  /* construct and send the client ack string*/
  /*// Construct ACK
  sprintf(msgbuf, "ex0 %d %d \n", USERNUM+2, servernum+1);

  // Send ACK
  int ackResult = send(mySocket, msgbuf, sizeof(msgbuf), 0);
  if (ackResult < 0) die("error: failed to send ACK to socket");*/

  /*// Check receive result
  int ackReceiveResult = recv(mySocket, inbuf, sizeof(inbuf), 0);
  if (ackReceiveResult < 0) die("error: failed to receive from socket");
  inbuf[ackReceiveResult] = '\0'; // terminate string

  // Verify that OK was received
  if (strstr(inbuf, "OK") == NULL) {
    printf("error: Not OK\n%s\n", inbuf);
    die("");
  }

  // display the received ACK response
  printf("Received ACK: %s\n", inbuf);
  
  // Check servernum+1
  obtained = nextTokenFromString(inbuf, "OK");
  strcpy(recServernum, obtained);
  printf("Received servernum+1: %s", recServernum);*/

  /* now close the connection -- hint -- use close() */

  // all values needed should have been saved, close the connection
  close(psock);
  close(mySocket);
  return 0;
}