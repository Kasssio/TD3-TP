## [Link a documentación de LaTeX](https://ashki23.github.io/markdown-latex.html#latex-equations)
### Invariante de representación:

$$
\text{rep}(B:text{Billetera}) = \text{saldosCorrectos}(B) \land \text{EsRecientes}(B) \land \text{EsFrecuentes}(B)
$$

### Funciones del rep:
$$
\text{SaldosCorrectos}(B:\text{Billetera}) \equiv 
( \exists \ \text{UT:transaccion}) \text{EsUltimaTransacción}(\text{UT}) \land B.\textunderscore saldo = B.\textunderscore \text{saldo} \textunderscore \text{por} \textunderscore \text{dia}(\text{Fin}(\text{UT}.\textunderscore \text{timestamp})) \land 
( \forall T : \text{Transacción}) \  0 \le T.\textunderscore timestamp \le \text{Fin}(\text{UT}.\textunderscore timestamp) \land 
\left( \text{EsPrincipioDeDía}(T.\textunderscore timestamp) \Rightarrow \text{EsSaldoActualizadoPorDía}(B, T.\textunderscore timestamp) \right)
$$

### Funciones auxiliares
$$
\text{EsUltimaTransacción}(B\:\text{Billetera},\ T\:\text{Transacción}) \equiv 
L = \text{transaccionesBlockchain}(B) \land 
( \exists i : int) \ 0 \le i < |L| \land L[i] = T \land 
\neg (\exists j : int) 0 \le j < |L| \land j \ne i \land L[j].\textunderscore timestamp > L[i].\textunderscore timestamp))
$$


