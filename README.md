# Trabalho Prático - Computação Gráfica 2016

## PokeThief
Esse projeto é um jogo desenvolvido em **C++** como trabalho prático para a disciplina de Computação Gráfica no CEFET-MG, baseado em outro jogo, o **GORILLAS.BAS** feito em **BASIC**.

![alt Demo](https://raw.githubusercontent.com/caiubi/PokeThief/master/ImageResources/Demo.png)

### Instalação e execução

PokeThief requer as seguintes bibliotecas para ser compilado e executado:
* GLFW **v3.2.1** (baixe [aqui](http://www.glfw.org/download.html))
* SOIL **v1.16** (baixe [aqui](http://www.lonesock.net/soil.html))

Para instalar e configurar essas bibliotecas automaticamente (Linux apenas), utilize os seguintes comandos:

Linux:
```sh
$ cd <diretorio-raiz-pokethief>
$ make setup
```

Para compilar e executar o programa:

MacOS e Linux:
```sh
$ cd <diretorio-raiz-pokethief>
$ make
```

Para limpar os executaveis e arquivos objetos existentes:
```sh
$ cd <diretorio-raiz-pokethief>
$ make clean
```

### Como jogar:
Utilize as setas **para cima** e **para baixo** para mover a mira do jogador.
Utilize as setas **esquerda** e **direita** para mover a posição do jogador.
Com a tecla **space** o jogador pode controlar a intensidade do impulso a ser deferido no projétil.
A partir de qualquer tela as teclas r ou esq podem ser pressionadas para reiniciar ou finalizar o jogo respectivamente.

#### Em breve:
* Como instalar as dependências em MacOS
