#include <gb/gb.h>
#include <stdio.h>
#include "..\assets\barra.c"
#include "..\assets\bola.c"
#include "..\assets\parede.c"
#include "..\assets-test\testeback.c"
#include "..\assets-test\testeback2.c"
#include "..\assets-test\mapteste.c"
#include "..\assets-test\mapteste2.c"
#include "..\assets-test\mapteste3.c"

void main(){
    UINT8 currentspriteindex = 0;

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

    set_bkg_data(0, 21, BackTeste2); // Load os sprites que compõem o background na memória
    set_bkg_tiles(0, 0, 20, 18, MapTeste3);

    SHOW_BKG;
    DISPLAY_ON;
    
    delay(100);
    set_bkg_data(0, 3, BackTest); // Load os sprites que compõem o background na memória
    set_bkg_tiles(0, 0, 20, 18, MapTeste2);

    /*
    while(1){
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