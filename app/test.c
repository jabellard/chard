#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#include <sys/ioctl.h>
//#include "../drv/chard.h"



// aaaaaaaaaa
// bbbbbbbbbb
// cccccccccc

int main()
{

	const int len = 256;
char buf1[len];
char buf2[len];

  int fd;
  int ret;
  
  fd = open("/dev/chard0", O_RDWR);
  if (fd == -1)
  {
  	perror("open");
  } // end if
  
  int user_input;
  printf("Enter any integer and press enter to proceed: ");
  scanf("%d", &user_input);
  
  strcpy(buf2, "aaaaaaaaaa");
  printf("the buffer: %s\n", buf2);
  ret = write(fd, buf2, strlen(buf2));
  printf("ret = %d\n", ret);
  
  if (ret == -1)
  {
  	perror("99rite1");
  } // end if
  
   strcpy(buf2, "bbbbbbbbbb");
  
  ret = write(fd, buf2, strlen(buf2));
    printf("ret = %d\n", ret);
  if (ret == -1)
  {
  	perror("99rite2");
  } // end if
  
    strcpy(buf2, "cccccccccc");
  
  ret = write(fd, buf2, strlen(buf2));
    printf("ret = %d\n", ret);
  if (ret == -1)
  {
  	perror("99rite3");
  } // end if
  
  int count = 10;
  ret = read(fd, buf1, count);
  printf("ret-read = %d\n", ret);
  if (ret == -1)
  {
  	perror("read");
  } // end if
  
  buf1[count] = '\0';
  printf("read this: %s\n", buf1);
  printf("-----------------------------\n");
  
  
    ret = read(fd, buf1, count);
  printf("ret-read = %d\n", ret);
  if (ret == -1)
  {
  	perror("read");
  } // end if
  
  buf1[count] = '\0';
  printf("read this: %s\n", buf1);
   printf("-----------------------------\n");
 
    int a = 12;
    ret = -77;
   ret = ioctl(fd, 1074031360, a);
   printf("return value = %d.\n", ret);
   
      int  b = 0;
      ret = -88;
   ret = ioctl(fd, 2147773185, &b);
   printf("return value = %d.\n", ret);
printf("recieved value = %d.\n", b);
 
 

   
   
   
  return 0;
  
}

 

