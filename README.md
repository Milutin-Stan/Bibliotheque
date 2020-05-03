# Bibliotheque
Premier mini projet en c

FR

Un mini projet qui a pour objectif de créer un systeme d'emprints de livres dans une bilbiotheque.
Ce projet est special car pour sauvegarder il fallait utilliser des documents text et non des bases de données.

Sachant que j'ai mal nommé mes fichiers je vais expliquer leurs rôles:

bibli: le main

save: comme une base de donné j'ai crée ce fichier pour sauvegarder des id (qui s'incrimentes a chaque creation d'un adherant) 

adh : les adherents sont stockés ici

liv : les livres sont stockés ici

copie et lcopie: le systèm de sauvegarde est assez special j'utillise donc les fichiers de copie pour copier ce qui ne sera pas changé et j'ajoute la valeur que je voulait changer puis je recolle tout dans le fichier de sauvegarde de base. Car j'ai eu des erreurs quand je voulait supprimer directement une valeur.

Pour les test: Le fichier est assez instable et supprimer les contenus des fichiers txt et la save (gardez au moins 0) peut regler cerains problemes.

Système d'emprunt : Vous avez peutetre remarqué que les livres ont des identifiants aussi c'est fait dans le but quand un adherant emprunte un livre le id du livre copie celui du adherant. Et quand on veut regarder quel livre un adherant a emprunté on peut voir quel livre partage son id et vise versa.

Difficultés rencontrés: comme je l'ai dit supprimer une valeur n'est pas assez simple donc je pensait transformer les identifiants des livres et des adherents en "zzz" comme ca ils apparesent en bas de la liste.

ENG

This mini project was created to simulate a library borowing system.
This project is special because there are no data bases and only .txt files.

Knowing I didn't properly name my docs here is a simple explenation:

bibli: basically the main

save: like a data base i made a file that saves a users id on creation (and auto increments itself)

adh : the users are saved here

liv : the books are saved here

copie et lcopie: the save system is special because you can't out right delete or modify a attribute so what I do is I copy the whole data on the copie or lcopie (for books) and only leave out the attribute that i want to change, and finaly put it all back in the main save.

Testing : The files are unstable so sometimes you will need to delete everything only keep a 0 in the save file.

The Borowing system: You maybe saw that the books have a id as well they are all at 0 and when a user borows a book the books id is changed to be the same as the users id. That way you can trace whitch user has which book and the other way around.

Incountered problems : Like I stated previusly it is hard to delete a attribute so when you delete a user you only transform his name into zzz so it goes down the list
