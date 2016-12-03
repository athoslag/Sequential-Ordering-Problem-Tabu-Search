#		Sequential Ordering Problem 		#
#		Athos Lagemann e Eduardo Pereira 	# 
#		Otimização Combinatória 2016-2 		#
# br17 = 55

# 	Conjuntos
set N;
set C;

# 	Parâmetros
param INF, integer; # Um número mt grande 
param P{i in N, j in N}, binary; # Dígrafo de precedência
param n := card(C)+1; # tamanho
param c{i in N, j in N}, integer; # custo de ir de i para j

#	Variáveis
# Define x(i,j) como variável binária, onde 1: arco está na solução final e 0 caso contrário
var x{i in N, j in N}, binary; # (MATRIZ)

# Ordem de visitação dos vértices, feita pelo caixeiro viajante
var u{i in N} >= 0, integer; # (ARRAY)

# Função objetivo
minimize costs: sum{i in N, j in N: i !=j and i != n and j != 0} x[i,j] * c[i,j];

# 1 - Parte sempre do início
s.t. start:
		sum{j in N: j != 0} x[0,j] = 1;

# 2 - Chega sempre no final
s.t. end:
		sum{i in N: i != n} x[i,n] = 1;

# 3 - Cada vértice deve ser visitado exatamente uma vez
s.t. onevisit{i in C}:
		sum{j in N: j != 0 and j != i} x[i,j] = 1;

# 4 - Todo vértice tem um entrante
s.t. inLim{j in C}: 
		sum{i in N: j != i and i != n} x[i,j] = 1;

# 4 - Todo vértice tem um sainte
s.t. outLim{j in C}: 
		sum{k in N: j != k and k != 0} x[j,k] = 1;

# 4 - Todo entrante tem exatamente um sainte
s.t. paired{j in C}: 
		sum{i in N: j != i and i != n} x[i,j] + sum{k in N: j != k and k != 0} x[j,k] = 2;

# 6 - Mantém coerente a ordem de visitação
s.t. order{i in N, j in N: i != j and i != n and j != 0}:
		1 + u[i] <= u[j] - INF * (x[i,j] - 1);

# 7 - Precedências devem ser respeitadas
s.t. prec{i in N, j in N: i != j and i != n and j != 0 and P[i,j] = 1}: 
		u[i] + 1 <= u[j];

end;
