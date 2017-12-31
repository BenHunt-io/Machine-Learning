#ifndef DATAREADER_H
#define DATAREADER_H
#include <Plant.h>

class DataReader
{
    public:
        DataReader();
        static void read(Plant[]);
        virtual ~DataReader();
    protected:

    private:
};

#endif // DATAREADER_H
