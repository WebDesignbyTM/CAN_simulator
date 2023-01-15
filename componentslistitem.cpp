#include "componentslistitem.h"

ComponentsListItem::ComponentsListItem(int id, std::string name) : QListWidgetItem(name.c_str())
{
    device = new NetworkDevice(id, name);
}

NetworkDevice* ComponentsListItem::getDevice()
{
    return device;
}

ComponentsListItem::~ComponentsListItem()
{
    if (device != nullptr)
        delete device;
}
