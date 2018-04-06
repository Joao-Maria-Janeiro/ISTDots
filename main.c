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

// declaration of the functions related to graphical issues
void InitEverything(int , int , TTF_Font **, SDL_Surface **, SDL_Window ** , SDL_Renderer ** );
void InitSDL();
void InitFont();
SDL_Window* CreateWindow(int , int );
SDL_Renderer* CreateRenderer(int , int , SDL_Window *);
int RenderText(int, int, const char *, TTF_Font *, SDL_Color *, SDL_Renderer *);
int RenderLogo(int, int, SDL_Surface *, SDL_Renderer *);
int RenderTable(int, int, int [], TTF_Font *, SDL_Surface **, SDL_Renderer *);
void ProcessMouseEvent(int , int , int [], int , int *, int * );
void RenderPoints(int [][MAX_BOARD_POS], int, int, int [], int, SDL_Renderer *);
void RenderStats( SDL_Renderer *, TTF_Font *, int [], int , int );
void filledCircleRGBA(SDL_Renderer * , int , int , int , int , int , int );
void parameters(int *, int *, int*, int *, int*);

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

    int rows, columns, int_colors, jogadas = 0;
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
    int derrotas = 0;
    int count1 = 0;

    int pontos[MAX_BOARD_POS];

    board_pos_x = 5;
    board_pos_y = 7;
    // some examples
//    board[0][0] = 1;
//    board[2][0] = 2;
//    board[3][3] = 3;
//    board[4][4] = 4;
//    board[4][0] = 1;
//    board[3][0] = 1;
//    board[0][1] = 1;


    printf( "Whats your name? " );
   fgets( username, sizeof( username ), stdin );


    //Parameters to intialize the game
    parameters(&board_pos_y, &board_pos_x, &int_colors, pontos, &jogadas);

    //Randomly generates colors
    game_board(board, board_pos_x, board_pos_y, int_colors);

    // initialize graphics
    InitEverything(width, height, &serif, imgs, &window, &renderer);

    //Sets the move array to all 7 before starting the game
    move_reset(board_pos_x, board_pos_y, move);



    while( quit == 0 )
    {
        // while there's events to handle
        while( SDL_PollEvent( &event ) )
        {
            if( event.type == SDL_QUIT )
            {
                    quit = 1;// quit !
            }
            else if ( event.type == SDL_KEYDOWN )
            {
                switch ( event.key.keysym.sym )
                {
                    case SDLK_n:
                       game_board(board, board_pos_x, board_pos_y, int_colors);
                       derrotas++;
                       move_reset(board_pos_x, board_pos_y, move);
                       break;
                    case SDLK_q:
                        quit = 1;
                        filecreate();
                        break;
                    case SDLK_u:
                        // todo
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
            }
            else if ( event.type == SDL_MOUSEBUTTONUP )
            {
                ProcessMouseEvent(event.button.x, event.button.y, board_size_px, square_size_px, &pt_x, &pt_y);
                printf("Button up: %d %d\n", pt_x, pt_y);
                play = 2;

//                    for(j = 0; j < board_pos_y; j++){
//                    for(i = 0; i < board_pos_x; i++){
//                       printf("%d ", move[i][j]); //Tive de dar printf ao contrário pois as linhas estavam a ficar nas colunas, assim o print já está correto!
//                        }
//                        printf("\n");
//                        }
//
//                    printf("-----------------\n");
//
//
//                    for(i = 0; i < mem_pos; i++){
//                       printf("%d ", mem[i][0]);
//                        printf("%d", mem[i][1]);
//                        printf("\n");
//                        }

                valid = evaluate_color(board_pos_x, board_pos_y, move, &count, &color);
//                printf("A jogada vale: %d\n", valid);
                printf("Rebentou %d bolas\n", count);
                valid_pos = evaluate_pos(board_pos_x, board_pos_y, move);
//                printf("A posicao vale: %d", valid_pos);
                if(valid == 0 && count >=2 && valid_pos == 0){
                    movedots(board_pos_x, board_pos_y, board, move, int_colors);
                    jogadas --;
                    pontos[color] = pontos[color] - count;
//                printf("%d", square); // Se for quadrado retorna 0
                if ( square == 0 && validate != 1){
                    //remove_inside_square(mem, mem_pos, board, color);
                    remove_same_color(board_pos_x, board_pos_y, board, move, int_colors, &count1);
                    if(pontos[color] - count1 < 0){
                        pontos[color] = 0;
                    }else{
                        pontos[color] = pontos[color] - count1;
                    }
                }}

                move_reset(board_pos_x, board_pos_y, move);
                mem_pos = 0;
                validate = 0;

            }
            else if ( event.type == SDL_MOUSEMOTION )
            {
                ProcessMouseEvent(event.button.x, event.button.y, board_size_px, square_size_px, &pt_x, &pt_y);
                //printf("Mouse: %d %d\n", pt_x, pt_y);
                if( play == 1 ){
                    if( lastXpos != pt_x || lastYpos != pt_y){
                    square = square_detect(board_pos_x, board_pos_y, board, move, int_colors, pt_x, pt_y);
//                    printf("%d", square);
                    move[pt_x][pt_y] = board[pt_x][pt_y];
                    SDL_RenderDrawLine(renderer, event.button.x, event.button.y, event.button.x+5, event.button.y +2);
                    SDL_RenderPresent(renderer);
                    lastXpos = pt_x;
                    lastYpos = pt_y;
                    mem[mem_pos][0] = pt_x;
                    mem[mem_pos][1] = pt_y;
                    validate = square_validate(mem, mem_pos);//Se for quadrado retorna 0
                    mem_pos++;
                    }

                }


            }

        }



        // render game table
        square_size_px = RenderTable( board_pos_x, board_pos_y, board_size_px, serif, imgs, renderer);
        // render board
        RenderPoints(board, board_pos_x, board_pos_y, board_size_px, square_size_px, renderer);
        //Render stats
        RenderStats( renderer, serif, pontos, int_colors, jogadas);
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


void parameters(int *rows1, int *columns1, int *int_colors1, int pontos[MAX_BOARD_POS], int *jogadas1){

    int rows, columns, int_colors, jogadas = 0;
    int i = 0;

    printf("Qual é o tamanho do tabuleiro que quer(rows * columns): ");
    scanf("%d %d", &rows, &columns);
    if (rows < 15 && rows > 5 && columns < 15 && columns > 5 ){

    }else{
        printf("\nOs valores do tabuleiro têm de estar compreeendidos entre 5 e 15");
        printf("Qual é o tamanho do tabuleiro que quer(rows * columns): ");
        scanf(" %d %d", &rows, &columns);
    }


    printf("\nQuantas cores quer no jogo: ");
    scanf(" %d", &int_colors);
    if( int_colors <= 5){

    }else{
        printf("\nNão podem existir mais que 5 cores no jogo");
        printf("\nQuantas cores quer no jogo: ");
        scanf(" %d", &int_colors);
    }


//    printf("\nNúmero de pontos a alcançar na: ");
//    scanf(" %d", &pontos);
//    if(pontos <= 99){
//
//    }else{
//        printf("\nNão pode ser mais que 99 pontos");
//        printf("\nNúmero de pontos a alcançar: ");
//        scanf("%d", &pontos);
//    }

    for( i = 0; i < int_colors; i++){
    printf("\nNúmero de pontos a alcançar na cor %d: ", i+1);
    scanf(" %d", &pontos[i]);
    if( pontos[i] > 99){
        printf("Esse valor é superior a 99");
        printf("\nNúmero de pontos a alcançar na cor %d: ", i);
        scanf(" %d", &pontos[i]);
    }

    }


    printf("\nNúmero máximo de jogadas: ");
    scanf(" %d", &jogadas);
    if(jogadas <= 99){

    }else{
        printf("\nNão pode ser mais que 99 jogadas");
        printf("\nNúmero máximo de jogadas");
        scanf(" %d", &jogadas);
    }


    *rows1 = rows;
    *columns1 = columns;
    *int_colors1 = int_colors;
    *jogadas1 = jogadas;
}


void game_board(int board[MAX_BOARD_POS][MAX_BOARD_POS], int _lines, int _col, int _colors){
    int i,j = 0;
    srand(time(NULL));

    for(i = 0; i < _lines; i++){
        for(j = 0; j < _col; j++){
            board[i][j] = ((int)rand()%(_colors));
        }
    }
}


void move_reset(int board_pos_x, int board_pos_y, int move[MAX_BOARD_POS][MAX_BOARD_POS]){
    int i,j = 0;
    for(i = 0; i < board_pos_x; i++){
    for(j = 0; j < board_pos_y; j++){
        move[i][j] = 7;
        }
            }
}

int evaluate_color(int board_pos_x, int board_pos_y, int move[MAX_BOARD_POS][MAX_BOARD_POS], int *count, int *color){
    int aux = 9;
    int i, j, count1 = 0;
    for(i = 0; i < board_pos_x; i++){
    for(j = 0; j < board_pos_y; j++){
        if(move[i][j] != 7){
            if( aux == 9 ){
                aux = move[i][j];
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

int evaluate_pos(int board_pos_x, int board_pos_y, int move[MAX_BOARD_POS][MAX_BOARD_POS]){
    int aux = 9;
    int i, j, count1 = 0;
    for(i = 0; i < board_pos_x; i++){
    for(j = 0; j < board_pos_y; j++){
        if(move[i][j] != 7){
            if ( move[i][j] == move[i+1][j+1] && move[i][j] != move[i+1][j] && move[i][j] != move[i-1][j] && move[i][j] != move[i][j+1] && move[i][j] != move[i][j-1] || move[i][j] == move[i+1][j-1] && move[i][j] != move[i+1][j] && move[i][j] != move[i-1][j] && move[i][j] != move[i][j+1] && move[i][j] != move[i][j-1] || move[i][j] == move[i-1][j+1] && move[i][j] != move[i+1][j] && move[i][j] != move[i-1][j] && move[i][j] != move[i][j+1] && move[i][j] != move[i][j-1] || move[i][j] == move[i-1][j-1] && move[i][j] != move[i+1][j] && move[i][j] != move[i-1][j] && move[i][j] != move[i][j+1] && move[i][j] != move[i][j-1]){
                return -1;
            }

        }


            }}

    return 0;
}

void movedots(int board_pos_x, int board_pos_y, int board[MAX_BOARD_POS][MAX_BOARD_POS], int move[MAX_BOARD_POS][MAX_BOARD_POS], int _colors){
    int i, j, c,d = 0;
    int aux = 9;
    srand(time(NULL));

    for(i = 0; i < board_pos_x; i++){
    for(j = 0; j < board_pos_y; j++){
        if(move[i][j] != 7){
            if( aux == 9 ){
                aux = move[i][j];
            }}}}

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

int square_detect(int board_pos_x, int board_pos_y, int board[MAX_BOARD_POS][MAX_BOARD_POS], int move[MAX_BOARD_POS][MAX_BOARD_POS], int _colors, int pt_x, int pt_y){
    int i, j = 0;

    if( move[pt_x][pt_y] != 7){
            return 0;
    }

return 1;
}

int square_validate( int mem[STRING_SIZE][STRING_SIZE], int mem_pos ){

    if( mem[mem_pos][0] == mem[mem_pos-2][0] && mem[mem_pos][1] == mem[mem_pos-2][1] ){
        return 1;
    }
return 0;
}

int remove_same_color(int board_pos_x, int board_pos_y, int board[MAX_BOARD_POS][MAX_BOARD_POS], int move[MAX_BOARD_POS][MAX_BOARD_POS], int _colors, int *count){
    int i, j, c,d = 0;
    int aux = 9;
    int count1 = 0;
    srand(time(NULL));

    for(i = 0; i < board_pos_x; i++){
    for(j = 0; j < board_pos_y; j++){
        if(move[i][j] != 7){
            if( aux == 9 ){
                aux = move[i][j];
            }}}}

    for(i = 0; i < board_pos_x; i++){
    for(j = 0; j < board_pos_y; j++){
        if( board[i][j] == aux ){
        count1++;
            for(d = 0; d < j; d++){
                board[i][j-d] = board[i][j-d-1];
            }
            board[i][0] = (int) (rand()% (_colors));
        }
    }
    }

    *count = count1;

}

void remove_inside_square( int mem[STRING_SIZE][STRING_SIZE], int mem_pos, int board[MAX_BOARD_POS][MAX_BOARD_POS], int color ){
int i, j, maximum_x, maximum_y = 0;
int minimum_x = 40;
int minimum_y = 40;
int d = 0;
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
        board[i][j] = color;
        printf("\n%d %d\n", i,j);
    }
    }

}

void filecreate(){

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
    _mouse_pos_x = _mouse_pos_x - x_corner;
    _mouse_pos_y = _mouse_pos_y - y_corner;

    *_pt_x = _mouse_pos_x / (_square_size_px + SQUARE_SEPARATOR);
    *_pt_y = _mouse_pos_y / (_square_size_px + SQUARE_SEPARATOR);
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

    SDL_Rect jogadas = {50,50,80,50};
    SDL_RenderFillRect(_renderer, &jogadas);
    RenderText(65, 65, numberPlays, _font, &black, _renderer);

    //Dar print às cores
    for(int i = 0; i < _ncolors; i++){
        SDL_SetRenderDrawColor(_renderer, 205, 193, 181, 255);
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
        TTF_Font *_font, SDL_Surface *_img[], SDL_Renderer* _renderer )
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
            board_square.x = board.x + (i+1)*SQUARE_SEPARATOR + i*square_size_px;
            board_square.y = board.y + (j+1)*SQUARE_SEPARATOR + j*square_size_px;
            board_square.w = square_size_px;
            board_square.h = square_size_px;
            SDL_RenderFillRect(_renderer, &board_square);
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
void InitEverything(int width, int height, TTF_Font **_font, SDL_Surface *_img[], SDL_Window** _window, SDL_Renderer** _renderer)
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
    window = SDL_CreateWindow( "1024", WINDOW_POSX, WINDOW_POSY, width, height, 0 );
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
