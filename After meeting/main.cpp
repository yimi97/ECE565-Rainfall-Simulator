#include <iostream>
#include "landscape.h"

// Return if completed
bool first_trav(Landscape& myLS, bool isRaining){
    
    //  1) Receive a new raindrop (if it is still raining) for each point.
    if(isRaining) {
        myLS.receive_new();
    }

    //  2) If there are raindrops on a point, absorb water into the point
    myLS.absorb();

    // Check completion (need confirmation with Brian)
    if(!isRaining && myLs.isComplete()) {
        return true;
    }

    //  3a) Calculate the number of raindrops that will next trickle to the lowest neighbor(s)
    myLS.cal_trickle();

    return false;
}

void second_trav(Landscape& myLS){
    
    //  3b) For each point, use the calculated number of raindrops that will trickle to the
    //      lowest neighbor(s) to update the number of raindrops at each lowest neighbor, if
    //      applicable.
    myLS.trickle();

}

int main(int argc, char *argv[])
{
    // CLI arguments check
    /** Code here **/

    // Create landscape
    Landscape myLandscape;
    int timestep;

    // Time passing
    for(timestep=0;timestep<M;++timestep) {
        first_trav(myLandscape, true); // Traverse over all landscape points
        second_trav(myLandscape); // Make a second traversal over all landscape points
    
    }

    while (!isComplete) {
        bool isComplete = first_trav(myLandscape, false);
        second_trav(myLandscape);
        timestep++;
    }
    
    

    // Print result
    print_result();

    return 0;

}

// // Error control: syntax
//     if (argc != 3) {
//         cerr << "Error: Wrong command syntax, check your manual!" << endl;
//         exit(EXIT_FAILURE);
//     } 


//     string machine_name (argv[1]); // Host name
//     int port_num = atoi(argv[2]);  // Port number

//     // Error control: port number out of range
//     if ( port_num < 0 || port_num > 65535) {
//         cerr << "Error: Invalid port number!" << endl;
//         exit(EXIT_FAILURE);
//     } 