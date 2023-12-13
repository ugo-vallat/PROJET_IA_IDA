# PROJET IA
### Ugo VALLAT MUNOS ENZO

## Présentation
Ce projet a été réalisé dans le cadre de l'UE d'IA pour la partie symbolique.
Il contient de une implémentation de l'algorithme de recherche en profondeur bornée
et une implémentation de l'algorithme IDA*.

## Compilation
Pour compiler le main (avec l'interface utilisateur), exécuter la commande :
```bash
$ make
```

Pour compiler les tests :
```bash
$ make test_depth
$ make test_ida
```

## Lancement  

### Main  
```bash
$ ./bin/main
```


### Tests
```bash
$ ./bin/tdepth <num état départ> <num état but> <profondeur de recherche>
```

```bash
$ ./bin/tida <num état départ> <num état but> <num fonction heuristique> <numéro fonction poids>
```

Pour ida, le numéro de la fonction heuristique correspond à :  
    1 - Etat mal positionné  
    2 - Profondeur source  
    3 - Profondeur source + destination  
    4 - Mal positionné pour cas coup = id  

Pour ida, le numéro de la fonction poids correspond à :  
    1 - Coup 1  
    2 - Coup = id de l'anneau  


### Notes / remarques
Différents jeux de tests sont disponibles dont voici des recommandations d'utilisation:

Association des tests :   
    start -> end  
    1     -> 1,2  
    2     -> 3,4,5,6  
    3     -> 7  
    4     -> 8  
    5     -> 9  
    6     -> 10,11,12,13,14  
    7     -> 15  
