# Projeto Pong Souls

Projeto para a 3 avaliação da disciplina **Interface de Hardware e Software**, do curso de Engenharia da Computação da Universiade Federal de Sergipe.

# Funcionamento do Jogo

O jogo é uma uma fusão do jogo breakout com o jogo pong com multiplayer local suportando a conexão de dois players. 
Os dois players, representado por duas barras verticais, tem que destruir os obstáculos para conseguir marcar pontos e consequentemente vencer o jogo. O ponto é marcado quando alguma das duas bolas atingir os extremos horizontais da tela, sendo o extremo esquerdo contando como ponto para barra direita e o extremo direito contando como ponto para barra esquerda.
O jogo termina quando algum dos players marcarem 8 pontos.

# Vídeo de apresentação
Link: https://www.youtube.com/watch?v=ajt4nx_Inkg
[![Watch the video](https://imgur.com/mcH2Q9l.png)](https://www.youtube.com/watch?v=ajt4nx_Inkg)

# Ferramentas utilizadas

- O jogo foi programado utilizando a linguagem C.
- O **GameBoy Development Kit** (GBDK) foi a biblioteca de ferramentas utilizada na construção da rom do jogo.
- O **GameBoy Tile Design** (GBTD) foi utilizado na criação dos tiles do gameboy.
- O **GameBoy Map Builder** (GBMB) foi utilizado na criação do mapa do jogo.
- O **GitHub** foi utilziado para o versionamento do código.
- O emulador de gameboy **BGB**.

# Controles de Jogo

- A tecla **A** e **S** vão representar a tecla START do jogo. Sendo A para o player 1 e S para o player 2.
- **Seta pra cima** e **Seta para baixo** comanda as barras do jogo.

# Como Jogar

1. Clone o repositório.
2. Execute o make.bat dentro da pasta src, isso irá criar uma pasta **build** com o rom do jogo.
3. Entre na pasta BGB Emulador e execute duas telas do emulador bgb64.exe.                                                                                                        ![Ambos os emuladores rodando](https://i.imgur.com/4g02LHY.png)
4. Em ambas as telas, clique com o botão direito do mouse e selecione Load Rom... e escolha o arquivo main.gb criado na pasta **build** deste repositório.                        ![Load ROM](https://i.imgur.com/FoSFOon.png)                       
5. Escolha uma das telas e clique com o botão direito nela, vá em link -> listen, e coloque a porta **8765**.                                                                      ![Listen](https://i.imgur.com/OH638vg.png)                                                                                                                                      ![Porta 8765](https://imgur.com/sQD9Ykj.png) 
6. Na outra tela, faça o mesmo procedimento porém agora siga o caminho link -> connect e coloque o ip e a porta **127.0.0.1:8765**.<br/>                                                ![Connect](https://imgur.com/Qj5fgnR.png)                                                                                                                                        ![Ip/Porta](https://imgur.com/gvbz84K.png)                                              
8. Permita a conexão local caso o firewall emita um aviso.
9. Aperte A na primeira tela escolhida e S na segunda tela, assim o jogo irá começar.                                                                                            ![Jogo rodando](https://imgur.com/mcH2Q9l.png)
