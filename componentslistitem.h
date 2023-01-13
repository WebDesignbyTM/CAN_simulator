#ifndef COMPONENTSLISTITEM_H
#define COMPONENTSLISTITEM_H

#include <QListWidgetItem>
#include "NetworkDevice.h"

class ComponentsListItem : public QListWidgetItem
{
private:
    NetworkDevice* device;
public:
    ComponentsListItem(int id, std::string name);
    NetworkDevice* getDevice();
    ~ComponentsListItem();
};

#endif // COMPONENTSLISTITEM_H
