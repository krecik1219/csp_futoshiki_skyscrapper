#include <iostream>

#include <loader/FutoInstanceLoader.hpp>
#include <loader/ConfigParsingException.hpp>

using namespace std;

int main()
{
	loader::FutoInstanceLoader loader;

	cout << "starting program" << endl;
	try
	{
		auto futoshiki = loader.loadFutoInstanceConfig("data/test_futo_4_0.txt");
		cout << "calling futoshiki solve" << endl;
		futoshiki.solve();
		cout << "futoshiki solved" << endl;
	}
	catch (loader::ConfigParsingException& e)
	{
		cout << "Exception thrown: " << e.what() << endl;
	}
	catch (std::runtime_error& e)
	{
		cout << "Runtime error: " << e.what() << endl;
	}

	cout << "program finishing" << endl;
	getchar(); getchar();
	return 0;
}
