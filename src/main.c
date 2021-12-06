#include <gb/gb.h>
#include <stdio.h>
#include <stdlib.h>
#include "..\assets\barraLongaPreta.c"
#include "..\assets\bola.c"
#include "..\assets\parede.c"
#include "..\assets\backgroundPong.c"
#include "..\assets\linhaDaQuadra.c"
#include "..\assets-test\testeback2.c"
#include "..\assets-test\mapteste3.c"
#include "..\assets\pontuacaoNumbers.c"
#include "multiplayer.c"
#define TRUE 1
#define FALSE 0
#define WINNER_SCORE 8

//SCORES DOS PLAYERS
UINT16 SCORE_PLAYER_ONE = 0;
UINT16 SCORE_PLAYER_TWO = 0;

// Bola um começa com o x e o y aumentando.
// Bola dois começa com o x diminuindo e o y aumentando.
INT16 BALL_ONE_XVEL = 4;
INT16 BALL_ONE_YVEL = 4;
INT16 BALL_TWO_XVEL = -4;
INT16 BALL_TWO_YVEL = 4;

typedef struct Ball {
	UINT16 spritid;
	UINT16 x;
	UINT16 y;
	UINT16 width;
	UINT16 height;
    UINT16 latestPlayer; // serve para indica qual player vai receber pontuação dos blocos quebrados por ter sido o último player a bater na bola.
} Ball;

typedef struct Barra {
	UINT16 spritid[3];
	UINT16 x[3];
	UINT16 y[3];
	UINT16 width;
	UINT16 height;
} BarraGame;

UBYTE vetorBarrasRemovidas[360];

//Barra global para a colisão das barras
BarraGame barraEsq, barraDir;

/*
* Se a direção for 0 é para cima, se for 1 é para baixo.
*/
UBYTE canPlayerMove(UINT16 topy, UINT16 bottomy){
    if(topy > 16 && bottomy <= 17*8+8){
        return TRUE;
    }
    return FALSE;
}


UBYTE checkBallCollisions(INT16 x, INT16 y){
    //Colisão com a barra esquerda
    if(x <= barraEsq.x[0]){
        if(y >= barraEsq.y[0] && y <= barraEsq.y[0]+barraEsq.height){
            return TRUE;
        }
        if(y+8 >= barraEsq.y[0] && y+8 <= barraEsq.y[0]+barraEsq.height){
            return TRUE;
        }
    }

    //Colisão com a barra direita
    if(x >= barraDir.x[0]){
        if(y >= barraDir.y[0] && y <= barraDir.y[0]+barraDir.height){
            return TRUE;
        }
        if(y+8 >= barraDir.y[0] && y+8 <= barraDir.y[0]+barraDir.height){
            return TRUE;
        }
    }

    //Colisão com os blocos e com as paredes!
    INT16 indexTLx, indexTLy, tileindexTL;
    INT16 teste_tile[1];

    indexTLx = (x - 8) / 8;
    indexTLy = (y - 16) / 8;
    tileindexTL = 20 * indexTLy + indexTLx;
    UINT8 next_cell[1];
    get_bkg_tiles(indexTLx, indexTLy, 1, 1, next_cell);

    if(vetorBarrasRemovidas[tileindexTL] == TRUE){
        return FALSE;
    }

    if(BackgroundPong[tileindexTL] == 0x07){
        unsigned char blank_tile[1] = {0x00};
        set_bkg_tiles(indexTLx, indexTLy, 1, 1, blank_tile);
        vetorBarrasRemovidas[tileindexTL] = TRUE;
    }else{
        if(indexTLx == 0){ // Marca ponto para barra da esquerda
            SCORE_PLAYER_TWO += 1;
            if(SCORE_PLAYER_TWO<WINNER_SCORE){
                set_sprite_tile(9, SCORE_PLAYER_TWO + 8);
            }
            wait_vbl_done();
        }

        if(indexTLx == 19){ //Marca ponto para barra da direita
            SCORE_PLAYER_ONE += 1;
            if(SCORE_PLAYER_ONE<WINNER_SCORE){
                set_sprite_tile(8, SCORE_PLAYER_ONE + 8);
            }
            wait_vbl_done();
        }
    }
    
    return BackgroundPong[tileindexTL] != 0;
}

void moveBola(Ball* selectedBall){
    /*
        *  INT8 BALL_ONE_XVEL = 1;
        *  INT8 BALL_ONE_YVEL = 1;
        *  INT8 BALL_TWO_XVEL = -1;
        *  INT8 BALL_TWO_YVEL = 1;
    */

    if(selectedBall->spritid==0){

        if(checkBallCollisions(selectedBall->x+BALL_ONE_XVEL, selectedBall->y)){
            BALL_ONE_XVEL = -BALL_ONE_XVEL;

        }

        if(checkBallCollisions(selectedBall->x, selectedBall->y+BALL_ONE_YVEL)){
            BALL_ONE_YVEL = -BALL_ONE_YVEL;
        }
        
        selectedBall->x += BALL_ONE_XVEL;
        selectedBall->y += BALL_ONE_YVEL;
        move_sprite(selectedBall->spritid, selectedBall->x, selectedBall->y);

    }else{

        if(checkBallCollisions(selectedBall->x+BALL_TWO_XVEL, selectedBall->y)){
            BALL_TWO_XVEL = -BALL_TWO_XVEL;
        }

        if(checkBallCollisions(selectedBall->x, selectedBall->y+BALL_TWO_YVEL)){
            BALL_TWO_YVEL = -BALL_TWO_YVEL;
        }

        selectedBall->x += BALL_TWO_XVEL;
        selectedBall->y += BALL_TWO_YVEL;
        move_sprite(selectedBall->spritid, selectedBall->x, selectedBall->y);


    }
}

void main(){

    SPRITES_8x8;
    Ball ballOne, ballTwo;

    barraDir.spritid[0] = 4; barraDir.spritid[1] = 5; barraDir.spritid[2] = 6;
    barraDir.x[0] = 152; barraDir.x[1] = 152; barraDir.x[2] = 152;
    barraDir.y[0] = 120; barraDir.y[1] = 128; barraDir.y[2] = 136;
    barraDir.width = 8; barraDir.height = 24;

    barraEsq.spritid[0] = 1; barraEsq.spritid[1] = 2; barraEsq.spritid[2] = 3;
    barraEsq.x[0] = 16; barraEsq.x[1] = 16; barraEsq.x[2] = 16;
    barraEsq.y[0] = 32; barraEsq.y[1] = 40; barraEsq.y[2] = 48;
    barraEsq.width = 8; barraEsq.height = 24;

    ballOne.spritid = 0;
    ballOne.x = 48; ballOne.y = 24;
    ballOne.width = 8; ballOne.height = 8;

    ballTwo.spritid = 7;
    ballTwo.x = 120; ballTwo.y = 64;
    ballTwo.width = 8; ballTwo.height = 8;

    /* set_sprite_data: (Tile de início, a quantidade de tiles do arquivo que vai carregar, data)
     * Tile de início é a posição do VRAM do gamebou onde ele vai começar, todos os outros tiles vao ser colocados a partir dele.
     * set_sprite_tile: (Um valor que você quer atribuir ao sprite, tile que voce definiu no set_sprite_data)
     * mov_sprite: move
     * set_bkg_data(Tile de inicio (Esse vai ser o da tela do gameboy em si), quantidade de tiles 
     *  necessárias para o background, a função asset dos tiles)
     * set_bkg_tiles(X inicial, y incial, x final, y final, mapa)
     * Limites: Horizontal: De 8 em 8 até 20*8 e vertical de 16 em 8 até 18*8+8
    */

    set_bkg_data(0, 21, BackTeste2); // Load os sprites que compõem o background na memória
    set_bkg_tiles(0, 0, 20, 18, MapTeste3);
    SHOW_BKG;

    int playerMultiplayerL_Or_R = wait_for_connection();

    set_bkg_data(0, 8, LinhaDaQuadra);
    set_bkg_tiles(0, 0, 20, 18, BackgroundPong);

    // Bola Um
	set_sprite_data(ballOne.spritid, 1, Bola);
    // Barra Esquerda
    set_sprite_data(barraEsq.spritid[0], 1, Barra);
    set_sprite_data(barraEsq.spritid[1], 1, Barra);
    set_sprite_data(barraEsq.spritid[2], 1, Barra);
    // Barra Direita
    set_sprite_data(barraDir.spritid[0], 1, Barra);
    set_sprite_data(barraDir.spritid[1], 1, Barra);
    set_sprite_data(barraDir.spritid[2], 1, Barra);
    // Bola Dois
	set_sprite_data(ballTwo.spritid, 1, Bola);
    // Scores
    set_sprite_data(8, 9, Pontuacao);
    // Meio que serve para associar o desenho do tile que está na VRAM com a referência que vamos usar para manipular o tile no código.
	set_sprite_tile(0, 0); // primeiro valor é a referência (Nb) definida para o dado através do primeiro campo do sprite_data, e o segundo valor é o indice do desenho do tile na VRAM.
    set_sprite_tile(1, 1);
    set_sprite_tile(2, 2);
    set_sprite_tile(3, 3);
    set_sprite_tile(4, 4);
    set_sprite_tile(5, 5);
    set_sprite_tile(6, 6);
    set_sprite_tile(7, 7);
    set_sprite_tile(8, 8);
    set_sprite_tile(9, 8);


	move_sprite(ballOne.spritid, ballOne.x, ballOne.y);
	move_sprite(barraEsq.spritid[0], barraEsq.x[0], barraEsq.y[0]);
    move_sprite(barraEsq.spritid[1], barraEsq.x[1], barraEsq.y[1]);
    move_sprite(barraEsq.spritid[2], barraEsq.x[2], barraEsq.y[2]);
    move_sprite(barraDir.spritid[0], barraDir.x[0], barraDir.y[0]);
    move_sprite(barraDir.spritid[1], barraDir.x[1], barraDir.y[1]);
    move_sprite(barraDir.spritid[2], barraDir.x[2], barraDir.y[2]);
    move_sprite(ballTwo.spritid, ballTwo.x, ballTwo.y);
    move_sprite(8, 32 ,32); // Posição do score do player 1
    move_sprite(9, 136, 32); // Posição do score do player 2

	SHOW_SPRITES;
    SHOW_BKG;
    DISPLAY_ON;

	while(1){
        if(playerMultiplayerL_Or_R==0){
            NR52_REG = 0x80;  //habilita o som
            NR50_REG = 0x77; //volume no maximo
            WORD pad = joypad();
            int input[1];
            recieve_data(input,1);
            if (pad & J_UP)
            { 
                if(canPlayerMove(barraEsq.y[0]-8, barraEsq.y[2]-8)){
                    for(UINT8 x=0; x<3; x++){
                        barraEsq.y[x]-=8;
                        move_sprite(x+1,barraEsq.x[x],barraEsq.y[x]);
                    }
                }
            }
            if (pad & J_DOWN)
            { 
                if(canPlayerMove(barraEsq.y[0]+8, barraEsq.y[2]+8)){
                    for(UINT8 x=0; x<3; x++){
                        barraEsq.y[x]+=8;
                        move_sprite(x+1,barraEsq.x[x],barraEsq.y[x]);
                    }
                }
            }
            if(input[0]==1){
                if(canPlayerMove(barraDir.y[0]-8, barraDir.y[2]-8)){
                    for(UINT8 x=0; x<3; x++){
                        barraDir.y[x]-=8;
                        move_sprite(x+4,barraDir.x[x],barraDir.y[x]);
                    }
                }
            }
            if(input[0]==0){
                if(canPlayerMove(barraDir.y[0]+8, barraDir.y[2]+8)){
                    for(UINT8 x=0; x<3; x++){
                        barraDir.y[x]+=8;
                        move_sprite(x+4,barraDir.x[x],barraDir.y[x]);
                    }
                }
            }
            moveBola(&ballOne);

            moveBola(&ballTwo);

            /*for(UINT16 i=0; i<6; i++){
                wait_vbl_done();
            }*/
            
            int data[12];
            data[0] = ballOne.x;
            data[1] = ballOne.y;
            data[2] = ballTwo.x;
            data[3] = ballTwo.y;
            data[4] = barraEsq.y[0];
            data[5] = barraEsq.y[1];
            data[6] = barraEsq.y[2];
            data[7] = barraDir.y[0];
            data[8] = barraDir.y[1];
            data[9] = barraDir.y[2];
            data[10] = SCORE_PLAYER_ONE;
            data[11] = SCORE_PLAYER_TWO;
            send_data(data, 12);
            if(SCORE_PLAYER_ONE == WINNER_SCORE || SCORE_PLAYER_TWO == WINNER_SCORE){
                if(SCORE_PLAYER_ONE == WINNER_SCORE)
                    printf("\n\n\n\n\n\n\n      Parabens\n    JOGADOR UM\n    voce venceu!");
                else
                    while(1){}
                //Esconder os sprites de alguma forma.
                HIDE_SPRITES;
                while(1){
                    WORD pad = joypad();
                    if(pad) 
                    break;
                }
                if((SCORE_PLAYER_ONE == WINNER_SCORE) || (SCORE_PLAYER_TWO == WINNER_SCORE)){
                    break;
                }
            }
		}else{
            WORD pad = joypad();
            int input[1];
            input[0] = 3;
            if (pad & J_UP)
            { 
                input[0]=1;
            }
            if (pad & J_DOWN)
            { 
                input[0]=0;
            }
            send_data(input,1);
            int datarecieve[12];
            recieve_data(datarecieve, 12);
            ballOne.x = datarecieve[0];
            ballOne.y = datarecieve[1];
            ballTwo.x = datarecieve[2];
            ballTwo.y = datarecieve[3];
            barraEsq.y[0] = datarecieve[4];
            barraEsq.y[1] = datarecieve[5];
            barraEsq.y[2] = datarecieve[6];
            barraDir.y[0] = datarecieve[7];
            barraDir.y[1] = datarecieve[8];
            barraDir.y[2] = datarecieve[9];
            SCORE_PLAYER_ONE = datarecieve[10];
            SCORE_PLAYER_TWO = datarecieve[11];

            if(SCORE_PLAYER_ONE == WINNER_SCORE || SCORE_PLAYER_TWO == WINNER_SCORE){
                if(SCORE_PLAYER_TWO == WINNER_SCORE)
                    printf("\n\n\n\n\n\n\n      Parabens\n    JOGADOR DOIS\n    voce venceu!");
                else
                    while(1){}
                //Esconder os sprites de alguma forma.
                HIDE_SPRITES;
                while(1){
                    WORD pad = joypad();
                    if(pad) 
                    break;
                }
                if((SCORE_PLAYER_ONE == WINNER_SCORE) || (SCORE_PLAYER_TWO == WINNER_SCORE)){
                    break;
                }
            }

            move_sprite(ballOne.spritid, ballOne.x, ballOne.y);
            move_sprite(barraEsq.spritid[0], barraEsq.x[0], barraEsq.y[0]);
            move_sprite(barraEsq.spritid[1], barraEsq.x[1], barraEsq.y[1]);
            move_sprite(barraEsq.spritid[2], barraEsq.x[2], barraEsq.y[2]);
            move_sprite(barraDir.spritid[0], barraDir.x[0], barraDir.y[0]);
            move_sprite(barraDir.spritid[1], barraDir.x[1], barraDir.y[1]);
            move_sprite(barraDir.spritid[2], barraDir.x[2], barraDir.y[2]);
            move_sprite(ballTwo.spritid, ballTwo.x, ballTwo.y);

            moveBola(&ballOne);

            moveBola(&ballTwo);

            /*for(UINT16 j=0; j<6; j++){
                wait_vbl_done();
            }*/
        }
	}
}