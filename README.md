
O projeto está organizado da seguinte forma:

├── Makefile
├── README.md
├── bin # diretório de todos os arquivos executáveis gerados
├── lib # pasta onde fica todos os arquivos headers .h
│   ├── border_detection.h # header dos algoritmos de detecção de borda (sem manipulação de imagem)
│   ├── hardware
│   │   └── convolution.h # header do algoritmo de convolução utilizando coprocessador
│   ├── image.h # header para manipulação básica de imagem, bem como filtros de detecção de borda
│   └── software
│       └── convolution.h # header do algoritmo de convolução implementado 100% via software
├── main.c 
├── media
│   ├── <imagem a ser utilizada o filtro>.<extensão de imagem>
│   └── <imagem resultado>.jpg
├── obj # diretório de todos os arquivos objeto gerados
├── src # diretório onde inclue as implementações dos header localizados em lib
│   ├── border_detection.c
│   ├── hardware
│   │   └── convolution.c
│   ├── image.c
│   └── software
│       └── convolution.c
└── tests # diretório que possui programas testes para a biblioteca
    ├── border_detection.c
    ├── convolution.c
    └── image.c

