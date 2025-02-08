# Notre encodeur JPEG à nous

## Modules et répartition:
- paramcomm (Etienne):
    Récupère les paramètres en ligne de commande, les vérifie et les parse,
    puis les mets dans une SDD Entree.
    - Entrée: ligne de commande.
    - Sortie: Une SDD Entree.
- lecture_fichier (Jérémie):
    Permet de parser une image et de la mettre dans la SDD "Pgm" ou "Ppm". 
    La conversion RGB -> YCbCr à lieu ici.
    - Entrée : fichier .ppm/pgm
    - Sortie : La SDD Pgm ou Ppm si le parsage est réussi sinon NULL.
- decoupage_mcu (Jérémie):
    Découpage en MCU, sous-mcu et blocs, et downsampling La SDD "Pgm" et "Ppm" sont transformé 
    en "Mcu_pgm" et "Mcu_ppm".   
    - Entrée : La SDD Pgm ou Ppm.
    - Sortie : Le découpage sous la forme Mcu_Pgm ou Mcu_ppm.
- dct (Jérémie) :
    Applique la DCT sur une SDD Bloc.
    - Entrée : La SDD Bloc
    - Sortie : La SDD Bloc modifié.
- zig_zag (Jérémie):
    Créer un Bloc_ZZ à partir d'un Bloc.
    - Entrée : La SDD Bloc.
    - Sortie : Le Bloc_ZZ.
- quantification (Jérémie):
    Applique en place la quantification sur un Bloc_ZZ.
    - Entrée : Le Bloc_ZZ.
    - Sortie : Le Bloc_ZZ modifié.
- compression (Thomas):
    Fait la compression (supression des 0 puis application de Huffman) sur un bloc_ZZ et renvoie 
    une sdd de type Encode_composante.
    - Entrée : Le Bloc_ZZ.
    - Sortie : Encode_composante.
- table_huffman (Thomas):
    Génération des tables de Huffman pour la compression.
    - Entrée : Tables fournies dans htables.
    - Sortie : Tables de Huffman.

- ecriture_entete (Etienne):
    Ecrit les en-tête JPG dans un fichier.
    - Entrée : Table de Huffman et de quantification, et la SDD Entree 
    - Sortie : écriture dans le fichier.

- ecriture_flux (Etienne):
    - Entrée : Encode_composante
    - Sortie : le fichier avec le flux écrit.
  
- encodage (Jérémie, Thomas, Etienne):
    Gestion complete de l'encodage avec 0 erreurs Valgrind et tout est bien libéré.
    - Entrée : Sur la ligne de commande.
    - Sortie : Image au format JPG générée.


## Foncitons terminées

| Etape  | Difficulté annoncée         | Fin de tâche |
| :--------------- |:---------------| :-----:|
| Ecriture bit à bit dans le flux  |:star: :star: :star: :star:| :white_check_mark: |
| Ecriture en-tête JPEG  |:star: :star: :star: :star:| :white_check_mark: |
| Gestion des tables de Huffman  |:star: :star: :star: :star: :star:| :white_check_mark: |
| Gestion des paramètres sur la ligne de commande  |:star: :star: à :star: :star: :star:| :white_check_mark: |
| Découpage de l'image en MCUs, des MCUs en blocs  |:star: :star: :star: | :white_check_mark: |
| Lecture fichier PPM |:star: :star: à :star: :star: :star: :star:| :white_check_mark: |
| Conversion RGB vers YCbCr  |:star:| :white_check_mark: |
| *Downsampling*  |:star: :star: :star: :star:| :white_check_mark: |
| DCT  | :star: :star:| :white_check_mark: |
| Zig-zag |:star: :star:| :white_check_mark: |
| Quantification | :star:| :white_check_mark: |
| Gestion complète de l'encodage | :star: :star: à :star: :star: :star: :star: :star:| :white_check_mark: |


## Temps d'exécution selon les images 

### Pour les images en niveau de gris (PGM)

| Image en entrée  | Temps (s) |
| :--------------- |:---------------|
| invader.pgm  | 0.000205 |
| gris.pgm  | 0.006323 | 
| bisou.pgm  | 0.011252 | 
| complexite.pgm  | 0.212795 | 


### Pour les images en couleur (PPM)

| Image en entrée     | 1x1,1x1,1x1 | 1x2,1x2,1x2 | 2x2,1x1,1x1 | 2x2, 1x2, 1x2 |
| :---------------    | :-----      | :-----      | :-----      | :-----        | 
| zig-zag.pgm         | 0.034279s   | 0.034193s   | 0.022205s   | 0.027998s     |
| thumbs.ppm          | 0.014472s   | 0.015296s   | 0.009761s   | 0.011301s     |
| horizontal.ppm      | 0.015366s   | 0.015330s   | 0.010260s   | 0.010996s     |
| vertical.ppm        | 0.099703s   | 0.101075s   | 0.070986s   | 0.078075s     |
| shaun_the_shepp.ppm | 0.007390s   | 0.007388s   | 0.004758s   | 0.006568s     | 
| biiiiiig.ppm        | 2.594011s   | 2.645428s   | 1.582866s   | 1.966817s     |


## Liens utiles
- [Lien du sujet](https://formationc.pages.ensimag.fr/projet/jpeg/jpeg/)
- [DCT](https://codereview.stackexchange.com/questions/265527/faster-aan-algorithm-for-calculating-discrete-cosine-transform) version optimisée : pour toute question sur son fonctionnement il est conseillé de s'addresser directement à l'auteur. Il vous expliquera bien mieux que nous.
- Problème relationnel au sein du groupe ? Contactez [Pascal](https://fr.wikipedia.org/wiki/Pascal,_le_grand_fr%C3%A8re) !
- Besoin de prendre l'air ? Le [Mont Rachais](https://fr.wikipedia.org/wiki/Mont_Rachais) est accessible à pieds depuis la salle E301 !
- Un peu juste sur le projet à quelques heures de la deadline ? Le [Montrachet](https://www.vinatis.com/achat-vin-puligny-montrachet) peut faire passer l'envie à vos profs de vous mettre une tôle !

## Auteurs
- Jérémie Villepreux
- Etienne Fontbonne
- Thomas Démaret
