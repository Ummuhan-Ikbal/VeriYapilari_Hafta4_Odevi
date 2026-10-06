//Hafta 4 Veri Yapilari ve Algoritma Odevi Soru 1//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Song {
    char name[50];
    struct Song* next;
    struct Song* prev;
} Song;

// 1. Şarkı Ekleme (Listenin Sonuna)
void addSongToEnd(Song** head, char* name) {
    Song* newSong = (Song*)malloc(sizeof(Song));
    strcpy(newSong->name, name);
    newSong->next = NULL;
    newSong->prev = NULL;

    if (*head == NULL) {
        *head = newSong;
        return;
    }

    Song* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = newSong;
    newSong->prev = temp;
}

// 2. Şarkı Silme (Pratik Bağlantı Mantığı)
void removeSong(Song** head, char* name) {
    if (*head == NULL) {
        printf("Liste bos!\n");
        return;
    }

    Song* temp = *head;
    while (temp != NULL && strcmp(temp->name, name) != 0) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Sarki bulunamadi.\n");
        return;
    }

    // Sol ve sağındaki bağları güncelle
    if (temp->prev != NULL) temp->prev->next = temp->next;
    else *head = temp->next; // İlk eleman siliniyorsa head'i kaydır

    if (temp->next != NULL) temp->next->prev = temp->prev;

    free(temp);
    printf("'%s' silindi.\n", name);
}

// 3. Sonraki Şarkı
void playNext(Song** current) {
    if (*current == NULL) printf("Liste bos!\n");
    else if ((*current)->next != NULL) {
        *current = (*current)->next;
        printf("Caliniyor: %s\n", (*current)->name);
    } else printf("Son sarkidasiniz.\n");
}

// 4. Önceki Şarkı
void playPrevious(Song** current) {
    if (*current == NULL) printf("Liste bos!\n");
    else if ((*current)->prev != NULL) {
        *current = (*current)->prev;
        printf("Caliniyor: %s\n", (*current)->name);
    } else printf("Ilk sarkidasiniz.\n");
}

// 5. Listeyi Yazdır
void displayPlaylist(Song* head) {
    if (head == NULL) {
        printf("Liste bos!\n");
        return;
    }
    printf("\n--- CALMA LISTESI ---\n");
    for (Song* temp = head; temp != NULL; temp = temp->next) {
        printf("- %s\n", temp->name);
    }
}

int main() {
    Song* head = NULL;
    Song* current = NULL;
    int secim = -1;
    char isim[50];

    while (secim != 0) {
        printf("\n1:Ekle | 2:Sil | 3:İleri | 4:Geri | 5:Liste | 0:Cikis\nSecim: ");
        scanf("%d", &secim);

        if (secim == 1) {
            printf("Sarki adi: ");
            scanf(" %[^\n]", isim); // Satır sonuna kadar okur
            addSongToEnd(&head, isim);
            if (current == NULL) current = head; // İlk eklemede aktif şarkı başa geçer
        } else if (secim == 2) {
            printf("Silinecek sarki: ");
            scanf(" %[^\n]", isim);
            if (current && strcmp(current->name, isim) == 0) {
                current = current->next ? current->next : current->prev;
            }
            removeSong(&head, isim);
        } else if (secim == 3) {
            playNext(&current);
        } else if (secim == 4) {
            playPrevious(&current);
        } else if (secim == 5) {
            displayPlaylist(head);
            if (current) printf(">>> Su an calan: %s <<<\n", current->name);
        }
    }

    return 0;
}