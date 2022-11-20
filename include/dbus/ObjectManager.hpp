#pragma once
#include <sdbus-c++/sdbus-c++.h>

namespace app::dbus
{
class ObjectManager : public sdbus::AdaptorInterfaces<sdbus::ObjectManager_adaptor> {
public:
	ObjectManager(sdbus::IConnection &connection, std::string objectPath)
	    : AdaptorInterfaces(connection, std::move(objectPath))
	{
		registerAdaptor();
	}

	~ObjectManager()
	{
		unregisterAdaptor();
	}
};

} // namespace app::dbus
