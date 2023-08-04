#pragma once

#include "macros.h"

float rnd();

//  !!! compiler avec -O3

float fastExp3(register float x)  // cubic spline approximation
{
    union { float f; int i; } reinterpreter;

    reinterpreter.i = (int)(12102203.0f*x) + 127*(1 << 23);
    int m = (reinterpreter.i >> 7) & 0xFFFF;  // copy mantissa
    // empirical values for small maximum relative error (8.34e-5):
    reinterpreter.i +=
         ((((((((1277*m) >> 14) + 14825)*m) >> 14) - 79749)*m) >> 11) - 626;
    return reinterpreter.f;
}

//  =========== Calcule Optimisee =========
float __exp(float x);

float __gauss(float x);         //exp(-abs(x))
float __d_gauss(float x);
float __dd_gauss(float x);

float __logistique(float x);    //  x/(0.5+abs(x))
float __d_logistique(float x);
float __dd_logistique(float x);

float __tanh(float x);
float __d_tanh(float x);
float __dd_tanh(float x);

//  ========= Utilitaire =============

typedef struct {
    uint noms;
    char ** nom;
    //
    uint taille_lst;
    float *** valeurs;  //[nom][N][i]
    uint * depart;      //[nom]
    //
    uint t;
} Gnuplot_t;

Gnuplot_t gnuplot;

void traquer(char * nom, uint N, ...);  //nom=le titre de la fennetre; N=le nombre de courbes sur cette fennettre; ...=les N flotants de cette etape
void affichage();
