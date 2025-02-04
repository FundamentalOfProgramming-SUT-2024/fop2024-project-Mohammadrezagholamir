#include <ncurses.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <locale.h>
#include <regex.h>


#define MAP_WIDTH 105
#define MAP_HEIGHT 35
#define MIN_ROOM_SIZE 7
#define MAX_ROOM_SIZE 12
#define MAX_ROOMS 8

typedef struct {
    int x, y;
    bool exists;
} Stair;

// Floor containers seen
bool seen[MAP_WIDTH][MAP_HEIGHT] = {{false}};
bool seen2[MAP_WIDTH][MAP_HEIGHT] = {{false}};
bool seen3[MAP_WIDTH][MAP_HEIGHT] = {{false}};
bool seen4[MAP_WIDTH][MAP_HEIGHT] = {{false}};

// Floor containers
char container[MAP_WIDTH][MAP_HEIGHT];
char container2[MAP_WIDTH][MAP_HEIGHT];
char container3[MAP_WIDTH][MAP_HEIGHT];
char container4[MAP_WIDTH][MAP_HEIGHT];
typedef struct {
    int x , y;
    int type;
    bool used;
    
} Gun;
int guns =0;
int macecounter = 1;
int daggercounter = 0;
int mwandcounter = 0;
int narrowcounter = 0;
int swordcounter =0 ;
int scounter = 0;
int dcounter = 0;
int hcounter =0;
int smove = 0;
int dmove = 0;
int hmove = 0;
typedef struct {
    int x ,y;
    int type;

} Food;
typedef struct {
    int x , y;
    int value;
} Gold;


Gold goldcontainer[50];
Gun guncontainer[50];

typedef struct {
    int x , y ;
} BGold;

BGold bgoldcontainer[50];

int floorcount = 0;

void map_container(WINDOW* win, char container[MAP_WIDTH][MAP_HEIGHT]) {
    for (int i = 0; i < MAP_WIDTH; i++) {
        for (int j = 0; j < MAP_HEIGHT; j++) {
            chtype ch = mvwinch(win, j, i) & A_CHARTEXT;
            container[i][j] = (char)ch;
        }
    }
}

typedef struct {
    int x , y;
    bool alwaysclose;
    bool open;
    int password;
} Pdoor;
typedef struct {
    int x;
    int y;
    bool active;
} Trap;

Trap trapcounter[30];

typedef struct{
    int x ,y;
    int type;
    
} Poison;

Poison poisoncontainer[50];

typedef struct {
    int x , y;
} Cup;

typedef struct {
    int x, y;
    char HeroColor[30];
    int heart;
    int food;
    int guncount;
    int typefood;
    Food foods[30];
    Gun guns[30];
    BGold bgolds[30];
    Poison poisons[50];
    int poisoncount;
    int bgoldcounter;
    int goldcount;
    int gold;
    int move;
    int typeofInitialGun;

    bool sdrug;
    int ddrug;

    int score;
    
    int cup ;
    bool jam;
    int kill;
    
} Hero;

Hero hero;

typedef struct {
    int x , y;
    int health ; 
    bool active;
    int type;
    int damage;
    int moves;
    char nmd;
    bool die;
    bool stop;
    char name[30];
} Monster;
int enemycount = 0;

Monster monstercontainer[50];
int enemy = 0 ;


typedef struct {
    int x, y;
    int width, height;
    bool haspillar;
    // has 3 types: Regular , treasure , poison :
    int typeroom;
    //Gun and Gold
    int guncount;
    Gun guns[30];
    Gold golds[30];
    BGold bgolds[50];
    int bgoldcounter;
    int goldcount;
    //traps
    
    
    //Foods
    int foodCount;
    Food foods[20];
    int trapcount;
    Trap traps[30];
    Poison poisons[50];
    int poisoncounter;

    int monstercount;
    Monster monsters[50];
    
    int cup;

} Room;
typedef struct {
    int floorcount;
    int guns;
    int macecounter;
    int daggercounter;
    int mwandcounter;
    int narrowcounter;
    int swordcounter;
    int scounter;
    int dcounter;
    int hcounter;
    int smove;
    int dmove;
    int hmove;
    int enemycount;
    int enemy;

    
    bool seen[MAP_WIDTH][MAP_HEIGHT];
    bool seen2[MAP_WIDTH][MAP_HEIGHT];
    bool seen3[MAP_WIDTH][MAP_HEIGHT];
    bool seen4[MAP_WIDTH][MAP_HEIGHT];
    char container[MAP_WIDTH][MAP_HEIGHT];
    char container2[MAP_WIDTH][MAP_HEIGHT];
    char container3[MAP_WIDTH][MAP_HEIGHT];
    char container4[MAP_WIDTH][MAP_HEIGHT];

    
    Gun guncontainer[50];
    Gold goldcontainer[50];
    BGold bgoldcontainer[50];
    Trap trapcounter[30];
    Poison poisoncontainer[50];
    Monster monstercontainer[50];

    Hero hero;


} GameState;




int start_game(char* choices[] , int n_choices){
    
    int highlight = 0;
    int start_y =15 ;      // محل شروع چاپ در محور Y
    int start_x = 40;     // محل شروع چاپ در محور X

    // چاپ متن در موقعیت مشخص شده
    mvprintw(start_y + 0, start_x, "   _________________________________________________________");
    mvprintw(start_y + 1, start_x, " /|     -_-                                             _-  |\\");
    mvprintw(start_y + 2, start_x, "/ |_-_- _                                         -_- _-   -| \\   ");
    mvprintw(start_y + 3, start_x, "  |                            _-  _--                      | ");
    mvprintw(start_y + 4, start_x, "  |                            ,                            |");
    mvprintw(start_y + 5, start_x, "  |      .-'````````'.        '(`        .-'```````'-.      |");
    mvprintw(start_y + 6, start_x, "  |    .` |           `.      `)'      .` |           `.    |");
    mvprintw(start_y + 7, start_x, "  |   /   |   ()        \\      U      /   |    ()       \\   |");
    mvprintw(start_y + 8, start_x, "  |  |    |    ;         | o   T   o |    |    ;         |  |");
    mvprintw(start_y + 9, start_x, "  |  |    |     ;        |  .  |  .  |    |    ;         |  |");
    mvprintw(start_y + 10, start_x, "  |  |    |     ;        |   . | .   |    |    ;         |  |");
    mvprintw(start_y + 11, start_x, "  |  |    |     ;        |    .|.    |    |    ;         |  |");
    mvprintw(start_y + 12, start_x, "  |  |    |____;_________|     |     |    |____;_________|  |");
    mvprintw(start_y + 13, start_x, "  |  |   /  __ ;   -     |     !     |   /     `'() _ -  |  |");
    mvprintw(start_y + 14, start_x, "  |  |  / __  ()        -|        -  |  /  __--      -   |  |");
    mvprintw(start_y + 15, start_x, "  |  | /        __-- _   |   _- _ -  | /        __--_    |  |");
    mvprintw(start_y + 16, start_x, "  |__|/__________________|___________|/__________________|__|");
    mvprintw(start_y + 17, start_x, " /                                             _ -        lc \\");
    mvprintw(start_y + 18, start_x, "/   -_- _ -             _- _---                       -_-  -_ \\");

    refresh();
    while (1) {
        
        for (int i = 0; i < n_choices; i++) {
            if (i == highlight) {
                attron(A_REVERSE);
                mvprintw(i, 0, "%s", choices[i]);
                attroff(A_REVERSE);
            } else {
                mvprintw(i, 0, "%s", choices[i]);
            }
        }
        refresh();

        int choice = getch();
        switch (choice) {
            case KEY_UP:
                highlight = (highlight == 0) ? n_choices - 1 : highlight - 1;
                break;
            case KEY_DOWN:
                highlight = (highlight == n_choices - 1) ? 0 : highlight + 1;
                break;
            case 10: // Enter key
                if (strcmp(choices[highlight], "Exit") == 0) {
                    endwin();
                    return 0;
                } else {
                    int result = handle_menu(choices, highlight);
                    if(result == 1){
                        return 1;
                    }
                }
                break;
        }
    }
}




typedef struct {
    char name[50];
    int score;
} Player;

int compare(const void *a, const void *b) {
    Player *playerA = (Player *)a;
    Player *playerB = (Player *)b;
    return playerB->score - playerA->score;
}
//default = easy -> 0
//medium -> 1
//hard -> 2
int dificulty = 0;


int herocolor = 0; //blue 2.red 3.yellow
char heroname[30];
char herogame[30];

void draw_table(int start_row, int start_col, int rows, int cols, int *col_widths, int cell_height) {
    int i, j, current_row, current_col;

   
    for (i = 0; i <= rows; i++) {
        current_col = start_col;
        for (j = 0; j < cols; j++) {
            for (int k = 0; k < col_widths[j]; k++) {
                mvaddch(start_row + i * cell_height, current_col + k, '_');
            }
            current_col += col_widths[j];
        }
    }

    
    for (j = 0; j <= cols; j++) {
        current_row = start_row;
        current_col = start_col;
        for (int col = 0; col < j; col++) {
            current_col += col_widths[col];
        }
        for (i = 0; i < rows; i++) {
            for (int k = 0; k < cell_height; k++) {
                mvaddch(current_row + k, current_col, '|');
            }
            current_row += cell_height;
        }
        mvaddch(current_row, current_col, '|'); 
    }
}
void handle_settings(char *choices[], int i) {
    int rows , cols;
    getmaxyx(stdscr , rows , cols);

    if (strcmp(choices[i], "Dificulty") == 0) {
        clear();
        const char *dificulties[] = {"Easy" , "Medium", "Hard"};
        int choice;
        int n_choice = sizeof(dificulties) / sizeof(dificulties[0]);
        int counter = 0;

        while (1) {
            clear();
            for (int j = 0; j < n_choice; j++) {
                if (j == counter) {
                    attron(A_REVERSE);
                    mvprintw(j, 0, "%s", dificulties[j]);
                    attroff(A_REVERSE);
                } else {
                    mvprintw(j, 0, "%s", dificulties[j]);
                }
            }
            refresh();

            choice = getch();
            if (choice == 27) // دکمه ESC
                return; // برگرد به منوی قبل
            switch (choice) {
                case KEY_UP:
                    counter = (counter == 0) ? n_choice - 1 : counter - 1;
                    break;
                case KEY_DOWN:
                    counter = (counter == n_choice - 1) ? 0 : counter + 1;
                    break;
                case 10:
                    dificulty = counter;
                    
                    if(dificulty == 2){
                        mvprintw(rows / 2 , (cols -20)/2 , "Game Difficulty : Hard");
                    }
                    else if(dificulty == 1){
                        mvprintw(rows / 2 , (cols -20)/2 , "Game Difficulty : Medium ");
                    }
                    else if(dificulty == 0){
                        mvprintw(rows / 2 , (cols -20)/2 , "Game Difficulty : Easy");
                    }
                    getch();

                    return;
            }
        }
    }
    else if(!strcmp(choices[i] , "Hero color")){
        clear();
        const char *dificulties[] = {"Blue" , "Red", "Yellow"};
        int choice;
        int n_choice = sizeof(dificulties) / sizeof(dificulties[0]);
        int counter = 0;

        while (1) {
            clear();
            for (int j = 0; j < n_choice; j++) {
                if (j == counter) {
                    attron(A_REVERSE);
                    mvprintw(j+rows/2, (cols - 20)/2, "%s", dificulties[j]);
                    attroff(A_REVERSE);
                } else {
                    mvprintw(j+rows, (cols - 20)/2, "%s", dificulties[j]);
                }
            }
            refresh();

            choice = getch();
            if (choice == 27) // دکمه ESC
                return; // برگرد به منوی قبل
            switch (choice) {
                case KEY_UP:
                    counter = (counter == 0) ? n_choice - 1 : counter - 1;
                    break;
                case KEY_DOWN:
                    counter = (counter == n_choice - 1) ? 0 : counter + 1;
                    break;
                case 10:
                    herocolor = counter;
                    
                    if(dificulty == 2){
                        mvprintw(rows / 2 , (cols -20)/2 , "Hero color : Blue");
                    }
                    else if(dificulty == 1){
                        mvprintw(rows / 2 , (cols -20)/2 , "Hero color : Red ");
                    }
                    else if(dificulty == 0){
                        mvprintw(rows / 2 , (cols -20)/2 , "Hero color : Yellow");
                    }
                    getch();

                    return;
            }
        }

    }
}

char* my_strdup(const char* str) {
    size_t length = strlen(str) + 1;
    char* copy = (char*)malloc(length);
    if (copy) {
        memcpy(copy, str, length);
    }
    return copy;
}

char* make_login(const char* name) {
    static char filename[400];
    snprintf(filename, sizeof(filename), "%s_games.txt", name);
    return filename;
}

char* convertor(const char* name, const char* suffix, const char* game) {
    static char filename[400];
    snprintf(filename, sizeof(filename), "%s_%s_%s.bin", name, suffix, game);
    return filename;
}

int handle_login(char* login_choices[], int i, char* name) {
    clear();
    if (strcmp(login_choices[i], "Create a new game") == 0) {
        FILE* game_list = fopen(make_login(name), "a");
        if (!game_list) {
            mvprintw(0, 0, "Error creating game list file.");
            refresh();
            getch();
            return;
        }
        int rows, cols;
        getmaxyx(stdscr, rows, cols);
        char game_name[100];
        mvprintw(rows / 2, (cols -20) / 2, "Please choose a name for your game: ");
        echo();
        scanw("%s", game_name);
        
        strcpy(herogame , game_name);
        fprintf(game_list, "%s\n", game_name);
        fclose(game_list);

        FILE* game_file = fopen(convertor(name, "games", game_name), "a");
        if (!game_file) {
            clear();
            mvprintw(rows / 2 , (cols - 20)/ 2, "Error creating game file.");
            refresh();
            getch();
            return;
        }
        fclose(game_file);
        clear();

        mvprintw(rows / 2 , (cols - 20)/ 2, "Game created successfully! Press any key to continue.");

        refresh();
        getch();
        return 1;
    } else if (strcmp(login_choices[i], "Resume game") == 0) {
        int rows , cols;
        getmaxyx(stdscr , rows , cols);
        FILE* game_list = fopen(make_login(name), "r");
        if (!game_list) {
            clear();
            mvprintw(rows / 2 , (cols - 20)/ 2, "Error: Unable to open game list file.");
            refresh();
            getch();
            return;
        }

        char* lines[1024];
        int line_count = 0;

        while (!feof(game_list) && !ferror(game_list)) {
            char buffer[200];
            if (fgets(buffer, sizeof(buffer), game_list) != NULL) {
                buffer[strcspn(buffer, "\n")] = '\0';
                lines[line_count] = my_strdup(buffer);
                line_count++;
                if (line_count >= 1024) {
                    break;
                }
            }
        }
        fclose(game_list);

        int counter = 0;
        int choice;
        while (1) {
            clear();
            for (int j = 0; j < line_count; j++) {
                if (j == counter) {
                    attron(A_REVERSE);
                    mvprintw(j + rows/2, (cols -20) / 2, "%s", lines[j]);
                    attroff(A_REVERSE);
                } else {
                    mvprintw(j + rows/2, (cols - 20)/2, "%s", lines[j]);
                }
            }
            refresh();
            choice = getch();
            switch (choice) {
                case KEY_UP:
                    counter = (counter == 0) ? line_count - 1 : counter - 1;
                    break;
                case KEY_DOWN:
                    counter = (counter == line_count - 1) ? 0 : counter + 1;
                    break;
                case 10:
                    if (counter == line_count - 1) { // اگر دکمه "Back" انتخاب شود
                        return -1; // برگشت به منوی قبلی
                    }
                    loadGameState(convertor(name , "games" , lines[counter]));
                    getch();
                    
                    return 1;
            }
        }

        for (int i = 0; i < line_count; i++) {
            free(lines[i]);
        }
    } else if (strcmp(login_choices[i], "Settings") == 0) {
        int rows , cols;
        getmaxyx(stdscr , rows , cols);
        const char *dificulties[] = {"Dificulty", "Hero color", "Music", "Back"};
        int choice;
        int n_choice = sizeof(dificulties) / sizeof(dificulties[0]);
        int counter = 0;
        while (1) {
            clear();
            for (int j = 0; j < n_choice; j++) {
                if (j == counter) {
                    attron(A_REVERSE);
                    mvprintw(j + rows/2, (cols-20)/2, "%s", dificulties[j]);
                    attroff(A_REVERSE);
                } else {
                    mvprintw(j+rows/2, (cols - 20)/2, "%s", dificulties[j]);
                }
            }
            refresh();
            choice = getch();
            switch (choice) {
                case KEY_UP:
                    counter = (counter == 0) ? n_choice - 1 : counter - 1;
                    break;
                case KEY_DOWN:
                    counter = (counter == n_choice - 1) ? 0 : counter + 1;
                    break;
                case 10:
                    handle_settings((char **)dificulties, counter);
                    return;
            }
        }
    }

    else if(strcmp(login_choices[i], "Back") ==0){
        return -1;
    }
    else if(strcmp(login_choices[i] , "Scoreboard") == 0){
        attroff(COLOR_PAIR(1));
        curs_set(FALSE);
        clear();
        int rows = 6, cols = 7, cell_height = 3;
        int col_widths[] = {5, 10, 10, 10 , 10 ,10 ,10}; // عرض ستون‌ها

        draw_table(1, 0, rows, cols, col_widths, cell_height);
    int counter =1;
    int place = 2;
    int count = 5;
    char *menus[]={
        "Name",
        "Score",
        "Golds",
        "Exp",
        "Others",
        "Com Games"
    };
    mvprintw(0 , 0 , "|");
    int menu_counter = 7;
    for(int i=0 ; i<7 ; i++){
        mvprintw(0  ,count ,"|" );
        count +=10;
    }
    for(int i =0 ; i<6 ; i++){
        mvprintw(0 , menu_counter , "%s" , menus[i]);
        menu_counter+=10;
    }
    for(int i=0 ; i<6 ; i++){

        wchar_t gold = L'🏅';
        wchar_t silver = L'🥈'; 
        wchar_t bronze = L'🥉';
        mvprintw(place, 2 , "%d",  counter);
        if(i==0){
            mvprintw(place + 1,2 ,"%lc",gold );
        }
        else if(i==1){
            mvprintw(place + 1 , 2 , "%lc" , silver);
        }
        else if(i==2){
            mvprintw(place + 1 , 2 , "%lc" , bronze);
        }
        counter ++;
        place+=3;
    }
    start_color();
    init_pair(2 , COLOR_RED , COLOR_YELLOW);
    init_pair(3 , COLOR_GREEN , COLOR_BLUE);
    init_pair(4 , COLOR_YELLOW , COLOR_CYAN);
    init_pair(5 , COLOR_BLACK , COLOR_WHITE);
    FILE *file = fopen("scores.txt", "r");
    if (!file) {
        endwin();
        perror("Unable to open the file.");
        return 1;
    }

    Player players[100];
    int counters = 0;
    while (fscanf(file, "%[^:]: %d\n", players[counters].name, &players[counters].score) == 2) {
        counters++;
    }
    fclose(file);

    qsort(players, counters, sizeof(Player), compare);

    

    int place_name = 2, limit = counters < 6 ? counters : 6;

    for (int i = 0; i < limit; i++) {
        int color_pair; 

        
        if (i == 0)
            color_pair = 3; 
        else if (i == 1)
            color_pair = 4; 
        else if (i == 2)
            color_pair = 5; 

        attron(COLOR_PAIR(color_pair));
        
        if (strcasecmp(players[i].name, name) == 0) {
            mvprintw(place_name, 3, ">");
            attron(A_BOLD);                
        }

        mvprintw(place_name, 7, "%s", players[i].name); 
        if(i ==0){
            mvprintw(place_name + 1 , 7 , "Goat");
        } 
        else if(i==1){
            mvprintw(place_name + 1 , 7 , "Legend");
        }

        mvprintw(place_name, 17, "%d", players[i].score); 

        
        if (strcmp(players[i].name, name) == 0)
            attroff(A_BOLD); 

        attroff(COLOR_PAIR(color_pair)); 
        place_name += 3; 
        refresh();

    getch();
    attron(COLOR_PAIR(1));
    }
    return 0;
}

}

void make_file(char *name, char *password, char *email) {
    char filename[300];
    snprintf(filename, sizeof(filename), "%s_rouge.txt", name);
    FILE *ptr = fopen(filename, "w");
    fprintf(ptr, "name : %s\n", name);
    fprintf(ptr, "password : %s\n", password);
    fprintf(ptr, "email : %s\n", email);
    fclose(ptr);
}

int upper_lower_digit_password(const char *password) {
    int count_upper = 0;
    int count_lower = 0;
    int count_digit = 0;

    for (const char *p = password; *p; p++) {
        if ('A' <= *p && *p <= 'Z')
            count_upper++;
        else if ('a' <= *p && *p <= 'z')
            count_lower++;
        else if ('0' <= *p && *p <= '9')
            count_digit++;
    }
    return (count_digit > 0 && count_upper > 0 && count_lower > 0);
}

int validate_email(const char *email) {
    regex_t regex;
    const char *pattern = "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$";

    if (regcomp(&regex, pattern, REG_EXTENDED)) {
        return 0;
    }

    int result = (regexec(&regex, email, 0, NULL, 0) == 0);
    regfree(&regex);
    return result;
}

int correct_password(const char *password) {
    return (strlen(password) >= 7);
}

void clear_string(char *string) {
    memset(string, '\0', strlen(string));
}

int repeate_name(const char *filename, const char *name) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return 0;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';
        if (strcmp(line, name) == 0) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}
char* random_password(char password[]){
      
    int upper_random = (rand() % 26) + 65;
    password[0] = (char)upper_random;

    for(int i = 1; i < 6; i++){
        password[i] = (char)((rand() % 26) + 97);  
    }
    
    password[6] = rand() % 10 + '0';  
    password[7] = '\0';  

    return password;
}

int handle_menu(char *choices[], int i) {
    clear();
    start_color();
    init_pair(1, COLOR_RED, COLOR_WHITE);
    
    int rows , cols ;
    getmaxyx(stdscr , rows ,cols);
    if (strcmp(choices[i], "Sign in") == 0) {
        char new_name[400];
        mvprintw(rows/2, (cols  - 20)/2, "Enter your name: ");
        echo();
        scanw("%399s", new_name);
        

        while (repeate_name("accountsname.txt", new_name)) {
            clear();
            mvprintw(rows/2, (cols - 20)/2, "This name already exists, please choose a different name: ");
            clear_string(new_name);
            scanw("%399s", new_name);
        }
        strcpy(heroname , new_name);

        char password[400];
        clear();
        mvprintw(rows/2 , (cols - 20)/2 , "Random password ? y or n : ");
        char answer;
        scanw(" %c" , &answer);
        if(answer == 'y'){
            clear();
            random_password(password);
            mvprintw(rows/2 , (cols - 20)/2 , "This is your password : %s" , password);
            getch();
            

        }
        else{

        

            clear();
            mvprintw(rows / 2, (cols - 20)/2, "Enter your password: ");
            echo();
            scanw("%s", password);
            
            while (!correct_password(password) || !upper_lower_digit_password(password)) {
                clear();
                mvprintw(rows / 2,(cols - 20)/2, "Please choose a stronger password: ");
                clear_string(password);
                scanw("%s", password);
            }
        }
        char email[400];
        clear();
        mvprintw(rows / 2, (cols - 20)/2, "Enter your email address: ");
        echo();
        scanw("%s", email);
        clear();


        
        while (!validate_email(email)) {
            clear();
            mvprintw(rows / 2, (cols - 20) /2, "Please choose a correct email: ");
            clear_string(email);
            scanw("%s", email);
        }

        make_file(new_name, password, email);
        clear();
        mvprintw(rows / 2 , (cols - 20)/ 2, "Account created successfully! Press any key to continue.");
        refresh();
        getch();
    } else if (strcmp(choices[i], "Login") == 0) {
        char username[400], password_user[400];
        clear();
        mvprintw(rows / 2 , (cols - 20)/ 2, "Enter your name for login: ");
        echo();
        scanw("%s", username);
        

        char file_name[400];
        snprintf(file_name, sizeof(file_name), "%s_rouge.txt", username);
        FILE *userfile = fopen(file_name, "r");

        while (userfile == NULL) {
            clear();
            mvprintw(rows / 2 , (cols - 20)/ 2, "Your name is not correct, please enter another name: ");
            clear_string(username);
            scanw("%s", username);
            snprintf(file_name, sizeof(file_name), "%s_rouge.txt", username);
            userfile = fopen(file_name, "r");
        }

        char line[400], stored_password[400];
        while (fgets(line, sizeof(line), userfile)) {
            if (strncmp(line, "password :", 9) == 0) {
                sscanf(line + 11, "%s", stored_password);
                break;
            }
        }
        fclose(userfile);
        clear();
        mvprintw(rows / 2 , (cols - 20)/ 2, "Enter your password: ");
        echo();
        scanw("%s", password_user);
        
        while (strcmp(password_user, stored_password) != 0) {
            clear();
            mvprintw(rows / 2 , (cols - 20)/ 2, "This password is incorrect, please try again: ");
            clear_string(password_user);
            scanw("%s", password_user);
        }
        clear();
        mvprintw(rows / 2 , (cols - 20)/ 2, "Login was successful! Press any key to continue.");
        refresh();
        getch();

        char *login_choices[] = {
            "Create a new game",
            "Resume game",
            "Scoreboard",
            "Settings",
            "Back"
        };

        int login = sizeof(login_choices) / sizeof(login_choices[0]);
        int highlight = 0;
        int choice;

        while (1) {
            clear();
            for (int j = 0; j < login; j++) {
                if (j == highlight) {
                    attron(A_REVERSE);
                    mvprintw(j + rows/2, (cols - 20)/2, "%s", login_choices[j]);
                    attroff(A_REVERSE);
                } else {
                    mvprintw(j + rows/2,(cols - 20)/2 , "%s", login_choices[j]);
                }
            }
            refresh();

            choice = getch();
            switch (choice) {
                case KEY_UP:
                    highlight = (highlight == 0) ? login - 1 : highlight - 1;
                    break;
                case KEY_DOWN:
                    highlight = (highlight == login - 1) ? 0 : highlight + 1;
                    break;
                case 10:
                    int result = handle_login(login_choices, highlight, username);
                    if(result == -1){
                        return 0;
                    }
                    if(result == 1){
                        return 1;
                    }
                    break;
            }
        }
    }
    else if (strcmp(choices[i], "Login as a guest") == 0){
        return 1;
    }
}





void revealRoom(Room room, bool seen[MAP_WIDTH][MAP_HEIGHT]) {
    if(dificulty == 2){
        return;
    }
    if(room.typeroom == 4){
        return;
    }
    for (int i = 0; i < room.height; i++) {
        for (int j = 0; j < room.width; j++) {
            int nx = room.x + j;
            int ny = room.y + i;
            if (nx >= 0 && nx < MAP_WIDTH && ny >= 0 && ny < MAP_HEIGHT) {
                seen[nx][ny] = true;
            }
        }
    }
}


void updateVisibility(WINDOW* win, Hero hero, int radius, bool seen[MAP_WIDTH][MAP_HEIGHT] , Room* rooms , int roomcount) {
    for (int dx = -radius; dx <= radius; dx++) {
        for (int dy = -radius; dy <= radius; dy++) {
            int nx = hero.x + dx;
            int ny = hero.y + dy;

            if (nx >= 0 && nx < MAP_WIDTH && ny >= 0 && ny < MAP_HEIGHT) {
                seen[nx][ny] = true;  // Mark as seen
            }
        }
    }
    for (int i = 0; i < roomcount; i++) {
    Room room = rooms[i];
    if (hero.x >= room.x && hero.x < room.x + room.width &&
            hero.y >= room.y && hero.y < room.y + room.height) {
            //show room
            revealRoom(room, seen);
            break;
        }
    }
}

void drawSeenMap(WINDOW* win, char container[MAP_WIDTH][MAP_HEIGHT], bool seen[MAP_WIDTH][MAP_HEIGHT] , Pdoor* pdoor , Room* rooms , int roomcount) {

    
    

    for (int x = 0; x < MAP_WIDTH; x++) {
        for (int y = 0; y < MAP_HEIGHT; y++) {
            int roomnumber = inside(x , y ,rooms ,roomcount );
            if(roomnumber != -1 && rooms[roomnumber].typeroom == 3){
                if (seen[x][y]) {
                    
                    

                    chtype ch = container[x][y];
                    if((char)ch == '.' || (char)ch == '^'){
                        wattron(win , COLOR_PAIR(2));
                        mvwaddch(win, y, x, ch); 
                        wattroff(win , COLOR_PAIR(2));

                    }
                    else if((char)ch == '|' || (char)ch == '_' || (char)ch == 'O' || (char)ch == '&' || (char)ch == '+'){
                        wattron(win , COLOR_PAIR(4));
                        mvwaddch(win, y, x, ch); 
                        wattroff(win , COLOR_PAIR(4));
                    }
                    else if((char)ch == 'A' || (char)ch == 'M' || (char)ch == 'G' || (char)ch == 'K' || (char)ch == 'X' ){
                        wattron(win , COLOR_PAIR(5));
                        mvwaddch(win , y ,x , ch);
                        wattroff(win , COLOR_PAIR(5));
                    }
                    else if((char)ch =='#' || (char)ch == '>' || (char)ch == 'N' || (char)ch == 'E' || (char)ch == 'T' || (char)ch == 'U' || (char)ch == 'F'){
                        wattron(win , COLOR_PAIR(6));
                        mvwaddch(win , y ,x , ch);
                        wattroff(win , COLOR_PAIR(6)); 

                    }
                    else if( (char)ch == '!' || (char)ch == '1' || (char)ch == '4' || (char)ch == 'I' || (char)ch == '/'){
                        wattron(win , COLOR_PAIR(1));
                        mvwaddch(win , y ,x , ch);
                        wattroff(win , COLOR_PAIR(1));
                    }
                    else if((char)ch =='$' || (char)ch == '*'){
                        wattron(win ,COLOR_PAIR(4));
                        mvwaddch(win , y , x ,ch);
                        wattroff(win , COLOR_PAIR(4));
                    }
                    else if((char)ch =='@' && pdoor->open == true){
                        wattron(win , COLOR_PAIR(5));
                        mvwaddch(win , y ,x , ch);
                        wattroff(win , COLOR_PAIR(5));

                    }
                    else if((char)ch == '@' && pdoor->open == false){
                        wattron(win , COLOR_PAIR(1));
                        mvwaddch(win , y ,x , ch);
                        wattroff(win , COLOR_PAIR(1)); 
                    }
                    else if((char)ch == 'D' || (char)ch == 'S'|| (char)ch == 'C' ){
                        wattron(win , COLOR_PAIR(7));
                        mvwaddch(win , y ,x , ch);
                        wattroff(win , COLOR_PAIR(7));
                    }
    // Display the actual character
                } else {
                    mvwaddch(win, y, x, ' ');  // Display empty space
                }
            }
            else if(roomnumber != -1 && rooms[roomnumber].typeroom == 2){
                
                if (seen[x][y]) {
                    
                    

                    chtype ch = container[x][y];
                    if((char)ch == '.' || (char)ch == '^'){
                        wattron(win , COLOR_PAIR(2));
                        mvwaddch(win, y, x, ch); 
                        wattroff(win , COLOR_PAIR(2));

                    }
                    else if((char)ch == '|' || (char)ch == '_' || (char)ch == 'O' || (char)ch == '&' || (char)ch == '+'){
                        wattron(win , COLOR_PAIR(2));
                        mvwaddch(win, y, x, ch); 
                        wattroff(win , COLOR_PAIR(2));
                    }
                    else if((char)ch == 'A' || (char)ch == 'M' || (char)ch == 'G' || (char)ch == 'K' ||(char)ch == 'X'){
                        wattron(win , COLOR_PAIR(5));
                        mvwaddch(win , y ,x , ch);
                        wattroff(win , COLOR_PAIR(5));
                    }
                    else if((char)ch =='#' || (char)ch == '>' || (char)ch == 'N' || (char)ch == 'E' || (char)ch == 'T' || (char)ch == 'U' || (char)ch == 'F'){
                        wattron(win , COLOR_PAIR(6));
                        mvwaddch(win , y ,x , ch);
                        wattroff(win , COLOR_PAIR(6)); 

                    }
                    else if( (char)ch == '!' || (char)ch == '1' || (char)ch == '4' || (char)ch == 'I' || (char)ch == '/'){
                        wattron(win , COLOR_PAIR(1));
                        mvwaddch(win , y ,x , ch);
                        wattroff(win , COLOR_PAIR(1));
                    }
                    else if((char)ch =='$' || (char)ch == '*'){
                        wattron(win ,COLOR_PAIR(4));
                        mvwaddch(win , y , x ,ch);
                        wattroff(win , COLOR_PAIR(4));
                    }
                    else if((char)ch =='@' && pdoor->open == true){
                        wattron(win , COLOR_PAIR(5));
                        mvwaddch(win , y ,x , ch);
                        wattroff(win , COLOR_PAIR(5));

                    }
                    else if((char)ch == '@' && pdoor->open == false){
                        wattron(win , COLOR_PAIR(1));
                        mvwaddch(win , y ,x , ch);
                        wattroff(win , COLOR_PAIR(1)); 
                    }
                    else if((char)ch == 'D' || (char)ch == 'S'|| (char)ch == 'C' ){
                        wattron(win , COLOR_PAIR(7));
                        mvwaddch(win , y ,x , ch);
                        wattroff(win , COLOR_PAIR(7));
                    }
    
                } else {
                    mvwaddch(win, y, x, ' ');  
                }





            }
            else{
                if (seen[x][y]) {
                    
                    

                    chtype ch = container[x][y];
                    if((char)ch == '.' || (char)ch == '^'){
                        wattron(win , COLOR_PAIR(2));
                        mvwaddch(win, y, x, ch); 
                        wattroff(win , COLOR_PAIR(2));

                    }
                    else if((char)ch == '|' || (char)ch == '_' || (char)ch == 'O' || (char)ch == '&' || (char)ch == '+'){
                        wattron(win , COLOR_PAIR(3));
                        mvwaddch(win, y, x, ch); 
                        wattroff(win , COLOR_PAIR(3));
                    }
                    else if((char)ch == 'A' || (char)ch == 'M' || (char)ch == 'G' || (char)ch == 'K' || (char)ch == 'X' ){
                        wattron(win , COLOR_PAIR(5));
                        mvwaddch(win , y ,x , ch);
                        wattroff(win , COLOR_PAIR(5));
                    }
                    else if((char)ch =='#' || (char)ch == '>' || (char)ch == 'N' || (char)ch == 'E' || (char)ch == 'T' || (char)ch == 'U' || (char)ch == 'F'){
                        wattron(win , COLOR_PAIR(6));
                        mvwaddch(win , y ,x , ch);
                        wattroff(win , COLOR_PAIR(6)); 

                    }
                    else if( (char)ch == '!' || (char)ch == '1' || (char)ch == '4' || (char)ch == 'I' || (char)ch == '/'){
                        wattron(win , COLOR_PAIR(1));
                        mvwaddch(win , y ,x , ch);
                        wattroff(win , COLOR_PAIR(1));
                    }
                    else if((char)ch =='$' || (char)ch == '*'){
                        wattron(win ,COLOR_PAIR(4));
                        mvwaddch(win , y , x ,ch);
                        wattroff(win , COLOR_PAIR(4));
                    }
                    else if((char)ch =='@' && pdoor->open == true){
                        wattron(win , COLOR_PAIR(5));
                        mvwaddch(win , y ,x , ch);
                        wattroff(win , COLOR_PAIR(5));

                    }
                    else if((char)ch == '@' && pdoor->open == false){
                        wattron(win , COLOR_PAIR(1));
                        mvwaddch(win , y ,x , ch);
                        wattroff(win , COLOR_PAIR(1)); 
                    }
                    else if((char)ch == 'D' || (char)ch == 'S'|| (char)ch == 'C' ){
                        wattron(win , COLOR_PAIR(7));
                        mvwaddch(win , y ,x , ch);
                        wattroff(win , COLOR_PAIR(7));
                    }
    
                } else {
                    mvwaddch(win, y, x, ' ');  
                }
            }
        }
        
    }
}
void markseen(int x , int y , bool seen[MAP_WIDTH][MAP_HEIGHT]){
    seen[x][y] = true;
}
bool isitwallorO(WINDOW* win, int x, int y ) {
    
        chtype ch = mvwinch(win, y, x);
        
        if ((char)ch != '|' && (char)ch != '_' && (char)ch != 'O' && (char)ch != ' ' ) {
            return true;
        }

        return false;
    
}
bool isitwallorOdrug(WINDOW* win, int x, int y , int way) {
    chtype ch = mvwinch(win, y, x);
    chtype ch2;
    
    if (way == 50) { // پایین
        ch2 = mvwinch(win, y+1, x);
    } else if (way == 56) { // بالا
        ch2 = mvwinch(win, y-1, x);
    } else if (way == 52) { // چپ
        ch2 = mvwinch(win, y, x-1);
    } else if (way == 54) { // راست
        ch2 = mvwinch(win, y, x+1);
    } else {
        return false;
    }

    // فقط دیوارها و موانع رو بررسی کن، ولی # باید قابل عبور باشه
    if ((char)ch != '|' && (char)ch != '_' && (char)ch != 'O' && (char)ch != ' ' ||
        (char)ch == '#' ||
        (char)ch2 != '|' && (char)ch2 != '_' && (char)ch2 != 'O' && (char)ch2 != ' ' ||
        (char)ch2 == '#') {
        return true;
    }

    return false;
}


bool isInsideRoom(int x, int y, Room* rooms, int roomCount);

int Herox() {
    return rand() % (MAP_WIDTH - 2);
}

int Heroy() {
    return rand() % (MAP_HEIGHT - 2);
}

void HeroPlace(WINDOW* win, Room* rooms, int roomCount, int* savedX, int* savedY) {
    Room room = rooms[2];
    int xrnd = room.x + 1 + rand() % (room.width - 2);
    int yrnd = room.y + 1 + rand() % (room.height - 2);
    *savedX = xrnd;
    *savedY = yrnd;
    mvwaddch(win, yrnd, xrnd, 'H');
}

int oneOrTwo() {
    return rand() % 2 + 1;
}

bool haspillar(Room* room) {
    return oneOrTwo() == 2;
}

void placeTraps(Room* rooms , Trap* trapcounter , int roomcount) {
    int random = 2 + dificulty;
    int num = 0 ;
    for(int i=0 ; i<roomcount ; i++){
        if(rooms[i].typeroom == 3){
            rooms[i].trapcount = 3 + dificulty;
        }
        else{
            rooms[i].trapcount = rand() % random;
        }
        int counter=rooms[i].trapcount;

        Room room = rooms[i];
        for(int j=0 ; j<counter ; j++){
            int xrnd = room.x + 1 + rand() % (room.width - 2);
            int yrnd = room.y + 1 + rand() % (room.height - 2);
            rooms[i].traps[j].x = xrnd;
            rooms[i].traps[j].y =yrnd;
            rooms[i].traps[j].active = false;
            trapcounter[num].x = xrnd;
            trapcounter[num].y = yrnd;
            trapcounter[num].active = false;
            num++;
        }

    }
}

void isontrap(WINDOW* win,WINDOW* messagewin , Room* rooms, int roomCount, Hero* hero  ,Trap* trapcounter , char container[MAP_WIDTH][MAP_HEIGHT]) {
    for(int i=0 ; i<50 ; i++){
        if(hero->x == trapcounter[i].x  && hero->y == trapcounter[i].y){
            trapcounter[i].active = true;
            hero->heart -= 2 + dificulty;
            wclear(messagewin);
            mvwprintw(messagewin , 0 ,0 , "Trap activated!");
            mvwprintw(messagewin ,1 ,0 ,"%d" , hero->heart);
            mvwaddch(win , trapcounter[i].y , trapcounter[i].x , '^');
            container[trapcounter[i].x][trapcounter[i].y] = '^';
            mvwprintw(messagewin , 4, 10, "               _______");
            mvwprintw(messagewin ,5, 10, "              /  /  / ''..");
            mvwprintw(messagewin ,6, 10, "            |~||~||~|     '.");
            mvwprintw(messagewin ,7, 10, "            | || || |      : (~)T(~)");
            mvwprintw(messagewin ,8, 10, "            | || || |      '. /   \\");
            mvwprintw(messagewin ,9, 10, "            =========        |  ._ |");
            mvwprintw(messagewin ,10, 10, "            | || || |         \\ | /");
            mvwprintw(messagewin ,11, 10, "            | || || |         /^^^\\");
            mvwprintw(messagewin ,12, 10, "            |_||_||_|");

            wrefresh(messagewin);
            getch();


        }
    }
}

void placestair(WINDOW* win, Room* rooms, int roomcount, Stair* stair) {
    Room room = rooms[3];
    int xrnd = room.x + 1 + rand() % (room.width - 2);
    int yrnd = room.y + 1 + rand() % (room.height - 2);
    stair->x = xrnd;
    stair->y = yrnd;
    stair->exists = true;
    mvwaddch(win, yrnd, xrnd, '>');
}

void drawpillar(WINDOW* win, Room room) {
    if (room.haspillar) {
        int xrnd = room.x + 1 + rand() % (room.width - 2);
        int yrnd = room.y + 1 + rand() % (room.height - 2);
        mvwaddch(win, yrnd, xrnd, 'O');
    }
}

bool doesOverlap(Room* rooms, int roomCount, Room newRoom) {
    for (int i = 0; i < roomCount; i++) {
        Room r = rooms[i];

        if (newRoom.x < r.x + r.width &&
            newRoom.x + newRoom.width > r.x &&
            newRoom.y < r.y + r.height &&
            newRoom.y + newRoom.height > r.y) {
            return true;
        }

        int horizontalDist = (newRoom.x > r.x + r.width) ? newRoom.x - (r.x + r.width)
                          : (r.x > newRoom.x + newRoom.width) ? r.x - (newRoom.x + newRoom.width)
                          : 0;

        int verticalDist = (newRoom.y > r.y + r.height) ? newRoom.y - (r.y + r.height)
                        : (r.y > newRoom.y + newRoom.height) ? r.y - (newRoom.y + newRoom.height)
                        : 0;

        if (horizontalDist < 10 && verticalDist < 10) {
            return true;
        }
    }
    return false;
}

bool isInsideRoom(int x, int y, Room* rooms, int roomCount) {
    for (int i = 0; i < roomCount; i++) {
        Room r = rooms[i];
        if (x >= r.x && x < r.x + r.width && y >= r.y && y < r.y + r.height) {
            return true;
        }
    }
    return false;
}
int inside(int x , int y ,Room* rooms , int roomcount){
    for (int i = 0; i < roomcount; i++) {
        Room r = rooms[i];
        if (x >= r.x && x <= r.x + r.width && y >= r.y && y <= r.y + r.height) {
            return i;
        }
    }
    return -1;

}
void gunsinroom(WINDOW* win , Room* rooms , int roomcount , char container[MAP_WIDTH][MAP_HEIGHT] , Gun* guncontainer){
    int count = 0;
    for(int i=0 ; i<roomcount ; i++){
    
        int guncounter = rand() %2+1;
        rooms[i].guncount = guncounter;
        for(int j=0 ; j<guncounter ; j++){
            int xrnd = rooms[i].x + 1 + rand() % (rooms[i].width - 2);
            int yrnd = rooms[i].y + 1 + rand() % (rooms[i].height - 2);
            int typeg = rand() % 5 + 1;
            switch(typeg){
                case 1:
                    mvwaddch(win , yrnd , xrnd ,'4' );
                    container[xrnd][yrnd]= '4';
                    wrefresh(win);
                    break;
                case 2 :
                    mvwaddch(win , yrnd , xrnd ,'!' );
                    container[xrnd][yrnd]= '!';
                    wrefresh(win); 
                    break; 
                case 3:
                    mvwaddch(win , yrnd , xrnd ,'I' );
                    container[xrnd][yrnd]= 'I';
                    wrefresh(win);
                    break; 
                case 4 :
                    mvwaddch(win , yrnd , xrnd ,'/' );
                    container[xrnd][yrnd]= '/';
                    wrefresh(win);
                    break;
                case 5:
                    mvwaddch(win , yrnd , xrnd ,'1' );
                    container[xrnd][yrnd]= '1';
                    wrefresh(win);
                    break;
            }
            rooms[i].guns[j].x = xrnd;
            rooms[i].guns[j].y = yrnd;
            rooms[i].guns[j].type = typeg;
            rooms[i].guns[j].used = 1;
            guncontainer[count].x =xrnd;
            guncontainer[count].y = yrnd;
            guncontainer[count].type =typeg;
            guncontainer[count].used = 1;
            count++;
        }

    }
    guns = count;
}
int isitongun(WINDOW* win , WINDOW* messagewin , int x , int y ){
    chtype ch = mvwinch(win , y , x);
    if((char)ch == '4' || (char)ch == '!' || (char)ch == '1' || (char)ch == '/' || (char)ch =='I'){
        return 1;
    }
    return 0;
    
}
void addtoinventory(WINDOW* win , WINDOW* messagewin , Hero* hero , int x , int y ,Gun* guncontainer ){
    wclear(messagewin);
    for(int i=0 ; i<50 ; i++){
        if(guncontainer[i].x == x && guncontainer[i].y == y){
            hero->guns[hero->guncount].x = x; 
            hero->guns[hero->guncount].y = y;
            hero->guns[hero->guncount].type = guncontainer[i].type;
            if(guncontainer[i].type == 1){
                macecounter++;
            }
            else if(guncontainer[i].type == 2){
                if(guncontainer[i].used == 1){
                    daggercounter+= 10;
                }
                else {
                    daggercounter++;
                }
            }
            else if(guncontainer[i].type == 3){
                if(guncontainer[i].used ==1){
                    mwandcounter+= 8;
                }
                else {
                    mwandcounter++;
                }
            }
            else if(guncontainer[i].type == 4){

                if(guncontainer[i].used == 1){

                
                    narrowcounter+=20;
                }
                else{
                    narrowcounter++;
                }

            }
            else if(guncontainer[i].type == 5){
                swordcounter++;
            }
            hero->guncount++;
            
            mvwprintw(messagewin , 0 , 0 , "You add gun type : %d" , guncontainer[i].type);
            wrefresh(messagewin);
            sleep(2);
            container[x][y] = '.';
            break;
            
        }
    }
}
void changegun(WINDOW* win , WINDOW*  messagewin , Hero* hero  ){
    wclear(messagewin);
    mvwprintw(messagewin , 0 , 0  , "Short-Range Weapons: ");
    mvwprintw(messagewin , 1 , 0 , "1. Mace : 4 %d" , macecounter);
    mvwprintw(messagewin , 2 , 0 , "2. Sword : 1 %d" , swordcounter);
    mvwprintw(messagewin , 3, 0 , "Long-Range Weapons: ");
    mvwprintw(messagewin , 4 ,0 , "3. Dagger : ! %d" , daggercounter);
    mvwprintw(messagewin , 5 , 0 , "4. Magic Wand : I %d" , mwandcounter);
    mvwprintw(messagewin ,6, 0, "5. Normal Arrow : / %d" , narrowcounter);
    int start_x = 1;
    int start_y = 9;
    mvwprintw(messagewin,start_y + 0, start_x, "               .m.");
    mvwprintw(messagewin,start_y + 1, start_x, "               (;)");
    mvwprintw(messagewin,start_y + 2, start_x, "               (;)");
    mvwprintw(messagewin,start_y + 3, start_x, "               (;)");
    mvwprintw(messagewin,start_y + 4, start_x, "            .  (;)  .");
    mvwprintw(messagewin,start_y + 5, start_x, "            |\\_(;)_/|");
    mvwprintw(messagewin,start_y + 6, start_x, "            |/ )|( \\|");
    mvwprintw(messagewin,start_y + 7, start_x, "              ( o )");
    mvwprintw(messagewin,start_y + 8, start_x, "               )8(");
    mvwprintw(messagewin,start_y + 9, start_x, "              ( o )");
    mvwprintw(messagewin,start_y + 10, start_x, "               )8(");
    mvwprintw(messagewin,start_y + 11, start_x, "              ;|S|;");
    mvwprintw(messagewin,start_y + 12, start_x, "              ||S||");
    mvwprintw(messagewin,start_y + 13, start_x, "              ||S||");
    mvwprintw(messagewin,start_y + 14, start_x, "              ||S|<");
    mvwprintw(messagewin,start_y + 15, start_x, "              ||S||");
    mvwprintw(messagewin,start_y + 16, start_x, "              ||S||");
    mvwprintw(messagewin,start_y + 17, start_x, "              ||S||");
    mvwprintw(messagewin,start_y + 18, start_x, "              ||S||");
    mvwprintw(messagewin,start_y + 19, start_x, "              >|S||");
    mvwprintw(messagewin,start_y + 20, start_x, "              ||S||");
    mvwprintw(messagewin,start_y + 21, start_x, "              ||S||");
    mvwprintw(messagewin,start_y + 22, start_x, "              \\\\ //");
    mvwprintw(messagewin,start_y + 23, start_x, "               \\V/");
    mvwprintw(messagewin,start_y + 24, start_x, "                V");
   


    int choice;
    echo();
    mvwprintw(messagewin , 7 , 0 , "Choose your weapon : ");
    wscanw(messagewin , "%d" , &choice);
    noecho();
    if(choice > 5){
        mvwprintw(messagewin , 8 , 0 , "Invalid number");
        wrefresh(messagewin);
        sleep(1);
        return;
    }
    if(choice == 1  ){
        if(macecounter>0){
            hero->typeofInitialGun = 1;
            mvwprintw(messagewin , 8 , 0  , "Your weapon has changed!");
            wrefresh(messagewin);
            sleep(1);
        }
        else {
            mvwprintw(messagewin , 8 , 0 , "There are no weapons!");
            wrefresh(messagewin);
            sleep(1);
        }
        
    }
    else if(choice == 2 ){
        if(swordcounter>0){
            hero->typeofInitialGun = 5;
            mvwprintw(messagewin , 8 , 0  , "Your weapon has changed!");
            wrefresh(messagewin);
            sleep(1);
        }
        else{
            mvwprintw(messagewin , 8 , 0 , "There are no weapons!");
            wrefresh(messagewin);
            sleep(1);
        }
    }
    else if(choice == 3 ){
        if(daggercounter>0){
            hero->typeofInitialGun = 2;
            mvwprintw(messagewin , 8 , 0  , "Your weapon has changed!");
            wrefresh(messagewin);
            sleep(1);
        }
        else {
            mvwprintw(messagewin , 8 , 0 , "There are no weapons!");
            wrefresh(messagewin);
            sleep(1);
        }

    }
    else if(choice == 4  ){
        if(mwandcounter>0){

        
            hero->typeofInitialGun = 3;
            mvwprintw(messagewin , 8 , 0  , "Your weapon has changed!");
            wrefresh(messagewin);
            sleep(1);
        }
        else {
            mvwprintw(messagewin , 8 , 0 , "There are no weapons!");
            wrefresh(messagewin);
            sleep(1);
        }
    }
    else if(choice == 5){
        if(narrowcounter > 0){
            hero->typeofInitialGun = 4;
            mvwprintw(messagewin , 8 , 0  , "Your weapon has changed!");
            wrefresh(messagewin);
            sleep(1);
        }
        else {
            mvwprintw(messagewin , 8 , 0 , "There are no weapons!");
            wrefresh(messagewin);
            sleep(1);
        }
    }


}
void foodsinroom(WINDOW* win , Room* rooms , int roomcount , char container[MAP_WIDTH][MAP_HEIGHT]){
    int random = 4 - dificulty;
    
    for(int i =0 ; i<roomcount ; i++){
        int foodcounter = rand() % random;
        rooms[i].foodCount = foodcounter;
        for(int j=0 ; j<foodcounter ; j++){
            int xrnd = rooms[i].x + 1 + rand() % (rooms[i].width - 2);
            int yrnd = rooms[i].y + 1 + rand() % (rooms[i].height - 2);
            
            int typef = rand() % 4+1;

            switch(typef){
                case 1 :
                    mvwaddch(win , yrnd , xrnd , 'A');
                    container[xrnd][yrnd] = 'A';
                    wrefresh(win);
                    break;
                case 2 :
                    mvwaddch(win , yrnd , xrnd , 'G');
                    container[xrnd][yrnd] = 'G';
                    wrefresh(win);
                    break;
                case 3 :
                    mvwaddch(win , yrnd , xrnd , 'M');
                    container[xrnd][yrnd] = 'M';
                    wrefresh(win);
                    break;
                case 4 :
                    mvwaddch(win , yrnd , xrnd , 'A');
                    container[xrnd][yrnd] = 'A';
                    wrefresh(win);
                    break;
            }
            rooms[i].foods[j].x = xrnd;
            rooms[i].foods[j].y =yrnd;
            rooms[i].foods[j].type = typef;


        }
    }

}
void poisonsinroom(WINDOW* win , Room* rooms , int roomcount , char container[MAP_WIDTH][MAP_HEIGHT] , Poison* poisoncontainer){
    int count = 0;
    int random = 4 - dificulty;
    for(int i=0 ; i<roomcount ; i++){
    
        int guncounter;
        if(rooms[i].typeroom ==2){
            guncounter = 3;
        }
        else {
            guncounter = rand() % random;
        }
        rooms[i].poisoncounter = guncounter;
        for(int j=0 ; j<guncounter ; j++){
            int xrnd = rooms[i].x + 1 + rand() % (rooms[i].width - 2);
            int yrnd = rooms[i].y + 1 + rand() % (rooms[i].height - 2);
            int typeg = rand() % 3 + 1;
            switch(typeg){
                case 1:
                    mvwaddch(win , yrnd , xrnd ,'S' );
                    container[xrnd][yrnd]= 'S';
                    wrefresh(win);
                    break;
                case 2 :
                    mvwaddch(win , yrnd , xrnd ,'D' );
                    container[xrnd][yrnd]= 'D';
                    wrefresh(win); 
                    break; 
                case 3:
                    mvwaddch(win , yrnd , xrnd ,'C' );
                    container[xrnd][yrnd]= 'C';
                    wrefresh(win);
                    break; 

            }
            rooms[i].poisons[j].x = xrnd;
            rooms[i].poisons[j].y = yrnd;
            rooms[i].poisons[j].type = typeg;
            poisoncontainer[count].x =xrnd;
            poisoncontainer[count].y = yrnd;
            poisoncontainer[count].type =typeg;
            count++;
        }

    }
}
int isitonpoison(WINDOW* win , WINDOW* messagewin , int x , int y ){
    chtype ch = mvwinch(win , y , x);
    if((char)ch == 'D' || (char)ch == 'C' || (char)ch == 'S' ){
        return 1;
    }
    return 0;
    
}

void addtoinventoryp(WINDOW* win , WINDOW* messagewin , Hero* hero , int x , int y ,Poison* poisoncontainer ){
    wclear(messagewin);
    for(int i=0 ; i<50 ; i++){
        if(poisoncontainer[i].x == x && poisoncontainer[i].y == y){
            hero->poisons[hero->poisoncount].x = x; 
            hero->poisons[hero->poisoncount].y = y;
            hero->poisons[hero->poisoncount].type = poisoncontainer[i].type;
            if(poisoncontainer[i].type == 1){
                scounter++;
            }
            else if(poisoncontainer[i].type == 2){
                dcounter++;
            }
            else if(poisoncontainer[i].type == 3){
                hcounter++;
            }

            hero->poisoncount++;
            
            mvwprintw(messagewin , 0 , 0 , "You add poison type : %d" , poisoncontainer[i].type);
            wrefresh(messagewin);
            sleep(2);
            container[x][y] = '.';
            break;
            
        }
    }
}
void usepoison(WINDOW* win , WINDOW*  messagewin , Hero* hero  ){
    wclear(messagewin);
    mvwprintw(messagewin , 0 , 0  , "YOUR POISONS : ");
    mvwprintw(messagewin , 1 , 0 , "Speed : %d" , scounter);
    mvwprintw(messagewin , 2 ,0 , "Damage : %d" , dcounter);
    mvwprintw(messagewin , 3 , 0 , "Health : %d" , hcounter);
    echo();
    char yorn;
    mvwprintw(messagewin , 4 , 0 ,"Use poisons? : ");
    wscanw(messagewin , "%c" , &yorn);
    noecho();
    if(yorn == 'n'){
        return;
    }


    int choice;
    
    mvwprintw(messagewin , 5 , 0 , "Choose poison : ");
    wscanw(messagewin , "%d" , &choice);
    noecho();
    if(choice > 3){
        return;
    }
    if(choice == 1 && scounter !=0){
        hero->sdrug = true;
        scounter--;
        return;
    }
    else if(choice == 2 && dcounter != 0){
        hero->ddrug = true;
        dcounter--;
        return;
    }
    else if(choice == 3 &&hcounter != 0){
        return;

    }



}
void movecontrol(Hero* hero){
    smove++;
    if(smove>10){
        hero->sdrug =false;
        smove =0 ;
        return;
    }
}
void movecontrold(Hero* hero){
    dmove++;
    if(dmove>10){
        hero->ddrug = false;
        dmove = 0;
        return; 
    }
}
void bgoldsinroom(WINDOW* win , Room* rooms , int roomcount , char container[MAP_WIDTH][MAP_HEIGHT] , BGold* bgoldcontainer){
    int counter = 0;
    for(int i= 0 ; i< roomcount ; i++){
        int bgoldcount;
        if(rooms[i].typeroom == 3){
            bgoldcount = 2;
        }
        else {
            bgoldcount = rand() % 2;
        }
        rooms[i].bgoldcounter = bgoldcount;
        for(int j =0 ; j<bgoldcount ; j++){
            int xrnd = rooms[i].x + 1 + rand() % (rooms[i].width - 2);
            int yrnd = rooms[i].y + 1 + rand() % (rooms[i].height - 2);
            
            rooms[i].bgolds[j].x = xrnd ;
            rooms[i].bgolds[j].y = yrnd;
            
            bgoldcontainer[counter].x =xrnd;
            bgoldcontainer[counter].y = yrnd;
            
            counter ++;
            mvwaddch(win, yrnd , xrnd , 'X');
            container[xrnd][yrnd] = 'X';
            wrefresh(win);            
        }
    }
}
void isitinbgold(WINDOW* win,WINDOW* messagewin ,int x , int y , Hero* hero , BGold* bgoldcontainer){
    chtype ch = mvwinch(win , y ,x);
    if((char)ch == 'X'){
        wclear(messagewin);
        for(int i= 0 ; i<50 ; i++){
            if( x == bgoldcontainer[i].x && y== bgoldcontainer[i].y){
                mvwprintw(messagewin , 0 , 0 , "you earned blck gold!");
                hero->goldcount += 4;
                container[x][y]='.';
            }
        }
        
        
    }
    
}
void cupinroom(WINDOW* win , Room* rooms , int roomcount  , char container[MAP_WIDTH][MAP_HEIGHT]){
    for(int i=0 ; i<roomcount ; i++){
        if(rooms[i].typeroom == 3){
            rooms[i].cup = 1;
            int xrnd = rooms[i].x + 1 + rand() % (rooms[i].width - 2);
            int yrnd = rooms[i].y + 1 + rand() % (rooms[i].height - 2);
            mvwaddch(win , yrnd ,xrnd , '*');
            container[xrnd][yrnd] = '*';
            wrefresh(win);
        }


    }
}


void isitoncup(WINDOW* win, WINDOW* messagewin, int x, int y, Hero* hero) {
    wchar_t trophy[] = L"\U0001F3C6";  
    chtype ch = mvwinch(win, y, x);
    
    if ((char)ch == '*') {
        wclear(messagewin);
        mvwprintw(messagewin, 0, 0, "Well done! You've earned cup!");
        mvwaddwstr(messagewin, 1, 0, trophy); 
        wrefresh(messagewin);
        sleep(2);
        
        hero->jam = true;
        hero->cup = 1;
        container[x][y] = '.';
    }
}


void goldsinroom(WINDOW* win  , Room* rooms , int roomcount , char container[MAP_WIDTH][MAP_HEIGHT] , Gold* goldcontainer){
    
    


    int counter = 0;
    for(int i= 0 ; i< roomcount ; i++){
        int goldcount;
        if(rooms[i].typeroom == 3){
            goldcount = 4;
        }
        else {
            goldcount = rand() % 2 + 1;
        }
        rooms[i].goldcount = goldcount;
        for(int j =0 ; j<goldcount ; j++){
            int xrnd = rooms[i].x + 1 + rand() % (rooms[i].width - 2);
            int yrnd = rooms[i].y + 1 + rand() % (rooms[i].height - 2);
            int what = rand() % 3 + 1;
            rooms[i].golds[j].x = xrnd ;
            rooms[i].golds[j].y = yrnd;
            rooms[i].golds[j].value = what;
            goldcontainer[counter].x =xrnd;
            goldcontainer[counter].y = yrnd;
            goldcontainer[counter].value = what;
            counter ++;
            mvwaddch(win, yrnd , xrnd , '$');
            container[xrnd][yrnd] = '$';
            wrefresh(win);            
        }
    }
}

void isitingold(WINDOW* win,WINDOW* messagewin ,int x , int y , Hero* hero , Gold* goldcontainer){
    chtype ch = mvwinch(win , y ,x);
    if((char)ch == '$'){
        wclear(messagewin);
        for(int i= 0 ; i<50 ; i++){
            if( x == goldcontainer[i].x && y== goldcontainer[i].y){
                mvwprintw(messagewin , 0 , 0 , "you earned %d golds!" , goldcontainer[i].value);
                hero->goldcount += goldcontainer[i].value;
                container[x][y]='.';
            }
        }
        
        
    }
    
}
int isitinfood(WINDOW* win , int x , int y){
    chtype ch  = mvwinch(win , y , x);
    if((char)ch == 'G' || (char)ch == 'M' || (char)ch == 'A' || (char)ch == 'K'){
        return 1;
    }
    return 0;
}
void addfoodhero(WINDOW* win , Hero* hero , char container[MAP_WIDTH][MAP_HEIGHT] , int x , int y ){
    if (hero->food > 5){
        return;
    }
    chtype ch = mvwinch(win , y , x);
    if((char)ch =='A'){
        hero->foods[hero->food].type = 1;
        hero->food++;
        mvwaddch(win , y , x , '.');
        container[x][y]= '.';
    }
    if((char)ch =='G'){
        hero->foods[hero->food].type = 2;
        hero->food++;
        mvwaddch(win , y , x , '.');
        container[x][y]= '.';
    }
    if((char)ch =='M'){
        hero->foods[hero->food].type = 3;
        hero->food++;
        mvwaddch(win , y , x , '.');
        container[x][y]= '.';
    }
    if((char)ch =='K'){
        hero->foods[hero->food].type = 4;
        hero->food++;
        mvwaddch(win , y , x , '.');
        container[x][y]= '.';
    }

    
}
void removeFood(Hero* hero, int index) {
    if (index >= hero->food || index < 0) return; 
    
    for (int i = index; i < hero->food - 1; i++) {
        hero->foods[i] = hero->foods[i + 1];
    }
    hero->food -= hero->food; 
}

void showingfoods(WINDOW* win , WINDOW* messagewin , Hero* hero){
    int count =hero->food;
    if(count==0){
        mvwprintw(messagewin , 0 , 0 , "No food !");
        wrefresh(messagewin);
        return ;
    }
    
    int count_copy = 0;
    char* typecontainer[30];
    for(int i=0 ; i<count ; i++){
        int type = hero->foods[i].type;
        switch (type) {
            case 1:
                typecontainer[count_copy] = "Apple";
                count_copy++;
                break;
            case 2 :
                typecontainer[count_copy] = "Golden Apple";
                count_copy++;
                break;
            case 3:
                typecontainer[count_copy] = "Magic Apple";
                count_copy++;
                break;
            case 4:
                typecontainer[count_copy] = "Poisin Apple";
                count_copy++;
                break;
        }
    }
    wclear(messagewin);
    for(int i=0 ; i<count ; i++){
        mvwprintw(messagewin,i+1 , 0 , "%s\n" , typecontainer[i]);
    }
    mvwprintw(messagewin, count + 1, 0, "Choose a number to eat:");

    
    echo();
    int choice;
    wscanw(messagewin, "%d", &choice);
    noecho();
    int start_y = count+4;
    int start_x = 4;
    mvwprintw(messagewin,start_y + 0, start_x, " .d888                     888 ");
    mvwprintw(messagewin,start_y + 1, start_x, "d88P\"                      888 ");
    mvwprintw(messagewin,start_y + 2, start_x, "888                        888 ");
    mvwprintw(messagewin,start_y + 3, start_x, "888888 .d88b.  .d88b.  .d88888 ");
    mvwprintw(messagewin,start_y + 4, start_x, "888   d88\"88bd88\"88bd88\" 888 ");
    mvwprintw(messagewin,start_y + 5, start_x, "888   888  888888  888888  888 ");
    mvwprintw(messagewin,start_y + 6, start_x, "888   Y88..88PY88..88PY88b 888 ");
    mvwprintw(messagewin,start_y + 7, start_x, "888    \"Y88P\"  \"Y88P\"  \"Y88888");

    wrefresh(messagewin);

    if (choice >= 0 && choice < count) {
        if(strcmp(typecontainer[choice] , "Apple") == 0){
            hero->heart += 2;

        }
        else if(strcmp(typecontainer[choice] , "Golden Apple") == 0){
            hero->heart +=4;
        }
        else if(strcmp(typecontainer[choice] , "Magic Apple") == 0){
            hero->heart +=6;

        }
        else if(strcmp(typecontainer[choice] , "Poison Apple") == 0){
            hero->heart -= 3;
        }
        mvwprintw(messagewin, count + 2, 0, "Eating food %d...", choice);
        wrefresh(messagewin);

        
        removeFood(hero, choice);
        getch();
    } else {
        mvwprintw(messagewin, count + 2, 0, "Invalid choice!");
        wrefresh(messagewin);
        getch();
        return 0;
    }
}
void monstersinroom(WINDOW* win , Room* rooms , int roomcount , Monster* monstercontainer  , char container[MAP_WIDTH][MAP_HEIGHT] ){
    
    int count =0 ;
    for(int i=0 ; i<roomcount; i++){
        int mon;
        if(rooms[i].typeroom == 3){
            mon = 3;
        }
        else{
            mon = rand() % (2 + dificulty);
        }
        rooms[i].monstercount = mon;
        for(int j=0 ; j<mon ; j++){
            int xrnd = rooms[i].x + 1 + rand() % (rooms[i].width - 2);
            int yrnd = rooms[i].y + 1 + rand() % (rooms[i].height - 2);
            int typeg = rand() % 5 + 1;

            switch(typeg){
                case 1:
                    mvwaddch(win , yrnd , xrnd , 'N');
                    container[xrnd][yrnd] = 'N';
                    wrefresh(win);
                    rooms[i].monsters[j].x = xrnd;
                    rooms[i].monsters[j].y = yrnd;
                    rooms[i].monsters[j].type = typeg;
                    rooms[i].monsters[j].health = 5;
                    rooms[i].monsters[j].damage = 1;
                    rooms[i].monsters[j].active = false;
                    rooms[i].monsters[j].moves = 5;
                    rooms[i].monsters[j].nmd = 'N';
                    rooms[i].monsters[j].die = false;
                    rooms[i].monsters[j].stop = false;
                    strcpy(rooms[i].monsters[j].name , "Deamon");
                    strcpy(monstercontainer[count].name ,"Deamon");
                    monstercontainer[count].stop = false ;
                    monstercontainer[count].die = false ;
                    monstercontainer[count].nmd = 'N';
                    monstercontainer[count].moves = 5;
                    monstercontainer[count].x = xrnd;
                    monstercontainer[count].y = yrnd;
                    monstercontainer[count].type = typeg;
                    monstercontainer[count].health = 5;
                    monstercontainer[count].damage = 1;
                    monstercontainer[count].active = false;
                    count++;
                    break;
                
                case 2:
                    mvwaddch(win , yrnd , xrnd , 'F');
                    container[xrnd][yrnd] = 'F';
                    wrefresh(win);
                    rooms[i].monsters[j].x = xrnd;
                    rooms[i].monsters[j].y = yrnd;
                    rooms[i].monsters[j].type = typeg;
                    rooms[i].monsters[j].health = 10;
                    rooms[i].monsters[j].damage = 2;
                    rooms[i].monsters[j].active = false;
                    rooms[i].monsters[j].moves = 7;
                    rooms[i].monsters[j].nmd = 'F';
                    rooms[i].monsters[j].die = false;
                    rooms[i].monsters[j].stop = false;
                    strcpy(rooms[i].monsters[j].name , "Fire Breathing Monster");
                    strcpy(monstercontainer[count].name ,"Fire Breathing Monster");
                    monstercontainer[count].stop = false ;
                    monstercontainer[count].die = false ;
                    monstercontainer[count].nmd = 'F';
                    monstercontainer[count].moves = 7;
                    monstercontainer[count].x = xrnd;
                    monstercontainer[count].y = yrnd;
                    monstercontainer[count].type = typeg;
                    monstercontainer[count].health = 10;
                    monstercontainer[count].damage = 2;
                    monstercontainer[count].active = false;
                    count++;
                    break;

                case 3:

                    mvwaddch(win , yrnd , xrnd , 'T');
                    container[xrnd][yrnd] = 'T';
                    wrefresh(win);
                    rooms[i].monsters[j].x = xrnd;
                    rooms[i].monsters[j].y = yrnd;
                    rooms[i].monsters[j].type = typeg;
                    rooms[i].monsters[j].health = 15;
                    rooms[i].monsters[j].damage = 3;
                    rooms[i].monsters[j].active = false;
                    rooms[i].monsters[j].moves = 8;
                    rooms[i].monsters[j].nmd = 'T';
                    rooms[i].monsters[j].die = false;
                    rooms[i].monsters[j].stop = false;
                    strcpy(rooms[i].monsters[j].name , "Giant");
                    strcpy(monstercontainer[count].name , "Giant");
                    monstercontainer[count].stop = false ;
                    monstercontainer[count].die = false ;
                    monstercontainer[count].nmd = 'T';
                    monstercontainer[count].moves = 8;
                    monstercontainer[count].x = xrnd;
                    monstercontainer[count].y = yrnd;
                    monstercontainer[count].type = typeg;
                    monstercontainer[count].health = 15;
                    monstercontainer[count].damage = 3;
                    monstercontainer[count].active = false;
                    count++;
                    break;
                
                case 4 :
                    mvwaddch(win , yrnd , xrnd , 'E');
                    container[xrnd][yrnd] = 'E';
                    wrefresh(win);
                    rooms[i].monsters[j].x = xrnd;
                    rooms[i].monsters[j].y = yrnd;
                    rooms[i].monsters[j].type = typeg;
                    rooms[i].monsters[j].health = 20;
                    rooms[i].monsters[j].damage = 4;
                    rooms[i].monsters[j].active = false;
                    rooms[i].monsters[j].moves = 10;
                    rooms[i].monsters[j].nmd = 'E';
                    rooms[i].monsters[j].die = false;
                    rooms[i].monsters[j].stop = false;
                    strcpy(rooms[i].monsters[j].name ,"Snake");
                    strcpy(monstercontainer[count].name , "Snake");
                    monstercontainer[count].stop = false ;
                    monstercontainer[count].die = false ;
                    monstercontainer[count].nmd = 'E';
                    monstercontainer[count].moves = 10;
                    monstercontainer[count].x = xrnd;
                    monstercontainer[count].y = yrnd;
                    monstercontainer[count].type = typeg;
                    monstercontainer[count].health = 20;
                    monstercontainer[count].damage = 4;
                    monstercontainer[count].active = false;
                    count++;
                    break;

                case 5:
                    mvwaddch(win , yrnd , xrnd , 'U');
                    container[xrnd][yrnd] = 'U';
                    wrefresh(win);
                    rooms[i].monsters[j].x = xrnd;
                    rooms[i].monsters[j].y = yrnd;
                    rooms[i].monsters[j].type = typeg;
                    rooms[i].monsters[j].health = 30;
                    rooms[i].monsters[j].damage = 5;
                    rooms[i].monsters[j].active = false;
                    rooms[i].monsters[j].moves = 12;
                    rooms[i].monsters[j].nmd = 'U';
                    rooms[i].monsters[j].die = false;
                    rooms[i].monsters[j].stop = false;
                    strcpy(rooms[i].monsters[j].name , "Undeed");
                    strcpy(monstercontainer[count].name , "Undeed");
                    monstercontainer[count].stop = false ;
                    monstercontainer[count].die = false ;
                    monstercontainer[count].nmd = 'U';
                    monstercontainer[count].moves = 12;
                    monstercontainer[count].x = xrnd;
                    monstercontainer[count].y = yrnd;
                    monstercontainer[count].type = typeg;
                    monstercontainer[count].health = 30;
                    monstercontainer[count].damage = 5;
                    monstercontainer[count].active = false;
                    count++;
                    break;

                
            }
        }
    }
    enemy = count;
}
int aroundhero(Hero* hero, Monster monster) {
    int dx = abs(hero->x - monster.x);
    int dy = abs(hero->y - monster.y);
    return (dx <= 1 && dy <= 1); 
}


void activatemonsters(WINDOW* win, Room* rooms, int roomcount, int x, int y, Monster* monstercontainer, Hero* hero, WINDOW* messagewin) {
    static int monster_move_counter = 0;
    monster_move_counter++;


    int room = inside(x, y, rooms, roomcount);
    if (room == -1) {
        return;
    }

    for (int i = 0; i < rooms[room].monstercount ; i++) {
        if(!rooms[room].monsters[i].die){
            rooms[room].monsters[i].active = true;

            // ذخیره موقعیت قبلی
            int prevX = rooms[room].monsters[i].x;
            int prevY = rooms[room].monsters[i].y;

            wattron(messagewin , COLOR_PAIR(2));

            mvwaddch(win, prevY, prevX, container[prevX][prevY]);

            wattroff(messagewin , COLOR_PAIR(2));

            // محاسبه فاصله از قهرمان
            int distance = abs(hero->x - prevX) + abs(hero->y - prevY);

            // اگر خیلی نزدیک است، کندتر حرکت کند
            if (distance < 3 && monster_move_counter % 5 != 0) { 
                continue;
            }
            if(rooms[room].monsters[i].stop == false){
            // حرکت به سمت قهرمان
                rooms[room].monsters[i].x += (hero->x > prevX) ? 1 : (hero->x < prevX) ? -1 : 0;
                rooms[room].monsters[i].y += (hero->y > prevY) ? 1 : (hero->y < prevY) ? -1 : 0;
            }

            // بررسی برخورد با قهرمان
            if (aroundhero(hero, rooms[room].monsters[i])) {
                hero->heart -= rooms[room].monsters[i].damage;
                mvwprintw(messagewin, 0, 0, "Monster hit you! Health: %d", hero->heart);
                wrefresh(messagewin);
            }

            wattron(messagewin , COLOR_PAIR(6));
            mvwaddch(win, rooms[room].monsters[i].y, rooms[room].monsters[i].x, rooms[room].monsters[i].nmd);
            wattroff(messagewin , COLOR_PAIR(6));
            wrefresh(win);
            usleep(200000);
            } // تاخیر بیشتر برای حرکت کندتر
    }
}

void attackmonster(WINDOW* win , WINDOW* messagewin, Hero* hero, Room* rooms, int roomcount, Monster* monstercontainer){
    int room = inside(hero->x  ,hero->y , rooms , roomcount);
    if(room == -1){
        return;
    }



    for(int i=0 ; i<rooms[room].monstercount ; i++){
        movecontrold(hero);
        int damage =0;
        int mx = rooms[room].monsters[i].x;
        int my = rooms[room].monsters[i].y;
        if(abs(hero->x - mx) <= 1 && abs(hero->y - my) <= 1 && hero->typeofInitialGun == 1){
            if(hero->ddrug == true){
                damage = 10;
            }
            else{
                damage = 5;
            } 
            rooms[room].monsters[i].health -= damage;
            mvwprintw(messagewin ,0 ,0 ,"You attacked with mace!");
            wrefresh(messagewin);
            sleep(1);
            if(rooms[room].monsters[i].health <= 0){
                rooms[room].monsters[i].die = true;
                mvwprintw(messagewin , 0  , 0 , "you killed enemy %s!" , rooms[room].monsters[i].name);
                wrefresh(messagewin);
                hero->kill++;
                sleep(1);
            }
            
        }
        else if(abs(hero->x - mx) <= 1 && abs(hero->y - my) <= 1 && hero->typeofInitialGun == 5 ){
            if(hero->ddrug == true){
                damage = 20;
            }
            else{
                damage = 10;
            } 
            rooms[room].monsters[i].health -= damage;
            mvwprintw(messagewin ,0 ,0 ,"You attacked with sword!");
            wrefresh(messagewin);
            sleep(1);
            if(rooms[room].monsters[i].health <= 0){
                rooms[room].monsters[i].die = true;
                mvwprintw(messagewin , 0  , 0 , "you killed enemy %s!" , rooms[room].monsters[i].name);
                wrefresh(messagewin);
                hero->kill++;
                sleep(1);
            }
            
        }
        else if(hero->typeofInitialGun == 2  && daggercounter > 0){
            if(hero->ddrug == true){
                damage = 24;
            }
            else{
                damage = 12;
            } 
            int c = getch();
            if(c=='d'){
                for(int k=hero->x ; k<hero->x + 5 ; k++){
                    chtype ch = mvwinch(win , hero->y  ,k);
                    if(rooms[room].monsters[i].x == k && rooms[room].monsters[i].y == hero->y){
                        rooms[room].monsters[i].health -= damage;
                        mvwprintw(messagewin , 0 , 0, "You attacked with dagger!");
                        wrefresh(messagewin);
                        sleep(1);
                        if(rooms[room].monsters[i].health <= 0){
                            rooms[room].monsters[i].die = true;
                            mvwprintw(messagewin , 0  , 0 , "you killed enemy %s!" , rooms[room].monsters[i].name);
                            hero->kill++;
                            wrefresh(messagewin);
                            sleep(1);
                        }
                        daggercounter --;
                        return;
                        
                    
                    }
                    else if((char)ch == '|'){
                        mvwaddch(win , hero->y , k-1 , '!');
                        container[k-1][hero->y] = '!';
                        guncontainer[guns].used = 0;
                        guncontainer[guns].x = k-1;
                        guncontainer[guns].y = hero->y;
                        guncontainer[guns].type = 2;
                        guns++;
                        daggercounter--;
                        wrefresh(win);
                        return;
                        
                    }
                }
                mvwaddch(win , hero->y , hero->x + 4 , '!');
                container[hero->x+4][hero->y] = '!';
                guncontainer[guns].used = 0;
                guncontainer[guns].x = hero->x + 4;
                guncontainer[guns].y = hero->y;
                guncontainer[guns].type = 2;
                guns++;
                daggercounter--;
                wrefresh(win);


            }
            else if(c=='a'){
                for(int k=hero->x ; k>hero->x - 6 ; k--){
                    chtype ch = mvwinch(win , hero->y , k);
                    if(rooms[room].monsters[i].x == k && rooms[room].monsters[i].y == hero->y){
                        rooms[room].monsters[i].health -= damage;
                        mvwprintw(messagewin , 0 , 0, "You attacked with dagger!");
                        wrefresh(messagewin);
                        sleep(1);
                        if(rooms[room].monsters[i].health <= 0){
                            rooms[room].monsters[i].die = true;
                            mvwprintw(messagewin , 0  , 0 , "you killed enemy %s!" , rooms[room].monsters[i].name);
                            hero->kill++;
                            wrefresh(messagewin);
                            sleep(1);
                        }
                        daggercounter--;
                        return;
                        
                    }
                    else if((char)ch == '|'){
                        mvwaddch(win , hero->y , k+1 , '!');
                        container[k+1][hero->y] = '!';
                        guncontainer[guns].used = 0;
                        guncontainer[guns].x = k+1;
                        guncontainer[guns].y = hero->y;
                        guncontainer[guns].type = 2;
                        guns++;
                        daggercounter--;
                        wrefresh(win);
                        return;
                    }
                    
                }
                mvwaddch(win , hero->y , hero->x -4 , '!');
                container[hero->x - 4][hero->y] = '!';
                guncontainer[guns].used = 0;
                guncontainer[guns].x = hero->x - 4;
                guncontainer[guns].y = hero->y;
                guncontainer[guns].type = 2;
                guns++;
                daggercounter--;
                wrefresh(win);

            }
            else if(c=='w'){
                for(int k=hero-> y; k>hero->y - 6 ; k--){
                    chtype ch = mvwinch(win , k , hero->x);
                    if(rooms[room].monsters[i].y == k && rooms[room].monsters[i].x == hero->x){
                        rooms[room].monsters[i].health -= damage;
                        mvwprintw(messagewin , 0 , 0, "You attacked with dagger!");
                        wrefresh(messagewin);
                        sleep(1);
                        if(rooms[room].monsters[i].health <= 0){
                            rooms[room].monsters[i].die = true;
                            mvwprintw(messagewin , 0  , 0 , "you killed enemy %s!" , rooms[room].monsters[i].name);
                            wrefresh(messagewin);
                            hero->kill++;
                            sleep(1);
                        }
                        daggercounter--;
                        return;
                        
                    }
                    else if((char)ch == '_'){
                        mvwaddch(win ,k+1 ,hero->x, '!');
                        container[hero->x][k+1] = '!';
                        guncontainer[guns].used = 0;
                        guncontainer[guns].x = hero->x;
                        guncontainer[guns].y = k+1;
                        guncontainer[guns].type = 2;
                        guns++;
                        daggercounter--;
                        wrefresh(win);
                        return;
                        
                    }
                }
                mvwaddch(win , hero->y - 4 , hero->x , '!');
                container[hero->x][hero->y - 4] = '!';
                guncontainer[guns].used = 0;
                guncontainer[guns].x = hero->x;
                guncontainer[guns].y = hero->y - 4;
                guncontainer[guns].type = 2;
                guns++;
                daggercounter--;
                wrefresh(win);
            }
            else if(c=='s'){
                for(int k=hero->y ; k<hero->y + 6 ; k++){
                    chtype ch  = mvwinch(win , k , hero->x);
                    if(rooms[room].monsters[i].y == k && rooms[room].monsters[i].x == hero->x){
                        rooms[room].monsters[i].health -= damage;
                        mvwprintw(messagewin , 0 , 0, "You attacked with dagger!");
                        wrefresh(messagewin);
                        sleep(2);
                        if(rooms[room].monsters[i].health <= 0){
                            rooms[room].monsters[i].die = true;
                            mvwprintw(messagewin , 0  , 0 , "you killed enemy %s!" , rooms[room].monsters[i].name);
                            wrefresh(messagewin);
                            hero->kill++;
                            sleep(1);
                        }
                        daggercounter--;
                        return;
                        
                    }

                    else if((char)ch == '_'){
                        mvwaddch(win , k-1 ,hero->x , '!');
                        container[hero->x][k-1] = '!';
                        guncontainer[guns].used = 0;
                        guncontainer[guns].x =hero->x;
                        guncontainer[guns].y = k-1;
                        guncontainer[guns].type = 2;
                        guns++;
                        daggercounter--;
                        wrefresh(win);
                        return;
                        
                    }
                }
                mvwaddch(win , hero->y + 4 , hero->x , '!');
                container[hero->x][hero->y + 4] = '!';
                guncontainer[guns].used = 0;
                guncontainer[guns].x = hero->x;
                guncontainer[guns].y = hero->y + 4;
                guncontainer[guns].type = 2;
                guns++;
                daggercounter--;
                wrefresh(win);
            }

        }
        else if(hero->typeofInitialGun == 3  && mwandcounter > 0){

            if(hero->ddrug == true){
                damage = 30;
            }
            else{
                damage = 15;
            } 
            int c = getch();
            if(c=='d'){
                for(int k=hero->x ; k<hero->x + 10 ; k++){
                    chtype ch = mvwinch(win , hero->y  ,k);
                    if(rooms[room].monsters[i].x == k && rooms[room].monsters[i].y == hero->y){
                        rooms[room].monsters[i].health -= damage;
                        mvwprintw(messagewin , 0 , 0, "You attacked with magicwand!");
                        
                        wrefresh(messagewin);
                        sleep(1);
                        if(rooms[room].monsters[i].health <= 0){
                            rooms[room].monsters[i].die = true;
                            mvwprintw(messagewin , 1 , 0 , "you killed enemy %s" , rooms[room].monsters[i].name);
                            hero->kill++;
                            sleep(1);
                        }
                        mwandcounter --;
                        rooms[room].monsters[i].stop = true;
                        return;
                        
                    
                    }
                    else if((char)ch == '|'){
                        mvwaddch(win , hero->y , k-1 , 'I');
                        container[k-1][hero->y] = 'I';
                        guncontainer[guns].used = 0;
                        guncontainer[guns].x = k-1;
                        guncontainer[guns].y = hero->y;
                        guncontainer[guns].type = 3;
                        guns++;
                        mwandcounter--;
                        wrefresh(win);
                        return;
                        
                    }
                }
                mvwaddch(win , hero->y , hero->x+9 , 'I');
                container[hero->x+9][hero->y] = 'I';
                guncontainer[guns].used = 0;
                guncontainer[guns].x = hero->x+9;
                guncontainer[guns].y = hero->y;
                guncontainer[guns].type = 3;
                guns++;
                mwandcounter--;
                wrefresh(win);
            }
            else if(c=='a'){
                for(int k=hero->x ; k>hero->x - 10 ; k--){
                    chtype ch = mvwinch(win , hero->y , k);
                    if(rooms[room].monsters[i].x == k && rooms[room].monsters[i].y == hero->y){
                        rooms[room].monsters[i].health -= damage;
                        mvwprintw(messagewin , 0 , 0, "You attacked with magicwand!");
                        wrefresh(messagewin);
                        sleep(1);
                        if(rooms[room].monsters[i].health <= 0){
                            rooms[room].monsters[i].die = true;
                            mvwprintw(messagewin , 1 , 0 , "you killed enemy %s" , rooms[room].monsters[i].name);
                            wrefresh(messagewin);
                            hero->kill++;
                            sleep(1);
                        }
                        mwandcounter--;
                        rooms[room].monsters[i].stop = true;
                        return;
                       
                    }
                    else if((char)ch == '|'){
                        mvwaddch(win , hero->y , k+1 , 'I');
                        container[k+1][hero->y] = 'I';
                        guncontainer[guns].used = 0;
                        guncontainer[guns].x = k+1;
                        guncontainer[guns].y = hero->y;
                        guncontainer[guns].type = 3;
                        guns++;
                        mwandcounter--;
                        wrefresh(win);
                        return;
                        
                    }
                    
                }
                mvwaddch(win , hero->y , hero->x-9 , 'I');
                container[hero->x-9][hero->y] = 'I';
                guncontainer[guns].used = 0;
                guncontainer[guns].x = hero->x-9;
                guncontainer[guns].y = hero->y;
                guncontainer[guns].type = 3;
                guns++;
                mwandcounter--;
                wrefresh(win);

            }
            else if(c=='w'){
                for(int k=hero-> y; k>hero->y - 10 ; k--){
                    chtype ch = mvwinch(win , k , hero->x);
                    if(rooms[room].monsters[i].y == k && rooms[room].monsters[i].x == hero->x){
                        rooms[room].monsters[i].health -= damage;
                        mvwprintw(messagewin , 0 , 0, "You attacked with magicwand!");
                        wrefresh(messagewin);
                        sleep(1);
                        if(rooms[room].monsters[i].health <= 0){
                            rooms[room].monsters[i].die = true;
                            mvwprintw(messagewin , 1 , 0 , "you killed enemy %s" , rooms[room].monsters[i].name);
                            wrefresh(messagewin);
                            hero->kill++;
                            sleep(1);
                        }
                        mwandcounter--;
                        rooms[room].monsters[i].stop = true;
                        return;
                       
                    }
                    else if((char)ch == '_'){
                        mvwaddch(win ,k+1 ,hero->x, 'I');
                        container[hero->x][k+1] = 'I';
                        guncontainer[guns].used = 0;
                        guncontainer[guns].x = hero->x;
                        guncontainer[guns].y = k+1;
                        guncontainer[guns].type = 3;
                        guns++;
                        mwandcounter--;
                        wrefresh(win);
                        return;
                        
                    }
                }
                mvwaddch(win , hero->y-9 , hero->x , 'I');
                container[hero->x][hero->y-9] = 'I';
                guncontainer[guns].used = 0;
                guncontainer[guns].x = hero->x;
                guncontainer[guns].y = hero->y-9;
                guncontainer[guns].type = 3;
                guns++;
                mwandcounter--;
                wrefresh(win);
            }
            else if(c=='s'){
                for(int k=hero->y ; k<hero->y + 10 ; k++){
                    chtype ch  = mvwinch(win , k , hero->x);
                    if(rooms[room].monsters[i].y == k && rooms[room].monsters[i].x == hero->x){
                        rooms[room].monsters[i].health -= damage;
                        mvwprintw(messagewin , 0 , 0, "You attacked with magicwand!");
                        wrefresh(messagewin);
                        sleep(1);
                        if(rooms[room].monsters[i].health <= 0){
                            rooms[room].monsters[i].die = true;
                            mvwprintw(messagewin , 1 , 0 , "you killed enemy %s" , rooms[room].monsters[i].name);
                            wrefresh(messagewin);
                            hero->kill++;
                            sleep(1);
                        }
                        daggercounter--;
                        rooms[room].monsters[i].stop = true;
                        return;
                        
                    }

                    else if((char)ch == '_'){
                        mvwaddch(win , k-1 ,hero->x , 'I');
                        container[hero->x][k-1] = 'I';
                        guncontainer[guns].used = 0;
                        guncontainer[guns].x = hero->x;
                        guncontainer[guns].y = k-1;
                        guncontainer[guns].type = 3;
                        guns++;
                        mwandcounter--;
                        wrefresh(win);
                        return;
                        
                    }
                }
                mvwaddch(win , hero->y+9 , hero->x , 'I');
                container[hero->x][hero->y+9] = 'I';
                guncontainer[guns].used = 0;
                guncontainer[guns].x = hero->x;
                guncontainer[guns].y = hero->y+9;
                guncontainer[guns].type = 3;
                guns++;
                mwandcounter--;
                wrefresh(win);
            }
        
        }
        else if(hero->typeofInitialGun == 4  && narrowcounter > 0){
            if(hero->ddrug == true){
                damage = 10;
            }
            else{
                damage = 5;
            } 
            int c = getch();
            if(c=='d'){
                for(int k=hero->x ; k<hero->x + 5 ; k++){
                    chtype ch = mvwinch(win , hero->y  ,k);
                    if(rooms[room].monsters[i].x == k && rooms[room].monsters[i].y == hero->y){
                        rooms[room].monsters[i].health -= damage;
                        mvwprintw(messagewin , 0 , 0, "You attacked with arrow!");
                        
                        wrefresh(messagewin);
                        sleep(1);
                        if(rooms[room].monsters[i].health <= 0){
                            rooms[room].monsters[i].die = true;
                            mvwprintw(messagewin , 1 , 0 , "you killed enemy %s" , rooms[room].monsters[i].name);
                            hero->kill++;
                            sleep(1);
                        }
                        narrowcounter --;
                        return;
                        
                        
                    
                    }
                    else if((char)ch == '|'){
                        mvwaddch(win , hero->y , k-1 , '/');
                        container[k-1][hero->y] = '/';
                        guncontainer[guns].used = 0;
                        guncontainer[guns].x = k-1;
                        guncontainer[guns].y = hero->y;
                        guncontainer[guns].type = 4;
                        guns++;
                        narrowcounter--;
                        wrefresh(win);
                        return;
                        
                    }
                }
                mvwaddch(win , hero->y , hero->x+4 , '/');
                container[hero->x+4][hero->y] = '/';
                guncontainer[guns].used = 0;
                guncontainer[guns].x = hero->x+4;
                guncontainer[guns].y = hero->y;
                guncontainer[guns].type = 4;
                guns++;
                narrowcounter--;
                wrefresh(win);
            }
            else if(c=='a'){
                for(int k=hero->x ; k>hero->x - 5 ; k--){
                    chtype ch = mvwinch(win , hero->y , k);
                    if(rooms[room].monsters[i].x == k && rooms[room].monsters[i].y == hero->y){
                        rooms[room].monsters[i].health -= damage;
                        mvwprintw(messagewin , 0 , 0, "You attacked with arrow!");
                        wrefresh(messagewin);
                        sleep(1);
                        if(rooms[room].monsters[i].health <= 0){
                            rooms[room].monsters[i].die = true;
                            mvwprintw(messagewin , 1 , 0 , "you killed enemy %s" , rooms[room].monsters[i].name);
                            wrefresh(messagewin);
                            hero->kill++;
                            sleep(1);
                        }
                            narrowcounter--;
                            return;
                       
                    }
                    else if((char)ch == '|'){
                        mvwaddch(win , hero->y , k+1 , '/');
                        container[k+1][hero->y] = '/';
                        guncontainer[guns].used = 0;
                        guncontainer[guns].x = k+1;
                        guncontainer[guns].y = hero->y;
                        guncontainer[guns].type = 4;
                        guns++;
                        narrowcounter--;
                        wrefresh(win);
                        return;
                        
                    }
                    
                }
                mvwaddch(win , hero->y , hero->x-4 , '/');
                container[hero->x-4][hero->y] = '/';
                guncontainer[guns].used = 0;
                guncontainer[guns].x = hero->x-4;
                guncontainer[guns].y = hero->y;
                guncontainer[guns].type = 4;
                guns++;
                narrowcounter--;
                wrefresh(win);

            }
            else if(c=='w'){
                for(int k=hero-> y; k>hero->y - 5 ; k--){
                    chtype ch = mvwinch(win , k , hero->x);
                    if(rooms[room].monsters[i].y == k && rooms[room].monsters[i].x == hero->x){
                        rooms[room].monsters[i].health -= damage;
                        mvwprintw(messagewin , 0 , 0, "You attacked with arrow!");
                        wrefresh(messagewin);
                        sleep(1);
                        if(rooms[room].monsters[i].health <= 0){
                            rooms[room].monsters[i].die = true;
                            mvwprintw(messagewin , 1 , 0 , "you killed enemy %s" , rooms[room].monsters[i].name);
                            wrefresh(messagewin);
                            hero->kill++;
                            sleep(1);
                        }
                            narrowcounter--;
                            return;
                       
                    }
                    else if((char)ch == '_'){
                        mvwaddch(win ,k+1 ,hero->x, '/');
                        container[hero->x][k+1] = '/';
                        guncontainer[guns].used = 0;
                        guncontainer[guns].x = hero->x;
                        guncontainer[guns].y = k+1;
                        guncontainer[guns].type = 4;
                        guns++;
                        mwandcounter--;
                        wrefresh(win);
                        return;
                        
                    }
                }
                mvwaddch(win , hero->y - 4 , hero->x , '/');
                container[hero->x][hero->y-4] = '/';
                guncontainer[guns].used = 0;
                guncontainer[guns].x = hero->x;
                guncontainer[guns].y = hero->y-4;
                guncontainer[guns].type = 4;
                guns++;
                narrowcounter--;
                wrefresh(win);
            }
            else if(c=='s'){
                for(int k=hero->y ; k<hero->y + 5 ; k++){
                    chtype ch  = mvwinch(win , k , hero->x);
                    if(rooms[room].monsters[i].y == k && rooms[room].monsters[i].x == hero->x){
                        rooms[room].monsters[i].health -= damage;
                        mvwprintw(messagewin , 0 , 0, "You attacked with arrow!");
                        wrefresh(messagewin);
                        sleep(1);
                        if(rooms[room].monsters[i].health <= 0){
                            rooms[room].monsters[i].die = true;
                            mvwprintw(messagewin , 1 , 0 , "you killed enemy %s" , rooms[room].monsters[i].name);
                            wrefresh(messagewin);
                            hero->kill++;
                            sleep(1);
                        }
                            narrowcounter--;
                            return;
                        
                    }

                    else if((char)ch == '_'){
                        mvwaddch(win , k-1 ,hero->x , '/');
                        container[hero->x][k-1] = '/';
                        guncontainer[guns].used = 0;
                        guncontainer[guns].x = hero->x;
                        guncontainer[guns].y = k-1;
                        guncontainer[guns].type = 3;
                        guns++;
                        narrowcounter--;
                        wrefresh(win);
                        return;
                        
                    }
                }
                mvwaddch(win , hero->y+4 , hero->x , '/');
                container[hero->x][hero->y+4] = '/';
                guncontainer[guns].used = 0;
                guncontainer[guns].x = hero->x;
                guncontainer[guns].y = hero->y+4;
                guncontainer[guns].type = 4;
                guns++;
                narrowcounter--;
                wrefresh(win);
            }
        
        }
    }
}

void cheetcode(WINDOW* win , Hero* hero  , char container[MAP_WIDTH][MAP_HEIGHT]){
    int c = getch();
    chtype ch = container[hero->x][hero->y];
    switch(c){
        case 's':
            while((char)ch == '#'){
                if(container[hero->x][hero->y + 1] != '#'){
                    break;
                }
                hero->y = hero->y + 1;
                ch = container[hero->x][hero->y];
            }
            break;

        case 'a':
            while((char)ch == '#'){
                if(container[hero->x - 1][hero->y] != '#'){
                    break;
                }
                hero->x = hero->x - 1;
                ch =container[hero->x][hero->y];
            }
            break;

        case 'w': 
            while (hero->y - 1 >= 0 && container[hero->x][hero->y] == '#') {
                if (container[hero->x][hero->y - 1] != '#') {
                    break;
                }
                hero->y -= 1;
            }
            break;

        case 'd':
            while (hero->x + 1 < MAP_WIDTH && container[hero->x][hero->y] == '#') {
                if (container[hero->x + 1][hero->y] != '#') {
                    break;
                }
                hero->x += 1;
            }
            break;
            }
}
    




void drawRoom(WINDOW* win, Room room) {
    for (int i = 0; i < room.height; i++) {
        for (int j = 0; j < room.width; j++) {
            if (i == 0) {
                mvwaddch(win, room.y + i, room.x + j, '_');
            } else if (i == room.height - 1) {
                if (j == 0 || j == room.width - 1) {
                    mvwaddch(win, room.y + i, room.x + j, '|');
                } else {
                    mvwaddch(win, room.y + i, room.x + j, '_');
                }
            } else {
                if (j == 0 || j == room.width - 1) {
                    mvwaddch(win, room.y + i, room.x + j, '|');
                } else {
                    mvwaddch(win, room.y + i, room.x + j, '.');
                }
            }
        }
    }
    drawpillar(win, room);
}
void roomtype(WINDOW* win , Room* rooms , int roomcount){
    if(floorcount == 4){
        rooms[roomcount -1].typeroom = 3;
        int poison = roomcount / 3 ; 
        for(int i=0 ; i<poison ; i++){
            rooms[i].typeroom = 2;

        }
        rooms[roomcount - 2].typeroom = 4;


    }
    else {
        int poison = roomcount / 3;
        for(int i=0 ; i<poison ; i++){
            rooms[i].typeroom = 2;
        }
        rooms[roomcount - 1].typeroom = 4;

    }
}

void drawCorridor(WINDOW* win, int x1, int y1, int x2, int y2, Room* rooms, int roomCount) {
    int x = x1, y = y1;

    while (x != x2 || y != y2) {
        if (!isInsideRoom(x, y, rooms, roomCount)) {
            mvwaddch(win, y, x, '#');
        } else {
            chtype ch1 = mvwinch(win, y + 1, x) & A_CHARTEXT;
            chtype ch2 = mvwinch(win, y - 1, x) & A_CHARTEXT;
            chtype ch3 = mvwinch(win, y, x + 1) & A_CHARTEXT;
            chtype ch4 = mvwinch(win, y, x - 1) & A_CHARTEXT;

            if ((ch1 == '#' || ch2 == '#' || ch3 == '#' || ch4 == '#')) {
                mvwaddch(win, y, x, '+');
            }
        }

        if (x != x2 && y != y2) {
            x += (x < x2) ? 1 : -1;
            y += (y < y2) ? 1 : -1;
        } else if (x != x2) {
            x += (x < x2) ? 1 : -1;
        } else if (y != y2) {
            y += (y < y2) ? 1 : -1;
        }
    }
}

void makedoor(WINDOW* win, int x, int y, Room* rooms, int roomCount) {
    chtype ch1 = mvwinch(win, y + 1, x);
    chtype ch2 = mvwinch(win, y - 1, x);
    chtype ch3 = mvwinch(win, y, x + 1);
    chtype ch4 = mvwinch(win, y, x - 1);

    if (isInsideRoom(x, y, rooms, roomCount)) {
        if ((char)ch1 == '#' || (char)ch2 == '#' || (char)ch3 == '#' || (char)ch4 == '#') {
            mvwaddch(win, y, x, '+');
        }
    }
}
int timer(int seconds) {
    clock_t start_time = clock(); 
    while (1) {
        clock_t current_time = clock();
        double elapsed_time = (double)(current_time - start_time) / CLOCKS_PER_SEC;

        if (elapsed_time >= seconds) {
            return 0;
            
        }
    }
}
void passwordkey(WINDOW* mapWin , Room* rooms  , char container[MAP_WIDTH][MAP_HEIGHT]){
    Room room = rooms[4];
    int xrnd = room.x + 1 + rand() % (room.width - 2);
    int yrnd = room.y + 1 + rand() % (room.height - 2);
    container[xrnd][yrnd] = '&';
    mvwaddch(mapWin , yrnd , xrnd , '&');
    
}
int generatepassword(WINDOW* win , WINDOW* messagewin , Pdoor* pdoor){
    int password = 1000 + rand() % 9000;
    pdoor->password = password;
    
    pdoor->open = false;
    return password;
}
void isonpasswordkey(WINDOW* win, WINDOW* messagewin, int x, int y, Pdoor* pdoor) {
    wclear(messagewin);
    chtype ch = mvwinch(win, y, x) & A_CHARTEXT; 
    if ((char)ch == '&') { 
        mvwprintw(messagewin, 0, 0, "You found the key!"); 
        wrefresh(messagewin); 

    
        int password = generatepassword(win, messagewin, pdoor);
        mvwprintw(messagewin , 1 , 0 , "%d" , password);        



        wrefresh(messagewin);
    }
}



bool isitpassdoor(WINDOW* win, WINDOW* messagewin, int x, int y, Pdoor* pdoor) {

    wclear(messagewin);
    chtype ch = mvwinch(win, y, x);
    if ((char)ch == '@' && pdoor->open == false ){
        if (pdoor->alwaysclose == true) {
            attron(COLOR_PAIR(1));
             mvwprintw(messagewin, 0, 0, "The door is permanently locked!");
             attroff(COLOR_PAIR(1));
            wrefresh(messagewin);
            sleep(2);
            return false;
        }
        else{

 
            int input = -1; 
            int wrongs = 0;

            while (wrongs < 3) {
                mvwprintw(messagewin, 0, 0, "Enter password: ");
                wrefresh(messagewin);
                echo(); 
                mvwscanw(messagewin, 1, 0, "%4d", &input);
                noecho(); 

                if (input == pdoor->password) {
                    pdoor->open = true;
                    wattron(win , COLOR_PAIR(5));
                    mvwaddch(win , y ,x , '@');
                    wattroff(win , COLOR_PAIR(5));
                    mvwprintw(messagewin, 2, 0, "Access granted!");
                    wrefresh(messagewin);
                    sleep(2);
                    return true; 
                } else {
                    wrongs++;
                    mvwprintw(messagewin, 2, 0, "Wrong password! Attempts left: %d", 3 - wrongs);
                    wrefresh(messagewin);
                }
            }

            
            mvwprintw(messagewin, 3, 0, "The door is now permanently locked!");
            wrefresh(messagewin);
            sleep(2);
            pdoor->alwaysclose = true; 
        
            return false;
        }
    }
    return true;
}
void Dheartmove(Hero* hero , WINDOW* messagewin){
    if((hero->move) % 50 == 0){
        hero->heart --;
        mvwprintw(messagewin ,0,0, "Hero is hungry! HP : %d" , hero->heart);
        
        wrefresh(messagewin);
        getch();
    }
}


void generateFloor(WINDOW* mapWin, WINDOW* messagewin, Room rooms[], int* roomCount, Hero* hero, Stair* stair, bool seen[MAP_WIDTH][MAP_HEIGHT], char container[MAP_WIDTH][MAP_HEIGHT] , Pdoor* pdoor , Gold* goldcontainer) {
    floorcount++;
    werase(mapWin);
    mvwprintw(messagewin ,0,0, "You are in floor %d" , floorcount);
    wrefresh(messagewin);
    start_color();
    init_pair(1 , COLOR_RED , COLOR_BLACK);

    *roomCount = 0;
    memset(seen, 0, sizeof(seen)); 
    memset(container, '.', sizeof(container)); 

    int tryes =0 ; 
    while (*roomCount < MAX_ROOMS && tryes<1000) {
        tryes++;
        Room newRoom;
        newRoom.width = rand() % (MAX_ROOM_SIZE - MIN_ROOM_SIZE + 1) + MIN_ROOM_SIZE;
        newRoom.height = rand() % (MAX_ROOM_SIZE - MIN_ROOM_SIZE + 1) + MIN_ROOM_SIZE;
        newRoom.x = rand() % (MAP_WIDTH - newRoom.width - 1) + 1;
        newRoom.y = rand() % (MAP_HEIGHT - newRoom.height - 1) + 1;
        newRoom.haspillar = haspillar(&newRoom);

        if (!doesOverlap(rooms, *roomCount, newRoom)) {
            rooms[*roomCount] = newRoom;
            (*roomCount)++;
        }
    }

    
    for (int i = 0; i < *roomCount; i++) {
        drawRoom(mapWin, rooms[i]);

        if (i > 0) {
            int prevX = rooms[i - 1].x + rooms[i - 1].width / 2;
            int prevY = rooms[i - 1].y + rooms[i - 1].height / 2;
            int currX = rooms[i].x + rooms[i].width / 2;
            int currY = rooms[i].y + rooms[i].height / 2;
            drawCorridor(mapWin, prevX, prevY, currX, currY, rooms, *roomCount);
        }
        
    }

    roomtype(mapWin , rooms , *roomCount);
    placeTraps(rooms , trapcounter , *roomCount);
    foodsinroom(mapWin , rooms , *roomCount , container);
    bgoldsinroom( mapWin ,  rooms , *roomCount , container,bgoldcontainer);
    goldsinroom(mapWin , rooms , *roomCount , container , goldcontainer);
    poisonsinroom(mapWin , rooms , *roomCount , container , poisoncontainer);
    gunsinroom(mapWin , rooms ,*roomCount ,container , guncontainer);
    monstersinroom(mapWin, rooms , *roomCount , monstercontainer , container);
    cupinroom(mapWin , rooms , *roomCount , container);
    
    for (int i = 0; i < MAP_WIDTH; i++) {
        for (int j = 0; j < MAP_HEIGHT; j++) {
            makedoor(mapWin, i, j, rooms, *roomCount);
        }
    }
    char x_doors[60];
    char y_doors[60];
    int doorcount = 0;
    for(int i=0 ; i<MAP_WIDTH ; i++){
        for(int j=0; j<MAP_HEIGHT ; j++){
            chtype ch = mvwinch(mapWin , j , i);
            if((char)ch == '+'){
                x_doors[doorcount] = i;
                y_doors[doorcount] = j;
                doorcount++;
            }
        }
       
    }

    container[x_doors[3]][y_doors[3]] = '@';
    attron(COLOR_PAIR(1));
    mvwaddch(mapWin , y_doors[3], x_doors[3] , '@');
    attroff(COLOR_PAIR(1));
    wrefresh(mapWin);
    passwordkey(mapWin , rooms , container);
    pdoor->x = x_doors[3];
    pdoor->y =y_doors[3];
    
    pdoor->open = false;
    pdoor->alwaysclose = false;
    stair->exists = false;
    if(floorcount != 4){
        placestair(mapWin, rooms, *roomCount, stair);
    }

    
    int heroX, heroY;
    HeroPlace(mapWin, rooms, *roomCount, &heroX, &heroY);
    hero->x = heroX;
    hero->y = heroY;
    mvwaddch(mapWin, hero->y, hero->x, '.');

    
    map_container(mapWin, container);
    updateVisibility(mapWin, *hero, 1, seen , rooms , roomCount);

    
    wrefresh(mapWin);
}
void save_game_binary(Hero* hero, char container[MAP_WIDTH][MAP_HEIGHT], int floorcount , WINDOW* messagewin) {
    FILE* file = fopen("save.bin", "wb");
    if (file == NULL) {
        perror("خطا در باز کردن فایل برای ذخیره");
        return;
    }

    
    fwrite(hero, sizeof(Hero), 1, file);

    
    fwrite(&floorcount, sizeof(int), 1, file);

    
    fwrite(container, sizeof(char), MAP_WIDTH * MAP_HEIGHT, file);

    fclose(file);
    wclear(messagewin);
    mvwprintw(messagewin, 0 , 0 , "game saved!");
    wrefresh(messagewin);
    sleep(1);
    
}
void save_explored_map(bool seen[MAP_WIDTH][MAP_HEIGHT], int floorcount , WINDOW* messagewin) {
    char filename[20] = "save.bin";
    

    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        perror("خطا در ذخیره نقشه");
        return;
    }

    fwrite(&floorcount, sizeof(int), 1, file);  
    fwrite(seen, sizeof(bool), MAP_WIDTH * MAP_HEIGHT, file);  

    fclose(file);
    mvwprintw(messagewin , 1 , 0 , "map saved! , please wait seconds!");
    wrefresh(messagewin);
    sleep(2);
}
void load_game_binary(Hero* hero, char container[MAP_WIDTH][MAP_HEIGHT]) {
    FILE* file = fopen("save.bin", "rb");
    if (file == NULL) {
        perror("فایل ذخیره‌شده‌ی باینری یافت نشد");
        return;
    }

    
    fread(hero, sizeof(Hero), 1, file);

    


    
    fread(container, sizeof(char), MAP_WIDTH * MAP_HEIGHT, file);

    fclose(file);
    
}
void load_explored_map(bool seen[MAP_WIDTH][MAP_HEIGHT], int* floorcount) {
    char filename[20];
    sprintf(filename, "save_floor_%d.bin", *floorcount);

    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("فایل ذخیره‌شده برای این طبقه یافت نشد، بازی جدیدی آغاز می‌شود.\n");
        memset(seen, false, sizeof(bool) * MAP_WIDTH * MAP_HEIGHT);  
        return;
    }

    fread(floorcount, sizeof(int), 1, file);  
    fread(seen, sizeof(bool), MAP_WIDTH * MAP_HEIGHT, file);  

    fclose(file);
    printf("نقشه کشف‌شده طبقه %d بارگذاری شد.\n", *floorcount);
}
void saveGameState(const char *filename ) {
    GameState state;
    
    // مقداردهی به `state` از متغیرهای `global`
    state.floorcount = floorcount;
    state.guns = guns;
    state.macecounter = macecounter;
    state.daggercounter = daggercounter;
    state.mwandcounter = mwandcounter;
    state.narrowcounter = narrowcounter;
    state.swordcounter = swordcounter;
    state.scounter = scounter;
    state.dcounter = dcounter;
    state.hcounter = hcounter;
    state.smove = smove;
    state.dmove = dmove;
    state.hmove = hmove;
    state.enemycount = enemycount;
    state.enemy = enemy;

    // کپی آرایه‌های نقشه و وضعیت دیده شدن
    memcpy(state.seen, seen, sizeof(seen));
    memcpy(state.seen2, seen2, sizeof(seen2));
    memcpy(state.seen3, seen3, sizeof(seen3));
    memcpy(state.seen4, seen4, sizeof(seen4));
    memcpy(state.container, container, sizeof(container));
    memcpy(state.container2, container2, sizeof(container2));
    memcpy(state.container3, container3, sizeof(container3));
    memcpy(state.container4, container4, sizeof(container4));

    // کپی سایر آرایه‌ها
    memcpy(state.guncontainer, guncontainer, sizeof(guncontainer));
    memcpy(state.goldcontainer, goldcontainer, sizeof(goldcontainer));
    memcpy(state.bgoldcontainer, bgoldcontainer, sizeof(bgoldcontainer));
    memcpy(state.trapcounter, trapcounter, sizeof(trapcounter));
    memcpy(state.poisoncontainer, poisoncontainer, sizeof(poisoncontainer));
    memcpy(state.monstercontainer, monstercontainer, sizeof(monstercontainer));
    
    state.hero = hero;

    // ذخیره در فایل
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("خطا در ذخیره‌ی وضعیت بازی");
        return;
    }
    fwrite(&state, sizeof(GameState), 1, file);
    fclose(file);
}
int loadGameState(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("خطا در بارگذاری وضعیت بازی");
        return 0;
    }

    GameState state;


    fread(&state, sizeof(GameState), 1, file);
    fclose(file);

    // مقداردهی مجدد به متغیرهای `global`
    floorcount = state.floorcount;
    guns = state.guns;
    macecounter = state.macecounter;
    daggercounter = state.daggercounter;
    mwandcounter = state.mwandcounter;
    narrowcounter = state.narrowcounter;
    swordcounter = state.swordcounter;
    scounter = state.scounter;
    dcounter = state.dcounter;
    hcounter = state.hcounter;
    smove = state.smove;
    dmove = state.dmove;
    hmove = state.hmove;
    enemycount = state.enemycount;
    enemy = state.enemy;

    // بازیابی آرایه‌های نقشه و دیده شدن
    memcpy(seen, state.seen, sizeof(seen));
    memcpy(seen2, state.seen2, sizeof(seen2));
    memcpy(seen3, state.seen3, sizeof(seen3));
    memcpy(seen4, state.seen4, sizeof(seen4));
    memcpy(container, state.container, sizeof(container));
    memcpy(container2, state.container2, sizeof(container2));
    memcpy(container3, state.container3, sizeof(container3));
    memcpy(container4, state.container4, sizeof(container4));

    // بازیابی سایر آرایه‌ها
    memcpy(guncontainer, state.guncontainer, sizeof(guncontainer));
    memcpy(goldcontainer, state.goldcontainer, sizeof(goldcontainer));
    memcpy(bgoldcontainer, state.bgoldcontainer, sizeof(bgoldcontainer));
    memcpy(trapcounter, state.trapcounter, sizeof(trapcounter));
    memcpy(poisoncontainer, state.poisoncontainer, sizeof(poisoncontainer));
    memcpy(monstercontainer, state.monstercontainer, sizeof(monstercontainer));

    hero = state.hero;

    return 1;
}

int gameover(Hero* hero){
    if(hero->heart < 0){
        return 0;
    }
    return 1;
}
int wingame(Hero* hero  , Room* rooms , int roomcount){
    for(int i=0 ; i<roomcount ; i++){
        if(rooms[i].typeroom == 3){
            int count = 0;
            for(int j=0 ; j<rooms[i].monstercount ; j++){
                if(rooms[i].monsters[j].die){
                    count++;
                }
            }
            if(count == 3 && hero->jam == true){
                return 1;
            }
        }
    }
    return 0;

}

int main() {
    srand(time(0));
    setlocale(LC_ALL ,"");
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr , true);
    char *choices[] = {
        "Sign in",
        "Login",
        "Login as a guest",
        "Exit"
    };
    
    int n_choices = sizeof(choices) / sizeof(choices[0]);
    int result = start_game(choices , n_choices);
    if(result == 1){
        char savegame[30] ;
        strcpy( savegame  , convertor(heroname , "games" , herogame));
        start_color();
        init_pair(1 , COLOR_RED , COLOR_BLACK);
        init_pair(2 , COLOR_MAGENTA , COLOR_BLACK);
        init_pair(3 , COLOR_CYAN , COLOR_BLACK);
        init_pair(4 , COLOR_YELLOW , COLOR_BLACK);
        init_pair(5 , COLOR_GREEN , COLOR_BLACK);
        init_pair(6, COLOR_BLUE , COLOR_BLACK);
        init_color(COLOR_CYAN , 500 , 300, 0);
        init_pair(7 , COLOR_CYAN , COLOR_BLACK);

        WINDOW* mapWin = newwin(MAP_HEIGHT + 2, MAP_WIDTH + 2, 0, 0);
        WINDOW* messagewin = newwin(MAP_HEIGHT + 4, 40, 0, MAP_WIDTH + 2);
        
        box(messagewin, 0, 0); 
        noecho();


        
        refresh();

        
        hero.food = 0;
        hero.heart = 100;
        hero.move = 1;
        hero.typeofInitialGun = 1;
        Stair stair;
        Pdoor pdoor;
        Room rooms[MAX_ROOMS];
        int roomCount = 0;

        
        generateFloor(mapWin ,messagewin, rooms, &roomCount, &hero, &stair, seen, container , &pdoor , goldcontainer);
    
        keypad(stdscr, TRUE);
        wrefresh(mapWin);
        refresh();
        int check1;
        int check2;
        int c;
        do {
            if(floorcount == 1){
                drawSeenMap(mapWin, container, seen , &pdoor , rooms , roomCount);
            }
            if(floorcount == 2){
                drawSeenMap(mapWin, container, seen2 , &pdoor , rooms ,roomCount);
            }
            if(floorcount == 3){
                drawSeenMap(mapWin, container, seen3 , &pdoor , rooms , roomCount);
            }
            if(floorcount == 4){
                drawSeenMap(mapWin, container, seen4 , &pdoor ,rooms ,  roomCount);
            }
            c = getch();
            int prevX = hero.x;
            int prevY = hero.y;

            
            switch (c) {
                case 50: 
                    if (isitwallorO(mapWin, hero.x, hero.y + 1) && isitpassdoor(mapWin ,messagewin , hero.x , hero.y + 1 , &pdoor)) {
                        if(hero.sdrug){
                            if(isitwallorOdrug(mapWin , hero.x , hero.y+1 , c)){
                                hero.y+=2;
                                hero.move ++;
                                Dheartmove(&hero , messagewin);
                                activatemonsters(mapWin, rooms , roomCount , hero.x , hero.y , monstercontainer , &hero , messagewin);
                                
            
                                

                                if(floorcount == 1){
                                    markseen(hero.x , hero.y , seen);
                                }
                                if(floorcount == 2){
                                    markseen(hero.x , hero.y , seen2);
                                }
                                if(floorcount == 3){
                                    markseen(hero.x , hero.y , seen3);
                                }
                                if(floorcount == 4){
                                    markseen(hero.x , hero.y , seen4);
                                }
                                movecontrol(&hero);
                            }

                        }
                        else{
                            hero.y++;
                            hero.move ++;
                            Dheartmove(&hero , messagewin);
                            activatemonsters(mapWin, rooms , roomCount , hero.x , hero.y , monstercontainer , &hero , messagewin);
                            
        
                            

                            if(floorcount == 1){
                                markseen(hero.x , hero.y , seen);
                            }
                            if(floorcount == 2){
                                markseen(hero.x , hero.y , seen2);
                            }
                            if(floorcount == 3){
                                markseen(hero.x , hero.y , seen3);
                            }
                            if(floorcount == 4){
                                markseen(hero.x , hero.y , seen4);
                            }
                        }
                    }

                    break;
                case 56:  //up
                    if (isitwallorO(mapWin, hero.x, hero.y - 1) && isitpassdoor(mapWin ,messagewin , hero.x , hero.y - 1 , &pdoor)) {
                        if(hero.sdrug){
                            if(isitwallorOdrug(mapWin , hero.x , hero.y-1 , c)){
                                hero.y-=2;
                                hero.move ++;
                                Dheartmove(&hero , messagewin);
                                activatemonsters(mapWin, rooms , roomCount , hero.x , hero.y , monstercontainer , &hero , messagewin);
                                
            
                                

                                if(floorcount == 1){
                                    markseen(hero.x , hero.y , seen);
                                }
                                if(floorcount == 2){
                                    markseen(hero.x , hero.y , seen2);
                                }
                                if(floorcount == 3){
                                    markseen(hero.x , hero.y , seen3);
                                }
                                if(floorcount == 4){
                                    markseen(hero.x , hero.y , seen4);
                                }
                                movecontrol(&hero);
                            }

                        }
                        else{
                            hero.y--;
                            hero.move ++;
                            Dheartmove(&hero , messagewin);
                            activatemonsters(mapWin, rooms , roomCount , hero.x , hero.y , monstercontainer , &hero , messagewin);
                            
        
                            

                            if(floorcount == 1){
                                markseen(hero.x , hero.y , seen);
                            }
                            if(floorcount == 2){
                                markseen(hero.x , hero.y , seen2);
                            }
                            if(floorcount == 3){
                                markseen(hero.x , hero.y , seen3);
                            }
                            if(floorcount == 4){
                                markseen(hero.x , hero.y , seen4);
                            }
                        }
                    }
 
                    break;
                case 54:
                    if (isitwallorO(mapWin, hero.x + 1, hero.y) && isitpassdoor(mapWin ,messagewin , hero.x +1  , hero.y , &pdoor)) {
                        if(hero.sdrug){
                            if(isitwallorOdrug(mapWin , hero.x + 1 , hero.y, c)){
                                hero.x+=2;
                                hero.move ++;
                                Dheartmove(&hero , messagewin);
                                activatemonsters(mapWin, rooms , roomCount , hero.x , hero.y , monstercontainer , &hero , messagewin);
                                // اگر قهرمان از اتاق خارج شد، نقشه را بازسازی کن
            
                                

                                if(floorcount == 1){
                                    markseen(hero.x , hero.y , seen);
                                }
                                if(floorcount == 2){
                                    markseen(hero.x , hero.y , seen2);
                                }
                                if(floorcount == 3){
                                    markseen(hero.x , hero.y , seen3);
                                }
                                if(floorcount == 4){
                                    markseen(hero.x , hero.y , seen4);
                                }
                                movecontrol(&hero);
                            }

                        }
                        else{
                            hero.x++;
                            hero.move ++;
                            Dheartmove(&hero , messagewin);
                            activatemonsters(mapWin, rooms , roomCount , hero.x , hero.y , monstercontainer , &hero , messagewin);
                            // اگر قهرمان از اتاق خارج شد، نقشه را بازسازی کن
        
                            

                            if(floorcount == 1){
                                markseen(hero.x , hero.y , seen);
                            }
                            if(floorcount == 2){
                                markseen(hero.x , hero.y , seen2);
                            }
                            if(floorcount == 3){
                                markseen(hero.x , hero.y , seen3);
                            }
                            if(floorcount == 4){
                                markseen(hero.x , hero.y , seen4);
                            }
                        }
                    }
                    

                    break;
                case 52:
                    if (isitwallorO(mapWin, hero.x - 1, hero.y) && isitpassdoor(mapWin ,messagewin , hero.x -1 , hero.y , &pdoor)) {
                        if(hero.sdrug){
                            if(isitwallorOdrug(mapWin , hero.x -1  , hero.y , c)){
                                hero.x-=2;
                                hero.move ++;
                                Dheartmove(&hero , messagewin);
                                activatemonsters(mapWin, rooms , roomCount , hero.x , hero.y , monstercontainer , &hero , messagewin);
                                // اگر قهرمان از اتاق خارج شد، نقشه را بازسازی کن
            
                                

                                if(floorcount == 1){
                                    markseen(hero.x , hero.y , seen);
                                }
                                if(floorcount == 2){
                                    markseen(hero.x , hero.y , seen2);
                                }
                                if(floorcount == 3){
                                    markseen(hero.x , hero.y , seen3);
                                }
                                if(floorcount == 4){
                                    markseen(hero.x , hero.y , seen4);
                                }
                                movecontrol(&hero);
                            }

                        }
                        else{
                            hero.x--;
                            hero.move ++;
                            Dheartmove(&hero , messagewin);
                            activatemonsters(mapWin, rooms , roomCount , hero.x , hero.y , monstercontainer , &hero , messagewin);
                            // اگر قهرمان از اتاق خارج شد، نقشه را بازسازی کن
        
                            

                            if(floorcount == 1){
                                markseen(hero.x , hero.y , seen);
                            }
                            if(floorcount == 2){
                                markseen(hero.x , hero.y , seen2);
                            }
                            if(floorcount == 3){
                                markseen(hero.x , hero.y , seen3);
                            }
                            if(floorcount == 4){
                                markseen(hero.x , hero.y , seen4);
                            }
                        }
                    }

                    break;
                case 55:
                    if(isitwallorO(mapWin , hero.x - 1 , hero.y - 1 ) && isitpassdoor(mapWin ,messagewin , hero.x - 1 , hero.y - 1 , &pdoor)){
                        hero.x--;
                        hero.y--;
                        hero.move++;
                        Dheartmove(&hero , messagewin);
                        activatemonsters(mapWin, rooms , roomCount , hero.x , hero.y , monstercontainer , &hero , messagewin);

                        
                        if(floorcount == 1){
                            markseen(hero.x , hero.y , seen);
                        }
                        if(floorcount == 2){
                            markseen(hero.x , hero.y , seen2);
                        }
                        if(floorcount == 3){
                            markseen(hero.x , hero.y , seen3);
                        }
                        if(floorcount == 4){
                            markseen(hero.x , hero.y , seen4);
                        }
                    }
                    int check1 = gameover(&hero);
  
                    break;
                case 57:
                    if(isitwallorO(mapWin , hero.x + 1 , hero.y - 1 ) && isitpassdoor(mapWin ,messagewin , hero.x + 1 , hero.y - 1 , &pdoor)){
                        hero.x ++;
                        hero.y --;
                        hero.move++;
                        Dheartmove(&hero , messagewin);
                        activatemonsters(mapWin, rooms , roomCount , hero.x , hero.y , monstercontainer , &hero , messagewin);

                        if(floorcount == 1){
                            markseen(hero.x , hero.y , seen);
                        }
                        if(floorcount == 2){
                            markseen(hero.x , hero.y , seen2);
                        }
                        if(floorcount == 3){
                            markseen(hero.x , hero.y , seen3);
                        }
                        if(floorcount == 4){
                            markseen(hero.x , hero.y , seen4);
                        }
                    }

                    break;
                case 49:
                    if(isitwallorO(mapWin , hero.x - 1 , hero.y + 1 ) && isitpassdoor(mapWin ,messagewin , hero.x - 1 , hero.y + 1, &pdoor)){
                        hero.x --;
                        hero.y++;
                        hero.move++;
                        Dheartmove(&hero , messagewin);
                        activatemonsters(mapWin, rooms , roomCount , hero.x , hero.y , monstercontainer , &hero , messagewin);

                        if(floorcount == 1){
                            markseen(hero.x , hero.y , seen);
                        }
                        if(floorcount == 2){
                            markseen(hero.x , hero.y , seen2);
                        }
                        if(floorcount == 3){
                            markseen(hero.x , hero.y , seen3);
                        }
                        if(floorcount == 4){
                            markseen(hero.x , hero.y , seen4);
                        }
                    }

                    break;
                case 51:
                    if(isitwallorO(mapWin , hero.x + 1 , hero.y + 1 ) && isitpassdoor(mapWin ,messagewin, hero.x + 1 , hero.y + 1, &pdoor)){
                        hero.x++;
                        hero.y++;
                        hero.move++;
                        Dheartmove(&hero , messagewin);
                        activatemonsters(mapWin, rooms , roomCount , hero.x , hero.y , monstercontainer , &hero , messagewin);

                        if(floorcount == 1){
                            markseen(hero.x , hero.y , seen);
                        }
                        if(floorcount == 2){
                            markseen(hero.x , hero.y , seen2);
                        }
                        if(floorcount == 3){
                            markseen(hero.x , hero.y , seen3);
                        }
                        if(floorcount == 4){
                            markseen(hero.x , hero.y , seen4);
                        }
                    }

                    
                    break;
                case 101:

                    if(isitongun(mapWin ,messagewin , hero.x , hero.y)){
                        addtoinventory(mapWin , messagewin , &hero , hero.x , hero.y , guncontainer );
                    }
                    if(isitonpoison(mapWin , messagewin , hero.x , hero.y)){
                        addtoinventoryp(mapWin , messagewin , &hero , hero.x , hero.y , poisoncontainer);
                    }
                    
                    break;
                case 117 :
                    addfoodhero(mapWin , &hero ,container , hero.x , hero.y);
                    break;
                case 105:
                    changegun( mapWin ,  messagewin ,  &hero );
                    break;
                case 112:
                    usepoison(mapWin, messagewin , &hero);
                    break;
                case 's':
                    saveGameState(savegame);
                    break;
                case 'a':
                    attackmonster( mapWin ,  messagewin,  &hero, rooms, roomCount, monstercontainer);
                    break;
                case 'f':
                    
                        
                    showingfoods(mapWin , messagewin , &hero);
                    
                    break;
                case 'c':
                    cheetcode(mapWin , &hero , container);
                    break;
                
                case 'h':
                    wclear(messagewin);
                    mvwprintw(messagewin , 0  ,0  , "HP : %d" , hero.heart);
                    wrefresh(messagewin);
                    sleep(2);
                case 'l':
                    load_game_binary(&hero , container);

                }
                
                

            chtype ch1  = mvwinch(mapWin , hero.y , hero.x);
            if((char)ch1 != 'D' && (char)ch1 != 'S' && (char)ch1 != 'C' && (char)ch1 != 'X'){
                isontrap(mapWin,messagewin , rooms, roomCount, &hero , trapcounter , container);
            }

            isonpasswordkey(mapWin , messagewin , hero.x , hero.y , &pdoor);
            isitingold( mapWin, messagewin ,hero.x , hero.y ,  &hero , goldcontainer);
            isitoncup(mapWin , messagewin , hero.x , hero.y , &hero);
            isitinbgold(mapWin, messagewin, hero.x , hero.y , &hero , bgoldcontainer);
            
            for(int i=0 ; i<enemy ; i++){
                if(monstercontainer[i].active == true){
                    mvwaddch(mapWin, monstercontainer[i].y , monstercontainer[i].x , monstercontainer[i].nmd);
                }
            }

            wrefresh(messagewin);
            if (stair.exists && hero.x == stair.x && hero.y == stair.y) {
                
                generateFloor(mapWin, messagewin, rooms, &roomCount, &hero, &stair, seen, container , &pdoor , goldcontainer);
            }

            // به‌روزرسانی نقشه و موقعیت قهرمان
            if(floorcount == 1){
                updateVisibility(mapWin, hero, 1, seen , rooms , roomCount);
            }
            if(floorcount == 2){
                updateVisibility(mapWin, hero, 1, seen2 , rooms ,roomCount);
            }
            if(floorcount == 3){
                updateVisibility(mapWin, hero, 1, seen3 , rooms , roomCount);
            }
            if(floorcount == 4){
                updateVisibility(mapWin, hero, 1, seen4 , rooms , roomCount);
            }
            check1 = gameover(&hero);
            if(!check1){
                wclear(messagewin);
                mvwprintw(messagewin , 0 , 0 , "You lost ):");
                wrefresh(messagewin);
                getch();
                // delwin(mapWin);
                // endwin();
                break;
            }
            check2 = wingame(&hero , rooms , roomCount );
            if (check2) {
                wchar_t fire[] = L"\U0001F525";  
                wchar_t heart[] = L"\u2764";      
                hero.score = hero.goldcount + (hero.kill) * 2 + hero.heart + 10 * dificulty;
                wclear(messagewin);
                mvwprintw(messagewin, 0, 0, "Victory! ");  
                waddwstr(messagewin, fire); 
                waddwstr(messagewin, heart);
                int start_y = 2;      // محل شروع چاپ در محور Y
                int start_x = 4;     // محل شروع چاپ در محور X

                mvwprintw(messagewin,start_y + 0, start_x, "             ___________");
                mvwprintw(messagewin,start_y + 1, start_x, "            '._==_==_=_.'");
                mvwprintw(messagewin,start_y + 2, start_x, "            .-\\:      /-.");
                mvwprintw(messagewin,start_y + 3, start_x, "           | (|:.     |) |");
                mvwprintw(messagewin,start_y + 4, start_x, "            '-|:.     |-'");
                mvwprintw(messagewin,start_y + 5, start_x, "              \\::.    /");
                mvwprintw(messagewin,start_y + 6, start_x, "               '::. .'");
                mvwprintw(messagewin,start_y + 7, start_x, "                 ) (");
                mvwprintw(messagewin,start_y + 8, start_x, "               _.' '._");
                mvwprintw(messagewin,start_y + 9, start_x, "              `""""""`");
                mvwprintw(messagewin,start_y + 11 , start_x , "Your score : %d" , hero.score);
                wrefresh(messagewin);

                getch();
                break;
            }

            
            mvwaddch(mapWin, hero.y, hero.x, 'H');
            wrefresh(messagewin);
            wrefresh(mapWin);
            
        } while (c != 27); 

        getch();
        delwin(mapWin);
        endwin();
        return 0;
    }
}