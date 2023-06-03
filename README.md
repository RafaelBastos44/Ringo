# RINGO - MAT1303/MAT2461

## Objetivo
Esse jogo de tabuleiro foi o primeiro trabalho de MAT1303/MAT2461, Elementos Matemáticos de Computação Gráfica na PUC-Rio.
O objetivo foi recriar um jogo de tabuleiro sorteado em C++, utilizando a biblioteca gráfica OpenGL, a partir da API freeGLUT.

## Requerimentos
- C++
- freeGLUT

## Instruções
Para mover as peças, o jogador do turno deve clicar na peça uma vez, e então na casa desejada.
A peça só pode ser movida para casas permitidas, ou seja, sem movimentos nas diagonais ou em casas distantes.

As peças atacantes só podem se mover uma casa para os lados e na direção do castelo, menos nas diagonais.
As peças defensoras podem se mover uma casa em qualquer direção, menos nas diagonais.
As peças defensoras não podem pisar na casa central.

O mesmo vale para a captura de peças. O jogador deve clicar no lugar onde a peça estaria após a captura, e a peça a ser capturada será removida do tabuleiro.
A captura não pode ocorrer nas casas do setor neutro.
O defensor pode capturar um atacante na casa central.

O atacante vence ao colocar duas peças na casa central, ou ao capturar todos os defensores.
O defensor vence apenas ao reduzir o número de peças do atacante a 1.

Para compilar o código, utilize o comando a seguir:
g++ ringo.cpp -lglut -lGL -lGLU
