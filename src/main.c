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

#define TRUE 1
#define FALSE 0

// Bola um começa com o x e o y aumentando.
// Bola dois começa com o x diminuindo e o y aumentando.
INT16 BALL_ONE_XVEL = 8;
INT16 BALL_ONE_YVEL = 8;
INT16 BALL_TWO_XVEL = -8;
INT16 BALL_TWO_YVEL = 8;

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
    //Colisão com as barras
    if(x <= barraEsq.x[0]){
        if(y >= barraEsq.y[0] && y <= barraEsq.y[0]+barraEsq.height){
            return TRUE;
        }

        if(y+8 >= barraEsq.y[0] && y+8 <= barraEsq.y[0]+barraEsq.height){
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
    barraDir.y[0] = 136; barraDir.y[1] = 128; barraDir.y[2] = 120;
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

    while(joypad()!=J_START){}

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

    // Meio que serve para associar o desenho do tile que está na VRAM com a referência que vamos usar para manipular o tile no código.
	set_sprite_tile(0, 0); // primeiro valor é a referência (Nb) definida para o dado através do primeiro campo do sprite_data, e o segundo valor é o indice do desenho do tile na VRAM.
    set_sprite_tile(1, 1);
    set_sprite_tile(2, 2);
    set_sprite_tile(3, 3);
    set_sprite_tile(4, 4);
    set_sprite_tile(5, 5);
    set_sprite_tile(6, 6);
    set_sprite_tile(7, 7);

	move_sprite(ballOne.spritid, ballOne.x, ballOne.y);
	move_sprite(barraEsq.spritid[0], barraEsq.x[0], barraEsq.y[0]);
    move_sprite(barraEsq.spritid[1], barraEsq.x[1], barraEsq.y[1]);
    move_sprite(barraEsq.spritid[2], barraEsq.x[2], barraEsq.y[2]);
    move_sprite(barraDir.spritid[0], barraDir.x[0], barraDir.y[0]);
    move_sprite(barraDir.spritid[1], barraDir.x[1], barraDir.y[1]);
    move_sprite(barraDir.spritid[2], barraDir.x[2], barraDir.y[2]);
    move_sprite(ballTwo.spritid, ballTwo.x, ballTwo.y);


	SHOW_SPRITES;
    SHOW_BKG;
    DISPLAY_ON;

	while(1){
		if (joypad() & J_UP)
		{ 
            if(canPlayerMove(barraEsq.y[0]-8, barraEsq.y[2]-8)){
                for(UINT8 x=0; x<3; x++){
                    barraEsq.y[x]-=8;
			        move_sprite(x+1,barraEsq.x[x],barraEsq.y[x]);
                }
            }
		}
		else if (joypad() & J_DOWN)
		{ 
            if(canPlayerMove(barraEsq.y[0]+8, barraEsq.y[2]+8)){
                for(UINT8 x=0; x<3; x++){
                    barraEsq.y[x]+=8;
			        move_sprite(x+1,barraEsq.x[x],barraEsq.y[x]);
                }
            }
		}
        
        moveBola(&ballOne);

        moveBola(&ballTwo);

        for(UINT16 i=0; i<6; i++){
		    wait_vbl_done();
        }
	}
}