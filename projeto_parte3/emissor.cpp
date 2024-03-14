#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <cstring>

#define SHM_SIZE 1024
#define NUM_PROCESSES 3 // Número de processos receptores

struct SharedMemory {
    char message[SHM_SIZE];
    int readCount;
};

int main() {
    // Cria a chave única para a memória compartilhada
     const char *pathname = "emissor.cpp";
    key_t key = ftok(pathname, 1234);
    if (key == -1) {
        perror("ftok");
        return 1;
    }

    // Cria ou obtém a ID da memória compartilhada
    int shmid = shmget(key, sizeof(SharedMemory), 0666 | IPC_CREAT);
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

    // Inicializa os dados da memória compartilhada
    sharedMemory->readCount = 0;

    // Processo emissor envia o texto para os processos receptores

    std::string message = "Hello from Process Emitter!";
    std::strncpy(sharedMemory->message, message.c_str(), SHM_SIZE);
    std::cout << "Process Emitter enviou a mensagem: " << message << std::endl;

    // Aguarda até que todos os processos receptores leiam a mensagem
    while (sharedMemory->readCount < NUM_PROCESSES) {
        sleep(1);
    }

    // Expira o texto após ser lido por todos os processos receptores
    std::cout << "O texto expirou após ser lido por todos os processos receptores." << std::endl;

    // Desanexa e remove a memória compartilhada
    shmdt(sharedMemory);
    shmctl(shmid, IPC_RMID, nullptr);

    return 0;
}
