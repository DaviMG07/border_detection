#/data/data/com.termux/files/usr/bin/bash

case $1 in 
  build)
  ;;
  run)
  ;;
  test)
    case $2 in 
      image)
        gcc -c src/software/convolution.c -o obj/convolution.o
        gcc src/edge_detection.c src/image.c test/image.c obj/convolution.o -o bin/test_image
        ./bin/test_image
      ;;
      edge)
      ;;
      conv)
      ;;
      *)
      ;;
    esac
  ;;
  *)
  ;;
esac
