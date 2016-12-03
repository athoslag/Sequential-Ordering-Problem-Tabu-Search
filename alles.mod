set N;
set C;
param G;
param p{i in N, j in N};

param DIMENSION, integer, >=3;

set VERTICES := 1..DIMENSION;
set ARCS, within (VERTICES cross VERTICES);

param arcCost{(i,j) in ARCS};

var x{(i,j) in ARCS}, binary;

var y{(i,j) in ARCS}, >= 0;

minimize costs: sum{(i,j) in ARCS: i!=j}(x[i,j] * arcCost[i,j]);

s.t. outLim{j in VERTICES}: sum{(i,j) in ARCS} x[i,j] = 1;

s.t. inLIM{i in VERTICES}: sum{(i,j) in ARCS} x[i,j] = 1;

s.t. cap{(i,j) in ARCS}: y[i,j] <= (DIMENSION-1) * x[i,j];

s.t. node{i in VERTICES}:

		sum{(j,i) in ARCS} y[i,j]

		+ (if i = 1 then DIMENSION) =

		sum{(i,j) in ARCS} y[i,j]

		+1;

solve;
end;
