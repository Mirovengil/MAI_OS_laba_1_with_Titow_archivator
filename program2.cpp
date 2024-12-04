#include "TQueue.h"
#include "TMessage.h"
#include "TBytesArray.h"
#include "TBytesArrayFiller.h"
#include "TCryptographer.h"
#include "TTxtWriter.h"

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>

int getFirstIntFromMessage(TMessage &message);
int getSecondIntFromMessage(TMessage &message);
void startProgram1(std::string mesage);

int main()
{
    TQueue queue;
    TMessage message;
    int numberOfMessages;
    int numberOfBytes;


    std::cout << "Program 1 start #1:\n";
    std::cout << "------------------------\n";
    
    startProgram1("./out.txt");

    queue.waitForReceiving();
    message = queue.popElem();
    numberOfMessages = getFirstIntFromMessage(message);
    numberOfBytes = getSecondIntFromMessage(message);
    
    TBytesArray str1(numberOfBytes);
    TBytesArrayFiller filler1(&str1);

    for (int i = 0; i < numberOfMessages; ++i)
    {
        queue.waitForReceiving();
        message = queue.popElem();
        filler1.fillWithMessage(message);
        std::cout << "Message #" << i << " received: \"" << message.getMessageStr() << "\"\n";
    }

    queue.close();

    std::cout << "Result: \"" << str1.getAsString() << "\"\n";

    std::cout << "------------------------\n"; 
    std::cout << "Program 1 start #2:\n";
    std::cout << "------------------------\n"; 

    queue = TQueue();
    startProgram1("./key.txt");

    queue.waitForReceiving();
    message = queue.popElem();
    numberOfMessages = getFirstIntFromMessage(message);
    numberOfBytes = getSecondIntFromMessage(message);

    TBytesArray str2(numberOfBytes);
    TBytesArrayFiller filler2(&str2);

    for (int i = 0; i < numberOfMessages; ++i)
    {
        queue.waitForReceiving();
        message = queue.popElem();
        filler2.fillWithMessage(message);
        std::cout << "Message #" << i << " received: \"" << message.getMessageStr() << "\"\n";
    }

    std::cout << "Result: \"" << str2.getAsString() << "\"\n";

    TCryptographer crypto;
    TBytesArray str3 = crypto.doCrypto(str1, str2);

    TTxtWriter fileWriter;
    fileWriter.open("out2.txt");
    fileWriter.write(str3);
    fileWriter.close();

    return 0;
}

int getFirstIntFromMessage(TMessage &message)
{
    int value;
    memcpy(&value, message.getMessage(), sizeof(int));
    return value;
}

int getSecondIntFromMessage(TMessage &message)
{
    int value;
    memcpy(&value, message.getMessage() + sizeof(int), sizeof(int));
    return value;
}

void startProgram1(std::string message)
{
    system(("./program1 " + message).c_str());
};