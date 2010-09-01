/*
 * xmodem-at91.c
 *
 * A simple program using xmodem/1kxmode upload file to at91rm9200 based board.
 * Created by (C) Copyright 2004
 * Linhang.Zhang, Jilin University of PR.China, linxing@jlu.edu.cn.
 *
 *************************************************************************************
 *
 * Modified 01-Feb-2005 (C)Copyright 2005
 * Marco Cavallini, www.KoanSoftware.com - ITALY, m.cavallini@koansoftware.com
 * - edited indentations and changed break usage in switch statement.
 * - added "\r" to printf
 *
 * - build with 
 *   gcc sx-at91.c -o sx-at91
 *
 * - Howto use this program with minicom/xminicom and AT91 
 *   start minicom or xminicom
 *   edit Options / File transfer protocol, 
 *   add a name (for example J) like the following example
 *
 *   |     Name             Program                 Name U/D FullScr IO-Red. Multi  |
 *   | A  zmodem     /usr/bin/sz -vv -b              Y    U    N       Y       Y    |
 *   | B  ymodem     /usr/bin/sb -vv                 Y    U    N       Y       Y    |
 *   | C  xmodem     /usr/bin/sx -vv                 Y    U    N       Y       N    |
 *   | D  zmodem     /usr/bin/rz -vv -b -E           N    D    N       Y       Y    |
 *   | E  ymodem     /usr/bin/rb -vv                 N    D    N       Y       Y    |
 *   | F  xmodem     /usr/bin/rx -vv                 Y    D    N       Y       N    |
 *   | G  kermit     /usr/bin/kermit -i -l %l -s     Y    U    Y       N       N    |
 *   | H  kermit     /usr/bin/kermit -i -l %l -r     N    D    Y       N       N    |
 *   | I  ascii      /usr/bin/ascii-xfr -dsv         Y    U    N       Y       N    |
 *   | J  at91       /home/koan/xmodem/xs-at91       Y    U    Y       N       N    |
 *   | K    -                                                                       |
 *   | L    -                                                                       |
 *
 *   save and use it selecting at91 protocol when you start an Xmodem upload to AT91
 *
 *************************************************************************************
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include     <stdio.h>
#include     <stdlib.h>
#include     <string.h>
#include     <unistd.h>
#include     <sys/types.h>
#include     <sys/stat.h>
#include     <fcntl.h>
#include     <termios.h>
#include     <errno.h>
#include     <time.h>

#define	TRUE		1
#define	FALSE		0
#define LINESIZE	1024

/*********/

#define SERIAL_DEVICE "/dev/ttyS0"
#define MYBAUDRATE B115200

/***************SUB PROGRAM*******/

int Initial_SerialPort(void)
{
    int fd;

    struct termios options;

    fd = open(SERIAL_DEVICE, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1) {
        /*
         * open error!
         */
        perror("Can't open serial port!");
        return -1;
    }

    /*
     * Get the current options for the port...
     */
    tcgetattr(fd, &options);

    /*
     * Set the baud rates to BAUDRATE...
     */
    cfsetispeed(&options, MYBAUDRATE);
    cfsetospeed(&options, MYBAUDRATE);
    tcsetattr(fd, TCSANOW, &options);
    if (0 != tcgetattr(fd, &options)) {
        perror("SetupSerial 1");
        return -1;
    }

    /*
     * 8bit Data,no partity,1 stop bit...
     */
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;
    tcflush(fd, TCIFLUSH);

        /***Choosing Raw Input*/
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    options.c_oflag &= ~OPOST;

    /*
     * Set the new options for the port...
     */
    if (0 != tcsetattr(fd, TCSANOW, &options)) {
        perror("SetupSerial error");
        return -1;
    }

    return fd;
}

/******************************/
void ClearReceiveBuffer(int fd)
{
    unsigned char tmp;

    while ((read(fd, &tmp, 1)) > 0) ;

    return;
}

unsigned char filebuf[LINESIZE + 2];

unsigned char outbuf[LINESIZE + 2];

FILE *datafile;

int fd;

static unsigned int ChCnt = 0;

static unsigned int ChIx;

unsigned char GetChar(unsigned char *ch)
/* 
 * SUCCESS:	Return TRUE
 * FAILURE:	Return FALSE
 */
{

    if (ChCnt == 0) {
        ChCnt = fread(filebuf, sizeof (char), LINESIZE, datafile);
        ChIx = 0;
    }
    if (ChCnt > 0) {
        *ch = filebuf[ChIx++];
        ChCnt--;
        return TRUE;
    } else {
        return FALSE;           /* Reached End of File */
    }
}

/********************************/
void delay()
{
}

int main(int argc, char *argv[])
{
    char *data_file_name;

    int len;

    unsigned char c;

    int complete, i, sts;

    printf("raw-at91 started...\r\n");

    /*
     * open serial port1 
     */
    if ((fd = Initial_SerialPort()) == -1)
        return -1;

    data_file_name = argv[1];

    if ((datafile = fopen(data_file_name, "rb")) == NULL) {
        perror("Can't open file!");
        return -1;
    }

        /*******************************/

    complete = 0;
    /*
     * ClearReceiveBuffer(fd); 
     */

    /*
     * while((read(fd,&ack_id,1))<=0);
     */

    /*
     * printf("%c\r\n",ack_id); 
     */
    while (!complete) {
        for (i = 0; i < LINESIZE; i++) {        /* A line more than 1024 characters will have problems... */
            if ((sts = GetChar(&outbuf[i]))) {
                /*
                 * Sts = Success 
                 */
                if ((c = outbuf[i]) == '\n') {  /* Found end of Line - Start Processing */
                    outbuf[i + 1] = '\0';       /* Terminate String */
                    break;
                }
            } else {
                /*
                 * Sts = Failure - End of File 
                 */
                outbuf[i] = '\n';
                outbuf[i + 1] = '\0';
                complete = 1;
            }
        }
        printf("%s", outbuf);   /* Inform user */
        len = strlen((char *)outbuf);
        write(fd, outbuf, strlen((char *)outbuf));
        for (i = 0; i < 500000000; i++)
            delay();
        while ((read(fd, &c, 1)) <= 0)
            putchar(c);
        printf("  ");
    }
    fclose(datafile);
    close(fd);
    return 0;
}
