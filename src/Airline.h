//
// Created by alexandre on 21-12-2023.
//

#ifndef AED_PROJ_2_AIRLINE_H
#define AED_PROJ_2_AIRLINE_H

#include <string>

/**
 * @brief Represents an airline with various information such as code, name, callsign, and country.
 */
class Airline {
    std::string code_;         /**< The airline code. */
    std::string name_;         /**< The name of the airline. */
    std::string callsign_;     /**< The callsign used by the airline. */
    std::string country_;      /**< The country where the airline is based. */
    std::wstring wcode_;       /**< The wide string representation of the airline code. */
    std::wstring wname_;       /**< The wide string representation of the airline name. */
    std::wstring wcallsign_;   /**< The wide string representation of the airline callsign. */
    std::wstring wcountry_;    /**< The wide string representation of the airline country. */

public:
    /**
     * @brief Constructor for the Airline class.
     * @param code The airline code.
     * @param name The name of the airline.
     * @param callsign The callsign used by the airline.
     * @param country The country where the airline is based.
     */
    Airline(const std::string &code, const std::string &name, const std::string &callsign, const std::string &country);

    /**
     * @brief Default constructor for the Airline class.
     */
    Airline();

    /**
     * @brief Getter function for the airline code.
     * @return The airline code.
     */
    const std::string &getCode() const;

    /**
     * @brief Getter function for the wide string representation of the airline code.
     * @return The wide string representation of the airline code.
     */
    const std::wstring &getWcode() const;

    /**
     * @brief Getter function for the wide string representation of the airline name.
     * @return The wide string representation of the airline name.
     */
    const std::wstring &getWname() const;

    /**
     * @brief Getter function for the wide string representation of the airline callsign.
     * @return The wide string representation of the airline callsign.
     */
    const std::wstring &getWcallsign() const;

    /**
     * @brief Getter function for the wide string representation of the airline country.
     * @return The wide string representation of the airline country.
     */
    const std::wstring &getWcountry() const;

    /**
     * @brief Equality comparison operator for the Airline class.
     * @param other Another Airline object to compare with.
     * @return True if the two objects are equal, false otherwise.
     */
    bool operator==(const Airline &other) const;
};


#endif //AED_PROJ_2_AIRLINE_H
