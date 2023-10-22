#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Estrutura de n� da lista
struct Node {
    char artist[100];
    char song[100];
    struct Node* next;
    struct Node* prev;
};

// Fun��o para inserir um n� na lista
void insertNode(struct Node** head, char artist[], char song[]) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->artist, artist);
    strcpy(newNode->song, song);

    if (*head == NULL) {
        newNode->next = newNode;
        newNode->prev = newNode;
        *head = newNode;
    } else {
        struct Node* tail = (*head)->prev;
        newNode->next = *head;
        (*head)->prev = newNode;
        newNode->prev = tail;
        tail->next = newNode;
    }
}

// Fun��o para exibir a lista pela ordem de cadastro
void displayPlaylist(struct Node* head) {
    if (head == NULL) {
        printf("Playlist vazia.\n");
        return;
    }

    struct Node* current = head;
    do {
        printf("Artista: %s, M�sica: %s\n", current->artist, current->song);
        current = current->next;
    } while (current != head);
}

// Fun��o para exibir a lista ordenada pelo nome das m�sicas
void displaySortedPlaylist(struct Node* head) {
    if (head == NULL) {
        printf("Playlist vazia.\n");
        return;
    }

    // Copiar a lista para um array
    int count = 0;
    struct Node* current = head;
    do {
        count++;
        current = current->next;
    } while (current != head);

    struct Node* playlistArray[count];
    current = head;
    for (int i = 0; i < count; i++) {
        playlistArray[i] = current;
        current = current->next;
    }

    // Ordenar o array pelo nome das m�sicas
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (strcmp(playlistArray[i]->song, playlistArray[j]->song) > 0) {
                struct Node* temp = playlistArray[i];
                playlistArray[i] = playlistArray[j];
                playlistArray[j] = temp;
            }
        }
    }

    // Exibir a lista ordenada
    for (int i = 0; i < count; i++) {
        printf("Artista: %s, M�sica: %s\n", playlistArray[i]->artist, playlistArray[i]->song);
    }
}

// Fun��o para remover uma m�sica da playlist
void removeSong(struct Node** head, char song[]) {
    if (*head == NULL) {
        printf("Playlist vazia. N�o � poss�vel remover m�sicas.\n");
        return;
    }

    struct Node* current = *head;
    int removed = 0;

    do {
        if (strcmp(current->song, song) == 0) {
            if (current->next == current) {
                *head = NULL;
            } else {
                if (current == *head) {
                    *head = current->next;
                }

                current->prev->next = current->next;
                current->next->prev = current->prev;
            }
            free(current);
            removed = 1;
            break;
        }

        current = current->next;
    } while (current != *head);

    if (removed) {
        printf("M�sica removida com sucesso.\n");
    } else {
        printf("M�sica n�o encontrada na playlist.\n");
    }
}

// Fun��o para salvar a playlist no arquivo
void saveToFile(struct Node* head) {
    if (head == NULL) {
        printf("Playlist vazia. Nada para salvar.\n");
        return;
    }

    FILE* file = fopen("musicas.txt", "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    struct Node* current = head;
    do {
        fprintf(file, "%s;%s\n", current->artist, current->song);
        current = current->next;
    } while (current != head);

    fclose(file);
}

int main() {

    setlocale(LC_ALL,"");
    struct Node* playlist = NULL;
    char artist[100], song[100];
    char songName[100];

    // Carregar a playlist a partir do arquivo
    FILE* file = fopen("musicas.txt", "r");
    if (file != NULL) {
        while (fscanf(file, "%99[^;];%99[^\n]\n", artist, song) == 2) {
            insertNode(&playlist, artist, song);
        }
        fclose(file);
    }

    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Exibir a playlist pela ordem de cadastro\n");
        printf("2. Exibir a playlist ordenada pelo nome das m�sicas\n");
        printf("3. Inserir nova m�sica\n");
        printf("4. Remover uma m�sica\n");
        printf("5. Buscar por uma m�sica\n");
        printf("6. Avan�ar para a pr�xima m�sica\n");
        printf("7. Retornar � m�sica anterior\n");
        printf("8. Sair\n");
        printf("Escolha uma a��o: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayPlaylist(playlist);
                break;
            case 2:
                displaySortedPlaylist(playlist);
                break;
            case 3:
                printf("Digite o nome do artista: ");
                scanf(" %99[^\n]", artist);
                printf("Digite o nome da m�sica: ");
                scanf(" %99[^\n]", song);
                insertNode(&playlist, artist, song);
                saveToFile(playlist);
                printf("M�sica inserida com sucesso.\n");
                break;
            case 4:
                printf("Digite o nome da m�sica a ser removida: ");
                scanf(" %99[^\n]", songName);
                removeSong(&playlist, songName);
                saveToFile(playlist);
                break;
            case 5:
                printf("Digite o nome da m�sica a ser buscada: ");
                scanf(" %99[^\n]", songName);
                struct Node* found = playlist;
                do {
                    if (strcmp(found->song, songName) == 0) {
                        printf("Artista: %s, M�sica: %s\n", found->artist, found->song);
                        break;
                    }
                    found = found->next;
                } while (found != playlist);

                if (found == playlist) {
                    printf("M�sica n�o encontrada na playlist.\n");
                }
                break;
            case 6:
                playlist = playlist->next;
                break;
            case 7:
                playlist = playlist->prev;
                break;
            case 8:
                saveToFile(playlist);
                break;
            default:
                printf("Escolha inv�lida. Tente novamente.\n");
        }
    } while (choice != 8);

    return 0;
}
