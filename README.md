# Projeto

Implementar um programa que atue como um mensageiro de texto (estilo whatsapp) que troca mensagens usando memória compartilhada (Shared Memory - SHM). Assim, o programa precisa escrever e ler na SHM os dados trocados. Adicionalmente, devem ser feitas as seguintes funcionalidades:
1. Comunicação entre 2 processos (P2P) somente por Texto: os dois processos apenas leem e escrevem caracteres de texto na SHM, onde qualquer um dos dois pode ler ou escrever a qualquer momento;
2. Comunicação entre P2P para troca de arquivos: Um processo envia um arquivo para o outro pela SHM, onde apenas um arquivo por vez é enviado;
3. Comunicação de um processo para vários: Um processo envia um texto via SHM para N processos (onde N>2) que recebem o texto, onde o texto expira após ser lido por todos os N processos.

## 🚀 Programa sendo executado

Vídeo do programa da **[parte 1](https://drive.google.com/file/d/1ojtSX6ScRf-2oN_J0-f2D-w8MOW6lz8-/view?usp=drive_link)** executando.
Vídeo do programa da **[parte 3](https://drive.google.com/file/d/146cS6GeEY41Diae3ApMzWb2z3G9Cwz3Y/view?usp=drive_link)** executando.

### 📋 Parte 1 do projeto: Compartilhamento de caracteres

A princípio, foi utilizada a ideia de fazer dois códigos separados para testar a escrita e leitura dos processos, de forma separada, que iria trabalhar junto de um arquivo main. Porém, para diminuir a quantidade de escrita de código, resolvemos utilizar threads que poderiam chamar as funções de escrita e leitura.

* Função de escrita - Foi criada a função void escreve(){} colocando todas as funções necessárias para a escrita da mensagem. No código utilizamos o ponteiro do pathname para referenciar o arquivo e facilitar a manipulação do mesmo, já que o arquivo faz referência a um dos dois processos. No processo de escrita, é feita a utilização de um ftok, com o intuito de criar um processo filho com uma chave, após isso, utiliza-se a função shmget, que retorna um identificador no id da memória compartilhada. Para anexar os caracteres na memória compartilhada, utiliza-se a função shmat e ponteiro. Usa-se o size_t para verificar o tamanho do identificador. Na utilização do While, usa-se um valor booleano para verificar se ainda pode ser escrito algo ou não. Usa-se dentro o getline para facilitar a manipulação de strings para receber mais de um caractere. Após terminar as mensagens, shmdt é usado para desanexar o ponteiro do bloco de memória compartilhado.

* Função de leitura  - Foi criada a função void ler(){} colocando todas as funções necessárias para a escrita da mensagem. Novamente é utilizado o ponteiro do pathname para referenciar o arquivo, porém agora fazendo referência ao processo oposto. Os códigos de leitura e escrita são bem semelhantes, tendo sua principal diferença dentro do While, onde verifica-se se a string existe, se existir, é mostrado a mensagem do processo e é feita a cópia da string antes de ser desanexada a memória e a exclusão da mesma utilizando o shmctl.

* Função Main dentro dos processos - Na função main são realizadas as criações de threads para leitura e escrita. Cada thread chama uma das funções específicas. Após a chamada da função, as threads são bloqueadas utilizando o join para que não exista conflito de informações.

* Main geral - No arquivo main.cpp, a função System é utilizada para realizar comandos no Linux. Dentro dos comandos, é utilizado o "g++ processo1.cpp -o processo1.out && g++ processo2.cpp -o processo2.out", que serve para abrir os arquivos dos processos junto de seu compilador. Logo depois é utilizado o comando “xterm -e ./processo1.out &” para chamar o emulador.

### 📋 Parte 2 do projeto: Compartilhamento de arquivos

Devido a parte 1 do projeto não ter sido finalizada somente com um bloco de memória, não foi implementada a parte de arquivos. A ideia seria utilizar a biblioteca cstdio do C++, que auxilia na manipulação de arquivos, com funções como fopen, fscran, etc.

### 📋 Parte 3 do projeto: Troca de mensagens com mais de um processo

Os processos são similares com os processos da parte 1 do projeto, porém, utilizando um vetor de controle de escrita e leitura.

* Header - Dentro do arquivo header, tem a criação de uma struct para definir o nome da memória, tendo como atributos uma variável N, que define quantos processos irão ler a mensagem, um ID, e o vetor de caracteres da mensagem, chamando a struct de mem_type.

* Escrita - Dentro da função main, são passados como parâmetros um inteiro e um ponteiro de vetor de caracteres. Logo após, é feita a conversão do ID da memória da string para inteiro. A mem_type faz referência a struct criada no arquivo header.cpp, que vai trabalhar junto com outra memória chamada Control. Assim que começar o código, a variável ctrl será 0, passando pelo primeiro if, é feita a escrita da memória passando pelo for, que controla qual processo já leu a mensagem, trocando de 0 para 1. Passando pelo segundo if, caso a variável ctrl possuir valor 1, é verificado no looping While se a posição é menor do que a quantidade de processos definidos, trocando sua posição para 1, passando pro próximo processo.

* Leitura - Novamente, é passado como parâmetro da main um vetor de caracteres e um inteiro index. É feita a criação da string com um identificador, trabalhando junto do index da memória. O comando Stoi converte o id da string para inteiro. O mem_type faz referência a struct criada no arquivo header.cpp, que vai trabalhar junto com outra memória chamada Control. Entrando no looping While, verificando se já foi feita a leitura ou não, se a leitura já for feita, sendo indicada por 1, o sistema mostra a mensagem.

* Main - No arquivo main é feita a solicitação das mensagens dos processos. Logo após, é feita a criação do Id das duas memórias. O valor do Control se inicia como 0, para que todos os processos possam ler e escrever. Após isso, são chamados os comandos do Linux para abrir os processo de escrita e leitura. O looping do for serve para realizar a leitura constante das mensagens enquanto ainda houver processos, enquanto o While é para manter os processos abertos.

### ✨ Outras informações
Trabalho feito para a cadeira de Sistemas Operacionais em 2023.1.

---
Feito por [Alicia Paiva](https://github.com/aliciapaivaa) 😊
