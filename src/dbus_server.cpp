

#include "dbus/Server.hpp"
#include "util/App.hpp"
#include <csignal>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <memory>
#include <sdbus-c++/sdbus-c++.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/syslog_sink.h>
#include <spdlog/spdlog.h>

extern "C" {
#include <getopt.h>
#include <syslog.h>
}

static void terminate(int signum)
{
	std::cout << "Interrupt signal (" << signum << ") received.\n";
	exit(signum);
}

int main(int argc, char *argv[])
{
	int exitcode = EXIT_SUCCESS;
	int opt = 0;
	int debug = false;
	app::App app{std::filesystem::path(argv[0]).filename()};
	std::vector<spdlog::sink_ptr> sinks;
	sinks.push_back(std::make_shared<spdlog::sinks::syslog_sink_st>(app.Name(), LOG_PID, LOG_AUTH, false));

	static struct option long_options[] = {
	    {"help", no_argument, NULL, 'h'},
	    {"version", no_argument, NULL, 'v'},
	    {"debug", no_argument, NULL, 'd'},
	    {NULL, 0, NULL, 0},
	};

	while ((opt = getopt_long(argc, argv, ":hvd", long_options, NULL)) != -1) {
		switch (opt) {
		case 'v':
			std::cout << app.Name() << " version " << app::App::version << std::endl;
			exit(EXIT_SUCCESS);
		case 'h':
			std::cout << app.Usage() << std::endl;
			exit(EXIT_SUCCESS);
		case 'd':
			sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_st>());
			debug = true;
			break;
		case ':':
			std::cout << "Option: -" << char(optopt) << " requires an argument." << std::endl;
			std::cout << app.Usage() << std::endl;
			exit(EXIT_FAILURE);
		case '?':
		default:
			if (optopt) {
				std::cout << "Unknown option: -" << char(optopt) << std::endl;
			} else {
				std::cout << "Unknown option: " << argv[optind - 1] << std::endl;
			}
			std::cout << app.Usage() << std::endl;
			exit(EXIT_FAILURE);
		}
	}

	spdlog::set_default_logger(std::make_shared<spdlog::logger>(app.Name(), begin(sinks), end(sinks)));
	if (debug) {
		spdlog::set_level(spdlog::level::debug);
	}

	if (std::signal(SIGTERM, terminate) == SIG_ERR) {
		spdlog::critical("Unable to initialize SIGTERM handler.");
		exit(EXIT_FAILURE);
	}

	if (std::signal(SIGINT, terminate) == SIG_ERR) {
		spdlog::critical("Unable to initialize SIGINT handler.");
		exit(EXIT_FAILURE);
	}

	// Initialize D-Bus server
	try {
		auto dbus_server = std::make_unique<app::dbus::Server>("com.cppnd.calculator");
		spdlog::info("Server will run NOW!");
		dbus_server->GetConnection().enterEventLoop();

	} catch (const std::exception &e) {
		spdlog::error(e.what());
		exit(EXIT_FAILURE);
	}

	return exitcode;
}
