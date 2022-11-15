#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "skel.h"
char *program_name;

void error( int status, int err, char *fmt, ... ){
    va_list ap;
    va_start(ap, fmt );
    fprintf( stderr, "%s: ", program_name );
    vfprintf( stderr, fmt, ap );
    va_end(ap);

    if(err)
        fprintf(stderr, ": %s (%d)\n", strerror(err), err);
    if(status)
        EXIT(status);
}

static void set_addres(char *hname, char *sname, struct sockaddr_in *sap, char * protocol){
    struct servent *sp;
    struct hostent *hp; 
    char *endptr;
    short port;
    bzero(sap, sizeof( *sap ) ); 
    sap->sin_family = AF_INET;
    if(hname != NULL){
        if(!inet_aton(hname, &sap ->sin_addr)){
            hp = gethostbyname( hname );
            if(hp == NULL)
                error(1, 0, "неизвестный хост: %s\n", hname);
            sap -> sin_addr = *(struct in_addr *)hp ->h_addr;
        }
    }
    else
    sap->sin_addr.s_addr = htonl( INADDR_ANY );
    port = strtol ( sname, &endptr, 0 );
    if(*endptr== '\0')
        sap->sin_port = htons( port );
    else{
        sp = getservbyname( sname, protocol );
        if ( sp == NULL )
            error(1, 0, "неизвестный сервис: %s\n", sname);
        sap->sin_port = sp->s_port;
    }
}

static void client( SOCKET s, struct sockaddr_in *peerp ){

}

int main(int argc, char **argv){
    struct sockaddr_in peer;
    SOCKET s;
    INIT();
    set_addres( argv[ 1 ], argv[ 2 ], &peer, "tcp" );
    s = socket( AF_INET, SOCK_STREAM, 0 );
    if(!isvalidsock(s ))
        error ( 1, errno, "ошибка вызова socket" );
    
    if ( connect( s, ( struct sockaddr* )&peer, sizeof( peer ) ) )
        error( 1, errno, "ошибка вызова connect" );

    client( s, &peer );
    EXIT(0);
}