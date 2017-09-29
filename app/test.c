#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>



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
  
  return 0;
  
}

 

