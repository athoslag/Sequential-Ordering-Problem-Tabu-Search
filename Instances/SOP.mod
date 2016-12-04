#		Sequential Ordering Problem 		#
#		Athos Lagemann e Eduardo Pereira 	# 
#		Otimização Combinatória 2016-2 		#

# 	Conjuntos
set NODES;
set ARCS;

# 	Parâmetros
param INF; # Um número muito grande 
param P{i in NODES, j in NODES}; # Dígrafo de precedência
param n := card(ARCS) + 1; # tamanho
param c{i in NODES, j in NODES}; # custo de ir de i para j

#	Variáveis
# Define x(i,j) como variável binária, onde 1: arco está na solução final e 0 caso contrário
var x{i in NODES, j in NODES}, binary; # (MATRIZ)

# Ordem de visitação dos vértices, feita pelo caixeiro viajante
var u{i in NODES} >= 0; # (ARRAY)

# 1 - Função objetivo
minimize costs: sum{i in NODES, j in NODES: i !=j and i != n and j != 0} x[i,j] * c[i,j];

# 2 - Parte sempre do início
s.t. start:
		sum{j in NODES: j != 0} x[0,j] = 1;

# 3 - Chega sempre no final
s.t. end:
		sum{i in NODES: i != n} x[i,n] = 1;

# 4 - Cada vértice deve ser visitado exatamente uma vez
s.t. onevisit{i in ARCS}:
		sum{j in NODES: j != 0 and j != i} x[i,j] = 1;

# 5 - Todo entrante tem exatamente um sainte (com exceção do início e fim)
s.t. paired{j in ARCS}: 
		sum{i in NODES: j != i and i != n} x[i,j] - sum{k in NODES: j != k and k != 0} x[j,k] = 0;

# 6 - Mantém coerente a ordem de visitação
s.t. order{i in NODES, j in NODES: i != j and i != n and j != 0}:
		u[i] + 1 <= u[j] - INF * (x[i,j] - 1);

# 7 - Precedências devem ser respeitadas
s.t. prec{i in NODES, j in NODES: i != j and i != n and j != 0 and P[i,j] = 1}: 
		u[i] + 1 <= u[j];

end;
