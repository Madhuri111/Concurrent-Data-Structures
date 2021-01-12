#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>
#include<time.h>
#include<stdlib.h>

//lets define max number of customes allowed as 20

int maxCustomer=20;

int everythingOver=0;

//first four variables for semaphores
sem_t bChair; //barber chair 
sem_t bRoom; //to enter into waiting room
sem_t bSleep; //barber to sleep until customer arrives
sem_t bSeat; //barber to release seat only after cutting is over

//random wait function

void randwait(int secs) {
	int len;

	// Generate a random number…
	len = (int) ((1 * secs) + 1);
	sleep(len);
}

//one function for barber working,another for customer functioning
void *customer(void *);
void *barber(void *junk) {
	// While there are still customers to be serviced…
	// Our barber is omnicient and can tell if there are
	// customers still on the way to his shop.
	while (!everythingOver) {

		// Sleep until someone arrives and wakes you..
		printf("The barber is sleeping\n\n");
		sem_wait(&bSleep);

		// Skip this stuff at the end…
		if (!everythingOver) {

			// Take a random amount of time to cut the
			// customer’s hair.
			printf("The barber is cutting hair\n\n");
			randwait(2);
			printf("The barber has finished cutting hair.\n\n");

			// Release the customer when done cutting…
			sem_post(&bSeat);
		}
		else {
			printf("The barber is going home for the day.\n\n");
		}
	}
}
int main()
{
    //take input from user for number of customes and chairs
    int nCustomers,nChairs;
    printf("Enter number of customers and chais:\n");
    scanf("%d",&nCustomers);
    scanf("%d",&nChairs);

    //if number of customers exceeds max then dont allow them
    if(nCustomers>maxCustomer)
    {
        printf("Only %d customers are allowed , rest can leave\n",maxCustomer);
    }

    //arrange an value for every customer
    int Customers[maxCustomer];
    for(int i=1;i<=maxCustomer;i++)
    {
        Customers[i]=i;
    }
    /*
    //checking whether its working right
    for(int i=1;i<=maxCustomer;i++)
    {
        printf("%d",Customers[i]);
    }
    */

    //Now , create a thread for barber and n customers;
    pthread_t tBarber;
    pthread_t tCustomer[maxCustomer];

    //initialize semaphores
    sem_init(&bChair,0,1);
    sem_init(&bSeat,0,0);
    sem_init(&bSleep,0,0);
    sem_init(&bRoom,0,nChairs);

    pthread_create(&tBarber,NULL,barber,NULL);
    for(int j=1;j<=maxCustomer;j++)
    {
        pthread_create(&tCustomer[j],NULL,customer,(void*)&Customers[j]);
    }
    
    //join threads after waiting them for finish
    for(int k=1;k<=maxCustomer;k++)
    {
        pthread_join(tCustomer[k],NULL);
        sleep(1);
    }

    int everythingOver=1;
    //after everything gets done,wake barber so he will wake up
    sem_post(&bSleep);
    pthread_join(tBarber,NULL);   
}

void *customer(void *input)
{
    	int number= *(int *)input;
 printf("Customer %d going to enter waiting room\n\n",number);
 sem_wait(&bRoom);

//until the chair becomes free,wait for it
 sem_wait(&bChair);

 printf("Customer %d entered waiting room\n\n",number);
 sem_post(&bRoom);

 //then wait for barber chair 

 //when you acquired chair,wake up the barber as he is sleeping or if he is sleeping
 printf("Barber has got customer %d so woke up\n\n",number);
 sem_post(&bSleep); //which means you woke up barber

 //wait till barber cuts ur hair
 sem_wait(&bSeat);

 //when done with your cutting,leave the chair for next customer
 sem_post(&bChair);

 printf("Customer %d is done with his cutting and left\n\n",number);

}