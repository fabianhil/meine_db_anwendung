#include <iostream>
#include <CLI/CLI.hpp>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

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

    

    json database_object;
    try
    {
        database_object = json::parse(file);
    }
    catch (json::parse_error& ex)
    {
        std::cerr << "parse error at byte " << ex.byte << std::endl;
    }

    for (auto& element : database_object["Regale"]){
        std::cout << "Regal: " << element["Regal"] << std::endl;
        std::cout << "Anzahl Lagerplätze: " << element["Anzahl Lagerplätze"] << std::endl;
        std::cout << "Inhalt: " << element["Inhalt"] << std::endl;
    }

    std::cout << "\n" << std::endl;

    for (auto it = database_object["Regale"].begin(); it != database_object["Regale"].end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    std::cout << "\n" << std::endl;

    std::cout << "\n" << std::endl;

    for (auto it = database_object.begin(); it != database_object.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    std::cout << "\n" << std::endl;

    for (auto& el : database_object["Inhalt"].items())
    {
        std::cout << ", value:" << el.value() << '\n';
    }


    
json patch = R"(
        [
          { "op": "add", "path": "/hello", "value": ["world"] },
          { "op": "remove", "path": "/Inhalt", "value":["Fernseher"]}
        ]
    )"_json;

std::cout << database_object << std::endl;

    return 0;
}