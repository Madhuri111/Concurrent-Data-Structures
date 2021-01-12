#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>
#include<time.h>
#include<stdlib.h>


//4 arrays:- semaphore array(sArray),state array(prof_state),input passing array(prof),thread for each prof array(pthread)

//we have five professors
#define n 5

//we have three states for each professor THINKING,EATING,HUNGRY
//So lets define 0,1,2 as eating,hungry,thinking

int prof_state[n];

//lets define a mutex such that no two professors can eat at the same time

sem_t mutex;
sem_t sArray[n]; //for each philosopher , this array is used to control the behaviour

//function for random time
void randwait(int secs) {
	int len;

	// Generate a random number…
	len = (int) ((1 * secs) + 1);
	sleep(len);
}
//total 4 functions :- one for taking forks,one for putting forks,one for testing whether forks free, one for functioning

void* function(void* num);
void test_neighbours(int);
void fork_take(int); 
void fork_free(int);


int main()
{
    int prof[5];
    for(int i=0;i<5;i++)
    {
        prof[i]=i;
    }

    //create a thread for each philosopher
    pthread_t pthread[n];

    sem_init(&mutex,0,1);
    //initialize every semaphore
    for(int i=0;i<5;i++)
    {
        sem_init(&sArray[i],0,0);
    }

    //initialize thread for each professor and then wait for them to complete 
    for(int i=0;i<5;i++)
    {
        pthread_create(&pthread[i],NULL,function,&prof[i]);

        printf("Professor %d is thinking right now\n\n",i+1);
    }
    //join threads after completion

    for(int i=0;i<5;i++)
    {
        pthread_join(pthread[i],NULL);
    }
}
void* function(void* num) 
{ 

	while(1) 
    {
		int* input = num; 

		randwait(1); 

        //take fork if free
		fork_take(*input); 

		//randwait(0); 

        //after ur completion put out forks for next use
		fork_free(*input); 
	} 
} 

void fork_take(int inp1)
{
    //dont enter any other when one person is waiting
    //so we use mutex here
    sem_wait(&mutex);
    
    //here prof came to take fork which means he is hungry,so change state
    prof_state[inp1]=1;
    int p=inp1+1;
    printf("Professor %d is hungry right now \n \n",p);

    //now check if forks are free
    test_neighbours(inp1);

    //then release the mutex when your work is over
    sem_post(&mutex);

    // wait until the particular prof gets his work done
	sem_wait(&sArray[inp1]); 

	randwait(1);
}
void fork_free(int inp2)
{
        //dont enter any other when one person is waiting
    //so we use mutex here
    sem_wait(&mutex);
    
    //here prof came to put fork which means he is thinking,so change state
    prof_state[inp2]=2;
    int p=inp2+1;

    int l=(inp2+4)%5;
    int r=(inp2+1)%5;
    //int ll=l+1;
    //int rr=r+1;
    printf("Professor %d is putting forks %d , %d right now.. \n\n",p,l+1,r+1);
    printf("Professor %d is thinking right now\n\n",p);
    sem_post(&mutex);

    //now check if forks are free
    test_neighbours(l);
    test_neighbours(r);

    //then release the mutex when your work is over


}
void test_neighbours(int inp3)
{
    int l=(inp3+4)%5;
    int r=(inp3+1)%5;
    //if prof is hungry(0), and neighbours are not eating then proceed
    if(prof_state[inp3]==1 && prof_state[l]!=0 && prof_state[r]!= 0)
    {
        //you can eat now :) so change the state
        prof_state[inp3]=0;

        randwait(2);

        int ll=l+1;
        int rr=r+1;

        printf("Professor %d have taken forks %d,%d \n\n",inp3+1,ll,rr);
        printf("Professor %d is eating right now..\n",inp3+1);
        sem_post(&sArray[inp3]); 

    }
}