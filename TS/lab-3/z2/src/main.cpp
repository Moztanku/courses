#include "Simulation.hpp"

auto main() -> int 
{
    Simulation sim(20, 1000.0 / 60.0);

    sim.simulate(1000);    

    return 0;
}