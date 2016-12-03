set N;
set C;

param c{i in N, j in N}; #Custo da viajem do cliente i ao cliente j.
param p{i in N, j in N}; #Se i precede j

param n := card(C)+1; #número de clientes.
param G;

var x{i in N, j in N: i!=j and i!=n and j!=0} binary; #Binária
var s{i in N} >= 0; 

minimize obj: sum{i in N, j in N: i!=j and i!=n and j!=0} c[i,j] * x[i,j];

#Cada nodo deve ser visitado apenas uma vez.
s.t. c1{i in C}: 
    sum{j in N: j!=0 and i!=j} x[i,j] = 1;
    
#Partida sempre do nodo 0.
s.t. partida: 
    sum{j in N: j!=0} x[0,j] = 1;

#Chegada sempre no nodo n.
s.t. chegada:
    sum{i in N: i!=n} x[i,n] = 1;

# Para cada entrante tem um sainte.    
s.t. c4{h in C}: 
    sum{i in N: i!=n and  h!=i} x[i,h] - sum{j in N: j!=0 and  h!=j} x[h,j] = 0;

#Um sempre deve ser visitado após o outra.  
s.t. c6{i in N, j in N: i!=j and i!=n and j!=0}: 
    s[i] + 1 <= s[j] + G * (1-x[i,j]) ;
    
#Satisfazer restrição de precedencia. 
s.t. precedencia{i in N, j in N: p[i,j]=1 and i!=j and i!=n and j!=0}: 
   s[i] + 1 <= s[j];

end;

