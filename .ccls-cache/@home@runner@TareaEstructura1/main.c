#include "tdas/list.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 50

typedef struct tipoPaciente {
  int prioridad;
  char nombre[MAX];
  int edad;
  char sintoma[MAX];
  time_t hora;
} tipoPaciente;

int totalPacientes = 0;
void limpiarPantalla() { system("clear"); }

void strMay(char *cadena) {
  int i = 0;
  while (cadena[i] != '\0') {
    cadena[i] = toupper(cadena[i]);
    i++;
  }
}

void presioneTeclaParaContinuar() {
  puts("Presione una tecla para continuar...");
  getchar();
  getchar();
}
// Menú principal
void mostrarMenuPrincipal() {
  limpiarPantalla();
  puts("========================================");
  puts("     Sistema de Gestión Hospitalaria");
  puts("========================================");

  puts("1) Registrar paciente");
  puts("2) Asignar prioridad a paciente");
  puts("3) Mostrar lista de espera");
  puts("4) Atender al siguiente paciente");
  puts("5) Mostrar pacientes por prioridad");
  puts("6) Salir");
}

void ordenarPrioridad(List *listaPacientes) {
  bool intercambio;
  bool igualPrioridad;
  do {
    intercambio = false;
    igualPrioridad = false;

    tipoPaciente *pacienteActual = list_first(listaPacientes);
    tipoPaciente *siguientePaciente = list_next(listaPacientes);
    while (siguientePaciente != NULL) {
      if (pacienteActual->prioridad < siguientePaciente->prioridad) {
        tipoPaciente temp = *pacienteActual;
        *pacienteActual = *siguientePaciente;
        *siguientePaciente = temp;
        intercambio = true;
      } else if (pacienteActual->prioridad == siguientePaciente->prioridad &&
                 pacienteActual->hora > siguientePaciente->hora) {
        tipoPaciente temp = *pacienteActual;
        *pacienteActual = *siguientePaciente;
        *siguientePaciente = temp;
        intercambio = true;
      }
      pacienteActual = siguientePaciente;
      siguientePaciente = list_next(listaPacientes);
    }
  } while (intercambio);
}

void registrar_paciente(List *pacientes) {
  printf("\nRegistrar nuevo paciente \n");
  tipoPaciente *paciente = malloc(sizeof(tipoPaciente));
  if (paciente == NULL) {
    printf("ERROR DE MEMORIA");
    return;
  }

  printf("Por favor, introduce el nombre del paciente: \n");
  getchar();
  char nombreIngresado[MAX];
  scanf(" %[^\n]", nombreIngresado);
  strMay(nombreIngresado);

  bool encontPaciente = false;
  tipoPaciente *pacienteActual = list_first(pacientes);
  while (pacienteActual != NULL && !encontPaciente) {
    if (strcmp(pacienteActual->nombre, nombreIngresado) == 0) {
      puts("El paciente ya se encuentra en el sistema");
      encontPaciente = true;
      return;
    } else
      pacienteActual = list_next(pacientes);
  }
  if (pacienteActual == NULL) {
    strcpy(paciente->nombre, nombreIngresado);
  }
  printf("Añadir la edad del paciente: \n");
  scanf("%i", &paciente->edad);
  printf("Añadir el sintoma del paciente:\n");
  getchar();
  scanf(" %[^\n]", paciente->sintoma);
  strMay(paciente->sintoma);
  strMay(paciente->nombre);
  paciente->prioridad = 1;
  time(&paciente->hora);
  list_pushBack(pacientes, paciente);
  totalPacientes += 1;
  ordenarPrioridad(pacientes);
}

void mostrar_lista_pacientes(List *listaPacientes)
{
  printf("Pacientes en lista de espera: \n");
  tipoPaciente *pacienteActual = list_first(listaPacientes);
  if (pacienteActual == NULL) {
    puts("No se encutran pacientes registrados");
    return;
  }
  puts("=============================================================================");
  printf("|                          Pacientes en lista de espera: %d                     "
         "      |\n",
         totalPacientes);
  puts("=============================================================================");
  printf("| %-20s | %-10s | %-25s | %-8s |\n", "Nombres", "Edad", "Sintoma",
         "Prioridad");
  puts("=============================================================================");
  while (pacienteActual != NULL) {
    char nombre[MAX];
    strcpy(nombre, pacienteActual->nombre);
  
    int edad = pacienteActual->edad;
  
    char sintoma[MAX];
    strcpy(sintoma, pacienteActual->sintoma);
  
    int prioridad = pacienteActual->prioridad;
  
    printf("| %-20s | %-10d | %-25s |", nombre, edad, sintoma);
    if (prioridad == 1)
      printf(" %-9s |\n", "Baja");
    else if (prioridad == 2)
      printf(" %-9s |\n", "Media");
    else if (prioridad == 3)
      printf(" %-9s |\n", "Alto");
  
    pacienteActual = list_next(listaPacientes);
  }
}

int contador_prioridad(List *listaPacientes, int prioridad) 
{
  int cont = 0;
  tipoPaciente *pacienteActual = list_first(listaPacientes);
  while (pacienteActual != NULL)
  {
    if (pacienteActual->prioridad == prioridad)
    {
      cont += 1;
      pacienteActual = list_next(listaPacientes);
    }
  }
  return cont;
}

void mostrar_lista_prioridad(List *listaPacientes) {
  int prioriIngresada;
  bool validPriori = false;

  while (!validPriori) // Bucle solamente para definir y validar el dato
                       // nuevaPrioridad
  {
    printf("\nIngrese el numero de la prioridad que desea mostrar: \n");
    printf("1) Baja\n");
    printf("2) Media\n");
    printf("3) Alta\n");
    scanf("%i", &prioriIngresada);
    if (prioriIngresada == 1 || prioriIngresada == 2 || prioriIngresada == 3)
      validPriori = true;
    else
      puts("Prioridad no valida, ingrese nuevamente");
  }

  int cantPrioridad = contador_prioridad(listaPacientes, prioriIngresada);

  tipoPaciente *pacienteActual = list_first(listaPacientes);

  if (pacienteActual == NULL || cantPrioridad == 0) {
    puts("No hay pacientes registrados");
    return;
  }

  puts("======================================================================="
       "======");
  printf("|                          Pacientes en espera: %d                   "
         "        |\n",
         cantPrioridad);
  puts("======================================================================="
       "======");
  printf("| %-20s | %-10s | %-25s | %-8s |\n", "Nombres", "Edad", "Sintoma",
         "Prioridad");
  puts("======================================================================="
       "======");
  while (pacienteActual != NULL) {
    char nombre[MAX];
    strcpy(nombre, pacienteActual->nombre);

    int edad = pacienteActual->edad;

    char sintoma[MAX];
    strcpy(sintoma, pacienteActual->sintoma);

    int prioridad = pacienteActual->prioridad;
    if (prioridad == prioriIngresada) {
      printf("| %-20s | %-10d | %-25s |", nombre, edad, sintoma);
      if (prioridad == 1)
        printf(" %-9s |\n", "Baja");
      else if (prioridad == 2)
        printf(" %-9s |\n", "Media");
      else if (prioridad == 3)
        printf(" %-9s |\n", "Alto");
    }

    pacienteActual = list_next(listaPacientes);
  }
}

void asignar_prioridad(List *listaPacientes) {
  if (totalPacientes == 0) {
    puts("No hay pacientes registrados");
    return;
  }
  
  printf("Ingrese el nombre del paciente del cual quiere cambiar prioridad:\n");
  getchar();
  char nombrePaciente[MAX];
  scanf(" %[^\n]", nombrePaciente);
  strMay(nombrePaciente);

  tipoPaciente *pacienteActual = list_first(listaPacientes);

  while (pacienteActual != NULL)
  {
    if (strcmp(pacienteActual->nombre, nombrePaciente) == 0) {
      break;
    } else
      pacienteActual = list_next(listaPacientes);
    if (pacienteActual == NULL) {
      puts("No se ha encontrado al paciente");
      return;
    }
  }
  printf("El paciente tiene prioridad ");
  if (pacienteActual->prioridad == 1)
    printf("baja");
  else if (pacienteActual->prioridad == 2)
    printf("media");
  else if (pacienteActual->prioridad == 3)
    printf("alta");
  int nuevaPrioridad;
  bool validPriori = false;

  while (!validPriori) 
  {
    printf("\nIngrese el numero de la nueva prioridad: \n");
    printf("1) Baja\n");
    printf("2) Media\n");
    printf("3) Alta\n");
    scanf("%i", &nuevaPrioridad);
    if (nuevaPrioridad == 1 || nuevaPrioridad == 2 || nuevaPrioridad == 3)
      validPriori = true;
    else
      puts("Prioridad no valida, ingrese nuevamente");
  }

  bool cambGuard = false;
  if (pacienteActual->prioridad == nuevaPrioridad) {
    puts("No se ha hecho ningun cambio");
  }

  else {
    pacienteActual->prioridad = nuevaPrioridad;
    puts("Se han guardado los cambios");
  }

  ordenarPrioridad(listaPacientes);
}

void siguiente_paciente(List *listaPacientes) {
  puts("¿Desea pasar al siguiente en la lista de espera?");
  puts("Y/N");
  getchar();

  char confirmacion;
  bool confirmado = false;

  while (!confirmado) {
    scanf(" %c", &confirmacion);
    confirmacion = toupper(confirmacion);

    if (confirmacion != 'Y' && confirmacion != 'N') {
      puts("Respuesta no valida");
      puts("Intente de nuevo:");
      while (getchar() != '\n');

    } else if (confirmacion == 'N') {
      puts("Acción cancelada");
      return;
    } else {
      confirmado = true;
    }
  }
  tipoPaciente *pacienteActual = list_first(listaPacientes);
  if (pacienteActual == NULL)
  { 
    puts("No hay pacientes registrados");
    return;
  }
  puts("\nPaciente atendido:");
  printf("Nombre Paciente: %s\n", pacienteActual->nombre);
  printf("Edad: %i\n", pacienteActual->edad);
  printf("Sintoma: %s\n", pacienteActual->sintoma);

  list_popFront(listaPacientes);
  totalPacientes -= 1;
  puts("Se ha continuado con el siguiente paciente");
  printf("Pacientes restantes: %i\n", totalPacientes);
}
int main() {
  char opcion;
  List *listaPacientes = list_create();
  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion);
    switch (opcion) {
    case '1':
      registrar_paciente(listaPacientes);
      break;
    case '2':
      asignar_prioridad(listaPacientes);
      break;
    case '3':
      mostrar_lista_pacientes(listaPacientes);
      break;
    case '4':
      siguiente_paciente(listaPacientes);
      break;
    case '5':
      mostrar_lista_prioridad(listaPacientes);
      break;
    case '6':
      puts("Saliendo del sistema de gestión hospitalaria...");
      break;
    default:
      puts("Opción no válida. Por favor, intente de nuevo.");
    }
    presioneTeclaParaContinuar();

  } while (opcion != '6');
  list_clean(listaPacientes);
  return 0;
}