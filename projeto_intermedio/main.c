/**
* Intermediate project for the programming subject
* Project done by João Maria Janeiro Gonçalves da Silva
* Integrated master in electrical and computer engineering in IST
* IST id: 190105
*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX(a,b)    (((a)>(b))?(a):(b))
#define M_PI 3.14159265
#define STRING_SIZE 100       // max size for some strings
#define TABLE_SIZE 850        // main game space size
#define LEFT_BAR_SIZE 150     // left white bar size
#define WINDOW_POSX 200       // initial position of the window: x
#define WINDOW_POSY 200       // initial position of the window: y
#define SQUARE_SEPARATOR 8    // square separator in px
#define BOARD_SIZE_PER 0.7f   // board size in % wrt to table size
#define MAX_BOARD_POS 15      // maximum size of the board
#define MAX_COLORS 5
#define MARGIN 5
#define SQR(a)      (a)*(a)

// declaration of the functions related to graphical issues
void InitEverything(int , int , TTF_Font **, SDL_Surface **, SDL_Window ** , SDL_Renderer **, TTF_Font ** );
void InitSDL();
void InitFont();
SDL_Window* CreateWindow(int , int );
SDL_Renderer* CreateRenderer(int , int , SDL_Window *);
int RenderText(int, int, const char *, TTF_Font *, SDL_Color *, SDL_Renderer *);
int RenderLogo(int, int, SDL_Surface *, SDL_Renderer *);
int RenderTable(int, int, int [], TTF_Font *, SDL_Surface **, SDL_Renderer *, int [MAX_BOARD_POS][MAX_BOARD_POS]);
void ProcessMouseEvent(int , int , int [], int , int *, int * );
void RenderPoints(int [][MAX_BOARD_POS], int, int, int [], int, SDL_Renderer *);
void RenderStats( SDL_Renderer *, TTF_Font *, int [], int , int );
void filledCircleRGBA(SDL_Renderer * , int , int , int , int , int , int );
void parameters(int *, int *, int*, int *, int*);
void game_board(int [MAX_BOARD_POS][MAX_BOARD_POS], int , int , int );
void move_reset(int , int , int [MAX_BOARD_POS][MAX_BOARD_POS]);
int evaluate_color(int , int , int [MAX_BOARD_POS][MAX_BOARD_POS], int *, int *);
int evaluate_pos(int , int , int [MAX_BOARD_POS][MAX_BOARD_POS]);
void movedots(int , int , int [MAX_BOARD_POS][MAX_BOARD_POS], int [MAX_BOARD_POS][MAX_BOARD_POS], int , int , int , int );
int square_detect(int , int , int [MAX_BOARD_POS][MAX_BOARD_POS], int [MAX_BOARD_POS][MAX_BOARD_POS], int , int , int );
int square_validate( int [STRING_SIZE][STRING_SIZE], int );
void remove_same_color(int , int , int [MAX_BOARD_POS][MAX_BOARD_POS], int [MAX_BOARD_POS][MAX_BOARD_POS], int , int *);
void remove_inside_square( int [STRING_SIZE][STRING_SIZE], int , int [MAX_BOARD_POS][MAX_BOARD_POS], int , int [MAX_BOARD_POS][MAX_BOARD_POS], int *, int *, int *, int *, int *);
void filecreate(int [], int , char [], int [], int , int);
int victory(int []);
int defeat(int [], int );
void render_squares( SDL_Renderer *, TTF_Font *, int , int );
int shuffle(int [MAX_BOARD_POS][MAX_BOARD_POS], int , int );
void render_shuffle(SDL_Renderer *, TTF_Font *);
void update_points(int [MAX_BOARD_POS], int , int , int , int , int , int );
void do_shuffle_do(int [MAX_BOARD_POS][MAX_BOARD_POS], int , int, int );


// definition of some strings: they cannot be changed when the program is executed !
const char myName[] = "Joao Maria Silva";
const char myNumber[] = "IST190105";
const int colors[3][MAX_COLORS] = {{91, 170, 54, 255, 253},{32, 240, 61, 174, 118},{94, 183, 105, 3, 144}};

/**
 * main function: entry point of the program
 * only to invoke other functions !
 */
int main( void )
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    TTF_Font *serif = NULL;
    TTF_Font *serif_big = NULL;
    SDL_Surface *imgs[2];
    SDL_Event event;
    int delay = 300;
    int quit = 0;
    int width = (TABLE_SIZE + LEFT_BAR_SIZE);
    int height = TABLE_SIZE;
    int square_size_px = 0, board_size_px[2] = {0};
    int board_pos_x = 0, board_pos_y = 0;
    int board[MAX_BOARD_POS][MAX_BOARD_POS] = {{0}};
    int pt_x = 0, pt_y = 0;

    int int_colors, jogadas = 0;
    int i = 0;
    char username[STRING_SIZE];
    int move[MAX_BOARD_POS][MAX_BOARD_POS] = {{0}};
    int play = 0;
    int j = 0;
    int valid, count, valid_pos = 0;
    int square, lastXpos, lastYpos, mem_pos = 0;

    int mem[STRING_SIZE][STRING_SIZE] = {{0}};
    int validate = 0;
    int color = 0;
    int derrotas, vitorias = 0;
    int count1 = 0;

    int pontos[MAX_BOARD_POS] = {0};
    int pontos1[MAX_BOARD_POS] = {0};
    int pontos_undo[MAX_BOARD_POS] = {0};

    int board_pos_x_1, board_pos_y_1, int_colors_1, jogadas1 = 0;
    int jogos[STRING_SIZE] = {2};
    int jogo = 0;
    int vitoria, derrota = 0;
    int plays[STRING_SIZE] = {0};

    int do_shuffle = 0;
    int game_on = 1;

    int count_0 = 0;
    int count_1 = 0;
    int count_2 = 0;
    int count_3 = 0;
    int count_4 = 0;
    int board_undo[MAX_BOARD_POS][MAX_BOARD_POS] = {{0}};
    int jogadas_undo = 0;


    board_pos_x = 5;
    board_pos_y = 7;

    srand(time(NULL));


   do{
    printf( "Whats your name? " );
    fgets( username, sizeof( username ), stdin );
    if(strlen(username) > 8 || strlen(username)  < 1){
                printf("\nO username tem de ter menos de 8 caracteres\n");
            }
   }while( strlen(username) < 1 || strlen(username) > 8);


    //Parameters to intialize the game
    parameters(&board_pos_y, &board_pos_x, &int_colors, pontos, &jogadas);

    board_pos_y_1 = board_pos_y;
    board_pos_x_1 = board_pos_x;
    int_colors_1 = int_colors;
    jogadas1 = jogadas;
    for( i = 0; i < MAX_BOARD_POS; i++){
        pontos1[i] = pontos[i];
    }
    //Randomly generates colors
    game_board(board, board_pos_x, board_pos_y, int_colors);

    // initialize graphics
    InitEverything(width, height, &serif, imgs, &window, &renderer, &serif_big);

    //Sets the move array to all 7 before starting the game
    move_reset(board_pos_x, board_pos_y, move);



    while( quit == 0 )
    {
        // while there's events to handle
        while( SDL_PollEvent( &event ) )
        {
            if( event.type == SDL_QUIT )
            {
                if(game_on == 1){
                    jogos[jogo] = 0;
                    plays[jogo] = jogadas1 - jogadas;
                    jogo ++;
                    derrotas++;
                }
                quit = 1; // Closes the game
                filecreate(jogos, jogo, username, plays, vitorias, derrotas);
                jogo = 0;
            }
            else if ( event.type == SDL_KEYDOWN )
            {
                switch ( event.key.keysym.sym )
                {
                    case SDLK_n:
                        if(game_on == 1){ // If a game is active when you press 'n'
                            jogos[jogo] = 0; // Sets a loss
                            plays[jogo] = jogadas1 - jogadas;
                            jogo ++;
                            derrotas++;
                        }
                        game_board(board, board_pos_x, board_pos_y, int_colors); //Generates a new board
                        move_reset(board_pos_x, board_pos_y, move); // Resets the move array
                        //Restores all the parameters
                        board_pos_y = board_pos_y_1;
                        board_pos_x = board_pos_x_1;
                        int_colors = int_colors_1;
                        jogadas = jogadas1;
                        for( i = 0; i < MAX_BOARD_POS; i++){
                            pontos[i] = pontos1[i];
                        }
                        game_on = 1; // Starts a game
                        vitoria = 0;
                        derrota = 0;
                       break;
                    case SDLK_q:
                        if(game_on == 1){
                            jogos[jogo] = 0;
                            plays[jogo] = jogadas1 - jogadas;
                            jogo ++;
                            derrotas++;
                        }
                        quit = 1; // Closes the game
                        filecreate(jogos, jogo, username, plays, vitorias, derrotas);
                        jogo = 0;
                        break;
                    case SDLK_u:
                        for(i= 0; i < board_pos_x; i++){
                            for(j= 0; j < board_pos_y; j++){
                                board[i][j] = board_undo[i][j]; // Sets the board to the undo board saved in the last play
                            }
                        }
                        for( i = 0; i < MAX_BOARD_POS; i++){
                            pontos[i] = pontos_undo[i]; // Sets the points to the points to the last play
                        }
                        jogadas = jogadas_undo; // Sets the moves to the moves to the last play
                        break;
                    default:
                        break;
                }

            }
            else if ( event.type == SDL_MOUSEBUTTONDOWN )
            {
                ProcessMouseEvent(event.button.x, event.button.y, board_size_px, square_size_px, &pt_x, &pt_y);
                printf("Button down: %d %d\n", pt_x, pt_y);
                play = 1;
                lastXpos = 30;
                lastYpos = 30;
                for(i= 0; i < board_pos_x; i++){
                    for(j= 0; j < board_pos_y; j++){
                        board_undo[i][j] = board[i][j]; // Saves the current board in the undo copy board so we can undo the next play
                    }
                }
                for( i = 0; i < MAX_BOARD_POS; i++){
                    pontos_undo[i] = pontos[i]; // Saves the current player points
                }

                jogadas_undo = jogadas;
            }
            else if ( event.type == SDL_MOUSEBUTTONUP )
            {
                ProcessMouseEvent(event.button.x, event.button.y, board_size_px, square_size_px, &pt_x, &pt_y);
                printf("Button up: %d %d\n", pt_x, pt_y);
                play = 2; // Ends the current play
                valid = evaluate_color(board_pos_x, board_pos_y, move, &count, &color); // Checks if all the selected dots had the same color and returns the color of the play and how many dots were selected
                printf("Rebentou %d bolas\n", count);
                valid_pos = evaluate_pos(board_pos_x, board_pos_y, move); // Checks if the selected dots were not a diagonal
                if(valid == 0 && count >=2 && valid_pos == 0){
                    jogadas --;
                    if ( square == 0 && validate != 1){
                        remove_inside_square(mem, mem_pos, board, color, move, &count_0, &count_1, &count_2, &count_3, &count_4); // Removes all the dots inside the squares
                        remove_same_color(board_pos_x, board_pos_y, board, move, int_colors, &count1); // Removes all the dots with the same color as the square
                        if(pontos[color] - count1 < 0){
                            pontos[color] = 0; // If the points are negative set them to zero
                        }else{
                            pontos[color] = pontos[color] - count1; // If they are not negative set them to current points
                        }
                        update_points(pontos, color, count_0, count_1, count_2, count_3, count_4); // Updates the player points
                    }
                    else{
                        if(pontos[color] - count < 0){
                            pontos[color] = 0;
                        }else{
                            pontos[color] = pontos[color] - count;
                        }
                    }
                    movedots(board_pos_x, board_pos_y, board, move, int_colors, color, square, validate); // After the play was validated moves all the selcted dots
                }
                vitoria = victory(pontos);
                derrota = defeat(pontos, jogadas);
                if(vitoria == 1){
                    jogos[jogo] = 1; // Sets the current game to 1 in the "jogo" array which means the game was won
                    plays[jogo] = jogadas1 - jogadas; //Stores the amount of moves the player did in each game
                    jogo ++;
                    vitorias++;
                    game_on = 0; // This means that when the win text is beeing displayed the game in not being played until the user presses 'n'
                }
                if(derrota == 1){
                    jogos[jogo] = 0; // Sets the current game to 0 in the "jogo" array which means the game was lost
                    plays[jogo] = jogadas1 - jogadas; //Stores the amount of moves the player did in each game
                    jogo ++;
                    derrotas++;
                    game_on = 0; // This means that when the lost text is beeing displayed the game in not being played until the user presses 'n'
                }
                move_reset(board_pos_x, board_pos_y, move);
                mem_pos = 0;
                validate = 0;

            }
            else if ( event.type == SDL_MOUSEMOTION )
            {
                ProcessMouseEvent(event.button.x, event.button.y, board_size_px, square_size_px, &pt_x, &pt_y);
                if( play == 1 ){
                    if( lastXpos != pt_x || lastYpos != pt_y){ //So it only saves the current position one time
                        if(pt_x != -1){
                            square = square_detect(board_pos_x, board_pos_y, board, move, int_colors, pt_x, pt_y);
                            move[pt_x][pt_y] = board[pt_x][pt_y]; //Array that stores the move the player did, stores the color of each dot the player selected
                            SDL_RenderDrawLine(renderer, event.button.x, event.button.y, event.button.x+5, event.button.y +2);
                            SDL_RenderPresent(renderer);
                            lastXpos = pt_x; //Sets the last position to the current one so we can check if the next position is equal to the current one in the next cicle
                            lastYpos = pt_y;
                            mem[mem_pos][0] = pt_x; //Array that stores all the postions in a play
                            mem[mem_pos][1] = pt_y;
                            validate = square_validate(mem, mem_pos);// Returns 0 if it's a square
                            mem_pos++;
                        }
                    }

                }
            }


        }

        do_shuffle = shuffle(board, board_pos_x, board_pos_y); //Returns 1 if a shuffle is verified
        // render game table
        square_size_px = RenderTable( board_pos_x, board_pos_y, board_size_px, serif, imgs, renderer, move);
        // render board
        RenderPoints(board, board_pos_x, board_pos_y, board_size_px, square_size_px, renderer);
        //Render stats
        RenderStats( renderer, serif, pontos, int_colors, jogadas);
        //Render game result
        render_squares(renderer, serif_big, vitoria, derrota);
        //If shuffle is equal to one, render the shuffle text and shuffles the board
        if(do_shuffle == 1){
            render_shuffle(renderer, serif_big);
            SDL_Delay(400);
            do_shuffle_do(board, board_pos_x, board_pos_y, int_colors);
        }
        // render in the screen all changes above
        SDL_RenderPresent(renderer);
        // add a delay
        SDL_Delay( delay );

    }



    // free memory allocated for images and textures and closes everything including fonts
    TTF_CloseFont(serif);
    SDL_FreeSurface(imgs[0]);
    SDL_FreeSurface(imgs[1]);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}

/**
 * parameters: gets the user parameters to start the game
 */
void parameters(int *rows1, int *columns1, int *int_colors1, int pontos[MAX_BOARD_POS], int *jogadas1){

    int rows, columns, int_colors, jogadas = 0;
    int i = 0;
    char temp[STRING_SIZE] = "\0";

    do{
        printf("Qual é o tamanho do tabuleiro que quer(rows * columns): ");
        fgets(temp, STRING_SIZE, stdin);
        sscanf(temp, "%d %d", &rows, &columns);
            if(rows > 15 || rows < 5 || columns > 15 || columns < 5){
                printf("\nOs valores do tabuleiro têm de estar compreeendidos entre 5 e 15\n");
            }
    }while(rows > 15 || rows < 5 || columns > 15 || columns < 5);


    do{
        printf("\nQuantas cores quer no jogo: ");
        fgets(temp, STRING_SIZE, stdin);
        sscanf(temp, " %d", &int_colors);
            if(int_colors > 5 || int_colors < 1){
                printf("\nNão podem existir mais que 5 cores no jogo");
            }
    }while(int_colors > 5 || int_colors < 1);

    for( i = 0; i < int_colors; i++){
        printf("\nNúmero de pontos a alcançar na cor %d: ", i+1);
        fgets(temp, STRING_SIZE, stdin);
        sscanf(temp, "%d", &pontos[i]);
            while( pontos[i] > 99 || pontos[i] < 1){
                printf("Esse valor é superior a 99");
                printf("\nNúmero de pontos a alcançar na cor %d: ", i+1);
                fgets(temp, STRING_SIZE, stdin);
                sscanf(temp, "%d", &pontos[i]);
            }
    }


    do{
        printf("\nNúmero máximo de jogadas: ");
        fgets(temp, STRING_SIZE, stdin);
        sscanf(temp, "%d", &jogadas);
            if(jogadas > 99 || jogadas < 1){
                printf("\nNão pode ser mais que 99 jogadas");
            }
    }while(jogadas > 99 || jogadas < 1);


    *rows1 = rows;
    *columns1 = columns;
    *int_colors1 = int_colors;
    *jogadas1 = jogadas;
}

/**
 * game_board: randomly generates the game board for the game
 * \param _lines amount of lines the user selected for the board
 * \param _col amount of columns the user selected for the board
 * \param _colors the amount of the colors the user selected for the game
 */
void game_board(int board[MAX_BOARD_POS][MAX_BOARD_POS], int _lines, int _col, int _colors){
    int i,j = 0;

    for(i = 0; i < _lines; i++){
        for(j = 0; j < _col; j++){
            board[i][j] = ((int)rand()%(_colors)); //Generates random colors for all the board positions
        }
    }
}

/**
 * move_reset: sets the two dimensional array move to the initial state, all postions equal to 7(because there can only be 5 colors in a game and 7 is a lucky number)
 * \param board_pos_x amount of lines the user selected for the board
 * \param board_pos_y amount of columns the user selected for the board
 * \param move the array we want to reset to 7
 */
void move_reset(int board_pos_x, int board_pos_y, int move[MAX_BOARD_POS][MAX_BOARD_POS]){
    int i,j = 0;
    for(i = 0; i < board_pos_x; i++){
    for(j = 0; j < board_pos_y; j++){
        move[i][j] = 7; //REsets the whole array to the vaule of 7
        }
            }
}

/**
 * evaluate_color: checks if all the dots selected have the same color
 * \param board_pos_x amount of lines the user selected for the board
 * \param board_pos_y amount of columns the user selected for the board
 * \param move the array that stores all the dots the player selected and changes the postion values equal to the color of the selected dot from the board
 * \param *count returns how many dots were selcted in a play
 * \param *color returns the color of the selected dots
 */
int evaluate_color(int board_pos_x, int board_pos_y, int move[MAX_BOARD_POS][MAX_BOARD_POS], int *count, int *color){
    int aux = 9;
    int i, j, count1 = 0;
    for(i = 0; i < board_pos_x; i++){
        for(j = 0; j < board_pos_y; j++){
            if(move[i][j] != 7){
                if( aux == 9 ){
                    aux = move[i][j]; //Gets the value of the color
                }
                count1 ++;
                if( move[i][j] != aux ){
                    return -1;
                }
            }

        }
    }
            *count = count1;
            *color = aux;
            return 0;
}

/**
 * evaluate_pos: checks if the selected dots were not connected in a diagonal which is an invalid play, if it was a diagonal return 1
 * \param board_pos_x amount of lines the user selected for the board
 * \param board_pos_y amount of columns the user selected for the board
 * \param move the array that stores all the dots the player selected and changes the postion values equal to the color of the selected dot from the board
 */
int evaluate_pos(int board_pos_x, int board_pos_y, int move[MAX_BOARD_POS][MAX_BOARD_POS]){
    int i, j = 0;
    for(i = 0; i < board_pos_x; i++){
        for(j = 0; j < board_pos_y; j++){
            if(move[i][j] != 7){
                if ( (move[i][j] == move[i+1][j+1] && move[i][j] != move[i+1][j] && move[i][j] != move[i-1][j] && move[i][j] != move[i][j+1] && move[i][j] != move[i][j-1]) || (move[i][j] == move[i+1][j-1] && move[i][j] != move[i+1][j] && move[i][j] != move[i-1][j] && move[i][j] != move[i][j+1] && move[i][j] != move[i][j-1]) || (move[i][j] == move[i-1][j+1] && move[i][j] != move[i+1][j] && move[i][j] != move[i-1][j] && move[i][j] != move[i][j+1] && move[i][j] != move[i][j-1]) || (move[i][j] == move[i-1][j-1] && move[i][j] != move[i+1][j] && move[i][j] != move[i-1][j] && move[i][j] != move[i][j+1] && move[i][j] != move[i][j-1])){
                    return -1;
                }
            }
        }
    }

    return 0;
}

/**
 * movedots: after a play is validated moves the selcted dots down
 * \param board_pos_x amount of lines the user selected for the board
 * \param board_pos_y amount of columns the user selected for the board
 * \param move the array that stores all the dots the player selected and changes the postion values equal to the color of the selected dot from the board
 * \param board the game board that has all the color values in it
 * \param _colors amount of colors in the game
 * \param color the color selected in the play
 * \param square is equal to 0 if a square is selcted
 * \param validate is equal to 0 if a selected square is valid
 */
void movedots(int board_pos_x, int board_pos_y, int board[MAX_BOARD_POS][MAX_BOARD_POS], int move[MAX_BOARD_POS][MAX_BOARD_POS], int _colors, int color, int square, int validate){
    int i, j,d = 0;
    int aux = 9;
    int aux_1 = 0;


    for(i = 0; i < board_pos_x; i++){
        for(j = 0; j < board_pos_y; j++){
            if(move[i][j] != 7){
                if( aux == 9 ){
                    aux = move[i][j];
                }
            }
        }
    }

    if(square == 0 && validate == 0){
        for(i = 0; i < board_pos_x; i++){
            for(j = 0; j < board_pos_y; j++){
                if( move[i][j] == aux ){ //If they have the square color
                    for(d = 0; d < j; d++){ //
                        board[i][j-d] = board[i][j-d-1]; //Push them down
                    }
                    while(1){
                        aux_1 = (int) (rand()% (_colors)); //Generates a random number
                        if( aux_1 != aux ){ //Check if the random number has the same color as the square, if not
                            board[i][0] = aux_1; //Set the new dot to that random color
                            break;
                        }
                    }
                }
            }
        }
    }

    if(square == 1){
        for(i = 0; i < board_pos_x; i++){
            for(j = 0; j < board_pos_y; j++){
                if( move[i][j] == aux){
                    for(d = 0; d < j; d++){
                        board[i][j-d] = board[i][j-d-1];
                    }
                    board[i][0] = (int) (rand()% (_colors));
                }
            }
        }
    }

}

/**
 * square_detect: checks if the postion the user selcted had already been selected in that play, meaning he closed a figure
 * \param board_pos_x amount of lines the user selected for the board
 * \param board_pos_y amount of columns the user selected for the board
 * \param board the game board that has all the color values in it
 * \param _colors amount of colors in the game
 * \param move the array that stores all the dots the player selected and changes the postion values equal to the color of the selected dot from the board
 * \param pt_x the current x value for the postion the mouse is in
 * \param pt_y the current y value for the postion the mouse is in
 */
int square_detect(int board_pos_x, int board_pos_y, int board[MAX_BOARD_POS][MAX_BOARD_POS], int move[MAX_BOARD_POS][MAX_BOARD_POS], int _colors, int pt_x, int pt_y){
    if( move[pt_x][pt_y] != 7){
            return 0;
    }

return 1;
}

/**
 * square_validate: checks if the user actaully did a square and didn't just return to the same position in a straight line
 * \param mem array that stores all the x and y postions the user passed through during a play
 * \param mem_pos the current/last position in the array during a play
 */
int square_validate( int mem[STRING_SIZE][STRING_SIZE], int mem_pos ){

    if( mem[mem_pos][0] == mem[mem_pos-2][0] && mem[mem_pos][1] == mem[mem_pos-2][1] ){
        return 1;
    }
return 0;
}

/**
 * remove_same_color: changes the value of the move array(so the function movedots can remove them) to the value of the color if the color of that position is equal to the square color
 * \param board_pos_x amount of lines the user selected for the board
 * \param board_pos_y amount of columns the user selected for the board
 * \param board the game board that has all the color values in it
 * \param _colors amount of colors in the game
 * \param move the array that stores all the dots the player selected and changes the postion values equal to the color of the selected dot from the board
 * \param *count returns the amount of dots with the same color as the square
 */
void remove_same_color(int board_pos_x, int board_pos_y, int board[MAX_BOARD_POS][MAX_BOARD_POS], int move[MAX_BOARD_POS][MAX_BOARD_POS], int _colors, int *count){
    int i, j = 0;
    int aux = 9;
    int count1 = 0;


    for(i = 0; i < board_pos_x; i++){
        for(j = 0; j < board_pos_y; j++){
            if(move[i][j] != 7){
                if( aux == 9 ){
                    aux = move[i][j];
                }
            }
        }
    }

    for (i = 0; i < board_pos_x; i++) {
        for (j = 0; j < board_pos_y; j++) {
            if (board[i][j] == aux) {
                move[i][j] = aux;
                count1++;
            }
        }
    }

    *count = count1;

}

/**
 * remove_inside_square: changes the value of the move array(so the function movedots can remove them) to the value of the square color if any dot is inside the square
 * \param board the game board that has all the color values in it
 * \param move the array that stores all the dots the player selected and changes the postion values equal to the color of the selected dot from the board
 * \param mem array that stores all the x and y postions the user passed through during a play
 * \param mem_pos the current/last position in the array during a play
 * \param color the color selected in the play
 * \param *count[0-4] counts the amount of dots of each color inside the square
 */
void remove_inside_square( int mem[STRING_SIZE][STRING_SIZE], int mem_pos, int board[MAX_BOARD_POS][MAX_BOARD_POS], int color, int move[MAX_BOARD_POS][MAX_BOARD_POS], int *count_0, int *count_1, int *count_2, int *count_3, int *count_4){
    int i, j, maximum_x, maximum_y = 0;
    int minimum_x = 40;
    int minimum_y = 40;

    int count_0_1 = 0;
    int count_1_1 = 0;
    int count_2_1 = 0;
    int count_3_1 = 0;
    int count_4_1 = 0;

    maximum_x = 0;
    maximum_y = 0;
    for(i = 0; i < mem_pos; i++){
        if( mem[i][0] > maximum_x){
            maximum_x = mem[i][0];
        }
    }

    for(i = 0; i < mem_pos; i++){
        if( mem[i][1] > maximum_y){
            maximum_y = mem[i][1];
        }
    }

    for(i = 0; i < mem_pos; i++){
        if( mem[i][0] < minimum_x){
            minimum_x = mem[i][0];
        }
    }

    for(i = 0; i < mem_pos; i++){
        if( mem[i][1] < minimum_y){
            minimum_y = mem[i][1];
        }
    }



    for(i = minimum_x; i <= maximum_x; i++){
        for(j = minimum_y; j <= maximum_y; j++){
            if(board[i][j] == 0){
                count_0_1++;
            }
            if(board[i][j] == 1){
                count_1_1++;
            }
            if(board[i][j] == 2){
                count_2_1++;
            }
            if(board[i][j] == 3){
                count_3_1++;
            }
            if(board[i][j] == 4){
                count_4_1++;
            }
            move[i][j] = color;
        }
    }
    *count_0 = count_0_1;
    *count_1 = count_1_1;
    *count_2 = count_2_1;
    *count_3 = count_3_1;
    *count_4 = count_4_1;
}

/**
 * filecreate: generates a stats.txt file with all the stats from the game
 * \param jogos an array that has 0 if a game is lost and 1 if a game is won
 * \param jogo amount of games played
 * \param username is the player selected username
 * \param plays an array that stores the amount of moves for each game
 * \param vitorias has the amount of wins the player had in the session
 * \param derrotas has the amount of losses the player had in the session
 */
void filecreate(int jogos[STRING_SIZE], int jogo, char username[STRING_SIZE], int plays[STRING_SIZE], int vitorias, int derrotas){
    int i = 0;
    FILE *f = fopen("stats.txt", "w");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    fprintf(f, "Username: %s\n", username);
    fprintf(f, "Games: %d\n", jogo);
    fprintf(f, "Losses: %d\n", derrotas);
    fprintf(f, "Victories: %d\n", vitorias);

    for(i = 0; i < jogo; i++){
        if(jogos[i] == 0){
            fprintf(f, "Game %d: Defeat with %d moves\n", i+1, plays[i]);
        }
        if(jogos[i] == 1){
            fprintf(f, "Game %d: Victory with %d moves\n", i+1, plays[i]);
        }
    }
    fclose(f);
}

/**
 * victory: checks if all the user selected objetives were met and returns 1 if so
 * \param pontos an array that keeps the amount of desired points to achieve for each color in the game(defined by the user in the parameters)
 */
int victory(int pontos[MAX_BOARD_POS]){

    int i = 0;
    int count = 0;
    for(i = 0; i < 5; i++){
        if(pontos[i] <= 0){
            count++;
        }
    }


    if(count == 5){ //Checks if all the objectives were met
        printf("\nVitória!\n");
        return 1;
    }else{
        return 0;
    }

}

/**
 * defeat: checks there are no moves left and if the objectives were not met, if so returns 1
 * \param pontos an array that keeps the amount of desired points to achieve for each color in the game(defined by the user in the parameters)
 * \param jogadas has the amount of moves the user chose in the parameters in order to achieve his objectives
 */
int defeat(int pontos[MAX_BOARD_POS], int jogadas){
    int i = 0;
    int count = 0;
    for(i = 0; i < 5; i++){
        if(pontos[i] <= 0){
            count++;
        }
    }

    if(jogadas == 0 && count !=5){ //Checks if there are no moves left and the objectives were not accomplished
        printf("\nDefeat\n");
        return 1;
    }else{
        return 0;
    }
}

/**
 * render_squares: renders a square in the middle of the screen with a defeat or victory message
 * \param _renderer renderer to handle all rendering in a window
 * \param _font font to display the text
 * \param vitoria is 1 if the player won a game
 * \param derrota is 1 if a game was lost
 */
void render_squares( SDL_Renderer *_renderer, TTF_Font *_font, int vitoria, int derrota){
    SDL_Color blue = {30,144,255};
    SDL_SetRenderDrawColor( _renderer, 250, 250, 210, 0.5);


    if(vitoria == 1){
    //Renders the square to display the text
        SDL_Rect victoria = {80, 200, 700, 500};
        SDL_RenderFillRect( _renderer, &victoria);
    //Render victory text
        RenderText(340, 300, "VICTORY", _font, &blue, _renderer);
        RenderText(180, 350, "Press n to play another game", _font, &blue, _renderer);
    }

    if(derrota == 1){
    //Renders the square to display the text
        SDL_Rect victoria = {80, 200, 700, 500};
        SDL_RenderFillRect( _renderer, &victoria);
    //Render Defeat text
        RenderText(340, 300, "DEFEAT", _font, &blue, _renderer);
        RenderText(180, 350, "Press n to play another game", _font, &blue, _renderer);
    }

}

/**
 * shuffle: checks if there are no possible moves in the board, if there are no possible moves left return 1
 * \param board_pos_x amount of lines the user selected for the board
 * \param board_pos_y amount of columns the user selected for the board
 * \param board the game board that has all the color values in it
 */
int shuffle(int board[MAX_BOARD_POS][MAX_BOARD_POS], int board_pos_x, int board_pos_y){
    int i, j = 0;

    for(i = 0; i < board_pos_x; i++){
        for(j = 0; j < board_pos_y; j++){
            if( i!= board_pos_x-1 && j != board_pos_y-1){
                if(board[i][j] == board[i][j+1] || board[i][j] == board[i+1][j]){
                    return 0;
                }
            }
            else if( i != board_pos_x-1 && j == board_pos_y-1){
                if(board[i][j] == board[i+1][j]){
                    return 0;
                }
            }
            else if(i == board_pos_x-1 && j != board_pos_y-1){
                if(board[i][j] == board[i][j+1]){
                    return 0;
                }
            }
        }
    }
    return 1;
}

/**
 * render_shuffle: renders a square in the middle of the screen with a shuffle message
 * \param _renderer renderer to handle all rendering in a window
 * \param _font font to display the text
 */
void render_shuffle(SDL_Renderer *_renderer, TTF_Font *_font){
    SDL_Color blue = {30,144,255};
    SDL_SetRenderDrawColor( _renderer, 250, 250, 210, 0.5);

    //Renders the square to display the text
        SDL_Rect victoria = {80, 200, 700, 500};
        SDL_RenderFillRect( _renderer, &victoria);
    //Render Defeat text
        RenderText(340, 300, "SHUFFLE", _font, &blue, _renderer);

}

/**
* update_points: updates the objectives of each color after every play
* \param pontos an array that keeps the amount of desired points to achieve for each color in the game(defined by the user in the parameters)
* \param color the color selected in the play
* \param *count[0-4] amount of selected dots in eah play for the color of the play
*/
void update_points(int pontos[MAX_BOARD_POS], int color, int count_0, int count_1, int count_2, int count_3, int count_4){
    if(color != 0){
        if(pontos[0] - count_0 < 0){
            pontos[0] = 0;
        }else{
            pontos[0] = pontos[0] - count_0;
        }
    }
    if(color != 1){
        if(pontos[1] - count_1 < 0){
            pontos[1] = 0;
        }else{
            pontos[1] = pontos[1] - count_1;
        }
    }
    if(color != 2){
        if(pontos[2] - count_2 < 0){
            pontos[2] = 0;
        }else{
            pontos[2] = pontos[2] - count_2;
        }
    }
    if(color != 3){
        if(pontos[3] - count_3 < 0){
            pontos[3] = 0;
        }else{
            pontos[3] = pontos[3] - count_3;
        }
    }
    if(color != 4){
        if(pontos[4] - count_4 < 0){
            pontos[4] = 0;
        }else{
            pontos[4] = pontos[4] - count_4;
        }
    }
}

/**
 * do_shuffle_do: mixes the postions in the board array randomly
 * \param _lines amount of lines the user selected for the board
 * \param _col amount of columns the user selected for the board
 * \param board the game board that has all the color values in it
 * \param _colors amount of colors in the game
 */
void do_shuffle_do(int board[MAX_BOARD_POS][MAX_BOARD_POS], int _lines, int _col, int _colors){

    int i,j, aux = 0;

    int color0 = 0;
    int color1 = 0;
    int color2 = 0;
    int color3 = 0;
    int color4 = 0;

    for(i = 0; i < _lines; i++){
        for(j = 0; j < _col; j++){
            if(board[i][j] == 0){
                color0++;
            }
            if(board[i][j] == 1){
                color1++;
            }
            if(board[i][j] == 2){
                color2++;
            }
            if(board[i][j] == 3){
                color3++;
            }
            if(board[i][j] == 4){
                color4++;
            }
        }
    }

    for(i = 0; i < _lines; i++){
        for(j = 0; j < _col; j++){
            while(1){
                aux = ((int)rand()%_colors);
                if(color0 != 0 && aux == 0){
                    board[i][j] = 0;
                    color0--;
                    break;
                }
                else if(color1 != 0 && aux == 1){
                    board[i][j] = 1;
                    color1--;
                    break;
                }
                else if(color2 != 0 && aux == 2){
                    board[i][j] = 2;
                    color2--;
                    break;
                }
                else if(color3 != 0 && aux == 3){
                    board[i][j] = 3;
                    color3--;
                    break;
                }
                else if(color4 != 0 && aux == 4){
                    board[i][j] = 4;
                    color4--;
                    break;
                }
            }
        }

    }
}

/**
 * ProcessMouseEvent: gets the square pos based on the click positions !
 * \param _mouse_pos_x position of the click on pixel coordinates
 * \param _mouse_pos_y position of the click on pixel coordinates
 * \param _board_size_px size of the board !
 * \param _square_size_px size of each square
 * \param _pt_x square nr
 * \param _pt_y square nr
 */
void ProcessMouseEvent(int _mouse_pos_x, int _mouse_pos_y, int _board_size_px[], int _square_size_px,
        int *_pt_x, int *_pt_y )
{
    int sqr_x = 0, sqr_y = 0, dist = 0;
    int circleX = 0, circleY = 0, circleR = 0;
    // corner of the board
    int x_corner = (TABLE_SIZE - _board_size_px[0]) >> 1;
    int y_corner = (TABLE_SIZE - _board_size_px[1] - 15);

    // verify if valid cordinates
    if (_mouse_pos_x < x_corner || _mouse_pos_y < y_corner || _mouse_pos_x > (x_corner + _board_size_px[0])
        || _mouse_pos_y > (y_corner + _board_size_px[1]) )
    {
        *_pt_x = -1;
        *_pt_y = -1;
        return;
    }

    // computes the square where the mouse position is
    sqr_x = (_mouse_pos_x - x_corner) / (_square_size_px + SQUARE_SEPARATOR);
    sqr_y = (_mouse_pos_y - y_corner) / (_square_size_px + SQUARE_SEPARATOR);

    //compute the circle parameters
    circleX = x_corner + (sqr_x+1)*SQUARE_SEPARATOR + sqr_x*(_square_size_px)+(_square_size_px>>1);
    circleY = y_corner + (sqr_y+1)*SQUARE_SEPARATOR + sqr_y*(_square_size_px)+(_square_size_px>>1);
    circleR = (int)(_square_size_px*0.4f);

    dist = (int)floor( sqrt(SQR(_mouse_pos_x - circleX) + SQR(_mouse_pos_y - circleY)));

    if (dist < circleR)
    {
      *_pt_x = sqr_x;
      *_pt_y = sqr_y;
    }
    else
    {
      *_pt_x = -1;
      *_pt_y = -1;
    }
}


/**
 * RenderPoints: renders the board
 * \param _board 2D array with integers representing board colors
 * \param _board_pos_x number of positions in the board (x axis)
 * \param _board_pos_y number of positions in the board (y axis)
 * \param _square_size_px size of each square
 * \param _board_size_px size of the board
 * \param _renderer renderer to handle all rendering in a window
 */
void RenderPoints(int _board[][MAX_BOARD_POS], int _board_pos_x, int _board_pos_y,
        int _board_size_px[], int _square_size_px, SDL_Renderer *_renderer )
{
    int clr, x_corner, y_corner, circleX, circleY, circleR;

    // corner of the board
    x_corner = (TABLE_SIZE - _board_size_px[0]) >> 1;
    y_corner = (TABLE_SIZE - _board_size_px[1] - 15);

    // renders the squares where the dots will appear
    for ( int i = 0; i < _board_pos_x; i++ )
    {
        for ( int j = 0; j < _board_pos_y; j++ )
        {
                // define the size and copy the image to display
                circleX = x_corner + (i+1)*SQUARE_SEPARATOR + i*(_square_size_px)+(_square_size_px>>1);
                circleY = y_corner + (j+1)*SQUARE_SEPARATOR + j*(_square_size_px)+(_square_size_px>>1);
                circleR = (int)(_square_size_px*0.4f);
                // draw a circle
                clr = _board[i][j];
                filledCircleRGBA(_renderer, circleX, circleY, circleR, colors[0][clr], colors[1][clr], colors[2][clr]);
        }
    }
}

/**
 * filledCircleRGBA: renders a filled circle
 * \param _circleX x pos
 * \param _circleY y pos
 * \param _circleR radius
 * \param _r red
 * \param _g gree
 * \param _b blue
 */
void filledCircleRGBA(SDL_Renderer * _renderer, int _circleX, int _circleY, int _circleR, int _r, int _g, int _b)
{
    int off_x = 0;
    int off_y = 0;
    float degree = 0.0;
    float step = M_PI / (_circleR*8);

    SDL_SetRenderDrawColor(_renderer, _r, _g, _b, 255);

    while (_circleR > 0)
    {
        for (degree = 0.0; degree < M_PI/2; degree+=step)
        {
            off_x = (int)(_circleR * cos(degree));
            off_y = (int)(_circleR * sin(degree));
            SDL_RenderDrawPoint(_renderer, _circleX+off_x, _circleY+off_y);
            SDL_RenderDrawPoint(_renderer, _circleX-off_y, _circleY+off_x);
            SDL_RenderDrawPoint(_renderer, _circleX-off_x, _circleY-off_y);
            SDL_RenderDrawPoint(_renderer, _circleX+off_y, _circleY-off_x);
        }
        _circleR--;
    }
}

/*
 * Shows some information about the game:
 * - Goals of the game
 * - Number of moves
 * \param _renderer renderer to handle all rendering in a window
 * \param _font font to display the scores
 * \param _goals goals of the game
 * \param _ncolors number of colors
 * \param _moves number of moves remaining
 */
void RenderStats( SDL_Renderer *_renderer, TTF_Font *_font, int _goals[], int _ncolors, int _moves)
{
    /* To Be Done */
    SDL_Color black = { 0,0,0};
    int rect_x_pos = 170;
    SDL_SetRenderDrawColor(_renderer, 205, 193, 101, 255 );
    char numberPlays[5];
    sprintf(numberPlays, "%d", _moves);

    //Dar print às jogadas restantes
    SDL_Rect jogadas = {50,50,80,50};
    SDL_RenderFillRect(_renderer, &jogadas);
    RenderText(67, 62, numberPlays, _font, &black, _renderer);

    //Dar print às cores
    for(int i = 0; i < _ncolors; i++){
        SDL_SetRenderDrawColor(_renderer, 205, 194, 180, 255);
        SDL_Rect rect = {rect_x_pos, 50, 100, 50};
        SDL_RenderFillRect(_renderer, &rect);
        char colorPoints[5];
        sprintf(colorPoints, "%d", _goals[i]);
        filledCircleRGBA(_renderer, rect_x_pos + 25, 75, 15, colors[0][i], colors[1][i], colors[2][i]);
        RenderText(rect_x_pos + 50, 65, colorPoints, _font, &black, _renderer);
        rect_x_pos = rect_x_pos + 120;
    }
}

/*
 * RenderTable: Draws the table where the game will be played, namely:
 * -  some texture for the background
 * -  the right part with the IST logo and the student name and number
 * -  the grid for game board with squares and seperator lines
 * \param _board_pos_x number of positions in the board (x axis)
 * \param _board_pos_y number of positions in the board (y axis)
 * \param _board_size_px size of the board
 * \param _font font used to render the text
 * \param _img surfaces with the table background and IST logo (already loaded)
 * \param _renderer renderer to handle all rendering in a window
 */
int RenderTable( int _board_pos_x, int _board_pos_y, int _board_size_px[],
        TTF_Font *_font, SDL_Surface *_img[], SDL_Renderer* _renderer, int move[MAX_BOARD_POS][MAX_BOARD_POS] )
{
    SDL_Color black = { 0, 0, 0 }; // black
    SDL_Color light = { 205, 193, 181 };
    SDL_Color dark = { 120, 110, 102 };
    SDL_Texture *table_texture;
    SDL_Rect tableSrc, tableDest, board, board_square;
    int height, board_size, square_size_px, max_pos;

    // set color of renderer to some color
    SDL_SetRenderDrawColor( _renderer, 255, 255, 255, 255 );

    // clear the window
    SDL_RenderClear( _renderer );

    tableDest.x = tableSrc.x = 0;
    tableDest.y = tableSrc.y = 0;
    tableSrc.w = _img[0]->w;
    tableSrc.h = _img[0]->h;
    tableDest.w = TABLE_SIZE;
    tableDest.h = TABLE_SIZE;

    // draws the table texture
    table_texture = SDL_CreateTextureFromSurface(_renderer, _img[0]);
    SDL_RenderCopy(_renderer, table_texture, &tableSrc, &tableDest);

    // render the IST Logo
    height = RenderLogo(TABLE_SIZE, 0, _img[1], _renderer);

    // render the student name
    height += RenderText(TABLE_SIZE+3*MARGIN, height, myName, _font, &black, _renderer);

    // this renders the student number
    RenderText(TABLE_SIZE+3*MARGIN, height, myNumber, _font, &black, _renderer);

    // compute and adjust the size of the table and squares
    max_pos = MAX(_board_pos_x, _board_pos_y);
    board_size = (int)(BOARD_SIZE_PER*TABLE_SIZE);
    square_size_px = (board_size - (max_pos+1)*SQUARE_SEPARATOR) / max_pos;
    _board_size_px[0] = _board_pos_x*(square_size_px+SQUARE_SEPARATOR)+SQUARE_SEPARATOR;
    _board_size_px[1] = _board_pos_y*(square_size_px+SQUARE_SEPARATOR)+SQUARE_SEPARATOR;

    // renders the entire board background
    SDL_SetRenderDrawColor(_renderer, dark.r, dark.g, dark.b, dark.a );
    board.x = (TABLE_SIZE - _board_size_px[0]) >> 1;
    board.y = (TABLE_SIZE - _board_size_px[1] - 15);
    board.w = _board_size_px[0];
    board.h = _board_size_px[1];
    SDL_RenderFillRect(_renderer, &board);

    // renders the squares where the numbers will appear
    SDL_SetRenderDrawColor(_renderer, light.r, light.g, light.b, light.a );

    // iterate over all squares
    for ( int i = 0; i < _board_pos_x; i++ )
    {
        for ( int j = 0; j < _board_pos_y; j++ )
        {
            if(move[i][j] != 7){
                SDL_SetRenderDrawColor(_renderer, black.r, black.g, black.b, black.a );
            }
            board_square.x = board.x + (i+1)*SQUARE_SEPARATOR + i*square_size_px;
            board_square.y = board.y + (j+1)*SQUARE_SEPARATOR + j*square_size_px;
            board_square.w = square_size_px;
            board_square.h = square_size_px;
            SDL_RenderFillRect(_renderer, &board_square);
            SDL_SetRenderDrawColor(_renderer, light.r, light.g, light.b, light.a );
        }
    }

    // destroy everything
    SDL_DestroyTexture(table_texture);
    // return for later use
    return square_size_px;
}

/**
 * RenderLogo function: Renders the IST logo on the app window
 * \param x X coordinate of the Logo
 * \param y Y coordinate of the Logo
 * \param _logoIST surface with the IST logo image to render
 * \param _renderer renderer to handle all rendering in a window
 */
int RenderLogo(int x, int y, SDL_Surface *_logoIST, SDL_Renderer* _renderer)
{
    SDL_Texture *text_IST;
    SDL_Rect boardPos;

    // space occupied by the logo
    boardPos.x = x;
    boardPos.y = y;
    boardPos.w = _logoIST->w;
    boardPos.h = _logoIST->h;

    // render it
    text_IST = SDL_CreateTextureFromSurface(_renderer, _logoIST);
    SDL_RenderCopy(_renderer, text_IST, NULL, &boardPos);

    // destroy associated texture !
    SDL_DestroyTexture(text_IST);
    return _logoIST->h;
}

/**
 * RenderText function: Renders some text on a position inside the app window
 * \param x X coordinate of the text
 * \param y Y coordinate of the text
 * \param text string with the text to be written
 * \param _font TTF font used to render the text
 * \param _color color of the text
 * \param _renderer renderer to handle all rendering in a window
 */
int RenderText(int x, int y, const char *text, TTF_Font *_font, SDL_Color *_color, SDL_Renderer* _renderer)
{
    SDL_Surface *text_surface;
    SDL_Texture *text_texture;
    SDL_Rect solidRect;

    solidRect.x = x;
    solidRect.y = y;
    // create a surface from the string text with a predefined font
    text_surface = TTF_RenderText_Blended(_font,text,*_color);
    if(!text_surface)
    {
        printf("TTF_RenderText_Blended: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    // create texture
    text_texture = SDL_CreateTextureFromSurface(_renderer, text_surface);
    // obtain size
    SDL_QueryTexture( text_texture, NULL, NULL, &solidRect.w, &solidRect.h );
    // render it !
    SDL_RenderCopy(_renderer, text_texture, NULL, &solidRect);
    // clear memory
    SDL_DestroyTexture(text_texture);
    SDL_FreeSurface(text_surface);
    return solidRect.h;
}

/**
 * InitEverything: Initializes the SDL2 library and all graphical components: font, window, renderer
 * \param width width in px of the window
 * \param height height in px of the window
 * \param _font font that will be used to render the text
 * \param _img surface to be created with the table background and IST logo
 * \param _window represents the window of the application
 * \param _renderer renderer to handle all rendering in a window
 */
void InitEverything(int width, int height, TTF_Font **_font, SDL_Surface *_img[], SDL_Window** _window, SDL_Renderer** _renderer, TTF_Font **_font1)
{
    InitSDL();
    InitFont();
    *_window = CreateWindow(width, height);
    *_renderer = CreateRenderer(width, height, *_window);

    // load the table texture
    _img[0] = IMG_Load("table_texture.png");
    if (_img[0] == NULL)
    {
        printf("Unable to load image: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // load IST logo
    _img[1] = SDL_LoadBMP("ist_logo.bmp");
    if (_img[1] == NULL)
    {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    // this opens (loads) a font file and sets a size
    *_font = TTF_OpenFont("FreeSerif.ttf", 16);
    if(!*_font)
    {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

     *_font1 = TTF_OpenFont("FreeSerif.ttf", 38);
    if(!*_font)
    {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
}

/**
 * InitSDL: Initializes the SDL2 graphic library
 */
void InitSDL()
{
    // init SDL library
    if ( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        printf(" Failed to initialize SDL : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

/**
 * InitFont: Initializes the SDL2_ttf font library
 */
void InitFont()
{
    // Init font library
    if(TTF_Init()==-1)
    {
        printf("TTF_Init: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
}

/**
 * CreateWindow: Creates a window for the application
 * \param width width in px of the window
 * \param height height in px of the window
 * \return pointer to the window created
 */
SDL_Window* CreateWindow(int width, int height)
{
    SDL_Window *window;
    // init window
    window = SDL_CreateWindow( "ISTDots", WINDOW_POSX, WINDOW_POSY, width, height, 0 );
    // check for error !
    if ( window == NULL )
    {
        printf("Failed to create window : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    return window;
}

/**
 * CreateRenderer: Creates a renderer for the application
 * \param width width in px of the window
 * \param height height in px of the window
 * \param _window represents the window for which the renderer is associated
 * \return pointer to the renderer created
 */
SDL_Renderer* CreateRenderer(int width, int height, SDL_Window *_window)
{
    SDL_Renderer *renderer;
    // init renderer
    renderer = SDL_CreateRenderer( _window, -1, 0 );

    if ( renderer == NULL )
    {
        printf("Failed to create renderer : %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // set size of renderer to the same as window
    SDL_RenderSetLogicalSize( renderer, width, height );

    return renderer;
}
