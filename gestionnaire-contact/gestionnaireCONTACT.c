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
        printf("[!] - Erreur d'allocation mémoire \n");
        return;
    }

    printf("-   Nom: ");
    scanf("%s", (*contacts)[*taille].nom);
    printf("-   Prénom: ");
    scanf("%s", (*contacts)[*taille].prenom);
    printf("-   Téléphone: ");
    scanf("%s", (*contacts)[*taille].telephone);
    printf("-   Email: ");
    scanf("%s", (*contacts)[*taille].email);

    (*taille)++;
    printf("\n [+] - contact ajouter ! \n");
}

void supprimer_contact(Contact **contacts, int *taille) {
    char nom_suppr[50];
    printf(">   Entrée le nom à supprimer: ");
    scanf("%s", nom_suppr);

    int index = -1;
    for(int i = 0; i < *taille; i++) {
        if(strcmp(nom_suppr, (*contacts)[i].nom) == 0) {
            index = i;
            break;
        }        
    }

    if(index == -1) {
        printf("[!] - contact introuvable \n");
        return;
    }

    for(int i = index; i < *taille-1; i++) {
        (*contacts)[i] = (*contacts)[i+1];
    }

    *contacts = realloc(*contacts, (*taille-1)*sizeof(Contact));
    (*taille)--;
    printf("\n [-] - contact supprimer ! \n");
}

void chercher_contact(Contact *contacts, int taille) {
    char nom_rechercher[50];
    printf(">   Entrée le nom rechercher: ");
    scanf("%s", nom_rechercher);

    for(int i = 0; i < taille; i++) {
        if (strcmp(nom_rechercher, contacts[i].nom) == 0) {
            printf("\n [?] - contact trouvé ! \n");
            printf("- Nom       : %s\n", contacts[i].nom);
            printf("- Prénom    : %s\n", contacts[i].prenom);
            printf("- Téléphone : %s\n", contacts[i].telephone);
            printf("- Email     : %s\n", contacts[i].email);
        }
        else{
            printf("[!] - contact introuvable \n");
        }
    }
}

void afficher_contact(Contact *contacts, int taille) {
    if (taille == 0) {
        printf("[!] - aucun contact \n");
        return;
    }

    for(int i = 0; i < taille; i++) {
        printf("\n | Contact | \n");
        printf("- Nom       : %s\n", contacts[i].nom);
        printf("- Prénom    : %s\n", contacts[i].prenom);
        printf("- Téléphone : %s\n", contacts[i].telephone);
        printf("- Email     : %s\n", contacts[i].email);
    }
}

void enregistrer_fichier(Contact *contacts, int taille) {
    char nomFichier[100];
    printf(">   Entrer le nom du fichier: ");
    scanf("%s", nomFichier);

    FILE *fichier = fopen(nomFichier, "w");
    if (fichier == NULL) {
        printf("[!] - Erreur lors de l'ouverture du fichier \n");
        return;
    }

    for(int i = 0; i < taille; i++) {
        fprintf(fichier, "Nom: %s\n", contacts[i].nom);
        fprintf(fichier, "Prénom: %s\n", contacts[i].prenom);
        fprintf(fichier, "Téléphone: %s\n", contacts[i].telephone);
        fprintf(fichier, "Email: %s\n", contacts[i].email);
        fprintf(fichier, "--------------------------------------------\n");
    }

    fclose(fichier);
    printf("\n [:] - Contacts enregistrer dans '%s' !\n", nomFichier);
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
        printf("5. Enregistrer les contacts \n");
        printf("6. quitter \n");
        printf("> Votre choix : ");
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
            afficher_contact(contacts, taille);
            break;
        case 5:
            enregistrer_fichier(contacts, taille);
            break;
        case 6:
            printf("au revoir le s !!!");
            break;
        default:
            printf("Choix invalide...");
        }
        } while (choix != 5);

    free(contacts);
    return 0;
}