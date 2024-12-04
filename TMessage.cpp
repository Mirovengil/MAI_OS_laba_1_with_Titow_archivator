#include "TMessage.h"
#include <string.h>

TMessage::TMessage()
{
}


TMessage::~TMessage()
{
}


char*   TMessage::getFirstByte()
{
    return (char*)&legacyMessage;
}


long    TMessage::getType()
{
    return legacyMessage.type;
}


char*   TMessage::getMessage()
{
    return legacyMessage.data;
}

void    TMessage::setType(long type)
{
    legacyMessage.type = type;
}

void    TMessage::setMessage(char *message)
{
    memcpy(legacyMessage.data, message, messageSize);
}

std::string TMessage::getMessageStr()
{
    std::string messageStr = "";
    for (int i = 0; i < messageSize; ++i)
        messageStr = messageStr + legacyMessage.data[i];
    return messageStr;
}
