#ifndef __UTILS_H__
#define __UTILS_H__

#define TYPE Action*

/**
 * @brief Exit le programme en affichant le message msg
 * 
 * @param msg Message à afficher
 * @param exit_val Valeur de sortie
 */
void error(char* msg, int exit_val);

/**
 * @brief Test si l'argument est NULL et exit si oui
 * 
 * @param arg argument à tester
 * @param fun_name Nom de la fonction appelante
 */
void testArgNull(void* arg, char* fun_name);



#endif
