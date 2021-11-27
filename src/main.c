#include <gb/gb.h>
#include <stdio.h>
#include "..\assets\barra.c"
#include "..\assets\bola.c"
#include "..\assets\parede.c"

void main(){
    UINT8 currentspriteindex = 0;
    UINT8 limiteVerSup=80, limiteVerInf=-80;

    SPRITES_8x8;
    /* set_sprite_data: (Tile de início, a quantidade de tiles do arquivo que vai carregar, data)
     * set_sprite_tile: (Um valor que você quer atribuir ao sprite, tile que voce definiu no set_sprite_data)
     * mov_sprite: move
     * Limites: Horizontal: De 8 em 8 até 20*8 e vertical de 16 em 8 até 18*8+8
    */
    set_sprite_data(0, 1, Barra);
    set_sprite_tile(3, 0);
    move_sprite(3, 0, 0);

    set_sprite_data(1, 1, Bola);
    set_sprite_tile(1, 1);
    move_sprite(1, 88, 16);

    set_sprite_data(2, 1, Parede);
    set_sprite_tile(2, 2);
    move_sprite(2, 20*4,144+8);

    SHOW_SPRITES;

    /*while(1){
        if(currentspriteindex==0){
            currentspriteindex = 1;
        }
        else{
            currentspriteindex = 0;
        }
        set_sprite_tile(0, currentspriteindex);
        switch(joypad()){
            case J_UP:
                scroll_sprite(0,0,-10);
                break;
            case J_DOWN:
                scroll_sprite(0,0,10);
                break;
        }


        delay(100);
        scroll_sprite(0,10,0);
    }*/
}