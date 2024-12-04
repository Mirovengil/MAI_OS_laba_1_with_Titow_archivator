#include <iostream>
#include "TQueue.h"
#include "TTxtReader.h"
#include <string.h>

TMessage codeIntsToMessage(int numMessages, int startByte);

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        throw std::logic_error("No input file in program1 args!");
        return 1;
    }

    std::string filename = argv[1];
    std::cout << "Try to open file: " << filename << "\n";
    TQueue queue;
    TMessage message;

    TTxtReader fileReader;
    fileReader.openFile(filename);
    int indexOfMessage = 1;

    int numberOfMessages = fileReader.getNumberOfMessages();
    int numberOfBytes = fileReader.getSizeInBytes();
    message = codeIntsToMessage(numberOfMessages, numberOfBytes);
    queue.addElem(message);

    while (!fileReader.fileIsFinished())
    {
        message = fileReader.readMessage();
        std::cout << "Message #" << indexOfMessage++ << ": \"" <<  message.getMessageStr() << "\"\n";

        queue.addElem(message);
    }
    fileReader.closeFile();
}

TMessage codeIntsToMessage(int numMessages, int startByte)
{
    char buffer[TMessage::messageSize];
    memcpy(buffer, &numMessages, sizeof(int));
    memcpy(&buffer[sizeof(int)], &startByte, sizeof(int));

    TMessage message;
    message.setMessage(buffer);
    return message;
};