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

<h2>Metodologia aplicada</h2>
  <p>O desenvolvimento do projeto se deu por meio de sessões tutoriais, as quais auxiliaram o grupo a cumprir os objetivos propostos. Através da primeira sessão de laboratório, foi apresentada a placa na qual o trabalho seria realizado. A partir daí, foram desenvolvidas as habilidades necessárias para a implementação do projeto.
    
    
<h4>- Captação do mouse</h4>
  <div style="margin-top: 50px;">
   Para capturar o comportamento do mouse através do Linux, acessamos o diretório `/dev/input`, onde estão listados todos os dispositivos de hardware externos conectados ao sistema, como mouse, teclado, entre outros. A partir desse conhecimento, pudemos analisar o movimento do mouse utilizando o comando `sudo xxd -b mice`, o qual nos permitiu capturar os movimentos e cliques do mouse e receber essas informações em formato binário através do terminal. Com essa captura realizada, pudemos adicionar suas funcionalidades ao código.

  A captação do movimento do mouse é realizada através da leitura dos dados do dispositivo de entrada do mouse, que é acessado como um arquivo no sistema operacional Linux. O utilizamos a função `fread` para ler os dados do mouse, os quais são armazenados em um array de caracteres chamado `mouse_data`.

  Esses dados representam os eventos gerados pelo movimento e cliques do mouse. Cada vez que o mouse é movido ou um botão é pressionado, um evento é registrado e   seus detalhes são enviados para o sistema operacional, que os disponibiliza para leitura pelo programa.

  Neste caso, os eventos do mouse são representados pelos seis primeiros bytes do array `mouse_data`. O primeiro byte representa os botões do mouse, onde o bit 0 (menos significativo) corresponde ao botão esquerdo, o bit 1 ao botão direito e o bit 2 ao botão do meio. Os bytes seguintes representam os movimentos do mouse ao longo dos eixos x e y, respectivamente, indicando a direção e magnitude do movimento.

  Esses dados são interpretados para determinar se houve movimento do mouse e/ou cliques nos botões. Dependendo dos valores lidos nos bytes do array `mouse_data`, as funções `clique_mouse` e `movimentacao_mouse` decidem como o cursor deve se mover e se uma jogada deve ser registrada no tabuleiro do jogo da velha.

  Dentro das funções de movimento do mouse, é utilizada uma variável contadora para auxiliar no acumular do movimento do mouse ao longo do tempo. Isso permite   determinar se o movimento foi suficiente para ser considerado uma ação do usuário. Quando o contador é incrementado, significa que houve uma captura de movimento   para a direita, e quando é decrementado, uma captura de movimento para a esquerda. Além disso, há variáveis de sensibilidade nas funções que precisam ser zeradas   ao captar o movimento, evitando que movimentos anteriores influenciem na detecção de movimentos futuros, garantindo que cada movimento seja tratado de forma   independente e precisa durante o loop do jogo.
</div>
<h4>- Funcionamento do jogo</h4>
<div style="margin-top: 50px;">
  <p></p>
  Com base nas informações obtidas sobre o movimento do mouse e os cliques, o funcionamento do jogo foi implementado. O jogo apresenta uma tabela 3x3 no terminal, seguindo o formato do jogo da velha, com espaços em branco. A movimentação do mouse é refletida no preenchimento do quadrante selecionado, destacado pela cor verde, indicando que o quadrante está disponível para seleção. Conforme o mouse é movido, o quadrante verde se move correspondendo ao movimento.

<p></p>
Ao clicar com o botão esquerdo do mouse, o jogador insere um marcador (X ou O) na posição selecionada, indicando se é o jogador 1 ou o jogador 2, respectivamente. Se o usuário tentar selecionar um quadrante já preenchido, o quadrante é destacado em vermelho, indicando que não pode ser selecionado novamente. Assim, o jogo continua até que um dos jogadores vença o desafio.
</div>


<h4>- Componentes da placa</h4>
    <div style="margin-top: 50px;">
Para facilitar certas operações durante o jogo, como iniciar ou encerrar uma partida, os botões do kit de desenvolvimento DE1-SoC foram empregados. Esses botões, conhecidos como pushbuttons, foram identificados no código como "KEY". Para implementar essa funcionalidade, utilizamos a documentação fornecida pela placa, que oferecia um código básico para abrir, ler e fechar o arquivo do pushbutton. Esse procedimento foi adotado devido à natureza do arquivo, onde abrimos o arquivo para acessar suas informações, verificamos o sinal recebido e, em seguida, fechamos o arquivo novamente.

Os botões utilizados foram o pushbutton 01 e 02 do kit de desenvolvimento. Capturamos os sinais desses botões através de condições, verificando se o valor da variável "data" (onde está armazenado o estado dos botões) era igual a 8, indicando que o primeiro botão foi pressionado, ou igual a 4, representando o segundo botão. Essa lógica se estende até o bit menos significativo.

Dessa forma, ao pressionar o botão 1, o jogo é iniciado, e ao pressionar o botão 2, o jogo é encerrado. No entanto, é importante observar que essa funcionalidade está disponível apenas no início do jogo, ou seja, logo após a compilação do código. Não é possível iniciar ou encerrar o jogo durante sua execução.



