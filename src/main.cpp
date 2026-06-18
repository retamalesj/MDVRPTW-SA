#include <iostream>
#include "Parser.h"
#include "InstanceProcessor.h"
#include "SolutionBuilder.h"
#include "Evaluator.h"
#include "SolutionUtils.h"
#include "SA.h"

using namespace std;

int main(int argc, char* argv[])
{
  double ALPHA = 100.0;
  double BETA = 100.0;
  unsigned int SEED = 42;

  if (argc >= 4)
  {
    ALPHA = stod(argv[1]);
    BETA = stod(argv[2]);
    SEED = (unsigned)stoul(argv[3]);
  }

  Instance instance = readInstance("./Instancias/instancias_25/C101.txt");

  #ifdef DEBUG_MODE
    cout << "Instancia: " << instance.name << '\n';
    cout << "Cantidad de depositos: " << instance.depots.size() << '\n';
    cout << "Cantidad de clientes: " << instance.customers.size() << '\n';
    cout << "Vehiculos por deposito: " << instance.vehiclesPerDepot << '\n';
    cout << "Capacidad: " << instance.capacity << '\n';

    cout << "\n=== DEPOSITOS ===\n";

    for (const auto &depot : instance.depots)
    {
      cout
          << depot.id << " "
          << depot.x << " "
          << depot.y << " "
          << depot.demand << " "
          << depot.e << " "
          << depot.l << " "
          << depot.serviceTime << '\n';
    }

    cout << "\n=== CLIENTES ===\n";

    for (const auto &customer : instance.customers)
    {
      cout
          << customer.id << " "
          << customer.x << " "
          << customer.y << " "
          << customer.demand << " "
          << customer.e << " "
          << customer.l << " "
          << customer.serviceTime << '\n';
    }
  #endif

  process(instance);

  #ifdef DEBUG_MODE
    cout << "\n--- INSTANCIA PROCESADA ---\n";

    cout << "Primer nodo: "
        << instance.allNodes[0].id
        << " (" << instance.allNodes[0].x
        << "," << instance.allNodes[0].y << ")\n";

    cout << "Distancia 0 -> 1: " << instance.dist[0][1] << '\n';

    cout << "\n--- MATRIZ DE DISTANCIAS ---\n";
    int n = instance.allNodes.size();

    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n; j++)
      {
        cout << instance.dist[i][j] << "\t";
      }
      cout << "\n";
    }

    cout << "Depositos en modelo: " << instance.depots.size() << '\n';
  #endif

  Solution initialSolution = buildRandomSolution(
    instance,
    SEED
  );

  #ifdef DEBUG_MODE
    cout << "\n--- SOLUCION INICIAL ---\n";

    for (size_t r = 0; r < sol.routes.size(); r++)
    {
      int load = 0;

      for (int c : sol.routes[r].customers)
      {
        load += instance.allNodes[c].demand;
      }

      cout << "Ruta " << r
          << " | Depot: " << instance.allNodes[sol.routes[r].depot].id
          << " | Carga: " << load
          << "/" << instance.capacity
          << " | Clientes: ";

      for (int c : sol.routes[r].customers)
      {
        cout << instance.allNodes[c].id << " ";
      }

      cout << '\n';
    }

    cout << "\n--- REPRESENTACION ---\n";

    for (const Route &route : sol.routes)
{
    cout << "{ depot = "
         << route.depot
         << ", customers = { ";

    for (size_t i = 0; i < route.customers.size(); i++)
    {
        cout << route.customers[i];

        if (i < route.customers.size() - 1)
            cout << ", ";
    }

    cout << " } }\n";
}

  #endif
  
  Solution Sbest = simulatedAnnealing(
    initialSolution,
    instance,
    ALPHA,
    BETA,
    100000,
    50,
    SEED
  );
  
  writeSolution(SEED, initialSolution, instance, ALPHA, BETA);

  writeSolution(SEED, Sbest, instance, ALPHA, BETA);

  return 0;
}