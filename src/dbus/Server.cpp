

#include "dbus/Server.hpp"
#include "util/App.hpp"
#include <spdlog/spdlog.h>

namespace app::dbus
{

Server::Server(std::string name)
    : name_{name}
    , connection_{sdbus::createSessionBusConnection(Server::name_)}
    , object_manager_{std::make_unique<app::dbus::ObjectManager>(*connection_, root_object_path_)}
    , com_cppnd_calculator_intf_{std::make_unique<app::dbus::Calculator>(*this, *connection_, root_object_path_)}
{
}

sdbus::IConnection &Server::GetConnection() const
{
	return *connection_;
}

} // namespace app::dbus
