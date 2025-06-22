## [Link a documentación de LaTeX](https://ashki23.github.io/markdown-latex.html#latex-equations)
### Invariante de representación:

$$
\text{REP}(B:\text{Billetera})\equiv \text{saldosCorrectos}(B) \land \text{EsRecientes}(B) \land \text{EsFrecuentes}(B)
$$

### Funciones del rep:
$$
\text{SaldosCorrectos}(B:\text{Billetera}) \equiv 
( \exists \ \text{UT:transaccion}) \text{EsUltimaTransacción}(\text{B, UT}) \land B.\textunderscore saldo = B.\textunderscore \text{saldo} \textunderscore \text{por} \textunderscore \text{dia}(\text{Fin}(\text{UT}.\textunderscore \text{timestamp})) \land 
( \forall T : \text{Transacción}) \  0 \le T.\textunderscore timestamp \le \text{Fin}(\text{UT}.\textunderscore timestamp) \land 
\left( \text{EsPrincipioDeDía}(T.\textunderscore timestamp) \Rightarrow \text{EsSaldoActualizadoPorDía}(B, T.\textunderscore timestamp) \right)
$$

$$
\text{EsRecientes}(B : \text{Billetera}) \equiv 
 L = \text{transaccionesBlockchain}(B) \land 
\text{RecientesDentroDeTransacciones}(B, L) \land 
\text{RecientesLimpio}(B, L) \land 
\text{EstaOrdenado}(B)
$$

$$
\text{EsFrecuentes}(B: \text{Billetera}) \equiv L = \text{TransaccionesBlockchain(B)} \land \text{tiene} \textunderscore \text{cant} \textunderscore \text{transacciones(B)} \land
\text{tiene}\textunderscore \text{cant}\textunderscore \text{transacciones}\textunderscore \text{invertido}(B) \land ( 
\forall i : int) 0 \le i < |B.\textunderscore \text{frecuentes}| \Rightarrow 
( \exists j : int) \ j \in \text{claves}(B.\textunderscore \text{cantidad}\textunderscore \text{transacciones}\textunderscore \text{invertido} ) \land 
\text{estáContenido}(B.\textunderscore \text{frecuentes}[i], B.\textunderscore \text{cantidad}\textunderscore \text{transacciones}\textunderscore \text{invertido}[j]) \land 
\text{FrecuentesOrdenado}(B, L)
\land \sum_{c \in \text{claves}(B.\textunderscore \text{cti})} |B.\textunderscore \text{cantidad}\textunderscore \text{transacciones}\textunderscore \text{invertido}[c]| = |B.\textunderscore \text{frecuentes}|
$$



### Funciones auxiliares
$$
\text{EsUltimaTransacción}(B\:\text{Billetera},\ T\:\text{Transacción}) \equiv 
L = \text{transaccionesBlockchain}(B) \land 
( \exists i : int) \ 0 \le i < |L| \land L[i] = T \land 
\neg (\exists j : int) 0 \le j < |L| \land j \ne i \land L[j].\textunderscore timestamp > L[i].\textunderscore timestamp))
$$

$$
\text{EsSaldoActualizadoPorDía}(B:\text{Billetera}, t:\text{timestamp}) \equiv 
L = \text{transaccionesBlockchain}(B) \land 
B.\textunderscore \text{saldo} \textunderscore \text{por} \textunderscore \text{día}[t] = 
\sum_{i = 0}^{|L| - 1} 
\beta(L[i].\textunderscore timestamp < t) \cdot L[i].\textunderscore monto \cdot 
\left( \beta(L[i].\textunderscore destino = B.\textunderscore id) - \beta(L[i].\textunderscore origen = B.\textunderscore id) \right)
$$

$$
\text{RecientesDentroDeTransacciones}(B:\text{Billetera}, L:{list \textless \text{transacción} \textgreater}) \equiv 
(\forall i:int),\ 0 \le i < |L| \Rightarrow 
(\exists j:int) \ 0 \le j < |B.\textunderscore \text{recientes}| \land B.\textunderscore \text{recientes}[j] = L[i]
$$

$$
\text{RecientesLimpio}(B:\text{Billetera},L \text{list}\textless \text{transacción} \textgreater) \equiv 
\neg (\exists j:int) 0 \le j < |L| \land (\forall i:int) 0 \le i < |L| \Rightarrow L[i] \ne B.\textunderscore \text{recientes}[j]
$$

$$
\text{EstáOrdenado}(B:\text{Billetera}) \equiv 
(\forall i :int) 0 \le i < |B.\textunderscore \text{recientes}| - 1 \Rightarrow 
B.\textunderscore \text{recientes}[i].\textunderscore \text{timestamp} \ge B.\textunderscore \text{recientes}[i+1].\textunderscore \text{timestamp}
$$

$$
\text{tiene}\textunderscore \text{Cant} \textunderscore \text{Transacciones} \textunderscore \text{invertido}(B: \text{Billetera}) \equiv 
(\forall i: \text{int}) ( i \in \text{claves}(B.\textunderscore \text{cant} \textunderscore \text{transacciones} \textunderscore \text{invertido}) \Rightarrow 
(\exists v: \text{vector<id_billetera>}) 
|v| = \text{cantidadAcordeTransacciones}(B, i) \land
\left( (\forall j: \text{int}) , 0 \leq j < |v| \Rightarrow B.\textunderscore \text{cant} \textunderscore \text{transacciones}[v[j]] = i \right) \land 
B.\textunderscore \text{cant} \textunderscore \text{transacciones} \textunderscore \text{invertido}[i] = v 
$$

$$
\text{tiene}\textunderscore \text{cant} \textunderscore \text{transaccion}(B: \text{Billetera}) \equiv 
L = \text{transaccionesBlockchain}(B) \land 
(\forall id: \text{id}\textunderscore \text{billetera}) , id \in \text{claves}(B.\textunderscore \text{cant} \textunderscore \text{transacciones}) \Rightarrow 
B.\textunderscore \text{cant} \textunderscore \text{transacciones}[id] = \text{CantVecesTransferidas}(L, id)
$$

$$
\text{CantVecesTransferidas}(L:\text{list}\textless \text{Transaccion} \textgreater ,id: \text{id}\textunderscore \text{billetera}): \text{int} \equiv 
\sum_{i = 0}^{|L| - 1} 
\beta(L[i].\text{destino} = id)
$$

$$
\text{estáContenido}(id: \text{int},\text{idsPorCantTrans}: \text{vector}\textless \text{id}\textunderscore \text{billetera}\textgreater) \equiv 
(\exists i: \text{int}) , 0 \leq i < |\text{idsPorCantTrans}| \land \text{idsPorCantTrans}[i] = id
$$

$$
\text{cantidadAcordeTransacciones}(B: \text{Billetera}, i: \text{int}) : \text{int} = 
\sum_{j \in \text{claves}(B.\textunderscore \text{cantidad}\textunderscore \text{transacciones})} 
\beta(B.\textunderscore \text{cantidad}\textunderscore \text{transacciones}[j] = i)
$$

$$
\text{FrecuentesOrdenado}(B:\text{Billetera}, L:\text{list} \textless \text{Transaccion} \textgreater) \equiv ( \forall k : int) 0 \le k < |B.\textunderscore \text{frecuentes}| - 1 \Rightarrow 
\text{cantidadVecesTransferidas}(L, B.\textunderscore \text{frecuentes}[k]) \geq 
\text{cantidadVecesTransferidas}(L, B.\textunderscore \text{frecuentes}[k+1])
$$



