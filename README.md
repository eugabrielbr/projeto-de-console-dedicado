<h1>
  <p align="center">Tic-Tac-Toe</p>
</h1>


<h2>
  <p align="center">Jogo da velha (tic-tac-toe) desenvolvido para o kit de desenvolvimento DE1-SoC utilizando a linguagem C</p>
  
</h2>

<h3>
  <h2>Sobre o projeto</h2>
  <p>
    O mercado de jogos digitais é uma indústria em constante evolução, movimentando bilhões de dólares anualmente e desempenhando um papel significativo na  economia global. Enquanto os jogos de última geração continuam a oferecer experiências imersivas e inovadoras, uma tendência nostálgica em direção aos jogos clássicos também tem se manifestado. O jogo da velha, um exemplo emblemático de jogo clássico, permanece popular devido à sua simplicidade e jogabilidade intemporal, atraindo jogadores de todas as idades.
  </p>
  <p>
  Diante desse cenário, foi proposto o desenvolvimento de um console que implementa uma versão do jogo da velha. Este console deve operar em uma interface de modo texto, acessível via terminal, e permitir a interação de dois jogadores. A escolha das posições no tabuleiro e a confirmação das jogadas devem ser realizadas através de um mouse conectado a uma das portas USB do Kit de desenvolvimento DE1-SoC. Além disso, os botões e chaves disponíveis na placa podem ser utilizados para controlar o jogo, como iniciar, pausar e continuar. Os LEDs e displays 7-segmentos também podem ser empregados para representar outras informações, conforme necessário.
    </p>

  <p>
    Requisitos
    
    - O código deve ser escrito em linguagem C
    - O sistema só poderá utilizar os componentes disponíveis na placa
    - A escolha de quadrante e confirmação de jogada devem ser feitas pela movimentação e cliques do mouse
  </p>
</h3>

<h2>- Equipe</h2>
<uL>
  <li><a href="https://github.com/Armaaaaaaaaaaaaaaaaaaaaaaaaaaando">Armando de Lima Almeida</a></li>
  <li><a href="https://github.com/DiogoDSJ">Diogo dos Santos de Jesus</a></li>
  <li><a href="https://github.com/eugabrielbr">Gabriel Silva dos Santos</a></li>
</ul>

<h2>- Sumário</h2>
<div id="sumario">
<ul>
        <li><a href="#mouse">  Captação do mouse</a></li>
        <li><a href="#funcionamento">  Funcionamento do jogo</a></li>
        <li><a href="#placa"> Componentes da placa</a></li>
        <li><a href="#teste"> Testes </a></li>
        <li><a href="#conclusao"> Conclusão </a></li>
        <li><a href="#execucao"> Execução do Projeto </a></li>
        <li><a href="#referencias"> Referências </a></li>
</ul>
</div>


<h2>Metodologia aplicada</h2>
  <p>O desenvolvimento do projeto se deu por meio de sessões tutoriais, as quais auxiliaram o grupo a cumprir os objetivos propostos. Através da primeira sessão de laboratório, foi apresentada a placa na qual o trabalho seria realizado. A partir daí, foram desenvolvidas as habilidades necessárias para a implementação do projeto.

<div id="mouse">
<h4>- Captação do mouse</h4>
  <div style="margin-top: 50px;">
   Para capturar o comportamento do mouse através do Linux, acessamos o diretório `/dev/input`, onde estão listados todos os dispositivos de entrada conectados ao sistema, como mouse, teclado, entre outros. A partir desse conhecimento, pudemos analisar o comportamento do arquivo utilizando o comando `sudo xxd -b mice`, o qual nos permitiu obeservar as alterações dos registros e receber essas informações em formato binário através do terminal (Figura 1). Cada byte, apresenta um comportamento diferente ao realizar alguma interação com o mouse.

<div align="center"> 
  <img src = "https://github.com/eugabrielbr/projeto-de-console-dedicado/assets/129075181/3304f4c7-4661-4230-b8f3-60e1b84037c8" width="500px" />
</div>
<p align="center"><strong>Figura 1.</strong></p>

  A captação do movimento do mouse é realizada através da leitura dos dados do dispositivo de entrada do mouse, que é acessado como um arquivo no sistema operacional Linux. O utilizamos a função `fread` para ler os dados do mouse, os quais são armazenados em um array de caracteres chamado `mouse_data`.

  Esses dados representam os eventos gerados pelo movimento e cliques do mouse. Cada vez que o mouse é movido ou um botão é pressionado, um evento é registrado e   seus detalhes são enviados para o sistema operacional, que os disponibiliza para leitura pelo programa.

  Neste caso, os eventos do mouse são representados pelos seis primeiros bytes do array `mouse_data`. O primeiro byte representa os botões do mouse, onde o bit 0 (menos significativo) corresponde ao botão esquerdo, o bit 1 ao botão direito e o bit 2 ao botão do meio. Os bytes seguintes representam os movimentos do mouse ao longo dos eixos x e y, respectivamente, indicando a direção e magnitude do movimento.

  Esses dados são interpretados para determinar se houve movimento do mouse e/ou cliques nos botões. Dependendo dos valores lidos nos bytes do array `mouse_data`, as funções `clique_mouse` e `movimentacao_mouse` decidem como o cursor deve se mover e se uma jogada deve ser registrada no tabuleiro do jogo da velha.

  Dentro das funções de movimento do mouse, é utilizada uma variável contadora para auxiliar no acumular do movimento do mouse ao longo do tempo. Isso permite   determinar se o movimento foi suficiente para ser considerado uma ação do usuário. Quando o contador é incrementado, significa que houve uma captura de movimento   para a direita, e quando é decrementado, uma captura de movimento para a esquerda. Além disso, há variáveis de sensibilidade nas funções que precisam ser zeradas   ao captar o movimento, evitando que movimentos anteriores influenciem na detecção de movimentos futuros, garantindo que cada movimento seja tratado de forma   independente e precisa durante o loop do jogo.
</div>

<div id="funcionamento">
<h4>- Funcionamento do jogo</h4>
<div style="margin-top: 50px;">
  <p></p>
  Com base nas informações obtidas sobre o movimento do mouse e os cliques, o funcionamento do jogo foi implementado. O jogo apresenta uma tabela 3x3 no terminal, seguindo o formato do jogo da velha, com espaços em branco. A movimentação do mouse é refletida no preenchimento do quadrante selecionado, destacado pela cor verde (Figura 2), indicando que o quadrante está disponível para seleção. Conforme o mouse é movido, o quadrante verde se move correspondendo ao movimento.

<p></p>
Ao clicar com o botão esquerdo do mouse, o jogador insere um marcador (X ou O) na posição selecionada, indicando se é o jogador 1 ou o jogador 2, respectivamente. Se o usuário tentar selecionar um quadrante já preenchido, o quadrante é destacado em vermelho (Figura 3), indicando que não pode ser selecionado novamente. Assim, o jogo continua até que um dos jogadores vença o desafio.
</div>

<div align="center"> 
  <img src = "https://github.com/eugabrielbr/projeto-de-console-dedicado/assets/111616936/a0e104cd-3376-4e62-ae37-ed172887e48f" width="700px" />
</div>
<p align="center"><strong>Figura 2.</strong></p>

<div align="center"> 
  <img src = "https://github.com/eugabrielbr/projeto-de-console-dedicado/assets/111616936/956023f5-26a6-4b35-a604-901b55a2f035" width="700px" />
</div>
<p align="center"><strong>Figura 3.</strong></p>

<div id="placa">
<h4>- Componentes da placa</h4>
    <div style="margin-top: 50px;">
Para facilitar certas operações durante o jogo, como iniciar ou encerrar uma partida, os botões do kit de desenvolvimento DE1-SoC foram empregados. Esses botões, conhecidos como pushbuttons, foram identificados no código como "KEY". Para implementar essa funcionalidade, utilizamos a documentação fornecida pela placa, que oferecia um código básico para abrir, ler e fechar o arquivo do pushbutton. Esse procedimento foi adotado devido à natureza do arquivo, onde abrimos o arquivo para acessar suas informações, verificamos o sinal recebido e, em seguida, fechamos o arquivo novamente.

Os botões utilizados foram o pushbutton KEY2 e KEY3 do kit de desenvolvimento. Capturamos os sinais desses botões através de condições, verificando se o valor da variável "data" (onde está armazenado o estado dos botões) era igual a 8, indicando que o primeiro botão foi pressionado, ou igual a 4, representando o segundo botão. Essa lógica se estende até o bit menos significativo.

Dessa forma, ao pressionar o botão 1, o jogo é iniciado, e ao pressionar o botão 2, o jogo é encerrado. No entanto, é importante observar que essa funcionalidade está disponível apenas no início do jogo, ou seja, logo após a compilação do código. Não é possível iniciar ou encerrar o jogo durante sua execução.

<div id="teste">
<h4>- Testes e resultados</h4>
  <div style="margin-top: 50px;">
    
Com a conclusão do projeto, foi necessário confirmar que o jogo funcionava de forma adequada, atendendo a todos os requisitos estabelecidos. Como parte deste processo, foram realizados testes de funcionamento do jogo. Ao compilar e executar o projeto, é necessário pressionar um dos botões da placa. Neste caso, o botão específico é o botão KEY3. Após seguir este procedimento, a interface do jogo será exibida conforme ilustrado na Figura 4.
<p></p>

<div align="center"> 
  <img src = "https://github.com/eugabrielbr/projeto-de-console-dedicado/assets/111616936/34c7af5e-90ce-4ee9-9b65-52d08f6db669" width="700px" />
</div>
<p align="center"><strong>Figura 4.</strong></p>

<div style="margin-top: 50px;">
   Após o aparecimento dessas informações, é necessário pressionar novamente o mesmo botão para iniciar o jogo. Após este procedimento, o jogo é iniciado com um tabuleiro 3x3, e um quadrado verde indicando a posição selecionada, como mostrado na Figura 2:
</div>
<p></p>


 <div style="margin-top: 50px;">
    Com o jogo iniciado, é possível movimentar o cursor do mouse para a esquerda, direita, para cima e para baixo, a fim de alterar a posição do quadrante e selecionar onde fazer a jogada. A progressão do jogo continua até que um dos jogadores vença a partida, podendo ser a vitória do jogador 1 (Figura 5) ou do jogador 2 (Figura 6). Além dessas duas possibilidades, há também a chance de ocorrer um empate (Figura 7).
<p></p>

<div align="center"> 
  <img src = "https://github.com/eugabrielbr/projeto-de-console-dedicado/assets/111616936/e735c815-7c32-4ca6-86ca-23063262b9ed" width="700px" />
</div>
<p align="center"><strong>Figura 5.</strong></p>

<div align="center"> 
  <img src = "https://github.com/eugabrielbr/projeto-de-console-dedicado/assets/111616936/28e6e49b-f3e5-4138-b304-591936b1cb77" width="700px" />
</div>
<p align="center"><strong>Figura 6.</strong></p>

<div align="center"> 
  <img src = "https://github.com/eugabrielbr/projeto-de-console-dedicado/assets/111616936/23f0c46a-45a0-4649-b7f5-aaa5de8ab078" width="700px" />
</div>
<p align="center"><strong>Figura 7.</strong></p>

  </div>
   <div style="margin-top: 50px;">
    Abaixo (Figura 8), é apresentado uma abstração do funcionamento do programa em forma de fluxograma, facilitando assim, o entendimento. 
<p></p>


<div align="center"> 
  <img src = "https://github.com/eugabrielbr/projeto-de-console-dedicado/assets/107954198/fdf10546-b4d8-4f2e-8b3f-6509275a5d2c" width="700px" />
</div>
<p align="center"><strong>Figura 8.</strong></p>

<div id="conclusao">
<h2>- Conclusão</h2>
<div style="margin-top: 50px;">
  O propósito do projeto foi proporcionar aos integrantes do projeto uma compreensão mais profunda da comunicação entre o kit de desenvolvimento DE1-SoC e o mouse, com foco na identificação do tipo de comunicação entre esses dois componentes, a fim de formular o funcionamento do jogo da velha. O experimento foi altamente bem-sucedido, uma vez que todos os objetivos foram alcançados, atendendo plenamente aos requisitos pré-estabelecidos.
  <p></p>

Além disso, o desenvolvimento do projeto proporcionou uma ampla expansão do conhecimento no campo dos sistemas digitais. Foi possível compreender como os componentes externos se comunicam com a máquina, bem como onde e como capturar essas informações e manipulá-las para criar diversos cenários. Adicionalmente, o projeto permitiu uma imersão no funcionamento dos componentes do kit de desenvolvimento, como a utilização dos pushbuttons para iniciar e encerrar o jogo, respectivamente.

A experiência adquirida durante este projeto não apenas cumpriu seus objetivos educacionais, mas também proporcionou aos integrantes do projeto uma base sólida de compreensão dos conceitos fundamentais de sistemas digitais e sua aplicação prática. Este conhecimento não apenas beneficia o desenvolvimento de projetos futuros, mas também promove uma visão mais abrangente e crítica no campo da tecnologia.


  
</div>

<div id="execucao">
<h2>- Execução do projeto</h2>
 <div style="margin-top: 50px;">
 Para iniciar o jogo, é necessário seguir os seguintes passos para obter o código-fonte, compilar o código em C e executá-lo em um dispositivo FPGA DE1-SoC. 

**Passo 1: Clonar o Repositório**

Abra o terminal e execute o seguinte comando para clonar o repositório:


      git clone https://github.com/eugabrielbr/projeto-de-console-dedicado.git 

**Passo 2: Compile os codigos usando o make execute o arquivo Main.exe**


      make 
      sudo ./Main.exe 

**Passo 3: Para limpar objetos .o e Main.exe gerados na compilação**



      make clean

<div id="referencias">
<h2>- Referências</h2>
 <div style="margin-top: 50px;">
    - FPGA ACADEMY. Disponível em: https://fpgacademy.org/. Acesso em: 25 de abril de 2024.
   <p></p>
    - Piazza, JEFF. Exploring /dev/input. Disponivel em: https://thehackerdiary.wordpress.com/2017/04/21/exploring-devinput-1/. Acesso em: 07 de abril de 2024.
<p></p>




