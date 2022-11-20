#include "dbus/interfaces/Calculator.hpp"
#include "util/App.hpp"
#include <future>
#include <spdlog/spdlog.h>

namespace app::dbus
{

Calculator::Calculator(app::dbus::Server &server, sdbus::IConnection &connection, std::string objectPath)
    : AdaptorInterfaces(connection, std::move(objectPath))
    , server_{server}
{
	registerAdaptor();
}

Calculator::~Calculator()
{
	unregisterAdaptor();
}

double Calculator::Add(const std::vector<double> &values)
{
	double result = 0.0;
	std::string log{"Add method called with: "};
	std::for_each(values.begin(), values.end(), [&result, &log](const double v) {
		result += v;
		log += std::to_string(v) + ", ";
	});

	spdlog::info(log);
	return result;
}

double Calculator::Sub(const double &a, const double &b)
{
	spdlog::info("Sub method called with: " + std::to_string(a) + ", " + std::to_string(b));
	double result = 0.0;
	std::future<void> fut = std::async(std::launch::async, [&result, a, b]() { result = a - b; });
	fut.get();
	return result;
}

double Calculator::Mult(const std::vector<double> &values)
{
	double result = 0.0;
	double prev = 1;
	std::string log{"Mult method called with: "};
	std::for_each(values.begin(), values.end(), [&](const double v) {
		prev *= v;
		result = prev;
		log += std::to_string(v) + ", ";
	});
	spdlog::info(log);
	return result;
}

double Calculator::Div(const double &a, const double &b)
{
	spdlog::info("Div method called with: " + std::to_string(a) + ", " + std::to_string(b));
	return a / b;
}

} // namespace app::dbus
