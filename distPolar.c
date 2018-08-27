/*#################################################################
Alunos:
Everton da Silva Coelho - 101937
Yasmin Wassef - 102129

##################################################################*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <sys/time.h>


#define MAX_TAM 100000 //10⁵
//#define MAX_TAM 10000000//10⁷

#define NUM_TH 1
double r1[MAX_TAM], r2[MAX_TAM], tt1[MAX_TAM], tt2[MAX_TAM], dist[MAX_TAM];

struct 
{
	int begin;
	int end;
	double max_dist_thread;

}typedef parameters;

void initialize() {

	struct timeval tempo;
	gettimeofday(&tempo, NULL);

	srand(tempo.tv_usec);
	//printf("r1\n");
	for (int i = 0; i < MAX_TAM; i++)
	{
		r1[i] = (double)(rand()%101); 
		//printf("%f\n", r1[i]);
	}
	srand(time(NULL));
	//printf("r2\n");
	for (int i = 0; i < MAX_TAM; i++)
	{
		r2[i] = (double)(rand()%101); 
		//printf("%f\n", r2[i]);
	}
	gettimeofday(&tempo, NULL);

	srand(tempo.tv_usec);
	for (int i = 0; i < MAX_TAM; i++)
	{
		tt1[i] = (double)(rand()%361); 
	}
	srand(time(NULL));
	for (int i = 0; i < MAX_TAM; i++)
	{
		tt2[i] = (double)(rand()%361); 
	}
	//printf("saida\n");
}


void *distance(void *arg) {
	parameters *p = (parameters*) arg;
	p->max_dist_thread = 0;
	for (int i = p->begin; i < p->end; i++)
	{
		dist[i] = sqrt((pow(r1[i],2)+pow(r2[i],2)) - 2*r1[i]*r2[i]*cos(tt1[i]-tt2[i]));	/* code */
		//printf("%f\n", aux);
		/*if(aux > p->max_dist_thread){
			p->max_dist_thread = aux;
		}*/
	}
	pthread_exit(0);
}


int main(int argc, char const *argv[])
{
	parameters args[NUM_TH];
	int range = MAX_TAM/NUM_TH;

	for (int i = 0; i < NUM_TH; i++)
	{
		args[i].begin = i * range;
		args[i].end = ((i+1) * range)-1;
	}
	
	initialize();

	pthread_t thread[NUM_TH];

	struct timeval inicio, final;
  	int tmili;
  	gettimeofday(&inicio, NULL);


	for (int i = 0; i < NUM_TH; i++)
	{
		pthread_create(&thread[i], NULL, &distance, (void*) &args[i]);
	}
	for (int i = 0; i < NUM_TH; i++)
	{
		pthread_join(thread[i], NULL);
	}

	gettimeofday(&final, NULL);
  	tmili = (int) (1000 * (final.tv_sec - inicio.tv_sec) + (final.tv_usec - inicio.tv_usec) / 1000);
  
  	printf("tempo decorrido: %d milisegundos\n", tmili);
	
	//printf("%f\n",args.max_dist_thread);
	
	return 0;
}