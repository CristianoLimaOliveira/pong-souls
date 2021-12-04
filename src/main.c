#include <gb/gb.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <rand.h>
#include <stdint.h>
#include "..\assets\barraLongaPreta.c"
#include "..\assets\bola.c"
#include "..\assets\parede.c"
#include "..\assets\backgroundPong.c"
#include "..\assets\linhaDaQuadra.c"
#include "..\assets-test\testeback.c"
#include "..\assets-test\testeback2.c"
#include "..\assets-test\mapteste.c"
#include "..\assets-test\mapteste2.c"
#include "..\assets-test\mapteste3.c"

typedef struct Ball {
	UINT16 spritid;
	UINT16 x;
	UINT16 y;
	UINT16 width;
	UINT16 height;
    UINT16 direction;
    UINT16 latestPlayer; // serve para indica qual player vai receber pontuação dos blocos quebrados por ter sido o último player a bater na bola.
} Ball;

typedef struct Barra {
	UINT16 spritid[3];
	UINT16 x[3];
	UINT16 y[3];
	UINT16 width;
	UINT16 height;
} BarraGame;

UINT16 transitionBarraRight = 0;

UINT16 sortearUmValor(){
    uint16_t seed = LY_REG;
    seed |= (uint16_t)DIV_REG << 8;
    initrand(seed);
    return ((UINT16)rand()) % (UINT16)3;
}

UINT16 canplayermove(UINT16 newplayerx, UINT16 newplayery){
    UINT16 indexTLx, indexTLy, tileindexTL;
    UBYTE result;

    indexTLx = (newplayerx - 8) / 8;
    indexTLy = (newplayery - 16) / 8;
    tileindexTL = 20 * indexTLy + indexTLx;

    result = BackgroundPong[tileindexTL] == 0x00; //0x00 indica os locais do background sem tiles.

    return result;
}

void moveBola(Ball* selectedBall){
    UINT16 resultSorteio=sortearUmValor();

    if(selectedBall->direction == 0 && !canplayermove(selectedBall->x, (selectedBall->y-8))){
        resultSorteio=sortearUmValor();
        if(resultSorteio==0 && canplayermove((selectedBall->x-8), (selectedBall->y+8))){
            selectedBall->direction = 3;
        } else if(resultSorteio==1 && canplayermove(selectedBall->x, (selectedBall->y+8))){
            selectedBall->direction = 4;
        }else if(resultSorteio==2 && canplayermove((selectedBall->x+8), (selectedBall->y+8))){
            selectedBall->direction = 5;
        } else if(canplayermove((selectedBall->x-8), (selectedBall->y+8))){
            selectedBall->direction = 3;
        } else if(canplayermove(selectedBall->x, (selectedBall->y+8))){
            selectedBall->direction = 4;
        }else if(canplayermove((selectedBall->x+8), (selectedBall->y+8))){
            selectedBall->direction = 5;
        }
    } else if(selectedBall->direction == 1 && !canplayermove((selectedBall->x-8), (selectedBall->y-8))){
        resultSorteio=sortearUmValor();
        if(resultSorteio==0 && canplayermove((selectedBall->x-8), selectedBall->y)){
            selectedBall->direction = 2;
        } else if(resultSorteio==1 && canplayermove((selectedBall->x-8), (selectedBall->y+8))){
            selectedBall->direction = 3;
        } else if(canplayermove((selectedBall->x-8), selectedBall->y)){
            selectedBall->direction = 2;
        } else if(canplayermove((selectedBall->x-8), (selectedBall->y+8))){
            selectedBall->direction = 3;
        }else if(canplayermove((selectedBall->x+8), selectedBall->y)){
            selectedBall->direction = 6;
        }
    } else if(selectedBall->direction == 2 && !canplayermove((selectedBall->x-8), selectedBall->y)){
        resultSorteio=sortearUmValor();
        if(resultSorteio==0 && canplayermove((selectedBall->x+8), (selectedBall->y+8))){
            selectedBall->direction = 5;
        } else if(resultSorteio==1 && canplayermove((selectedBall->x+8), selectedBall->y)){
            selectedBall->direction = 6;
        }else if(resultSorteio==2 && canplayermove((selectedBall->x+8), (selectedBall->y-8))){
            selectedBall->direction = 7;
        } else if(canplayermove((selectedBall->x+8), (selectedBall->y+8))){
            selectedBall->direction = 5;
        } else if(canplayermove((selectedBall->x+8), selectedBall->y)){
            selectedBall->direction = 6;
        }else if(canplayermove((selectedBall->x+8), (selectedBall->y-8))){
            selectedBall->direction = 7;
        }
    } else if(selectedBall->direction == 3 && !canplayermove((selectedBall->x-8), (selectedBall->y+8))){
        resultSorteio=sortearUmValor();
        if(resultSorteio==0 && canplayermove((selectedBall->x-8), selectedBall->y)){
            selectedBall->direction = 2;
        } else if(resultSorteio==1 && canplayermove((selectedBall->x-8), (selectedBall->y-8))){
            selectedBall->direction = 1;
        } else if(canplayermove((selectedBall->x-8), selectedBall->y)){
            selectedBall->direction = 2;
        } else if(canplayermove((selectedBall->x-8), (selectedBall->y-8))){
            selectedBall->direction = 1;
        }else if(canplayermove((selectedBall->x+8), selectedBall->y)){
            selectedBall->direction = 6;
        }
    } else if(selectedBall->direction == 4 && !canplayermove(selectedBall->x, (selectedBall->y+8))){
        resultSorteio=sortearUmValor();
        if(resultSorteio==0 && canplayermove((selectedBall->x+8), (selectedBall->y-8))){
            selectedBall->direction = 7;
        } else if(resultSorteio==1 && canplayermove(selectedBall->x, (selectedBall->y-8))){
            selectedBall->direction = 0;
        }else if(resultSorteio==2 && canplayermove((selectedBall->x-8), (selectedBall->y-8))){
            selectedBall->direction = 1;
        } else if(canplayermove((selectedBall->x+8), (selectedBall->y-8))){
            selectedBall->direction = 7;
        } else if(canplayermove(selectedBall->x, (selectedBall->y-8))){
            selectedBall->direction = 0;
        }else if(canplayermove((selectedBall->x-8), (selectedBall->y-8))){
            selectedBall->direction = 1;
        }
    } else if(selectedBall->direction == 5 && !canplayermove((selectedBall->x+8), (selectedBall->y+8))){
        resultSorteio=sortearUmValor();
        if(resultSorteio==1 && canplayermove((selectedBall->x+8), (selectedBall->y-8))){
            selectedBall->direction = 7;
        }else if(resultSorteio==2 && canplayermove((selectedBall->x+8), selectedBall->y)){
            selectedBall->direction = 6;
        } else if(canplayermove((selectedBall->x+8), (selectedBall->y-8))){
            selectedBall->direction = 7;
        }else if(canplayermove((selectedBall->x+8), selectedBall->y)){
            selectedBall->direction = 6;
        } else if(canplayermove((selectedBall->x-8), selectedBall->y)){
            selectedBall->direction = 2;
        }
    } else if(selectedBall->direction == 6 && !canplayermove((selectedBall->x+8), selectedBall->y)){
        resultSorteio=sortearUmValor();
        if(resultSorteio==0 && canplayermove((selectedBall->x-8), (selectedBall->y-8))){
            selectedBall->direction = 1;
        } else if(resultSorteio==1 && canplayermove((selectedBall->x-8), selectedBall->y)){
            selectedBall->direction = 2;
        }else if(resultSorteio==2 && canplayermove((selectedBall->x-8), (selectedBall->y+8))){
            selectedBall->direction = 3;
        } else if(canplayermove((selectedBall->x-8), (selectedBall->y-8))){
            selectedBall->direction = 1;
        } else if(canplayermove((selectedBall->x-8), selectedBall->y)){
            selectedBall->direction = 2;
        }else if(canplayermove((selectedBall->x-8), (selectedBall->y+8))){
            selectedBall->direction = 3;
        }
    } else if(selectedBall->direction == 7 && !canplayermove((selectedBall->x+8), (selectedBall->y-8))){
        resultSorteio=sortearUmValor();
        if(resultSorteio==1 && canplayermove((selectedBall->x+8), (selectedBall->y+8))){
            selectedBall->direction = 5;
        }else if(resultSorteio==2 && canplayermove((selectedBall->x+8), selectedBall->y)){
            selectedBall->direction = 6;
        } else if(canplayermove((selectedBall->x+8), (selectedBall->y+8))){
            selectedBall->direction = 5;
        }else if(canplayermove((selectedBall->x+8), selectedBall->y)){
            selectedBall->direction = 6;
        }else if(canplayermove((selectedBall->x-8), selectedBall->y)){
            selectedBall->direction = 2;
        }
    }

    if(selectedBall->direction == 0){
        selectedBall->y -= 8;
    } else if(selectedBall->direction == 1){
        selectedBall->x -= 8;
        selectedBall->y -= 8;
    } else if(selectedBall->direction == 2){
        selectedBall->x -= 8;
    } else if(selectedBall->direction == 3){
        selectedBall->x -= 8;
        selectedBall->y += 8;
    } else if(selectedBall->direction == 4){
        selectedBall->y += 8;
    } else if(selectedBall->direction == 5){
        selectedBall->x += 8;
        selectedBall->y += 8;
    } else if(selectedBall->direction == 6){
        selectedBall->x += 8;
    } else if(selectedBall->direction == 7){
        selectedBall->x += 8;
        selectedBall->y -= 8;
    }

    move_sprite(selectedBall->spritid, selectedBall->x, selectedBall->y);
}

void moveBarraRight(BarraGame* selectedBarra){
    if(!(canplayermove(selectedBarra->x[0], selectedBarra->y[0]-8) && canplayermove(selectedBarra->x[1], selectedBarra->y[1]-8) && canplayermove(selectedBarra->x[2], selectedBarra->y[2]-8))){
        transitionBarraRight=1; // Serve para identificar se a barra direita tem que continuar subindo ou descendo.
    }
    if(!(canplayermove(selectedBarra->x[0], selectedBarra->y[0]+8) && canplayermove(selectedBarra->x[1], selectedBarra->y[1]+8) && canplayermove(selectedBarra->x[2], selectedBarra->y[2]+8))){
        transitionBarraRight=0;
    }
    if(transitionBarraRight==0){
        for(UINT16 x=0; x<3; x++){
            selectedBarra->y[x]-=8;
            move_sprite(x+4,selectedBarra->x[x],selectedBarra->y[x]);
        }
    }
    if(transitionBarraRight==1){
        for(UINT16 x=0; x<3; x++){
            selectedBarra->y[x]+=8;
            move_sprite(x+4,selectedBarra->x[x],selectedBarra->y[x]);
        }
    }
}

void main(){

    SPRITES_8x8;
    BarraGame barraEsq, barraDir;
    barraDir.spritid[0] = 4; barraDir.spritid[1] = 5; barraDir.spritid[2] = 6;
    barraDir.x[0] = 152; barraDir.x[1] = 152; barraDir.x[2] = 152;
    barraDir.y[0] = 136; barraDir.y[1] = 128; barraDir.y[2] = 120;
    barraDir.width = 8; barraDir.height = 8;

    barraEsq.spritid[0] = 1; barraEsq.spritid[1] = 2; barraEsq.spritid[2] = 3;
    barraEsq.x[0] = 16; barraEsq.x[1] = 16; barraEsq.x[2] = 16;
    barraEsq.y[0] = 32; barraEsq.y[1] = 40; barraEsq.y[2] = 48;
    barraEsq.width = 8; barraEsq.height = 8;

    Ball ballOne, ballTwo;
    ballOne.spritid = 0;
    ballOne.x = 48; ballOne.y = 24;
    ballOne.width = 8; ballOne.height = 8;
    ballOne.direction = 2;

    ballTwo.spritid = 7;
    ballTwo.x = 120; ballTwo.y = 64;
    ballTwo.width = 8; ballTwo.height = 8;
    ballTwo.direction = 6;
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
			if(canplayermove(barraEsq.x[0], barraEsq.y[0]-8) && canplayermove(barraEsq.x[1], barraEsq.y[1]-8) && canplayermove(barraEsq.x[2], barraEsq.y[2]-8)){
                for(UINT16 x=0; x<3; x++){
                    barraEsq.y[x]-=8;
			        move_sprite(x+1,barraEsq.x[x],barraEsq.y[x]);
                }
            }
		}
		else if (joypad() & J_DOWN)
		{ 
			if(canplayermove(barraEsq.x[0], barraEsq.y[0]+8) && canplayermove(barraEsq.x[1], barraEsq.y[1]+8) && canplayermove(barraEsq.x[2], barraEsq.y[2]+8)){
                for(UINT16 x=0; x<3; x++){
                    barraEsq.y[x]+=8;
			        move_sprite(x+1,barraEsq.x[x],barraEsq.y[x]);
                }
            }
		}

        moveBarraRight(&barraDir);

        moveBola(&ballOne);

        moveBola(&ballTwo);

        for(UINT16 i=0; i<6; i++){
		    wait_vbl_done();
        }
	}
}