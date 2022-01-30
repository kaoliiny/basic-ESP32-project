# basic-ESP32-project
This is a simple ESP32 firmware that displays queue data

This program has basically two tasks:
1. dataQueueUpdate - Updates the counter each 5s and put its value to queue. Records the time of this operation.
2. displayQueueData - Receives and displays data from queue.

To compile it checkout to develop branch and build the project by:
 idf.py -C . build
to flash:
 idf.py -C . flash
