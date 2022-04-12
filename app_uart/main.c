
#include<stdio.h>      /*标准输入输出定义*/    
#include<stdlib.h>     /*标准函数库定义*/    
#include<unistd.h>     /*Unix 标准函数定义*/    
#include<sys/types.h>     
#include<sys/stat.h>       
#include<fcntl.h>      /*文件控制定义*/    
#include<termios.h>    /*PPSIX 终端控制定义*/    
#include<errno.h>      /*错误号定义*/    
#include<string.h>
#include "uart.h"

int ctrl_led(int fd, char *msg)
{
	if (0 == strcmp(msg, "exit") || strlen(msg) > 3) {
    return -1;
  } else {
		int len = strlen(msg) + 1;
		len = len < 3 ? len : 2;
		write(fd, msg, len);
	}
  return 0;
}

  
int main(int argc, char **argv)    
{
	  int fd = -1;           //文件描述符，先定义一个与程序无关的值，防止fd为任意值导致程序出bug    
    int led_fd = -1;
    //char led_buf[128] = {};
    int err;               //返回调用函数的状态    
    int len;                            
    //int i;    
    char rcv_buf[256] = {};
    if(argc != 2)    
    {    
        printf("Usage: %s /dev/ttyUSBX      #(recv data)\n",argv[0]);
      //  printf("open failure : %s\n", strerror(errno));
        return FALSE;    
    }    

    int re =  system("insmod ./100ask_led.ko");
    if (re !=0) {
      re = system("rmmod 100ask_led");
      perror("insmod error....");
      return -1;
    }

    fd = UART_Open(fd,argv[1]); //打开串口，返回文件描述符   
    do  
    {    
        err = UART_Init(fd,115200,0,8,1,'N');    
        //printf("Set Port Exactly!\n"); 
        sleep(1);   
    } while(FALSE == err || FALSE == fd);    


	  led_fd = open("/dev/led_dev0", O_RDWR);
	  if (led_fd == -1)
	  {
		  printf("can not open file /dev/led_dev\n");
		  return -1;
	  }
 
    printf("start receive data...\n");
    while(1)
    {   
        memset(rcv_buf, 0, 256);
        len = UART_Recv(fd, rcv_buf, sizeof(rcv_buf));
        if(len > 0) {
            rcv_buf[len] = '\0';
            printf("receive data is %s\n",rcv_buf);
            int res  = ctrl_led(led_fd, rcv_buf);
            if (res < 0) {
              printf("exit app\n");
              break;
            }
        } else {
            printf("cannot receive data\n");
        }
        usleep(100000);
    }    

    re = system("rmmod 100ask_led");
    UART_Close(fd);
    close(led_fd);
    return 0 ;
}  

