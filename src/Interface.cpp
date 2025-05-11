//
// Created by master on 23-12-2023.
//

#include <cstring>
#include "Interface.h"
#include "Printer.h"

Interface::Interface()= default;


void Interface::refreshDirectories(){
    directories.clear();
    directories.emplace_back(L"");
    directories.emplace_back(L"");
    directories.emplace_back(L"Statistics");
    directories.emplace_back(L"Statistics > Global Statistics");
    directories.emplace_back(L"Statistics > Global Statistics > Number of Airports");
    directories.emplace_back(L"Statistics > Global Statistics > Number of Available Flights");
    directories.emplace_back(L"Statistics > Global Statistics > Trip(s) with the Most Number of Stops");
    directories.emplace_back(L"Statistics > Choose an Airport");
    directories.push_back(L"Statistics > Airport " + airport_analised);
    directories.push_back(L"Statistics > Airport " + airport_analised + L" > Number of Flights Out of this Airport");
    directories.push_back(L"Statistics > Airport " + airport_analised + L" > Number of Different Airlines Out of this Airport");
    directories.push_back(L"Statistics > Airport " + airport_analised + L" > More Info on This Airport");
    directories.push_back(L"Statistics > Airport " + airport_analised + L" > Number of Destinations Available");
    directories.push_back(L"Statistics > Airport " + airport_analised + L" > Number of Airport Destinations Available");
    directories.push_back(L"Statistics > Airport " + airport_analised + L" > Number of City Destinations Available");
    directories.push_back(L"Statistics > Airport" + airport_analised + L" > Number of Country Destinations Available");
    directories.push_back(L"Statistics > Airport " + airport_analised + L" > Number of Destinations Available in a Certain Number of Stops");
    directories.push_back(L"Statistics > Airport " + airport_analised + L" > Number of Airport Destinations Available With Stops");
    directories.push_back(L"Statistics > Airport " + airport_analised + L" > Number of City Destinations Available With Stops");
    directories.push_back(L"Statistics > Airport " + airport_analised + L" > Number of Country Destinations Available With Stops");
    directories.emplace_back(L"Statistics > Choose a City");
    directories.push_back(L"Statistics > " + city_analised + L" City");
    directories.push_back(L"Statistics > " + city_analised + L" City > Number of Flights in this City");
    directories.push_back(L"Statistics > " + city_analised + L" City > Number of Different Countries this City Flies to");
    directories.emplace_back(L"Statistics > Choose an Airline");
    directories.push_back(L"Statistics > " + airline_analised + L" Airline");
    directories.push_back(L"Statistics > " + airline_analised + L" Airline > More Info on this Airline");
    directories.push_back(L"Statistics > " + airline_analised + L" Airline > Number of Flights of this Airline");
    directories.emplace_back(L"Statistics > Global Statistics > Top k Airports with the Greatest air Traffic Capacity");
    directories.emplace_back(L"Statistics > Global Statistics > Essential Airports");
    directories.emplace_back(L"Book a Flight");
    directories.emplace_back(L"Book a Flight > Choose an Airport Code");
    directories.push_back(L"Book a Flight > From " + airport_analised + L" Airport");
    directories.push_back(L"Book a Flight > From " + airport_analised + L" Airport > To ... (choose airport code)");
    directories.emplace_back(L"dummy");
    directories.emplace_back(L"Book a Flight > Choose an Airport Name");
    directories.push_back(L"Book a Flight > From " + airport_analised + L" Airport > To ... (choose airport name)");
    directories.emplace_back(L"dummy");
    directories.emplace_back(L"Book a Flight > Choose a City by Name");
    directories.emplace_back(L"Book a Flight > From " + city_analised + L" City > To...");
    directories.emplace_back(L"Book a Flight > From " + city_analised + L" City > To... (choose airport code)");
    directories.emplace_back(L"Book a Flight > From " + city_analised + L" City > To... (choose airport name)");
    directories.emplace_back(L"Book a Flight > From " + city_analised + L" City > To... (choose city name)");
    directories.push_back(L"Book a Flight > From " + airport_analised + L" Airport > To ... (choose city name)");
    directories.emplace_back(L"Book a Flight > Choose Geographical Coordinates");
    directories.push_back(L"Book a Flight > From " + latitude_analised + L", " + longitude_analised + L" > To...");
    directories.push_back(L"Book a Flight > From " + latitude_analised + L", " + longitude_analised + L" > To... (choose airport code)");
    directories.push_back(L"Book a Flight > From " + latitude_analised + L", " + longitude_analised + L" > To... (choose airport name)");
    directories.push_back(L"Book a Flight > From " + latitude_analised + L", " + longitude_analised + L" > To... (choose city name)");
    directories.push_back(L"Book a Flight > From " + latitude_analised + L", " + longitude_analised + L" > To... (choose coords)");
    directories.emplace_back(L"Book a Flight > From " + city_analised + L" City > To... (choose coords)");
    directories.push_back(L"Book a Flight > From " + airport_analised + L" Airport > To ... (choose city name)");
    directories.emplace_back(L"dummy");
    directories.emplace_back(L"dummy");
    directories.emplace_back(L"dummy");
    directories.emplace_back(L"dummy");
    directories.emplace_back(L"dummy");
    directories.emplace_back(L"dummy");
    directories.emplace_back(L"dummy");
    directories.emplace_back(L"dummy");
    directories.emplace_back(L"Choose preferred Airlines");
    directories.emplace_back(L"dummy");
}

void Interface::getForbiddenAirlines(){
    forbiddenAirlines.clear();
    for (std::wstring wstr : airlineCodeVector){
        if(std::find(chosenAirlines.begin(), chosenAirlines.end(), wstr) == chosenAirlines.end()){
            forbiddenAirlines.push_back(app->getAirline(converter.to_bytes(wstr)));
        }
    }
}

bool Interface::canBeDouble(const std::wstring& ws){
    try {
        size_t pos;
        std::stod(ws, &pos);
        return pos == ws.length();
    } catch (const std::invalid_argument&) {
        return false;
    } catch (const std::out_of_range&) {
        return false;
    }
}

void Interface::alphabeticSortVector(std::vector<std::wstring> &wstr){
    std::sort(wstr.begin(), wstr.end(), [](const auto& a, const auto& b){
        if (a > b){
            return false;
        }
        else {
            return true;
        }
    });
}

void Interface::stackClear(std::stack<int> &s){
    while (!s.empty()){
        s.pop();
    }
}

void Interface::getAirportCodes(const std::unordered_map<std::string, Airport>& airports){
    for (const auto& airport : airports){
        airportCodeVector.push_back(airport.second.getWcode());
    }
}

void Interface::getAirportNames(const std::unordered_map<std::string, Airport>& airports){
    for (const auto& airport : airports){
        airportNameVector.push_back(airport.second.getWname());
    }
}

void Interface::getTemporaryAirportCodes(const std::vector<Airport>& airports){
    for (const auto& airport : airports){
        temporaryAirportCodeVector.push_back(airport.getWcode());
    }
}

void Interface::getTemporaryAirportCodesFromSet(const std::set<Airport>& airports){
    for (const auto& airport : airports){
        temporaryAirportCodeVector.push_back(airport.getWcode());
    }
}


void Interface::getAirlineCodes(const std::unordered_map<std::string, Airline>& airlines){
    for (const auto& airline : airlines){
        airlineCodeVector.push_back(airline.second.getWcode());
    }
}

void Interface::getCities(){
    for (const auto& airport : app->getAirports()){
        if (std::find(citiesVector.begin(), citiesVector.end(), airport.second.getWcity()) == citiesVector.end()){
            citiesVector.push_back(airport.second.getWcity());
        }
    }
}

std::wstring Interface::smooth_string(const std::wstring& w){
    std::wstring sw;
    for (wchar_t c : w) {
        if (!iswspace(c)) {
            c = std::tolower(c);
            switch (c) {
                case L'á':
                case L'à':
                case L'â':
                case L'ä':
                case L'ã':
                case L'Á':
                case L'À':
                case L'Ã':
                case L'Â':
                case L'Ä':
                    sw += L'a';
                    break;
                case L'é':
                case L'è':
                case L'ê':
                case L'ë':
                case L'ẽ':
                case L'Ë':
                case L'É':
                case L'È':
                case L'Ê':
                case L'Ẽ':
                    sw += L'e';
                    break;
                case L'í':
                case L'ì':
                case L'î':
                case L'ï':
                case L'ĩ':
                case L'Í':
                case L'Ì':
                case L'Î':
                case L'Ĩ':
                case L'Ï':
                    sw += L'i';
                    break;
                case L'ó':
                case L'ò':
                case L'ô':
                case L'ö':
                case L'õ':
                case L'Ó':
                case L'Ò':
                case L'Õ':
                case L'Ô':
                case L'Ö':
                    sw += L'o';
                    break;
                case L'ú':
                case L'ù':
                case L'û':
                case L'ü':
                case L'ũ':
                case L'Ú':
                case L'Ù':
                case L'Ũ':
                case L'Û':
                case L'Ü':
                    sw += L'u';
                    break;
                case L'ç':
                    sw += L'c';
                default:
                    if (!ispunct(c)) {
                        sw += c;
                    }
            }
        }
    }
    return sw;
}


std::vector<std::wstring> Interface::filterSearch(const std::vector<std::wstring>& wstrings){
    std::vector<std::wstring> res;
    if (write.empty() || write == write_default){
        res = wstrings;
    }
    for (const std::wstring& wstr : wstrings){
        if (smooth_string(wstr).substr(0, smooth_string(write).size()) == smooth_string(write)){
            res.push_back(wstr);
        }
    }
    return res;
}


void Interface::writeOptionDefaulterAirport(){
    if (!write.empty() && write != write_default) {
        options[location][0] = L"Searching for: " + bold + write + end_effect;
    } else {
        options[location][0] = L"Search for an Airport code";
    }
    if (selected == 0 && write.empty() && !table_mode){
        options[location][0] = underline + bold + red + L"Search for an Airport code -> " + end_effect + L"  " + italic + write_default + end_italic;
        write_mode = true;
    }
    else if (selected == 0 && !table_mode){
        options[location][0] = underline + bold + red + L"Search for an Airport code -> " + end_effect + L"  " + write;
        write_mode = true;
    }
}

void Interface::writeOptionDefaulterAirportName(){
    if (!write.empty() && write != write_default) {
        options[location][0] = L"Searching for: " + bold + write + end_effect;
    } else {
        options[location][0] = L"Search for an Airport Name";
    }
    if (selected == 0 && write.empty() && !table_mode){
        options[location][0] = underline + bold + red + L"Search for an Airport Name -> " + end_effect + L"  " + italic + write_default + end_italic;
        write_mode = true;
    }
    else if (selected == 0 && !table_mode){
        options[location][0] = underline + bold + red + L"Search for an Airport Name -> " + end_effect + L"  " + write;
        write_mode = true;
    }
}

void Interface::writeOptionDefaulterCoords(){
    if (!write.empty() && write != write_default) {
        options[location][0] = L"Latitude: " + bold + write + end_effect;
    }
    else {
        options[location][0] = L"Write a Latitude";
    }
    if (!second_write.empty() && write != write_default){
        options[location][1] = L"Longitude: " + bold + second_write + end_effect;
    }
    else {
        options[location][1] = L"Write a Longitude";
    }
    if (selected == 0 && write.empty() && !table_mode){
        options[location][0] = underline + bold + red + L"Write a Latitude -> " + end_effect + L"  " + italic + write_default + end_italic;
        write_mode = true;
    }
    else if (selected == 0 && !table_mode){
        options[location][0] = underline + bold + red + L"Write a Latitude -> " + end_effect + L"  " + write;
        write_mode = true;
    }

    if (selected == 1 && second_write.empty() && !table_mode){
        options[location][1] = underline + bold + red + L"Write a Longitude -> " + end_effect + L"  " + italic + write_default + end_italic;
        write_mode = true;
    }
    else if (selected == 1 && !table_mode){
        options[location][1] = underline + bold + red + L"Write a Longitude -> " + end_effect + L"  " + second_write;
        write_mode = true;
    }
}


void Interface::writeOptionDefaulterCity(){
    if (!write.empty() && write != write_default) {
        options[location][0] = L"Searching for: " + bold + write + end_effect;
    } else {
        options[location][0] = L"Search for a City Name";
    }
    if (selected == 0 && write.empty() && !table_mode){
        options[location][0] = underline + bold + red + L"Search for a City Name -> " + end_effect + L"  " + italic + write_default + end_italic;
        write_mode = true;
    }
    else if (selected == 0 && !table_mode){
        options[location][0] = underline + bold + red + L"Search for a City Name -> " + end_effect + L"  " + write;
        write_mode = true;
    }
}


void Interface::writeOptionDefaulterAirline(){
    if (!write.empty() && write != write_default) {
        options[location][0] = L"Searching for: " + bold + write + end_effect;
    } else {
        options[location][0] = L"Search for a Airline Code";
    }
    if (selected == 0 && write.empty() && !table_mode){
        options[location][0] = underline + bold + red + L"Search for a Airline Code -> " + end_effect + L"  " + italic + write_default + end_italic;
        write_mode = true;
    }
    else if (selected == 0 && !table_mode){
        options[location][0] = underline + bold + red + L"Search for a Airline Code -> " + end_effect + L"  " + write;
        write_mode = true;
    }
}


void Interface::numeralWriteOptionsDefaulter(){
    options[location][0] = L"Number of Stops: " + bold + num_write + end_effect;
    if (selected == 0 && !table_mode){
        options[location][0] = underline + bold + red + L"Insert Number of Stops -> " + end_effect + L"  " + num_write;
        write_mode = true;
    }
}

void Interface::numeralWriteOptionsDefaulter2(){
    options[location][0] = L"Number of results shown: " + bold + num_write + end_effect;
    if (selected == 0 && !table_mode){
        options[location][0] = underline + bold + red + L"Insert Number of Results to see -> " + end_effect + L"  " + num_write;
        write_mode = true;
    }
}


void Interface::basicInputResponse(unsigned int user_in){
    if (locationHasTable[location]){
        if (user_in == '\t'){
            table_mode = !table_mode;
            selected = 0;
            selected_in_page = 0;
        }
        if (user_in == 'n'){
            page ++;
            selected_in_page = 0;
            if (page > filteredWstringVector.size()/elements_per_page) {
                page--;
            }
        }
        if (user_in == 'p'){
            page --;
            selected_in_page = 0;
            if (page < 0){
                page ++;
            }
        }
    }
    if (!table_mode){
        if (user_in == 'A') {
            if (selected > 0) { selected -= 1; }
            else { selected = options[location].size() - 1; }
        }
        if (user_in == 'B') {
            selected ++;
            if (selected >= options[location].size()) {selected = 0;}
        }
    }
    else{
        if (user_in == 'A') {
            if (selected_in_page > 0) { selected_in_page -= 1; }
            else if (page == filteredWstringVector.size()/elements_per_page){
                selected_in_page = filteredWstringVector.size()%elements_per_page - 1;
            }
            else {
                selected_in_page = elements_per_page - 1;
            }
        }
        if (user_in == 'B') {
            selected_in_page ++;
            if (page == filteredWstringVector.size()/elements_per_page){
                if (selected_in_page > filteredWstringVector.size()%elements_per_page - 1){
                    selected_in_page = 0;
                }
            }
            else{
                if (selected_in_page > elements_per_page - 1){
                    selected_in_page = 0;
                }
            }
        }
    }
    if (user_in == 'q') {
        location = -1;
    }
    //========================= ENTER INPUTS ===========================//
    if (user_in == '\n') {
        switch (location) {
            case 1:       //============================= MAIN MENU ===============================//
                switch (selected) {
                    case 0:
                        refreshDirectories();
                        location = 30;
                        directory = directories[location];
                        selected = 0;
                        break;
                    case 1:
                        refreshDirectories();
                        location = 2;
                        directory = directories[location];
                        selected = 0;

                        break;
                    case 2:
                        location = -1;
                        break;
                }
                break;

            case 2:       //============================= STATISTICS ===============================//
                switch (selected) {
                    case 0:
                        refreshDirectories();
                        earlier_locations.push(location);
                        location = 3;
                        directory = directories[location];
                        break;
                    case 1:
                        refreshDirectories();
                        earlier_locations.push(location);
                        location = 7;
                        directory = directories[location];
                        filteredWstringVector = airportCodeVector;
                        selected = 0;
                        break;
                    case 2:
                        refreshDirectories();
                        earlier_locations.push(location);
                        location = 20;
                        directory = directories[location];
                        filteredWstringVector = citiesVector;
                        selected = 0;
                        break;
                    case 3:
                        refreshDirectories();
                        earlier_locations.push(location);
                        location = 24;
                        directory = directories[location];
                        filteredWstringVector = airlineCodeVector;
                        selected = 0;
                        break;
                    case 4:
                        refreshDirectories();
                        location = 1;
                        directory = directories[location];
                        stackClear(earlier_locations);
                        selected = 0;
                        break;
                }
                break;

            case 3:       //==================== STATISTICS > GLOBAL STATISTICS ====================//
                switch (selected) {
                    case 0:
                        refreshDirectories();
                        earlier_locations.push(location);
                        location = 4;
                        directory = directories[location];
                        selected = 0;
                        break;
                    case 1:
                        refreshDirectories();
                        earlier_locations.push(location);
                        location = 5;
                        directory = directories[location];
                        selected = 0;
                        break;
                    case 2:
                        refreshDirectories();
                        earlier_locations.push(location);
                        location = 6;
                        directory = directories[location];
                        if (furthest_trips.empty()) {
                            appThread = std::thread([this]() {
                                furthest_trips = app->tripsWithGreatestNumberOfStops();
                                is_done = true;
                            });
                        }
                        while(furthest_trips.empty() && !is_done){
                            printAnimatedAirplane(airplaneLoadingScreen, 100);
                            printTextLoadingData();
                        }
                        if (is_done){
                            appThread.join();
                            is_done = false;
                        }
                        selected = 0;
                        break;
                    case 3:
                        refreshDirectories();
                        earlier_locations.push(location);
                        location = 28;
                        directory = directories[location];
                        selected = 0;
                        break;
                    case 4:
                        refreshDirectories();
                        earlier_locations.push(location);
                        location = 29;
                        directory = directories[location];
                        selected = 0;
                        break;
                    case 5:
                        refreshDirectories();
                        location = earlier_locations.top();
                        if (locationOfAirportSearch[location]){filteredWstringVector = airportCodeVector;}
                        if (locationAirportNmeSearch[location]){filteredWstringVector = airportNameVector;}
                        if (locationOfCitySearch[location]){filteredWstringVector = citiesVector;}
                        if (locationOfAirlineSearch[location]){filteredWstringVector = airlineCodeVector;}
                        earlier_locations.pop();
                        directory = directories[location];
                        selected = 0;
                        break;
                    case 6:
                        refreshDirectories();
                        location = 1;
                        directory = directories[location];
                        stackClear(earlier_locations);
                        selected = 0;
                        break;
                }
                break;

            case 4:       //========= STATISTICS > GLOBAL STATISTICS > NUMBER OF AIRPORTS ==========//
                switch (selected) {
                    case 0:
                        refreshDirectories();
                        location = earlier_locations.top();
                        if (locationOfAirportSearch[location]){filteredWstringVector = airportCodeVector;}
                        if (locationAirportNmeSearch[location]){filteredWstringVector = airportNameVector;}
                        if (locationOfCitySearch[location]){filteredWstringVector = citiesVector;}
                        if (locationOfAirlineSearch[location]){filteredWstringVector = airlineCodeVector;}
                        earlier_locations.pop();
                        directory = directories[location];
                        selected = 0;
                        break;
                    case 1:
                        refreshDirectories();
                        location = 1;
                        directory = directories[location];
                        stackClear(earlier_locations);
                        selected = 0;
                        break;
                }
                break;

            case 5:       //========= STATISTICS > GLOBAL STATISTICS > NUMBER OF AVAILABLE FLIGHTS ==========//
                switch (selected) {
                    case 0:
                        refreshDirectories();
                        location = earlier_locations.top();
                        if (locationOfAirportSearch[location]){filteredWstringVector = airportCodeVector;}
                        if (locationAirportNmeSearch[location]){filteredWstringVector = airportNameVector;}
                        if (locationOfCitySearch[location]){filteredWstringVector = citiesVector;}
                        if (locationOfAirlineSearch[location]){filteredWstringVector = airlineCodeVector;}
                        earlier_locations.pop();
                        directory = directories[location];
                        selected = 0;
                        break;
                    case 1:
                        refreshDirectories();
                        location = 1;
                        directory = directories[location];
                        stackClear(earlier_locations);
                        selected = 0;
                        break;
                }
                break;

            case 6:       //========= STATISTICS > GLOBAL STATISTICS > TRIP(S) WITH THE MOST NUMBER OF STOPS ==========//
                switch (selected) {
                    case 0:
                        refreshDirectories();
                        location = earlier_locations.top();
                        if (locationOfAirportSearch[location]){filteredWstringVector = airportCodeVector;}
                        if (locationAirportNmeSearch[location]){filteredWstringVector = airportNameVector;}
                        if (locationOfCitySearch[location]){filteredWstringVector = citiesVector;}
                        if (locationOfAirlineSearch[location]){filteredWstringVector = airlineCodeVector;}
                        earlier_locations.pop();
                        directory = directories[location];
                        selected = 0;
                        break;
                    case 1:
                        refreshDirectories();
                        location = 1;
                        directory = directories[location];
                        stackClear(earlier_locations);
                        selected = 0;
                        break;
                }
                break;

            case 7:       //========= STATISTICS > GLOBAL STATISTICS > CHOOSE AN AIRPORT ==========//
                switch (table_mode) {
                    case false:
                        switch (selected) {
                            case 1:
                                refreshDirectories();
                                location = earlier_locations.top();
                                if (locationOfAirportSearch[location]){filteredWstringVector = airportCodeVector;}
                                if (locationAirportNmeSearch[location]){filteredWstringVector = airportNameVector;}
                                if (locationOfCitySearch[location]){filteredWstringVector = citiesVector;}
                                if (locationOfAirlineSearch[location]){filteredWstringVector = airlineCodeVector;}
                                earlier_locations.pop();
                                directory = directories[location];
                                selected = 0;
                                break;
                            case 2:
                                refreshDirectories();
                                location = 1;
                                directory = directories[location];
                                stackClear(earlier_locations);
                                selected = 0;
                                break;
                        }
                        break;
                    case true:
                        earlier_locations.push(location);
                        airport_analised = filteredWstringVector[page * elements_per_page + selected_in_page];
                        refreshDirectories();
                        location = 8;
                        directory = directories[location];
                        write = write_default;
                        selected_in_page = 0;
                        selected = 0;
                        page = 0;
                        table_mode = !table_mode;
                        filteredWstringVector = airportCodeVector;
                        break;
                }
                break;

            case 8:        //========= STATISTICS > AIRPORT (X) ==========//
                switch (selected) {
                    case 0:
                        refreshDirectories();
                        earlier_locations.push(location);
                        location = 11;
                        directory = directories[location];
                        selected = 0;
                        break;
                    case 1:
                        refreshDirectories();
                        earlier_locations.push(location);
                        location = 9;
                        directory = directories[location];
                        selected = 0;
                        break;
                    case 2:
                        refreshDirectories();
                        earlier_locations.push(location);
                        location = 10;
                        directory = directories[location];
                        selected = 0;
                        break;
                    case 3:
                        refreshDirectories();
                        earlier_locations.push(location);
                        location = 12;
                        directory = directories[location];
                        selected = 0;
                        break;
                    case 4:
                        refreshDirectories();
                        earlier_locations.push(location);
                        location = 16;
                        directory = directories[location];
                        selected = 0;
                        break;
                    case 5:
                        refreshDirectories();
                        location = earlier_locations.top();
                        if (locationOfAirportSearch[location]){filteredWstringVector = airportCodeVector;}
                        if (locationAirportNmeSearch[location]){filteredWstringVector = airportNameVector;}
                        if (locationOfCitySearch[location]){filteredWstringVector = citiesVector;}
                        if (locationOfAirlineSearch[location]){filteredWstringVector = airlineCodeVector;}
                        earlier_locations.pop();
                        directory = directories[location];
                        selected = 0;
                        break;
                    case 6:
                        refreshDirectories();
                        location = 1;
                        directory = directories[location];
                        stackClear(earlier_locations);
                        selected = 0;
                        break;
                }
                break;

            case 9:
            case 10:
            case 11:
                switch (selected) {
                    case 0:
                        refreshDirectories();
                        location = earlier_locations.top();
                        if (locationOfAirportSearch[location]){filteredWstringVector = airportCodeVector;}
                        if (locationAirportNmeSearch[location]){filteredWstringVector = airportNameVector;}
                        if (locationOfCitySearch[location]){filteredWstringVector = citiesVector;}
                        if (locationOfAirlineSearch[location]){filteredWstringVector = airlineCodeVector;}
                        earlier_locations.pop();
                        directory = directories[location];
                        selected = 0;
                        break;
                    case 1:
                        refreshDirectories();
                        location = 1;
                        directory = directories[location];
                        stackClear(earlier_locations);
                        selected = 0;
                        break;
                }
                break;

            case 12:
                switch (selected) {
                    case 0:
                        refreshDirectories();
                        earlier_locations.push(location);
                        location = 13;
                        directory = directories[location];
                        selected = 0;
                        break;
                    case 1:
                        refreshDirectories();
                        earlier_locations.push(location);
                        location = 14;
                        directory = directories[location];
                        selected = 0;
                        break;
                    case 2:
                        refreshDirectories();
                        earlier_locations.push(location);
                        location = 15;
                        directory = directories[location];
                        selected = 0;
                        break;
                    case 3:
                        refreshDirectories();
                        location = earlier_locations.top();
                        if (locationOfAirportSearch[location]){filteredWstringVector = airportCodeVector;}
                        if (locationAirportNmeSearch[location]){filteredWstringVector = airportNameVector;}
                        if (locationOfCitySearch[location]){filteredWstringVector = citiesVector;}
                        if (locationOfAirlineSearch[location]){filteredWstringVector = airlineCodeVector;}
                        earlier_locations.pop();
                        directory = directories[location];
                        selected = 0;
                        break;
                    case 4:
                        refreshDirectories();
                        location = 1;
                        directory = directories[location];
                        stackClear(earlier_locations);
                        selected = 0;
                        break;
                }
                break;

            case 13:
            case 14:
            case 15:
                switch (selected) {
                    case 0:
                        refreshDirectories();
                        location = earlier_locations.top();
                        if (locationOfAirportSearch[location]){filteredWstringVector = airportCodeVector;}
                        if (locationAirportNmeSearch[location]){filteredWstringVector = airportNameVector;}
                        if (locationOfCitySearch[location]){filteredWstringVector = citiesVector;}
                        if (locationOfAirlineSearch[location]){filteredWstringVector = airlineCodeVector;}
                        earlier_locations.pop();
                        directory = directories[location];
                        selected = 0;
                        break;
                    case 1:
                        refreshDirectories();
                        location = 1;
                        directory = directories[location];
                        stackClear(earlier_locations);
                        selected = 0;
                        break;
                }
                break;

            case 16:
                switch (selected) {
                    case 0:
                        refreshDirectories();
                        earlier_locations.push(location);
                        location = 17;
                        directory = directories[location];
                        selected = 0;
                        break;
                    case 1:
                        refreshDirectories();
                        earlier_locations.push(location);
                        location = 18;
                        directory = directories[location];
                        selected = 0;
                        break;
                    case 2:
                        refreshDirectories();
                        earlier_locations.push(location);
                        location = 19;
                        directory = directories[location];
                        selected = 0;
                        break;
                    case 3:
                        refreshDirectories();
                        location = earlier_locations.top();
                        if (locationOfAirportSearch[location]){filteredWstringVector = airportCodeVector;}
                        if (locationAirportNmeSearch[location]){filteredWstringVector = airportNameVector;}
                        if (locationOfCitySearch[location]){filteredWstringVector = citiesVector;}
                        if (locationOfAirlineSearch[location]){filteredWstringVector = airlineCodeVector;}
                        earlier_locations.pop();
                        directory = directories[location];
                        selected = 0;
                        break;
                    case 4:
                        refreshDirectories();
                        location = 1;
                        directory = directories[location];
                        stackClear(earlier_locations);
                        selected = 0;
                        break;
                }
                break;

            case 17:
            case 18:
            case 19:
                switch (selected) {
                    case 1:
                        refreshDirectories();
                        location = earlier_locations.top();
                        if (locationOfAirportSearch[location]){filteredWstringVector = airportCodeVector;}
                        if (locationAirportNmeSearch[location]){filteredWstringVector = airportNameVector;}
                        if (locationOfCitySearch[location]){filteredWstringVector = citiesVector;}
                        if (locationOfAirlineSearch[location]){filteredWstringVector = airlineCodeVector;}
                        earlier_locations.pop();
                        directory = directories[location];
                        selected = 0;
                        break;
                    case 2:
                        refreshDirectories();
                        location = 1;
                        directory = directories[location];
                        stackClear(earlier_locations);
                        selected = 0;
                        break;
                }
                break;

            case 20:       //========= STATISTICS > GLOBAL STATISTICS > CHOOSE AN AIRPORT ==========//
                switch (table_mode) {
                    case false:
                        switch (selected) {
                            case 1:
                                refreshDirectories();
                                location = earlier_locations.top();
                                if (locationOfAirportSearch[location]){filteredWstringVector = airportCodeVector;}
                                if (locationAirportNmeSearch[location]){filteredWstringVector = airportNameVector;}
                                if (locationOfCitySearch[location]){filteredWstringVector = citiesVector;}
                                if (locationOfAirlineSearch[location]){filteredWstringVector = airlineCodeVector;}
                                earlier_locations.pop();
                                directory = directories[location];
                                selected = 0;
                                break;
                            case 2:
                                refreshDirectories();
                                location = 1;
                                directory = directories[location];
                                stackClear(earlier_locations);
                                selected = 0;
                                break;
                        }
                        break;
                    case true:
                        earlier_locations.push(location);
                        city_analised = filteredWstringVector[page * elements_per_page + selected_in_page];
                        refreshDirectories();
                        location = 21;
                        directory = directories[location];
                        write = write_default;
                        selected_in_page = 0;
                        selected = 0;
                        page = 0;
                        table_mode = !table_mode;
                        filteredWstringVector = citiesVector;
                        break;
                }
                break;

            case 21:
                switch (selected) {
                    case 0:
                        refreshDirectories();
                        earlier_locations.push(location);
                        location = 22;
                        directory = directories[location];
                        selected = 0;
                        break;
                    case 1:
                        refreshDirectories();
                        earlier_locations.push(location);
                        location = 23;
                        directory = directories[location];
                        selected = 0;
                        break;
                    case 2:
                        refreshDirectories();
                        location = earlier_locations.top();
                        if (locationOfAirportSearch[location]){filteredWstringVector = airportCodeVector;}
                        if (locationAirportNmeSearch[location]){filteredWstringVector = airportNameVector;}
                        if (locationOfCitySearch[location]){filteredWstringVector = citiesVector;}
                        if (locationOfAirlineSearch[location]){filteredWstringVector = airlineCodeVector;}
                        earlier_locations.pop();
                        directory = directories[location];
                        selected = 0;
                        break;
                    case 3:
                        refreshDirectories();
                        location = 1;
                        directory = directories[location];
                        stackClear(earlier_locations);
                        selected = 0;
                        break;
                }
                break;

            case 22:
            case 23:
                switch (selected) {
                    case 0:
                        refreshDirectories();
                        location = earlier_locations.top();
                        if (locationOfAirportSearch[location]){filteredWstringVector = airportCodeVector;}
                        if (locationAirportNmeSearch[location]){filteredWstringVector = airportNameVector;}
                        if (locationOfCitySearch[location]){filteredWstringVector = citiesVector;}
                        if (locationOfAirlineSearch[location]){filteredWstringVector = airlineCodeVector;}
                        earlier_locations.pop();
                        directory = directories[location];
                        selected = 0;
                        break;
                    case 1:
                        refreshDirectories();
                        location = 1;
                        directory = directories[location];
                        stackClear(earlier_locations);
                        selected = 0;
                        break;
                }
                break;

            case 24:
                switch (table_mode){
                    case false:
                        switch (selected) {
                            case 1:
                                refreshDirectories();
                                location = earlier_locations.top();
                                if (locationOfAirportSearch[location]){filteredWstringVector = airportCodeVector;}
                                if (locationAirportNmeSearch[location]){filteredWstringVector = airportNameVector;}
                                if (locationOfCitySearch[location]){filteredWstringVector = citiesVector;}
                                if (locationOfAirlineSearch[location]){filteredWstringVector = airlineCodeVector;}
                                earlier_locations.pop();
                                directory = directories[location];
                                selected = 0;
                                break;
                            case 2:
                                refreshDirectories();
                                location = 1;
                                directory = directories[location];
                                stackClear(earlier_locations);
                                selected = 0;
                                break;
                        }
                        break;
                    case true:
                        earlier_locations.push(location);
                        airline_analised = filteredWstringVector[page * elements_per_page + selected_in_page];
                        refreshDirectories();
                        location = 25;
                        directory = directories[location];
                        write = write_default;
                        selected_in_page = 0;
                        selected = 0;
                        page = 0;
                        table_mode = !table_mode;
                        filteredWstringVector = airlineCodeVector;
                        break;
                }
                break;

            case 25:
                switch (selected) {
                    case 0:
                        refreshDirectories();
                        earlier_locations.push(location);
                        location = 26;
                        directory = directories[location];
                        selected = 0;
                        break;
                    case 1:
                        refreshDirectories();
                        earlier_locations.push(location);
                        location = 27;
                        directory = directories[location];
                        selected = 0;
                        break;
                    case 2:
                        refreshDirectories();
                        location = earlier_locations.top();
                        if (locationOfAirportSearch[location]){filteredWstringVector = airportCodeVector;}
                        if (locationAirportNmeSearch[location]){filteredWstringVector = airportNameVector;}
                        if (locationOfCitySearch[location]){filteredWstringVector = citiesVector;}
                        if (locationOfAirlineSearch[location]){filteredWstringVector = airlineCodeVector;}
                        earlier_locations.pop();
                        directory = directories[location];
                        selected = 0;
                        break;
                    case 3:
                        refreshDirectories();
                        location = 1;
                        directory = directories[location];
                        stackClear(earlier_locations);
                        selected = 0;
                        break;
                }
                break;

            case 26:
            case 27:
                switch (selected) {
                    case 0:
                        refreshDirectories();
                        location = earlier_locations.top();
                        if (locationOfAirportSearch[location]){filteredWstringVector = airportCodeVector;}
                        if (locationAirportNmeSearch[location]){filteredWstringVector = airportNameVector;}
                        if (locationOfCitySearch[location]){filteredWstringVector = citiesVector;}
                        if (locationOfAirlineSearch[location]){filteredWstringVector = airlineCodeVector;}
                        earlier_locations.pop();
                        directory = directories[location];
                        selected = 0;
                        break;
                    case 1:
                        refreshDirectories();
                        location = 1;
                        directory = directories[location];
                        stackClear(earlier_locations);
                        selected = 0;
                        break;
                }
                break;

            case 28:
                switch (table_mode){
                    case false:
                        switch (selected) {
                            case 1:
                                refreshDirectories();
                                location = earlier_locations.top();
                                if (locationOfAirportSearch[location]){filteredWstringVector = airportCodeVector;}
                                if (locationAirportNmeSearch[location]){filteredWstringVector = airportNameVector;}
                                if (locationOfCitySearch[location]){filteredWstringVector = citiesVector;}
                                if (locationOfAirlineSearch[location]){filteredWstringVector = airlineCodeVector;}
                                earlier_locations.pop();
                                directory = directories[location];
                                selected = 0;
                                break;
                            case 2:
                                refreshDirectories();
                                location = 1;
                                directory = directories[location];
                                stackClear(earlier_locations);
                                selected = 0;
                                break;
                        }
                        break;
                    case true:
                        earlier_locations.push(location);
                        airport_analised = filteredWstringVector[page * elements_per_page + selected_in_page];
                        refreshDirectories();
                        location = 8;
                        directory = directories[location];
                        write = write_default;
                        selected_in_page = 0;
                        selected = 0;
                        page = 0;
                        table_mode = !table_mode;
                        filteredWstringVector = airportCodeVector;
                        break;
                }
                break;

            case 29:
                switch (table_mode){
                    case false:
                        switch (selected) {
                            case 0:
                                refreshDirectories();
                                location = earlier_locations.top();
                                if (locationOfAirportSearch[location]){filteredWstringVector = airportCodeVector;}
                                if (locationAirportNmeSearch[location]){filteredWstringVector = airportNameVector;}
                                if (locationOfCitySearch[location]){filteredWstringVector = citiesVector;}
                                if (locationOfAirlineSearch[location]){filteredWstringVector = airlineCodeVector;}
                                earlier_locations.pop();
                                directory = directories[location];
                                selected = 0;
                                break;
                            case 1:
                                refreshDirectories();
                                location = 1;
                                directory = directories[location];
                                stackClear(earlier_locations);
                                selected = 0;
                                break;
                        }
                        break;
                    case true:
                        earlier_locations.push(location);
                        airport_analised = filteredWstringVector[page * elements_per_page + selected_in_page];
                        refreshDirectories();
                        location = 8;
                        directory = directories[location];
                        write = write_default;
                        selected_in_page = 0;
                        selected = 0;
                        page = 0;
                        table_mode = !table_mode;
                        filteredWstringVector = airportCodeVector;
                        break;
                }
                break;

            case 30:
                switch (selected){
                    case 0:
                        refreshDirectories();
                        earlier_locations.push(location);
                        location = 31;
                        directory = directories[location];
                        filteredWstringVector = airportCodeVector;
                        selected = 0;
                        break;
                    case 1:
                        refreshDirectories();
                        earlier_locations.push(location);
                        location = 35;
                        directory = directories[location];
                        filteredWstringVector = airportNameVector;
                        selected = 0;
                        break;
                    case 2:
                        refreshDirectories();
                        earlier_locations.push(location);
                        location = 38;
                        directory = directories[location];
                        filteredWstringVector = citiesVector;
                        selected = 0;
                        break;
                    case 3:
                        refreshDirectories();
                        earlier_locations.push(location);
                        location = 44;
                        directory = directories[location];
                        selected = 0;
                        break;
                    case 4:
                        refreshDirectories();
                        location = 1;
                        directory = directories[location];
                        stackClear(earlier_locations);
                        selected = 0;
                        break;
                }
                break;

            case 31:
                switch (table_mode){
                    case false:
                        switch (selected){
                            case 1:
                                refreshDirectories();
                                location = earlier_locations.top();
                                if (locationOfAirportSearch[location]){filteredWstringVector = airportCodeVector;}
                                if (locationAirportNmeSearch[location]){filteredWstringVector = airportNameVector;}
                                if (locationOfCitySearch[location]){filteredWstringVector = citiesVector;}
                                if (locationOfAirlineSearch[location]){filteredWstringVector = airlineCodeVector;}
                                earlier_locations.pop();
                                directory = directories[location];
                                selected = 0;
                                break;
                            case 2:
                                refreshDirectories();
                                location = 1;
                                directory = directories[location];
                                stackClear(earlier_locations);
                                selected = 0;
                                break;
                        }
                        break;
                    case true:
                        earlier_locations.push(location);
                        airport_analised = filteredWstringVector[page * elements_per_page + selected_in_page];
                        refreshDirectories();
                        location = 32;
                        directory = directories[location];
                        write = write_default;
                        selected_in_page = 0;
                        selected = 0;
                        page = 0;
                        table_mode = !table_mode;
                        filteredWstringVector = airportCodeVector;
                        origin = {airport_analised, 0};
                        break;
                }
                break;

            case 32:
                switch (selected){
                    case 0:
                        refreshDirectories();
                        earlier_locations.push(location);
                        location = 33;
                        directory = directories[location];
                        filteredWstringVector = airportCodeVector;
                        selected = 0;
                        break;
                    case 1:
                        refreshDirectories();
                        earlier_locations.push(location);
                        location = 36;
                        directory = directories[location];
                        filteredWstringVector = airportNameVector;
                        selected = 0;
                        break;
                    case 2:
                        refreshDirectories();
                        earlier_locations.push(location);
                        location = 43;
                        directory = directories[location];
                        filteredWstringVector = citiesVector;
                        selected = 0;
                        break;
                    case 3:
                        refreshDirectories();
                        earlier_locations.push(location);
                        location = 51;
                        directory = directories[location];
                        selected = 0;
                        break;
                    case 4:
                        refreshDirectories();
                        location = earlier_locations.top();
                        if (locationOfAirportSearch[location]){filteredWstringVector = airportCodeVector;}
                        if (locationAirportNmeSearch[location]){filteredWstringVector = airportNameVector;}
                        if (locationOfCitySearch[location]){filteredWstringVector = citiesVector;}
                        if (locationOfAirlineSearch[location]){filteredWstringVector = airlineCodeVector;}
                        earlier_locations.pop();
                        directory = directories[location];
                        selected = 0;
                        break;
                    case 5:
                        refreshDirectories();
                        location = 1;
                        directory = directories[location];
                        stackClear(earlier_locations);
                        selected = 0;
                        break;
                }
                break;

            case 33:
                switch (table_mode){
                    case false:
                        switch (selected){
                            case 1:
                                refreshDirectories();
                                location = earlier_locations.top();
                                if (locationOfAirportSearch[location]){filteredWstringVector = airportCodeVector;}
                                if (locationAirportNmeSearch[location]){filteredWstringVector = airportNameVector;}
                                if (locationOfCitySearch[location]){filteredWstringVector = citiesVector;}
                                if (locationOfAirlineSearch[location]){filteredWstringVector = airlineCodeVector;}
                                earlier_locations.pop();
                                directory = directories[location];
                                selected = 0;
                                break;
                            case 2:
                                refreshDirectories();
                                location = 1;
                                directory = directories[location];
                                stackClear(earlier_locations);
                                selected = 0;
                                break;
                        }
                        break;
                    case true:
                        earlier_locations.push(location);
                        second_airport_analised = filteredWstringVector[page * elements_per_page + selected_in_page];
                        refreshDirectories();
                        location = 60;
                        chosenAirlines.clear();
                        directory = directories[location];
                        write = write_default;
                        selected_in_page = 0;
                        selected = 0;
                        page = 0;
                        table_mode = !table_mode;
                        filteredWstringVector = airlineCodeVector;;
                        destiny = {second_airport_analised, 0};
                        break;
                }
                break;

            case 35:
                switch (table_mode){
                    case false:
                        switch (selected){
                            case 1:
                                refreshDirectories();
                                location = earlier_locations.top();
                                if (locationOfAirportSearch[location]){filteredWstringVector = airportCodeVector;}
                                if (locationAirportNmeSearch[location]){filteredWstringVector = airportNameVector;}
                                if (locationOfCitySearch[location]){filteredWstringVector = citiesVector;}
                                if (locationOfAirlineSearch[location]){filteredWstringVector = airlineCodeVector;}
                                earlier_locations.pop();
                                directory = directories[location];
                                selected = 0;
                                break;
                            case 2:
                                refreshDirectories();
                                location = 1;
                                directory = directories[location];
                                stackClear(earlier_locations);
                                selected = 0;
                                break;
                        }
                        break;
                    case true:
                        earlier_locations.push(location);
                        airport_analised = filteredWstringVector[page * elements_per_page + selected_in_page];
                        refreshDirectories();
                        location = 32;
                        directory = directories[location];
                        write = write_default;
                        selected_in_page = 0;
                        selected = 0;
                        page = 0;
                        table_mode = !table_mode;
                        filteredWstringVector = airportCodeVector;
                        origin = {airport_analised, 0};
                        break;
                }
                break;

            case 36:
                switch (table_mode){
                    case false:
                        switch (selected){
                            case 1:
                                refreshDirectories();
                                location = earlier_locations.top();
                                if (locationOfAirportSearch[location]){filteredWstringVector = airportCodeVector;}
                                if (locationAirportNmeSearch[location]){filteredWstringVector = airportNameVector;}
                                if (locationOfCitySearch[location]){filteredWstringVector = citiesVector;}
                                if (locationOfAirlineSearch[location]){filteredWstringVector = airlineCodeVector;}
                                earlier_locations.pop();
                                directory = directories[location];
                                selected = 0;
                                break;
                            case 2:
                                refreshDirectories();
                                location = 1;
                                directory = directories[location];
                                stackClear(earlier_locations);
                                selected = 0;
                                break;
                        }
                        break;
                    case true:
                        earlier_locations.push(location);
                        second_airport_analised = filteredWstringVector[page * elements_per_page + selected_in_page];
                        refreshDirectories();
                        location = 60;
                        chosenAirlines.clear();
                        directory = directories[location];
                        write = write_default;
                        selected_in_page = 0;
                        selected = 0;
                        page = 0;
                        table_mode = !table_mode;
                        filteredWstringVector = airlineCodeVector;
                        destiny = {second_airport_analised, 0};
                        break;
                }
                break;

            case 38:
                switch (table_mode) {
                    case false:
                        switch (selected) {
                            case 1:
                                refreshDirectories();
                                location = earlier_locations.top();
                                if (locationOfAirportSearch[location]){filteredWstringVector = airportCodeVector;}
                                if (locationAirportNmeSearch[location]){filteredWstringVector = airportNameVector;}
                                if (locationOfCitySearch[location]){filteredWstringVector = citiesVector;}
                                if (locationOfAirlineSearch[location]){filteredWstringVector = airlineCodeVector;}
                                earlier_locations.pop();
                                directory = directories[location];
                                selected = 0;
                                break;
                            case 2:
                                refreshDirectories();
                                location = 1;
                                directory = directories[location];
                                stackClear(earlier_locations);
                                selected = 0;
                                break;
                        }
                        break;
                    case true:
                        earlier_locations.push(location);
                        city_analised = filteredWstringVector[page * elements_per_page + selected_in_page];
                        refreshDirectories();
                        location = 39;
                        directory = directories[location];
                        write = write_default;
                        selected_in_page = 0;
                        selected = 0;
                        page = 0;
                        table_mode = !table_mode;
                        filteredWstringVector = citiesVector;
                        origin = {city_analised, 1};
                        break;
                }
                break;

            case 39:
                switch (selected){
                    case 0:
                        refreshDirectories();
                        earlier_locations.push(location);
                        location = 40;
                        directory = directories[location];
                        filteredWstringVector = airportCodeVector;
                        selected = 0;
                        break;
                    case 1:
                        refreshDirectories();
                        earlier_locations.push(location);
                        location = 41;
                        directory = directories[location];
                        filteredWstringVector = airportNameVector;
                        selected = 0;
                        break;
                    case 2:
                        refreshDirectories();
                        earlier_locations.push(location);
                        location = 42;
                        directory = directories[location];
                        filteredWstringVector = airportNameVector;
                        selected = 0;
                        break;
                    case 3:
                        refreshDirectories();
                        earlier_locations.push(location);
                        location = 50;
                        directory = directories[location];
                        filteredWstringVector = airportNameVector;
                        selected = 0;
                        break;
                    case 4:
                        refreshDirectories();
                        location = earlier_locations.top();
                        if (locationOfAirportSearch[location]){filteredWstringVector = airportCodeVector;}
                        if (locationAirportNmeSearch[location]){filteredWstringVector = airportNameVector;}
                        if (locationOfCitySearch[location]){filteredWstringVector = citiesVector;}
                        if (locationOfAirlineSearch[location]){filteredWstringVector = airlineCodeVector;}
                        earlier_locations.pop();
                        directory = directories[location];
                        selected = 0;
                        break;
                    case 5:
                        refreshDirectories();
                        location = 1;
                        directory = directories[location];
                        stackClear(earlier_locations);
                        selected = 0;
                        break;
                }
                break;

            case 40:     //city-->airport//
                switch (table_mode){
                    case false:
                        switch (selected){
                            case 1:
                                refreshDirectories();
                                location = earlier_locations.top();
                                if (locationOfAirportSearch[location]){filteredWstringVector = airportCodeVector;}
                                if (locationAirportNmeSearch[location]){filteredWstringVector = airportNameVector;}
                                if (locationOfCitySearch[location]){filteredWstringVector = citiesVector;}
                                if (locationOfAirlineSearch[location]){filteredWstringVector = airlineCodeVector;}
                                earlier_locations.pop();
                                directory = directories[location];
                                selected = 0;
                                break;
                            case 2:
                                refreshDirectories();
                                location = 1;
                                directory = directories[location];
                                stackClear(earlier_locations);
                                selected = 0;
                                break;
                        }
                        break;
                    case true:
                        earlier_locations.push(location);
                        second_airport_analised = filteredWstringVector[page * elements_per_page + selected_in_page];
                        refreshDirectories();
                        location = 60;
                        chosenAirlines.clear();
                        directory = directories[location];
                        write = write_default;
                        selected_in_page = 0;
                        selected = 0;
                        page = 0;
                        table_mode = !table_mode;
                        filteredWstringVector = airlineCodeVector;
                        destiny = {second_airport_analised, 0};
                        break;
                }
                break;

            case 41:   //city-->airport//
                switch (table_mode){
                    case false:
                        switch (selected){
                            case 1:
                                refreshDirectories();
                                location = earlier_locations.top();
                                if (locationOfAirportSearch[location]){filteredWstringVector = airportCodeVector;}
                                if (locationAirportNmeSearch[location]){filteredWstringVector = airportNameVector;}
                                if (locationOfCitySearch[location]){filteredWstringVector = citiesVector;}
                                if (locationOfAirlineSearch[location]){filteredWstringVector = airlineCodeVector;}
                                earlier_locations.pop();
                                directory = directories[location];
                                selected = 0;
                                break;
                            case 2:
                                refreshDirectories();
                                location = 1;
                                directory = directories[location];
                                stackClear(earlier_locations);
                                selected = 0;
                                break;
                        }
                        break;
                    case true:
                        earlier_locations.push(location);
                        second_airport_analised = filteredWstringVector[page * elements_per_page + selected_in_page];
                        refreshDirectories();
                        location = 60;
                        chosenAirlines.clear();
                        directory = directories[location];
                        write = write_default;
                        selected_in_page = 0;
                        selected = 0;
                        page = 0;
                        table_mode = !table_mode;
                        filteredWstringVector = airlineCodeVector;
                        destiny = {second_airport_analised, 0};
                        break;
                }
                break;

            case 42:     //city -> city
                switch (table_mode) {
                    case false:
                        switch (selected) {
                            case 1:
                                refreshDirectories();
                                location = earlier_locations.top();
                                if (locationOfAirportSearch[location]){filteredWstringVector = airportCodeVector;}
                                if (locationAirportNmeSearch[location]){filteredWstringVector = airportNameVector;}
                                if (locationOfCitySearch[location]){filteredWstringVector = citiesVector;}
                                if (locationOfAirlineSearch[location]){filteredWstringVector = airlineCodeVector;}
                                earlier_locations.pop();
                                directory = directories[location];
                                selected = 0;
                                break;
                            case 2:
                                refreshDirectories();
                                location = 1;
                                directory = directories[location];
                                stackClear(earlier_locations);
                                selected = 0;
                                break;
                        }
                        break;
                    case true:
                        earlier_locations.push(location);
                        second_city_analised = filteredWstringVector[page * elements_per_page + selected_in_page];
                        refreshDirectories();
                        location = 60;
                        chosenAirlines.clear();
                        directory = directories[location];
                        write = write_default;
                        selected_in_page = 0;
                        selected = 0;
                        page = 0;
                        table_mode = !table_mode;
                        filteredWstringVector = airlineCodeVector;
                        destiny = {second_city_analised, 1};
                        break;
                }
                break;

            case 43:   //airport -> city//
                switch (table_mode) {
                    case false:
                        switch (selected) {
                            case 1:
                                refreshDirectories();
                                location = earlier_locations.top();
                                if (locationOfAirportSearch[location]){filteredWstringVector = airportCodeVector;}
                                if (locationAirportNmeSearch[location]){filteredWstringVector = airportNameVector;}
                                if (locationOfCitySearch[location]){filteredWstringVector = citiesVector;}
                                if (locationOfAirlineSearch[location]){filteredWstringVector = airlineCodeVector;}
                                earlier_locations.pop();
                                directory = directories[location];
                                selected = 0;
                                break;
                            case 2:
                                refreshDirectories();
                                location = 1;
                                directory = directories[location];
                                stackClear(earlier_locations);
                                selected = 0;
                                break;
                        }
                        break;
                    case true:
                        earlier_locations.push(location);
                        second_city_analised = filteredWstringVector[page * elements_per_page + selected_in_page];
                        refreshDirectories();
                        location = 60;
                        chosenAirlines.clear();
                        directory = directories[location];
                        write = write_default;
                        selected_in_page = 0;
                        selected = 0;
                        page = 0;
                        table_mode = !table_mode;
                        filteredWstringVector = airlineCodeVector;
                        destiny = {second_city_analised, 1};
                        break;
                }
                break;

            case 44:
                switch (selected) {
                    case 2:
                        if (canBeDouble(write) && canBeDouble(second_write)){
                            latitude_analised = write;
                            longitude_analised = second_write;
                            refreshDirectories();
                            earlier_locations.push(location);
                            location = 45;
                            directory = directories[location];
                            selected = 0;
                            coord_origin = {latitude_analised, longitude_analised};
                        }
                        break;
                    case 3:
                        refreshDirectories();
                        location = earlier_locations.top();
                        if (locationOfAirportSearch[location]){filteredWstringVector = airportCodeVector;}
                        if (locationAirportNmeSearch[location]){filteredWstringVector = airportNameVector;}
                        if (locationOfCitySearch[location]){filteredWstringVector = citiesVector;}
                        if (locationOfAirlineSearch[location]){filteredWstringVector = airlineCodeVector;}
                        earlier_locations.pop();
                        directory = directories[location];
                        selected = 0;
                        coord_origin.first.clear();
                        coord_origin.second.clear();
                        break;
                    case 4:
                        refreshDirectories();
                        location = 1;
                        directory = directories[location];
                        stackClear(earlier_locations);
                        selected = 0;
                        break;
                }
                write.clear();
                second_write.clear();
                break;

            case 45:
                switch (selected){
                    case 0:
                        refreshDirectories();
                        earlier_locations.push(location);
                        location = 46;
                        directory = directories[location];
                        filteredWstringVector = airportCodeVector;
                        selected = 0;
                        break;
                    case 1:
                        refreshDirectories();
                        earlier_locations.push(location);
                        location = 47;
                        directory = directories[location];
                        filteredWstringVector = airportNameVector;
                        selected = 0;
                        break;
                    case 2:
                        refreshDirectories();
                        earlier_locations.push(location);
                        location = 48;
                        directory = directories[location];
                        filteredWstringVector = citiesVector;
                        selected = 0;
                        break;
                    case 3:
                        refreshDirectories();
                        earlier_locations.push(location);
                        location = 49;
                        directory = directories[location];
                        selected = 0;
                        break;
                        break;
                    case 4:
                        refreshDirectories();
                        location = earlier_locations.top();
                        if (locationOfAirportSearch[location]){filteredWstringVector = airportCodeVector;}
                        if (locationAirportNmeSearch[location]){filteredWstringVector = airportNameVector;}
                        if (locationOfCitySearch[location]){filteredWstringVector = citiesVector;}
                        if (locationOfAirlineSearch[location]){filteredWstringVector = airlineCodeVector;}
                        earlier_locations.pop();
                        directory = directories[location];
                        selected = 0;
                        break;
                    case 5:
                        refreshDirectories();
                        location = 1;
                        directory = directories[location];
                        stackClear(earlier_locations);
                        selected = 0;
                        break;
                }
                break;

            case 46:   //coords-->airport//
                switch (table_mode){
                    case false:
                        switch (selected){
                            case 1:
                                refreshDirectories();
                                location = earlier_locations.top();
                                if (locationOfAirportSearch[location]){filteredWstringVector = airportCodeVector;}
                                if (locationAirportNmeSearch[location]){filteredWstringVector = airportNameVector;}
                                if (locationOfCitySearch[location]){filteredWstringVector = citiesVector;}
                                if (locationOfAirlineSearch[location]){filteredWstringVector = airlineCodeVector;}
                                earlier_locations.pop();
                                directory = directories[location];
                                selected = 0;
                                break;
                            case 2:
                                refreshDirectories();
                                location = 1;
                                directory = directories[location];
                                stackClear(earlier_locations);
                                selected = 0;
                                break;
                        }
                        break;
                    case true:
                        earlier_locations.push(location);
                        second_airport_analised = filteredWstringVector[page * elements_per_page + selected_in_page];
                        refreshDirectories();
                        location = 60;
                        chosenAirlines.clear();
                        directory = directories[location];
                        write = write_default;
                        selected_in_page = 0;
                        selected = 0;
                        page = 0;
                        table_mode = !table_mode;
                        filteredWstringVector = airlineCodeVector;
                        destiny = {second_airport_analised, 0};
                        break;
                }
                break;

            case 47:   //coords-->airport//
                switch (table_mode){
                    case false:
                        switch (selected){
                            case 1:
                                refreshDirectories();
                                location = earlier_locations.top();
                                if (locationOfAirportSearch[location]){filteredWstringVector = airportCodeVector;}
                                if (locationAirportNmeSearch[location]){filteredWstringVector = airportNameVector;}
                                if (locationOfCitySearch[location]){filteredWstringVector = citiesVector;}
                                if (locationOfAirlineSearch[location]){filteredWstringVector = airlineCodeVector;}
                                earlier_locations.pop();
                                directory = directories[location];
                                selected = 0;
                                break;
                            case 2:
                                refreshDirectories();
                                location = 1;
                                directory = directories[location];
                                stackClear(earlier_locations);
                                selected = 0;
                                break;
                        }
                        break;
                    case true:
                        earlier_locations.push(location);
                        second_airport_analised = filteredWstringVector[page * elements_per_page + selected_in_page];
                        refreshDirectories();
                        location = 60;
                        chosenAirlines.clear();
                        directory = directories[location];
                        write = write_default;
                        selected_in_page = 0;
                        selected = 0;
                        page = 0;
                        table_mode = !table_mode;
                        filteredWstringVector = airlineCodeVector;
                        destiny = {second_airport_analised, 0};
                        break;
                }
                break;

            case 48:     //coords -> city
                switch (table_mode) {
                    case false:
                        switch (selected) {
                            case 1:
                                refreshDirectories();
                                location = earlier_locations.top();
                                if (locationOfAirportSearch[location]){filteredWstringVector = airportCodeVector;}
                                if (locationAirportNmeSearch[location]){filteredWstringVector = airportNameVector;}
                                if (locationOfCitySearch[location]){filteredWstringVector = citiesVector;}
                                if (locationOfAirlineSearch[location]){filteredWstringVector = airlineCodeVector;}
                                earlier_locations.pop();
                                directory = directories[location];
                                selected = 0;
                                break;
                            case 2:
                                refreshDirectories();
                                location = 1;
                                directory = directories[location];
                                stackClear(earlier_locations);
                                selected = 0;
                                break;
                        }
                        break;
                    case true:
                        earlier_locations.push(location);
                        second_city_analised = filteredWstringVector[page * elements_per_page + selected_in_page];
                        refreshDirectories();
                        location = 60;
                        chosenAirlines.clear();
                        directory = directories[location];
                        write = write_default;
                        selected_in_page = 0;
                        selected = 0;
                        page = 0;
                        table_mode = !table_mode;
                        filteredWstringVector = airlineCodeVector;
                        destiny = {second_city_analised, 1};
                        break;
                }
                break;

            case 49:       // coords --> coords
                switch (selected) {
                    case 2:
                        if (canBeDouble(write) && canBeDouble(second_write)){
                            second_latitude_analised = write;
                            second_longitude_analised = second_write;
                            refreshDirectories();
                            earlier_locations.push(location);
                            location = 60;
                            chosenAirlines.clear();
                            directory = directories[location];
                            selected = 0;
                            coord_destiny = {second_latitude_analised, second_longitude_analised};
                            filteredWstringVector = airlineCodeVector;
                        }
                        break;
                    case 3:
                        refreshDirectories();
                        location = earlier_locations.top();
                        if (locationOfAirportSearch[location]){filteredWstringVector = airportCodeVector;}
                        if (locationAirportNmeSearch[location]){filteredWstringVector = airportNameVector;}
                        if (locationOfCitySearch[location]){filteredWstringVector = citiesVector;}
                        if (locationOfAirlineSearch[location]){filteredWstringVector = airlineCodeVector;}
                        earlier_locations.pop();
                        directory = directories[location];
                        selected = 0;
                        coord_destiny.first.clear();
                        coord_destiny.second.clear();
                        break;
                    case 4:
                        refreshDirectories();
                        location = 1;
                        directory = directories[location];
                        stackClear(earlier_locations);
                        selected = 0;
                        break;
                }
                write.clear();
                second_write.clear();
                break;

            case 50:           //city ---> coords
                switch (selected) {
                    case 2:
                        if (canBeDouble(write) && canBeDouble(second_write)){
                            second_latitude_analised = write;
                            second_longitude_analised = second_write;
                            refreshDirectories();
                            earlier_locations.push(location);
                            location = 60;
                            chosenAirlines.clear();
                            directory = directories[location];
                            selected = 0;
                            coord_destiny = {second_latitude_analised, second_longitude_analised};
                            filteredWstringVector = airlineCodeVector;
                        }
                        break;
                    case 3:
                        refreshDirectories();
                        location = earlier_locations.top();
                        if (locationOfAirportSearch[location]){filteredWstringVector = airportCodeVector;}
                        if (locationAirportNmeSearch[location]){filteredWstringVector = airportNameVector;}
                        if (locationOfCitySearch[location]){filteredWstringVector = citiesVector;}
                        if (locationOfAirlineSearch[location]){filteredWstringVector = airlineCodeVector;}
                        earlier_locations.pop();
                        directory = directories[location];
                        selected = 0;
                        coord_destiny.first.clear();
                        coord_destiny.second.clear();
                        break;
                    case 4:
                        refreshDirectories();
                        location = 1;
                        directory = directories[location];
                        stackClear(earlier_locations);
                        selected = 0;
                        break;
                }
                write.clear();
                second_write.clear();
                break;

            case 51:           //airport ---> coords
                switch (selected) {
                    case 2:
                        if (canBeDouble(write) && canBeDouble(second_write)){
                            second_latitude_analised = write;
                            second_longitude_analised = second_write;
                            refreshDirectories();
                            earlier_locations.push(location);
                            location = 60;
                            chosenAirlines.clear();
                            directory = directories[location];
                            selected = 0;
                            coord_destiny = {second_latitude_analised, second_longitude_analised};
                            filteredWstringVector = airlineCodeVector;
                        }
                        break;
                    case 3:
                        refreshDirectories();
                        location = earlier_locations.top();
                        if (locationOfAirportSearch[location]){filteredWstringVector = airportCodeVector;}
                        if (locationAirportNmeSearch[location]){filteredWstringVector = airportNameVector;}
                        if (locationOfCitySearch[location]){filteredWstringVector = citiesVector;}
                        if (locationOfAirlineSearch[location]){filteredWstringVector = airlineCodeVector;}
                        earlier_locations.pop();
                        directory = directories[location];
                        selected = 0;
                        coord_destiny.first.clear();
                        coord_destiny.second.clear();
                        break;
                    case 4:
                        refreshDirectories();
                        location = 1;
                        directory = directories[location];
                        stackClear(earlier_locations);
                        selected = 0;
                        break;
                }
                write.clear();
                second_write.clear();
                break;

            case 60:
                switch (table_mode) {
                    case false:
                        switch (selected) {
                            case 1:
                                chosenAirlines.clear();
                                break;
                            case 2:
                                chosenAirlines = airlineCodeVector;
                                break;
                            case 3:
                                if (!chosenAirlines.empty()){
                                    refreshDirectories();
                                    earlier_locations.push(location);
                                    location = 61;
                                    directory = directories[location];
                                    write = write_default;
                                    selected_in_page = 0;
                                    selected = 0;
                                    page = 0;
                                    getForbiddenAirlines();
                                }
                                break;
                            case 4:
                                refreshDirectories();
                                location = earlier_locations.top();
                                if (locationOfAirportSearch[location]){filteredWstringVector = airportCodeVector;}
                                if (locationAirportNmeSearch[location]){filteredWstringVector = airportNameVector;}
                                if (locationOfCitySearch[location]){filteredWstringVector = citiesVector;}
                                if (locationOfAirlineSearch[location]){filteredWstringVector = airlineCodeVector;}
                                earlier_locations.pop();
                                directory = directories[location];
                                selected = 0;
                                break;
                            case 5:
                                refreshDirectories();
                                location = 1;
                                directory = directories[location];
                                stackClear(earlier_locations);
                                selected = 0;
                                break;
                        }
                        break;
                    case true:
                        if(std::find(chosenAirlines.begin(), chosenAirlines.end(), filteredWstringVector[page * elements_per_page + selected_in_page]) == chosenAirlines.end()){
                            chosenAirlines.push_back(filteredWstringVector[page * elements_per_page + selected_in_page]);
                        }
                        else{
                            chosenAirlines.erase(std::find(chosenAirlines.begin(), chosenAirlines.end(), filteredWstringVector[page * elements_per_page + selected_in_page]));
                        }
                        refreshDirectories();
                        break;
                }
                break;

            case 61:       //========= STATISTICS > GLOBAL STATISTICS > NUMBER OF AVAILABLE FLIGHTS ==========//
                switch (selected) {
                    case 0:
                        refreshDirectories();
                        location = earlier_locations.top();
                        if (locationOfAirportSearch[location]){filteredWstringVector = airportCodeVector;}
                        if (locationAirportNmeSearch[location]){filteredWstringVector = airportNameVector;}
                        if (locationOfCitySearch[location]){filteredWstringVector = citiesVector;}
                        if (locationOfAirlineSearch[location]){filteredWstringVector = airlineCodeVector;}
                        earlier_locations.pop();
                        directory = directories[location];
                        airport_analised.clear();
                        second_airport_analised.clear();
                        city_analised.clear();
                        second_city_analised.clear();
                        latitude_analised.clear();
                        second_latitude_analised.clear();
                        longitude_analised.clear();
                        second_longitude_analised.clear();
                        selected = 0;
                        break;
                    case 1:
                        refreshDirectories();
                        location = 1;
                        directory = directories[location];
                        stackClear(earlier_locations);
                        selected = 0;
                        airport_analised.clear();
                        second_airport_analised.clear();
                        city_analised.clear();
                        second_city_analised.clear();
                        latitude_analised.clear();
                        second_latitude_analised.clear();
                        longitude_analised.clear();
                        second_longitude_analised.clear();
                        break;
                }
                break;
        }
    }
}


void Interface::inputResponseInWriteMode(wchar_t user_in){
    if (locationOfNumWrite[location]){
        if(isdigit(user_in)){
            if (num_write == num_write_default){
                num_write = L"";
            }
            num_write += user_in;
        }
        if (user_in == 8 || user_in == 127) {
            if (!num_write.empty()) {
                num_write.pop_back();
            }
        }
        if (num_write.empty()){
            num_write = num_write_default;
        }
        if (num_write.size() > capOfWrite[location]) {
            num_write.pop_back();
        }
    }
    else if (locationOfSecondWrite[location] && selected == 1){
        if (isdigit(user_in) || (ispunct(user_in))) {
            if (second_write == write_default) {
                second_write = L"";
            }
            second_write += user_in;
        }
        if (user_in == 32 && write != write_default) {
            second_write += L" ";
        }
        if ((user_in == 8 || user_in == 127) && second_write != write_default) {
            if (!second_write.empty()) {
                second_write.pop_back();
            }
        }
        if (second_write.empty()) {
            second_write = write_default;
        }
        if (second_write.size() > capOfWrite[location] && second_write != write_default) {
            second_write.pop_back();
        }
    }
    else{
        if ((isalpha(user_in) || isalnum(user_in) || (user_in >= 128 && user_in <= 255) || (ispunct(user_in))) && !locationOfSecondWrite[location]) {
            if (write == write_default) {
                write = L"";
            }
            write += user_in;
        }
        else if(isdigit(user_in) || (ispunct(user_in))){
            if (write == write_default) {
                write = L"";
            }
            write += user_in;
        }
        if (user_in == 32 && write != write_default) {
            write += L" ";
        }
        if ((user_in == 8 || user_in == 127) && write != write_default) {
            if (!write.empty()) {
                write.pop_back();
            }
        }
        if (write.empty()) {
            write = write_default;
        }
        if (write.size() > capOfWrite[location] && write != write_default) {
            write.pop_back();
        }
        if (locationOfAirportSearch[location]){
            filteredWstringVector = filterSearch(airportCodeVector);
            page = 0;
        }
        if (locationOfCitySearch[location]){
            filteredWstringVector = filterSearch(citiesVector);
            page = 0;
        }
        if (locationOfAirlineSearch[location]){
            filteredWstringVector = filterSearch(airlineCodeVector);
            page = 0;
        }
        if (locationAirportNmeSearch[location]){
            filteredWstringVector = filterSearch(airportNameVector);
            page = 0;
        }
    }
}


void Interface::inputer(){
    user_input = getwchar();
    if (!write_mode) {
        if (user_input == 27) {
            user_input = getwchar();
            user_input = getwchar();
        }
        basicInputResponse(user_input);
    }
    else{
        if (user_input == 27){
            user_input = getwchar();
            user_input = getwchar();
            write_mode = false;
            basicInputResponse(user_input);
        }
        else if ((user_input == '\n' || user_input == '\t') && locationHasTable[location]){
            write_mode = false;
            table_mode = true;
        }
        else{
            inputResponseInWriteMode(user_input);
        }
    }
}


void Interface::run(){
    setlocale(LC_CTYPE, "en_US.UTF-8"); // enconding to UTF-8 for extended characters such as "ç"

    struct termios oldt{}, newt{};
    tcgetattr(STDIN_FILENO, &oldt); // Get the current terminal settings

    newt = oldt; // Copy the current settings to the new settings

    newt.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode (line buffering) and echoing

    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // Set the new settings

    while(location != -1){

        system("clear");
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

        switch (location){
            case 0:       //============================= LOADING SCREEN ===============================//

                appThread = std::thread([this](){
                    app = std::make_shared<Application>();
                    airportsVector = app->getAirports();
                    getAirportCodes(airportsVector);
                    alphabeticSortVector(airportCodeVector);
                    getCities();
                    alphabeticSortVector(citiesVector);
                    airlineVector = app->getAirlines();
                    getAirlineCodes(airlineVector);
                    alphabeticSortVector(airlineCodeVector);
                    getAirportNames(airportsVector);
                    alphabeticSortVector(airportNameVector);
                    is_done = true;
                });

                while(!is_done){
                    printAnimatedAirplane(airplaneLoadingScreen, 100);
                    printTextLoadingData();
                    printMaximizeWarning();
                }
                is_done = false;
                appThread.join();

                location = 1;
                break;

            case 1:       //============================= MAIN MENU ===============================//

                printBoldTitle(tripInator);
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0});
                inputer();
                break;

            case 2:       //============================= STATISTICS ===============================//
                printDirectory(directory);
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0});
                inputer();
                break;

            case 3:       //==================== STATISTICS > GLOBAL STATISTICS ====================//
                printDirectory(directory);
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0});
                inputer();
                break;

            case 4:       //========= STATISTICS > GLOBAL STATISTICS > NUMBER OF AIRPORTS ==========//
                printDirectory(directory);
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0});
                printMonoinformation(L"There are " + bold + std::to_wstring(app->getAirportCount()) + end_effect + L" Airports");
                inputer();
                break;

            case 5:       //========= STATISTICS > GLOBAL STATISTICS > NUMBER OF AVAILABLE FLIGHTS ==========//
                printDirectory(directory);
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0});
                printMonoinformation(L"There are " + bold + std::to_wstring(app->getFlightCount()) + end_effect + L" Flights");
                inputer();
                break;

            case 6:       //========= STATISTICS > GLOBAL STATISTICS > TRIP(S) WITH THE MOST NUMBER OF STOPS ==========//
                printDirectory(directory);
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0});
                printGlobalStatisticsFurthestPathsInformation(furthest_trips);
                inputer();
                break;

            case 7:       //========= STATISTICS > CHOOSE AN AIRPORT ==========//
                printDirectory(directory);
                writeOptionDefaulterAirport();
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0, 1, 2});
                printTableAirportCode(filteredWstringVector, page, elements_per_page, selected_in_page, table_mode);
                inputer();
                break;

            case 8:       //========= STATISTICS > AIRPORT (X) ==========//
                printDirectory(directory);
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0});
                inputer();
                break;

            case 9:       //========= STATISTICS > AIRPORT X > NUMBER OF FLIGHTS OUT ==========//
                printDirectory(directory);
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0});
                printMonoinformation(L"There are " + bold + std::to_wstring(app->flightsOutboundOfAirport(converter.to_bytes(airport_analised))) + end_effect + L" Flights out of this Airport");
                inputer();
                break;

            case 10:       //========= STATISTICS > AIRPORT X > NUMBER OF AIRLINES OUT ==========//
                printDirectory(directory);
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0});
                printMonoinformation(L"There are " + bold + std::to_wstring(app->airlinesOutboundOfAirport(converter.to_bytes(airport_analised))) + end_effect + L" Airlines out of this Airport");
                inputer();
                break;

            case 11:       //========= STATISTICS > AIRPORT X > MORE INFO ==========//
                airport_analised_object = app->getAirport(converter.to_bytes(airport_analised));
                printDirectory(directory);
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0});
                printMonoinformation(L"The " + bold + airport_analised + end_effect + L" airport is named " + airport_analised_object.getWname() +
                                     L" and is located in " + airport_analised_object.getWcity() + L", " + airport_analised_object.getWcountry());
                printMonoinformation(L"Its coordinates are " + bold + airport_analised_object.getWlatitude() + L", " + airport_analised_object.getWlongitude() + end_effect);
                inputer();
                break;

            case 12:       //========= STATISTICS > AIRPORT X > NUMBER OF DESTINATIONS AVAILABLE ==========//
                printDirectory(directory);
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0});
                inputer();
                break;

            case 13:       //========= STATISTICS > AIRPORT X > NUMBER OF AIRPORT DESTINATIONS AVAILABLE ==========//
                printDirectory(directory);
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0});
                printMonoinformation(L"There are " + bold +
                                     std::to_wstring(app->numberOfAirportsFromAirport(converter.to_bytes(airport_analised)))
                                     + end_effect + L" airports reachable from this Airport");
                inputer();
                break;

            case 14:       //========= STATISTICS > AIRPORT X > NUMBER OF CITY DESTINATIONS AVAILABLE ==========//
                printDirectory(directory);
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0});
                printMonoinformation(L"There are " + bold +
                                     std::to_wstring(app->numberOfCitiesFromAirport(converter.to_bytes(airport_analised)))
                                     + end_effect + L" cities reachable from this Airport");
                inputer();
                break;

            case 15:       //========= STATISTICS > AIRPORT X > NUMBER OF COUNTRY DESTINATIONS AVAILABLE ==========//
                printDirectory(directory);
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0});
                printMonoinformation(L"There are " + bold +
                                     std::to_wstring(app->numberOfDifferentCountriesAirportFliesTo(converter.to_bytes(airport_analised)))
                                     + end_effect + L" countries reachable from this Airport");
                inputer();
                break;

            case 16:       //========= STATISTICS > AIRPORT X > NUMBER OF DESTINATIONS AVAILABLE WITH STEPS ==========//
                printDirectory(directory);
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0});
                inputer();
                break;

            case 17:      //========= STATISTICS > AIRPORT X > NUMBER OF AIRPORT DESTINATIONS AVAILABLE WITH STEPS ==========//
                printDirectory(directory);
                numeralWriteOptionsDefaulter();
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0});
                printMonoinformation(L"There are " + bold +
                                     std::to_wstring(app->numberOfAirportsFromAirportWithStops(converter.to_bytes(airport_analised), std::stoi(num_write)))
                                     + end_effect + L" airports reachable from this Airport in within " + num_write + L" stops");
                inputer();
                break;

            case 18:       //========= STATISTICS > AIRPORT X > NUMBER OF CITY DESTINATIONS AVAILABLE WITH STEPS ==========//
                printDirectory(directory);
                numeralWriteOptionsDefaulter();
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0});
                printMonoinformation(L"There are " + bold +
                                     std::to_wstring(app->numberOfCitiesFromAirportWithStops(converter.to_bytes(airport_analised), std::stoi(num_write)))
                                     + end_effect + L" cities reachable from this Airport in within " + num_write + L" stops");
                inputer();
                break;

            case 19:       //========= STATISTICS > AIRPORT X > NUMBER OF COUNTRY DESTINATIONS AVAILABLE WITH STEPS ==========//
                printDirectory(directory);
                numeralWriteOptionsDefaulter();
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0});
                printMonoinformation(L"There are " + bold +
                                     std::to_wstring(app->numberOfCountriesFromAirportWithStops(converter.to_bytes(airport_analised), std::stoi(num_write)))
                                     + end_effect + L" countries reachable from this Airport in within " + num_write + L" stops");
                inputer();
                break;

            case 20:       //========= STATISTICS > CHOOSE A CITY ==========//
                printDirectory(directory);
                writeOptionDefaulterCity();
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0, 1, 2});
                printTableAirportCode(filteredWstringVector, page, elements_per_page, selected_in_page, table_mode);
                inputer();
                break;

            case 21:       //========= STATISTICS > X CITY ==========//
                printDirectory(directory);
                printOptions(options[location], selected, table_mode);
                printHelper(helpers,{0});
                inputer();
                break;

            case 22:      //========= STATISTICS > X CITY > NUMBER OF FLIGHTS IN THIS CITY ==========//
                printDirectory(directory);
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0});
                printMonoinformation(L"There are " + bold +
                                     std::to_wstring(app->totalFlightsPerCity(converter.to_bytes(city_analised))) +
                                     end_effect + L" total flights in this city, where " +
                                     std::to_wstring(app->inboundFlightsPerCity(converter.to_bytes(city_analised))) +
                                     L" are inside the city boundaries and " +
                                     std::to_wstring(app->outboundFlightsPerCity(converter.to_bytes(city_analised))) +
                                     L" go outside the city boundaries");
                inputer();
                break;

            case 23:      //========= STATISTICS > X CITY > NUMBER OF DIFFERENT COUNTRIES THIS CITY FLIES TO ==========//
                printDirectory(directory);
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0});
                printMonoinformation(L"This city flies to " + bold +
                                     std::to_wstring(app->numberOfDifferentCountriesCityFliesTo(converter.to_bytes(city_analised))) +
                                     end_effect + L" different countries");
                inputer();
                break;

            case 24:      //========= STATISTICS > CHOOSE AN AIRLINE ==========//
                printDirectory(directory);
                writeOptionDefaulterAirline();
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0, 1, 2});
                printTableAirportCode(filteredWstringVector, page, elements_per_page, selected_in_page, table_mode);
                inputer();
                break;

            case 25:      //========= STATISTICS > X AIRLINE ==========//
                printDirectory(directory);
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0});
                inputer();
                break;
            case 26:      //========= STATISTICS > X AIRLINE > MORE INFO ==========//
                airline_analised_object = app->getAirline(converter.to_bytes(airline_analised));
                printDirectory(directory);
                printOptions(options[location], selected, table_mode);
                printMonoinformation(L"The " + bold + airline_analised + end_effect + L" Airline is called " +
                                     airline_analised_object.getWname() + L", and it's callsign is " + airline_analised_object.getWcallsign());
                printMonoinformation(L"This airline is from " + bold + airline_analised_object.getWcountry() + end_effect);
                printHelper(helpers, {0});
                inputer();
                break;

            case 27:      //========= STATISTICS > X AIRLINE > NUMBER OF FLIGHTS ==========//
                printDirectory(directory);
                printOptions(options[location], selected, table_mode);
                printMonoinformation(L"This airline has " + bold + std::to_wstring(app->flightsPerAirline(
                        converter.to_bytes(airline_analised)))
                                     + end_effect + L" flights");
                printHelper(helpers, {0});
                inputer();
                break;

            case 28:      //========= STATISTICS > GLOBAL STATISTICS > TOP K AIRPORTS GREATEST TRAFFIC ==========//
                printDirectory(directory);
                numeralWriteOptionsDefaulter2();
                printOptions(options[location], selected, table_mode);
                temporaryAirportCodeVector.clear();
                getTemporaryAirportCodes(app->airportsWithGreatestTrafficCapacity(std::stoi(num_write)));
                filteredWstringVector = temporaryAirportCodeVector;
                printHelper(helpers, {0, 1, 2});
                printTableAirportCode(filteredWstringVector, page, elements_per_page, selected_in_page, table_mode);
                inputer();
                break;

            case 29:      //========= STATISTICS > GLOBAL STATISTICS  > ESSENTIAL AIRPORTS ==========//
                printDirectory(directory);
                printOptions(options[location], selected, table_mode);
                temporaryAirportCodeVector.clear();
                getTemporaryAirportCodesFromSet(app->essentialAirports());
                filteredWstringVector = temporaryAirportCodeVector;
                printHelper(helpers, {0, 1, 2});
                printTableAirportCode(filteredWstringVector, page, elements_per_page, selected_in_page, table_mode);
                inputer();
                break;

            case 30:      //========= FLIGHTS ==========//
                printDirectory(directory);
                printMiniTitle(L"Choose a way to get the " + bold + L"Starting Airport" + end_effect);
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0});
                inputer();
                break;

            case 31:      //========= FLIGHTS > Choose an airport ==========//
                printDirectory(directory);
                writeOptionDefaulterAirport();
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0, 1, 2});
                printTableAirportCode(filteredWstringVector, page, elements_per_page, selected_in_page, table_mode);
                inputer();
                break;

            case 32:     //========= FLIGHTS > From Airport X // ==========//
                printDirectory(directory);
                printMiniTitle(L"Choose a way to get the " + bold + L"Destiny Airport" + end_effect);
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0});
                inputer();
                break;

            case 33:      //========= FLIGHTS > From Airport X // > Choose an airport ==========//
                printDirectory(directory);
                writeOptionDefaulterAirport();
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0, 1, 2});
                printTableAirportCode(filteredWstringVector, page, elements_per_page, selected_in_page, table_mode);
                inputer();
                break;

            case 35:      //========= FLIGHTS > From Airport X Name  ==========//
                printDirectory(directory);
                writeOptionDefaulterAirportName();
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0, 1, 2});
                printTableAirportCode(filteredWstringVector, page, elements_per_page, selected_in_page, table_mode);
                inputer();;
                break;

            case 36:      //========= FLIGHTS > From Airport X Name > To ... ==========//
                printDirectory(directory);
                writeOptionDefaulterAirportName();
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0, 1, 2});
                printTableAirportCode(filteredWstringVector, page, elements_per_page, selected_in_page, table_mode);
                inputer();;
                break;

            case 38:      //"Book a Flight > Choose a City by Name"//
                printDirectory(directory);
                writeOptionDefaulterCity();
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0, 1, 2});
                printTableAirportCode(filteredWstringVector, page, elements_per_page, selected_in_page, table_mode);
                inputer();
                break;

            case 39:         //"Book a Flight > Choose a City by Name" > to...//
                printDirectory(directory);
                printMiniTitle(L"Choose a way to get the " + bold + L"Destiny Airport" + end_effect);
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0});
                inputer();
                break;

            case 40:        //"Book a Flight > Choose a City by Name" > to Airport code//
                printDirectory(directory);
                writeOptionDefaulterAirport();
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0, 1, 2});
                printTableAirportCode(filteredWstringVector, page, elements_per_page, selected_in_page, table_mode);
                inputer();
                break;

            case 41:        //"Book a Flight > Choose a City by Name" > to Airport name//
                printDirectory(directory);
                writeOptionDefaulterAirportName();
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0, 1, 2});
                printTableAirportCode(filteredWstringVector, page, elements_per_page, selected_in_page, table_mode);
                inputer();
                break;

            case 42:      //"Book a Flight > Choose a City by Name> City"//
                printDirectory(directory);
                writeOptionDefaulterCity();
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0, 1, 2});
                printTableAirportCode(filteredWstringVector, page, elements_per_page, selected_in_page, table_mode);
                inputer();
                break;

            case 43:        //"Book a Flight > Airport > City"//
                printDirectory(directory);
                writeOptionDefaulterCity();
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0, 1, 2});
                printTableAirportCode(filteredWstringVector, page, elements_per_page, selected_in_page, table_mode);
                inputer();
                break;

            case 44:            //"Book a Flight > Coords"//
                printDirectory(directory);
                writeOptionDefaulterCoords();
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0});
                inputer();
                break;

            case 45:            //"Book a Flight > Coords > to..."//
                printDirectory(directory);
                printMiniTitle(L"Choose a way to get the " + bold + L"Destiny Airport" + end_effect);
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0});
                inputer();
                break;

            case 46:        //Coords to -> airport code//
                printDirectory(directory);
                writeOptionDefaulterAirport();
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0, 1, 2});
                printTableAirportCode(filteredWstringVector, page, elements_per_page, selected_in_page, table_mode);
                inputer();
                break;

            case 47:        //Coords to -> airport name//
                printDirectory(directory);
                writeOptionDefaulterAirport();
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0, 1, 2});
                printTableAirportCode(filteredWstringVector, page, elements_per_page, selected_in_page, table_mode);
                inputer();
                break;

            case 48:      //"Book a Flight > Choose a City by Name> City"//
                printDirectory(directory);
                writeOptionDefaulterCity();
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0, 1, 2});
                printTableAirportCode(filteredWstringVector, page, elements_per_page, selected_in_page, table_mode);
                inputer();
                break;

            case 49:            //"Book a Flight > Coords -> Coords"//
                printDirectory(directory);
                writeOptionDefaulterCoords();
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0});
                inputer();
                break;

            case 50:            //"Book a Flight > City -> Coords"//
                printDirectory(directory);
                writeOptionDefaulterCoords();
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0});
                inputer();
                break;

            case 51:            //"Book a Flight > Airport -> Coords"//
                printDirectory(directory);
                writeOptionDefaulterCoords();
                printOptions(options[location], selected, table_mode);
                printHelper(helpers, {0});
                inputer();
                break;

            case 60:           //"Choose airlines"//
                printDirectory(directory);
                writeOptionDefaulterAirline();
                printOptions(options[location], selected, table_mode);
                printAirlinesChosen(chosenAirlines);
                printHelper(helpers, {0, 1, 3});
                printTableAirportCode(filteredWstringVector, page, elements_per_page, selected_in_page, table_mode);
                inputer();
                break;

            case 61:
                if (!(coord_origin.first.empty())){
                    directory = L"Book a Flight > From " + coord_origin.first + L", " + coord_origin.second + L" Coords > To ";
                }
                else{
                    if (origin.second){
                        directory = L"Book a Flight > From " + origin.first + L" City > To ";
                    }
                    else{
                        directory = L"Book a Flight > From " + origin.first + L" Airport > To ";
                    }
                }

                if (!(coord_destiny.first.empty())){
                    directory += coord_destiny.first + L", " + coord_destiny.second + L" Coords";
                }
                else{
                    if (destiny.second){
                        directory += destiny.first + L" City";
                    }
                    else{
                        directory += destiny.first + L" Airport";
                    }
                }
                printDirectory(directory);
                printOptions(options[location], selected, table_mode);
                if (!coord_origin.first.empty()){
                    if (!coord_destiny.first.empty()){
                        possiblePaths = app->bestFlightLocationToLocation(
                                std::stod(coord_origin.first), std::stod(coord_origin.second)
                                , std::stod(coord_destiny.first), std::stod(coord_destiny.second), forbiddenAirlines);
                    }
                    else if (destiny.second){
                        possiblePaths = app->bestFlightLocationToCity(
                                std::stod(coord_origin.first), std::stod(coord_origin.second)
                                , converter.to_bytes(destiny.first), forbiddenAirlines);
                    }
                    else {
                        possiblePaths = app->bestFlightLocationToAirport(
                                std::stod(coord_origin.first), std::stod(coord_origin.second)
                                , converter.to_bytes(destiny.first), forbiddenAirlines);
                    }
                }
                else if (origin.second){
                    if (!coord_destiny.first.empty()){
                        possiblePaths = app->bestFlightCityToLocation(
                                converter.to_bytes(origin.first)
                                , std::stod(coord_destiny.first), std::stod(coord_destiny.second), forbiddenAirlines);
                    }
                    else if (destiny.second){
                        possiblePaths = app->bestFlightCityToCity(
                                converter.to_bytes(origin.first)
                                , converter.to_bytes(destiny.first), forbiddenAirlines);
                    }
                    else {
                        possiblePaths = app->bestFlightCityToAirport(
                                converter.to_bytes(origin.first)
                                , converter.to_bytes(destiny.first), forbiddenAirlines);
                    }
                }
                else{
                    if (!coord_destiny.first.empty()){
                        possiblePaths = app->bestFlightAirportToLocation(
                                converter.to_bytes(origin.first)
                                , std::stod(coord_destiny.first), std::stod(coord_destiny.second), forbiddenAirlines);
                    }
                    else if (destiny.second){
                        possiblePaths = app->bestFlightAirportToCity(
                                converter.to_bytes(origin.first)
                                , converter.to_bytes(destiny.first), forbiddenAirlines);
                    }
                    else {
                        possiblePaths = app->bestFlightAirportToAirport(
                                converter.to_bytes(origin.first)
                                , converter.to_bytes(destiny.first), forbiddenAirlines);
                    }
                }
                printHelper(helpers, {0});
                printPossiblePaths(possiblePaths, app, chosenAirlines);
                inputer();
                break;
        }
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); //restore old terminal

    system("clear");
}