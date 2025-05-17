#include <stdio.h>

typedef struct {
    char nom[50];
    char prenom[50];
    char telephone[20];
    char email[100];
} Contact;

int main() {
    int choix;

    do{
        printf("\n --------------< MENU >--------------\n");
        printf("1. Ajouter un contact \n");
        printf("2. Supprimer un contact \n");
        printf("3. Chercher un contact \n");
        printf("4. Afficher tous les contacts \n");
        scanf("%d\n", &choix);

        if (choix == 1) {
            printf("[+] -> ajouter un contact\n");
        } else if (choix == 2){
            printf("[-] -> supprimer un contact\n");
        } else if (choix == 3){
            printf("[?] -> chercher un contact\n");
        } else if (choix == 4){
            printf("[A] -> tout les contact\n");
        } else {
            printf("[!] -> choix invalide, réessayez...\n");
        }
    } while(choix != 5);

    return 0;
}