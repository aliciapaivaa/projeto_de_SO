#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>
using namespace std;

int main()
{
	// ====================== write process ====================
	void *shared_memory;
	char buff[100];
	int id;

	//it creates shared memory segment with the key 2345
	//size of the memory is 1024
	//IPC_CREAT is used to create the shared segment if it does not exist
	//0666 are the permisions on the shared segment
	
	id = shmget((key_t)2345, 1024, 0666 | IPC_CREAT);

	printf("Key of shared memory is %d\n",id);

	shared_memory = shmat(id ,NULL, 0); //process attached to shared memory segment
				    //shm at id

	printf("Process attached at %p\n",shared_memory); //this prints the address where the segment is attached with this process
	printf("Enter some data to write to shared memory:\n"); 

	cin >> buff;
	
	strcpy((char *)shared_memory, buff); //what is in buff go to shared_memory
	
	// printf("Process attached at %p\n",shared_memory); //this prints the address where the segment is attached with this process

	cout << "You wrote : " << (char *)shared_memory << "\n";

	return 0;
}


/*
#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
using namespace std;

int main()
{
	// ftok to generate unique key
	key_t key = ftok("shmfile",65);

	// shmget returns an identifier in shmid
	int shmid = shmget(key,1024,0666|IPC_CREAT);

	// shmat to attach to shared memory
	char *str = (char*) shmat(shmid,(void*)0,0);

	cout<<"Write Data : ";
	cin >> str;

	printf("Data written in memory: %s\n",str);
	
	//detach from shared memory
	shmdt(str);

	return 0;
}
*/