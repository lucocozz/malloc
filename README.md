# Malloc

La fonction `malloc()` de la bibliothèque standard C permet de réserver de l'espace mémoire dynamique dans le tas (heap en anglais) en utilisant des algorithmes de gestion de mémoire. L'algorithme de first fit consiste à parcourir la liste des blocs de mémoire libres jusqu'à trouver un bloc assez grand pour satisfaire la demande d'allocation. Pour implémenter cet algorithme, le système d'exploitation peut utiliser des fonctions comme `mmap()` et `munmap()`, qui permettent respectivement de mapper et démapper des fichiers ou des segments de mémoire dans l'espace d'adressage d'un processus.

La mémoire est généralement divisée en pages de taille fixe, généralement de l'ordre de kilo-octets. Certaines implémentations de `malloc()` utilisent des pages de différentes tailles pour gérer des demandes d'allocation de différentes tailles. Par exemple, on peut avoir des pages TINY pour les demandes d'allocation inférieures à 128 octets, des pages SMALL pour les demandes comprises entre 128 et 1024 octets, et des pages LARGE pour les demandes supérieures à 1024 octets.

Lorsqu'un programme libère de la mémoire en utilisant la fonction `free()`, cela peut entraîner la fragmentation de la mémoire en plusieurs petits blocs libres qui ne peuvent pas être réutilisés pour de nouvelles allocations de grande taille. Pour éviter cela, certains gestionnaires de mémoire utilisent une technique de défragmentation qui consiste à réunir les petits blocs libres en un seul bloc plus grand.

La fonction `realloc()` permet de redimensionner un bloc de mémoire déjà alloué. Si la nouvelle taille est plus grande que la taille actuelle, `realloc()` alloue un nouveau bloc de mémoire et copie les données du bloc existant dans le nouveau bloc avant de libérer l'ancien bloc. Si la nouvelle taille est plus petite, `realloc()` simplement modifie la taille du bloc existant sans en créer un nouveau.

<br/>

## **mmap(), munmap()**

`mmap()` et `munmap()` sont des fonctions qui permettent de mapper des fichiers ou des sections de mémoire dans l'espace d'adressage du processus. `mmap()` crée une association entre un fichier ou une zone de mémoire et une zone de l'espace d'adressage du processus, tandis que `munmap()` supprime cette association. Ces fonctions peuvent être utilisées comme une alternative à `malloc()` et `free()` pour la gestion de la mémoire dans un programme.

Voici un exemple d'utilisation de `mmap()` et `munmap()` :

```C
#include <sys/mman.h>

// Allouer une zone de mémoire de 1024 octets
void* ptr = mmap(NULL, 1024, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

// Utiliser la mémoire allouée

// Libérer la mémoire
munmap(ptr, 1024);
```

`mmap()` prend en entrée la taille de la zone de mémoire à allouer, ainsi que des indicateurs de protection et de mode d'utilisation. `munmap()` prend en entrée le pointeur vers la zone de mémoire à libérer, ainsi que sa taille.

Il est important de noter que `mmap()` et `munmap()` ne font pas partie de la bibliothèque standard C et ne sont donc pas disponibles sur tous les systèmes. Ils sont généralement utilisés pour des besoins spécifiques de gestion de la mémoire, tels que la mapping de fichiers ou la création de zones de mémoire partagées entre plusieurs processus.
