#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nom[50];
    char prenom[50];
    char telephone[20];
    char email[100];
} Contact;

void ajouter_contact(Contact **contacts, int *taille) {
    *contacts = realloc(*contacts, (*taille + 1)*sizeof(Contact));

    if (*contacts == NULL) {
        printf("Erreur d'allocation mémoire\n");
        return;
    }

    printf("Nom: ");
    scanf("%s", (*contacts)[*taille].nom);
    printf("Prénom: ");
    scanf("%s", (*contacts)[*taille].prenom);
    printf("Téléphon: ");
    scanf("%s", (*contacts)[*taille].telephone);
    printf("Email: ");
    scanf("%s", (*contacts)[*taille].email);

    (*taille)++;
    printf("[+] - contact ajouter !\n");
}



int main() {
    Contact *contacts = NULL;
    int taille = 0;
    int choix;

    do {
        printf("\n --------------< MENU >--------------\n");
        printf("1. Ajouter un contact \n");
        printf("2. Supprimer un contact \n");
        printf("3. Chercher un contact \n");
        printf("4. Afficher tous les contacts \n");
        printf("5. quitter \n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
        case 1:
            ajouter_contact(&contacts, &taille);
            break;
        case 2:
            supprimer_contact();
            break;
        case 3:
            chercher_contact();
            break;
        case 4:
            afficher_contacts();
            break;
        case 5:
            printf("au revoir le s !!!");
            break;        
        default:
            printf("Choix invalide...");
        }
        } while (choix != 5);

    free(contacts);
    return 0;
}