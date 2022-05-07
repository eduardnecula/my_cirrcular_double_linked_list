// Copyright 2021 Necula Eduard Ionut
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Circular.h"
#include "utils.h"

#define MIN_SHIELDS 4
#define AUX -10

/*
 * Functie care trebuie apelata pentru initializarea si alocarea listei.
 */
doubly_linked_list_t*
dll_create(unsigned int data_size) {
    doubly_linked_list_t* list = malloc(sizeof(doubly_linked_list_t));
    DIE(list == NULL, "faill to alloc mem for list");
    list->size = 0;
    list->head = NULL;
    list->data_size = data_size;

    return list;
}

/*
    Functia care printeaza valorile int ale unei liste.
*/
void
dll_print_int_list(doubly_linked_list_t* list)
{
    dll_node_t* aux = list->head;
    int size = list->size;
    while (aux != NULL && size > 0) {
        printf("%d ", *((int *)(aux->data)));
        aux = aux->next;
        size--;
    }
    printf("\n");
}

/*
    Functia care adauga scuturi unei planete
*/
doubly_linked_list_t*
shields(char* planet_name, int shield_nr) {
    doubly_linked_list_t* shields = dll_create(sizeof(dll_node_t));
    int initial_shield_value = 1;
    int *init = &initial_shield_value;
    for (int i = 0; i < shield_nr; i++) {
        add(shields, i, init, planet_name, shield_nr);
    }
    return shields;
}

/*
    Functia roteste planeta in sens orar sau sens trigonometric, in functie
    de litera pe care o primeste, cu units pozitii
*/
void
rotate(doubly_linked_list_t *galaxi, int  planet_index, char the_way[30],
    int units) {
    if ((strcmp(the_way, "t") != 0) && (strcmp(the_way, "c") != 0)) {
        printf("Not a valid direction!\n");
        return;
    }
    if (planet_index > galaxi->size) {
        printf("Planet out of bounds!\n");
        return;
    }
    dll_node_t* planet = (dll_node_t *)galaxi->head;
    int aux_planet_index = planet_index;
    // ma plimb din planeta in planeta
    while (aux_planet_index) {
        planet = planet->next;
        aux_planet_index--;
    }
    // cand ajung la planeta potrivita, intru pe scuturi
    doubly_linked_list_t* shields = (doubly_linked_list_t *)planet->data;
    int size_shields = shields->size;
    // intru pe lista de scuturi
    dll_node_t* aux_head_shields = (dll_node_t *)shields->head;
    int nr_pozitii = units % size_shields;
    int copy = nr_pozitii;
    if (strcmp(the_way, "c") != 0) {
        while (nr_pozitii) {
            aux_head_shields = aux_head_shields->next;
            nr_pozitii--;
        }
        shields->head = aux_head_shields;
    } else {
        while (copy) {
            aux_head_shields = aux_head_shields->prev;
            copy--;
        }
        shields->head = aux_head_shields;
    }
}

void
add_shield(doubly_linked_list_t *galaxi, int planet_index, int shield_value) {
    int *pass = &shield_value;
    if (planet_index >= galaxi->size) {
        printf("Planet out of bounds!\n");
        return;
    }
    dll_node_t* planet = (dll_node_t *)galaxi->head;
    int aux_planet_index = planet_index;
    // ma plimb din planeta in planeta
    while (aux_planet_index) {
        planet = planet->next;
        aux_planet_index--;
    }
    // cand ajung la planeta potrivita, intru pe scuturi
    doubly_linked_list_t* shields = (doubly_linked_list_t *)planet->data;
    int size_shields = shields->size;
    dll_node_t* head_shields = shields->head;
    int aux_shield_index = size_shields - 1;
    while (aux_shield_index) {
        head_shields = head_shields->next;
        aux_shield_index--;
    }
    // acum ca am ajuns la capat trebuie sa adaug noul scut, pe care il aloc
    dll_node_t* new_node = NULL;
    dll_node_t* first_node = head_shields->next;
    new_node = malloc(sizeof(dll_node_t));
    DIE(new_node == NULL, "failed to alocate new_node");
    new_node->data = malloc(sizeof(int));
    DIE(new_node->data == NULL, "failed to alocate new_node->data");
    memcpy(new_node->data, pass, sizeof(int));

    // adaug scutul la finalul listei de scuturi a planetei
    head_shields->next = new_node;
    new_node->next = first_node;
    new_node->prev = head_shields;
    first_node->prev = new_node;
    shields->size++;
}

/*
    Functia care adauga scutului unei planete valoarea shield_upg
*/

void
upgrade(doubly_linked_list_t* galaxi, int planet_index, int shield_index,
    int shield_upg) {
    if (planet_index > galaxi->size) {
        printf("Planet out of bounds!\n");
        return;
    }
    dll_node_t* planet = galaxi->head;
    int aux_planet_index = planet_index;
    // ma plimb din planeta in planeta
    while (aux_planet_index) {
        planet = planet->next;
        aux_planet_index--;
    }
    // cand ajung la planeta potrivita, intru pe scuturi
    doubly_linked_list_t* shields = planet->data;
    int size_shields = shields->size;
    if (shield_index > size_shields) {
        printf("Shield out of bounds!\n");
        return;
    }
    // caut indexul de la scutul potrivit si upgradez cu shield_upg
    dll_node_t* head_shields = shields->head;
    int aux_shield_index = shield_index;
    while (aux_shield_index) {
        head_shields = head_shields->next;
        aux_shield_index--;
    }
    int *element = (int *)head_shields->data;
    *element += shield_upg;
}

/*
    Functia care sterge un scut de la o planeta.
*/
void remove_shield(doubly_linked_list_t* galaxi, int planet_index,
    int shield_index) {
    if (planet_index >= galaxi->size) {
        printf("Planet out of bounds!\n");
        return;
    }
    dll_node_t* planet = galaxi->head;
    int aux_planet_index = planet_index;
    // ma plimb din planeta in planeta
    while (aux_planet_index) {
        planet = planet->next;
        aux_planet_index--;
    }

    doubly_linked_list_t* shields = planet->data;
    int size_shields = shields->size;  // fata de index, are 1 in plus
    if (shield_index >= size_shields) {
        printf("Shield out of bounds!\n");
        return;
    }
    if (size_shields <= MIN_SHIELDS) {
        printf("A planet cannot have less than 4 shields!\n");
        return;
    }
    // intru pe lista de scuturi si caut pozitia shield_index
    dll_node_t* head_shields = shields->head;
    int aux_shield_index = shield_index;
    while (aux_shield_index) {
        head_shields = head_shields->next;
        aux_shield_index--;
    }

    dll_node_t* prev_node = head_shields->prev;
    dll_node_t* next_node = head_shields->next;

    // dupa ce sterg scutul planetei, refac legaturile intre noduri
    if (shield_index == 0) {
        next_node->prev = prev_node;
        prev_node->next = next_node;

        free(head_shields->data);
        free(head_shields);
        shields->head = next_node;
    } else {
        prev_node->next = next_node;
        next_node->prev = prev_node;
        free(head_shields->data);
        free(head_shields);
    }
    shields->size--;
}

/*
    Functie care sterge o planeta de la pozitia planet_index
*/
int swallow(doubly_linked_list_t *galaxi, int planet_index) {
    dll_node_t* planet = NULL;
    if (planet_index >= galaxi->size) {
        printf("Planet out of bounds!\n");
        return -1;
    }

    planet = galaxi->head;
    int aux_planet_index = planet_index;
    // ma plimb din planeta in planeta
    while (aux_planet_index) {
        planet = planet->next;
        aux_planet_index--;
    }
    dll_node_t* before = planet->prev;
    dll_node_t* after = planet->next;

    printf("The planet %s has been eaten by the vortex.\n", planet->name);
    galaxi->size--;
    // in functie de ce nod sterg refac conexiunile intre planete
    if (galaxi->size == 1) {
        galaxi->head = before;
    } else if (galaxi->size > 1){
        if (planet_index == 0) {
            before->next = after;
            after->prev = before;
            galaxi->head = after;
        } else {
            before->next = after;
            after->prev = before;
        }
    }
    // acum ca am ajuns la vortex trebuie sa sterg toate scuturile
    // cand ajung la planeta potrivita, intru pe scuturi
    doubly_linked_list_t* shields = planet->data;
    dll_free(&shields);
    free(planet);
    return 0;
}

/*
    Functia care se ocupa de ciocnirea planetelor.
    In caz ca 2 planete se distrug intre
*/
int
collide(doubly_linked_list_t *galaxi, int planet_index1, int planet_index2) {
    if (planet_index1 > galaxi->size || planet_index2 > galaxi->size) {
        printf("Planet out of bounds!\n");
        return -1;
    }
    dll_node_t* planet1 = galaxi->head;
    dll_node_t* planet2 = NULL;
    int copy_element = AUX;  // valoare auxiliara
    int copy_element2 = AUX;  // valoare auxiliara
    int copy_galaxi_size = AUX;  // valoare auxiliara
    // pentru planetele before si after cand sterg
    dll_node_t* before1, *after1, *before2, *after2;

    int aux_planet_index = planet_index1;
    // ma plimb din planeta in planeta
    while (aux_planet_index) {
        planet1 = planet1->next;
        aux_planet_index--;
    }
    // acum sunt la planeta potrivita
    // setez nodurile auxiliare de care o sa am nevoie atunci cand
    // voi lovi planetele
    planet2 = planet1->next;  // planet2 este fix dupa planet1
    before1 = planet1->prev;
    after1 = planet1->next;
    before2 = planet2->prev;
    after2 = planet2->next;

    // intru pe shield-urile celor 2 planete
    doubly_linked_list_t* shields1 = planet1->data;
    int size_shields1 = shields1->size;
    doubly_linked_list_t* shields2 = planet1->next->data;
    int size_shields2 = shields2->size;

    // setez head pentru planet 1 si pentru planet 2
    dll_node_t* head_shields = shields1->head;
    dll_node_t* head_shields2 = shields2->head;

    // CAUT SCUTUL DE PE POZIZITA [SIZE / 4] PENTRU PLANET 1
    int aux_shield_index = size_shields1 / 4;
    while (aux_shield_index) {
        head_shields = head_shields->next;
        aux_shield_index--;
    }
    // CAUT SCUTUL DE PE POZITIA [SIZE / 4] * 3 PENTRU PLANET 2
    int aux_shield_index2 = (size_shields2 / 4) * 3;
    while (aux_shield_index2) {
        head_shields2 = head_shields2->next;
        aux_shield_index2--;
    }
    // In *element pastrez valoarea scutului planetei 1 dupa lovire
    // In element2 pastrez valoarea scutului planetei 2 dupa lovire
    int *element = (int *)head_shields->data;
    int *element2 = (int *)head_shields2->data;
    *element = *element - 1;
    *element2 = *element2 - 1;

    // folosesc dimensiunea galaxiei, valoarea scut 1 si valoarea scut 2
    copy_galaxi_size = galaxi->size;
    copy_element = *element;
    copy_element2 = *element2;

    // cazul in care ambele planete mor si in lista am doar 2 elemente
    // in acest caz sterg ambele elemente
    // si anunt ca trebuie sa se faca o galaxie noua (return 2)
    if (copy_element < 0 && copy_element2 < 0) {
        // cazul in care sterg planetele de la inceput si size_galaxi = 3
        if (copy_galaxi_size == 3 && planet_index1 == 0) {
            galaxi->head = after2;
        } else if (copy_galaxi_size > 3 && planet_index1 == 0) {
            before1->next = after2;
            after2->prev = before1;
            galaxi->head = after2;
        } else if (copy_galaxi_size > 3) {
            before1->next = after2;
            after2->prev = before1;
        }
    } else if (copy_element < 0) {  // cazul in care doar planet 1 se sterge
        if (planet_index1 == 0 && galaxi->size == 2) {
            galaxi->head = after1;
        } else if (planet_index1 == 0 && galaxi->size > 2){
            after1->prev = before1;
            before1->next = after1;
            galaxi->head = after1;
        } else if (galaxi->size > 2) {
            after1->prev = before1;
            before1->next = after1;
        }
    } else if (copy_element2 < 0) {  // cazul in care doar planet 2 se sterge
        if (copy_galaxi_size > 2) {
            before2->next = after2;
            after2->prev = before2;
        }
    }
    // STERG PLANETA 1 DACA UN SHIELD ESTE < 0
    if (*element < 0) {
        planet2->kills++;
        printf("The planet %s has imploded.\n", planet1->name);
        galaxi->size--;
        dll_free(&shields1);  // sterg scuturile planetei 1
    }
    // STERG PLANETA 2 DACA UN SHIELD ESTE  < 0
    if (*element2 < 0) {
        galaxi->size--;
        planet1->kills++;
        printf("The planet %s has imploded.\n", planet2->name);
        dll_free(&shields2);
    }
     // cazul in care in galaxie sunt 2 planete care se distrug reciproc
    if (copy_element < 0 && copy_element2 < 0 && copy_galaxi_size == 2) {
        free(planet2);
        free(planet1);
        return 2;
        // cazul in care in planete sunt mai mult de 3 planete, iar 2 se distrug
    } else if (copy_galaxi_size >= 3 && copy_element < 0 && copy_element2 < 0) {
        free(planet2);
        free(planet1);
    } else if (copy_element < 0){  // daca sterg planeta 1
        free(planet1);
    } else if (copy_element2 < 0){  // daca sterg planeta 2
        free(planet2);
    }
    return 0;
}

/*
    Functia care adauga intr-o lista o planeta, pe indexul n
*/
void
add(doubly_linked_list_t* list, int n, void* data, char *planet_name,
    int shield_nr) {
    /* TODO */
    dll_node_t *new_node;
    if (n < 0) {
    	return;
    }
    if (list == NULL) {
    	printf("lista e goala\n");
    }

    // initiez nodul cu valorile initiale
    new_node = malloc(sizeof(dll_node_t));
    DIE(new_node == NULL, "failed to alocate new_node");
    snprintf(new_node->name, sizeof(new_node->name), "%s", planet_name);
    new_node->kills = 0;
    new_node->shields_nr = shield_nr;
    new_node->data = malloc(list->data_size);
    DIE(new_node->data == NULL, "failed to alocate new_node->data");
    memcpy(new_node->data, data, list->data_size);
    new_node->next = NULL;
    new_node->prev = NULL;

    // in functie de pozitia unde am adaugat nodul in lista
    if (list->head == NULL) {   // daca lista este neinitializata
    	list->head = new_node;  // adaug la head
    	list->head->next = list->head;
    	list->head->prev = list->head;
    	list->size++;
    } else {
    	if (n == 0) {  // daca adaug pe pozitia 0
            if (list->size == 1) {
                new_node->next = list->head;
                new_node->prev = list->head;
                list->head->next = new_node;
                list->head->prev = new_node;
                list->head = new_node;
            } else {
                dll_node_t* last = list->head->prev;
                last->next = new_node;
                new_node->next = list->head;
                list->head->prev = new_node;
                new_node->prev = last;
                list->head = new_node;
            }
    	} else if (n == 1) {  // daca adaug pe pozitia 1
    		dll_node_t *temp = list->head;
    		dll_node_t *front = list->head->next;
    		temp->next = new_node;
    		new_node->prev = list->head;
    		new_node->next = front;
    		front->prev = new_node;

    	} else if (n >= 2 && n < (list->size + 1)) {  // adaug incepand
    	   dll_node_t *temp = list->head;             // cu pozitia 2
    	   dll_node_t *forward;
    	   dll_node_t *copy_temp;
    	   int copy_n = n;
    	   while ((copy_n > 1) && (temp != NULL)) {
    		  temp = temp->next;
    		  copy_n--;
    	   }
    	   copy_temp = temp;
    	   forward = temp->next;
    	   temp->next = new_node;
    	   new_node->prev = copy_temp;
    	   new_node->next = forward;
    	   forward->prev = new_node;
    	} else if (n >= (list->size + 1)) {  // daca adaug la final
    	   dll_node_t *last = list->head->prev;
    	   dll_node_t *copy_last = last;
    	   last->next = new_node;
    	   new_node->prev = copy_last;
    	   new_node->next = list->head;
    	   list->head->prev = new_node;
        }
        list->size++;
    }
}

/*
 Functia care afiseaza detaliile despre planeta cu indexul index_planet
*/
void show(doubly_linked_list_t* galaxi, int index_planet) {
    if ((1 + index_planet) > galaxi->size || index_planet < 0) {
        printf("Planet out of bounds!\n");
        return;
    }
    if (galaxi == NULL) {
        printf("Galaxi is NULL\n");
        return;
    }
    if (index_planet == 0) {  // info despre prima planeta
        doubly_linked_list_t* shield = galaxi->head->data;
        printf("NAME: %s\n", galaxi->head->name);
        if (galaxi->size == 1) {
            printf("CLOSEST: none\n");
        } else if (galaxi->size == 2) {
            printf("CLOSEST: %s\n", galaxi->head->next->name);
        } else if (galaxi->size >= 2) {
            printf("CLOSEST: ");
            printf("%s", galaxi->head->prev->name);
            printf(" and ");
            printf("%s\n", galaxi->head->next->name);
        }
        printf("SHIELDS: ");
        dll_print_int_list(shield);
        printf("KILLED: %d\n", galaxi->head->kills);
    }
    if (index_planet == 1) {  // info despre a doua planeta
        printf("NAME: %s\n", galaxi->head->next->name);
        if (galaxi->size == 2) {
            printf("CLOSEST: %s\n", galaxi->head->next->next->name);
        } else {
            printf("CLOSEST: ");
            printf("%s", galaxi->head->name);
            printf(" and ");
            printf("%s\n", galaxi->head->next->next->name);
        }
        printf("SHIELDS: ");
        dll_print_int_list(galaxi->head->next->data);
        printf("KILLED: %d\n", galaxi->head->next->kills);
    }
    if (index_planet >= 2) {  // info despre orice planeta cu index >= 2
        // ma plimb pana ajung la indexul dorit
        dll_node_t* aux = galaxi->head;
        int aux_planet_index = index_planet;
        while (aux != NULL && aux_planet_index != 0) {
            aux = aux->next;
            aux_planet_index--;
        }
        printf("NAME: %s\n", aux->name);
        printf("CLOSEST: ");
        printf("%s", aux->prev->name);
        printf(" and ");
        printf("%s\n", aux->next->name);
        printf("SHIELDS: ");
        dll_print_int_list(aux->data);
        printf("KILLED: %d\n", aux->kills);
    }
}

/*
 * Procedura elibereaza memoria folosita de toate nodurile din lista, iar la
 * sfarsit, elibereaza memoria folosita de structura lista.
 */
void
dll_free(doubly_linked_list_t** pp_list)
{
	doubly_linked_list_t *list = *pp_list;
	int size = list->size;
	dll_node_t* temp = list->head;
    dll_node_t* next = NULL;
        while (size) {
            free(temp->data);
            next = temp->next;
            free(temp);
            temp = next;
            size--;
        }
    free(*pp_list);
}

/*
    Functia care sterge toata galaxia, planeta cu planeta
*/
void dll_galaxi(doubly_linked_list_t* galaxi) {
    dll_node_t* head_galaxi = NULL;
    head_galaxi = galaxi->head;
    doubly_linked_list_t *planet_list = head_galaxi->data;
    int size_galaxi = galaxi->size;
    int size_planet = 0;

    dll_node_t* aux2 = NULL;
    dll_node_t* next = NULL;
    while (size_galaxi) {
        planet_list = head_galaxi->data;
        size_planet = planet_list->size;
        // voi sterge toate elementele din planeta
        dll_node_t* head_planet = planet_list->head;
        while (size_planet) {
            // sterg mai intai data din head
            free(head_planet->data);
            next = head_planet->next;
            free(head_planet);
            head_planet = next;
            size_planet--;
        }
        aux2 = head_galaxi->next;
        free(head_galaxi->data);
        free(head_galaxi);
        head_galaxi = aux2;
        size_galaxi--;
    }
}
