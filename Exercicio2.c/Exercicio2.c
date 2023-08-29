#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>
#define MAXSIZE 10


typedef struct Aluno {
    char nome[20];
    int matricula;
    float nota;
} Aluno;


typedef struct ListaAlunos {
    Aluno alunos[MAXSIZE];
    int numElem;
} ListaAlunos;


void preencheAluno(Aluno* ptrAluno,
                   int matricula,
                   float nota,
                   char* nome){
    (*ptrAluno).matricula = matricula;
    (*ptrAluno).nota = nota;
    strcpy((*ptrAluno).nome, nome);
}

void inicializaLista(ListaAlunos* listaAlunos){
    listaAlunos->numElem = 0;
}

void exibeLista(ListaAlunos* listaAlunos){
    int index;
    printf("Exibindo lista...\n");
    for(index = 0; index < listaAlunos->numElem;index++){
        printf("Aluno %d\n", index);
        printf("Nome: %s\n", listaAlunos->alunos[index].nome);
        printf("Matricula: %d\n", listaAlunos->alunos[index].matricula);
        printf("Nota: %.1f\n", listaAlunos->alunos[index].nota);
    }
}


bool insereAlunoNaLista(ListaAlunos* listaAlunos,
                        Aluno aluno,
                        int posicao) {
    if (listaAlunos->numElem >= MAXSIZE) {
        printf("Inserção em posição inválida (lista cheia)!\n");
        return false;
    }

    if (posicao < 0 || posicao > listaAlunos->numElem) {
        printf("Inserção em posição inválida!\n");
        return false;
    }

    for (int index = 0; index < listaAlunos->numElem; index++) {
        if (listaAlunos->alunos[index].matricula == aluno.matricula) {
            printf("Matrícula duplicada, inserção não permitida!\n");
            return false;
        }
    }

    if (posicao == listaAlunos->numElem) {
        listaAlunos->alunos[listaAlunos->numElem] = aluno;
    } else {
        for (int index = listaAlunos->numElem; index > posicao; index--) {
            listaAlunos->alunos[index] = listaAlunos->alunos[index - 1];
        }
        listaAlunos->alunos[posicao] = aluno;
    }

    listaAlunos->numElem++;
    return true;
}

void obterDetalhesAluno(Aluno* novoAluno) {
    printf("Digite o nome do aluno: ");
    scanf("%s", novoAluno->nome);
    printf("Digite a matrícula do aluno: ");
    scanf("%d", &novoAluno->matricula);
    printf("Digite a nota do aluno: ");
    scanf("%f", &novoAluno->nota);
}


bool excluiElementoDaLista(ListaAlunos* listaAlunos, int posicao) {
    if (posicao < 0 || posicao >= listaAlunos->numElem) {
        printf("Exclusão em posição inválida!\n");
        return false;
    }


    Aluno emptyAluno = { "", 0, 0.0 };
    listaAlunos->alunos[posicao] = emptyAluno;

    for (int index = posicao; index < listaAlunos->numElem - 1; index++) {
        listaAlunos->alunos[index] = listaAlunos->alunos[index + 1];
    }

    listaAlunos->numElem--;
    return true;
}


int buscaAlunoPorNome(ListaAlunos* listaAlunos, char* nome) {
    for (int index = 0; index < listaAlunos->numElem; index++) {
        if (strcmp(listaAlunos->alunos[index].nome, nome) == 0) {
            return index;
        }
    }
    return -1;
}


int buscaAlunoPorMatricula(ListaAlunos* listaAlunos, int matricula) {
    for (int index = 0; index < listaAlunos->numElem; index++) {
        if (listaAlunos->alunos[index].matricula == matricula) {
            return index;
        }
    }
    return -1;
}


Aluno* retornaNesimoAluno(ListaAlunos* listaAlunos, int n) {
    if (n >= 0 && n < listaAlunos->numElem) {
        return &listaAlunos->alunos[n];
    } else {
        return NULL;
    }
}

bool insereAlunoEmOrdem(ListaAlunos* listaAlunos, Aluno novoAluno) {
    if (listaAlunos->numElem >= MAXSIZE) {
        printf("Inserção em posição inválida (lista cheia)!\n");
        return false;
    }

    int posicaoInsercao = 0;
    while (posicaoInsercao < listaAlunos->numElem &&
           strcmp(novoAluno.nome, listaAlunos->alunos[posicaoInsercao].nome) > 0) {
        posicaoInsercao++;
    }

    for (int index = listaAlunos->numElem; index > posicaoInsercao; index--) {
        listaAlunos->alunos[index] = listaAlunos->alunos[index - 1];
    }

    listaAlunos->alunos[posicaoInsercao] = novoAluno;
    listaAlunos->numElem++;
    return true;
}

int buscaSequencialSentinela(ListaAlunos* listaAlunos, char* nome) {
    Aluno sentinela;
    strcpy(sentinela.nome, nome);
    listaAlunos->alunos[listaAlunos->numElem] = sentinela;

    int index = 0;
    while (strcmp(nome, listaAlunos->alunos[index].nome) != 0) {
        index++;
    }

    if (index == listaAlunos->numElem) {
        return -1; // Aluno não encontrado
    }

    return index;
}

int buscaBinaria(ListaAlunos* listaAlunos, char* nome) {
    int inicio = 0;
    int fim = listaAlunos->numElem - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        int comparacao = strcmp(nome, listaAlunos->alunos[meio].nome);

        if (comparacao == 0) {
            return meio; // Aluno encontrado
        } else if (comparacao < 0) {
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
    }

    return -1; // Aluno não encontrado
}

void ordenaAlunosPorNome(ListaAlunos* listaAlunos) {
    for (int i = 0; i < listaAlunos->numElem - 1; i++) {
        for (int j = 0; j < listaAlunos->numElem - i - 1; j++) {
            if (strcmp(listaAlunos->alunos[j].nome, listaAlunos->alunos[j + 1].nome) > 0) {
                Aluno temp = listaAlunos->alunos[j];
                listaAlunos->alunos[j] = listaAlunos->alunos[j + 1];
                listaAlunos->alunos[j + 1] = temp;
            }
        }
    }
}

void exibeListaOrdenada(ListaAlunos* listaAlunos) {
    ordenaAlunosPorNome(listaAlunos);

    printf("Exibindo lista ordenada por nome...\n");
    for (int index = 0; index < listaAlunos->numElem; index++) {
        printf("Aluno %d\n", index);
        printf("Nome: %s\n", listaAlunos->alunos[index].nome);
        printf("Matrícula: %d\n", listaAlunos->alunos[index].matricula);
        printf("Nota: %.1f\n", listaAlunos->alunos[index].nota);
    }
}

int main(){

    setlocale(LC_ALL, "");

    int matriculaBusca;
    int posicaoBusca;
    Aluno novoAluno;
    char nomeBusca[20];
    ListaAlunos listaAlunos;
    inicializaLista(&listaAlunos);

    Aluno aluno0, aluno1, aluno2;
    preencheAluno(&aluno0, 15424242, 9.5, "Joao");
    preencheAluno(&aluno1, 10101011, 10, "Ana");
    preencheAluno(&aluno2, 22222222, 7, "Bia");

    insereAlunoNaLista(&listaAlunos, aluno0, 0);
    insereAlunoNaLista(&listaAlunos, aluno1, 0);
    insereAlunoNaLista(&listaAlunos, aluno2, 1);

    exibeLista(&listaAlunos);
    printf("\nExcluindo elemento.............\n");
    excluiElementoDaLista(&listaAlunos, 1);
    exibeLista(&listaAlunos);
    printf("nao foi apagado %s\n", listaAlunos.alunos[2].nome);


    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Buscar aluno por nome\n");
        printf("2. Buscar aluno por matrícula\n");
        printf("3. Buscar aluno por posição\n"); // Opção adicionada
        printf("4. Inserir novo aluno\n");
        printf("5. Excluir aluno\n");
        printf("6. Buscar aluno por sentinela: \n");
        printf("7. Buscar aluno por número binário: \n");
        printf("8. Listar alunos em ordem alfabética\n");
        printf("9. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &choice);

        while (getchar() != '\n'); // Limpa o buffer de entrada

        switch (choice) {
            case 1:

                printf("Digite o nome do aluno a ser buscado: ");
                scanf("%s", nomeBusca);

                int indexNome = buscaAlunoPorNome(&listaAlunos, nomeBusca);
                if (indexNome != -1) {
                    printf("Aluno encontrado por nome:\n");
                    printf("Nome: %s\n", listaAlunos.alunos[indexNome].nome);
                    printf("Matrícula: %d\n", listaAlunos.alunos[indexNome].matricula);
                    printf("Nota: %.1f\n", listaAlunos.alunos[indexNome].nota);
                } else {
                    printf("Aluno não encontrado por nome.\n");
                }
                break;
                break;

            case 2:

                printf("Digite a matrícula do aluno a ser buscado: ");
                scanf("%d", &matriculaBusca);

                int indexMatricula = buscaAlunoPorMatricula(&listaAlunos, matriculaBusca);
                if (indexMatricula != -1) {
                    printf("Aluno encontrado por matrícula:\n");
                    printf("Nome: %s\n", listaAlunos.alunos[indexMatricula].nome);
                    printf("Matrícula: %d\n", listaAlunos.alunos[indexMatricula].matricula);
                    printf("Nota: %.1f\n", listaAlunos.alunos[indexMatricula].nota);
                } else {
                    printf("Aluno não encontrado por matrícula.\n");
                }
                break;

            case 3:

                printf("Digite a posição do aluno a ser buscado: ");
                scanf("%d", &posicaoBusca);

                if (posicaoBusca >= 0 && posicaoBusca < listaAlunos.numElem) {
                    Aluno* alunoNaPosicao = retornaNesimoAluno(&listaAlunos, posicaoBusca);
                    if (alunoNaPosicao != NULL) {
                        printf("Aluno na posição %d:\n", posicaoBusca);
                        printf("Nome: %s\n", alunoNaPosicao->nome);
                        printf("Matrícula: %d\n", alunoNaPosicao->matricula);
                        printf("Nota: %.1f\n", alunoNaPosicao->nota);
                    } else {
                        printf("Erro ao buscar aluno na posição %d.\n", posicaoBusca);
                    }
                } else {
                    printf("Posição inválida.\n");
                }
                break;

            case 4: {
                Aluno novoAluno;
                obterDetalhesAluno(&novoAluno);

                if (insereAlunoEmOrdem(&listaAlunos, novoAluno)) {
                    printf("Novo aluno inserido em ordem alfabética com sucesso!\n");
                } else {
                    printf("Erro ao inserir novo aluno.\n");
                }
                break;
                }

            case 5: {
                int posicaoExclusao;
                printf("Digite a posição do aluno a ser excluído: ");
                scanf("%d", &posicaoExclusao);

                if (excluiElementoDaLista(&listaAlunos, posicaoExclusao)) {
                    printf("Aluno excluído com sucesso da posição %d do array.\n", posicaoExclusao);
                } else {
                    printf("Erro ao excluir aluno.\n");
                }
                break;
            }

            case 6: {
                printf("Digite o nome do aluno a ser buscado: ");
                scanf("%s", nomeBusca);

                int indexSentinela = buscaSequencialSentinela(&listaAlunos, nomeBusca);
                if (indexSentinela != -1) {
                    printf("Aluno encontrado por nome (busca com sentinela):\n");
                    printf("Nome: %s\n", listaAlunos.alunos[indexSentinela].nome);
                    printf("Matrícula: %d\n", listaAlunos.alunos[indexSentinela].matricula);
                    printf("Nota: %.1f\n", listaAlunos.alunos[indexSentinela].nota);
                } else {
                    printf("Aluno não encontrado por nome (busca com sentinela).\n");
                }
                break;
            }

            case 7: {
                printf("Digite o nome do aluno a ser buscado: ");
                scanf("%s", nomeBusca);

                int indexBinaria = buscaBinaria(&listaAlunos, nomeBusca);
                if (indexBinaria != -1) {
                    printf("Aluno encontrado por nome (busca binária):\n");
                    printf("Nome: %s\n", listaAlunos.alunos[indexBinaria].nome);
                    printf("Matrícula: %d\n", listaAlunos.alunos[indexBinaria].matricula);
                    printf("Nota: %.1f\n", listaAlunos.alunos[indexBinaria].nota);
                } else {
                    printf("Aluno não encontrado por nome (busca binária).\n");
                }
                break;
            }

            case 8:
                exibeListaOrdenada(&listaAlunos);
                break;

            case 9:
                printf("Encerrando o programa.\n");
                break;

            default:
                printf("Opção inválida. Por favor, escolha uma opção válida.\n");
                break;
        }

    } while (choice != 9);

    return 0;
}
