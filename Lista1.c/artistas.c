#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Estrutura para representar um artista
typedef struct {
    char nome[100];
    char genero[100];
    char local[100];
    char **albums;
    int numAlbums;
} Artista;

// Fun��o para ler um artista a partir do arquivo
Artista lerArtista(FILE *arquivo) {
    Artista artista;
    fscanf(arquivo, " %99[^\n]%*c", artista.nome);
    fscanf(arquivo, " %99[^\n]%*c", artista.genero);
    fscanf(arquivo, " %99[^\n]%*c", artista.local);

    // Ler �lbuns
    artista.albums = NULL;
    artista.numAlbums = 0;
    char buffer[100];
    while (fscanf(arquivo, " %99[^\n]%*c", buffer) == 1 && strcmp(buffer, "===========\n") != 0) {
        artista.numAlbums++;
        artista.albums = realloc(artista.albums, sizeof(char *) * artista.numAlbums);
        artista.albums[artista.numAlbums - 1] = strdup(buffer);
    }

    return artista;
}

// Fun��o para imprimir os detalhes de um artista
void imprimirArtista(Artista artista) {
    printf("Nome: %s\n", artista.nome);
    printf("G�nero: %s\n", artista.genero);
    printf("Local: %s\n", artista.local);
    printf("�lbuns:\n");
    for (int i = 0; i < artista.numAlbums; i++) {
        printf("  %s\n", artista.albums[i]);
    }
}

// Fun��o para adicionar um artista � lista
void adicionarArtista(Artista **artistas, int *numArtistas, Artista novoArtista) {
    (*numArtistas)++;
    *artistas = realloc(*artistas, sizeof(Artista) * (*numArtistas));
    (*artistas)[*numArtistas - 1] = novoArtista;
}

// Fun��o para comparar dois artistas pelo nome (para a busca bin�ria)
int compararArtistas(const void *a, const void *b) {
    return strcmp(((Artista *)a)->nome, ((Artista *)b)->nome);
}

int main() {

    setlocale(LC_ALL,"");

    FILE *arquivo = fopen("artistas.txt", "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo artistas.txt");
        return 1;
    }

    // Ler artistas do arquivo e armazen�-los em uma lista
    Artista *artistas = NULL;
    int numArtistas = 0;
    while (!feof(arquivo)) {
        numArtistas++;
        artistas = realloc(artistas, sizeof(Artista) * numArtistas);
        artistas[numArtistas - 1] = lerArtista(arquivo);
    }
    fclose(arquivo);

    int escolha;
    do {
        printf("\nMenu:\n");
        printf("1. Inser��o de novo artista\n");
        printf("2. Remo��o de artista\n");
        printf("3. Edi��o de artista\n");
        printf("4. Buscar artista\n");
        printf("5. Buscar �lbum\n");
        printf("6. Sair\n");
        printf("Escolha uma op��o: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1: {
                // Implementa��o da inser��o ordenada de novo artista

                Artista novoArtista;
                printf("Nome do novo artista: ");
                scanf(" %99[^\n]%*c", novoArtista.nome);
                printf("G�nero do novo artista: ");
                scanf(" %99[^\n]%*c", novoArtista.genero);
                printf("Local de origem do novo artista: ");
                scanf(" %99[^\n]%*c", novoArtista.local);

                // Ler �lbuns do novo artista
                novoArtista.numAlbums = 0;
                novoArtista.albums = NULL;
                printf("Digite os �lbuns do novo artista (digite 'fim' para encerrar):\n");
                char buffer[100];
                while (1) {
                    scanf(" %99[^\n]%*c", buffer);
                    if (strcmp(buffer, "fim") == 0) {
                        break;
                    }
                    novoArtista.numAlbums++;
                    novoArtista.albums = realloc(novoArtista.albums, sizeof(char *) * novoArtista.numAlbums);
                    novoArtista.albums[novoArtista.numAlbums - 1] = strdup(buffer);
                }

                // Adicionar o novo artista � lista e orden�-la
                adicionarArtista(&artistas, &numArtistas, novoArtista);
                qsort(artistas, numArtistas, sizeof(Artista), compararArtistas);

                // Abrir o arquivo em modo de escrita e reescrever o conte�do atualizado
                arquivo = fopen("artistas.txt", "w");
                if (arquivo == NULL) {
                    perror("Erro ao abrir o arquivo artistas.txt");
                    return 1;
                }
                for (int i = 0; i < numArtistas; i++) {
                    fprintf(arquivo, "Nome: %s\n", artistas[i].nome);
                    fprintf(arquivo, "G�nero: %s\n", artistas[i].genero);
                    fprintf(arquivo, "Local: %s\n", artistas[i].local);
                    for (int j = 0; j < artistas[i].numAlbums; j++) {
                        fprintf(arquivo, "%s\n", artistas[i].albums[j]);
                    }
                    fprintf(arquivo, "===========\n");
                }
                fclose(arquivo);

                printf("Novo artista inserido com sucesso.\n");
                break;
            }
            case 2: {
                // Implementa��o da remo��o de artista

                char nomeParaRemover[100];
                printf("Digite o nome do artista que deseja remover: ");
                scanf(" %99[^\n]%*c", nomeParaRemover);

                int indiceParaRemover = -1;
                for (int i = 0; i < numArtistas; i++) {
                    if (strcmp(artistas[i].nome, nomeParaRemover) == 0) {
                        indiceParaRemover = i;
                        break;
                    }
                }

                if (indiceParaRemover != -1) {
                    // Remover o artista da lista
                    free(artistas[indiceParaRemover].albums);
                    for (int i = indiceParaRemover; i < numArtistas - 1; i++) {
                        artistas[i] = artistas[i + 1];
                    }
                    numArtistas--;

                    // Abrir o arquivo em modo de escrita e reescrever o conte�do atualizado
                    arquivo = fopen("artistas.txt", "w");
                    if (arquivo == NULL) {
                        perror("Erro ao abrir o arquivo artistas.txt");
                        return 1;
                    }
                    for (int i = 0; i < numArtistas; i++) {
                        fprintf(arquivo, "Nome: %s\n", artistas[i].nome);
                        fprintf(arquivo, "G�nero: %s\n", artistas[i].genero);
                        fprintf(arquivo, "Local: %s\n", artistas[i].local);
                        for (int j = 0; j < artistas[i].numAlbums; j++) {
                            fprintf(arquivo, "%s\n", artistas[i].albums[j]);
                        }
                        fprintf(arquivo, "===========\n");
                    }
                    fclose(arquivo);

                    printf("Artista removido com sucesso.\n");
                } else {
                    printf("Artista n�o encontrado.\n");
                }
                break;
            }
            case 3: {
                // Implementa��o da edi��o de artista

                char nomeParaEditar[100];
                printf("Digite o nome do artista que deseja editar: ");
                scanf(" %99[^\n]%*c", nomeParaEditar);

                int indiceParaEditar = -1;
                for (int i = 0; i < numArtistas; i++) {
                    if (strcmp(artistas[i].nome, nomeParaEditar) == 0) {
                        indiceParaEditar = i;
                        break;
                    }
                }

                if (indiceParaEditar != -1) {
                    Artista novoArtista;
                    printf("Novo nome do artista: ");
                    scanf(" %99[^\n]%*c", novoArtista.nome);
                    printf("Novo g�nero do artista: ");
                    scanf(" %99[^\n]%*c", novoArtista.genero);
                    printf("Novo local de origem do artista: ");
                    scanf(" %99[^\n]%*c", novoArtista.local);

                    // Ler novos �lbuns do artista
                    novoArtista.numAlbums = 0;
                    novoArtista.albums = NULL;
                    printf("Digite os novos �lbuns do artista (digite 'fim' para encerrar):\n");
                    char buffer[100];
                    while (1) {
                        scanf(" %99[^\n]%*c", buffer);
                        if (strcmp(buffer, "fim") == 0) {
                            break;
                        }
                        novoArtista.numAlbums++;
                        novoArtista.albums = realloc(novoArtista.albums, sizeof(char *) * novoArtista.numAlbums);
                        novoArtista.albums[novoArtista.numAlbums - 1] = strdup(buffer);
                    }

                    // Atualizar o artista na lista
                    free(artistas[indiceParaEditar].albums);
                    artistas[indiceParaEditar] = novoArtista;

                    // Abrir o arquivo em modo de escrita e reescrever o conte�do atualizado
                    arquivo = fopen("artistas.txt", "w");
                    if (arquivo == NULL) {
                        perror("Erro ao abrir o arquivo artistas.txt");
                        return 1;
                    }
                    for (int i = 0; i < numArtistas; i++) {
                        fprintf(arquivo, "Nome: %s\n", artistas[i].nome);
                        fprintf(arquivo, "G�nero: %s\n", artistas[i].genero);
                        fprintf(arquivo, "Local: %s\n", artistas[i].local);
                        for (int j = 0; j < artistas[i].numAlbums; j++) {
                            fprintf(arquivo, "%s\n", artistas[i].albums[j]);
                        }
                        fprintf(arquivo, "===========\n");
                    }
                    fclose(arquivo);

                    printf("Artista editado com sucesso.\n");
                } else {
                    printf("Artista n�o encontrado.\n");
                }
                break;
            }
            case 4: {
                // Implementa��o da busca bin�ria por artista
                // Lembre-se de que a lista deve estar ordenada pelo nome para usar a busca bin�ria

                char nomeParaBuscar[100];
                printf("Digite o nome do artista que deseja buscar: ");
                scanf(" %99[^\n]%*c", nomeParaBuscar);

                int indiceArtistaEncontrado = -1;
                // Implemente a busca bin�ria aqui e atribua o �ndice do artista encontrado a 'indiceArtistaEncontrado'
                int inicio = 0;
                int fim = numArtistas - 1;
                while (inicio <= fim) {
                    int meio = (inicio + fim) / 2;
                    int comparacao = strcmp(artistas[meio].nome, nomeParaBuscar);
                    if (comparacao == 0) {
                        indiceArtistaEncontrado = meio;
                        break;
                    } else if (comparacao < 0) {
                        inicio = meio + 1;
                    } else {
                        fim = meio - 1;
                    }
                }

                if (indiceArtistaEncontrado != -1) {
                    printf("Artista encontrado:\n");
                    imprimirArtista(artistas[indiceArtistaEncontrado]);
                } else {
                    printf("Artista n�o encontrado.\n");
                }
                break;
            }
            case 5: {
                // Implementa��o da busca sequencial por �lbum

                char nomeAlbum[100];
                printf("Digite o nome do �lbum que deseja buscar: ");
                scanf(" %99[^\n]%*c", nomeAlbum);

                int albumEncontrado = 0;
                printf("Artistas com o �lbum '%s':\n", nomeAlbum);
                for (int i = 0; i < numArtistas; i++) {
                    for (int j = 0; j < artistas[i].numAlbums; j++) {
                        if (strcmp(artistas[i].albums[j], nomeAlbum) == 0) {
                            imprimirArtista(artistas[i]);
                            albumEncontrado = 1;
                            break;
                        }
                    }
                }

                if (!albumEncontrado) {
                    printf("Nenhum artista encontrado com o �lbum '%s'.\n", nomeAlbum);
                }
                break;
            }
            case 6:
                printf("Saindo do programa.\n");
                break;
            default:
                printf("Op��o inv�lida. Tente novamente.\n");
        }
    } while (escolha != 6);

    // Liberar a mem�ria alocada para os artistas e seus �lbuns
    for (int i = 0; i < numArtistas; i++) {
        for (int j = 0; j < artistas[i].numAlbums; j++) {
            free(artistas[i].albums[j]);
        }
        free(artistas[i].albums);
    }
    free(artistas);

    return 0;
}
