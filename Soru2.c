//Hafta 4 Veri Yapilari ve Algoritma Odevi Soru 2//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Kelime düğüm yapısı (Stack)
typedef struct Word {
    char text[50];
    struct Word* next;
} Word;

// Fonksiyon prototipleri
void pushWord(Word** top, char* text);
void popWord(Word** top);
void showWords(Word* top);
void freeStack(Word** top);

int main() {
    Word* top = NULL; // Stack'in en üst elemanını tutan işaretçi
    char command[20];
    char text[50];

    printf("=== UNDO (GERI ALMA) SIMULASYONU ===\n");
    printf("Kullanilabilir komutlar:\n");
    printf("  add <kelime> : Kelime ekler\n");
    printf("  undo         : Son eklenen kelimeyi geri alir\n");
    printf("  show         : Kelimeleri gosterir\n");
    printf("  exit         : Programdan cikar\n");
    printf("------------------------------------\n");

    while (1) {
        printf("> ");
        scanf("%s", command);

        if (strcmp(command, "add") == 0) {
            scanf("%s", text); // Komuttan sonra gelen kelimeyi oku
            pushWord(&top, text);
        } 
        else if (strcmp(command, "undo") == 0) {
            popWord(&top);
        } 
        else if (strcmp(command, "show") == 0) {
            showWords(top);
        } 
        else if (strcmp(command, "exit") == 0) {
            freeStack(&top);
            printf("Programdan cikiliyor...\n");
            break;
        } 
        else {
            printf("Gecersiz komut! (add, undo, show, exit)\n");
        }
    }

    return 0;
}

// 1. Stack'in en üstüne kelime ekleme (Push)
void pushWord(Word** top, char* text) {
    Word* newWord = (Word*)malloc(sizeof(Word));
    if (newWord == NULL) {
        printf("Bellek yetersiz!\n");
        return;
    }

    strcpy(newWord->text, text);
    newWord->next = *top; // Yeni kelime eski top'ı gösterir
    *top = newWord;       // Top artık yeni kelime olur
}

// 2. Stack'in en üstündeki kelimeyi çıkarma/geri alma (Pop)
void popWord(Word** top) {
    if (*top == NULL) {
        printf("Geri alinacak kelime yok! (Stack bos)\n");
        return;
    }

    Word* temp = *top;     // En üstteki elemanı geçici değişkene al
    *top = (*top)->next;   // Top'ı bir altındaki elemana kaydır
    
    printf("Geri alindi: %s\n", temp->text);
    free(temp);            // Belleği serbest bırak
}

// 3. Kelimeleri sırayla ekrana yazırma
// Stack yapısında son giren ilk çıktığı için, kelimeleri ilk eklenenden 
// son eklenene doğru (düzgün sırada) yazdırmak üzere yardımcı bir fonksiyon kullanılır.
void printHelper(Word* node) {
    if (node == NULL) return;
    printHelper(node->next); // Önce altındaki elemanları yazdır (Özyineleme/Recursion)
    printf("%s ", node->text);
}

void showWords(Word* top) {
    if (top == NULL) {
        printf("Metin bos!\n");
        return;
    }

    printf("Metin: ");
    printHelper(top);
    printf("\n");
}

// Program kapanırken belleği temizleme
void freeStack(Word** top) {
    Word* current = *top;
    Word* nextWord;

    while (current != NULL) {
        nextWord = current->next;
        free(current);
        current = nextWord;
    }

    *top = NULL;
}