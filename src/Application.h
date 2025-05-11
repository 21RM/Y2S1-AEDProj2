//
// Created by alexandre on 21-12-2023.
//

#ifndef AED_PROJ_2_APPLICATION_H
#define AED_PROJ_2_APPLICATION_H

#include "FileReader.h"
#include <vector>
#include "Airline.h"
#include "Airport.h"
#include "Graph.h"
#include <algorithm>
#include <memory>
#include <set>
#include <cmath>

/**
 * @brief Represents an application managing airports, airlines, and flight information.
 */
class Application {
    std::unique_ptr<std::unordered_map<std::string, Airport>> airports_; /**< Pointer to a vector containing airports. */
    std::unique_ptr<std::unordered_map<std::string, Airline>> airlines_;  /**< Pointer to a vector containing airlines. */
    std::unique_ptr<Graph> flightNetwork_;           /**< Pointer to a graph representing the flight network. */

public:
    /**
     * @brief Default constructor for the Application class.
     */
    Application();
    /**
     * @brief Get the airport with the specified code.
     * @param code The code of the airport to retrieve.
     * @return The Airport object corresponding to the provided code.
     * @throws std::out_of_range if the airport with the given code is not found.
     */
    Airport getAirport(const std::string &code) const;

    /**
     * @brief Get the airport with the specified name.
     * @param name The name of the airport to retrieve.
     * @return The Airport object corresponding to the provided name.
     * @throws std::out_of_range if the airport with the given name is not found.
     */
    Airport getAirportByName(const std::string &name) const;

    /**
     * @brief Get the airline with the specified code.
     * @param code The code of the airline to retrieve.
     * @return The Airline object corresponding to the provided code.
     * @throws std::out_of_range if the airline with the given code is not found.
     */
    Airline getAirline(const std::string &code) const;
    /**
     * @brief Get the graph representing the flight network.
     * @return Const reference to the flight network graph.
     */
    const Graph &getGraph();

    /**
     * @brief Get the unordered map of airports.
     * @return Const reference to the unordered map of airports.
     */
    const std::unordered_map<std::string, Airport> &getAirports();

    /**
     * @brief Get the unordered map of airlines.
     * @return Const reference to the unordered map of airlines.
     */
    const std::unordered_map<std::string, Airline> &getAirlines();

    //3.1
    /**
     * @brief Get the total count of airports in the application.
     * @return The number of airports in the application.
     */
    size_t getAirportCount();

    /**
     * @brief Get the total count of flights in the flight network.
     * @return The number of flights in the flight network.
     */
    size_t getFlightCount();

    //3.2
    /**
     * @brief Get the total count of outbound flights from a specific airport.
     * @param airportCode The code of the airport for which outbound flights are counted.
     * @return The number of outbound flights from the specified airport.
     * @throws std::out_of_range if the airport with the given code is not found.
     */
    size_t flightsOutboundOfAirport(const std::string &airportCode);

    /**
     * @brief Get the total count of airlines with outbound flights from a specific airport.
     * @param airportCode The code of the airport for which outbound airlines are counted.
     * @return The number of airlines with outbound flights from the specified airport.
     * @throws std::out_of_range if the airport with the given code is not found.
     */
    size_t airlinesOutboundOfAirport(const std::string &airportCode);

    //3.3
    /**
     * @brief Get the total count of outbound flights from all airports in a specific city.
     * @param city The name of the city for which outbound flights are counted.
     * @return The number of outbound flights from all airports in the specified city.
     */
    size_t outboundFlightsPerCity(const std::string &city);

    /**
     * @brief Get the total count of inbound flights to all airports in a specific city.
     * @param city The name of the city for which inbound flights are counted.
     * @return The number of inbound flights to all airports in the specified city.
     */
    size_t inboundFlightsPerCity(const std::string &city);

    /**
     * @brief Get the total count of flights (both inbound and outbound) to and from all airports in a specific city.
     * @param city The name of the city for which total flights are counted.
     * @return The number of total flights to and from all airports in the specified city.
     */
    size_t totalFlightsPerCity(const std::string &city);

    /**
     * @brief Get the total count of flights operated by a specific airline.
     * @param airlineCode The code of the airline for which flights are counted.
     * @return The number of flights operated by the specified airline.
     * @throws std::out_of_range if the airline with the given code is not found.
     */
    size_t flightsPerAirline(const std::string &airlineCode);


    //3.4
    /**
     * @brief Get the number of different countries an airport flies to.
     * @param airportCode The code of the airport for which the count is obtained.
     * @return The count of different countries the specified airport flies to.
     * @throws std::out_of_range if the airport with the given code is not found.
     */
    size_t numberOfDifferentCountriesAirportFliesTo(const std::string &airportCode);

    /**
     * @brief Get the number of different countries all airports in a city collectively fly to.
     * @param city The name of the city for which the count is obtained.
     * @return The count of different countries all airports in the specified city collectively fly to.
     */
    size_t numberOfDifferentCountriesCityFliesTo(const std::string &city);

    /**
     * @brief Get a vector of shared pointers to vertices representing airports in a specific city.
     * @param city The name of the city for which the airports are retrieved.
     * @return Vector of shared pointers to vertices representing airports in the specified city.
     */
    std::vector<std::shared_ptr<Vertex>> getAirportsInCity(const std::string &city);


    //3.5
    /**
     * @brief Get the number of different cities reachable from a specific airport.
     * @param airportCode The code of the airport for which the count is obtained.
     * @return The count of different cities reachable from the specified airport.
     * @throws std::out_of_range if the airport with the given code is not found.
     */
    size_t numberOfCitiesFromAirport(const std::string &airportCode);

    /**
     * @brief Get the number of different airports reachable from a specific airport.
     * @param airportCode The code of the airport for which the count is obtained.
     * @return The count of different airports reachable from the specified airport.
     * @throws std::out_of_range if the airport with the given code is not found.
     */
    size_t numberOfAirportsFromAirport(const std::string &airportCode);


    //3.6
    /**
     * @brief Get the number of different airports reachable from a specific airport within a given number of stops.
     * @param airportCode The code of the airport for which the count is obtained.
     * @param steps The maximum number of stops allowed in the search.
     * @return The count of different airports reachable from the specified airport within the given number of stops.
     * @throws std::out_of_range if the airport with the given code is not found.
     */
    size_t numberOfAirportsFromAirportWithStops(const std::string &airportCode, int steps);

    /**
     * @brief Get the number of different cities reachable from a specific airport within a given number of stops.
     * @param airportCode The code of the airport for which the count is obtained.
     * @param stops The maximum number of stops allowed in the search.
     * @return The count of different cities reachable from the specified airport within the given number of stops.
     * @throws std::out_of_range if the airport with the given code is not found.
     */
    size_t numberOfCitiesFromAirportWithStops(const std::string &airportCode, int stops);

    /**
     * @brief Get the number of different countries reachable from a specific airport within a given number of stops.
     * @param airportCode The code of the airport for which the count is obtained.
     * @param stops The maximum number of stops allowed in the search.
     * @return The count of different countries reachable from the specified airport within the given number of stops.
     * @throws std::out_of_range if the airport with the given code is not found.
     */
    size_t numberOfCountriesFromAirportWithStops(const std::string &airportCode, int stops);


    //3.7
    /**
     * @brief Get a vector of pairs representing trips with the greatest number of stops from a specific airport.
     * @param airportCode The code of the airport for which the trips are obtained.
     * @return Vector of pairs, where each pair consists of a pair of airports representing the trip and an integer
     *         representing the number of stops in that trip.
     * @throws std::out_of_range if the airport with the given code is not found.
     */
    std::vector<std::pair<std::pair<Airport, Airport>, int>> tripsWithGreatestNumberOfStopsFromAirport(const std::string &airportCode);

    /**
     * @brief Get a vector of pairs representing trips with the greatest number of stops across all airports.
     * @return Vector of pairs, where each pair consists of a pair of airports representing the trip and an integer
     *         representing the number of stops in that trip.
     */
    std::vector<std::pair<std::pair<Airport, Airport>, int>> tripsWithGreatestNumberOfStops();


    //3.8
    /**
     * @brief Get a vector of airports with the greatest traffic capacity.
     * @param k The number of airports to retrieve with the greatest traffic capacity.
     * @return Vector of airports with the greatest traffic capacity, limited to the top 'k' airports.
     */
    std::vector<Airport> airportsWithGreatestTrafficCapacity(size_t k) const;


    //3.9
    /**
     * @brief Get a set of essential airports in the flight network.
     * @return Set of airports considered essential for maintaining connectivity in the flight network.
     */
    std::set<Airport> essentialAirports() const;

    /**
     * @brief Find articulation points in the flight network.
     * @return Set of airports that, when removed, would disconnect the flight network or reduce its connectivity.
     */
    std::set<Airport> findArticulationPoints() const;


    //4.1
    /**
     * @brief Find the best flights from one airport to another considering forbidden airlines.
     * @param airport1 The code of the source airport.
     * @param airport2 The code of the destination airport.
     * @param forbidden A vector of forbidden airlines that should not be used in the search.
     * @return Vector of vectors, where each inner vector represents a possible route with a sequence of airports.
     */
    std::vector<std::vector<Airport>> bestFlightAirportToAirport(const std::string &airport1,
                                                                 const std::string &airport2,
                                                                 const std::vector<Airline> &forbidden);

    /**
     * @brief Find the best flights from an airport to a city considering forbidden airlines.
     * @param airport The code of the source airport.
     * @param city The name of the destination city.
     * @param forbidden A vector of forbidden airlines that should not be used in the search.
     * @return Vector of vectors, where each inner vector represents a possible route with a sequence of airports.
     */
    std::vector<std::vector<Airport>> bestFlightAirportToCity(const std::string &airport,
                                                              const std::string &city,
                                                              const std::vector<Airline> &forbidden);

    /**
     * @brief Find the best flights from an airport to a location (latitude, longitude) considering forbidden airlines.
     * @param airport The code of the source airport.
     * @param latitude The latitude of the destination location.
     * @param longitude The longitude of the destination location.
     * @param forbidden A vector of forbidden airlines that should not be used in the search.
     * @return Vector of vectors, where each inner vector represents a possible route with a sequence of airports.
     */
    std::vector<std::vector<Airport>> bestFlightAirportToLocation(const std::string &airport,
                                                                  const long double &latitude,
                                                                  const long double &longitude,
                                                                  const std::vector<Airline> &forbidden);

    /**
     * @brief Find the best flights from one airport to another without considering forbidden airlines.
     * @param airport1 The code of the source airport.
     * @param airport2 The code of the destination airport.
     * @return Vector of vectors, where each inner vector represents a possible route with a sequence of airports.
     */
    std::vector<std::vector<Airport>> bestFlightAirportToAirport(const std::string &airport1,
                                                                 const std::string &airport2);

    /**
     * @brief Find the best flights from an airport to a city without considering forbidden airlines.
     * @param airport The code of the source airport.
     * @param city The name of the destination city.
     * @return Vector of vectors, where each inner vector represents a possible route with a sequence of airports.
     */
    std::vector<std::vector<Airport>> bestFlightAirportToCity(const std::string &airport,
                                                              const std::string &city);

    /**
     * @brief Find the best flights from an airport to a location (latitude, longitude) without considering forbidden airlines.
     * @param airport The code of the source airport.
     * @param latitude The latitude of the destination location.
     * @param longitude The longitude of the destination location.
     * @return Vector of vectors, where each inner vector represents a possible route with a sequence of airports.
     */
    std::vector<std::vector<Airport>> bestFlightAirportToLocation(const std::string &airport,
                                                                  const long double &latitude,
                                                                  const long double &longitude);


    //4.2
    /**
     * @brief Find the best flights from one city to another considering forbidden airlines.
     * @param sourceCity The name of the source city.
     * @param destinationCity The name of the destination city.
     * @param forbidden A vector of forbidden airlines that should not be used in the search.
     * @return Vector of vectors, where each inner vector represents a possible route with a sequence of airports.
     */
    std::vector<std::vector<Airport>> bestFlightCityToCity(const std::string &sourceCity,
                                                           const std::string &destinationCity,
                                                           const std::vector<Airline> &forbidden);

    /**
     * @brief Find the best flights from a city to an airport considering forbidden airlines.
     * @param city The name of the source city.
     * @param airport The code of the destination airport.
     * @param forbidden A vector of forbidden airlines that should not be used in the search.
     * @return Vector of vectors, where each inner vector represents a possible route with a sequence of airports.
     */
    std::vector<std::vector<Airport>> bestFlightCityToAirport(const std::string &city,
                                                              const std::string airport,
                                                              const std::vector<Airline> &forbidden);

    /**
     * @brief Find the best flights from a city to a location (latitude, longitude) considering forbidden airlines.
     * @param city The name of the source city.
     * @param latitude The latitude of the destination location.
     * @param longitude The longitude of the destination location.
     * @param forbidden A vector of forbidden airlines that should not be used in the search.
     * @return Vector of vectors, where each inner vector represents a possible route with a sequence of airports.
     */
    std::vector<std::vector<Airport>> bestFlightCityToLocation(const std::string &city,
                                                               const long double &latitude,
                                                               const long double &longitude,
                                                               const std::vector<Airline> &forbidden);

    /**
     * @brief Find the best flights from one city to another without considering forbidden airlines.
     * @param sourceCity The name of the source city.
     * @param destinationCity The name of the destination city.
     * @return Vector of vectors, where each inner vector represents a possible route with a sequence of airports.
     */
    std::vector<std::vector<Airport>> bestFlightCityToCity(const std::string &sourceCity,
                                                           const std::string &destinationCity);

    /**
     * @brief Find the best flights from a city to an airport without considering forbidden airlines.
     * @param city The name of the source city.
     * @param airport The code of the destination airport.
     * @return Vector of vectors, where each inner vector represents a possible route with a sequence of airports.
     */
    std::vector<std::vector<Airport>> bestFlightCityToAirport(const std::string &city,
                                                              const std::string airport);

    /**
     * @brief Find the best flights from a city to a location (latitude, longitude) without considering forbidden airlines.
     * @param city The name of the source city.
     * @param latitude The latitude of the destination location.
     * @param longitude The longitude of the destination location.
     * @return Vector of vectors, where each inner vector represents a possible route with a sequence of airports.
     */
    std::vector<std::vector<Airport>> bestFlightCityToLocation(const std::string &city,
                                                               const long double &latitude,
                                                               const long double &longitude);


    //4.3
    /**
     * @brief Find the best flights from one location to another considering forbidden airlines.
     * @param sourceLatitude The latitude of the source location.
     * @param sourceLongitude The longitude of the source location.
     * @param destLatitude The latitude of the destination location.
     * @param destLongitude The longitude of the destination location.
     * @param forbidden A vector of forbidden airlines that should not be used in the search.
     * @return Vector of vectors, where each inner vector represents a possible route with a sequence of airports.
     */
    std::vector<std::vector<Airport>> bestFlightLocationToLocation(const long double &sourceLatitude,
                                                                   const long double &sourceLongitude,
                                                                   const long double &destLatitude,
                                                                   const long double &destLongitude,
                                                                   const std::vector<Airline> &forbidden);

    /**
     * @brief Find the best flights from a location to an airport considering forbidden airlines.
     * @param latitude The latitude of the source location.
     * @param longitude The longitude of the source location.
     * @param airport The code of the destination airport.
     * @param forbidden A vector of forbidden airlines that should not be used in the search.
     * @return Vector of vectors, where each inner vector represents a possible route with a sequence of airports.
     */
    std::vector<std::vector<Airport>> bestFlightLocationToAirport(const long double &latitude,
                                                                  const long double &longitude,
                                                                  const std::string &airport,
                                                                  const std::vector<Airline> &forbidden);

    /**
     * @brief Find the best flights from a location to a city considering forbidden airlines.
     * @param latitude The latitude of the source location.
     * @param longitude The longitude of the source location.
     * @param city The name of the destination city.
     * @param forbidden A vector of forbidden airlines that should not be used in the search.
     * @return Vector of vectors, where each inner vector represents a possible route with a sequence of airports.
     */
    std::vector<std::vector<Airport>> bestFlightLocationToCity(const long double &latitude,
                                                               const long double &longitude,
                                                               const std::string &city,
                                                               const std::vector<Airline> &forbidden);

    /**
     * @brief Find the best flights from one location to another without considering forbidden airlines.
     * @param sourceLatitude The latitude of the source location.
     * @param sourceLongitude The longitude of the source location.
     * @param destLatitude The latitude of the destination location.
     * @param destLongitude The longitude of the destination location.
     * @return Vector of vectors, where each inner vector represents a possible route with a sequence of airports.
     */
    std::vector<std::vector<Airport>> bestFlightLocationToLocation(const long double &sourceLatitude,
                                                                   const long double &sourceLongitude,
                                                                   const long double &destLatitude,
                                                                   const long double &destLongitude);

    /**
     * @brief Find the best flights from a location to an airport without considering forbidden airlines.
     * @param latitude The latitude of the source location.
     * @param longitude The longitude of the source location.
     * @param airport The code of the destination airport.
     * @return Vector of vectors, where each inner vector represents a possible route with a sequence of airports.
     */
    std::vector<std::vector<Airport>> bestFlightLocationToAirport(const long double &latitude,
                                                                  const long double &longitude,
                                                                  const std::string &airport);

    /**
     * @brief Find the best flights from a location to a city without considering forbidden airlines.
     * @param latitude The latitude of the source location.
     * @param longitude The longitude of the source location.
     * @param city The name of the destination city.
     * @return Vector of vectors, where each inner vector represents a possible route with a sequence of airports.
     */
    std::vector<std::vector<Airport>> bestFlightLocationToCity(const long double &latitude,
                                                               const long double &longitude,
                                                               const std::string &city);


    /**
     * @brief Find airports near a specific location defined by latitude and longitude.
     * @param latitude The latitude of the location.
     * @param longitude The longitude of the location.
     * @return Vector of airports near the specified location.
     */
    std::vector<Airport> findAirportsNearLocation(const long double &latitude, const long double &longitude);

    /**
     * @brief Get a list of airlines available for a flight between two airports.
     * @param source The source airport.
     * @param destination The destination airport.
     * @return Vector of airline names available for the specified flight.
     */
    std::vector<std::string> airlinesAvailableForFlight(const Airport &source, const Airport &destination) const;
};


#endif //AED_PROJ_2_APPLICATION_H