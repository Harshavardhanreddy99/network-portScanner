#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
void check_arguments(int arg_count, char** arg_values);
void port_scan_tcp(char* host_name, int port_low, int port_high);
void port_scan_udp(char* host_name, int port_low, int port_high);

int main(int arg_count, char** arg_values)
{ 
	check_arguments(arg_count, arg_values);

		
	/* host_name, protocol, lower range, and upper range */
     char* host_name = arg_values[1];
	 char* protocol = arg_values[2];
	 int port_low = atoi(arg_values[3]);
	 int port_high = atoi(arg_values[4]);


	if (!strcmp(protocol, "tcp"))  /*tcp port*/
	{
		port_scan_tcp(host_name, port_low, port_high);
	}
	else if (!strcmp(protocol, "udp")) /*udp port*/
	{
	       	port_scan_udp(host_name, port_low, port_high);
       	}

	return 0;
}


/* Validation of input arguments */
void check_arguments(int arg_count, char** arg_values)
{
/* Validating hostname */
	if (gethostbyname(arg_values[1]) == NULL)
	{
		printf("ERROR: host %s does'nt not exist\n", arg_values[1]);
		exit(EXIT_FAILURE);
	}
/* Validate the number of input arguments */
	if (arg_count != 5)
	{
		printf("Input arguments: ./portScan <hostname> <protocol> <portlow> <porthigh>\n");
		exit(EXIT_FAILURE);
       	}
	else
	{
		printf("SCANNING=%s, PROTOCOL=%s, PORTS_LOW:%s ----->PORTS_HIGH:%s\n",arg_values[1], arg_values[2], arg_values[3], arg_values[4]);
       	}

}


/* TCPportScanner */
void port_scan_tcp(char* host_name, int port_low, int port_high)
{
	int send_fd;     /* Socket file descripter */
	int p;    
	struct hostent*     host;
	struct sockaddr_in  sock_addr; 
	struct servent*     serv_port;
	struct in_addr **addr_list;
/* Resolve hostname to IP address */
	host=gethostbyname(host_name);
	if (host == NULL)
       	{
		printf("usage: ./portScan <hostname> <protocol> <portlow> <porthigh>\n");
		printf("error: host %s not exist\n", host_name);
		exit(EXIT_FAILURE);
	}
	if(host->h_addrtype !=AF_INET)
	{
		fprintf(stderr,"NOT a IP HOST \n");
		exit(EXIT_FAILURE);
	}
	addr_list = (struct in_addr **)host->h_addr_list;

/* port scan loop */
	for (p = port_low; p <= port_high; p++)
	{
		/* socket */
		if ((send_fd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
		{
			perror("failed to open stream socket.\n");
			exit(EXIT_FAILURE);
		}
/* socket address */
		memset(&sock_addr, 0, sizeof(sock_addr));
		sock_addr.sin_family = AF_INET;
		sock_addr.sin_port = htons(p);
		sock_addr.sin_addr =*((struct in_addr*)host->h_addr);

/* Connect using that socket and sockaddr structure */
		int rval =connect(send_fd, (struct sockaddr*) &sock_addr,sizeof(sock_addr));
		{
			printf("port\t %d\t",p);
			if(rval<0)
			{
				printf("closed\t");
			}
			else
			{
			       	printf("open\t");
			}
			serv_port=getservbyport(htons(p),"udp");
			if(serv_port ==NULL)
			{
				printf("svc name unavail \n");
			}
			else
			{
				printf("%s\n",serv_port->s_name);
			}
			printf("\n");
			
			close(send_fd);
		}
	
	}
}

/* UDP port scanner */
void port_scan_udp(char* host_name, int port_low, int port_high)
{
    int send_fd;
    int p; 
    struct hostent *host; 
    struct sockaddr_in  sock_addr; 
    struct servent *serv_port; 
    struct timeval timeout;

    /* hostname to IP address */
    if ((host = gethostbyname(host_name)) == NULL)
    {
        printf(": ./portScan <hostname> <protocol> <portlow> <porthigh>\n");
        printf("error: host %s not exist\n", host_name);
        exit(EXIT_FAILURE);
    }
    for (p = port_low; p <= port_high; p++)
    {
        if ((send_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
        {
            perror("fail to open send datagram socket.\n");
            exit(EXIT_FAILURE);
        }

        /* filling the socket address */
        memset(&sock_addr, 0, sizeof(sock_addr));
        sock_addr.sin_family = AF_INET;
        sock_addr.sin_port = htons(p);
        sock_addr.sin_addr = *((struct in_addr*)host->h_addr);
	//int rval =connect(send_fd, (struct sockaddr*) &sock_addr,sizeof(sock_addr));
	
	/* sendto function in UDP */
        int rval=sendto(send_fd,(const char*)"HELLO",strlen("HELLO"),MSG_CONFIRM,(const struct sockaddr*) &sock_addr, sizeof(struct sockaddr_in));
       	{
	printf("port\t %d \t",p);
        if(rval<0)
        {
                printf("closed\t");
        }
        else
        {
                printf("open\t");
        }
	serv_port=getservbyport(htons(p),"udp");
	if(serv_port ==NULL)
	{
		printf("svc name unavail \n");
	}
	else
	{
		printf("%s\n",serv_port->s_name);
	}

        printf("\n");


        close(send_fd);
     }
    }
}


