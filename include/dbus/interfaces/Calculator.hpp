#pragma once

#include "dbus/Server.hpp"
#include "introspection/IComCppndCalculator.hpp"
#include <sdbus-c++/sdbus-c++.h>

namespace app::dbus
{

class Server;

class Calculator : public sdbus::AdaptorInterfaces<com::cppnd::calculator_adaptor> {
public:
	Calculator(app::dbus::Server &server, sdbus::IConnection &connection, std::string objectPath);
	~Calculator();

private:
	double Add(const std::vector<double> &values) override;
	double Sub(const double &a, const double &b) override;
	double Mult(const std::vector<double> &values) override;
	double Div(const double &a, const double &b) override;

private:
	app::dbus::Server &server_;
};

} // namespace app::dbus
