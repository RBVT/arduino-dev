#include <stdio.h>                                                    // объявления ввода/вывода.
#include <string.h>                                                   // объявления строковых функций.
#include <unistd.h>                                                   // объявления функций UNIX.
#include <fcntl.h>                                                    // объявления управления файлами.
#include <errno.h>                                                    // объявления кодов ошибок.
#include <termios.h>                                                  // объявления управления POSIX-терминалом.
#include <sys/types.h>
#include <sys/stat.h>
 
//---------------------------------------------------------------------------------------------------------------------------------------
 
int fd;                                                              // file дескриптор для serialport.
char buf[512];                                                       // buf зависит от размера строки принимаемых данных.
int outa=0; 
int iIn;
 
int open_port(void);

//----------------------------------------------------------------------------------------------------------------------------------------

int main(void)

{ 
port_set:

         fd = open("/dev/ttyUSB2", O_RDWR | O_NOCTTY | O_NDELAY);     // 'open_port()' - открывает serial port.

//---------------------------------------------------------------------------------------------------------------------------------------
 
if
         (fd == -1)

//----------------------------------------------------ERROR-------------------------------------------------------------------------------

{
         printf("error port\n");
         perror("open_port: Unable to open /dev/ttyUSBn - ");
}

//----------------------------------------------------------------------------------------------------------------------------------------

else

//--------------------------------------------------OPTIONS-----------------------------------------------------------------------------
       
{
         struct termios options;                                     // структура для установки port.
         tcgetattr(fd, &options);                                    // чтение параметров port.
        
         cfsetispeed(&options, B115200);                             // установка input baudrate.
         cfsetospeed(&options, B115200);                             // установка output baudrate.
         
         options.c_cflag &= ~PARENB;                                 // выкл проверка четности.
         options.c_cflag &= ~CSTOPB;                                 // выкл 2-х stopbit,вкл 1 stopbit.
         options.c_cflag &= ~CSIZE;                                  // выкл bit mask.
         options.c_cflag |= CS8;                                     // вкл 8bit.
         tcsetattr(fd, TCSANOW, &options);                           // сохранение параметров порта.
        
}

//--------------------------------------------------OUTPUT--------------------------------------------------------------------------------

read_port:

        iIn=read(fd,buf,8);                                                // чтения входящих данных из порта.

        printf("%s",buf);

//---------------------------------------------------------

goto read_port;                                                      // прыжок на функцию 'read_port'.
 
//--------------------------------------------------------     
    
        printf("stop1\n");
}
