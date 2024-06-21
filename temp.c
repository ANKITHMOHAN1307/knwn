#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_DIRECTIONS 8

enum direction { NORTH, EAST, SOUTH, WEST, NORTHEAST, SOUTHEAST, SOUTHWEST, NORTHWEST };

struct room {
  int has_exit;  // Flag indicating if this room has the exit
  int has_key;   // Flag indicating if this room has the key
  struct room* exits[NUM_DIRECTIONS];  // Array of pointers to rooms in each direction (can be NULL)
};

// Function prototypes
struct room* create_room();
void link_rooms(struct room* room1, struct room* room2, enum direction dir);
void print_room(struct room* room, enum direction from);

int main() {
  srand(time(NULL));  // Seed random number generator

  // Create the starting room
  struct room* current_room = create_room();

  // Create additional rooms (optional, adjust number)
  for (int i = 0; i < 2; i++) {
    struct room* new_room = create_room();
    link_rooms(current_room, new_room, rand() % NUM_DIRECTIONS);
    current_room = new_room;
  }

  // Randomly place the exit and potentially a key
  current_room->has_exit = rand() % 2;
  current_room->has_key = rand() % 2;

  // Start exploring the room from the beginning
  print_room(current_room, NORTH);

  return 0;
}

// Creates a new room with no exits or key initially
struct room* create_room() {
  struct room* room = malloc(sizeof(struct room));
  room->has_exit = 0;
  room->has_key = 0;
  for (int i = 0; i < NUM_DIRECTIONS; i++) {
    room->exits[i] = NULL;
  }
  return room;
}

// Links two rooms in a specific direction
void link_rooms(struct room* room1, struct room* room2, enum direction dir) {
  room1->exits[dir] = room2;
  // Since this is a non-maze structure, link back for two-way movement
  room2->exits[(dir + 4) % NUM_DIRECTIONS] = room1;
}

// Prints information about the current room and explores connected rooms
void print_room(struct room* room, enum direction from) {
  printf("You are in a room.\n");
  if (room->has_exit) {
    printf("There is an exit here!\n");
  }
  if (room->has_key) {
    printf("You found a key here!\n");
  }

  for (int i = 0; i < NUM_DIRECTIONS; i++) {
    if (room->exits[i] != NULL) {
      enum direction next_dir = (from + i) % NUM_DIRECTIONS;
      const char* dir_names[] = {"North", "East", "South", "West", "Northeast", "Southeast", "Southwest", "Northwest"};
      printf("There is a passage to the %s.\n", dir_names[next_dir]);
      print_room(room->exits[i], next_dir);
    }
  }
}
