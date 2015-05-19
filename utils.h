#ifndef UTILS_H
#define UTILS_H


#include "entities.h"

class Utils
{
public:
    Utils();
    ~Utils();

    static IssueQualityItem findQualityItemById(const Dictionary &dictionary, const long itemId);
};

#endif // UTILS_H
