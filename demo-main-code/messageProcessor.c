#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_t  mythread_led;
pthread_t  mythread_beep;
pthread_t  mythread_camera;
pthread_t  mythread_dht;


void *myled_fun()
{

   printf("###mythread_led...\n");
}

void *mybeep_fun()
{

   printf("###mythread_beep...\n");
}

int main(int argc, const char *argv[])
{
   int i=0;

    printf("home directory=%s\n", getenv("HOME"));
    printf("Parameters count: %d\n", argc);
   
    for(i=0; i<argc; i++)
    {	
    	printf("Parameter #%d = %s\n", i, argv[i]);

    }

    
   if(0!=pthread_create(&mythread_led, NULL, &myled_fun, NULL))
   {
	perror("mythread_led");     
	return -1;      
   }

   if(0!=pthread_create(&mythread_beep, NULL, &mybeep_fun, NULL))
   {
       perror("mythread_beep");
   }


   if(0 != pthread_join(mythread_led,NULL))
   {
         perror("pthread_led");
                return -1;
    }

    if(0 != pthread_join(mythread_beep,NULL))
    {
          perror("pthread_beep");
          return -1;
    }



}
