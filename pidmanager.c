#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#define MIN_PID 100
#define MAX_PID 1000
#define ARRAY MAX_PID-MIN_PID+1

int statusofpid[ARRAY];       

int allocate_map()        
{
  int i;
  for(i=0;i<ARRAY;i++)
  {
    statusofpid[i]=0;
  }
  return 0;               
}

int allocate_pid()
{
  int i;
  for(i=0;i<ARRAY;i++)
  {
    if(pid_status[i]==0)   
    {
      pid_status[i]=1;     
      return i+100;        
    }
  }
  return 1;                
}

void release_pid(int p)
{
  int pid=p-100;           
  pid_status[pid]=0;        
}

void display()
{
  int i,c=0;
  
  for(i=0;i<ARR_SIZE;i++)
  {
    if(pid_status[i]==1)              
    {
      printf("\n[%d] = %d\t",i+100,pid_status[i]);
      c++;
    }
  }
  printf("\nPids in Use: %d",c);
  
}

int pid_check(int pid)
{
  if(pid>=100)                        
  {
    printf("\nPid %d assigned successfully...\n",pid);
    return 0;                               
  }
  else if(pid==1)                     
  {
    printf("\npid allocation failed...\n"); 
    return 1;                         
  }
  else                              
  {
    printf("\nSomething went wrong... pid: %d is returned...",pid);
    return 1;
  }
}

void *thread_fun(void *pro)              
{
  int pid = allocate_pid();                
  
  while(pid_check(pid)==1)             
  {
    sleep(3);                             
       
    pid = allocate_pid();              
  }
  display();                             
  
  
  sleep(3);                                                    
  
  release_pid(pid);                                    
  display();
}

int main()
{
  int i, no_of_threads;
  printf("Enter no of threads: ");
  scanf("%d",&no_of_threads);               
  
  int x = allocate_map();                   
  if(x==0)                                  
    printf("Map allocated...\n");
  else
    printf("Problem in initializing statuses...\n");
  
                 
  pthread_t pr_threads[no_of_threads];              
  
  for(i=0;i<no_of_threads;i++)
  {
                                     
    pthread_create(&pr_threads[i],NULL,thread_fun,NULL);           
  }
  
  for(i=0;i<no_of_threads;i++)              
  {
    pthread_join(pr_threads[i],NULL);                     
  }
  
  printf("\n...Program Successfully terminated...\n");
}
  
