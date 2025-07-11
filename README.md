#  Projeto de Detecção de Bordas em C com Aceleração por Hardware             

  ## Autores                                                                  
                                                                              
  • Davi Macêdo Gomes: github.com/davimg07 https://github.com/davimg07        
  • Pedro Henrique Santos Silva: github.com/PSSUEFS https://github.com/PSSUEFS
                                                                              
  ## Sumário                                                                  
                                                                              
  • Visão Geral                                                               
  • Estrutura do Projeto                                                      
  • Como Compilar                                                             
  • Como Executar                                                             
  • Algoritmos e Teoria                                                       
  • Funções da Biblioteca                                                     
  • Testes                                                                    
                                                                              
  ## Visão Geral                                                              
                                                                              
  Este projeto oferece uma implementação em C de algoritmos clássicos de      
  detecção de bordas, como Sobel, Prewitt, Roberts e Laplace. A principal     
  característica do projeto é sua arquitetura dual, que permite a execução    
  tanto em um processador padrão (HPS - Hard Processor System) quanto com     
  aceleração por hardware em um FPGA (Field-Programmable Gate Array).         
                                                                              
  A operação de convolução, que é a base para a maioria dos filtros de imagem 
  e computacionalmente intensiva, pode ser descarregada para o FPGA,          
  resultando em um ganho de performance significativo em comparação com a     
  execução puramente em software.                                             
                                                                              
  ## Estrutura do Projeto                                                     
                                                                              
    .                                                                         
    ├── Makefile                                                              
    ├── README.md                                                             
    ├── bin/                                                                  
    ├── lib/                                                                  
    ├── media/                                                                
    ├── src/                                                                  
    └── tests/                                                                
                                                                              
  •  bin/ : Contém os arquivos executáveis compilados.                        
  •  lib/ : Inclui todos os arquivos de cabeçalho ( .h ).                     
  •  media/ : Contém imagens de entrada para teste e as imagens de saída      
  geradas pelos algoritmos.                                                   
  •  src/ : Contém as implementações ( .c ) das funções definidas nos         
  cabeçalhos.                                                                 
  •  tests/ : Contém os códigos de teste para os módulos do projeto.          
                                                                              
  ## Como Compilar                                                            
                                                                              
  Para compilar o projeto, o  Makefile  automatiza todo o processo.           
  Simplesmente execute:                                                       
                                                                              
    make                                                                      
                                                                              
  Este comando irá gerar dois executáveis no diretório  bin/ :                
                                                                              
  1.  bin/image_hps : Uma versão puramente em software, onde todos os cálculos
  são realizados pelo processador principal (CPU/HPS).                        
  2.  bin/image : A versão acelerada por hardware, que utiliza o coprocessador
  em FPGA para a operação de convolução. Esta versão é compilada com a macro  -
  DCOPROCESSOR .                                                              
                                                                              
  ## Como Executar                                                            
                                                                              
  Após a compilação, você pode executar os testes de detecção de borda usando 
  os scripts do  Makefile  para conveniência.                                 
                                                                              
  • Para executar a versão em software (HPS):                                 
    make run_hps                                                              
                                                                              
  • Para executar a versão acelerada por hardware (FPGA):                     
    make run                                                                  
                                                                              
                                                                              
  Ambos os comandos irão processar a imagem de teste  media/tilapia.jpg  e    
  salvar os resultados dos diferentes filtros de borda no diretório  media/ . 
  Você pode então comparar visualmente os resultados.                         
                                                                              
  ## Algoritmos e Teoria                                                      
                                                                              
  A detecção de bordas é uma técnica fundamental em processamento de imagens  
  que visa identificar pontos em uma imagem digital nos quais o brilho da     
  imagem muda drasticamente. Essas mudanças abruptas geralmente correspondem a
  eventos importantes na cena, como limites de objetos, mudanças de textura ou
  profundidade.                                                               
                                                                              
  O método central utilizado é a convolução 2D. A imagem é percorrida por uma 
  pequena matriz chamada kernel (ou máscara). Para cada pixel, o valor do novo
  pixel é calculado como a soma ponderada dos pixels vizinhos, onde os pesos  
  são dados pelo kernel. Diferentes kernels detectam diferentes               
  características, como bordas horizontais, verticais ou diagonais.           
                                                                              
  Os algoritmos implementados são:                                            
                                                                              
  • Operadores baseados em Gradiente (1ª Derivada): Aproximam o gradiente da  
  intensidade da imagem para encontrar as bordas. Onde o gradiente é alto, há 
  uma borda.                                                                  
    • Roberts Cross: Usa um par de kernels 2x2 para detectar bordas diagonais.
    É rápido, mas sensível a ruído.                                           
    • Prewitt: Usa kernels 3x3 para detectar bordas horizontais e verticais,  
    dando igual importância a todos os pixels vizinhos.                       
    • Sobel: Similar ao Prewitt, mas dá mais peso aos pixels mais próximos do 
    centro, o que o torna um pouco mais robusto a ruído.                      
  • Operador Laplaciano (2ª Derivada): Detecta bordas procurando por          
  cruzamentos por zero na segunda derivada da imagem. É muito sensível a ruído,
  mas bom para encontrar a localização exata das bordas.                      
                                                                              
  ### Resultados Visuais                                                      
                                                                              
  É altamente recomendável inserir aqui as imagens de saída geradas para cada 
  filtro (e.g.,  sobel_gray.jpg ,  laplace_gray.jpg ) para uma comparação     
  visual direta dos resultados de cada algoritmo.                             
                                                                              
             Filtro Aplicado           │         Imagem Resultante            
  ─────────────────────────────────────┼────────────────────────────────────  
                  Sobel                │        media/sobel_gray.jpg          
                 Prewitt               │       media/prewitt_gray.jpg         
                 Roberts               │       media/roberts_gray.jpg         
                 Laplace               │       media/laplace_gray.jpg         
                                                                              
  ## Funções da Biblioteca                                                    
                                                                              
  ### lib/matrix.h                                                            
                                                                              
  A biblioteca  matrix.h  é o núcleo do processamento, tratando as imagens    
  como matrizes de pixels.                                                    
                                                                              
  •  convolution : Realiza a convolução 2D. É a função chave que pode ser     
  executada tanto em software (HPS) quanto descarregada para o hardware (FPGA).
  •  generic_edge_detection : Implementa um detector de bordas genérico       
  baseado em gradiente, que é a base para Sobel e Prewitt.                    
  •  sobel ,  sobel_expanded ,  prewitt ,  roberts ,  laplace : Implementam os
  respectivos algoritmos de detecção de bordas.                               
                                                                              
  ### lib/image.h                                                             
                                                                              
  A biblioteca  image.h  abstrai as operações de manipulação de imagens.      
                                                                              
  •  get_image : Carrega uma imagem de um arquivo (usando  stb_image ).       
  •  save_image : Salva uma imagem em um arquivo JPG (usando  stb_image_write 
  ).                                                                          
  •  sobel_image ,  prewitt_image , etc.: Funções de alto nível que aplicam os
  filtros a uma estrutura  Image .                                            
                                                                              
  ### lib/coprocessor.h                                                       
                                                                              
  A biblioteca  coprocessor.h  gerencia a comunicação com o FPGA.             
                                                                              
  •  init_mpu  /  cleanup_mpu : Funções para inicializar e finalizar a        
  comunicação com o hardware.                                                 
  •  send_matrix : Envia a janela da imagem e o kernel para o FPGA.           
  •  conv : Envia o comando para iniciar a convolução no hardware.            
                                                                              
  ## Testes                                                                   
                                                                              
  ### tests/matrix.c                                                          
                                                                              
  Contém testes unitários para as funções da biblioteca  matrix.h . Cada      
  filtro e operação matemática possui uma função de teste dedicada que usa    
  matrizes pré-definidas e imprime o resultado para verificação.              
                                                                              
  ### tests/image.c                                                           
                                                                              
  Contém testes de integração que operam em imagens reais.                    
                                                                              
  •  test_image : Testa o fluxo de carga, manipulação de pixels e salvamento  
  de uma imagem.                                                              
  •  test_edge_detection_image : Aplica todos os filtros de detecção de bordas
  em uma imagem de teste e salva os resultados, permitindo a verificação      
  visual completa do pipeline.
