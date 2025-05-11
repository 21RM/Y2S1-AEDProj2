#include "Application.h"
#include "Interface.h"

int main() {
    Interface anInterface;
    anInterface.run();

    /*
    Application app;

    auto start = std::chrono::high_resolution_clock::now();
    for (const auto &v : app.bestFlightAirportToAirport("OPO", "BOS")){
        for (const auto &flight : v) {
            std::cout << flight.getCode() << std::endl;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << duration.count() << "\n";
    return 0;*/
}
