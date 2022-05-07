// Copyright 2021 Necula Eduard Ionut
#ifndef CIRCULAR_H_
#define CIRCULAR_H_

#define NAME_MAX_SIZE 30  // pentru dimensiunea maxima de caractere
#define MIN_SHIELDS 4  // dim de shield-uri minime
#define AUX -10  // initializare valori random pentru checker
#define MAX_COMMANDS 100  // dimensiunea maxima a unei comenzi

typedef struct dll_node_t dll_node_t;

struct dll_node_t
{
	char name[NAME_MAX_SIZE]; /*planet name*/
	int shields_nr; /*shields number*/
	int kills; /*for the number of the destroyed planets*/
    void* data;
    /* Pentru ca datele stocate sa poata avea orice tip, folosim un
                   pointer la void. */
    dll_node_t *prev, *next;
};

typedef struct doubly_linked_list_t doubly_linked_list_t;
struct doubly_linked_list_t
{
    dll_node_t* head;
    unsigned int data_size;
    int size;
};

// functia care creeaza si initializeaza o lista dubla inlantuita
doubly_linked_list_t*
dll_create(unsigned int data_size);

// functia care sterge o lista dubla inlantuita
void
dll_free(doubly_linked_list_t** pp_list);

// functia care printeaza lista
void
dll_print_int_list(doubly_linked_list_t* list);

// functia care adauga o planeta in galaxie
void
add_galaxi(doubly_linked_list_t* list, char* planet_name, int planet_index,
	int shields_nr);

// functia care arata detalii despre planeta
void
show(doubly_linked_list_t* galaxi, int planet_index);

// functie care printeaza scuturile unei planete
void
print_shield(doubly_linked_list_t *galaxi,  int planet_index);

// functia care da upgrade la indexul unei planete
void
upgrade(doubly_linked_list_t* galaxi, int planet_index, int shield_index,
	int shield_upg);

// functia care adauga in galaxie o planeta
void
add(doubly_linked_list_t* list, int n, void* data, char* planet_name,
	int shields_nr);

// functia care roteste intr-un sens o planeta
void
rotate(doubly_linked_list_t *galaxi, int  planet_index, char the_way[30],
	int units);

// functia care se ocupa de stersul galaxiei
void
dll_galaxi(doubly_linked_list_t* galaxi);

// functia care sterge un scut de la o planeta
void
remove_shield(doubly_linked_list_t* galaxi, int planet_index, int shield_index);

// functia care adauga unei planete un scut la final
void
add_shield(doubly_linked_list_t *galaxi, int planet_index, int shield_value);

// functa care sterge o planeta din galaxie
int
swallow(doubly_linked_list_t *galaxi, int planet_index);

// functia care se ocupa de ciocnirea a doua planete
int
collide(doubly_linked_list_t *galaxi, int planet_index, int planet_index2);

#endif  // CIRCULAR_H_
