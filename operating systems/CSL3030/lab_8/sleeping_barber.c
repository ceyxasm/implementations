#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdbool.h>

// semaphores
sem_t customerSemaphore, mutex, barberSemaphore, sem_custDone, sem_barbDone;

// functions
void *customer(void *num);
void *barber(void *);
void *cutHair();
void *getHairCut();
void waiting();

// global variables
int chairs = 8;
int totalCustomers = 50;
int currentCustomers = 0;
int hairCutTime = 0;

// customers
void *customer(void *b)
{
	int customerID = *(int *)b;

	sem_wait(&mutex);
	if (currentCustomers >= chairs)
	{
		printf("customer %d leaves, chairs full\n", customerID);
		sem_post(&mutex);
		waiting();
	}
	else
	{
		if(currentCustomers == 0)
		{
			printf("customer wakes up barber \n");
		}
		currentCustomers++;
	}

	printf("customer %d arrived and takes chair : %d\n", customerID, (chairs - currentCustomers));
	sem_post(&mutex);

	sem_post(&customerSemaphore);
	sem_wait(&barberSemaphore);
	printf("customer %d is getting haircut\n", customerID);
	hairCutTime = rand() % 50 + 1;
	cutHair();
	sem_post(&sem_custDone);
	sem_wait(&sem_barbDone);

	sem_wait(&mutex);
	currentCustomers--;
	sem_post(&mutex);

	if (customerID == totalCustomers)
	{
		printf("Barbershop closes\n");
		exit(0);
	}
	return;
}

void waiting()
{
	while (1)
	{
	}
	return;
}

// barber
void *barber(void *a)
{
	int check = 1;
	while (check)
	{
		sem_wait(&customerSemaphore);
		sem_post(&barberSemaphore);
		printf("barber is cutting hair\n");
		getHairCut();
		printf("barber finished cutting hair\n");
		sem_wait(&sem_custDone);
		sem_post(&sem_barbDone);

		if(currentCustomers == 0)
		{
			printf("Barber Goes to sleep, no customers \n");
		}
	}
	return;
}

void *getHairCut()
{
	sleep(hairCutTime);
	return;
}

void *cutHair()
{
	sleep(hairCutTime);
	return;
}

int main(int argc, char *argv[])
{
	if (argc == 3)
	{
		chairs = atoi(argv[1]);
		totalCustomers = atoi(argv[2]);
	}
	else if (argc != 1)
	{
		printf("USAGE: con4b chairs customers\n");
		exit(EXIT_FAILURE);
	}

	pthread_t bid;
	pthread_t cid[totalCustomers];

	int customerArr[totalCustomers], index;
	index = 0;

	while (index < totalCustomers)
	{
		customerArr[index] = index;
		index++;
	}

	sem_init(&customerSemaphore, 0, 0);
	sem_init(&mutex, 0, 1);
	sem_init(&barberSemaphore, 0, 0);
	sem_init(&sem_custDone, 0, 0);
	sem_init(&sem_barbDone, 0, 0);

	pthread_create(&bid, NULL, barber, NULL);

	index = 0;
	while (index < totalCustomers)
	{
		pthread_create(&cid[index], NULL, customer, (void *)&customerArr[index]);
		int randomValue = rand() % 10 + 1;
		sleep(randomValue);
		index++;
	}

	index = 0;
	while (index < totalCustomers)
	{
		pthread_join(cid[index], NULL);
		index++;
	}

	return 0;
}
