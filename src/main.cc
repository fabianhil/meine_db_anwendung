#include <iostream>
#include <CLI/CLI.hpp>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>

int main(int argc, char** argv)
{
	std::cout << "Hello World" << "\n";

	CLI::App app{"Dies ist ein Programm was uns den Umgang mit Lagerhaltungsdaten zeigen soll","Lagerhaltungsprogramm"};

    std::string filepath;
    app.add_option("-r,--read", filepath,"Path to config file")
        ->required()
        ->check(CLI::ExistingFile);
        
	try{
        app.parse(argc, argv);
    } catch(const CLI::ParseError& e){
        return app.exit(e);
    }

    std::ifstream file{filepath};
    if(!file.is_open()){
        std::cout << "Error opening file!\n";
        exit(0);
    }

    

    nlohmann::json database_object;
    try
    {
        database_object = nlohmann::json::parse(file);
    }
    catch (nlohmann::json::parse_error& ex)
    {
        std::cerr << "parse error at byte " << ex.byte << std::endl;
    }

    for (auto& element : database_object["Regale"]){
        std::cout << "Anzahl Lagerplätze: " << element["Anzahl Lagerplätze"] << std::endl;
    }

    return 0;
}