//
// Created by alexandre on 21-12-2023.
//

#include "Application.h"
#include <chrono>

Application::Application()
        : airports_(std::make_unique<std::unordered_map<std::string, Airport>>()),
          airlines_(std::make_unique<std::unordered_map<std::string, Airline>>()),
          flightNetwork_(std::make_unique<Graph>())
{
    FileReader airlineData("../dataset/airlines.csv");
    FileReader airportsData("../dataset/airports.csv");
    FileReader flightsData("../dataset/flights.csv");

    for (const auto &line : airportsData.getData()) {
        airports_->insert({line.at(0), Airport(line.at(0), line.at(1), line.at(2), line.at(3), line.at(4), line.at(5))});
    }
    for (const auto &line : airlineData.getData()) {
        airlines_->insert({line.at(0), Airline(line.at(0), line.at(1), line.at(2), line.at(3))});
    }

    for (const auto& airport : *airports_) {
        flightNetwork_->addVertex(airport.second);
    }

    auto start = std::chrono::high_resolution_clock::now();
    for (const auto &line : flightsData.getData()) {
        auto sourceAirportCode = line.at(0);
        auto destinationAirportCode = line.at(1);
        auto airlineCode = line.at(2);

        Airport sourceAirport = getAirport(sourceAirportCode);
        Airport destinationAirport = getAirport(destinationAirportCode);
        Airline airline = getAirline(airlineCode);

        auto source = flightNetwork_->findVertex(sourceAirport);
        auto dest = flightNetwork_->findVertex(destinationAirport);

        source->getInfo().setTrafficCapacity(source->getInfo().getTrafficCapacity()+1);
        dest->getInfo().setTrafficCapacity(dest->getInfo().getTrafficCapacity()+1);

        flightNetwork_->addEdge(sourceAirport, destinationAirport, 0, airline);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << duration.count() << "\n";

}

Airport Application::getAirport(const std::string &code) const {
    auto it = airports_->find(code);
    if (it == airports_->end()) return {};
    return it->second;
}

Airline Application::getAirline(const std::string &code) const {
    auto it = airlines_->find(code);
    if (it == airlines_->end()) return {};
    return it->second;
}

const Graph &Application::getGraph() {
    return *flightNetwork_;
}

const std::unordered_map<std::string, Airport> &Application::getAirports() {
    return *airports_;
}

const std::unordered_map<std::string, Airline> &Application::getAirlines() {
    return *airlines_;
}

size_t Application::getAirportCount() {
    return airports_->size();
}

size_t Application::getFlightCount() {
    return flightNetwork_->getNumEdge();
}

size_t Application::flightsOutboundOfAirport(const string &airportCode) {
    auto airportObj = getAirport(airportCode);
    auto airport = flightNetwork_->findVertex(airportObj);

    return airport->getAdj().size();
}

size_t Application::airlinesOutboundOfAirport(const std::string &airportCode) {
    auto airportObj = getAirport(airportCode);
    auto airport = flightNetwork_->findVertex(airportObj);

    return airport->getNumDifferentAirlines();
}

std::vector<std::shared_ptr<Vertex>> Application::getAirportsInCity(const std::string &city){
    auto vertexVector = flightNetwork_->getVertexSet();

    std::vector<std::shared_ptr<Vertex>> airportsInCity;

    for (const auto& p : vertexVector) {
        if (p.second->getInfo().getCity() == city) {
            airportsInCity.push_back(p.second);
        }
    }

    return airportsInCity;
}

size_t Application::outboundFlightsPerCity(const std::string &city) {

    std::vector<std::shared_ptr<Vertex>> airportsInCity = getAirportsInCity(city);

    size_t res = 0;

    for (const auto& vertex : airportsInCity) {
        res += vertex->getAdj().size();
    }

    return res;
}

size_t Application::inboundFlightsPerCity(const std::string &city) {
    auto vertexVector = flightNetwork_->getVertexSet();

    size_t res = 0;

    for (auto p : vertexVector) {
        if (p.second->getInfo().getCity() == city) continue;    //todo

        for (const Edge &e : p.second->getAdj()) {
            if (e.getDest()->getInfo().getCity() == city) ++res;
        }
    }
    return res;
}

size_t Application::totalFlightsPerCity(const std::string &city) {
    return inboundFlightsPerCity(city) + outboundFlightsPerCity(city);
}

size_t Application::flightsPerAirline(const std::string &airlineCode) {
    size_t res = 0;
    auto vertexVector = flightNetwork_->getVertexSet();

    for (const auto& p : vertexVector) {
        for (const Edge &edge : p.second->getAdj()) {
            if (edge.getAirline().getCode() == airlineCode) ++res;
        }
    }

    return res;
}

size_t Application::numberOfDifferentCountriesAirportFliesTo(const std::string &airportCode) {
    auto airportObj = getAirport(airportCode);
    auto airport = flightNetwork_->findVertex(airportObj);

    unordered_set<std::string> countries;

    size_t res = 0;

    for (const Edge& destinyAirports : airport->getAdj()){
        countries.insert(destinyAirports.getDest()->getInfo().getCountry());
    }

    res += countries.size();

    return res;
}

size_t Application::numberOfDifferentCountriesCityFliesTo(const std::string &city){
    std::vector<std::shared_ptr<Vertex>> airportsInCity = getAirportsInCity(city);

    unordered_set<std::string> countries;

    size_t res = 0;
    for (const auto& airport : airportsInCity) {
        for (const Edge& destinyAirports : airport->getAdj()){
            countries.insert(destinyAirports.getDest()->getInfo().getCountry());
        }
    }

    res += countries.size();

    return res;
}

size_t Application::numberOfCitiesFromAirport(const std::string &airportCode){
    auto airportObj = getAirport(airportCode);
    auto airport = flightNetwork_->findVertex(airportObj);

    unordered_set<std::string> cities;

    for (const Edge& edge : airport->getAdj()){
        cities.insert(edge.getDest()->getInfo().getCity());
    }

    return cities.size();
}

size_t Application::numberOfAirportsFromAirportWithStops(const std::string &airportCode, int stops){
    ++stops;
    auto airportObj = getAirport(airportCode);
    auto airport = flightNetwork_->findVertex(airportObj);

    return flightNetwork_->bfsWithSteps(airport->getInfo(), stops).size() - 1;
}

size_t Application::numberOfCitiesFromAirportWithStops(const std::string &airportCode, int stops){
    ++stops;
    auto airportObj = getAirport(airportCode);
    auto airport = flightNetwork_->findVertex(airportObj);

    unordered_set<std::string> cities;

    std::vector airportsInRange = flightNetwork_->bfsWithSteps(airport->getInfo(), stops);
    airportsInRange.erase(airportsInRange.begin());

    for (const Airport& airport1 : airportsInRange){
        cities.insert(airport1.getCity());
    }

    return cities.size();
}

size_t Application::numberOfCountriesFromAirportWithStops(const std::string &airportCode, int stops){
    ++stops;
    auto airportObj = getAirport(airportCode);
    auto airport = flightNetwork_->findVertex(airportObj);

    unordered_set<std::string> countries;

    std::vector airportsInRange = flightNetwork_->bfsWithSteps(airport->getInfo(), stops);
    airportsInRange.erase(airportsInRange.begin());

    for (const Airport& airport1 : airportsInRange){
        countries.insert(airport1.getCountry());
    }

    return countries.size();
}

std::vector<std::pair<std::pair<Airport, Airport>, int>> Application::tripsWithGreatestNumberOfStopsFromAirport(const std::string &airportCode){
    auto airportObj = getAirport(airportCode);
    auto airport = flightNetwork_->findVertex(airportObj);

    std::vector<std::pair<Airport, int>> mostStops = flightNetwork_->bfsFurthestVertices(airport->getInfo());
    std::vector<std::pair<std::pair<Airport, Airport>, int>> trips;
    trips.reserve(mostStops.size());
    for (const auto& dest_airport : mostStops){
        trips.push_back({{airportObj, dest_airport.first}, dest_airport.second});
    }
    return trips;
}

std::vector<std::pair<std::pair<Airport, Airport>, int>> Application::tripsWithGreatestNumberOfStops(){
    int max_length = INT8_MIN;

    std::vector<std::pair<std::pair<Airport, Airport>, int>> longest_trips;

    for (const auto& vertex : flightNetwork_->getVertexSet()){
        std::vector<std::pair<std::pair<Airport, Airport>, int>> trips = tripsWithGreatestNumberOfStopsFromAirport(vertex.second->getInfo().getCode());
        if (trips[0].second > max_length){
            max_length = trips[0].second;
            longest_trips.clear();
        }
        if (trips[0].second == max_length){
            for (const auto& trip : trips){
                longest_trips.push_back(trip);
            }
        }
    }
    return longest_trips;
}

size_t Application::numberOfAirportsFromAirport(const string &airportCode) {
    auto airportObj = getAirport(airportCode);
    auto airport = flightNetwork_->findVertex(airportObj);

    std::set<Airport> airports;

    for (const Edge& edge : airport->getAdj()){
        airports.insert(edge.getDest()->getInfo());
    }

    return airports.size();
}

std::vector<Airport> Application::airportsWithGreatestTrafficCapacity(size_t k) const{
    if (k > 3019){
        k = 3019;
    }
    auto copyMap(flightNetwork_->getVertexSet());
    vector<std::shared_ptr<Vertex>> copy;
    copy.reserve(copyMap.size());
    for (const auto& p : copyMap) copy.push_back(p.second);

    std::sort(copy.begin(), copy.end(), [](const std::shared_ptr<Vertex>& obj1, const std::shared_ptr<Vertex>& obj2) {
        return obj1->getInfo().getTrafficCapacity() > obj2->getInfo().getTrafficCapacity();
    });

    std::vector<Airport> res;

    for (size_t i = 0; i < k; i++) {
        res.push_back(copy.at(i)->getInfo());
    }

    return res;
}

void dfsArt(const std::shared_ptr<Vertex>& v, int &index, std::set<Airport> &articulationPoints) {
    v->setVisited(true);
    v->setNum(index);
    v->setLow(index);
    index++;

    int children = 0;

    for (auto &e : v->getAdj()) {
        auto w = e.getDest();

        if (!w->isVisited()) {
            children++;
            dfsArt(w, index, articulationPoints);
            v->setLow(min(v->getLow(), w->getLow()));

            if (v->getNum() == 0 && children > 1) {
                // Special case for the root of DFS tree
                articulationPoints.insert(v->getInfo());
            } else if (v->getNum() != 0 && w->getLow() >= v->getNum()) {
                // Regular articulation point
                articulationPoints.insert(v->getInfo());
            }
        } else if (w->getNum() < v->getNum()) {
            // Back edge, update low value
            v->setLow(min(v->getLow(), w->getNum()));
        }
    }
}

std::set<Airport> Application::findArticulationPoints() const{
    std::set<Airport> articulationPoints;
    int index = 0;

    for (auto &v : flightNetwork_->getVertexSet()) {
        v.second->setVisited(false);
        v.second->setNum(0);
    }

    for (auto &v : flightNetwork_->getVertexSet()) {
        if (!v.second->isVisited()) {
            dfsArt(v.second, index, articulationPoints);
        }
    }

    return articulationPoints;
}

std::set<Airport> Application::essentialAirports() const {
    std::set res = findArticulationPoints();
    return res;
}

std::vector<std::vector<Airport>>
Application::bestFlightAirportToAirport(const string &airport1, const string &airport2) {
    Airport airport1Obj;
    Airport airport2Obj;
    if (airport1.length() == 3) {
        auto airportObj = getAirport(airport1);
        airport1Obj = airportObj;
    } else {
        auto airportObj = getAirportByName(airport1);
        airport1Obj = airportObj;
    }

    if (airport2.length() == 3) {
        auto airportObj = getAirport(airport2);
        airport2Obj = airportObj;
    } else {
        auto airportObj = getAirportByName(airport2);
        airport2Obj = airportObj;
    }
    auto vec = flightNetwork_->bfsShortestPath(airport1Obj, airport2Obj);

    return vec;
}

Airport Application::getAirportByName(const string &name) const {
    for (const auto &airport : *airports_) {
        if (airport.second.getName() == name) {
            return airport.second;
        }
    }
    return {};
}

std::vector<std::string>
Application::airlinesAvailableForFlight(const Airport &source, const Airport &destination) const {
    auto sourceVertex = flightNetwork_->findVertex(source);

    std::vector<std::string> res;

    for (const auto &e : sourceVertex->getAdj()) {
        if (e.getDest()->getInfo() == destination) {
            res.push_back(e.getAirline().getCode());
        }
    }

    return res;
}

std::vector<std::vector<Airport>>
Application::bestFlightCityToCity(const string &sourceCity, const string &destinationCity) {
    auto airportsInSourceCity = getAirportsInCity(sourceCity);
    auto airportsInDestinationCity = getAirportsInCity(destinationCity);

    std::vector<std::vector<Airport>> res;

    for (const auto &sourceAirport : airportsInSourceCity) {
        for (const auto &destinationAirport : airportsInDestinationCity) {
            for (const auto &i : flightNetwork_->bfsShortestPath(sourceAirport, destinationAirport)) {
                res.push_back(i);
            }
        }
    }

    return res;
}

std::vector<std::vector<Airport>>
Application::bestFlightAirportToCity(const string &airport, const string &city) {
    Airport airport1Obj;
    if (airport.length() == 3) {
        auto airportObj = getAirport(airport);
        airport1Obj = airportObj;
    } else {
        auto airportObj = getAirportByName(airport);
        airport1Obj = airportObj;
    }

    auto airportVertex = flightNetwork_->findVertex(airport1Obj);
    auto airportsInDestinationCity = getAirportsInCity(city);

    std::vector<std::vector<Airport>> res;
    for (const auto &destinationAirport : airportsInDestinationCity) {
        for (const auto &i : flightNetwork_->bfsShortestPath(airportVertex, destinationAirport)) {
            res.push_back(i);
        }
    }

    return res;
}

std::vector<std::vector<Airport>>
Application::bestFlightCityToAirport(const string &city, const std::string airport) {
    Airport airport1Obj;
    if (airport.length() == 3) {
        auto airportObj = getAirport(airport);
        airport1Obj = airportObj;
    } else {
        auto airportObj = getAirportByName(airport);
        airport1Obj = airportObj;
    }

    auto airportVertex = flightNetwork_->findVertex(airport1Obj);
    auto airportsInSourceCity = getAirportsInCity(city);

    std::vector<std::vector<Airport>> res;
    for (const auto &sourceAirport : airportsInSourceCity) {
        for (const auto &i : flightNetwork_->bfsShortestPath(sourceAirport, airportVertex)) {
            res.push_back(i);
        }
    }

    return res;
}

std::vector<std::vector<Airport>>
Application::bestFlightLocationToLocation(const long double &sourceLatitude, const long double &sourceLongitude,
                                          const long double &destLatitude, const long double &destLongitude) {

    auto sourceAirports = findAirportsNearLocation(sourceLatitude, sourceLongitude);
    auto destinationAirports = findAirportsNearLocation(destLatitude, destLongitude);

    std::vector<std::vector<Airport>> res;

    for (const auto &sourceAirport : sourceAirports) {
        for (const auto &destinationAirport : destinationAirports) {
            for (const auto &i : flightNetwork_->bfsShortestPath(sourceAirport, destinationAirport)) {
                res.push_back(i);
            }
        }
    }

    return res;
}

std::vector<Airport> Application::findAirportsNearLocation(const long double &latitude, const long double &longitude) {
    std::vector<Airport> nearbyAirports;

    long double min_dist = INT16_MAX;

    for (const auto &airport : *airports_) {
        long double latDiff = airport.second.getLatitude() - latitude;
        long double lonDiff = airport.second.getLongitude() - longitude;

        // Use Pythagorean theorem to calculate distance
        long double distance = std::sqrt(latDiff * latDiff + lonDiff * lonDiff);


        // Check if the distance is within the specified maximum distance
        if (distance <= min_dist) {
            min_dist = distance;
        }
    }
    for (const auto &airport : *airports_) {
        long double latDiff = airport.second.getLatitude() - latitude;
        long double lonDiff = airport.second.getLongitude() - longitude;

        // Use Pythagorean theorem to calculate distance
        long double distance = std::sqrt(latDiff * latDiff + lonDiff * lonDiff);


        // Check if the distance is within the specified maximum distance
        if (distance <= min_dist) {
            nearbyAirports.push_back(airport.second);
        }
    }


    return nearbyAirports;
}

std::vector<std::vector<Airport>>
Application::bestFlightAirportToLocation(const string &airport, const long double &latitude,
                                         const long double &longitude) {
    auto destinationAirports = findAirportsNearLocation(latitude, longitude);

    std::vector<std::vector<Airport>> res;

    auto source = getAirport(airport);

    for (const auto &destinationAirport : destinationAirports) {
        for (const auto &i : flightNetwork_->bfsShortestPath(source, destinationAirport)) {
            res.push_back(i);
        }
    }

    return res;
}

std::vector<std::vector<Airport>>
Application::bestFlightCityToLocation(const string &city, const long double &latitude, const long double &longitude) {
    auto sourceAirports = getAirportsInCity(city);
    auto destinationAirports = findAirportsNearLocation(latitude, longitude);

    std::vector<std::vector<Airport>> res;

    for (const auto &source : sourceAirports) {
        for (const auto &destinationAirport : destinationAirports) {
            for (const auto &i : flightNetwork_->bfsShortestPath(source->getInfo(), destinationAirport)) {
                res.push_back(i);
            }
        }
    }
    return res;
}

std::vector<std::vector<Airport>>
Application::bestFlightLocationToAirport(const long double &latitude, const long double &longitude,
                                         const string &airport) {

    auto sourceAirports = findAirportsNearLocation(latitude, longitude);

    std::vector<std::vector<Airport>> res;

    auto destinationAirport = getAirport(airport);

    for (const auto &sourceAirport : sourceAirports) {
        for (const auto &i : flightNetwork_->bfsShortestPath(sourceAirport, destinationAirport)) {
            res.push_back(i);
        }
    }

    return res;
}

std::vector<std::vector<Airport>>
Application::bestFlightLocationToCity(const long double &latitude, const long double &longitude, const string &city) {
    auto sourceAirports = findAirportsNearLocation(latitude, longitude);
    auto destinationAirports = getAirportsInCity(city);

    std::vector<std::vector<Airport>> res;

    for (const auto &source : sourceAirports) {
        auto sourceAirport = flightNetwork_->findVertex(source);
        for (const auto &destinationAirport : destinationAirports) {
            for (const auto &i : flightNetwork_->bfsShortestPath(sourceAirport, destinationAirport)) {
                res.push_back(i);
            }
        }
    }

    return res;
}

std::vector<std::vector<Airport>>
Application::bestFlightAirportToAirport(const string &airport1, const string &airport2,
                                        const std::vector<Airline> &forbidden) {
    Airport airport1Obj;
    Airport airport2Obj;
    if (airport1.length() == 3) {
        auto airportObj = getAirport(airport1);
        airport1Obj = airportObj;
    } else {
        auto airportObj = getAirportByName(airport1);
        airport1Obj = airportObj;
    }

    if (airport2.length() == 3) {
        auto airportObj = getAirport(airport2);
        airport2Obj = airportObj;
    } else {
        auto airportObj = getAirportByName(airport2);
        airport2Obj = airportObj;
    }
    auto vec = flightNetwork_->bfsShortestPath(airport1Obj, airport2Obj, forbidden);

    return vec;
}

std::vector<std::vector<Airport>>
Application::bestFlightAirportToCity(const string &airport, const string &city, const vector<Airline> &forbidden) {
    Airport airport1Obj;
    if (airport.length() == 3) {
        auto airportObj = getAirport(airport);
        airport1Obj = airportObj;
    } else {
        auto airportObj = getAirportByName(airport);
        airport1Obj = airportObj;
    }

    auto airportVertex = flightNetwork_->findVertex(airport1Obj);
    auto airportsInDestinationCity = getAirportsInCity(city);

    std::vector<std::vector<Airport>> res;
    for (const auto &destinationAirport : airportsInDestinationCity) {
        for (const auto &i : flightNetwork_->bfsShortestPath(airportVertex, destinationAirport, forbidden)) {
            res.push_back(i);
        }
    }

    return res;
}

std::vector<std::vector<Airport>>
Application::bestFlightAirportToLocation(const string &airport, const long double &latitude,
                                         const long double &longitude, const vector<Airline> &forbidden) {
    auto destinationAirports = findAirportsNearLocation(latitude, longitude);

    std::vector<std::vector<Airport>> res;

    auto source = getAirport(airport);

    for (const auto &destinationAirport : destinationAirports) {
        for (const auto &i : flightNetwork_->bfsShortestPath(source, destinationAirport, forbidden)) {
            res.push_back(i);
        }
    }

    return res;
}

std::vector<std::vector<Airport>>
Application::bestFlightCityToCity(const string &sourceCity, const string &destinationCity,
                                  const vector<Airline> &forbidden) {
    auto airportsInSourceCity = getAirportsInCity(sourceCity);
    auto airportsInDestinationCity = getAirportsInCity(destinationCity);

    std::vector<std::vector<Airport>> res;

    for (const auto &sourceAirport : airportsInSourceCity) {
        for (const auto &destinationAirport : airportsInDestinationCity) {
            for (const auto &i : flightNetwork_->bfsShortestPath(sourceAirport, destinationAirport, forbidden)) {
                res.push_back(i);
            }
        }
    }

    return res;
}

std::vector<std::vector<Airport>>
Application::bestFlightCityToAirport(const string &city, const std::string airport, const vector<Airline> &forbidden) {
    Airport airport1Obj;
    if (airport.length() == 3) {
        auto airportObj = getAirport(airport);
        airport1Obj = airportObj;
    } else {
        auto airportObj = getAirportByName(airport);
        airport1Obj = airportObj;
    }

    auto airportVertex = flightNetwork_->findVertex(airport1Obj);
    auto airportsInSourceCity = getAirportsInCity(city);

    std::vector<std::vector<Airport>> res;
    for (const auto &sourceAirport : airportsInSourceCity) {
        for (const auto &i : flightNetwork_->bfsShortestPath(sourceAirport, airportVertex, forbidden)) {
            res.push_back(i);
        }
    }

    return res;
}

std::vector<std::vector<Airport>>
Application::bestFlightCityToLocation(const string &city, const long double &latitude, const long double &longitude,
                                      const vector<Airline> &forbidden) {
    auto sourceAirports = getAirportsInCity(city);
    auto destinationAirports = findAirportsNearLocation(latitude, longitude);

    std::vector<std::vector<Airport>> res;

    for (const auto &source : sourceAirports) {
        for (const auto &destinationAirport : destinationAirports) {
            for (const auto &i : flightNetwork_->bfsShortestPath(source->getInfo(), destinationAirport, forbidden)) {
                res.push_back(i);
            }
        }
    }
    return res;
}

std::vector<std::vector<Airport>>
Application::bestFlightLocationToLocation(const long double &sourceLatitude, const long double &sourceLongitude,
                                          const long double &destLatitude, const long double &destLongitude,
                                          const vector<Airline> &forbidden) {
    auto sourceAirports = findAirportsNearLocation(sourceLatitude, sourceLongitude);
    auto destinationAirports = findAirportsNearLocation(destLatitude, destLongitude);

    std::vector<std::vector<Airport>> res;

    for (const auto &sourceAirport : sourceAirports) {
        for (const auto &destinationAirport : destinationAirports) {
            for (const auto &i : flightNetwork_->bfsShortestPath(sourceAirport, destinationAirport, forbidden)) {
                res.push_back(i);
            }
        }
    }

    return res;
}

std::vector<std::vector<Airport>>
Application::bestFlightLocationToAirport(const long double &latitude, const long double &longitude,
                                         const string &airport, const vector<Airline> &forbidden) {
    auto sourceAirports = findAirportsNearLocation(latitude, longitude);

    std::vector<std::vector<Airport>> res;

    auto destinationAirport = getAirport(airport);

    for (const auto &sourceAirport : sourceAirports) {
        for (const auto &i : flightNetwork_->bfsShortestPath(sourceAirport, destinationAirport, forbidden)) {
            res.push_back(i);
        }
    }

    return res;
}

std::vector<std::vector<Airport>>
Application::bestFlightLocationToCity(const long double &latitude, const long double &longitude, const string &city,
                                      const vector<Airline> &forbidden) {
    auto sourceAirports = findAirportsNearLocation(latitude, longitude);
    auto destinationAirports = getAirportsInCity(city);

    std::vector<std::vector<Airport>> res;

    for (const auto &source : sourceAirports) {
        auto sourceAirport = flightNetwork_->findVertex(source);
        for (const auto &destinationAirport : destinationAirports) {
            for (const auto &i : flightNetwork_->bfsShortestPath(sourceAirport, destinationAirport, forbidden)) {
                res.push_back(i);
            }
        }
    }

    return res;
}




