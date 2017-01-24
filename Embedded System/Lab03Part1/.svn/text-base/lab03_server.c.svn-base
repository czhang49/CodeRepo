//
// CS 431 - Lab 03 Server Skeleton
// PC/Linux (Provided)
//

#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include "pc_crc16.h"
#include "lab03.h"

int main(int argc, char* argv[])
{
	double troll_pct=0;		// Perturbation % for the troll (if needed)
	int ofd,i,troll=0;	// Input and Output file descriptors (serial/troll)
	char str[MSG_BYTES_MSG],opt;	// String input
	struct termios oldtio, tio;	// Serial configuration parameters
	int VERBOSE = 0;		// Verbose output - can be overriden with -v
	int ack=0;
	// Command line options
	while ((opt = getopt(argc, argv, "t:v")) != -1) {
		switch (opt) {
			case 't':	troll = 1; 
					troll_pct = atof(optarg);
					break;
			case 'v':	VERBOSE = 1; break;
			default: 	break;
		}
	}

	printf("CS431 - Lab 03 Server\n(Enter a message to send.  Type \"quit\" to exit)\n");


	//
	// WRITE ME: Open the serial port (/dev/ttyS0) read-write
	//

	FILE * ifd = fopen("/dev/ttyS0", "rw+" );

	if (ifd == 0) { printf("check 1\n"); perror("/dev/ttyS0"); exit(-1); }

	// Start the troll if necessary
	if (troll)
	{
		// Open troll process (lab03_troll) for output only
		FILE * pfile;		// Process FILE for troll (used locally only)
		char cmd[128];		// Shell command

		snprintf(cmd, 128, "./lab03_troll -p%f %s", troll_pct, (VERBOSE) ? "-v" : "");

		pfile = popen(cmd, "w");
		if (!pfile) { perror("lab03_troll"); exit(-1); }
		ofd = fileno(pfile);
	}
	else ofd = fileno(ifd);		// Use the serial port for both input and output
	
//printf("check 2\n");

	//
 	// WRITE ME: Set up the serial port parameters and data format
	//
	
	tcgetattr(fileno(ifd), &oldtio);
	tio.c_cflag 	= B9600 | CS8 | CLOCAL;
	tio.c_iflag 	= CREAD;
	tio.c_oflag 	= 0;
	tio.c_lflag 	= 0;
	tcflush(fileno(ifd), TCIFLUSH);
	tcsetattr(fileno(ifd), TCSANOW, &tio);


	while(1)
	{

		//
		// WRITE ME: Read a line of input (Hint: use fgetc(stdin) to read each character)
		//
		//char inLine[MSG_BYTES_MSG];
		int lineIdx = 0;
		for(lineIdx=0; lineIdx<MSG_BYTES_MSG; lineIdx++){
			str[lineIdx] = '\0';
		}
		lineIdx = 0;
		while(lineIdx<MSG_BYTES_MSG){
			str[lineIdx] = getc(stdin);
			if(str[lineIdx]=='\n'||str[lineIdx]=='\r'/*||str[lineIdx]=='\0'*/) // newline or EOF
				break;
			lineIdx++;
		}
		if(lineIdx>=MSG_BYTES_MSG)
			printf("Message length exceeded!\n");

		//printf("string = %s", str);
		if (strcmp(str, "quit\n") == 0||strcmp(str, "quit\r") == 0) break;

		//
		// WRITE ME: Compute crc (only lowest 16 bits are returned)
		//
		int crc16 = pc_crc16(str, lineIdx);
		int attempts=0;
		ack = 0;
		char a = 0;
		while (!ack)
		{
			printf("Sending (attempt %d)...\n", ++attempts);

			//printf("ifd = %d\n", ifd);
			// 
			// WRITE ME: Send message
			//

			write(ofd,&a, 1);

			a = crc16>>8;
			write(ofd,&a, 1);



			a = crc16&0xFF;
			write(ofd,&a, 1);



			a = MSG_BYTES_MSG_LEN;
			write(ofd,&a, 1);



			i=0;
			while(i<strlen(str)){
				a = str[i];
				write(ofd,&a, 1);
				i++;

			}

			printf("Message sent, waiting for ... ");

			
			//
			// WRITE ME: Wait for MSG_ACK or MSG_NACK
			//

			read(fileno(ifd),&ack, 1);


			printf("%s\n", ack ? "ACK" : "NACK, resending");

			
		}
		printf("\n");

	
	}



	//
	// WRITE ME: Reset the serial port parameters
	//

	tcflush(fileno(ifd), TCIFLUSH);
	tcsetattr(fileno(ifd), TCSANOW, &tio);

	
	// Close the serial port
	close(fileno(ifd));
	
	return 0;
}
