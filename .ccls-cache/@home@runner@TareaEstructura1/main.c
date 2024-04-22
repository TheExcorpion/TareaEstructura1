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

// Función para limpiar la pantall
void limpiarPantalla() { system("clear"); }

void strMay(char *cadena) 
{
  int i = 0;
  while (cadena[i] != '\0')
    {
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

void ordenarPrioridad(List *listaPacientes)
{
    bool intercambio;
    bool igualPrioridad;
    do {
      intercambio = false;
      igualPrioridad = false;

      tipoPaciente *pacienteActual = list_first(listaPacientes);
      tipoPaciente *siguientePaciente = list_next(listaPacientes);
      while (siguientePaciente != NULL) {
        if (pacienteActual->prioridad < siguientePaciente->prioridad)
        {
          tipoPaciente temp = *pacienteActual;
          *pacienteActual = *siguientePaciente;
          *siguientePaciente = temp;
          intercambio = true;
        } else if (pacienteActual->prioridad == siguientePaciente->prioridad &&
                   pacienteActual->hora > siguientePaciente->hora)
        {
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

void registrar_paciente(List *pacientes)
{
  printf("\nRegistrar nuevo paciente \n");
  tipoPaciente *paciente = malloc(sizeof(tipoPaciente));
  if (paciente == NULL)
  {
    printf("ERROR DE MEMORIA");
    return;
  }

  printf("Ingresa el nombre del paciente: \n");
  getchar();
  char nombreIngresado[MAX];
  scanf(" %[^\n]", nombreIngresado);
  strMay(nombreIngresado);

  bool encontPaciente = false;
  tipoPaciente *pacienteActual = list_first(listaPacientes);
  while (pacienteActual != NULL && !encontPaciente) 
  {
    if (strcmp(pacienteActual->nombre, nombreIngresado) == 0)
    {
      puts("El paciente ya se encuentra registrado");
      encontPaciente = true;
      return;
    } else
      pacienteActual = list_next(listaPacientes);
  }
  if (pacienteActual == NULL)
  { 
    strcpy(paciente->nombre, nombreIngresado);
  }
  printf("Ingresa la edad del paciente: \n");
  scanf("%i", &paciente->edad);
  printf("Ingresa el sintoma del paciente:\n");
  getchar();
  scanf(" %[^\n]", paciente->sintoma);
  strMay(paciente->sintoma);
  strMay(paciente->nombre);
  paciente->prioridad = 1; 
  time(&paciente->hora);
  list_pushBack(listaPacientes, paciente);
  totalPacientes += 1;
  ordenarPrioridad(listaPacientes);
  }
}

void mostrar_lista_pacientes(List *pacientes) {
  printf("Pacientes en espera: \n");

}

int main() {
  char opcion;
  List *pacientes =
      list_create(); 

  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion); 

    switch (opcion) {
    case '1':
      registrar_paciente(pacientes);
      break;
    case '2':

      break;
    case '3':
      mostrar_lista_pacientes(pacientes);
      break;
    case '4':

      break;
    case '5':

      break;
    case '6':
      puts("Saliendo del sistema de gestión hospitalaria...");
      break;
    default:
      puts("Opción no válida. Por favor, intente de nuevo.");
    }
    presioneTeclaParaContinuar();

  } while (opcion != '6');


  list_clean(pacientes);

  return 0;
}
