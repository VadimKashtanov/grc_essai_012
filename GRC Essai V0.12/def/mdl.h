#pragma once

#include "marchee.h"

//
//  !!! THREADS !!!
//

//  H = diag(a) + non-diag(b)
//  alpha ~= - (a+b) / ( (b-a) * (a+2b) ) ~= - (a+b)/( ab + (N-1)*bb - aa -(N-1)*ab ) (FAUX)

//http://ijeais.org/wp-content/uploads/2018/07/IJAER180702.pdf
//https://stackoverflow.com/questions/47025373/fastest-implementation-of-the-natural-exponential-function-using-sse
//https://stackoverflow.blog/2020/07/08/improving-performance-with-simd-intrinsics-in-three-use-cases/
//https://arxiv.org/pdf/1504.06734.pdf

//compiler explorer

#define total 100
#define poids 100

typedef struct structure_de_model_general {
    //  Chaque implementation de mdl
    void * contenue;
    //
    uint poids;
    uint exi;   //position de l'exi
    //
    float _var[total];
    float _poid[poids];
    //
    float _grad[total]; //approximation : dpoid ne sera += qu'une fois par retro-propa
} Mdl_t;

//  === Implementation d'un type de model ===

typedef Mdl_t* (*generique_f)();
typedef Mdl_t* (*cree_mdl_f)(uint);
typedef void   (*liberer_f)(Mdl_t*); 
typedef void   (*F_f)(Mdl_t*,uint); 
typedef void   (*dF_f)(Mdl_t*,uint,float); 
typedef Mdl_t* (*muter_f)(Mdl_t*);
typedef Mdl_t* (*melanger_f)(Mdl_t*, Mdl_t*); 

typedef struct structure_des_fonctions_de_limplementation_de_ce_type_de_model {
    generique_f generique;
    cree_mdl_f cree_mdl;
    liberer_f liberer;
    //
    F_f F;
    dF_f dF;
    //
    muter_f muter;
    melanger_f melanger;
} Fonctions_t;

Mdl_t* generique(Fonctions_t fonctions);
Mdl_t* cree_mdl(uint graine, Fonctions_t fonctions);
void liberer(Mdl_t* mdl, Fonctions_t fonctions);
//
void F(Mdl_t* mdl, uint heure, Fonctions_t fonctions);
void dF(Mdl_t* mdl, uint heure, float erreur, Fonctions_t fonctions);
//
Mdl_t* muter(Mdl_t * mdl, Fonctions_t fonctions);
Mdl_t* melanger(Mdl_t * mdl0, Mdl_t * mdl1, Fonctions_t fonctions);
//
//
float score_ema1000(Mdl_t * mdl, Fonctions_t * fonctions);
