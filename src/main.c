#include <gb/gb.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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

UINT16 positionBall[] = {48,24};
UINT16 positionBallTwo[] = {64,112};
UINT16 positionBarraRightX[] = {152,152,152};
UINT16 positionBarraRightY[] = {136,128,120};
UINT16 transitionBarraRight = 0;
UINT16 directionBallOne = 0;
UINT16 directionBallTwo = 4;

UINT16 sortearUmValor(){
    UINT16 srand = positionBall[0] + positionBall[1] + positionBallTwo[0] + positionBallTwo[1] + positionBarraRightX[0] + positionBarraRightX[1] + positionBarraRightX[2] + positionBarraRightY[0] + positionBarraRightY[1] + positionBarraRightY[2] + transitionBarraRight + directionBallOne + directionBallTwo;
    return srand % 3;
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

void moveBolaUm(){
    UINT16 resultSorteio=sortearUmValor();

    if(directionBallOne == 0 && !canplayermove(positionBall[0], (positionBall[1]-8))){
        resultSorteio=sortearUmValor();
        if(resultSorteio==0 && canplayermove((positionBall[0]-8), (positionBall[1]+8))){
            directionBallOne = 3;
        } else if(resultSorteio==1 && canplayermove(positionBall[0], (positionBall[1]+8))){
            directionBallOne = 4;
        }else if(resultSorteio==2 && canplayermove((positionBall[0]+8), (positionBall[1]+8))){
            directionBallOne = 5;
        }
        if(canplayermove((positionBall[0]-8), (positionBall[1]+8))){
            directionBallOne = 3;
        } else if(canplayermove(positionBall[0], (positionBall[1]+8))){
            directionBallOne = 4;
        }else if(canplayermove((positionBall[0]+8), (positionBall[1]+8))){
            directionBallOne = 5;
        }
    } else if(directionBallOne == 1 && !canplayermove((positionBall[0]-8), (positionBall[1]-8))){
        resultSorteio=sortearUmValor();
        if(resultSorteio==0 && canplayermove((positionBall[0]-8), positionBall[1])){
            directionBallOne = 2;
        } else if(resultSorteio==1 && canplayermove((positionBall[0]-8), (positionBall[1]+8))){
            directionBallOne = 3;
        }else if(resultSorteio==2 && canplayermove(positionBall[0], (positionBall[1]+8))){
            directionBallOne = 4;
        }
        if(canplayermove((positionBall[0]-8), positionBall[1])){
            directionBallOne = 2;
        } else if(canplayermove((positionBall[0]-8), (positionBall[1]+8))){
            directionBallOne = 3;
        }else if(canplayermove(positionBall[0], (positionBall[1]+8))){
            directionBallOne = 4;
        }
    } else if(directionBallOne == 2 && !canplayermove((positionBall[0]-8), positionBall[1])){
        resultSorteio=sortearUmValor();
        if(resultSorteio==0 && canplayermove((positionBall[0]+8), (positionBall[1]+8))){
            directionBallOne = 5;
        } else if(resultSorteio==1 && canplayermove((positionBall[0]+8), positionBall[1])){
            directionBallOne = 6;
        }else if(resultSorteio==2 && canplayermove((positionBall[0]+8), (positionBall[1]-8))){
            directionBallOne = 7;
        }
        if(canplayermove((positionBall[0]+8), (positionBall[1]+8))){
            directionBallOne = 5;
        } else if(canplayermove((positionBall[0]+8), positionBall[1])){
            directionBallOne = 6;
        }else if(canplayermove((positionBall[0]+8), (positionBall[1]-8))){
            directionBallOne = 7;
        }
    } else if(directionBallOne == 3 && !canplayermove((positionBall[0]-8), (positionBall[1]+8))){
        resultSorteio=sortearUmValor();
        if(resultSorteio==0 && canplayermove((positionBall[0]-8), positionBall[1])){
            directionBallOne = 2;
        } else if(resultSorteio==1 && canplayermove((positionBall[0]-8), (positionBall[1]-8))){
            directionBallOne = 1;
        }else if(resultSorteio==2 && canplayermove(positionBall[0], (positionBall[1]-8))){
            directionBallOne = 0;
        }
        if(canplayermove((positionBall[0]-8), positionBall[1])){
            directionBallOne = 2;
        } else if(canplayermove((positionBall[0]-8), (positionBall[1]-8))){
            directionBallOne = 1;
        }else if(canplayermove(positionBall[0], (positionBall[1]-8))){
            directionBallOne = 0;
        }
    } else if(directionBallOne == 4 && !canplayermove(positionBall[0], (positionBall[1]+8))){
        resultSorteio=sortearUmValor();
        if(resultSorteio==0 && canplayermove((positionBall[0]+8), (positionBall[1]-8))){
            directionBallOne = 7;
        } else if(resultSorteio==1 && canplayermove(positionBall[0], (positionBall[1]-8))){
            directionBallOne = 0;
        }else if(resultSorteio==2 && canplayermove((positionBall[0]-8), (positionBall[1]-8))){
            directionBallOne = 1;
        }
        if(canplayermove((positionBall[0]+8), (positionBall[1]-8))){
            directionBallOne = 7;
        } else if(canplayermove(positionBall[0], (positionBall[1]-8))){
            directionBallOne = 0;
        }else if(canplayermove((positionBall[0]-8), (positionBall[1]-8))){
            directionBallOne = 1;
        }
    } else if(directionBallOne == 5 && !canplayermove((positionBall[0]+8), (positionBall[1]+8))){
        resultSorteio=sortearUmValor();
        if(resultSorteio==0 && canplayermove(positionBall[0], (positionBall[1]-8))){
            directionBallOne = 0;
        } else if(resultSorteio==1 && canplayermove((positionBall[0]+8), (positionBall[1]-8))){
            directionBallOne = 7;
        }else if(resultSorteio==2 && canplayermove((positionBall[0]+8), positionBall[1])){
            directionBallOne = 6;
        }
        if(canplayermove(positionBall[0], (positionBall[1]-8))){
            directionBallOne = 0;
        } else if(canplayermove((positionBall[0]+8), (positionBall[1]-8))){
            directionBallOne = 7;
        }else if(canplayermove((positionBall[0]+8), positionBall[1])){
            directionBallOne = 6;
        }
    } else if(directionBallOne == 6 && !canplayermove((positionBall[0]+8), positionBall[1])){
        resultSorteio=sortearUmValor();
        if(resultSorteio==0 && canplayermove((positionBall[0]-8), (positionBall[1]-8))){
            directionBallOne = 1;
        } else if(resultSorteio==1 && canplayermove((positionBall[0]-8), positionBall[1])){
            directionBallOne = 2;
        }else if(resultSorteio==2 && canplayermove((positionBall[0]-8), (positionBall[1]+8))){
            directionBallOne = 3;
        }
        if(canplayermove((positionBall[0]-8), (positionBall[1]-8))){
            directionBallOne = 1;
        } else if(canplayermove((positionBall[0]-8), positionBall[1])){
            directionBallOne = 2;
        }else if(canplayermove((positionBall[0]-8), (positionBall[1]+8))){
            directionBallOne = 3;
        }
    } else if(directionBallOne == 7 && !canplayermove((positionBall[0]+8), (positionBall[1]-8))){
        resultSorteio=sortearUmValor();
        if(resultSorteio==0 && canplayermove(positionBall[0], (positionBall[1]+8))){
            directionBallOne = 4;
        } else if(resultSorteio==1 && canplayermove((positionBall[0]+8), (positionBall[1]+8))){
            directionBallOne = 5;
        }else if(resultSorteio==2 && canplayermove((positionBall[0]+8), positionBall[1])){
            directionBallOne = 6;
        }
        if(canplayermove(positionBall[0], (positionBall[1]+8))){
            directionBallOne = 4;
        } else if(canplayermove((positionBall[0]+8), (positionBall[1]+8))){
            directionBallOne = 5;
        }else if(canplayermove((positionBall[0]+8), positionBall[1])){
            directionBallOne = 6;
        }
    }

    if(directionBallOne == 0){
        positionBall[1] -= 8;
    } else if(directionBallOne == 1){
        positionBall[0] -= 8;
        positionBall[1] -= 8;
    } else if(directionBallOne == 2){
        positionBall[0] -= 8;
    } else if(directionBallOne == 3){
        positionBall[0] -= 8;
        positionBall[1] += 8;
    } else if(directionBallOne == 4){
        positionBall[1] += 8;
    } else if(directionBallOne == 5){
        positionBall[0] += 8;
        positionBall[1] += 8;
    } else if(directionBallOne == 6){
        positionBall[0] += 8;
    } else if(directionBallOne == 7){
        positionBall[0] += 8;
        positionBall[1] -= 8;
    }

    move_sprite(0, positionBall[0], positionBall[1]);
}

void moveBolaDois(){
    UINT16 resultSorteio=sortearUmValor();

    if(directionBallTwo == 0 && !canplayermove(positionBallTwo[0], (positionBallTwo[1]-8))){
        resultSorteio=sortearUmValor();
        if(resultSorteio==0 && canplayermove((positionBallTwo[0]-8), (positionBallTwo[1]+8))){
            directionBallTwo = 3;
        } else if(resultSorteio==1 && canplayermove(positionBallTwo[0], (positionBallTwo[1]+8))){
            directionBallTwo = 4;
        }else if(resultSorteio==2 && canplayermove((positionBallTwo[0]+8), (positionBallTwo[1]+8))){
            directionBallTwo = 5;
        }
        if(canplayermove((positionBallTwo[0]-8), (positionBallTwo[1]+8))){
            directionBallTwo = 3;
        } else if(canplayermove(positionBallTwo[0], (positionBallTwo[1]+8))){
            directionBallTwo = 4;
        }else if(canplayermove((positionBallTwo[0]+8), (positionBallTwo[1]+8))){
            directionBallTwo = 5;
        }
    } else if(directionBallTwo == 1 && !canplayermove((positionBallTwo[0]-8), (positionBallTwo[1]-8))){
        resultSorteio=sortearUmValor();
        if(resultSorteio==0 && canplayermove((positionBallTwo[0]-8), positionBallTwo[1])){
            directionBallTwo = 2;
        } else if(resultSorteio==1 && canplayermove((positionBallTwo[0]-8), (positionBallTwo[1]+8))){
            directionBallTwo = 3;
        }else if(resultSorteio==2 && canplayermove(positionBallTwo[0], (positionBallTwo[1]+8))){
            directionBallTwo = 4;
        }
        if(canplayermove((positionBallTwo[0]-8), positionBallTwo[1])){
            directionBallTwo = 2;
        } else if(canplayermove((positionBallTwo[0]-8), (positionBallTwo[1]+8))){
            directionBallTwo = 3;
        }else if(canplayermove(positionBallTwo[0], (positionBallTwo[1]+8))){
            directionBallTwo = 4;
        }
    } else if(directionBallTwo == 2 && !canplayermove((positionBallTwo[0]-8), positionBallTwo[1])){
        resultSorteio=sortearUmValor();
        if(resultSorteio==0 && canplayermove((positionBallTwo[0]+8), (positionBallTwo[1]+8))){
            directionBallTwo = 5;
        } else if(resultSorteio==1 && canplayermove((positionBallTwo[0]+8), positionBallTwo[1])){
            directionBallTwo = 6;
        }else if(resultSorteio==2 && canplayermove((positionBallTwo[0]+8), (positionBallTwo[1]-8))){
            directionBallTwo = 7;
        }
        if(canplayermove((positionBallTwo[0]+8), (positionBallTwo[1]+8))){
            directionBallTwo = 5;
        } else if(canplayermove((positionBallTwo[0]+8), positionBallTwo[1])){
            directionBallTwo = 6;
        }else if(canplayermove((positionBallTwo[0]+8), (positionBallTwo[1]-8))){
            directionBallTwo = 7;
        }
    } else if(directionBallTwo == 3 && !canplayermove((positionBallTwo[0]-8), (positionBallTwo[1]+8))){
        resultSorteio=sortearUmValor();
        if(resultSorteio==0 && canplayermove((positionBallTwo[0]-8), positionBallTwo[1])){
            directionBallTwo = 2;
        } else if(resultSorteio==1 && canplayermove((positionBallTwo[0]-8), (positionBallTwo[1]-8))){
            directionBallTwo = 1;
        }else if(resultSorteio==2 && canplayermove(positionBallTwo[0], (positionBallTwo[1]-8))){
            directionBallTwo = 0;
        }
        if(canplayermove((positionBallTwo[0]-8), positionBallTwo[1])){
            directionBallTwo = 2;
        } else if(canplayermove((positionBallTwo[0]-8), (positionBallTwo[1]-8))){
            directionBallTwo = 1;
        }else if(canplayermove(positionBallTwo[0], (positionBallTwo[1]-8))){
            directionBallTwo = 0;
        }
    } else if(directionBallTwo == 4 && !canplayermove(positionBallTwo[0], (positionBallTwo[1]+8))){
        resultSorteio=sortearUmValor();
        if(resultSorteio==0 && canplayermove((positionBallTwo[0]+8), (positionBallTwo[1]-8))){
            directionBallTwo = 7;
        } else if(resultSorteio==1 && canplayermove(positionBallTwo[0], (positionBallTwo[1]-8))){
            directionBallTwo = 0;
        }else if(resultSorteio==2 && canplayermove((positionBallTwo[0]-8), (positionBallTwo[1]-8))){
            directionBallTwo = 1;
        }
        if(canplayermove((positionBallTwo[0]+8), (positionBallTwo[1]-8))){
            directionBallTwo = 7;
        } else if(canplayermove(positionBallTwo[0], (positionBallTwo[1]-8))){
            directionBallTwo = 0;
        }else if(canplayermove((positionBallTwo[0]-8), (positionBallTwo[1]-8))){
            directionBallTwo = 1;
        }
    } else if(directionBallTwo == 5 && !canplayermove((positionBallTwo[0]+8), (positionBallTwo[1]+8))){
        resultSorteio=sortearUmValor();
        if(resultSorteio==0 && canplayermove(positionBallTwo[0], (positionBallTwo[1]-8))){
            directionBallTwo = 0;
        } else if(resultSorteio==1 && canplayermove((positionBallTwo[0]+8), (positionBallTwo[1]-8))){
            directionBallTwo = 7;
        }else if(resultSorteio==2 && canplayermove((positionBallTwo[0]+8), positionBallTwo[1])){
            directionBallTwo = 6;
        }
        if(canplayermove(positionBallTwo[0], (positionBallTwo[1]-8))){
            directionBallTwo = 0;
        } else if(canplayermove((positionBallTwo[0]+8), (positionBallTwo[1]-8))){
            directionBallTwo = 7;
        }else if(canplayermove((positionBallTwo[0]+8), positionBallTwo[1])){
            directionBallTwo = 6;
        }
    } else if(directionBallTwo == 6 && !canplayermove((positionBallTwo[0]+8), positionBallTwo[1])){
        resultSorteio=sortearUmValor();
        if(resultSorteio==0 && canplayermove((positionBallTwo[0]-8), (positionBallTwo[1]-8))){
            directionBallTwo = 1;
        } else if(resultSorteio==1 && canplayermove((positionBallTwo[0]-8), positionBallTwo[1])){
            directionBallTwo = 2;
        }else if(resultSorteio==2 && canplayermove((positionBallTwo[0]-8), (positionBallTwo[1]+8))){
            directionBallTwo = 3;
        }
        if(canplayermove((positionBallTwo[0]-8), (positionBallTwo[1]-8))){
            directionBallTwo = 1;
        } else if(canplayermove((positionBallTwo[0]-8), positionBallTwo[1])){
            directionBallTwo = 2;
        }else if(canplayermove((positionBallTwo[0]-8), (positionBallTwo[1]+8))){
            directionBallTwo = 3;
        }
    } else if(directionBallTwo == 7 && !canplayermove((positionBallTwo[0]+8), (positionBallTwo[1]-8))){
        resultSorteio=sortearUmValor();
        if(resultSorteio==0 && canplayermove(positionBallTwo[0], (positionBallTwo[1]+8))){
            directionBallTwo = 4;
        } else if(resultSorteio==1 && canplayermove((positionBallTwo[0]+8), (positionBallTwo[1]+8))){
            directionBallTwo = 5;
        }else if(resultSorteio==2 && canplayermove((positionBallTwo[0]+8), positionBallTwo[1])){
            directionBallTwo = 6;
        }
        if(canplayermove(positionBallTwo[0], (positionBallTwo[1]+8))){
            directionBallTwo = 4;
        } else if(canplayermove((positionBallTwo[0]+8), (positionBallTwo[1]+8))){
            directionBallTwo = 5;
        }else if(canplayermove((positionBallTwo[0]+8), positionBallTwo[1])){
            directionBallTwo = 6;
        }
    }

    if(directionBallTwo == 0){
        positionBallTwo[1] -= 8;
    } else if(directionBallTwo == 1){
        positionBallTwo[0] -= 8;
        positionBallTwo[1] -= 8;
    } else if(directionBallTwo == 2){
        positionBallTwo[0] -= 8;
    } else if(directionBallTwo == 3){
        positionBallTwo[0] -= 8;
        positionBallTwo[1] += 8;
    } else if(directionBallTwo == 4){
        positionBallTwo[1] += 8;
    } else if(directionBallTwo == 5){
        positionBallTwo[0] += 8;
        positionBallTwo[1] += 8;
    } else if(directionBallTwo == 6){
        positionBallTwo[0] += 8;
    } else if(directionBallTwo == 7){
        positionBallTwo[0] += 8;
        positionBallTwo[1] -= 8;
    }

    move_sprite(7, positionBallTwo[0], positionBallTwo[1]);
}

void moveBarraRight(){
    if(!(canplayermove(positionBarraRightX[0], positionBarraRightY[0]-8) && canplayermove(positionBarraRightX[1], positionBarraRightY[1]-8) && canplayermove(positionBarraRightX[2], positionBarraRightY[2]-8))){
        transitionBarraRight=1;
    }
    if(!(canplayermove(positionBarraRightX[0], positionBarraRightY[0]+8) && canplayermove(positionBarraRightX[1], positionBarraRightY[1]+8) && canplayermove(positionBarraRightX[2], positionBarraRightY[2]+8))){
        transitionBarraRight=0;
    }
    if(transitionBarraRight==0){
        for(UINT16 x=0; x<3; x++){
            positionBarraRightY[x]-=8;
            move_sprite(x+4,positionBarraRightX[x],positionBarraRightY[x]);
        }
    }
    if(transitionBarraRight==1){
        for(UINT16 x=0; x<3; x++){
            positionBarraRightY[x]+=8;
            move_sprite(x+4,positionBarraRightX[x],positionBarraRightY[x]);
        }
    }
}


void main(){

    SPRITES_8x8;
    /* set_sprite_data: (Tile de início, a quantidade de tiles do arquivo que vai carregar, data)
     * Tile de início é a posição do VRAM do gamebou onde ele vai começar, todos os outros tiles vao ser colocados a partir dele.
     * set_sprite_tile: (Um valor que você quer atribuir ao sprite, tile que voce definiu no set_sprite_data)
     * mov_sprite: move
     * set_bkg_data(Tile de inicio (Esse vai ser o da tela do gameboy em si), quantidade de tiles 
     *  necessárias para o background, a função asset dos tiles)
     * set_bkg_tiles(X inicial, y incial, x final, y final, mapa)
     * Limites: Horizontal: De 8 em 8 até 20*8 e vertical de 16 em 8 até 18*8+8
    */

    /*set_sprite_data(0, 1, Barra);
    set_sprite_tile(3, 0);
    move_sprite(3, 0, 0);

    set_sprite_data(1, 1, Bola);
    set_sprite_tile(1, 1);
    move_sprite(1, 88, 16);

    set_sprite_data(2, 1, Parede);
    set_sprite_tile(2, 2);
    move_sprite(2, 20*4,144+8);

    SHOW_SPRITES;*/

    set_bkg_data(0, 21, BackTeste2); // Load os sprites que compõem o background na memória
    set_bkg_tiles(0, 0, 20, 18, MapTeste3);
    SHOW_BKG;

    while(joypad()!=J_START){}

    set_bkg_data(0, 7, LinhaDaQuadra);
    set_bkg_tiles(0, 0, 20, 18, BackgroundPong);

    UINT16 positionBarraLeftX[] = {16,16,16};
    UINT16 positionBarraLeftY[] = {32,40,48};

    // Bola Um
	set_sprite_data(0, 1, Bola);
    // Barra Esquerda
    set_sprite_data(1, 1, Barra);
    set_sprite_data(2, 1, Barra);
    set_sprite_data(3, 1, Barra);
    // Barra Direita
    set_sprite_data(4, 1, Barra);
    set_sprite_data(5, 1, Barra);
    set_sprite_data(6, 1, Barra);
    // Bola Dois
	set_sprite_data(7, 1, Bola);

    // Meio que serve para associar o desenho do tile que está na VRAM com a referência que vamos usar para manipular o tile no código.
	set_sprite_tile(0, 0); // primeiro valor é a referência (Nb) definida para o dado através do primeiro campo do sprite_data, e o segundo valor é o indice do desenho do tile na VRAM.
    set_sprite_tile(1, 1);
    set_sprite_tile(2, 2);
    set_sprite_tile(3, 3);
    set_sprite_tile(4, 4);
    set_sprite_tile(5, 5);
    set_sprite_tile(6, 6);
    set_sprite_tile(7, 7);

	move_sprite(0, positionBall[0], positionBall[1]);
	move_sprite(1, positionBarraLeftX[0], positionBarraLeftY[0]);
    move_sprite(2, positionBarraLeftX[1], positionBarraLeftY[1]);
    move_sprite(3, positionBarraLeftX[2], positionBarraLeftY[2]);
    move_sprite(4, positionBarraRightX[0], positionBarraRightY[0]);
    move_sprite(5, positionBarraRightX[1], positionBarraRightY[1]);
    move_sprite(6, positionBarraRightX[2], positionBarraRightY[2]);
    move_sprite(7, positionBallTwo[0], positionBallTwo[1]);


	SHOW_SPRITES;
    SHOW_BKG;
    DISPLAY_ON;

	while(1){
		if (joypad() & J_UP)
		{ 
			if(canplayermove(positionBarraLeftX[0], positionBarraLeftY[0]-8) && canplayermove(positionBarraLeftX[1], positionBarraLeftY[1]-8) && canplayermove(positionBarraLeftX[2], positionBarraLeftY[2]-8)){
                for(UINT16 x=0; x<3; x++){
                    positionBarraLeftY[x]-=8;
			        move_sprite(x+1,positionBarraLeftX[x],positionBarraLeftY[x]);
                }
            }
		}
		else if (joypad() & J_DOWN)
		{ 
			if(canplayermove(positionBarraLeftX[0], positionBarraLeftY[0]+8) && canplayermove(positionBarraLeftX[1], positionBarraLeftY[1]+8) && canplayermove(positionBarraLeftX[2], positionBarraLeftY[2]+8)){
                for(UINT16 x=0; x<3; x++){
                    positionBarraLeftY[x]+=8;
			        move_sprite(x+1,positionBarraLeftX[x],positionBarraLeftY[x]);
                }
            }
		}

        moveBarraRight();

        moveBolaUm();

        moveBolaDois();

        for(UINT16 i=0; i<6; i++){
		    wait_vbl_done();
        }
	}
}