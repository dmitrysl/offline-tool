#include "utils.h"

Utils::Utils()
{

}

Utils::~Utils()
{

}

IssueQualityItem Utils::findQualityItemById(const Dictionary &dictionary, const long itemId)
{
    if (dictionary.IssueQualityItems.isEmpty()) return IssueQualityItem{0};
    foreach (const IssueQualityItem &item, dictionary.IssueQualityItems)
    {
        if (item.Id == itemId) return item;
    }
    return IssueQualityItem{0};
}

