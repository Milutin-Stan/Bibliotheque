#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Fonctions prototypes des Adherents
void ajout_personne(FILE*);
void modifier_nom_personne(FILE*,FILE*);
void supprimer_personne(FILE*,FILE*);


//Fonctions prototypes des Livres
void ajout_livre(FILE*);
void modifier_titre_livre(FILE*,FILE*);
void modifier_auteur_livre(FILE*,FILE*);
void supprimer_livre(FILE*,FILE*);


//Fonction menu
void menu(FILE*,FILE*,FILE*,FILE*);

//Fonction de tri
void tri(FILE*,FILE*);
void tri_livre(FILE*,FILE*);

//Fonction d'emprunts
void emprunt(FILE*, FILE*, FILE*);
void rendre_livre(FILE*,FILE*);


//Deffinir le type de structure globale pour les Adherents
typedef struct {
  int adh_Index;
  char adh_Nom[15];
  int adh_NbEmprunts;
}SAdherent;

//Deffinir le type de structure globale pour les Adherents
typedef struct{
  int liv_Index;
  char liv_Titre[20];
  char liv_Auteur[15];
} SLivre;

int Index = 0;

void main(){

//Ouvrir les fichiers .txt pour les adherents et les livres

FILE *file_adh; //Pointeur du fichier .txt des Adherents

  file_adh = fopen("adh.txt","r+");
    if (file_adh == NULL){
      printf("Le fichier n'a pas pu être ouvert");
      exit(1);
    }

FILE *file_liv; //Pointeur du fichier .txt des Livres

file_liv = fopen("liv.txt","r+");
  if (file_liv == NULL){
    printf("Le fichier n'a pas pu être ouvert");
    exit(1);
  }

FILE *filec; //Declarer le pointeur du fichier de copie

  filec = fopen("copie.txt","r+");
    if (filec == NULL){
      printf("Le fichier n'a pas pu être ouvert");
      exit(1);
    }

FILE *filecl; //Declarer le pointeur du fichier de copie

    filecl = fopen("lcopie.txt","r+");
    if (filecl == NULL){
      printf("Le fichier n'a pas pu être ouvert");
      exit(1);
    }


menu(file_adh,file_liv,filec,filecl);

fclose(file_adh);
fclose(file_liv);
fclose(filec);
fclose(filecl);

}
////////////////////////////////////////////////////////////////////////////////
void ajout_personne(FILE *rep){

    fseek(rep, 0, SEEK_END); //Mettre le pointeur a la fin du fichier

    SAdherent Adherent; //Deffinir une variable type contact

    FILE *file_index; //Pointeur du fichier .txt pour la sauvegarde des Index

    file_index = fopen("save.txt","r+");
    if (file_index == NULL){
      printf("Le fichier n'a pas pu être ouvert");
      exit(1);
    }
    fseek(file_index, 0, SEEK_SET);//Mettre le pointeur au debut du fichier

//Entrer les infos du contact puis les mettre dans le fichier
    printf("Entrez le nom de la personne : ");
      scanf("%s",Adherent.adh_Nom);

//Copie sur le file
    fprintf(rep,"%s ",Adherent.adh_Nom);

    fscanf(file_index, "%d ",&Index);//Scaner le dernier chiffre utilisé

    //Assigner un code pour l'adherent
      Adherent.adh_Index = Index +1;
        fprintf(rep,"%d \n",Adherent.adh_Index);

        fseek(file_index, 0, SEEK_SET);//Remettre le pointeur au debut du fichier
          fprintf(file_index,"%d ",Adherent.adh_Index);//Ecraser la sauvegarde

fclose(file_index);
}
////////////////////////////////////////////////////////////////////////////////
void modifier_nom_personne(FILE *rep,FILE *repc){

  fseek(rep, 0, SEEK_SET); //Remettre le pointeur au debut du fichier

  SAdherent Adherent; //Deffinir une variable type contact

    char search[15];//Le nom que on veut changer
    char new[15]; //Nouveau nom
    char c; //Variable qui copira char par char de filec sur file
    int comp; //Retour du strcmp

    printf("Entrez le nom a changer : ");
      scanf("%s",search);

    printf("Entrez le nouveau nom : ");
      scanf("%s",new);

    fseek(rep, 0, SEEK_SET); //Remettre le pointeur au debut du fichier

//Mettre toutes les infos sur un fichier de copie en filtrant les selements que on veux supprimer
    while (feof(rep) == 0){

      fscanf(rep, "%s %d \n",Adherent.adh_Nom,&Adherent.adh_Index);

      comp = strcmp(search,Adherent.adh_Nom); //Comparer les 2 chaines

        if (comp != 0){
          fprintf(repc,"%s ",Adherent.adh_Nom);
          fprintf(repc,"%d \n",Adherent.adh_Index);
        }
        else if (comp == 0){
          strcpy(Adherent.adh_Nom,new); //Le nouveau nom prends la place de l'ancien
          fprintf(repc,"%s ",Adherent.adh_Nom);
          fprintf(repc,"%d \n",Adherent.adh_Index);
        }
    }

    fseek(rep, 0, SEEK_SET); //Remettre le pointeur au debut du fichier
    fseek(repc, 0, SEEK_SET); //Remettre le pointeur au debut du fichier

  while (1){ //Copier les info du fichier de copier et remplacer les a la place du fichier originel

      c = fgetc(repc);

        if (c == EOF){   //Si on arive a la fin du fichier arreter le procesus
          break;
        }
        else{
          putc(c,rep);
        }
      }
    }
////////////////////////////////////////////////////////////////////////////////
void supprimer_personne(FILE* rep,FILE *repc){

  fseek(rep, 0, SEEK_SET); //Remettre le pointeur au debut du fichier

  SAdherent Adherent; //Deffinir une variable type contact

    char search[15];//Le nom que on veut changer
    char new[15] = "zzz"; //Nouveau nom
    char c; //Variable qui copira char par char de filec sur file
    int comp; //Retour du strcmp

    printf("Entrez le nom a supprimer : ");
      scanf("%s",search);


    fseek(rep, 0, SEEK_SET); //Remettre le pointeur au debut du fichier

  //Mettre toutes les infos sur un fichier de copie en filtrant les selements que on veux supprimer
    while (feof(rep) == 0){

      fscanf(rep, "%s %d \n",Adherent.adh_Nom,&Adherent.adh_Index);

      comp = strcmp(search,Adherent.adh_Nom); //Comparer les 2 chaines

        if (comp != 0){
          fprintf(repc,"%s ",Adherent.adh_Nom);
          fprintf(repc,"%d \n",Adherent.adh_Index);
        }
        else if (comp == 0){
          strcpy(Adherent.adh_Nom,new); //Le nouveau nom prends la place de l'ancien
          fprintf(repc,"%s ",Adherent.adh_Nom);
          fprintf(repc,"%d \n",Adherent.adh_Index);
        }
    }

    fseek(rep, 0, SEEK_SET); //Remettre le pointeur au debut du fichier
    fseek(repc, 0, SEEK_SET); //Remettre le pointeur au debut du fichier

  while (1){ //Copier les info du fichier de copier et remplacer les a la place du fichier originel

      c = fgetc(repc);

        if (c == EOF){   //Si on arive a la fin du fichier arreter le procesus
          break;
        }
        else{
          putc(c,rep);
        }
      }
    }

////////////////////////////////////////////////////////////////////////////////
                   //Fonctions pour la structure SLivres
////////////////////////////////////////////////////////////////////////////////

void ajout_livre(FILE* lrep){

  fseek(lrep, 0, SEEK_END); //Mettre le pointeur a la fin du fichier

  SLivre Livre; //Deffinir une variable type contact

  //Entrer les infos du contact puis les mettre dans le fichier
  printf("Entrez le Titre du Livre : ");
    scanf("%s",Livre.liv_Titre);

  //Copie sur le file
  fprintf(lrep,"%s ",Livre.liv_Titre);

  printf("Entrez l'auteur du Livre : ");
    scanf("%s",Livre.liv_Auteur);

  //Copie sur le file
  fprintf(lrep,"%s ",Livre.liv_Auteur);

  //Index NULL
  int x = 0;
  fprintf(lrep,"%d \n",x);

  }
///////////////////////////////////////////////////////////////////////////////
void modifier_titre_livre(FILE *lrep,FILE *lrepc){

fseek(lrep, 0, SEEK_SET); //Remettre le pointeur au debut du fichier

SLivre Livre; //Deffinir une variable type contact

  char search[15];//Le titre que on veut changer
  char new[15]; //Nouveau titre
  char c; //Variable qui copira char par char de filec sur file
  int comp; //Retour du strcmp

  printf("Entrez le titre a changer : ");
    scanf("%s",search);

  printf("Entrez le nouveau titre : ");
    scanf("%s",new);

  fseek(lrep, 0, SEEK_SET); //Remettre le pointeur au debut du fichier

//Mettre toutes les infos sur un fichier de copie en filtrant les selements que on veux supprimer
  while (feof(lrep) == 0){

    fscanf(lrep, "%s %s %d \n",Livre.liv_Titre,Livre.liv_Auteur,&Livre.liv_Index);

    comp = strcmp(search,Livre.liv_Titre); //Comparer les 2 chaines

      if (comp != 0){
        fprintf(lrepc,"%s ",Livre.liv_Titre);
        fprintf(lrepc,"%s \n",Livre.liv_Auteur);
        fprintf(lrepc,"%d \n",Livre.liv_Index);
      }
      else if (comp == 0){
        strcpy(Livre.liv_Titre,new); //Le nouveau nom prends la place de l'ancien
        fprintf(lrepc,"%s ",Livre.liv_Titre);
        fprintf(lrepc,"%s \n",Livre.liv_Auteur);
        fprintf(lrepc,"%d \n",Livre.liv_Index);
      }
  }

  fseek(lrep, 0, SEEK_SET); //Remettre le pointeur au debut du fichier
  fseek(lrepc, 0, SEEK_SET); //Remettre le pointeur au debut du fichier

while (1){ //Copier les info du fichier de copier et remplacer les a la place du fichier originel

    c = fgetc(lrepc);

      if (c == EOF){   //Si on arive a la fin du fichier arreter le procesus
        break;
      }
      else{
        putc(c,lrep);
      }
    }
  }
///////////////////////////////////////////////////////////////////////////////////
void modifier_auteur_livre(FILE *lrep,FILE *lrepc){

  SLivre Livre; //Deffinir une variable type contact

    char search[15];//Le titre que on veut changer
    char new[15]; //Nouveau titre
    char c; //Variable qui copira char par char de filec sur file
    int comp; //Retour du strcmp

    printf("Entrez le nom de l'auteur a changer : ");
      scanf("%s",search);

    printf("Entrez le nouveau nom d'auteur : ");
      scanf("%s",new);

    fseek(lrep, 0, SEEK_SET); //Remettre le pointeur au debut du fichier
    fseek(lrepc, 0, SEEK_SET); //Remettre le pointeur au debut du fichier

  //Mettre toutes les infos sur un fichier de copie en filtrant les selements que on veux supprimer
    while (feof(lrep) == 0){

      fscanf(lrep, "%s %s %d \n",Livre.liv_Titre,Livre.liv_Auteur,&Livre.liv_Index);

      comp = strcmp(search,Livre.liv_Auteur); //Comparer les 2 chaines

        if (comp != 0){
          fprintf(lrepc,"%s ",Livre.liv_Titre);
          fprintf(lrepc,"%s ",Livre.liv_Auteur);
          fprintf(lrepc,"%d \n",Livre.liv_Index);
        }
        else if (comp == 0){
          fprintf(lrepc,"%s ",Livre.liv_Titre);
          strcpy(Livre.liv_Auteur,new); //Le nouveau nom prends la place de l'ancien
          fprintf(lrepc,"%s ",Livre.liv_Auteur);
          fprintf(lrepc,"%d \n",Livre.liv_Index);
        }
    }

    fseek(lrep, 0, SEEK_SET); //Remettre le pointeur au debut du fichier
    fseek(lrepc, 0, SEEK_SET); //Remettre le pointeur au debut du fichier

  while (1){ //Copier les info du fichier de copier et remplacer les a la place du fichier originel

      c = fgetc(lrepc);

        if (c == EOF){   //Si on arive a la fin du fichier arreter le procesus
          break;
        }
        else{
          putc(c,lrep);
        }
      }
}
////////////////////////////////////////////////////////////////////////////////////////
void supprimer_livre(FILE *lrep,FILE *lrepc){

  fseek(lrep, 0, SEEK_SET); //Remettre le pointeur au debut du fichier

  SLivre Livre; //Deffinir une variable type contact

    char search[15];//Le titre que on veut changer
    char new[15] = "zzz"; //Nouveau titre
    char c; //Variable qui copira char par char de filec sur file
    int comp; //Retour du strcmp

    printf("Entrez le nom de l'auteur a supprimer : ");
      scanf("%s",search);

    fseek(lrep, 0, SEEK_SET); //Remettre le pointeur au debut du fichier
    fseek(lrepc, 0, SEEK_SET); //Remettre le pointeur au debut du fichier

  //Mettre toutes les infos sur un fichier de copie en filtrant les selements que on veux supprimer
    while (feof(lrep) == 0){

      fscanf(lrep, "%s %s %d \n",Livre.liv_Titre,Livre.liv_Auteur,&Livre.liv_Index);

      comp = strcmp(search,Livre.liv_Auteur); //Comparer les 2 chaines

        if (comp != 0){
          fprintf(lrepc,"%s ",Livre.liv_Titre);
          fprintf(lrepc,"%s ",Livre.liv_Auteur);
          fprintf(lrepc,"%d \n",Livre.liv_Index);
        }
        else if (comp == 0){
          strcpy(Livre.liv_Titre,new);
          fprintf(lrepc,"%s ",Livre.liv_Titre);
          strcpy(Livre.liv_Auteur,new);
          fprintf(lrepc,"%s ",Livre.liv_Auteur);
          fprintf(lrepc,"%d \n",Livre.liv_Index);
        }
    }

    fseek(lrep, 0, SEEK_SET); //Remettre le pointeur au debut du fichier
    fseek(lrepc, 0, SEEK_SET); //Remettre le pointeur au debut du fichier

  while (1){ //Copier les info du fichier de copier et remplacer les a la place du fichier originel

      c = fgetc(lrepc);

        if (c == EOF){   //Si on arive a la fin du fichier arreter le procesus
          break;
        }
        else{
          putc(c,lrep);
        }
      }
  }
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
void tri(FILE *rep,FILE *repc){

  SAdherent Adherent[10];
 int i;
  fseek(rep,0,SEEK_SET);

  //Affecter les valeurs sauvegardées dans le file .txt dans les variables
  for(i = 0; feof(rep)==0 ;i++){

    fscanf(rep,"%s %d \n",Adherent[i].adh_Nom,&Adherent[i].adh_Index);

  }
  //Faire le tri au debut du programme
  int indrech;
  SAdherent inter;
  int comp;
  int echange;
  char c;

  do{

    echange = 0;

    for(indrech=0;indrech<i;indrech++){

      if (comp = strcmp(Adherent[indrech].adh_Nom,Adherent[indrech+1].adh_Nom)<0){


        inter = Adherent[indrech+1];
        Adherent[indrech+1] = Adherent[indrech];
        Adherent[indrech] = inter;

        echange = 1;
      }
    }
  }while (echange == 1);

  //Imprimer le tri dans les file .txt

  for(int a = i; a>0 ;a--){

    printf("%s %d \n",Adherent[a].adh_Nom,Adherent[a].adh_Index);
  }
}
////////////////////////////////////////////////////////////////////////////////
void tri_livre(FILE *lrep,FILE *lrepc){

  SLivre Livres[10];

 int i;
  fseek(lrep,0,SEEK_SET);

  //Affecter les valeurs sauvegardées dans le file .txt dans les variables
  for(i = 0; feof(lrep)==0 ;i++){

    fscanf(lrep,"%s %s %d \n",Livres[i].liv_Titre,Livres[i].liv_Auteur,&Livres[i].liv_Index);

  }
  //Faire le tri au debut du programme
  int indrech;
  SLivre inter;
  int comp;
  int echange;
  char c;

  do{

    echange = 0;

    for(indrech=0;indrech<i;indrech++){

      if (comp = strcmp(Livres[indrech].liv_Titre,Livres[indrech+1].liv_Titre)<0){


        inter = Livres[indrech+1];
        Livres[indrech+1] = Livres[indrech];
        Livres[indrech] = inter;

        echange = 1;
      }
    }
  }while (echange == 1);

  //Imprimer le tri dans les file .txt
  for(int a = 0; a<=i ;a++){

    printf("%s %s %d \n",Livres[a].liv_Titre,Livres[a].liv_Auteur,Livres[a].liv_Index);
  }
}
///////////////////////////////////////////////////////////////////////////////
void emprunt(FILE *rep, FILE *lrep, FILE *lrepc){

  SAdherent Adherent;//Deffinir une variable type contact
  SLivre Livre;//Deffinir une variable type contact

  char search[15];//Le nom du contact
  char search_livre[15];//Le titre du livre
  int comp; //Retour du strcmp
  char c;//Variable qui copira char par char de filec sur file
  int ind;

  //Demander a l'admin de choisir quel contact shouaite emprinter
  printf("Quel contact shouaite emprinter un livre ? :");
    scanf("%s",search);

    fseek(rep, 0, SEEK_SET); //Remettre le pointeur au debut du fichier

//On cherche a trouver l'Index du contact en question
  while (feof(rep)==0){

    fscanf(rep, "%s %d \n",Adherent.adh_Nom,&Adherent.adh_Index);

    comp = strcmp(search,Adherent.adh_Nom); //Comparer les 2 chaines

    if (comp == 0){

      printf("%s  existe \n",search);
      ind = Adherent.adh_Index;
    }
  }

//Demander quel livre veut t'il/elle emprinter
  printf("Quel livre voulez vous enprinter ? \n");
    scanf("%s",search_livre);

fseek(lrep, 0, SEEK_SET); //Remettre le pointeur au debut du fichier
fseek(lrepc, 0, SEEK_SET); //Remettre le pointeur au debut du fichier

//On cherche le livre en question
  while (feof(lrep)==0){

    fscanf(lrep, "%s %s %d \n",Livre.liv_Titre,Livre.liv_Auteur,&Livre.liv_Index);

      comp = strcmp(search_livre,Livre.liv_Titre); //Comparer les 2 chaines

      if (comp != 0){
        fprintf(lrepc,"%s ",Livre.liv_Titre);
        fprintf(lrepc,"%s ",Livre.liv_Auteur);
        fprintf(lrepc,"%d \n",Livre.liv_Index);
      }
      else if (comp == 0){
        fprintf(lrepc,"%s ",Livre.liv_Titre);
        fprintf(lrepc,"%s ",Livre.liv_Auteur);
        Livre.liv_Index = ind;
        fprintf(lrepc,"%d \n",Livre.liv_Index);

        printf("Livre empriné avec succes \n");
      }
  }

  fseek(lrep, 0, SEEK_SET); //Remettre le pointeur au debut du fichier
  fseek(lrepc, 0, SEEK_SET); //Remettre le pointeur au debut du fichier

while (1){ //Copier les info du fichier de copier et remplacer les a la place du fichier originel

    c = fgetc(lrepc);

      if (c == EOF){   //Si on arive a la fin du fichier arreter le procesus
        break;
      }
      else{
        putc(c,lrep);
      }
    }
}
////////////////////////////////////////////////////////////////////////////////
void rendre_livre(FILE *lrep,FILE *lrepc){

  SLivre Livre;//Deffinir une variable type contact

    char search[15];//Le titre que on veut changer
    char c; //Variable qui copira char par char de filec sur file
    int comp; //Retour du strcmp

  //Demander quel livre rendre
printf("Quel livre voulez vous rendre ? \n");
  scanf("%s",search);

  fseek(lrep, 0, SEEK_SET); //Remettre le pointeur au debut du fichier

  while (feof(lrep)==0){

    fscanf(lrep, "%s %s %d \n",Livre.liv_Titre,Livre.liv_Auteur,&Livre.liv_Index);

    comp = strcmp(search,Livre.liv_Titre); //Comparer les 2 chaines

    if (comp != 0){
      fprintf(lrepc,"%s ",Livre.liv_Titre);
      fprintf(lrepc,"%s ",Livre.liv_Auteur);
      fprintf(lrepc,"%d \n",Livre.liv_Index);
    }
    else if (comp == 0){
      fprintf(lrepc,"%s ",Livre.liv_Titre);
      fprintf(lrepc,"%s ",Livre.liv_Auteur);
      Livre.liv_Index = 0;
      fprintf(lrepc,"%d \n",Livre.liv_Index);

      printf("Le livre a bien été rendu \n");
    }
  }
  fseek(lrep, 0, SEEK_SET); //Remettre le pointeur au debut du fichier
  fseek(lrepc, 0, SEEK_SET); //Remettre le pointeur au debut du fichier

  while (1){ //Copier les info du fichier de copier et remplacer les a la place du fichier originel

    c = fgetc(lrepc);

      if (c == EOF){   //Si on arive a la fin du fichier arreter le procesus
        break;
      }
      else{
        putc(c,lrep);
      }
    }
}

//////////////////////////////////////////////////////////////////////////////////////
void menu(FILE *rep,FILE *lrep,FILE *repc,FILE *lrepc){

  int a; //Variable qui servira de chemin dans le menu

  //Afficher les options du menu
    printf("Options Adherents : (1) \n");
    printf("Options Livres : (2) \n");
    printf("Emprunt : (3) \n");
    printf("Rendre un livre : (4) \n");
    printf("Fermer le programme (9) \n");

      scanf("%d",&a); //Lire l'entré de l'utillisateur pour naviguer dans le menu

        if (a==1){
//Afficher le sous menu des Adherents
          a=0;
          printf("Ajouter un contact : (1) \n");
          printf("Modifier le nom du contact : (2) \n");
          printf("Supprimer un contact (3) \n");
          printf("Afficher tout les utillisateurs (4) \n");

              scanf("%d",&a); //Lire l'entré de l'utillisateur pour naviguer dans le menu

                if (a==1){
                    ajout_personne(rep);
                  }
                else if (a==2){
                    modifier_nom_personne(rep,repc);
                 }
                else if (a==3){
                    supprimer_personne(rep,repc);
                }
                else if (a==4){
                    tri(rep,repc);
                }
        }
        else if (a==2){
        //Afficher le sous menu des Livres
                  a=0;
                  printf("Ajouter un livre : (1) \n");
                  printf("Modifier le titre du livre : (2) \n");
                  printf("Modifier l'auteur du livre : (3) \n");
                  printf("Supprimer un livre (4) \n");
                  printf("Afficher tout les livres (5) \n");

                      scanf("%d",&a); //Lire l'entré de l'utillisateur pour naviguer dans le menu

                        if (a==1){
                            ajout_livre(lrep);
                          }
                        else if (a==2){
                            modifier_titre_livre(lrep,lrepc);
                         }
                        else if (a==3){
                            modifier_auteur_livre(lrep,lrepc);
                         }
                        else if (a==4){
                            supprimer_livre(lrep,lrepc);
                         }
                        else if (a==5){
                            tri_livre(lrep,lrepc);
                         }
                }

        else if (a==3){
            emprunt(rep,lrep,lrepc);
        }

        else if (a==4){
            rendre_livre(lrep,lrepc);
        }

}
