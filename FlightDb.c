// Implementation of the Flight DB ADT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FlightDb.h"
#include "List.h"
#include "Tree.h"

// • Flights with the same flight number will always have the same departure and arrival airports 
// • The flight schedule is the same every week 
// • departureDay is between 0 and 6 o 0 for Monday, 1 for Tuesday, ... , 6 for Sunday 
// • departureHour is between 0 and 23 • departureMinute is between 0 and 59 • durationMinutes indicates the duration of the flight in minutes 

typedef struct node *Node;
struct node {
    Record rec;
    Node   left;
    Node   right;

    // IMPORTANT: Do not modify the fields above
    // You may add additional fields below if necessary
    
};

struct flightDb {
    Tree tree;
    // char flightNumber[MAX_FLIGHT_NUMBER + 1];
    // char departureAirport[MAX_AIRPORT_NAME + 1];
    // char arrivalAirport[MAX_AIRPORT_NAME + 1];
    // int departureDay;    // 0 for Monday, ... , 6 for Sunday
    // int departureHour;   // Between 0 and 23 (inclusive)
    // int departureMinute; // Between 0 to 59 (inclusive)
    // int durationMinutes; // Duration of the flight, in minutes

};

//compare function for tree
int compareFlightNumber(Record r1, Record r2) {
    return strcmp(RecordGetFlightNumber(r1), RecordGetFlightNumber(r2));
}

//compare function for tree
int compareDepartureAirport(Record r1, Record r2) {
    return strcmp(RecordGetDepartureAirport(r1), RecordGetDepartureAirport(r2));
}

//compare function for tree
int compareArrivalAirport(Record r1, Record r2) {
    return strcmp(RecordGetArrivalAirport(r1), RecordGetArrivalAirport(r2));
}

//compare function for tree
int compareDepartureDay(Record r1, Record r2) {
    return RecordGetDepartureDay(r1) - RecordGetDepartureDay(r2);
}

//compare function for tree
int compareDepartureHour(Record r1, Record r2) {
    return RecordGetDepartureHour(r1) - RecordGetDepartureHour(r2);
}

//compare function for tree
int compareDepartureMinute(Record r1, Record r2) {
    return RecordGetDepartureMinute(r1) - RecordGetDepartureMinute(r2);
}

//compare function for tree
int compareDurationMinutes(Record r1, Record r2) {
    return RecordGetDurationMinutes(r1) - RecordGetDurationMinutes(r2);
}





// Creates a new flight database
FlightDb DbNew(void) {

    // create a new flightDb
    FlightDb newDb = malloc(sizeof(struct flightDb));
    if (newDb == NULL) {
        fprintf(stderr, "error: couldn't allocate memory for new flightDb");
        return NULL;
    }

    // create a new tree
    newDb->tree = TreeNew(compareFlightNumber);
    if (newDb->tree == NULL) {
        fprintf(stderr, "error: couldn't allocate memory for new tree");
        return NULL;
    }

    return newDb;

}




void DbFree(FlightDb db) {
    /* Description: Frees all memory associated with the given flight database.
        * 
        * Precondition: db is not NULL.
        * 
        * Postcondition: All memory associated with db has been freed.
        
        Returns: Nothing.
        Arguments: db - the flight database to be freed.
        
    */


    // free the tree
    TreeFree(db->tree, true);

    // free the flightDb
    free(db);

}

bool DbInsertRecord(FlightDb db, Record r) {
    /* Description: Inserts the given record into the given flight database.
    Returns true if the record was inserted, false if the record was already
    in the database.

    Return Type : bool
    Argument 1 : FlightDb db
    Argument 2 : Record r
    */

    // insert the record into the tree
    return TreeInsert(db->tree, r);
    
}



List DbFindByFlightNumber(FlightDb db, char *flightNumber) {
    /* Description: Returns a list of all records in the given flight database
    that have the given flight number. The list is sorted by departure time.

    Return Type : List
    Argument 1 : FlightDb db
    Argument 2 : char *flightNumber
    */

    // create a new list
    List list = ListNew();

    // create a new record
    Record rec = RecordNew(flightNumber, "", "", 0, 0, 0, 0);

    // find the record in the tree
    Record r = TreeSearch(db->tree, rec);

    // find all records with the same flight number
    while (r != NULL) {
        ListAppend(list, r);
        r = TreeNext(db->tree, r);

    }
    
    // free the record
    RecordFree(rec);



    return list;



}




void Recordfree(Record r) {
    free(r);
}

List DbFindByDepartureAirportDay(FlightDb db, char *departureAirport,
                                 int day) {
    /* Description: Returns a list of all records in the given flight database
    that have the given departure airport and departure day. The list is sorted
    by departure time.

    Return Type : List
    Argument 1 : FlightDb db
    Argument 2 : char *departureAirport
    Argument 3 : int day
    */

   return ListNew();


}

List DbFindBetweenTimes(FlightDb db, 
                        int day1, int hour1, int min1, 
                        int day2, int hour2, int min2) {
    return ListNew();
}

Record DbFindNextFlight(FlightDb db, char *flightNumber, 
                        int day, int hour, int min) {
    return NULL;
}

