# network-portScanner
This network port scanner is developed in C that will report the status of services and their associated ports for the TCP and UDP protocols for a given port range. 

Port scanner shall be invoked as follows:

     portScan <hostname> <protocol> <portlow> <porthigh>

where
• <hostname> is the host name of the machine you want to run the port scanner on.
• <protocol>istheprotocol,limitedto"TCP"or"UDP".
• <portlow>isthelowerrange,inclusively,ofportstoscan.
• <porthigh>istheupperrange,inclusively,ofportstoscan.
  
The basic idea behind a network port scanner is simple: given a host name of a machine and a list of ports to scan, the scanner will connect to each port using sockets with the specified protocol (i.e., TCP or UDP) to determine whether or not the port is open based on the success of a connection request and then close the socket before moving on to the next port to scan. Especially for TCP, you will not allow for “half-open” scans (i.e., connection requests without a corresponding close) as it can lead to network failures and availability issues. Where available, you will include the name of the service that is likely running on that port. 

Visit https://www.iana.org/assignments/port-numbers for information about the services and transport protocol associated with each of the ports. If no service is available or you are unable to determine the service for open ports, you will simply display "svc name unavail".

The program shall also adhere to the following requirements:
• If the user does not enter all required command-line arguments, you will display a usage statement and terminate the program. You may assume the user enters the correct data type (e.g., string or integer), but you should check for errors and handle accordingly as appropriate.
• Your program should run on the INET domain using SOCK_STREAM and SOCK_DGRAM for TCP and UDP sockets, respectively so that the port scanner can operate over the network on a remote machine.
