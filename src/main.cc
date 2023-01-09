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

for (auto& element : database_object["Regale"])
{
    
}


for (auto& change : database_object["Regale"])
{
    std::cout << "Welchen Lagerinhalt wollen sie verändern?" << "\n";

    std::cout << change["Inhalt"] << "\n";

    std::string inhalt_neu;

    std::cin >> inhalt_neu;

    for (auto& inhalt : change["Inhalt"])
    {
        std::cout << "neuer Inhalt = " << inhalt_neu << "Inhalt =" << inhalt << std::endl;
        if(inhalt_neu == inhalt)
        {
            std::cin >> inhalt;

            std::cout << inhalt << std::endl;

            break;
        }
    }

    std::cout << "Neuer Inhalt:" << change["Inhalt"] << std::endl;
}



    return 0;
}