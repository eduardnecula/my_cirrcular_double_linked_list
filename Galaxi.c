// Copyright 2021 Necula Eduard Ionut
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Circular.h"


int main() {
	doubly_linked_list_t* galaxi = dll_create(sizeof(doubly_linked_list_t));
	int number_commands = -1, aux = 0;
	char command[MAX_COMMANDS];
	int am_sterg_galaxi = 0;  // daca sterg galaxia voi initializa cu 1
                              // altfel ramane pe 0 si se sterge la final

	scanf("%d", &number_commands);
	for (int i = 0; i < number_commands; ++i) {
		char planet_name[NAME_MAX_SIZE];
		int planet_index = -100, planet_index2 = -1;
		int shield_index = -100, shield_nr = 0;
        int shield_upg = 0, shield_value = 0;
		char the_way[30], blank = ' ';
		int units = -1;

		scanf("%s", command);
			if (strcmp(command, "ADD") == 0){
            	scanf("%s", planet_name);
            	scanf("%d", &planet_index);
            	scanf("%d", &shield_nr);
            	if (am_sterg_galaxi == 1) {
            		galaxi = dll_create(sizeof(doubly_linked_list_t));
            		am_sterg_galaxi = 0;
            	}
                if (planet_index > galaxi->size) {
                    printf("Planet out of bounds!\n");
                } else {
                    printf("The planet %s has joined the galaxy.\n",
                        planet_name);
                    doubly_linked_list_t* shields = dll_create(sizeof(int));
                    int initial_shield_value = 1;
                    int *init = &initial_shield_value;
                    for (int i = 0; i < shield_nr; i++) {
                        add(shields, i, init, planet_name, shield_nr);
                    }
                    add(galaxi, planet_index, shields, planet_name, shield_nr);
                    free(shields);
                }
        	}
        	if (strcmp(command, "BLH") == 0) {
        		scanf("%d", &planet_index);
        		if (am_sterg_galaxi != 1) {
        			aux = swallow(galaxi, planet_index);
        		} else {
        			printf("Planet out of bounds!\n");
        		}
            	if (aux != -1 && am_sterg_galaxi != 1) {
            		if (galaxi->size == 0) {
					   free(galaxi);
					   am_sterg_galaxi = 1;
            		}
            	}
        	}
        	if (strcmp(command, "UPG") == 0) {
            	scanf("%d", &planet_index);
            	scanf("%d", &shield_index);
            	scanf("%d", &shield_upg);
            	if (am_sterg_galaxi != 1) {
            		upgrade(galaxi, planet_index, shield_index, shield_upg);
            	} else {
            		printf("Planet out of bounds!\n");
            	}
        	}
        	if (strcmp(command, "EXP") == 0) {
            	scanf("%d", &planet_index);
            	scanf("%d", &shield_value);
            	if (am_sterg_galaxi != 1) {
            		add_shield(galaxi, planet_index, shield_value);
            	} else {
            		printf("Planet out of bounds!\n");
            	}
        	}
        	if (strcmp(command, "RMV") == 0) {
            	scanf("%d", &planet_index);
            	scanf("%d", &shield_index);
            	if (am_sterg_galaxi != 1) {
            		remove_shield(galaxi, planet_index, shield_index);
            	} else {
            		printf("Planet out of bounds!\n");
            	}
        	}
        	if (strcmp(command, "COL") == 0) {
            	scanf("%d", &planet_index);
            	scanf("%d", &planet_index2);
            	if (am_sterg_galaxi != 1) {
            		aux = collide(galaxi, planet_index, planet_index2);
                    // asta inseamna ca am sters ultimele 2 planete din lista
            		if (aux == 2) {
            			am_sterg_galaxi = 1;
            			free(galaxi);
            		}
            	} else {
            		printf("Planet out of bounds!\n");
            	}
        	}
        	if (strcmp(command, "ROT") == 0) {
            	scanf("%d", &planet_index);
            	scanf("%c", &blank);
            	scanf("%s", the_way);
            	scanf("%d", &units);
            	if (am_sterg_galaxi != 1) {
            		rotate(galaxi, planet_index, the_way, units);
            	} else {
            		printf("Planet out of bounds!\n");
            	}
        	}
        	if (strcmp(command, "SHW") == 0) {
            	scanf("%d", &planet_index);
            	if (am_sterg_galaxi != 1) {
            		show(galaxi, planet_index);
            	} else {
            		printf("Planet out of bounds!\n");
            	}
        	}
	}
	if (am_sterg_galaxi != 1) {
		if (galaxi->size > 0) {
			dll_galaxi(galaxi);
		}
	}
	if (am_sterg_galaxi == 0) {
        free(galaxi);
    }
	return 0;
}
