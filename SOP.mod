/*		Sequential Ordering Problem 		*/
/*		Athos Lagemann e Eduardo Pereira 	*/ 
/*		Otimização Combinatória 2016-2 		*/

param DIMENSION, integer, >=3; 

/* Definindo G = (V,A) */
set VERTICES := 1..DIMENSION;
set ARCS, within (VERTICES cross VERTICES);

/* custo de ir de i para j */
param c{(i,j) in ARCS};

/* Define x(i,j) como variável binária, onde: */
/* || 1: arco está na solução final e */
/* || 0: caso contrário */
var x{(i,j) in ARCS}, binary;

/* Função objetivo */
minimize costs: sum{(i,j) in ARCS}(x[i,j] * c[i,j]);

/* Apenas 1 arco sainte */
s.t. outLim{j in VERTICES}: sum{(i,j) in ARCS} x[i,j] = 1;

/* Apenas 1 arco entrante */
s.t. inLim{i in VERTICES}: sum{(i,j) in ARCS} x[i,j] = 1;

/* Deve respeitar a precedência de vértices */
s.t. prec{(i,j) in ARCS}: x[i,j] >= 0;

solve;
end;
