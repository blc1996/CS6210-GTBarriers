//////////////////////////////////
//Deep Datta Roy
//Phil Johnson
//
//Dissemination barrier using OpenMP
//////////////////////////////////
#include "dissemination.h"


//////////////////////////GLOBAL VARIABLES//////////////////////////

#define NO_MESSAGE	0
#define MESSAGE	    1

int numThreads;					//number of threads
int rounds; 					//number of rounds

/////////////////////////////////////////////////////////////////////


void barrier_init(int barrierThreads){
	numThreads = barrierThreads;				//initialize number of threads for barrier
	rounds = ceil(log(numThreads)/log(2));		//find the number of rounds - log2numThreads
}

void barrier(){
	int i;
	int sendID, recvID;
	int myID;
	int recvMsg;
	int sendMsg = MESSAGE;

  	MPI_Comm_rank(MPI_COMM_WORLD, &myID);	//Get ID
	
	//Do the rounds
	for (i = 0; i < rounds; i++){
		//Send message to correct thread
		sendID = (myID + (int)pow(2,i))%numThreads;
		MPI_Send(&sendMsg, 1, MPI_INT, sendID, 0, MPI_COMM_WORLD);
		//Recieve Message from correct threads
		recvID = myID -  (int)pow(2,i);
		if (recvID < 0){
			recvID = recvID + numThreads;
		}
		MPI_Recv(&recvMsg, 1, MPI_INT, recvID, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}


}
