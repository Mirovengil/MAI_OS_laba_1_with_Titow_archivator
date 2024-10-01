#ifndef TCORES_H
#define TCORES_H

#include <vector>

class TCore
{
private:
    std::vector <std::vector <int>> _data;
public:
    TCore(std::vector <std::vector <int>> data){_data = data;};
    int getValue(int i, int j) const {return _data[i + 1][j + 1];};
    int getSize(){return _data.size();};
};

static const TCore SobelsMatrixY(
    {{ 1,  2,  1}, 
    {  0,  0,  0}, 
    { -1, -2, -1}});

static const TCore SobelsMatrixX(
    {{ -1,  0,  +1}, 
    {  -2,  0,  +2}, 
    {  -1,  0,  +1}});


#endif //TCORES_H