#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <cstring>

#define SHM_SIZE 1024

struct SharedMemory {
    char message[SHM_SIZE];
    int readCount;
};

int main() {
    // Cria a chave única para a memória compartilhada
    key_t key = ftok("receptor.cpp", 1234);
    if (key == -1) {
        perror("ftok");
        return 1;
    }

    // Obtém a ID da memória compartilhada
    int shmid = shmget(key, sizeof(char)*1024, 0666); 
    if (shmid == -1) {
        perror("shmget");
        return 1;
    }

    // Anexa a memória compartilhada ao processo
    SharedMemory* sharedMemory = static_cast<SharedMemory*>(shmat(shmid, nullptr, 0));
    if (sharedMemory == (SharedMemory*)-1) {
        perror("shmat");
        return 1;
    }

    // Lê a mensagem da memória compartilhada
    std::string receivedMessage(sharedMemory->message);
    std::cout << "Process Receptor leu a mensagem: " << receivedMessage << std::endl;

    // Incrementa o contador de leitura
    __sync_fetch_and_add(&sharedMemory->readCount, 1);

    // Desanexa a memória compartilhada
    shmdt(sharedMemory);

    return 0;
}
