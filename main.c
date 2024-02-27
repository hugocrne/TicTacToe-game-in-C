#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

void printBlock(char block[][3]);
void createBlock(char block[][3]);
char checkWinner(char const *p, char const *c, char const block[][3]);
char createPlayer();
char createComputer(char const p);
void printWinner(char const *w);
bool isGameEnd(char block[][3]);
char startGame(char const p, char const c, char block[][3]);
void playerPlay(char block[][3], char const p);
void computerPlay(char block[][3], char const c);

void printBlock(char block[][3]) {
    printf("\n  0 1 2\n");
    for (int i = 0; i < 3; ++i) {
        printf("%d ", i);
        for (int j = 0; j < 3; ++j) {
            if (j < 2) {
                printf("%c|", block[i][j]);
            } else {
                printf("%c", block[i][j]);
            }
        }
        if (i < 2) {
            printf("\n  -----\n");
        }
    }
    printf("\n");
}

void createBlock(char block[][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            block[i][j] = ' ';
        }
    }
    printBlock(block);
}

char createPlayer() {
    char player;
    printf("Which character do you want to use? ");
    scanf(" %c", &player);
    printf("You have chosen the character %c\n", player);
    return player;
}

char createComputer(char const p) {
    if (p == 'O') {
        return 'X';
    }
    return 'O';
}

void printWinner(char const *w) {
    if (*w == ' ')
    {
        printf("It's a tie !\n");
        return;
    }
    printf("%c wins!\n", *w);
}

char checkRows(char const *p, char const *c, char const block[][3]) {
    for (int i = 0; i < 3; ++i) {
        if (block[i][0] == *p && block[i][1] == *p && block[i][2] == *p) return *p;
        if (block[i][0] == *c && block[i][1] == *c && block[i][2] == *c) return *c;
    }
    return ' ';
}

char checkCols(char const *p, char const *c, char const block[][3]) {
    for (int i = 0; i < 3; ++i) {
        if (block[0][i] == *p && block[1][i] == *p && block[2][i] == *p) return *p;
        if (block[0][i] == *c && block[1][i] == *c && block[2][i] == *c) return *c;
    }
    return ' ';
}

char checkDial(char const *p, char const *c, char const block[][3]) {
    if ((block[0][0] == *p && block[1][1] == *p && block[2][2] == *p) || (block[0][2] == *p && block[1][1] == *p && block[2][0] == *p)) return *p;
    if ((block[0][0] == *c && block[1][1] == *c && block[2][2] == *c) || (block[0][2] == *c && block[1][1] == *c && block[2][0] == *c)) return *c;
    return ' ';
}

char checkWinner(char const *p, char const *c, char const block[][3]) {
    char winner;
    if ((winner = checkRows(p, c, block)) != ' ') return winner;
    if ((winner = checkCols(p, c, block)) != ' ') return winner;
    if ((winner = checkDial(p, c, block)) != ' ') return winner;
    return ' ';
}

bool isGameEnd(char block[][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (block[i][j] == ' ') {
                return false;
            }
        }
    }
    return true;
}

char startGame(char const p, char const c, char block[][3]) {
    char winner;
    while (!isGameEnd(block)) {
        playerPlay(block, p);
        if ((winner = checkWinner(&p, &c, block)) != ' ') return winner;
        if (isGameEnd(block)) break;
        computerPlay(block, c);
        if ((winner = checkWinner(&p, &c, block)) != ' ') return winner;
    }
    return ' ';
}

void playerPlay(char block[][3], char const p) {
    int r, c;
    printf("Which row do you want to play in? (0/1/2): ");
    scanf("%d", &r);
    printf("Which column do you want to play in? (0/1/2): ");
    scanf("%d", &c);
    
	while (block[r][c] != ' ') {
		printf("Invalid choice. Please choose another cell:\n");
		printf("Which row do you want to play in? (0/1/2): ");
		scanf("%d", &r);
		printf("Which column do you want to play in? (0/1/2): ");
		scanf("%d", &c);
	}
	block[r][c] = p;
    printBlock(block);
}

void computerPlay(char block[][3], char const c) {
	int row, col;
	srand(time(NULL));
	do {
		row = rand() % 3;
		col = rand() % 3;
	} while (block[row][col] != ' ');
	block[row][col] = c;
    printBlock(block);
}

int main() {
	char response = 'Y';
	while (response == 'Y' || response == 'y') {
		char player = createPlayer();
		char computer = createComputer(player);
		char block[3][3];
		createBlock(block);
		char winner = startGame(player, computer, block);
		printWinner(&winner);
		printf("Do you want to play another game? (Y/N)");
		scanf(" %c", &response);
	}
	return 0;
}