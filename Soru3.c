//Hafta 4 Veri Yapilari ve Algoritma Odevi Soru 3//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Düğüm yapısı (Her bir yazdırma işi)
typedef struct PrintJob {
    char fileName[50];
    struct PrintJob* next;
} PrintJob;

// Kuyruk yapısı (Ön ve Arka işaretçileri)
typedef struct Queue {
    PrintJob* front;
    PrintJob* rear;
} Queue;

// Fonksiyon prototipleri
void enqueuePrintJob(Queue* q, char* fileName);
void processNextJob(Queue* q);
void showQueue(Queue q);
void freeQueue(Queue* q);

int main() {
    // Kuyruğu başlat ve boş olarak ayarla
    Queue printQueue;
    printQueue.front = NULL;
    printQueue.rear = NULL;

    int choice = -1;
    char fileName[50];

    while (choice != 0) {
        printf("\n=== YAZICI KUYRUK SIMULASYONU ===\n");
        printf("1. Yeni Dosya Ekle (Enqueue)\n");
        printf("2. Yazdir (Process Job)\n");
        printf("3. Kuyrugu Goster\n");
        printf("0. Cikis\n");
        printf("Seciminiz: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Dosya adi: ");
            scanf("%s", fileName);
            enqueuePrintJob(&printQueue, fileName);
        } 
        else if (choice == 2) {
            processNextJob(&printQueue);
        } 
        else if (choice == 3) {
            showQueue(printQueue);
        } 
        else if (choice == 0) {
            freeQueue(&printQueue);
            printf("Programdan cikiliyor...\n");
        } 
        else {
            printf("Gecersiz secim! Tekrar deneyin.\n");
        }
    }

    return 0;
}

// 1. Kuyruğun sonuna yeni dosya ekleme (Enqueue)
void enqueuePrintJob(Queue* q, char* fileName) {
    PrintJob* newJob = (PrintJob*)malloc(sizeof(PrintJob));
    if (newJob == NULL) {
        printf("Bellek yetersiz!\n");
        return;
    }

    strcpy(newJob->fileName, fileName);
    newJob->next = NULL;

    // Eğer kuyruk boşsa, yeni eleman hem front hem de rear olur
    if (q->rear == NULL) {
        q->front = newJob;
        q->rear = newJob;
    } else {
        // Kuyruk boş değilse en arkaya ekle ve rear'ı güncelle
        q->rear->next = newJob;
        q->rear = newJob;
    }

    printf("'%s' yazdırma kuyruguna eklendi.\n", fileName);
}

// 2. Sıradaki dosyayı yazırma ve kuyruktan çıkarma (Dequeue)
void processNextJob(Queue* q) {
    // Kuyruk boş kontrolü
    if (q->front == NULL) {
        printf("Kuyruk bos! Yazdirilacak dosya yok.\n");
        return;
    }

    // En öndeki elemanı al
    PrintJob* temp = q->front;
    printf("Yazdiriliyor: %s\n", temp->fileName);

    // Front işaretçisini bir sonraki dosyaya kaydır
    q->front = q->front->next;

    // Eğer son eleman da silindiyse rear işaretçisini de NULL yap
    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp); // Belleği serbest bırak
}

// 3. Kuyruktaki tüm dosyaları yazdırma sırasına göre gösterme
void showQueue(Queue q) {
    if (q.front == NULL) {
        printf("Kuyruk bos!\n");
        return;
    }

    printf("\n--- YAZDIRMA KUYRUGU (Önden Arkaya) ---\n");
    PrintJob* current = q.front;
    int index = 1;

    while (current != NULL) {
        printf("%d. %s\n", index++, current->fileName);
        current = current->next;
    }
    printf("---------------------------------------\n");
}

// Program çıkışında kalan bellekleri temizleme
void freeQueue(Queue* q) {
    PrintJob* current = q->front;
    PrintJob* nextJob;

    while (current != NULL) {
        nextJob = current->next;
        free(current);
        current = nextJob;
    }

    q->front = NULL;
    q->rear = NULL;
}