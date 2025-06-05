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
  return _id;
}

void Billetera::notificar_transaccion(Transaccion t) {
  _recientes.push_back(t);
  if (t.origen == _id) {
    _saldo-=t.monto;
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

    _cantidad_transacciones_invertido[cant-1] = cantidad_anterior_vector;
    
    _cantidad_transacciones_invertido[cant].push_back(t.destino); // O(Log(C))
    _frecuentes = {};

    for(auto it = _cantidad_transacciones_invertido.rbegin(); it != _cantidad_transacciones_invertido.rend(); it ++){ // O(C)
      _frecuentes.insert(_frecuentes.end(),it->second.begin(), it->second.end()); // O(it->second) con it->second < C
    }

  }
  if (t.destino == _id) {
    _saldo+=t.monto;
  }


  // Hay que arreglar esa parte que dura 150ms aprox
  // Todo el for es O(D*Log(D))
  timestamp unDia = Calendario::dia(1);
  timestamp finalDeHoy = Calendario::fin_del_dia(Calendario::tiempo_actual());


  for (timestamp d = unDia; d < finalDeHoy ; d+=unDia){ // O(D)
    if (_saldo_por_dia.find(d+unDia) == _saldo_por_dia.end()){ // O(log(D))
      _saldo_por_dia[d+unDia] = _saldo_por_dia[d]; // O(log(D))
    }
  }

  
  timestamp fin_del_dia = Calendario::fin_del_dia(t._timestamp); // O(1)
  _saldo_por_dia[fin_del_dia] = _saldo; // log(D)
}

monto Billetera::saldo() const {
  return _saldo;
}

monto Billetera::saldo_al_fin_del_dia(timestamp t) const {

  if (_recientes[_recientes.size()-1]._timestamp < t) return _saldo; // O(1)

  timestamp fin_del_dia = Calendario::fin_del_dia(t); // O(1)
  return _saldo_por_dia.at(fin_del_dia); // log(D)
}

vector<Transaccion> Billetera::ultimas_transacciones(int k) const {
  auto it = _recientes.rbegin();
  vector<Transaccion> ret;
  while (it != _recientes.rend() && ret.size() < k){
    ret.push_back(*it);
    it++;
  }
  return ret;
}

vector<id_billetera> Billetera::detinatarios_mas_frecuentes(int k) const {
  
  vector<id_billetera> ret;
  int i = 0;
  int s = _frecuentes.size();
  while (i < s && i < k){
    ret.push_back(_frecuentes[i]);
    i++;
  }
  return ret;


  // const list<Transaccion> transacciones = _blockchain->transacciones();

  // // cuento la cantidad de transacciones salientes por cada billetera de destino
  // map<id_billetera, int> transacciones_por_billetera;
  // auto it = transacciones.begin();
  // while (it != transacciones.end()) {
  //   if (it->origen == _id) {
  //     // notar que el map devuelve 0 por default!
  //     transacciones_por_billetera[it->destino]++;
  //   }
  //   ++it;
  // }

  // // invierto el map de forma que puedo accedes a las billeteras según su
  // // cantidad de transacciones.
  // map<int, vector<id_billetera>> billeteras_por_cantidad_de_transacciones;
  // auto it2 = transacciones_por_billetera.begin();
  // while (it2 != transacciones_por_billetera.end()) {
  //   billeteras_por_cantidad_de_transacciones[it2->second].push_back(it2->first);
  //   ++it2;
  // }

  // // recorro el map usando un iterador en orden inverso, que me lleva por todos
  // // los pares de entradas desde la mayor clave hasta la menor.
  // vector<id_billetera> ret = {};
  // auto it3 = billeteras_por_cantidad_de_transacciones.rbegin();
  // while (it3 != billeteras_por_cantidad_de_transacciones.rend() && ret.size() < k) {
  //   vector<id_billetera> siguiente_grupo = it3->second;
  //   int i = 0;
  //   while (i < siguiente_grupo.size() && ret.size() < k) {
  //     ret.push_back(siguiente_grupo[i]);
  //     i++;
  //   }
  //   ++it3;
  // }

  // return ret;
}
