#include "TQueue.h"
#include <iostream>

// writer
int main()
{
    TQueue queue;
    TMessage message;
    char messageText[TMessage::messageSize];
    
    // messageText = "msg777\0"
    messageText[0] = 'm'; messageText[1] = 's'; messageText[2] = 'g';
    messageText[3] = '7'; messageText[4] = '7'; messageText[5] = '7';
    messageText[6] = '\0';

    message.setMessage(messageText);

    queue.addElem(message);

    std::cout << "\nelem was send\n";

    return 0;
}
