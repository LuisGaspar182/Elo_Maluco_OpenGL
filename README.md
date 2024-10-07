// Instale as seguintes bibliotecas:
//sudo apt-get install cmake build-essential libgl1-mesa-dev freeglut3 libglm-dev libsoil-dev

// Para compilar execute no terminal:
// g++ -o ELOMALUCO Elo_maluco.cpp -lglut -lGLU -lGL -lm -lSOIL
// ./ELOMALUCO


// --------------------------------------------------------

// Ordem das texturas:
// 0 - vms (vermelho superior)
// 1 - brs (branco superior)
// 2 - vrs (verde superior)
// 3 - ams (amarelo superior)
// 4 - vmm (vermelho meio)
// 5 - brm (branco meio)
// 6 - vrm (verde meio)
// 7 - amm (amarelo meio)
// 8 - vmi (vermelho inferior)
// 9 - bri (branco inferior)
// 10 - vri (verde inferior)
// 11 - ami (amarelo inferior)
// 20 - vzo (vazio)

// --------------------------------------------------------

// Rotacionar cubo:
// 'd' ou 'D' - rotaciona 90 graus no sentido horário
// 'a' ou 'A' - rotaciona 90 graus no sentido anti-horário


// Mover o espaço vazio:
// ' ' (tecla de espaço) - move o espaço vazio para baixo
// 'c' ou 'C' - move o espaço vazio para cima

// O espaço vazio é representado pela textura 20 (vzo). 
// Ao pressionar espaço, o vazio troca de posição com a textura abaixo dele.
// Ao pressionar 'C', o vazio troca de posição com a textura acima dele.

// Essas teclas permitem manipular a posição do espaço vazio no quebra-cabeça,
// facilitando a reorganização das peças para resolver o desafio.

