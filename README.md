## [Link a documentación de LaTeX](https://ashki23.github.io/markdown-latex.html#latex-equations)
### Invariante de representación:
$$ \large \text{Rep(B:Billetera)} \equiv \text{TransaccionesBlockchain(B)} = \text{listT} \land \text{EsSaldo} \textunderscore \text{actualizado(} \textunderscore \text{saldo, listT, B)} \land $$ $$ \large \text{Es} \textunderscore \text{recientes(listT, B, } \textunderscore \text{recientes)} \land \text{EsCant} \textunderscore \text{Transacciones(} \textunderscore \text{cant} \textunderscore \text{transacciones, } \textunderscore \text{cant} \textunderscore \text{transacciones} \textunderscore \text{invertido} \land $$
$$ \large \text{EsFrecuentes(} \textunderscore \text{cant} \textunderscore \text{transacciones} \textunderscore \text{invertido, } \textunderscore \text{frecuentes)} \land \text{EsSaldo} \textunderscore \text{por} \textunderscore \text{dia(} \textunderscore \text{saldo} \textunderscore \text{por} \textunderscore \text{dia, listT, B)}$$


### Funciones auxiliares:

$$\large \text{Es} \textunderscore \text{saldo} \textunderscore \text{actualizado(S:monto)} \equiv S = \sum_{\text{i=0}}^{\text{|list|-1}} \beta \ \text{(listT[i].destino == B.id) } \cdot \text{ list[i].monto} - \text{(listT[i].origen == B.id) } \cdot \text{ list[i].monto} $$

$$
\large \text{Es}\textunderscore\text{recientes}( \text{listT:vector}\langle\text{transaccion}\rangle, B:\text{Billetera}, \textunderscore\text{recientes}:\text{vector}\langle\text{Transaccion}\rangle ) = |\textunderscore\text{recientes}| = |\text{listT}| \land (\forall i \in \mathbb{N})(0 \le i < |\textunderscore\text{recientes}| - 1 \Rightarrow \textunderscore\text{recientes[i]} \ge \textunderscore\text{recientes[i+1])}
$$


