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
 *
 * Puts Serial Descriptor in COM_FD, 0 if fail
 */
int serial_init(void)
{
    if (COM_FD > 0)
    {
        return 0;
    }

    // Open serial port file
    int fd = open(COMPORT, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd < 0)
    {
        COM_FD = -1;
        return 0;
    }

    // Configure serial port
    struct termios config;
    if (tcgetattr(fd, &config) != 0)
    {
        COM_FD = -1;
        return 0;
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
        return 0;
    }

    COM_FD = fd;
    return 1;
}

int main(void)
{
    return 0;
}
