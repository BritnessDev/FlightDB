// Interface to the Flight DB ADT

// !!! DO NOT MODIFY THIS FILE !!!

#ifndef FLIGHT_DB_H
#define FLIGHT_DB_H

#include "List.h"
#include "Record.h"

typedef struct flightDb *FlightDb;

/**
 * Creates a new flight DB
 */
FlightDb DbNew(void);

/**
 * Frees all memory associated with the given DB
 */
void DbFree(FlightDb db);

/**
 * Inserts a flight record into the DB if the DB does not already contain
 * a record with the same flight number and departure day, hour and minute.
 * Returns true if the record was inserted into the DB, and false if the
 * DB already contained a record with the same flight number and departure
 * day, hour and minute.
 * The worst-case time complexity of this function must be O(log n).
 */
bool DbInsertRecord(FlightDb db, Record r);

/**
 * Searches for all records with the given flight number, and returns
 * them all in a list in increasing order of departure time (day, hour,
 * min). Returns an empty list if there are no such records.
 * The worst-case time complexity of this function must be O(m + log n),
 * where m is the length of the returned list.
 */
List DbFindByFlightNumber(FlightDb db, char *flightNumber);

/**
 * Searches for all records with the given departure airport and day of
 * week, and returns them all in a list in increasing order of (hour,
 * min, flight number). Returns an empty list if there are no such records.
 * The worst-case time complexity of this function must be O(m + log n),
 * where m is the length of the returned list.
 */
List DbFindByDepartureAirportDay(FlightDb db, char *departureAirport,
                                 int day);

/**
 * Searches for all records with departure times between (day1, hour1,
 * min1) and (day2, hour2, min2), and returns them all in a list in
 * increasing order of (day, hour, min, flight number). Returns an empty
 * list if there are no such records.
 * Note: See the spec for more details.
 * The worst-case time complexity of this function must be O(m + log n),
 * where m is the length of the returned list.
 */
List DbFindBetweenTimes(FlightDb db, 
                        int day1, int hour1, int min1, 
                        int day2, int hour2, int min2);

/**
 * Searches for and returns the earliest next flight with the given flight
 * number, on or after the given (day, hour, min), or NULL if there is no
 * such flight.
 * The worst-case time complexity of this function must be O(log n).
 */
Record DbFindNextFlight(FlightDb db, char *flightNumber, 
                        int day, int hour, int min);

#endif

