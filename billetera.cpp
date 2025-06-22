#include <vector>

#include "lib.h"
#include "calendario.h"
#include "billetera.h"
#include "blockchain.h"
#include <iostream>
#include <map>
/*
  INVARIANTE DE REP:

*/


using namespace std;

Billetera::Billetera(const id_billetera id, Blockchain* blockchain)
  : _id(id)
  , _blockchain(blockchain)
  , _saldo(0) // seteamos saldo en 0 asi no agarra basura
  , _cantidad_transacciones({})
  , _cantidad_transacciones_invertido({})
  , _saldo_por_dia({})
  , _frecuentes({})
  , _recientes({})
  {}

id_billetera Billetera::id() const {
  return _id; // O(1)
}

void Billetera::notificar_transaccion(Transaccion t) {
  _recientes.push_back(t); // O(1)
  if (t.origen == _id) { // O(1)
    _saldo-=t.monto; // O(1)
    int cant = _cantidad_transacciones[t.destino] + 1; // O(Log(C))
    _cantidad_transacciones[t.destino] = cant; // O(Log(C))

    vector<id_billetera> cantidad_anterior_vector; // O(1)
    vector<id_billetera> cantidad_anterior_vector_old = _cantidad_transacciones_invertido[cant-1]; // O(Log(C))

    int s = cantidad_anterior_vector_old.size(); // O(1)

    for (int i = 0; i < s;i++){ // O(S) con S < C
      if(cantidad_anterior_vector_old[i] != t.destino){ // O(1)
        cantidad_anterior_vector.push_back(cantidad_anterior_vector_old[i]); // O(1)
      }
    }

    _cantidad_transacciones_invertido[cant-1] = cantidad_anterior_vector; // O(Log(C))
    
    _cantidad_transacciones_invertido[cant].push_back(t.destino); // O(Log(C))
    _frecuentes = {}; // O(1)

    for(auto it = _cantidad_transacciones_invertido.rbegin(); it != _cantidad_transacciones_invertido.rend(); it ++){ // O(C)
      _frecuentes.insert(_frecuentes.end(),it->second.begin(), it->second.end()); // O(it->second) con it->second < C
    }

  } 
  if (t.destino == _id) {
    _saldo+=t.monto; // O(1)
  }
  // Todo el for es O(D*Log(D))
  timestamp unDia = Calendario::dia(1); // O(1)
  timestamp finalDeHoy = Calendario::fin_del_dia(Calendario::tiempo_actual()); // O(1)


  for (timestamp d = unDia; d < finalDeHoy ; d+=unDia){ // O(D)
    if (_saldo_por_dia.find(d+unDia) == _saldo_por_dia.end()){ // O(log(D))
      _saldo_por_dia[d+unDia] = _saldo_por_dia[d]; // O(log(D))
    }
  }

  
  timestamp fin_del_dia = Calendario::fin_del_dia(t._timestamp); // O(1)
  _saldo_por_dia[fin_del_dia] = _saldo; // log(D)
} // Complejdad final: O()

monto Billetera::saldo() const {
  return _saldo; // O(1)
}

monto Billetera::saldo_al_fin_del_dia(timestamp t) const {

  if (_recientes[_recientes.size()-1]._timestamp < t) return _saldo; // O(1)

  timestamp fin_del_dia = Calendario::fin_del_dia(t); // O(1)
  return _saldo_por_dia.at(fin_del_dia); // log(D)
}

vector<Transaccion> Billetera::ultimas_transacciones(int k) const {
  auto it = _recientes.rbegin(); // O(1)
  vector<Transaccion> ret; // O(1)
  while (it != _recientes.rend() && ret.size() < k){ // O(k)
    ret.push_back(*it); // O(1)
    it++; // O(1)
  }
  return ret; // O(1)
} // Complejidad final: O()

vector<id_billetera> Billetera::detinatarios_mas_frecuentes(int k) const {
  
  vector<id_billetera> ret; // O(1)
  int i = 0; // O(1)
  int s = _frecuentes.size(); // O(1)
  while (i < s && i < k){ // O(k)
    ret.push_back(_frecuentes[i]); // O(1)
    i++; // O(1)
  }
  return ret; // O(1)

}
