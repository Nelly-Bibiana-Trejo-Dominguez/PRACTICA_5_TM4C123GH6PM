function RGB
clc;

fprintf('Controlador de intensidad de un led RGB\n');
fprintf('Intensidad desde 0 hasta 255, las x representan numeros enteros\n ');
R=input('Coloca valor del led rojo de la forma rxxx:','s');
G=input('Coloca valor del led verde de la forma gxxx:','s');
B=input('Coloca valor del led azul de la forma bxxx:','s');

puerto = serialport("COM6",19200);

fwrite(puerto,R)
fwrite(puerto,G)
fwrite(puerto,B)

 fclose (puerto) ;
 delete (puerto) ;

end