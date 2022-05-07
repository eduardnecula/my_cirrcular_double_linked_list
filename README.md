// Copyright 2021 Necula Eduard Ionut

~ Theme 1 SD ~


The program is implemented in 4 files:

1. Galaxi.c
2. CircularDoublyLinkedList.c
3. CircularDoublyLinkedList.h
4. utils.h


In Galaxi.c the action begins. The program reads the number of commands at the beginning.
Then read from stdin nr_commands;
Each command is implemented separately in the file CircularDoublyLinkedList.c, the function header can be found in CircularDoublyLinkedList.h
The orders are as follows:
1. ADD.
The following function is used for ADD:
void add (doubly_linked_list_t * list, int n, void * data, char * planet_name, int shield_nr);

The add function adds a node to position n in a double linked list, and initializes it with:
a) void * data: which can be either an int or another double linked list (shields of the planet).
b) planet_name: the name of the added planet
c) shield_nr: the number of shields the planet will have. The initial value of the shields is 1.

At the beginning of the main function in Galaxi.c, if the first command is ADD, it will proceed as follows:
A double chained list is created, representing the galaxy, which will have planets. For each added planet, a double chained list will be created that represents the shields of the planet.

2. BLH:
int swallow (doubly_linked_list_t * galaxy, int planet_index);

The BLH command is implemented by the swallow function.
The swallow function deletes a planet from the galaxy.
How it works: Search for the planet at planet_index. Once I find the planet, I isolate it from the rest of the planets, then erase it, first with the shields of the planet and then with the planet itself. If planet_index is 0 mute the head of the galaxy on the next element.
If I have only one planet and I give this command. I will delete the entire galaxy, and initialize it again when I receive a new ADD. Why did I do that? Because I was getting errors from invalid write size 8/4 and invalid read size 4/8.
The function returns -1 if I delete both planets. In Galaxi.c if I get - 1, it means I have to delete the galaxy, and do another one at ADD (possible).
(galaxy is the list of all planets)

3. UPG:
void upgrade (doubly_linked_list_t * galaxy, int planet_index, int shield_index, int shield_upg);

The UPG command is implemented by the upgrade function.
This command adds the value shield_upg to the shield at shield_index in planet_index.
How it works: Search for the planet in the position planet_index. Once I find the planet, I enter the list of shields. I cross the list of shields until I reach the shield_index index. After finding this index, I add shield_upg to this value.

4. EXP:
void add_shield (doubly_linked_list_t * galaxy, int planet_index, int shield_value);

The EXP command is implemented by the add_shield function.
This command adds a shield to a planet.
How it works: Search for the planet in the position planet_index. Once found, enter the list of shields. I cross the list of shields to the last element. When I get to the last shield, I assign a new node that I initialize with the value 1. After I initialize the new node, I add it to the list of shields of the planet, restoring the connections between the shields. (new node points to the first element, and the last last element points to the new node).

5. RMV:
void remove_shield (doubly_linked_list_t * galaxy, int planet_index, int shield_index);

The RMV command is implemented by the remove_shield function.
This command deletes the shield of a planet.
How it works: Search for the planet in the position planet_index. Once it is found, I enter the list of shields. I cross the list of shields to the shield_index position. This node found will be isolated from the rest of the list of shields, restore the connections between the shields and then delete the node.

6. COL:
int collide (doubly_linked_list_t * galaxy, int planet_index1, int planet_index2);

The COL command is implemented by the collide function.
This command hits 2 planets on each other, in a shield unit each.

How it works: For this function, the most important thing is to find the first planet, the second is at a distance. Searching for the first planet in planet_index1. Planet 2 is planet_index1-> next. After I found the planets. I enter the list of shields of the 2 planets. For planet 1 I enter the list of shields to the position size_planet1 / 4 and for planet 2 I enter the list of shields to the position [size_planet2 / 4] * 3. After I have found the positions of each, I decrease by 1 both values. We now have 3 possible cases:
1. Both shields have values ​​<0. In this case they erase both planets
2. The first planet has a shield with a value of <0. I delete the first planet and then reconnect.
3. The second planet has a shield with a value of <0. I delete the second planet and then reconnect.
The function returns the value 2 if they delete both planets from the galaxy. If I delete both planets from the galaxy, I will also delete the galaxy, and reset it if I receive more.c ADD command. If I have more than 2 plants and 2 planets are erased, I will not erase the galaxy.
(galaxy is the list of all planets)

7. ROT:
void rotate (doubly_linked_list_t * galaxy, int planet_index, char * the_way, int units);

The ROT command is implemented by the rotate function.
This command rotates the planet in a clockwise direction.
If the_way is not valid, a corresponding message is displayed.
How it works: Searching for the planet from the planet_index index. When I find the planet I see which way to go, "c" or "t" given by the_way. To know which position I am going to do: units% size_shields, size_shields representing the size of the planet's shields. Then I will move the head depending on what value the calculation gives me from behind.

8. SHW:
void show (doubly_linked_list_t * galaxy, int index_planet);
The SHW command is implemented by the SHW function.

This command displays information about the planet.
How it works: I search for the planet at index_planet, then display the appropriate information.

Auxiliary functions:
DIE: found in utils.h. I used this function every time I assigned something with malloc.

void dll_print_int_list (doubly_linked_list_t * list);
~ I use this function to display the list of shields in the SHW command.

void dll_free (doubly_linked_list_t ** pp_list);
~ I use this feature every time I want to erase an entire planet, including shields. I enter the list of shields, go from node to node, then delete them at the end and delete the list (planet).

void dll_galaxi (doubly_linked_list_t * galaxi);
~ This is the function that erases the entire galaxy. It travels from planet to planet, for each planet, clears the shield list, the planet itself, then moves to the next planet until the galaxy size is 0.


For each function I checked all the parameters, and if a parameter did not match I displayed a corresponding message.

Thanks for the correction :).