/*
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "tddlight.h"

#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <unistd.h>


// COM PORT file descriptor
int COM_FD = 0;


/* Configure serial port with
 *
 * 4800 baud
 * 8 bit data
 * No parity
 * Non blocking reading
 * Special lines ignore
 * No control Terminal
 * Read enable
 * RAW input/output
 */
void serial_init(char* port)
{
    if (COM_FD > 0)
    {
        return;
    }

    // Open serial port file
    int fd = open(port, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd < 0)
    {
        COM_FD = -1;
        printf("Hardware not found in %s\n", port);
        printf("\nMaybe you don't have permissions to use it?");
        printf("\nTry running it as root or adding yourself to the group that owns %s", port);
        exit(1);
    }

    // Configure serial port
    struct termios config;
    if (tcgetattr(fd, &config) != 0)
    {
        COM_FD = -1;
        printf("Error while configing serial port");
        exit(1);
    }

    cfsetispeed(&config, B4800);
    cfsetospeed(&config, B4800);

    config.c_cflag |= (CLOCAL | CREAD | CS8);
    config.c_cflag &= ~(PARENB | PARODD);
    config.c_iflag = 0;
    config.c_oflag = 0;
    config.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    config.c_cc[VTIME] = 5;
    config.c_cc[VMIN] = 0;

    if (tcsetattr(fd, TCSANOW, &config) != 0)
    {
        COM_FD = -1;
        printf("Error while configing serial port");
        exit(1);
    }

    COM_FD = fd;
}

void print_usage()
{
    printf("tddlight [command] <serial_file>\n\n");
    printf("Available Commands:\n");
    printf("   r\tOutput red light\n");
    printf("   y\tOutput yellow light\n");
    printf("   g\tOutput green light\n");
    printf("   c\tClear output\n");
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        print_usage();
        exit(1);
    }

    if (argc == 3)
    {
        serial_init(argv[2]);
    }
    else
    {
        serial_init(COMPORT);
    }

    switch (argv[1][0])
    {
        case 'r':
            write(COM_FD, "r", 1);
            break;

        case 'y':
            write(COM_FD, "y", 1);
            break;

        case 'g':
            write(COM_FD, "g", 1);
            break;

        case 'c':
            write(COM_FD, "c", 1);
            break;

        default:
            print_usage();
            exit(1);
            break;
    }

    close(COM_FD);
    return 0;
}
