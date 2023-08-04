#pragma once

#include "mdl.h"

/*  var0 -> grand reseau de filtres X:{Y:{(intervalle, temps || n)}} -> petit reseau de neurones N:{l0,l1,l2,...,1} -> %


Il y a 2 type de filtres : 
    Multiple entrees Actuelles
    Multiples temps d'une entree a intervalles (avec emaN)

*/

//  Meta ethnicitee : Pile d'instructions "filtre_temps+filtre_Z+filtre_Y"

typedef struct structure_de_model_pour_les_filtres {
    
} Filtres_t;

Mdl_t* _filtres_generique();
Mdl_t* _filtres_cree_mdl(uint graine);
void _filtres_liberer(Mdl_t* mdl);
//
void _filtres_F(Mdl_t* mdl, uint heure);
void _filtres_dF(Mdl_t* mdl, uint heure, float erreur);
//
Mdl_t* _filtres_muter(Mdl_t * mdl);
Mdl_t* _filtres_melanger(Mdl_t * mdl0, Mdl_t * mdl1);
//
//
Fonctions_t filtres;
