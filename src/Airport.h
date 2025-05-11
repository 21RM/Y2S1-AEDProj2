//
// Created by alexandre on 21-12-2023.
//

#ifndef AED_PROJ_2_AIRPORT_H
#define AED_PROJ_2_AIRPORT_H

#include <string>
#include <iostream>

/**
 * @class Airport
 *
 * @brief Represents an airport with code, name, city, country, and geographical coordinates.
 */
class Airport {
    std::string code_; /**< The code of the airport. */
    std::string name_; /**< The name of the airport. */
    std::string city_; /**< The city where the airport is located. */
    std::string country_; /**< The country where the airport is located. */
    long double latitude_; /**< The latitude of the airport. */
    long double longitude_; /**< The longitude of the airport. */
    std::wstring wcode_; /**< Wide string representation of the airport code. */
    std::wstring wname_; /**< Wide string representation of the airport name. */
    std::wstring wcity_; /**< Wide string representation of the airport city. */
    std::wstring wcountry_; /**< Wide string representation of the airport country. */
    std::wstring wlatitude_; /**< Wide string representation of the airport latitude. */
    std::wstring wlongitude_; /**< Wide string representation of the airport longitude. */
    size_t trafficCapacity_ = 0; /**< The traffic capacity of the airport. */

public:
    /**
     * @brief Constructs an Airport object with specified details.
     *
     * @param code The code of the airport.
     * @param name The name of the airport.
     * @param city The city where the airport is located.
     * @param country The country where the airport is located.
     * @param latitude The latitude of the airport.
     * @param longitude The longitude of the airport.
     */
    Airport(const std::string &code, const std::string &name, const std::string &city, const std::string &country,
            const std::string &latitude, const std::string &longitude);

    /**
     * @brief Default constructor for the Airport class.
     */
    Airport();

    /**
     * @brief Dummy constructor for creating an Airport object with a given code.
     *
     * @param code The code of the airport.
     */
    Airport(const std::string &code);

    /**
     * @brief Gets the code of the airport.
     *
     * @return The code of the airport.
     */
    const std::string &getCode() const;

    /**
     * @brief Checks if two airports are equal.
     *
     * @param other The other Airport object for comparison.
     * @return True if the airports are equal, false otherwise.
     */
    bool operator==(const Airport &other) const;

    /**
     * @brief Output stream operator to print airport information.
     *
     * @param stream The output stream.
     * @param airport The Airport object to be printed.
     * @return The output stream after printing.
     */
    friend std::ostream& operator<<(std::ostream &stream, const Airport &airport);

    /**
     * @brief Gets the city where the airport is located.
     *
     * @return The city of the airport.
     */
    const std::string &getCity() const;

    /**
     * @brief Gets the country where the airport is located.
     *
     * @return The country of the airport.
     */
    const std::string &getCountry() const;

    /**
     * @brief Gets the wide string representation of the airport code.
     *
     * @return The wide string representation of the airport code.
     */
    const std::wstring &getWcode() const;

    /**
     * @brief Checks if the current airport is less than another airport based on code.
     *
     * @param obj The other Airport object for comparison.
     * @return True if the current airport is less than the other, false otherwise.
     */
    bool operator<(const Airport &obj) const;

    /**
     * @brief Sets the traffic capacity of the airport.
     *
     * @param capacity The traffic capacity to be set.
     */
    void setTrafficCapacity(size_t capacity);

    /**
     * @brief Gets the traffic capacity of the airport.
     *
     * @return The traffic capacity of the airport.
     */
    size_t getTrafficCapacity() const;

    /**
     * @brief Gets the wide string representation of the airport name.
     *
     * @return The wide string representation of the airport name.
     */
    const std::wstring &getWname() const;

    /**
     * @brief Gets the wide string representation of the airport city.
     *
     * @return The wide string representation of the airport city.
     */
    const std::wstring &getWcity() const;

    /**
     * @brief Gets the wide string representation of the airport country.
     *
     * @return The wide string representation of the airport country.
     */
    const std::wstring &getWcountry() const;

    /**
     * @brief Gets the wide string representation of the airport latitude.
     *
     * @return The wide string representation of the airport latitude.
     */
    const std::wstring &getWlatitude() const;

    /**
     * @brief Gets the wide string representation of the airport longitude.
     *
     * @return The wide string representation of the airport longitude.
     */
    const std::wstring &getWlongitude() const;

    /**
     * @brief Gets the name of the airport.
     *
     * @return The name of the airport.
     */
    const std::string &getName() const;

    /**
     * @brief Gets the latitude of the airport.
     *
     * @return The latitude of the airport.
     */
    const long double &getLatitude() const;

    /**
     * @brief Gets the longitude of the airport.
     *
     * @return The longitude of the airport.
     */
    const long double &getLongitude() const;

};


#endif //AED_PROJ_2_AIRPORT_H
