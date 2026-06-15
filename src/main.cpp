#include <iostream>
#include "Parser.h"
#include "ModelBuilder.h"
#include "SolutionBuilder.h"
#include "Evaluator.h"

using namespace std;

int main(int argc, char* argv[])
{
  double ALPHA = 100.0;
  double BETA = 100.0;

    if (argc >= 3)
    {
      ALPHA = stod(argv[1]);
      BETA = stod(argv[2]);
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

  Model model = buildModel(instance);

  #ifdef DEBUG_MODE
    cout << "\n--- REPRESENTACION ---\n";

    cout << "Primer nodo: "
        << model.allNodes[0].id
        << " (" << model.allNodes[0].x
        << "," << model.allNodes[0].y << ")\n";

    cout << "Distancia 0 -> 1: " << model.dist[0][1] << '\n';

    cout << "\n--- MATRIZ DE DISTANCIAS ---\n";
    int n = model.allNodes.size();

    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n; j++)
      {
        cout << model.dist[i][j] << "\t";
      }
      cout << "\n";
    }

    cout << "Depositos en modelo: "
        << instance.depots.size() << '\n';

    cout << "--- FIN DEBUG ---\n\n";
  #endif

  Solution sol = buildRandomSolution(
    model,
    instance.vehiclesPerDepot,
    instance.capacity,
    42
  );

  #ifdef DEBUG_MODE
    cout << "\n--- SOLUCION INICIAL ---\n";

    for (size_t r = 0; r < sol.routes.size(); r++)
    {
      int load = 0;

      for (int c : sol.routes[r].customers)
      {
        load += model.allNodes[c].demand;
      }

      cout << "Ruta " << r
          << " | Depot: " << model.allNodes[sol.routes[r].depot].id
          << " | Carga: " << load
          << "/" << instance.capacity
          << " | Clientes: ";

      for (int c : sol.routes[r].customers)
      {
        cout << model.allNodes[c].id << " ";
      }

      cout << '\n';
    }
  #endif
  
  double value = evaluateSolution(sol, model, instance.capacity, ALPHA, BETA);

  cout << "Función de evaluación: " << value << endl;
  

  return 0;
}