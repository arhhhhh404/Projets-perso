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
        printf("Erreur d'allocation mémoire \n");
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
    printf("\n [+] - contact ajouter ! \n");
}

void chercher_contact(Contact *contacts, int taille) {
    char nom_rechercher[50];
    printf("Entrée le nom rechercher: ");
    scanf("%s", nom_rechercher);

    for(int i = 0; i < taille; i++) {
        if (strcmp(nom_rechercher, contacts[i].nom)) {
            printf("\n [?] - contact trouvé ! \n");
            printf("Nom       : %s", contacts[i].nom);
            printf("Prénom    : %s", contacts[i].prenom);
            printf("Téléphone : %s", contacts[i].telephone);
            printf("Email     : %s", contacts[i].email);
        }
        else{
            printf("\n [?] - contact introuvable \n");
        }
    }

}

void afficher_contact(Contact *contacts, int taille) {
    if (taille = 0) {
        printf("\n aucun contact \n");
        return;
    }

    for(int i = 0; i < taille; i++) {
        printf("\n | Contact | \n");
        printf("Nom       : %s", contacts[i].nom);
        printf("Prénom    : %s", contacts[i].prenom);
        printf("Téléphone : %s", contacts[i].telephone);
        printf("Email     : %s", contacts[i].email);
    }
}

int main() {
    Contact *contacts = NULL;
    int taille = 0;
    int choix;

    do {
        printf("\n ----------------------------< MENU >---------------------------- \n");
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
            supprimer_contact(&contacts, &taille);
            break;
        case 3:
            chercher_contact(contacts, taille);
            break;
        case 4:
            afficher_contacts(contacts, taille);
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