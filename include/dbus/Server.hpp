
#pragma once

#include "dbus/ObjectManager.hpp"
#include "dbus/interfaces/Calculator.hpp"
#include <memory>
#include <sdbus-c++/sdbus-c++.h>
#include <string>

namespace app::dbus
{

class ObjectManager;
class Calculator;
class Server {
public:
	Server(std::string name);

	sdbus::IConnection &GetConnection() const;

private:
	const std::string root_object_path_{"/com/cppnd/calculator"};
	const std::string name_;
	std::unique_ptr<sdbus::IConnection> connection_;
	std::unique_ptr<app::dbus::ObjectManager> object_manager_;
	std::unique_ptr<app::dbus::Calculator> com_cppnd_calculator_intf_;
};

} // namespace app::dbus
