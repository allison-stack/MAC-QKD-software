#include <Arduino.h>

// Alice Skeleton Code


void setup() {
  // time syncronizatoin with bob
    // wifi connect to server get time (turn wifi off when done)

  // determine key length
    // account for the fact that they will loose some bits so add approx 50% more bits to basis selection and bits sent

  // determine basis slection at begining and store in array
    // X amount of random basis
    // this will save clock cycles in the loop where we are sending bits

  // need to decide whether this only happens once or the key generation is a continuos process
  
  // loop with counter for X number of bits 
    // use the random basis array to change to the basis at the specified index 
    // send a pulse
    // record the time that the pulse was sent and put that with the corresponding basis index
    // possibly add delay to ensure that Bob has enough time to recieve the bit

  // send data to Bob
    // array of basis and timestamps
  
  // recive Bobs data
    // compare the timestamps to ensure the bit sent is the same bit recieved
    // if the bits are the same compare basis selection
      // if basis are same keep bit for the key (if not discard the bit)

  
}


void loop() {

}