#include <iostream>
#include "TQueue.h"
#include <string.h>

int main()
{
  TQueue queue;
  TMessage message;

  message = queue.popElem();
  int numberOfMessages;
  memcpy(&numberOfMessages, message.getMessage(), sizeof(int));
  std::cout << "Messages received: " << numberOfMessages << "\n";

  for (int i = 0; i < numberOfMessages; ++i)
  {
    message = queue.popElem();
    std::cout << "Msg #" << i << ": " << message.getMessage();
    std::cout << "\nprogramm finished!\n";
    queue.close();
  };
  return 0; 
}
