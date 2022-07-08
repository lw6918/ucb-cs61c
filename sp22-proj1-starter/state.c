#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "snake_utils.h"
#include "state.h"

/* Helper function definitions */
static char get_board_at(game_state_t* state, int x, int y);
static void set_board_at(game_state_t* state, int x, int y, char ch);
static bool is_tail(char c);
static bool is_snake(char c);
static char body_to_tail(char c);
static int incr_x(char c);
static int incr_y(char c);
static void find_head(game_state_t* state, int snum);
static char next_square(game_state_t* state, int snum);
static void update_tail(game_state_t* state, int snum);
static void update_head(game_state_t* state, int snum);

static void allocation_failed() {
	 fprintf(stderr, "Out of memory.\n");
	 exit(1);
}
/* Helper function to get a character from the board (already implemented for you). */
static char get_board_at(game_state_t* state, int x, int y) {
  return state->board[y][x];
}

/* Helper function to set a character on the board (already implemented for you). */
static void set_board_at(game_state_t* state, int x, int y, char ch) {
  state->board[y][x] = ch;
}

/* Task 1 */
game_state_t* create_default_state() {
  // TODO: Implement this function
	game_state_t *gst = (game_state_t*) malloc(sizeof(game_state_t));
	if (gst == NULL) {
		allocation_failed();
	}
	gst->x_size = 14;
	gst->y_size = 10;
	gst->board = (char**) malloc(sizeof(char*) * gst->y_size);
	if (gst->board == NULL) {
		allocation_failed();
	}
	char *string1 = "##############";
	char *string2 = "#            #";
	char *string3 = "#        *   #";
	char *string4 = "#   d>       #";
	for (int i = 0; i < gst->y_size; i++) {
		gst->board[i] = (char*) malloc(sizeof(char) * gst->x_size + 1);
		if (gst->board[i] == NULL) {
			allocation_failed();
		}
		switch(i)
		{
			case 0 :
				strcpy(gst->board[i], string1);
				break;
			case 2 :
				strcpy(gst->board[i], string3);
				break;
			case 4 :
				strcpy(gst->board[i], string4);
				break;
			case 9 :
				strcpy(gst->board[i], string1);
				break;
			default :
				strcpy(gst->board[i], string2);
				break;
		}
	}
	gst->num_snakes = 1;
	gst->snakes = (snake_t*) malloc(sizeof(snake_t));
	if (gst->snakes == NULL) {
		allocation_failed();
	}
	gst->snakes[0].tail_x = 4;
	gst->snakes[0].tail_y = 4;
	gst->snakes[0].head_x = 5;
	gst->snakes[0].head_y = 4;
	gst->snakes[0].live = true;
    return gst;
}

/* Task 2 */
void free_state(game_state_t* state) {
  // TODO: Implement this function
	if (state != NULL) {
		for (int i = 0; i < state->y_size; i++) {
			free(state->board[i]);
		}
		free(state->board);
		free(state->snakes);
		free(state);
	}
    return;
}

/* Task 3 */
void print_board(game_state_t* state, FILE* fp) {
  // TODO: Implement this function.
	for (int i = 0; i < state->y_size; i++) {
		fprintf(fp,"%s\n" , state->board[i]);
	}
    return;
}

/* Saves the current state into filename (already implemented for you). */
void save_board(game_state_t* state, char* filename) {
  FILE* f = fopen(filename, "w");
  print_board(state, f);
  fclose(f);
}

/* Task 4.1 */
static bool is_tail(char c) {
  // TODO: Implement this function.
    if (c == 'w' || c == 'a' || c == 's' || c == 'd') {
		return true;
	}
    return false;
}

static bool is_snake(char c) {
  // TODO: Implement this function.
	if (c == 'w' || c == 'a' || c == 's' || c == 'd' || c == '^' || c == '<' || c == '>' || c == 'v' || c == 'x') {
		return true;
	}
    return false;
}

static char body_to_tail(char c) {
  // TODO: Implement this function.
	switch (c)
	{
		case '^' :
			return 'w';
		case '<' :
			return 'a';
		case 'v' :
			return 's';
		case '>' :
			return 'd';
	}
	return '?';
}

static int incr_x(char c) {
  // TODO: Implement this function.
	if (c == '>' || c == 'd') {
		return 1;
	} else if (c == '<' || c == 'a') {
		return -1;
	}
    return 0;
}

static int incr_y(char c) {
  // TODO: Implement this function.
	if (c == '^' || c == 'w' ) {
		return -1;
	} else if (c == 'v' || c == 's') {
		return 1;
	}
    return 0;
}
/* Task 4.2 */
static char next_square(game_state_t* state, int snum) {
  // TODO: Implement this function.
	unsigned int head_x = state->snakes[snum].head_x;
	unsigned int head_y = state->snakes[snum].head_y;
	char head = get_board_at(state, head_x, head_y);
	// switch (head)
	// {
	// 	case '^' :
	// 		return get_board_at(state, head_x, head_y - 1);
	// 	case '<' :
	// 		return get_board_at(state, head_x - 1, head_y);
	// 	case 'v' :
	// 		return get_board_at(state, head_x, head_y + 1);
	// 	case '>' :
	// 		return get_board_at(state, head_x + 1, head_y);
	// }
	return get_board_at(state, head_x + incr_x(head), head_y + incr_y(head));																
}

/* Task 4.3 */
static void update_head(game_state_t* state, int snum) {
  // TODO: Implement this function.
	unsigned int head_x = state->snakes[snum].head_x;
	unsigned int head_y = state->snakes[snum].head_y;
	char head = get_board_at(state, head_x, head_y);
	set_board_at(state, head_x + incr_x(head), head_y + incr_y(head), head);
	state->snakes[snum].head_x = head_x + incr_x(head);
	state->snakes[snum].head_y = head_y + incr_y(head);
    return;
}

/* Task 4.4 */
static void update_tail(game_state_t* state, int snum) {
  // TODO: Implement this function.
	unsigned int tail_x = state->snakes[snum].tail_x;
	unsigned int tail_y = state->snakes[snum].tail_y;
	char tail = get_board_at(state, tail_x, tail_y);
	char new_tail = body_to_tail(get_board_at(state, tail_x + incr_x(tail), tail_y + incr_y(tail)));
	set_board_at(state, tail_x + incr_x(tail), tail_y + incr_y(tail), new_tail);
	set_board_at(state, tail_x, tail_y, ' ');
	state->snakes[snum].tail_x = tail_x + incr_x(tail);
	state->snakes[snum].tail_y = tail_y + incr_y(tail);
  return;
}

/* Task 4.5 */
void update_state(game_state_t* state, int (*add_food)(game_state_t* state)) {
  // TODO: Implement this function.
	unsigned int head_x;
	unsigned int head_y;
	for(int i = 0; i < state->num_snakes; i++) {
		if(state->snakes[i].live == true) {
			head_x = state->snakes[i].head_x;
			head_y = state->snakes[i].head_y;
			char head = get_board_at(state, head_x, head_y);
			char new_head = get_board_at(state, head_x + incr_x(head), head_y + incr_y(head));
			if (is_snake(new_head) || new_head == '#') {
				state->snakes[i].live = false;
				set_board_at(state, head_x, head_y, 'x');
			} else if (new_head == '*') {
				update_head(state, i);
				add_food(state);
			} else {
				update_head(state, i);
				update_tail(state, i);
			}
		}
	}
  return;
}

/* Task 5 */
game_state_t* load_board(char* filename) {
  // TODO: Implement this function.
	unsigned int x_size = 0;
	unsigned int y_size = 0;
	char str[100];
	FILE *fp;
	fp = fopen(filename, "r");
	if (fp == NULL) {
		perror("error opening file");
	}
	game_state_t *gst = (game_state_t*) malloc(sizeof(game_state_t));
	if (gst == NULL) {
		allocation_failed();
	}
	gst->board = (char**) malloc(sizeof(char*) * 0);	//why need this line
	while (fgets(str, 100, fp) != NULL) {
		str[strcspn(str, "\n")] = 0;
		x_size = strlen(str);
		y_size += 1;
		gst->board = (char**) realloc(gst->board, sizeof(char*) * y_size);
		gst->board[y_size - 1] = (char*) malloc(sizeof(char) * (x_size + 1));
		strcpy(gst->board[y_size - 1], str);
	}
	gst->x_size = x_size;
	gst->y_size = y_size;
	return gst;
}

/* Task 6.1 */
static void find_head(game_state_t* state, int snum) {
  // TODO: Implement this function.
	unsigned int head_x = state->snakes[snum].tail_x;
	unsigned int head_y = state->snakes[snum].tail_y;
	char head = get_board_at(state, head_x, head_y);
	while (is_snake(get_board_at(state, head_x + incr_x(head), head_y + incr_y(head)))) {
		head_x = head_x + incr_x(head);
		head_y = head_y + incr_y(head);
		head = get_board_at(state, head_x, head_y);
	}
	state->snakes[snum].head_x = head_x;
	state->snakes[snum].head_y = head_y;
	return;
}

/* Task 6.2 */
game_state_t* initialize_snakes(game_state_t* state) {
  // TODO: Implement this function.
	state->num_snakes = 0;
	for (int i = 0; i < state->y_size; i++) {
		for (int j = 0; j < state->x_size; j++) {
			if (is_tail(state->board[i][j])) {
				state->num_snakes += 1;
				state->snakes = (snake_t*) realloc(state->snakes, sizeof(snake_t) * state->num_snakes);
				state->snakes[state->num_snakes - 1].tail_x = j;
				state->snakes[state->num_snakes - 1].tail_y = i;
				state->snakes[state->num_snakes - 1].live = true;
				find_head(state, state->num_snakes - 1);
			}
		}
	}
  return state;
}
